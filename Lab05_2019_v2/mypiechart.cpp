#include "mypiechart.h"

MyPieChart::MyPieChart(const QDir& dirSelected, QGraphicsItem *parent):QChart(parent)
{
    series = new QPieSeries(this);
    foreach(QFileInfo entry, dirSelected.entryInfoList())
        if(entry.isDir())
            series->append(entry.fileName(), rand() % 0xFFFFFF);

    QChart::addSeries(series);
    QChart::setTitle("Directory path:  \"" + dirSelected.path() + "\"");
    QChart::legend()->setAlignment(Qt::AlignLeft);
    QObject::connect(series,&QPieSeries::clicked,[this](QPieSlice *slice)->void{
         emit pathChanged(slice->label() + '/');
    });
}

MyPieChart::~MyPieChart(){
    delete this->series;
}
