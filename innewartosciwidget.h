#ifndef INNEWARTOSCIWIDGET_H
#define INNEWARTOSCIWIDGET_H

#include <QWidget>
#include "generator.h"
namespace Ui {
class InneWartosciWIDGET;
}

class InneWartosciWIDGET : public QWidget
{
    Q_OBJECT

public:
    explicit InneWartosciWIDGET(QWidget *parent = nullptr);
    ~InneWartosciWIDGET();

signals:
    void ZmianaGeneratora(Typ typ,double amplituda, int okres, int czasAktywacji, double wartoscStala, double p);

private slots:
    void on_Zapisz_clicked();
private:
    Ui::InneWartosciWIDGET *ui;
};

#endif // INNEWARTOSCIWIDGET_H
