#include <stdlib.h>
#include <iostream>
#include <thread>
#include <chrono>
// mutex = mutual exclusion - umożliwia szeregowanie dostępu do wspólnych zasobów

#include <mutex>

using namespace std;

const int OPOZNIENIE = 100;
int licznik = 50;

// deklaracja mutexu dla licznika, który jest wspólnym zasobem
mutex licznikMutex;

class Watek
{
private:
    int numer;

public:
    Watek(int _numer) : numer(_numer) {}
    void operator()()
    {
        while (true)
        {
            {
                lock_guard<mutex> blokada(licznikMutex);
                // licznikMutex.lock();
                
                if (licznik <= 0)
                    break;
                cout << "w: " << numer << " l: " << licznik << endl;
                --licznik;
                // snizu dodane w first version stroki 37 nie bylo
                // licznikMutex.unlock();     
            }
            this_thread::sleep_for(chrono::microseconds(OPOZNIENIE));       
        }
    }
};
int main(int argc, char **argv)
{
    thread w1(Watek(1));
    thread w2(Watek(2));
    w1.join();
    w2.join();
    return (EXIT_SUCCESS);
}