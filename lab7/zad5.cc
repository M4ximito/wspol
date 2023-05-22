#include <stdio.h>
#include <stdlib.h>
#define M 16
#define N 16

void mxv(int m, int n, double *a, double *b, double *c)
{
    int i, j;
    for (i = 0; i < m; i++)
    {
        a[i] = 0.0;
        // pętla obliczająca iloczyn i-tego wiersza

        for (j = 0; j < n; j++)
            a[i] += b[i * n + j] * c[j]; // a[i]=b[i][j]*c[j]
    }
}

int main()
{
    double A[M], B[M * N], C[N];
    int k, l;
    // inicjalizujemu macierze
    for (k = 0; k < M; k++)
        for (l = 0; l < N; l++)
        {
            C[l] = l * 1.0;
            B[k * N + l] = l * 0.1 + k;
        }
    // obliczamy wektor A
    mxv(M, N, A, B, C);
    for (k = 0; k < M; k++)
        printf("%5.2f ", A[k]);
    printf("\n");
    return 0;
}