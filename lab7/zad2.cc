#include <iostream>
#include <omp.h>
using namespace std;
int main()
{
    int id;
    int nthreads;

#pragma omp parallel private(id)
    {
        id = omp_get_thread_num();

#pragma omp single
        nthreads = omp_get_num_threads();

#pragma omp for schedule(static, 1)
        for (int i = 0; i < 16; ++i)
#pragma omp critical
            cout << " Obrót pętli " << i << ", wątek nr " << id << " z " << nthreads << endl;
    }
    return 0;
}
