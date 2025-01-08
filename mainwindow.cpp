#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "arx.h"
#include "generator.h"
#include "glowne.h"
#include "pid.h"
#include "symulacja.h"
#include "zarzadzanie_plikami.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
    Symulator(),
    arxWidget(new ARXWidget(this)),
    pidWidget(new PIDWidget(this)),
    inneWartosciWidget(new InneWartosciWIDGET(this))

{
    ui->setupUi(this);
    ui->Stop->setEnabled(false);
    Symulator.pliki.SciezkaKonfiguracyjna.setFileName("konfiguracja.txt");
    Symulator.pliki.SciezkaSymulacja.setFileName("symulacja.txt");
arxWidget->hide();
pidWidget->hide();
inneWartosciWidget->hide();




}

MainWindow::~MainWindow()
{
    delete ui;
    delete arxWidget;
    delete pidWidget;
    delete inneWartosciWidget;


}



void MainWindow::on_ZapiszWynik_clicked()
{
    Symulator.zapiszSymulacjeDoPliku();
}


void MainWindow::on_ZapiszKonfiguracje_clicked()
{
    Symulator.zapiszKonfiguracjeDoPliku();
}


void MainWindow::on_WczytajKonf_clicked()
{
    Symulator.wczytajKonfiguracje();
}


void MainWindow::on_Start_clicked()
{
    ui->Start->setEnabled(false);
    ui->Stop->setEnabled(true);
    Symulator.startSymulacji();
}


void MainWindow::on_Stop_clicked()
{
    ui->Start->setEnabled(true);
    ui->Stop->setEnabled(false);
     Symulator.stopSymulacji();
}



void MainWindow::on_ARX_clicked()
{


    if (currentWindow) {
        currentWindow->close();
        currentWindow = nullptr;
    }

    ARXWidget *arxWindow = new ARXWidget(this);
    connect(arxWindow, &ARXWidget::ZmianaARX, this, [this](QVector<double> wektorA, QVector<double> wektorB, int opoznienie) {
        std::vector<double> stdWektorA(wektorA.begin(), wektorA.end());
        std::vector<double> stdWektorB(wektorB.begin(), wektorB.end());

        Symulator.setARXWektory(stdWektorA, stdWektorB);
        Symulator.setARXOpoznienie(opoznienie);

        qDebug() << "Zaktualizowano ARX:";
        qDebug() << "Wektor A:" << wektorA;
        qDebug() << "Wektor B:" << wektorB;
        qDebug() << "Opóźnienie:" << opoznienie;
    });
    currentWindow = arxWindow;
    currentWindow->setAttribute(Qt::WA_DeleteOnClose);
    currentWindow->show();
}



void MainWindow::on_PID_clicked()
{
    if (currentWindow) {
        currentWindow->close();
        delete currentWindow;
        currentWindow = nullptr;
    }

    PIDWidget *pidWindow = new PIDWidget(this);
    connect(pidWindow, &PIDWidget::ZmianaPID, this, [this](double wzmocnienie, double stalaCalkowania, double stalaRozniczkowania, double minWyjscie, double maxWyjscie) {
        Symulator.setPID(wzmocnienie, stalaCalkowania, stalaRozniczkowania, minWyjscie, maxWyjscie);

        qDebug() << "Zaktualizowano PID:";
        qDebug() << "Wzmocnienie:" << wzmocnienie;
        qDebug() << "Stała Całkowania:" << stalaCalkowania;
        qDebug() << "Stała Różniczkowania:" << stalaRozniczkowania;
        qDebug() << "Min Wyjście:" << minWyjscie;
        qDebug() << "Max Wyjście:" << maxWyjscie;
    });

    pidWindow->setAttribute(Qt::WA_DeleteOnClose);
    currentWindow = pidWindow;
    currentWindow->show();
}

void MainWindow::on_InneWartosci_clicked()
{
    if (currentWindow) {
        currentWindow->close();
        delete currentWindow;
        currentWindow = nullptr;
    }

    InneWartosciWIDGET *inneWartosciWindow = new InneWartosciWIDGET(this);

    connect(inneWartosciWindow, &InneWartosciWIDGET::ZmianaGeneratora, this, [this](Typ typ, double amplituda, int okres, int czasAktywacji, double wartoscStala, double p) {
        qDebug() << "Odebrano sygnał ZmianaGeneratora:";
        qDebug() << "Typ generatora:" << static_cast<int>(typ);
        qDebug() << "Amplituda:" << amplituda;
        qDebug() << "Okres:" << okres;
        qDebug() << "Czas aktywacji:" << czasAktywacji;
        qDebug() << "Stała całkowania:" << wartoscStala;
        qDebug() << "Wzmocnienie (p):" << p;

        Symulator.setGeneratorTyp(typ);
        Symulator.setGeneratorParametry(amplituda, okres, czasAktywacji, wartoscStala, p);
    });

    currentWindow = inneWartosciWindow;
    currentWindow->setAttribute(Qt::WA_DeleteOnClose);
    currentWindow->show();

}



