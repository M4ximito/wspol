// g++ -std=c++11 -o kek lab5.cpp -pthread
// ./kek

#include <thread>
#include <mutex>
#include <random>
#include <iostream>
#include <vector>
#include "semafor.h"

using namespace std;

// czas jedzenia w ms
const int MAX_OPOZNIENIE = 1000;
random_device rd;
minstd_rand generator(rd());
uniform_int_distribution<int> rozklad(0, MAX_OPOZNIENIE);

const int LICZBA_FILOZOFOW = 5;
const int LICZBA_POSILKOW = 3;

class Filozof
{
private:
    int numer;
    int lewyWidelec;
    int prawyWidelec;
    int zjedzonychPosilkow;

public:
    Filozof(int n) : numer(n), zjedzonychPosilkow(0)
    {
        // lewyWidelec = //obliczyć numer lewego widelca
        // prawyWidelec = //obliczyć numer prawego widelca
    }

    void operator()()
    {
        while (zjedzonychPosilkow < LICZBA_POSILKOW)
        {
            int czasPosilku = rozklad(generator);
            cout << "Filozof " << numer << " je "
                 << zjedzonychPosilkow << " posilek przez najblizsze "
                 << czasPosilku << " ms" << endl;
            // filozof dad

            this_thread::sleep_for(chrono::milliseconds(czasPosilku));
            ++zjedzonychPosilkow;
            cout << "Filozof " << numer << " skonczyl jesc"
                 << zjedzonychPosilkow << " posilek " << endl;
            // filozof rozmyśla między posiłkami
        }
        cout << "Filozof " << numer << " sie najadl" << endl;
    }
};

int main(int argc, char **argv)
{
    // tworzenie filozofow
    vector<thread> filozofowie;

    for (int i = 0; i < LICZBA_FILOZOFOW; ++i)
        filozofowie.emplace_back(Filozof(i));

    // czekanie na zakonczenie
    for (thread &f : filozofowie)
        f.join();

    return (EXIT_SUCCESS);
}