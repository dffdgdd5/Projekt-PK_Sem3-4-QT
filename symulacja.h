#ifndef SYMULACJA_H
#define SYMULACJA_H


#include "glowne.h"
#include "pid.h"
#include "arx.h"
#include "generator.h"
#include "zarzadzanie_plikami.h"

class MainWindow;

class Symulacja : public QObject {
Q_OBJECT
private:
    PID regulator;
    ARX obiekt;
    Generator generator;
    int liczbaKrokow;
    int aktualnyKrok;
    Zarzadzanie_plikami pliki;
    QTimer* timer;

    friend MainWindow;

    vector<double> wyjscia;


public:
    Symulacja();
    Symulacja(PID pid, ARX arx, Generator gen, QObject* parent = nullptr);
    ~Symulacja();

    void uruchom();
    void zapiszSymulacjeDoPliku();
    void zapiszKonfiguracjeDoPliku();
    void wczytajSymulacje();
    void wczytajKonfiguracje();

    void startSymulacji();
    void stopSymulacji();

    const std::vector<double>& getWyjscia() const;
    void setPID(double wzmocnienie, double stalaCalkowania, double stalaRozniczkowania, double minWyjscie, double maxWyjscie);
    void setARXWektory(const vector<double>& wektorA, const vector<double>& wektorB);
    void setARXOpoznienie(int opoznienie);
    void setGeneratorTyp(Typ typ);
    void setGeneratorParametry(double amplituda, int okres, int czasAktywacji, double wartoscStala, double p);


private slots:
    void wykonajKrok();


};
#endif // SYMULACJA_H
