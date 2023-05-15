#include <thread>
#include <chrono>
#include <iostream>
#include <cmath>
#include <bits/stdc++.h>
using namespace std;

const int LICZBA_PUNKTOW = 10;

int main(int argc, char *argv[])
{
   // w zmiennych globalnych przechowywane są dane potrzebne
   // do działania wątku
   double a = 0.0; // zakres całkowania
   double b = 1.0;
   double wynik = 0.0; // wartosc całki
   // funkcja zawiera zadanie do wykonania w osobnym wątku
   double wynik_dokladny;
   // tworzenie wątku
   thread watek([](double a, double b, double *w)
                {
cout << "Wątek pracuje..." << endl;
double h = (b - a) / LICZBA_PUNKTOW;
double s = 0.0;
for (int i = 0; i < LICZBA_PUNKTOW; i++) {
//lekkie spowolnienie wątku (wartość w milisekundach)
this_thread::sleep_for(chrono::milliseconds(10));
// f(x)=x
s += h * (a + i * h);
}
 
*w = s;
cout << "Wątek się zakończył..." << endl; },
                a, b, &wynik);

   // główny wątek w między czasie może coś zrobić
   // np. sprawdzić możliwości sprzętu
   cout << "Sprzętowa współbieżność: " << thread::hardware_concurrency() << endl;
   cout << "ID wątku: " << watek.get_id() << endl;
   // i policzyc dokladna wartosc calki z funkcji f(x)=x
   wynik_dokladny = a * (b - a) + (b - a) * (b - a) / 2.0;
   cout << "wynik dokladny policzony przez watek glowny = " << wynik_dokladny << endl;

   // oczekiwanie na zakończenie wątku
   watek.join();
   cout << "wynik calkowania numerycznego policzony przez watek dodatkowy = " << wynik << endl;
   cout << "blad = " << wynik_dokladny - wynik << ",\tblad w % =" << (wynik_dokladny - wynik) / wynik_dokladny * 100 << endl;
   return EXIT_SUCCESS;
}