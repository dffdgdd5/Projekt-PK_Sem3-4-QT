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
public:
    Generator();
    Generator(Typ, double, int , int, double,double);
    double Generuj(int);

    double getStala();
    int getCzasAktywacji();
    int getOkres();
    double getAmplituda();
    double getP();

    Typ getTyp();
    void setTyp(Typ typ);

    void setParametry(double amplituda, int okres, int czasAktywacji, double wartoscStala, double p);

};

#endif // GENERATOR_H
