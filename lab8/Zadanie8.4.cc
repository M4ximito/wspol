#include <omp.h>       // Użycie OpenMP
#include <stdio.h>     // Dostarcza I/O
#include <stdlib.h>    // Użycie NULL
#include <unistd.h>    // Użycie usleep (sleep w mikrosekundach)
#include <time.h>      // Użycie time w generatorze liczb pseudolosowych
#include <pthread.h>   // Użycie biblioteki wątków POSIX
#include <semaphore.h> // Użycie semaforów

#define LICZBA_FILOZOFOW 5
#define liczbaPosilkow 3

const int MAX_OPOZNIENIE = 1000;

pthread_mutex_t mutex_widelec[LICZBA_FILOZOFOW];
sem_t kelner;

class Filozof
{
public:
    int numer;
    int lewyWidelec;
    int prawyWidelec;

    Filozof(int num) : numer(num), lewyWidelec(num), prawyWidelec((num + 1) % LICZBA_FILOZOFOW) {}

    void operator()()
    {
        int zjedzonychPosilkow;
        int czasPosilku;

        for (zjedzonychPosilkow = 0; zjedzonychPosilkow < liczbaPosilkow; zjedzonychPosilkow++)
        {
            sem_wait(&kelner);

            pthread_mutex_lock(&mutex_widelec[lewyWidelec]);
            pthread_mutex_lock(&mutex_widelec[prawyWidelec]);

            sem_post(&kelner);

            srand(100 * numer + 7);
            czasPosilku = (rand() % (MAX_OPOZNIENIE + 1));
            printf("Filozof %d je %d posiłek przez najbliższe %d ms\n", numer, zjedzonychPosilkow, czasPosilku);
            usleep(czasPosilku);
            printf("Filozof %d skończył jeść %d posiłek\n", numer, zjedzonychPosilkow);

            pthread_mutex_unlock(&mutex_widelec[lewyWidelec]);
            pthread_mutex_unlock(&mutex_widelec[prawyWidelec]);
        }
    }
};

int main(int argc, char **argv)
{
    int i;

    // Inicjalizacja semaforów
    sem_init(&kelner, 0, LICZBA_FILOZOFOW - 1);
    for (i = 0; i < LICZBA_FILOZOFOW; i++)
    {
        pthread_mutex_init(&mutex_widelec[i], NULL);
    }

    // Tworzenie wątków filozofów i ich uruchamianie
    Filozof filozofowie[LICZBA_FILOZOFOW] = {Filozof(0), Filozof(1), Filozof(2), Filozof(3), Filozof(4)};
    #pragma omp parallel num_threads(LICZBA_FILOZOFOW)
    {
        int numer = omp_get_thread_num();
        Filozof filozof = filozofowie[numer];
        filozof();
    }

    // Czekanie na zakończenie jedzenia przez filozofów
    for (i = 0; i < LICZBA_FILOZOFOW; i++)
    {
        pthread_mutex_destroy(&mutex_widelec[i]);
    }
    sem_destroy(&kelner);

    return 0;
}
