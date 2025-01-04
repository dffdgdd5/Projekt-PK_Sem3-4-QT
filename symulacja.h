#ifndef SYMULACJA_H
#define SYMULACJA_H

/*
class Symulacja;

class Symulacja
{
    int KrokCzasowy;
public:
    void StartSymulacji();
    void ResetSymulacji();
};
*/
#include "glowne.h"
//#include "mainwindow.h"
#include "pid.h"
#include "arx.h"
#include "generator.h"
#include "zarzadzanie_plikami.h"

class MainWindow;

class Symulacja {
private:
    PID regulator;
    ARX obiekt;
    Generator generator;
    int liczbaKrokow;
    Zarzadzanie_plikami pliki;


    friend MainWindow;

    vector<float> wyjscia;


public:

    Symulacja(PID pid, ARX arx, Generator gen, int liczbaKrokow);
    Symulacja();
    void uruchom();
    void zapiszSymulacjeDoPliku();
    void zapiszKonfiguracjeDoPliku();
    void wczytajSymulacje();
    void wczytajKonfiguracje();
};
#endif // SYMULACJA_H
