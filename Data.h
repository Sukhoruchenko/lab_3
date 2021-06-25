#ifndef DATA_H
#define DATA_H
#include <memory>
#include <QString>
#include <QWidget>
#include <QItemSelection>
#include <QFileSystemModel>

class Data
{
public:
    Data(const QString name_, const QString size_, const QString percent_, qreal proportion_)
    {
        name = name_;
        size = size_;
        percent = percent_;
        proportion = proportion_;
    }
    QString name;
    QString size;
    QString percent;
    qreal proportion;
};
#endif // DATA_H
