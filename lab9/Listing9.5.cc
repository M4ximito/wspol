#include <stdio.h>
#include <math.h>
#include <mpi.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int my_rank, p;
    int i, n;
    long double my_pi, pi, h, sum, x;

    if (argc < 2)
    {
        printf("Poprawne użycie programu: ./program liczba_przedziałów_całkowania\n");
        exit(1);
    }

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    if (my_rank == 0)
        n = atoi(argv[1]);

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    h = 1.0 / (long double)n;

    /* Całkowanie metodą trapezów */
    sum = 0.0;
    for (i = my_rank; i < n; i += p)
    {
        x = h * ((long double)i + 0.5);
        sum += 4.0 / (1.0 + x * x);
    }
    my_pi = h * sum;

    MPI_Reduce(&my_pi, &pi, 1, MPI_LONG_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (my_rank == 0)
        printf("pi=%.16Lf\n", pi);

    MPI_Finalize();

    return 0;
}