// g++ -std=c++11 -o zad1 zad1.cpp -pthread
// ./zad1

//Maksim Maltsau
//s96513@pollub.edu.pl

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>


using namespace std;

mutex mutex_code;

void thread_work(int thread_number) {
    for (int i = 0; i < 5; i ++) {
        lock_guard<mutex> guard (mutex_code);
        cout << "i = " << i << endl;
        cout << "number = " << thread_number << endl;
        cout << "id = " << std::this_thread::get_id() << endl;
        std::this_thread::sleep_for(chrono::milliseconds(50));
    }
}

int main() {
    thread th1(thread_work, 1);
    thread th2(thread_work, 2);

    th1.join();
    th2.join();
}
