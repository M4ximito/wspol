#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool jest_liczba_pierwsza(int n)
{
    int i;
    for (i = 2; i < n; i++)
        if (n % i == 0)
            return false;
    return true;
}

int main(int argc, char *argv[])
{
    int i;
    int total = 0;
    int N = atoi(argv[1]);
    for (i = 2; i < N; i++)
        if (jest_liczba_pierwsza(i))
            total++;
    printf("Liczb pierwszych w przedziale: 2...%d jest: %d\n", N,
           total);
    return 0;
}
