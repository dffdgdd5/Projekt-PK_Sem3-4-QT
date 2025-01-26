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


    vector<double> zadana;
    vector<double> uchyb;
    vector<double> sterowanie;
    vector<double> regulowana;
    vector<double> skladowaP;
    vector<double> skladowaI;
    vector<double> skladowaD;

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
    void restart();

    void setPID(double wzmocnienie, double stalaCalkowania, double stalaRozniczkowania, double minWyjscie, double maxWyjscie);
    void setARXWektory(const vector<double>& wektorA, const vector<double>& wektorB);
    void setARXOpoznienie(int opoznienie);
    void setGeneratorTyp(Typ typ);
    void setGeneratorParametry(double amplituda, int okres, int czasAktywacji, double wartoscStala, double p);


private slots:
    void wykonajKrok();


signals:
    void wykresyAktualizacja(
        const vector<double>& zadana,
        const vector<double>& uchyb,
        const vector<double>& sterowanie,
        const vector<double>& regulowana,
        const vector<double>& skladowaP,
        const vector<double>& skladowaI,
        const vector<double>& skladowaD);



};
#endif // SYMULACJA_H
