#include <QDir>
#include <QDebug>
#include <QFileInfo>
#include <QTextStream>
#include "GroupingByType.h"

qint64 GroupingByType::getSize(QString const& path) const
{
    qint64 fullSize = 0;
    QDir::Filters filters = QDir::AllEntries | QDir::NoDotAndDotDot | QDir::Hidden;
    QDir::SortFlags types = QDir::Name | QDir::Type | QDir::Size;
    QDir dir(path);
    for (const auto p : dir.entryInfoList(filters, types))
    if (p.isDir())
    {
        fullSize += getSize(p.absoluteFilePath());
    }
    else fullSize += p.size();
    return fullSize;
}

qint64 GroupingByType::getSumSize(const QMap<QString, qint64> sum) const
{
    qint64 fullSize = 0;
    foreach(qint64 size, sum.values())
        fullSize += size;
    return fullSize;
}

void GroupingByType::getTypesAndSizesFiles(const QString& path, QMap<QString, qint64>& FileTypesList)
{
    QDir dir(path);
    for (const auto i : dir.entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot | QDir::Hidden, QDir::Name | QDir::Type | QDir::Size))
    {
        if (i.isDir() && !i.isSymLink())
        {
            getTypesAndSizesFiles(i.absoluteFilePath(), FileTypesList);
        }
        else
        {
            if (FileTypesList.keys().contains(i.suffix().toLower()))
            {
                FileTypesList[i.suffix()] += i.size();
            }
            else
            {
                FileTypesList.insert(i.suffix().toLower(), i.size());
            }
        }
    }
}

QMap<QString, double> GroupingByType::getTypesFilesByPercentage(qint64& fullSize, QMap<QString, qint64>& FileTypesList) const
{
    QMap<QString, double> FileTypesListPercentage;
    double percent;
    for (auto i = FileTypesList.begin(); i != FileTypesList.end(); ++i)
    {
        if (i.value() == 0)
            percent = 0;
         else
        {
          percent = double(i.value() * 100) / fullSize;
          if (percent < 0.01)
            percent = -percent;
        }

        FileTypesListPercentage.insert(i.key(), percent);
    }
    return FileTypesListPercentage;
}

QList<Data> GroupingByType::explore(const QString& path)
{
    QMap<QString, qint64> fileTypesList;
    getTypesAndSizesFiles(path, fileTypesList);
    auto fullSize = getSumSize(fileTypesList);
    auto fileTypesByPercantage = getTypesFilesByPercentage(fullSize, fileTypesList);
    QList<Data> data;
    QList<QPair<double, QString>> TypeList;
    for (auto p : fileTypesByPercantage.keys())
    {
      TypeList.append(QPair<double, QString>(fileTypesByPercantage[p], p));
    }
    for (auto x : TypeList)
    {
        if (x.first < 0)
        {
            data.append(Data(x.second, QString::number(fileTypesList.value(x.second)), QString("< 0.01 %")));
        } else
        {
        data.append(Data("." + x.second, QString::number(fileTypesList.value(x.second)), QString::number(x.first, 'f', 2).append(" %")));
        }
    }
    return data;
}

