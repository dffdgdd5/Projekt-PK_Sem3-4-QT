#include "arx.h"
#include "generator.h"
#include "pid.h"
#include "symulacja.h"
#include "qdebug.h"
#include <QTimer>

Symulacja::Symulacja(PID pid, ARX arx, Generator gen, QObject* parent)
    : QObject(parent),
    regulator(pid),
    obiekt(arx),
    generator(gen)


{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Symulacja::wykonajKrok);

}

Symulacja::~Symulacja(){
    if(timer->isActive()){
            timer->stop();
        }
delete timer;
}

Symulacja::Symulacja()
    : regulator(PID(1.0, 0.1, 0.01, -10, 10)),
    obiekt(ARX({1.0}, {0.5}, 1)),
    generator(Generator(Typ::skokowy, 1.0, 10, 0, 1.0, 0.5))
    {
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Symulacja::wykonajKrok);

    }


void Symulacja::startSymulacji(){

    timer->start();
    qDebug() << "symulacja rozpoczęta.";

}
void Symulacja::stopSymulacji(){
    if(timer->isActive()){
        timer->stop();
        qDebug() << "Symulacja zatrzymana.";
    }
}
void Symulacja::restart(){
    regulator.Reset();
    zadana.clear();
    uchyb.clear();
    regulowana.clear();
    skladowaP.clear();
    skladowaI.clear();
    skladowaD.clear();
    sterowanie.clear();
    obiekt.reset();
}


void Symulacja::wykonajKrok(){
    static double y = 0.0;
    double w = generator.Generuj(regulowana.size());
    double e = regulator.Sumator(w,y);
    double u = regulator.ObliczSterowanie(e);
    y = obiekt.Oblicz(u);

    zadana.push_back(w);
    uchyb.push_back(e);
   sterowanie.push_back(u);
    regulowana.push_back(y);
    double p = regulator.getProporcjonalne();
    double i = regulator.getCalka();
    double d = regulator.getRozniczka();

    skladowaP.push_back(p);
    skladowaI.push_back(i);
    skladowaD.push_back(d);

    emit wykresyAktualizacja(zadana, uchyb, sterowanie, regulowana, skladowaP, skladowaI, skladowaD);
}

void Symulacja::setPID(double wzmocnienie, double stalaCalkowania, double stalaRozniczkowania, double minWyjscie, double maxWyjscie) {
    regulator = PID(wzmocnienie, stalaCalkowania, stalaRozniczkowania, minWyjscie, maxWyjscie);
}


void Symulacja::setARXWektory(const vector<double>& wektorA, const vector<double>& wektorB) {
    obiekt.setWektory(wektorA, wektorB);
}

void Symulacja::setARXOpoznienie(int opoznienie) {
    obiekt.setOpoznienie(opoznienie);
}


void Symulacja::setGeneratorTyp(Typ typ) {
    generator = Generator(typ, generator.getAmplituda(), generator.getOkres(), generator.getCzasAktywacji(), generator.getStala(), generator.getP());
}

void Symulacja::setGeneratorParametry(double amplituda, int okres, int czasAktywacji, double wartoscStala, double p) {
    generator = Generator(generator.getTyp(), amplituda, okres, czasAktywacji, wartoscStala, p);
}

QTimer* Symulacja::getTimer()
{
    return timer;
}
