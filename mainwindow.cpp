#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "arx.h"
#include "generator.h"
#include "glowne.h"
#include "pid.h"
#include "symulacja.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    Symulator()

{
    ui->setupUi(this);
    ui->Stop->setEnabled(false);
    this->setWindowTitle("Symulator UAR");

    inicjalizujWszystkieWykresy();
    connect(&Symulator, &Symulacja::wykresyAktualizacja, this, &MainWindow::aktualizujWykresy);
    ui->Reset->setEnabled(false);

    ui->wzmocnienie->setValue(0.5);
    ui->stalaCalkowania->setValue(10);
    ui->stalaRozniczkowania->setValue(0.2);
    ui->minWyjscie->setMinimum(-500);
    ui->maxWyjscie->setMaximum(500);
    ui->minWyjscie->setValue(-100);
    ui->maxWyjscie->setValue(100);

    ui->WektorA->setText("-0.4");
    ui->WektorB->setText("0.6");
    ui->Opoznienie->setValue(0);

    ui->amplituda->setValue(3);
    ui->okres->setValue(5);
    ui->czasAktywacji->setValue(0);
    ui->p->setValue(1);
    ui->Interwal->setValue(0.1);
    ui->wartoscStala->setValue(1);
    ui->amplituda->setDisabled(true);
    ui->okres->setDisabled(true);
    ui->p->setDisabled(true);
    ui->okres->setMinimum(1);

}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::on_Start_clicked()
{

    ui->Start->setEnabled(false);
     ui->Reset->setEnabled(false);
    ui->Stop->setEnabled(true);
    Symulator.startSymulacji();

}

void MainWindow::on_Stop_clicked()
{
    ui->Start->setEnabled(true);
    ui->Reset->setEnabled(true);
    ui->Stop->setEnabled(false);
     Symulator.stopSymulacji();
}

void MainWindow::on_Reset_clicked()
{
    Symulator.restart();
    series->clear();
    seriesP->clear();
    seriesI->clear();
    seriesD->clear();
    seriesUchyb->clear();
    seriesZadana->clear();
    seriesRegulowana->clear();

    chart->axes(Qt::Horizontal).first()->setRange(0, 1);
    chart->axes(Qt::Vertical).first()->setRange(0, 1);

    chartUchyb->axes(Qt::Horizontal).first()->setRange(0, 1);
    chartUchyb->axes(Qt::Vertical).first()->setRange(0, 1);

    chartZadanaRegulowana->axes(Qt::Horizontal).first()->setRange(0, 1);
    chartZadanaRegulowana->axes(Qt::Vertical).first()->setRange(0, 1);

    chartP->axes(Qt::Horizontal).first()->setRange(0, 1);
    chartP->axes(Qt::Vertical).first()->setRange(0, 1);

    chartI->axes(Qt::Horizontal).first()->setRange(0, 1);
    chartI->axes(Qt::Vertical).first()->setRange(0, 1);

    chartD->axes(Qt::Horizontal).first()->setRange(0, 1);
    chartD->axes(Qt::Vertical).first()->setRange(0, 1);

}

