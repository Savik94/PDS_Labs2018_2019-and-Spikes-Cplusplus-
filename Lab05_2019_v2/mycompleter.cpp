#include "mycompleter.h"

MyCompleter::MyCompleter(const QString &dirSelectedPath, QObject *parent): QCompleter(parent)
{
    model= new QFileSystemModel();
    model->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    model->setRootPath(dirSelectedPath);
    QCompleter::setModel(this->model);
}

MyCompleter::~MyCompleter(){
    delete model;
}
