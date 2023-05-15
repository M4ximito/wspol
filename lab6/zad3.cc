////g++ -o zad3 zad3.cc -fopenmp
#include <iostream>
#include <omp.h>
using namespace std;

int main()
{
    int id;
#pragma omp parallel private(id)
    {
        int id = omp_get_thread_num();
        int nthreads = omp_get_max_threads();
#pragma omp critical
        cout << "Wątek nr " << id << " z " << nthreads << endl;
    }
    return 0;
}

