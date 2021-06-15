#ifndef SOMEDATA_H
#define SOMEDATA_H
#include <memory>
#include <QString>
#include <QWidget>
#include <QItemSelection>
#include <QFileSystemModel>

class Data
{
public:
    Data(const QString name_, const QString size_, const QString percent_)
    {
        name = name_;
        size = size_;
        percent = percent_;
    }
    QString name;
    QString size;
    QString percent;
};
#endif // SOMEDATA_H
