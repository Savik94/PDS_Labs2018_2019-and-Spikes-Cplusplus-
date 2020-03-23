#ifndef STORAGEINDICATOR_H
#define STORAGEINDICATOR_H

#include <QStorageInfo>
#include <QDebug>

class storageIndicator:public QStorageInfo
{
public:
    storageIndicator();
    ~storageIndicator();
    int getValue();
private:
    qint64 percentage;
};

#endif // STORAGEINDICATOR_H
