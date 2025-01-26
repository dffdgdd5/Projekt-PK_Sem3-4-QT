#include "arx.h"
#include "generator.h"
#include "pid.h"
#include "symulacja.h"
#include "qdebug.h"
#include "zarzadzanie_plikami.h"

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
  /*  qDebug() << "wykresyAktualizacja emitted with:";
    qDebug() << "P size:" << skladowaP.size() << ", I size:" << skladowaI.size() << ", D size:" << skladowaD.size();
    qDebug() << "Krok symulacji:";
    qDebug() << "  Wejście (w):" << w;
    qDebug() << "  Uchyb (e):" << e;
    qDebug() << "  Sterowanie (u):" << u;
    qDebug() << "  Wyjście (y):" << y;
*/


}

void Symulacja::zapiszSymulacjeDoPliku()
{

    if(pliki.SciezkaSymulacja.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&pliki.SciezkaSymulacja);
        for(double w : regulowana)
            out << w << "\n";


        out << "Ti: " << regulator.stalaCalkowania << "\n"
            << "Td: " << regulator.stalaRozniczkowania
            << "\n" << "P: " << regulator.wzmocnienie << "\n";
        out << "typ skoku: " << static_cast<int>(generator.wyborTypu) << "\n"
            << "wzmocnienie: " << generator.p << "\n"
            << "okres: " << generator.okres << "\n"
            << "stała całkowania: " << generator.wartoscStala << "\n"
            << "Czas Aktywacji: " << generator.czasAktywacji << "\n"
            << "Amplituda: " << generator.amplituda << "\n";
        out << "Wektor A\n";
        for  (double a : obiekt.wektorA)
           out << a << "\n";
        out << "Wektor B\n";
        for  (double b : obiekt.wektorB)
            out << b << "\n";

        out << "Opoznienie: " << obiekt.opoznienie << "\n";

        pliki.SciezkaSymulacja.close();
    }
}

void Symulacja::zapiszKonfiguracjeDoPliku(){

    if(pliki.SciezkaKonfiguracyjna.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&pliki.SciezkaKonfiguracyjna);
    out << "Ti: " << regulator.stalaCalkowania << "\n"
        << "Td: " << regulator.stalaRozniczkowania<< "\n"
        << "P: " << regulator.wzmocnienie << "\n";
    out << "typ skoku: " << static_cast<int>(generator.wyborTypu) << "\n"
        << "wzmocnienie: " << generator.p << "\n"
        << "okres: " << generator.okres << "\n"
        << "stała całkowania: " << generator.wartoscStala << "\n"
        << "Czas Aktywacji: " << generator.czasAktywacji << "\n"
        << "Amplituda: " << generator.amplituda << "\n";
    out << "Wektor A:\n";
    for  (double a : obiekt.wektorA)
        out << a << "\n";
    out << "Wektor B:\n";
    for  (double b : obiekt.wektorB)
        out << b << "\n";

    out << "Opoznienie: " << obiekt.opoznienie << "\n";
     pliki.SciezkaKonfiguracyjna.close();
    }

}

void Symulacja::wczytajKonfiguracje() {
    if (pliki.SciezkaKonfiguracyjna.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&pliki.SciezkaKonfiguracyjna);

        vector<double> tmpWektorA, tmpWektorB;
        int tmpOpoznienie = 0;

        while (!in.atEnd()) {
            QString line = in.readLine().trimmed();

            if (line.startsWith("Ti:")) {
                regulator.stalaCalkowania = line.section(": ", 1, 1).toDouble();
            } else if (line.startsWith("Td:")) {
                regulator.stalaRozniczkowania = line.section(": ", 1, 1).toDouble();
            } else if (line.startsWith("P:")) {
                regulator.wzmocnienie = line.section(": ", 1, 1).toDouble();
            } else if (line.startsWith("typ skoku:")) {
                generator.wyborTypu = static_cast<Typ>(line.section(": ", 1, 1).toInt());
            } else if (line.startsWith("wzmocnienie:")) {
                generator.p = line.section(": ", 1, 1).toDouble();
            } else if (line.startsWith("okres:")) {
                generator.okres = line.section(": ", 1, 1).toInt();
            } else if (line.startsWith("stała całkowania:")) {
                generator.wartoscStala = line.section(": ", 1, 1).toDouble();
            } else if (line.startsWith("Czas Aktywacji:")) {
                generator.czasAktywacji = line.section(": ", 1, 1).toInt();
            } else if (line.startsWith("Amplituda:")) {
                generator.amplituda = line.section(": ", 1, 1).toDouble();
            } else if (line.startsWith("Wektor A:")) {

                tmpWektorA.clear();
                while (!(line = in.readLine().trimmed()).isEmpty() && !line.startsWith("Wektor B:")) {
                    tmpWektorA.push_back(line.toDouble());
                }
            } else if (line.startsWith("Wektor B:")) {

                tmpWektorB.clear();
                while (!(line = in.readLine().trimmed()).isEmpty() && !line.startsWith("Opoznienie:")) {
                    tmpWektorB.push_back(line.toDouble());
                }
            } else if (line.startsWith("Opoznienie:")) {
                tmpOpoznienie = line.section(": ", 1, 1).toInt();
            }
        }


        obiekt.setWektory(tmpWektorA, tmpWektorB);
        obiekt.setOpoznienie(tmpOpoznienie);

        pliki.SciezkaKonfiguracyjna.close();
    } else {
        qWarning() << "Nie udało się otworzyć pliku do odczytu.";
    }
}

/*
void Symulacja::wczytajKonfiguracje(){
    if(pliki.SciezkaKonfiguracyjna.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&pliki.SciezkaKonfiguracyjna);
        while(!in.atEnd())
        {
            QString line = in.readLine();
            if(line.startsWith("AKTUALNE: "))
            {
                QString nowyAktualny = line.section(": ", 1,1).trimmed();
                aktualne = nowyAktualny.toInt();;

                continue;
            }

        }
        pliki.SciezkaKonfiguracyjna.close();
    }
}
*/
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
    generator = Generator(typ, generator.amplituda, generator.okres, generator.czasAktywacji, generator.wartoscStala, generator.p);
}

void Symulacja::setGeneratorParametry(double amplituda, int okres, int czasAktywacji, double wartoscStala, double p) {
    generator = Generator(generator.wyborTypu, amplituda, okres, czasAktywacji, wartoscStala, p);
}

