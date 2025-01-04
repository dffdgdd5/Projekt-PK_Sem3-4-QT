#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

private slots:
    void on_ZapiszWynik_clicked();

    void on_ZapiszKonfiguracje_clicked();

    void on_WczytajKonf_clicked();

    void on_Start_clicked();

    void on_Stop_clicked();

private:
    Ui::MainWindow *ui;
   Symulacja Symulator;

};
#endif // MAINWINDOW_H
