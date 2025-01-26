#ifndef GENERATOR_H
#define GENERATOR_H



#include "glowne.h"

enum class Typ
{
    skokowy = 0, sinus = 1, prostokatny = 2
};
class Symulacja;
class Generator
{
private:
    Typ wyborTypu;
    double wartoscStala;
    int czasAktywacji;
    int okres;
    double amplituda;
    double p;
friend Symulacja;
public:
    Generator();
    Generator(Typ, double, int , int, double,double);
    double Generuj(int);

};

#endif // GENERATOR_H
