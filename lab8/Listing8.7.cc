/* C++, problem N Krolowych, algorytm z nawrotami
gcc -O -o nqueensserial nqueensserial.c
./nqueens liczba_krolowych
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>
#define MAX_N 16

int pole_bezpieczne(int krolowa_w_wierszu[MAX_N], int n)
{
    int i, j;
    for (i = 0; i < n; i++)
        for (j = i + 1; j < n; j++)
        {

            if (krolowa_w_wierszu[i] == krolowa_w_wierszu[j])
                return 0;

            if (krolowa_w_wierszu[i] - krolowa_w_wierszu[j] == i - j ||
                krolowa_w_wierszu[i] - krolowa_w_wierszu[j] == j - i)
                return 0;
        }
    return 1;
}

void drukuj_szachownice(int krolowa_w_wierszu[MAX_N], int n)
{
    int i;
    {
        printf("\n");
        for (i = 0; i < n; i++)
        {
            int j;
            for (j = 0; j < n; j++)
            {
                if (krolowa_w_wierszu[i] == j)
                    printf("1 ");
                else
                    printf("0 ");
            }
            printf("\n");
        }
        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    int liczba_krolowych;
    long int max_iteracji = 1;
    double czas;
    int liczba_rozwiazan = 0;
    int liczba_watkow;
    int i;

    liczba_krolowych = (argc > 1) ? atoi(argv[1]) : 4;
    for (i = 0; i < liczba_krolowych; i++)
        max_iteracji *= liczba_krolowych;

    int iteracja;
    for (iteracja = 0; iteracja < max_iteracji; iteracja++)
    {
        int zmienna_pomocnicza = iteracja;
        int i;
        int krolowa_w_wierszu[MAX_N];

        for (i = 0; i < liczba_krolowych; i++)
        {
            krolowa_w_wierszu[i] = zmienna_pomocnicza % liczba_krolowych;
            zmienna_pomocnicza /= liczba_krolowych;
        }
        if (pole_bezpieczne(krolowa_w_wierszu, liczba_krolowych))
        {
            drukuj_szachownice(krolowa_w_wierszu, liczba_krolowych);
            liczba_rozwiazan++;
        }
    }

    printf("Liczba rozwiązań: %d\n", liczba_rozwiazan);

    return 0;
}