void MainWindow::inicjalizujWszystkieWykresy()
{
    // Główny wykres
    chart = new QChart();
    series = new QLineSeries();
    chartView = new QChartView(chart, ui->chartWidget);
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Wykres PID");
    chartView->setRenderHint(QPainter::Antialiasing);
    QVBoxLayout *layout = new QVBoxLayout(ui->chartWidget);
    layout->addWidget(chartView);
    ui->chartWidget->setLayout(layout);
    chart->legend()->hide();

    // Wykres P (Proporcjonalny)
    chartP = new QChart();
    seriesP = new QLineSeries();
    chartViewP = new QChartView(chartP, ui->wykresP);
    chartP->addSeries(seriesP);
    chartP->createDefaultAxes();
    chartP->setTitle("Wykres Proporcjonalny (P)");
    chartViewP->setRenderHint(QPainter::Antialiasing);
    QVBoxLayout *layoutP = new QVBoxLayout(ui->wykresP);
    layoutP->addWidget(chartViewP);
    ui->wykresP->setLayout(layoutP);
    chartP->legend()->hide();

    // Wykres I (Całkujący)
    chartI = new QChart();
    seriesI = new QLineSeries();
    chartViewI = new QChartView(chartI, ui->wykresI);
    chartI->addSeries(seriesI);
    chartI->createDefaultAxes();
    chartI->setTitle("Wykres Całkujący (I)");
    chartViewI->setRenderHint(QPainter::Antialiasing);
    QVBoxLayout *layoutI = new QVBoxLayout(ui->wykresI);
    layoutI->addWidget(chartViewI);
    ui->wykresI->setLayout(layoutI);
    chartI->legend()->hide();

    // Wykres D (Różniczkujący)
    chartD = new QChart();
    seriesD = new QLineSeries();
    chartViewD = new QChartView(chartD, ui->wykresD);
    chartD->addSeries(seriesD);
    chartD->createDefaultAxes();
    chartD->setTitle("Wykres Różniczkujący (D)");
    chartViewD->setRenderHint(QPainter::Antialiasing);
    QVBoxLayout *layoutD = new QVBoxLayout(ui->wykresD);
    layoutD->addWidget(chartViewD);
    ui->wykresD->setLayout(layoutD);
    chartD->legend()->hide();

    // Wykres Uchyb
    chartUchyb = new QChart();
    seriesUchyb = new QLineSeries();
    chartViewUchyb = new QChartView(chartUchyb, ui->wykresUchyb);
    chartUchyb->addSeries(seriesUchyb);
    chartUchyb->createDefaultAxes();
    chartUchyb->setTitle("Wykres Uchyb");
    chartViewUchyb->setRenderHint(QPainter::Antialiasing);
    QVBoxLayout *layoutUchyb = new QVBoxLayout(ui->wykresUchyb);
    layoutUchyb->addWidget(chartViewUchyb);
    ui->wykresUchyb->setLayout(layoutUchyb);
    chartUchyb->legend()->hide();

    // Wykres Zadana i Regulowana
    chartZadanaRegulowana = new QChart();
    seriesRegulowana = new QLineSeries();
    seriesZadana = new QLineSeries();

    seriesZadana->setName("Wartość Zadana");
    seriesRegulowana->setName("Wartość Regulowana");

    chartZadanaRegulowana->addSeries(seriesRegulowana);
    chartZadanaRegulowana->addSeries(seriesZadana);
    chartZadanaRegulowana->createDefaultAxes();
    chartZadanaRegulowana->setTitle("Wartość Zadana i Regulowana");
    chartViewZadanaRegulowana = new QChartView(chartZadanaRegulowana, ui->wykresZadanaRegulowana);
    chartViewZadanaRegulowana->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout *layoutZadanaRegulowana = new QVBoxLayout(ui->wykresZadanaRegulowana);
    layoutZadanaRegulowana->addWidget(chartViewZadanaRegulowana);
    ui->wykresZadanaRegulowana->setLayout(layoutZadanaRegulowana);
}

