#include <iostream>
#include <chrono>
#include <thread>


const int ARRAY_SIZE = 100;
const int NUM_ELEMENTS = 60;
const int NUM_THREADS = 3;

void sequential_fill_array(int* array)
{
    for (int i = 0; i < NUM_ELEMENTS; i++)
    {
        array[i] = i + 1;
    }
}

void parallel_fill_array(int* array, int thread_id)
{
    int chunk_size = NUM_ELEMENTS / NUM_THREADS;
    int start_index = thread_id * chunk_size;
    int end_index = start_index + chunk_size;

    for (int i = start_index; i < end_index; i++)
    {
        array[i] = i + 1;
    }
}

void display_array(const int* array)
{
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

int main()
{
    int array1[ARRAY_SIZE];
    int array2[ARRAY_SIZE];

    auto start_sequential = std::chrono::high_resolution_clock::now();
    sequential_fill_array(array1);
    auto end_sequential = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> sequential_time = end_sequential - start_sequential;

    auto start_parallel = std::chrono::high_resolution_clock::now();
    std::thread threads[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++)
    {
        threads[i] = std::thread(parallel_fill_array, array2, i);
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        threads[i].join();
    }

    auto end_parallel = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> parallel_time = end_parallel - start_parallel;

    std::cout << "Tablica 1: ";
    display_array(array1);

    std::cout << "Tablica 2: ";
    display_array(array2);

    std::cout << "Czas generowania sekwencyjnego: " << sequential_time.count() << " ms" << std::endl;
    std::cout << "Czas generowania równoległego: " << parallel_time.count() << " ms" << std::endl;

    return 0;
}
