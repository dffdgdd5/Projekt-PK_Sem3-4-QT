#ifndef ARXWIDGET_H
#define ARXWIDGET_H

#include <QWidget>

namespace Ui {
class ARXWidget;
}

class ARXWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ARXWidget(QWidget *parent = nullptr);
    ~ARXWidget();

signals:
    void ZmianaARX(QVector<double> wektorA, QVector<double> wektorB, int opoznienie);

private slots:
    void on_Zapisz_clicked();

private:
    Ui::ARXWidget *ui;
};

#endif // ARXWIDGET_H
