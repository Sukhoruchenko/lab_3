#include "BrowserModel.h"

//В конструкторе инициализируем исходные данные.
BrowserModel::BrowserModel(const QList<Data> &data, QObject *parent) : QAbstractTableModel(parent)
{
    dataModel = data;
}

//Возвращаем количество строк, в зависимости от количества данных в списке
int BrowserModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return dataModel.count();
}

//Возвращаем количество столбцов, оно у нас постоянно
int BrowserModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return PERCENT + 1;
}

//Возвращаем названия заголовков.
QVariant BrowserModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
    {
        return QVariant();
    }

    if (orientation == Qt::Vertical)
    {
        return section;
    }

    switch (section)
    {
        case NAME:
            return QString::fromUtf8("Название");
        case NameColumn::SIZE:
            return QString::fromUtf8("Размер");
        case PERCENT:
            return QString::fromUtf8("В процентах");
    }
    return QVariant();
}

//Возвращаем соответствующие данные, относительно модельного индекса и роли.
QVariant BrowserModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || dataModel.count() <= index.row() || (role != Qt::DisplayRole && role != Qt::EditRole))
    {
        return QVariant();
    }

    if (index.column() == 0)
    {
        return dataModel[index.row()].name;
    }
    else if (index.column() == 1)
    {
        return dataModel[index.row()].size;
    }
    else if (index.column() == 2)
    {
        return dataModel[index.row()].percent;
    }
    else
        return QVariant();
}

//метод setModel, который будет устанавливать в модель данные, необходимые для отображения
void BrowserModel::setModel(const QList<Data> &data)
{
    beginResetModel();
    dataModel = data;
    endResetModel();
}
