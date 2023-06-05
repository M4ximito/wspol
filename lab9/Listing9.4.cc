#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    int size, rank;
    int tag, from, to;
    double data;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank != 0 && rank != 3)
        printf("Proces %d z %d w komunikatorze - leniuchuje.\n", rank, size);

    else if (rank == 0)
    {
        to = 3;
        tag = 2;
        data = 20.22;
        MPI_Send(&data, 1, MPI_DOUBLE, to, tag, MPI_COMM_WORLD);
        printf("Proces %d pracuje, wysłał: %5.2f do procesu %d\n", rank, data, to);
    }

    else if (rank == 3)
    {
        from = 0;
        tag = 2;
        MPI_Recv(&data, 1, MPI_DOUBLE, from, tag, MPI_COMM_WORLD, &status);
        printf("Proces %d pracuje, odebrał: %5.2f od procesu %d\n", rank, data, from);
    }

    MPI_Finalize();

    return 0;
}