#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>

#define LICZBA_FILOZOFOW 5
#define liczbaPosilkow 3

const int MAX_OPOZNIENIE = 1000;
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

    for (zjedzonychPosilkow = 0; zjedzonychPosilkow <
                                 liczbaPosilkow;
         zjedzonychPosilkow++)
    {

        srand(100 * omp_get_thread_num() + 7);
        czasPosilku = (rand() % (MAX_OPOZNIENIE + 1));
        printf("Filozof %d je %d posiłek przez najbliższe %d ms\n", numer, zjedzonychPosilkow, czasPosilku);
        usleep(czasPosilku);
        printf("Filozof %d skończył jeść %d posiłek\n", numer,
               zjedzonychPosilkow);
    }
}

int main(int argc, char **argv)
{
    int i;

    return 0;
}