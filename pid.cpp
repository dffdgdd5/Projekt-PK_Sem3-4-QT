#include "pid.h"

PID::PID(double up, double ui, double ud, double minWyjscie, double maxWyjscie)
    : wzmocnienie(up), stalaCalkowania(ui), stalaRozniczkowania(ud),
    sumaCalkowania(0.0f)
{
    poprzedniaWartosc = 0.0f;
    UstawOgraniczenia(minWyjscie, maxWyjscie);
}

void PID::UstawOgraniczenia(double minWyjscie, double maxWyjscie)
{
    this->minWyjscie = minWyjscie;
    this->maxWyjscie = maxWyjscie;
}

double PID::ObliczProporcjonalne(double uchyb)
{
    return wzmocnienie * uchyb;
}

double PID::ObliczCalka(double uchyb)
{
    if (stalaCalkowania)
    {
        sumaCalkowania += uchyb;
        return sumaCalkowania / stalaCalkowania;
    }
    else return 0;
}

double PID::ObliczRozniczka(double uchyb)
{
    double wartoscRozniczkujaca = 0.0f;
    if (! poprzedniaWartosc == NULL)
        wartoscRozniczkujaca = stalaRozniczkowania * (uchyb -  poprzedniaWartosc);
    else wartoscRozniczkujaca = stalaRozniczkowania * uchyb;

    poprzedniaWartosc = uchyb;

    return wartoscRozniczkujaca;
}

double PID::ObliczSterowanie(double uchyb)
{
    proporcjonalne = ObliczProporcjonalne(uchyb);
    calka = ObliczCalka(uchyb);
    rozniczka = ObliczRozniczka(uchyb);

    double sterowanie = proporcjonalne + calka + rozniczka;

    if (sterowanie < minWyjscie) sterowanie = minWyjscie;
    else if (sterowanie > maxWyjscie) sterowanie = maxWyjscie;

    return sterowanie;
}

double PID::Sumator(double wejscie, double wyjscie)
{
    return wejscie - wyjscie;
}

void PID::Reset()
{
    sumaCalkowania = 0.0f;
    poprzedniaWartosc = 0.0f;

}


double PID::getProporcjonalne() {

    return proporcjonalne; }
double PID::getCalka() {

    return calka; }
double PID::getRozniczka()  {

    return rozniczka; }
