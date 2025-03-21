#ifndef PID_H
#define PID_H

#include "glowne.h"
class Symulacja;
class PID
{
private:
    double wzmocnienie;
    double stalaCalkowania;
    double stalaRozniczkowania;
    double sumaCalkowania;
    double minWyjscie;
    double maxWyjscie;
    double poprzedniaWartosc;
    double proporcjonalne;
    double calka;
    double rozniczka;

public:
    PID(double, double = 0, double = 0, double = -20.0f, double = 20.0f);
    void UstawOgraniczenia(double, double);

    double ObliczProporcjonalne(double);
    double ObliczCalka(double);
    double ObliczRozniczka(double);
    double ObliczSterowanie(double);

    double Sumator(double, double);

    double getProporcjonalne();
    double getCalka();
    double getRozniczka();

    void Reset();
};

#endif // PID_H
