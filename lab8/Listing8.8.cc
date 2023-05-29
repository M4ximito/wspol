#include <omp.h>       //Użycie OpenMP
#include <stdio.h>     //Dostarcza I/O
#include <stdlib.h>    //Użycie NULL
#include <unistd.h>    //Użycie usleep (sleep w mikrosekundach)
#include <time.h>      //Użycie time w geneatorze liczb pseudolosowych
#include <semaphore.h> //Użycie semaforów

#define LICZBA_FILOZOFOW 5
#define liczbaPosilkow 3

const int MAX_OPOZNIENIE = 1000;

sem_t widelec[LICZBA_FILOZOFOW];
sem_t kelner;

void Filozof()
{
    int numer = omp_get_thread_num();
    int prawyWidelec;
    int lewyWidelec;

    lewyWidelec = numer;
    prawyWidelec = (numer + 1) % LICZBA_FILOZOFOW;

    int zjedzonychPosilkow;
    time_t t;
    int czasPosilku;

    for (zjedzonychPosilkow = 0; zjedzonychPosilkow < liczbaPosilkow; zjedzonychPosilkow++)
    {
        sem_wait(&kelner);

        sem_wait(&widelec[lewyWidelec]);
        sem_wait(&widelec[prawyWidelec]);

        sem_post(&kelner);

        srand(100 * omp_get_thread_num() + 7);
        czasPosilku = (rand() % (MAX_OPOZNIENIE + 1));
        printf("Filozof %d je %d posiłek przez najbliższe %d ms\n", numer, zjedzonychPosilkow, czasPosilku);
        usleep(czasPosilku);
        printf("Filozof %d skończył jeść %d posiłek\n", numer, zjedzonychPosilkow);

        sem_post(&widelec[lewyWidelec]);
        sem_post(&widelec[prawyWidelec]);
    }
}

int main(int argc, char **argv)
{
    int i;

    // Inicjalizacja semaforów
    sem_init(&kelner, 0, LICZBA_FILOZOFOW - 1);
    for (i = 0; i < LICZBA_FILOZOFOW; i++)
    {
        sem_init(&widelec[i], 0, 1);
    }

    // Tworzenie wątków filozofów i ich uruchamianie
    #pragma omp parallel num_threads(LICZBA_FILOZOFOW)
    {
        Filozof();
    }

    // Czekanie na zakończenie jedzenia przez filozofów
    for (i = 0; i < LICZBA_FILOZOFOW; i++)
    {
        sem_destroy(&widelec[i]);
    }
    sem_destroy(&kelner);

    return 0;
}
