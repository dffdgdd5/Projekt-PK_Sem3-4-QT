#ifndef ZARZADZANIE_PLIKAMI_H
#define ZARZADZANIE_PLIKAMI_H


#include "glowne.h"

class Zarzadzanie_plikami;
class Zarzadzanie_plikami
{


public:
    QFile SciezkaKonfiguracja;
    QFile SciezkaSymulacja;
    void ZapiszKonfiguracje();
    void ZapiszSymulacje();
    void OdczytajKonfiguracje();
    void OdczytajSymulacje();
};


#endif // ZARZADZANIE_PLIKAMI_H
