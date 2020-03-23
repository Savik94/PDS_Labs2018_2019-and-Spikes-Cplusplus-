#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mypieseries.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    pieChart = nullptr;
    completer = nullptr;
    indicator = new QStorageInfo();
    ui->setupUi(this);
    ui->folderEntriesPieChartView->setRenderHint(QPainter::Antialiasing);
    ui->searchBar->setDisabled(1);

    foreach(QFileInfo entry, dirRoot.drives())
        ui->driveSelection->addItem(QIcon(":/Resource/icons_pack/drive_icon.jpeg"),entry.absolutePath());

    ui->storageProgressBar->setRange(0,100);
    ui->storageProgressBar->setValue(0);
}


MainWindow::~MainWindow()
{
    delete ui;
    delete completer;
    delete indicator;
    delete pieChart;
}

//Passo il nome della entry cliccata, che non è altro che il path del drive in questione.
void MainWindow::on_driveSelection_activated(const QString &rootPath)
{
    delete this->completer;
    this->completer = new MyCompleter(rootPath,this);
    this->ui->searchBar->setDisabled(0);
    this->ui->searchBar->setCompleter(completer);
    indicator->setPath(rootPath);

    int percentage = (double)indicator->bytesFree()/indicator->bytesTotal() * 100;
    ui->storageProgressBar->setValue(percentage);

    QObject::connect(completer, QOverload<const QString &>::of(&QCompleter::activated),[this](const QString &text){
        this->completer->setCompletionPrefix(text +'/'); //Update of the the layer under the QEditLine WIdget (update of the prefix of the Mycompleter instance)
        ui->searchBar->setText(this->completer->completionPrefix()); //Update of the text contained in the QEditLine WIdget (for some reason is not shown..) but the list of possible choices is updated anyway..
    });

    /*
    QObject::connect(ui->upButton,&QPushButton::clicked,[this]()->void{
        QString path = completer->completionPrefix();
                         qDebug()<< path << "   ";
        QStringList list = path.split('/');
        list.removeAt(list.length()-1);
                         qDebug() << list << "    ";
        path = list.join('/');
                         qDebug()<< path;
        this->completer->setCompletionPrefix(path);
        ui->searchBar->setText(path);
    });
    */
}

//Instead of .textEdited, in this case the signal is emitted also if the text is changed via another method like .setText()
void MainWindow::on_searchBar_textChanged(const QString &dirSelectedPath)
{
    if(dirSelectedPath == '/' || dirSelectedPath[dirSelectedPath.length()-1]=='/'){

        QDir dirSelected(dirSelectedPath);
        dirSelected.setFilter(QDir::NoDotAndDotDot | QDir::AllEntries);

        ui->folderEntries->clear(); //Pulisco il QEditLine Widget prima della prossima visualizzazione
        foreach(QFileInfo entry, dirSelected.entryInfoList()){
            if(entry.isDir())
                ui->folderEntries->addItem(new QListWidgetItem(QIcon(":/Resource/icons_pack/folder_icon.jpeg"),entry.filePath(),ui->folderEntries));
            if(entry.isFile())
                ui->folderEntries->addItem(new QListWidgetItem(QIcon(":/Resource/icons_pack/file_icon.png"),entry.filePath(),ui->folderEntries));
        }
        pieChart = new MyPieChart(dirSelected);
        ui->folderEntriesPieChartView->setChart(pieChart);
        QObject::connect(pieChart,&MyPieChart::pathChanged,[this](const QString &text){
            QString path(this->completer->completionPrefix() + text);
            this->completer->setCompletionPrefix(path); //Update of the the layer under the QEditLine WIdget (update of the prefix of the Mycompleter instance)
            ui->searchBar->setText(path); //Update of the text contained in the QEditLine WIdget and the list of possible choices is updated anyway..
        });
    }
}
