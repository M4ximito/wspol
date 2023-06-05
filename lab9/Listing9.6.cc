#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    double t1, t2;

    MPI_Init(0, 0);

    t1 = MPI_Wtime();
    sleep(1);
    t2 = MPI_Wtime();
    printf("MPI_Wtime zmierzył czas 1-no sekundowego sleep-a i otrzymał: %1.2f\n", t2 - t1);

    MPI_Finalize();
    return 0;
}