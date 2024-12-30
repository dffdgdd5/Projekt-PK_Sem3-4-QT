#include "arx.h"
#include "generator.h"
#include "pid.h"
#include "symulacja.h"
#include "zarzadzanie_plikami.h"


Symulacja::Symulacja(PID pid, ARX arx, Generator gen, int liczbaKrokow)
    : regulator(pid), obiekt(arx), generator(gen), liczbaKrokow(liczbaKrokow)
{}
Symulacja::Symulacja()
    : regulator(PID(1.0, 0.1, 0.01, -10, 10)),
    obiekt(ARX({1.0}, {0.5}, 1)),
    generator(Generator(Typ::skokowy, 1.0, 10, 0, 1.0, 0.5)),
    liczbaKrokow(100) {}

void Symulacja::uruchom() {
    double y = 0.0f;
    double w = 0.0f;
    double u = 0.0f;
    double e = 0.0f;

    regulator.Reset();

    for (int i = 0; i < liczbaKrokow; i++) {
        w = generator.Generuj(i);
        e = regulator.Sumator(w, y);
        u = regulator.ObliczSterowanie(e);
        y = obiekt.Oblicz(u);

        cout << "Wejscie: " << w <<"\tPID: " << e << "\t\tWyjscie:\t" << y << endl;
    }
}
void Symulacja::zapiszSymulacjeDoPliku()
{
    if(pliki.SciezkaSymulacja.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&pliki.SciezkaSymulacja);
        for(double w : wyjscia)
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

    if(pliki.SciezkaKonfiguracja.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&pliki.SciezkaKonfiguracja);
    out << "Ti: " << regulator.stalaCalkowania << "\n"
        << "Td: " << regulator.stalaRozniczkowania
        << "\n" << "P: " << regulator.wzmocnienie << "\n";
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
     pliki.SciezkaKonfiguracja.close();
    }
}
