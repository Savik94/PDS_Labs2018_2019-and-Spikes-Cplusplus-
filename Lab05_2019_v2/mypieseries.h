#ifndef MYPIESERIES_H
#define MYPIESERIES_H

#include <QObject>
#include <QWidget>
#include <QtCharts>

class MyPieSeries: public QPieSeries
{
    Q_OBJECT
public:
    MyPieSeries();
};

#endif // MYPIESERIES_H
