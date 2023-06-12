#include <iostream>
#include <random>
#include <omp.h>

const int ROWS = 15;
const int COLS = 15;

int main()
{
    int matrix[ROWS][COLS];

#pragma omp parallel for
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {

            unsigned int seed = omp_get_thread_num() + 1;
            std::default_random_engine generator(seed);
            std::uniform_int_distribution<int> distribution(0, 9);

            matrix[i][j] = distribution(generator);
        }
    }

    int sum = 0;
#pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            sum += matrix[i][j];
        }
    }

    std::cout << "Tablica 2D:" << std::endl;
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Suma elementów: " << sum << std::endl;

    return 0;
}
