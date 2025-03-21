#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPointer>
#include "arxwidget.h"
#include "glowne.h"
#include "innewartosciwidget.h"
#include "pidwidget.h"
#include "symulacja.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;

}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setARXParameters(QVector<double> wektorA, QVector<double> wektorB, int opoznienie);
    void setPIDParameters(double kP, double kI, double kD);
    void setInneWartosci(int krokCzasowy);

private slots:
    void on_Start_clicked();

    void on_Stop_clicked();

    void on_ARX_clicked();

    void on_PID_clicked();

    void on_InneWartosci_clicked();

    void on_Reset_clicked();

    void aktualizujWykresy(const vector<double> &zadana,
                           const vector<double> &uchyb,
                           const vector<double> &sterowanie,
                           const vector<double> &regulowana,
                           const vector<double> &skladowaP,
                           const vector<double> &skladowaI,
                           const vector<double> &skladowaD);

private:
    Ui::MainWindow *ui;

    QPointer<QWidget> currentWindow;
    Symulacja Symulator;
    ARXWidget *arxWidget;
    PIDWidget *pidWidget;
    InneWartosciWIDGET *inneWartosciWidget;

    QWidget *chartWidget;
    QChart *chart;
    QLineSeries *series;
    QChartView *chartView;
    void inicjalizujWszystkieWykresy();

    QChart *chartPID;
    QLineSeries *seriesPID;
    QChartView *chartViewPID;

    QChart *chartZadanaRegulowana;
    QLineSeries *seriesZadanaRegulowana;
    QChartView *chartViewZadanaRegulowana;
    QLineSeries *seriesZadana;
    QLineSeries *seriesRegulowana;

    QChart *chartUchyb;
    QLineSeries *seriesUchyb;
    QChartView *chartViewUchyb;

    QChart *chartSterowanie;
    QLineSeries *seriesSterowanie;
    QChartView *chartViewSterowanie;

    QChart *chartP;
    QLineSeries *seriesP;
    QChartView *chartViewP;

    QChart *chartI;
    QLineSeries *seriesI;
    QChartView *chartViewI;

    QChart *chartD;
    QLineSeries *seriesD;
    QChartView *chartViewD;
};
#endif // MAINWINDOW_H
