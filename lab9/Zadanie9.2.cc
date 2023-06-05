#include <stdio.h>
#include <mpi.h>

#define MAX_MESSAGE_LENGTH 100

int main(int argc, char **argv)
{
    int rank;
    int num_processes;
    char greeting[MAX_MESSAGE_LENGTH];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_processes);

    if (rank == 0)
    {
        for (int i = 1; i < num_processes; i++)
        {
            sprintf(greeting, "Proces %d przesyła pozdrowienia pozostałym procesom!", rank);
            MPI_Send(greeting, MAX_MESSAGE_LENGTH, MPI_CHAR, i, 0, MPI_COMM_WORLD);
        }
    }
    else
    {
        MPI_Recv(greeting, MAX_MESSAGE_LENGTH, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Proces %d odebrał: %s\n", rank, greeting);
    }

    MPI_Finalize();

    return 0;
}
