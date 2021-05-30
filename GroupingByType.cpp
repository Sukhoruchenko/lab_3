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

void GroupingByType::Print(const QMap<QString, qint64>& FileTypesList, const  QMap<QString, double> FileTypesPercantage) const
{
    QTextStream cout(stdout);
    foreach(QString path, FileTypesPercantage.keys())
        {
            double percent = FileTypesPercantage.value(path);
            cout << qSetFieldWidth(25) << path << qSetFieldWidth(10)  << FileTypesList.value(path) / 1024 << qSetFieldWidth(5)<< "KB";
            if (percent < 0 || percent == 0)
            {
               cout << qSetFieldWidth(10) << "  < 0.01 %\n";
            }
            else
               cout << qSetFieldWidth(10) << QString::number(percent, 'f', 2).append(" %") << "\n";
        }
}

void GroupingByType::explore(const QString& path)
{
    QMap<QString, qint64> fileTypesList;
    getTypesAndSizesFiles(path, fileTypesList);
    auto fullSize = getSumSize(fileTypesList);
    auto fileTypesByPercantage = getTypesFilesByPercentage(fullSize, fileTypesList);
    Print(fileTypesList, fileTypesByPercantage);
}

