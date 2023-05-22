#include <iostream>
#include <omp.h>

using namespace std;

int main()
{
    int tab[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int b = 0;
    
    #pragma omp parallel for reduction(+:b)
    for (int i = 0; i < 10; ++i)
        b += tab[i];
    
    cout << "b = " << b << endl;
    return 0;
}
