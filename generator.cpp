#include "generator.h"

constexpr double PI = 3.141592653589793238;

Generator::Generator()
{
    amplituda = 1;
    okres = 1;
    czasAktywacji = 0;
    wyborTypu = Typ::skokowy;
    wartoscStala = 1;
    p = 1;
};

Generator::Generator(Typ typ, double amplituda, int okres, int czasAktywacji, double wartoscStala, double i_p)
    :wyborTypu(typ), wartoscStala(wartoscStala), czasAktywacji(czasAktywacji),p(i_p)
{
    this->amplituda = (amplituda < 0) ? 1 : amplituda;
    this->okres = (okres < 0) ? 1 : okres;
}

double Generator::Generuj(int czas)
{
    if (wyborTypu == Typ::skokowy)
        return (czas >= czasAktywacji) ? wartoscStala : 0;
    else if (wyborTypu == Typ::sinus)
    {
        double x = ((czas % okres)/(double)okres)*2*PI;
        return amplituda * sin(x);
    }
    else if (wyborTypu == Typ::prostokatny)
    {
        int i_mod = czas % okres;
        double prog = ((double)p * (double)okres);
        if (i_mod < prog)
            return amplituda;
        else
            return 0.0;
    }
}
