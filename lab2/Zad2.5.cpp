// g++ -std=c++11 -o program_cpp_multith Zad2.cpp -pthread
// lub
// g++ Zad2.cpp -o tw_watkow -std=c++11 -pthread
// lub:
// g++ Zad2.cpp -o tw_watkow -std=c++17 -pthread

// ./program_cpp_multith
// I dont know kak eto delac pojetomu niejestety
#include <thread>
#include <chrono>
#include <iostream>
#include <cmath>

using namespace std;

const int LICZBA_PUNKTOW = 10;

double a = 0.0;
double b = 1.0;
double wynik = 0.0;

void calkowanie_m_prostokatow()
{
    cout << "Wątek pracuje..." << endl;
    double h = (b - a) / LICZBA_PUNKTOW;
    double s = 0.0;
    for (int i = 0; i < LICZBA_PUNKTOW; i++)
    {

        this_thread::sleep_for(chrono::milliseconds(10));
        // f(x)=x
        s += h * (a + i * h);
    }

    wynik = s;
    cout << "Wątek się zakończył..." << endl;
}

int main(int argc, char *argv[])
{
    double wynik_dokladny;

    thread watek(calkowanie_m_prostokatow);

    cout << "Sprzętowa współbieżność: " << thread::hardware_concurrency() << endl;
    cout << "ID wątku: " << watek.get_id() << endl;

    wynik_dokladny = a * (b - a) + (b - a) * (b - a) / 2.0;
    cout << "wynik dokladny policzony przez watek glowny = " << wynik_dokladny << endl;

    watek.join();
    cout << "wynik calkowania numerycznego policzony przez watek dodatkowy = " << wynik << endl;
    cout << "blad = " << wynik_dokladny - wynik << ",\t blad w % = " << (wynik_dokladny - wynik) / wynik_dokladny * 100 << endl;
    return EXIT_SUCCESS;
}