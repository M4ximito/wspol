#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    int rank;
    int proces;
    int namelength;
    char processor_name[MPI_MAX_PROCESSOR_NAME];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &proces);
    MPI_Get_processor_name(processor_name, &namelength);

    printf("Proces %d z %d w komunikatorze, działjący na komputerze %s.\n", rank, proces, processor_name);

    MPI_Finalize();

    return 0;
}