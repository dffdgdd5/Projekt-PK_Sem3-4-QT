#ifndef ARX_H
#define ARX_H

#include "glowne.h"
class Symulacja;
class ARX
{
    vector<double> wektorA;
    vector<double> wektorB;
    int opoznienie;
    double m_u;

    deque<double> historiaY;
    deque<double> historiaU;
    deque<double> opoznienieTransportowe;
public:
    ARX(vector<double>, vector<double>, int, double);
    ARX(vector<double>, vector<double>, int);
    void setWektory(vector<double>, vector<double>);
    void setOpoznienie(int);
    double Oblicz(double);
    void inicjalizujBufory();
    void reset();
};


#endif // ARX_H
