#include <iostream>
#include <omp.h>
#include <cstdlib>
#include <unistd.h>

using namespace std;

int main()
{
    int licznik = 0;
    #pragma omp parallel num_threads(8)
    {
        for (int i = 0; i < 100; ++i)
            #pragma omp atomic
            licznik++;
    }
}
