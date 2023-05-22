#include <iostream>
#include <omp.h>
using namespace std;
int main()
{
    int tab[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, threads;
    long int a = -1;
    int a_thr = 1;
    threads = omp_get_num_procs();
    omp_set_num_threads(threads);

#pragma omp parallel firstprivate(a_thr) shared(a)
    {
#pragma omp for
        for (int i = 0; i < 10; i++)
            a_thr *= tab[i];

#pragma omp critical
        a *= a_thr;
    }

    cout << "a = " << a << endl;
    return 0;
}
