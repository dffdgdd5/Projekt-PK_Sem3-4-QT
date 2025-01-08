#ifndef PIDWIDGET_H
#define PIDWIDGET_H

#include <QWidget>

namespace Ui {
class PIDWidget;
}

class PIDWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PIDWidget(QWidget *parent = nullptr);
    ~PIDWidget();

signals:
    void ZmianaPID(double wzmocnienie, double stalaCalkowania, double stalaRozniczkowania, double minWyjscie, double maxWyjscie);


private slots:
    void on_Zapisz_clicked();


private:
    Ui::PIDWidget *ui;
};

#endif // PIDWIDGET_H
