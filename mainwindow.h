#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "glowne.h"
#include "symulacja.h"
#include "arxwidget.h"
#include "pidwidget.h"
#include "innewartosciwidget.h"
#include <QPointer>
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
    void on_ZapiszWynik_clicked();

    void on_ZapiszKonfiguracje_clicked();

    void on_WczytajKonf_clicked();

    void on_Start_clicked();

    void on_Stop_clicked();

    void on_ARX_clicked();

    void on_PID_clicked();

    void on_InneWartosci_clicked();


private:
    Ui::MainWindow *ui;

    QPointer<QWidget> currentWindow;
   Symulacja Symulator;
    ARXWidget *arxWidget;
    PIDWidget *pidWidget;
    InneWartosciWIDGET *inneWartosciWidget;




};
#endif // MAINWINDOW_H
