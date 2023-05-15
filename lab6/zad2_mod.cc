#include <iostream>
#include <omp.h>
using namespace std;

int main()
{
    int tid;
    int nthreads = omp_get_max_threads();

    const int bufsize = 256;
    char buffer[nthreads][bufsize];
    for (int i = 0; i < nthreads; ++i) {
        sprintf(buffer[i], "Wątek nr %d z %d\n", i, nthreads);
    }

#pragma omp parallel shared(buffer)
    {
        tid = omp_get_thread_num();

        cout << buffer[tid];
    }

    return 0;
}
