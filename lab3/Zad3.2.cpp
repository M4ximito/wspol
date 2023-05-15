#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

#include <condition_variable>

#include <random>

using namespace std;

const int CZAS_PRACY = 5;
mutex konsolaMutex; //*******************

template <typename TypDanych>
class Monitor
{
private:random
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
    uniform_int_distribution<> distr; //************
    int id;                           //*******
public:
    Producent(Monitor<char> &_pojemnik, int _id) :

                                                   czas(0), pojemnik(_pojemnik),
                                                   biezacyZnak('a'), generator(random_device()()),
                                                   rozklad('a', 'z'), id(_id), distr(1, 10) //**********
    {
    }

    void operator()()
    {
        while (czas < CZAS_PRACY)
        {

            pojemnik.zapisz(biezacyZnak);
            {
                lock_guard<mutex> blokada(konsolaMutex); //*************
                cout << "Producent " << id << " znak " << biezacyZnak << endl;
            }

            biezacyZnak = (biezacyZnak + 1 - 97) % 25 + 97;

            this_thread::sleep_for(chrono::milliseconds(80));
            ++czas;
        }
        pojemnik.zapisz(EOF);
    }
};

class Konsument
{
private:
    Monitor<char> &pojemnik;
    int id; //********

public:
    Konsument(Monitor<char> &_pojemnik, int _id) : pojemnik(_pojemnik), id(_id) {} //**********

    void operator()()
    {
        char znak = pojemnik.odczytaj();
        while (znak != EOF)
        {
            //**************
            {
                lock_guard<mutex> blokada(konsolaMutex);
                cout << "Konsument " << id << " odczytal znak " << znak << endl;
            }
            znak = pojemnik.odczytaj();
        }
    }
};

int main(int argc, char **argv)
{
    vector<thread> watki; //**********
    random_device r;
    minstd_rand generator(r());
    Monitor<char> pojemnik;
    //****************
    for (int i = 0; i < thread::hardware_concurrency(); i++)
    {
        watki.push_back(thread(Konsument(pojemnik, i)));
        watki.push_back(thread(Producent(pojemnik, i)));
    }

    for (thread &w : watki)
    {
        w.join();
    }
    return (EXIT_SUCCESS);
}