void MainWindow::aktualizujWykresy(
    const vector<double>& zadana,
    const vector<double>& uchyb,
    const vector<double>& sterowanie,
    const vector<double>& regulowana,
    const vector<double>& skladowaP,
    const vector<double>& skladowaI,
    const vector<double>& skladowaD)
{
    const int maxWartosc = 50;

    // Aktualizacja wykresu PID
    series->clear();
    int startIndex = max(0, static_cast<int>(sterowanie.size()) - maxWartosc);
    for (size_t index = startIndex; index < sterowanie.size(); ++index) {
        series->append(index * 0.1, sterowanie[index]);
    }

    if (!sterowanie.empty()) {
        auto maxY = *max_element(sterowanie.begin() + startIndex, sterowanie.end());
        chart->axes(Qt::Vertical).first()->setRange(maxY * -1.1, maxY * 1.1);
    }

    // Aktualizacja wykresu P (Proporcjonalny)
    seriesP->clear();
    int startIndexP = max(0, static_cast<int>(skladowaP.size()) - maxWartosc);
    for (size_t index = startIndexP; index < skladowaP.size(); ++index) {
        seriesP->append(index * 0.1, skladowaP[index]);
    }

    if (!skladowaP.empty()) {
        auto minY_P = *min_element(skladowaP.begin() + startIndexP, skladowaP.end());
        auto maxY_P = *max_element(skladowaP.begin() + startIndexP, skladowaP.end());
        double zakres_P = max(0.1, maxY_P - minY_P);
        chartP->axes(Qt::Vertical).first()->setRange(minY_P - zakres_P * 0.1, maxY_P + zakres_P * 0.1);
        chartP->axes(Qt::Horizontal).first()->setRange(startIndexP * 0.1, skladowaP.size() * 0.1);
    }

    // Aktualizacja wykresu I (Całkujący)
    seriesI->clear();
    int startIndexI = max(0, static_cast<int>(skladowaI.size()) - maxWartosc);
    for (size_t index = startIndexI; index < skladowaI.size(); ++index) {
        seriesI->append(index * 0.1, skladowaI[index]);
    }

    if (!skladowaI.empty()) {
        auto minY_I = *min_element(skladowaI.begin() + startIndexI, skladowaI.end());
        auto maxY_I = *max_element(skladowaI.begin() + startIndexI, skladowaI.end());
        double zakres_I = max(0.1, maxY_I - minY_I);
        chartI->axes(Qt::Vertical).first()->setRange(minY_I - zakres_I * 0.1, maxY_I + zakres_I * 0.1);
        chartI->axes(Qt::Horizontal).first()->setRange(startIndexI * 0.1, skladowaI.size() * 0.1);
    }

    // Aktualizacja wykresu D (Różniczkujący)
    seriesD->clear();
    int startIndexD = max(0, static_cast<int>(skladowaD.size()) - maxWartosc);
    for (size_t index = startIndexD; index < skladowaD.size(); ++index) {
        seriesD->append(index * 0.1, skladowaD[index]);
    }

    if (!skladowaD.empty()) {
        auto minY_D = *min_element(skladowaD.begin() + startIndexD, skladowaD.end());
        auto maxY_D = *max_element(skladowaD.begin() + startIndexD, skladowaD.end());
        double zakres_D = max(0.1, maxY_D - minY_D);
        chartD->axes(Qt::Vertical).first()->setRange(minY_D - zakres_D * 0.1, maxY_D + zakres_D * 0.1);
        chartD->axes(Qt::Horizontal).first()->setRange(startIndexD * 0.1, skladowaD.size() * 0.1);
    }

    // Aktualizacja wykresu Zadana i Regulowana
    seriesZadana->clear();
    for (size_t index = startIndex; index < zadana.size(); ++index) {
        seriesZadana->append(index * 0.1, zadana[index]);
    }

    seriesRegulowana->clear();
    for (size_t index = startIndex; index < regulowana.size(); ++index) {
        seriesRegulowana->append(index * 0.1, regulowana[index]);
    }
    if (!zadana.empty() && !regulowana.empty()) {
        auto minZadana = *min_element(zadana.begin() + startIndex, zadana.end());
        auto maxZadana = *max_element(zadana.begin() + startIndex, zadana.end());
        auto minRegulowana = *min_element(regulowana.begin() + startIndex, regulowana.end());
        auto maxRegulowana = *max_element(regulowana.begin() + startIndex, regulowana.end());


        double minY = min(minZadana, minRegulowana) - 0.1 * abs(min(minZadana, minRegulowana));
        double maxY = max(maxZadana, maxRegulowana) + 0.1 * abs(max(maxZadana, maxRegulowana));


        chartZadanaRegulowana->axes(Qt::Vertical).first()->setRange(minY, maxY);
    }
    chartZadanaRegulowana->axes(Qt::Horizontal).first()->setRange(startIndex * 0.1, regulowana.size() * 0.1);

    // Aktualizacja wykresu Uchyb
    seriesUchyb->clear();
    for (size_t index = startIndex; index < uchyb.size(); ++index) {
        seriesUchyb->append(index * 0.1, uchyb[index]);
    }

    if (!uchyb.empty()) {
        auto minY = *min_element(uchyb.begin() + startIndex, uchyb.end());
        auto maxY = *max_element(uchyb.begin() + startIndex, uchyb.end());
        chartUchyb->axes(Qt::Vertical).first()->setRange(minY * 1.1, maxY * 1.1);
    }

    double minX = startIndex * 0.1;
    double maxX = regulowana.size() * 0.1;

    chart->axes(Qt::Horizontal).first()->setRange(minX, maxX);
    chartUchyb->axes(Qt::Horizontal).first()->setRange(minX, maxX);

}

