#ifndef BROWSERMODEL_H
#define BROWSERMODEL_H
#include <QList>
#include <QLocale>
#include "Context.h"
#include <QAbstractTableModel>

class BrowserModel : public QAbstractTableModel
{
    Q_OBJECT
private:
    //Определим перечисление NameColumn для индексации столбцов нашей таблицы.
    enum NameColumn
    {
        NAME = 0,
        SIZE,
        PERCENT
    };
    //Представим данные модели в виде списка.
    QList<Data> dataModel;
public:
    BrowserModel() = default;
    ~BrowserModel() = default;
    BrowserModel(const QList<Data>& data, QObject* parent = nullptr);
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    void setModel(const QList<Data>& data);
};

#endif // BROWSERMODEL_H
