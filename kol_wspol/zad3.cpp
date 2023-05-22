//g++ -std=c++11 -o zad3 zad3.cpp -pthread semafor.cpp
//Maksim Maltsau
//s96513@pollub.edu.pl

#include <mutex>
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include "semafor.h"
 
using namespace std;
 
Semafor semafor_wyswietlania(3); 
const int liczba_watkow = 10;
vector<thread> watki;
 
void thread_work(int thread_number)
{
    for (int i = 0; i < 10; i++)
    {
        semafor_wyswietlania.czekaj(); 
        cout << "i = " << i << endl;
        cout << " numer = " << thread_number << endl;
        cout << " id = " << this_thread::get_id() << endl;
        semafor_wyswietlania.sygnalizuj(); 
        this_thread::sleep_for(chrono::milliseconds(50));
    }
}
 
int main()
{
    for (int i = 0; i < liczba_watkow; i++)
    {
        watki.emplace_back(thread_work, i); 
    }
    for (auto &watek : watki)
    {
        watek.join(); 
    }
 
    return 0;
}