void MainWindow::on_zapiszInne_clicked()
{
    Typ typ = static_cast<Typ>(ui->typComboBox->currentIndex());
    double amplituda = ui->amplituda->value();
    int okres = ui->okres->value();
    int czasAktywacji = ui->czasAktywacji->value();
    double wartoscStala = ui->wartoscStala->value();
    double p = ui->p->value();
    double interwal = ui->Interwal->value();

    qDebug() << "Wprowadzone dane w InneWartosciWidget:";
    qDebug() << "Typ generatora:" << static_cast<int>(typ);
    qDebug() << "Amplituda:" << amplituda;
    qDebug() << "Okres:" << okres;
    qDebug() << "Czas aktywacji:" << czasAktywacji;
    qDebug() << "Stała całkowania:" << wartoscStala;
    qDebug() << "Wzmocnienie (p):" << p;
    qDebug() << "Interwał (p):" << interwal;

    Symulator.setGeneratorTyp(typ);
    Symulator.setGeneratorParametry(amplituda, okres, czasAktywacji, wartoscStala, p);
    Symulator.getTimer()->setInterval(interwal*1000);
}


void MainWindow::on_ZapiszARX_clicked()
{
    QVector<double> wektorA;
    for (const QString& value : ui->WektorA->text().split(",")) {
        wektorA.append(value.trimmed().toDouble());

    }
    QVector<double> wektorB;
    for (const QString& value : ui->WektorB->text().split(",")) {
        wektorB.append(value.trimmed().toDouble());
    }
    int opoznienie = ui->Opoznienie->value();

    vector<double> tempWektorA(wektorA.begin(), wektorA.end());
    vector<double> tempWektorB(wektorB.begin(), wektorB.end());

    Symulator.setARXWektory(tempWektorA, tempWektorB);
    Symulator.setARXOpoznienie(opoznienie);
}


void MainWindow::on_ZapiszPID_clicked()
{
    double wzmocnienie = ui->wzmocnienie->value();
    double stalaCalkowania = ui->stalaCalkowania->value();
    double stalaRozniczkowania = ui->stalaRozniczkowania->value();
    double minWyjscie = ui->minWyjscie->value();
    double maxWyjscie = ui->maxWyjscie->value();

    Symulator.setPID(wzmocnienie, stalaCalkowania, stalaRozniczkowania, minWyjscie, maxWyjscie);
}

void MainWindow::odblokuj(){
    ui->amplituda->setDisabled(false);
    ui->okres->setDisabled(false);
    ui->czasAktywacji->setDisabled(false);
    ui->wartoscStala->setDisabled(false);
    ui->p->setDisabled(false);
    ui->Interwal->setDisabled(false);

}

void MainWindow::on_typComboBox_activated(int index)
{
    switch (index) {
    default:
        odblokuj();
        break;
    case 0:
        odblokuj();
        ui->amplituda->setDisabled(true);
        ui->okres->setDisabled(true);
        ui->p->setDisabled(true);
        break;
    case 1:
        odblokuj();
        ui->czasAktywacji->setDisabled(true);
        ui->wartoscStala->setDisabled(true);
        ui->p->setDisabled(true);

        break;

    case 2:
        odblokuj();
        ui->czasAktywacji->setDisabled(true);
        ui->wartoscStala->setDisabled(true);

        break;
    }
}
