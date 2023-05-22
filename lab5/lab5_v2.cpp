#include <thread>
#include <mutex>
#include <random>
#include <iostream>
#include <vector>
#include "semafor.h"
 
using namespace std;
 
//czas jedzenia w ms
const int MAX_OPOZNIENIE = 1000;
Semafor sem_widelce[5];
Semafor sem_room(4);
 
 
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
    Semafor& widelec;
    Semafor& room;
 
public:
    Filozof(int n, Semafor &_widelec, Semafor &_room) : numer(n), zjedzonychPosilkow(0), widelec(_widelec), room(_room)
    {
        lewyWidelec = n;
        prawyWidelec = (n + 1) % 5;
    }
 
    void operator()()
    {
 
        while (zjedzonychPosilkow < LICZBA_POSILKOW)
        { 
             sem_room.czekaj();
 
            int czasPosilku = rozklad(generator);
            sem_widelce[lewyWidelec].czekaj();
            cout << "Filozof " << numer << " podnosi lewy widelec"<<endl;
            sem_widelce[prawyWidelec].czekaj();
            cout << "Filozof " << numer << " podnosi prawy widelec"<<endl;
            cout << "Filozof " << numer << " je "
                 << zjedzonychPosilkow << " posilek przez najblizsze " << czasPosilku << " ms" << endl;
            //filozof je
 
            this_thread::sleep_for(chrono::milliseconds(czasPosilku));
            ++zjedzonychPosilkow;
            cout << "Filozof " << numer << " skonczyl jesc " << zjedzonychPosilkow << " posilek " << endl;
            sem_widelce[lewyWidelec].sygnalizuj();
            cout << "Filozof " << numer << " odklada lewy widelec"<<endl;
            sem_widelce[prawyWidelec].sygnalizuj();
            cout << "Filozof " << numer << " odklada prawy widelec"<<endl;
            //filozof rozmyśla między posiłkami
 
             sem_room.sygnalizuj();
        }
 
        cout << "Filozof " << numer << " sie najadl" << endl;
    }
};
 
int main(int argc, char **argv)
{
    //tworzenie filozofow
    vector<thread> filozofowie;
 
    for (int i = 0; i < LICZBA_FILOZOFOW; ++i)
        filozofowie.emplace_back(Filozof(i,*sem_widelce, sem_room));
 
    //czekanie na zakonczenie
    for (thread &f : filozofowie)
        f.join();
 
    return (EXIT_SUCCESS);
}
