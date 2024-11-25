#ifndef STATISTICFORM_H
#define STATISTICFORM_H

#include <QtCharts>
#include <QWidget>

namespace Ui {
class Statisticform;
}

class Statisticform : public QWidget
{
    Q_OBJECT

public:
    explicit Statisticform(QWidget *parent = nullptr);
    ~Statisticform();
    void bar();
    void pie();

private slots:
    void pie_series_Clicked(QPieSlice*);

private:
    Ui::Statisticform *ui;
};

#endif // STATISTICFORM_H
