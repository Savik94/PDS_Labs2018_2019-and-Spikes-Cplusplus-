#ifndef MYPIECHART_H
#define MYPIECHART_H

#include <QObject>
#include <QWidget>
#include <QFileInfoList>
#include <QtCharts>
#include <QToolTip>

class MyPieChart: public QChart
{
    Q_OBJECT
public:
    MyPieChart(const QDir& dirSelected, QGraphicsItem *parent = nullptr);
    ~MyPieChart();
private:
    QPieSeries *series;

signals:
    void pathChanged(const QString &);
};

#endif // MYPIECHART_H
