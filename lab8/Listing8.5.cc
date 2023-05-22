#include <iostream>
#include <omp.h>
#include <cstdlib>
#include <unistd.h>
using namespace std;
int main()
{
    srand(time(NULL));
    int suma = 0;
    int x[8];
#pragma omp parallel num_threads(8)
    {
#pragma omp for
        for (int i = 0; i < 8; i++)
        {
            int id = omp_get_thread_num();
            usleep((100 + rand() % 400) * 1000);
            x[id] = id;
        }
#pragma omp for
        for (int i = 0; i < 8; i++)
            suma += x[i];
#pragma omp master
        cout << "suma = " << suma << endl;
    }
    return 0;
}