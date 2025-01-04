#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "arx.h"
#include "generator.h"
#include "glowne.h"
#include "pid.h"
#include "symulacja.h"
#include "zarzadzanie_plikami.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Symulator.pliki.SciezkaKonfiguracyjna.setFileName("konfiguracja.txt");
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


void MainWindow::on_WczytajKonf_clicked()
{
    Symulator.wczytajKonfiguracje();
}

/*
void MainWindow::on_Start_clicked()
{

}


void MainWindow::on_Stop_clicked()
{

}

*/
