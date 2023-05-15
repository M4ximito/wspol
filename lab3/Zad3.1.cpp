#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

#include <condition_variable>
#include <random>
using namespace std;
const int CZAS_PRACY = 5;
template <typename TypDanych>

class Monitor
{
private:
    TypDanych dane;
    bool saDane;
    mutex mutexDane;
    condition_variable warunekSaNoweDane;
    condition_variable warunekZabranoDane;

public:
    Monitor()
    {
        saDane = false;
    }
    void zapisz(TypDanych noweDane)
    {
        unique_lock<mutex> blokada(mutexDane);
        while (saDane)
            warunekZabranoDane.wait(blokada);
        saDane = true;
        dane = noweDane;
        warunekSaNoweDane.notify_one();
    }
    TypDanych odczytaj()
    {
        unique_lock<mutex> blokada(mutexDane);
        while (!saDane)
            warunekSaNoweDane.wait(blokada);
        saDane = false;
        warunekZabranoDane.notify_one();
        return dane;
    }
};

class Producent
{
private:
    int czas;

    Monitor<char> &pojemnik;

    char biezacyZnak;

    minstd_rand generator;
    uniform_int_distribution<char> rozklad;

public:
    Producent(Monitor<char> &_pojemnik) : czas(0), pojemnik(_pojemnik),
                                          biezacyZnak('a'), generator(random_device()()),
                                          rozklad('a', 'z') {}
    void operator()()
    {
        while (czas < CZAS_PRACY)
        {
            pojemnik.zapisz(biezacyZnak);
            biezacyZnak = (biezacyZnak + 1 - 97) % 25 + 97;
            this_thread::sleep_for(chrono::seconds(1));
            ++czas;
        }
        pojemnik.zapisz(EOF);
    }
};

class Konsument
{
private:
    Monitor<char> &pojemnik;

public:
    Konsument(Monitor<char> &_pojemnik) : pojemnik(_pojemnik) {}
    void operator()()
    {
        char znak = pojemnik.odczytaj();
        while (znak != EOF)
        {
            cout << znak << endl;
            znak = pojemnik.odczytaj();
        }
    }
};

int main(int argc, char **argv)
{
    random_device r;
    minstd_rand generator(r());

    Monitor<char>
        pojemnik;
    Konsument konsument(pojemnik);
    Producent producent(pojemnik);
    thread wk(konsument);
    thread wp(producent);
    wp.join();
    wk.join();
    return (EXIT_SUCCESS);
}