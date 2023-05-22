// definiowanie ilości wątków w klauzuli "num_threads"
////g++ -o zad1 zad1.cc -fopenmp
#include <iostream>
#include <omp.h>
using namespace std;

int main()
{
#pragma omp parallel num_threads(4)
    {
#pragma omp critical
        cout << "Wątek nr " << omp_get_thread_num() << " z "
             << omp_get_num_threads() << endl;
    }
    cout << endl;

#pragma omp parallel num_threads(2)
    {
#pragma omp critical
        cout << "Wątek nr " << omp_get_thread_num() << " z "
             << omp_get_num_threads() << endl;
    }
}
