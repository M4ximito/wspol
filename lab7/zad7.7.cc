#include <iostream>
#include <omp.h>
using namespace std;
int main()
{
    int tab[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, threads;
    long int a = 1;
    threads = omp_get_num_procs();
    omp_set_num_threads(threads);
#pragma omp parallel
    {
#pragma omp for reduction(* : a)
        for (int i = 0; i < 10; ++i)
            a *= tab[i];
    }
    cout << "a = " << a << endl;
    return 0;
}
