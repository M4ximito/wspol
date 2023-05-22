#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define M 16
#define N 16

void mxv(int m, int n, double *a, double *b, double *c)
{
    #pragma omp parallel for
    for (int i = 0; i < m; i++)
    {
        a[i] = 0.0;

        for (int j = 0; j < n; j++)
            a[i] += b[i * n + j] * c[j];
    }
}

int main()
{
    double A[M], B[M * N], C[N];

    int k, l;
    // Inicjalizacja macierzy
    for (k = 0; k < M; k++)
    {
        for (l = 0; l < N; l++)
        {
            C[l] = l * 1.0;
            B[k * N + l] = l * 0.1 + k;
        }
    }

    // Obliczanie wektora A
    mxv(M, N, A, B, C);

    // Wyświetlanie wyniku
    for (k = 0; k < M; k++)
        printf("%5.2f ", A[k]);
    printf("\n");

    return 0;
}
