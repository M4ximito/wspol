#include <iostream>
#include <omp.h>
using namespace std;

int main()
{
    int id;
#pragma omp parallel shared(id)
    {
#pragma omp critical
        {
            id = omp_get_thread_num();
            int nthreads = omp_get_max_threads();
            cout << "Wątek nr " << id << " z " << nthreads << endl;
        }
    }
    return 0;
}
