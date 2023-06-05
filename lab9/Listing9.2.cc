#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    int rank;
    int proces;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &proces);

    printf("Proces %d z %d w komunikatorze.\n", rank, proces);

    MPI_Finalize();

    return 0;
}