#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QListWidget>
#include <QStorageInfo>
#include <QDebug>
#include <iostream>

#include "mycompleter.h"
#include "mypiechart.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_driveSelection_activated(const QString &arg1);
    void on_searchBar_textChanged(const QString &entryPath);

private:
    Ui::MainWindow *ui;
    QDir dirRoot;
    QCompleter *completer;
    MyPieChart *pieChart;
    QStorageInfo *indicator;
};

#endif // MAINWINDOW_H
