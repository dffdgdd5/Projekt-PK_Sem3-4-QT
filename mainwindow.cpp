#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "arx.h"
#include "generator.h"
#include "glowne.h"
#include "pid.h"
#include "symulacja.h"
#include "zarzadzanie_plikami.h"
/*    QString SciezkaKonfiguracja;
    QString SciezkaSymulacja;
public:
    void ZapiszKonfiguracje();
    void ZapiszSymulacje();
    void OdczytajKonfiguracje();
    void OdczytajSymulacje();
*/
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Symulator.pliki.SciezkaKonfiguracja.setFileName("konfiguracja.txt");
    Symulator.pliki.SciezkaSymulacja.setFileName("symulacja.txt");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ZapiszWynik_clicked()
{
    Symulator.zapiszSymulacjeDoPliku();
}


void MainWindow::on_ZapiszKonfiguracje_clicked()
{
    Symulator.zapiszKonfiguracjeDoPliku();
}

