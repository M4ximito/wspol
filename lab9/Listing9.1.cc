// mpic++ -o program program.c

#include <stdio.h>
#include <mpi.h>
int main(int argc, char **argv)
{
    int rank;
    int p;
    MPI_Init(&argc, &argv);
    printf("Hello, world!\n");

    MPI_Finalize();

    return 0;
}