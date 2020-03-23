#ifndef MYCOMPLETER_H
#define MYCOMPLETER_H

#include <QCompleter>
#include <QFileSystemModel>
#include <QDir>
#include <iostream>

class MyCompleter : public QCompleter
{
    Q_OBJECT
public:
    MyCompleter(const QString &dirSelectedPath, QObject *parent);
    ~MyCompleter();

private:
    QFileSystemModel *model;
};

#endif // MYCOMPLETER_H
