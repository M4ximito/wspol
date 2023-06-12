//
//Maksim Maltsau
//
//96513
//
#include <iostream>
#include <thread>
#include <mutex>

std::mutex console_mutex;

void print_thread_id(int x, int thread_num, int sleep_time)
{
    for (int i = 0; i <= x; i++)
    {
        std::lock_guard<std::mutex> lock(console_mutex); 
        std::cout << "i = " << i << ", numer = " << thread_num << std::endl;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time)); 
}

int main()
{
    int num_threads = std::thread::hardware_concurrency(); 
    std::cout << "Liczba procesorów: " << num_threads << std::endl;

    int x = 5;
    int sleep_time = 1000;
    std::thread *threads = new std::thread[num_threads];

    for (int i = 0; i < num_threads; i++)
    {
        threads[i] = std::thread(print_thread_id, x, i, sleep_time);
    }

    for (int i = 0; i < num_threads; i++)
    {
        threads[i].join();
    }

    delete[] threads;

    return 0;
}
