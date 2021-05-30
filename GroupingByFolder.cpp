#include <QDir>
#include <QDebug>
#include <QFileInfo>
#include <QTextStream>
#include "GroupingByFolder.h"

qint64 getSizeDirectory(const QString& path)
{
    qint64 fullSize = 0;
    QDir dir(path);
    for (const auto i : dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot , QDir::Name | QDir::Type))
        fullSize += i.size();
    return fullSize;
}

qint64 GroupingByFolder::getSize(QString const& path) const
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

qint64 GroupingByFolder::getSumSize(const QMap<QString, qint64> sum) const
{
    qint64 fullSize = 0;
    foreach(qint64 size, sum.values())
        fullSize += size;
    return fullSize;
}

QMap<QString, double> GroupingByFolder::getFoldersByPercentage(qint64& fullSize, QMap<QString, qint64>& FoldersList) const
{
    QMap<QString, double> FoldersListPercentage;
    double percent;
    for (auto i = FoldersList.begin(); i != FoldersList.end(); ++i)
    {
        if (i.value() == 0)
            percent = 0;
         else
        {
          percent = double(i.value() * 100) / fullSize;
          if (percent < 0.01)
            percent = -percent;
        }
        FoldersListPercentage.insert(i.key(), percent);
    }
    return FoldersListPercentage;
}

QMap<QString, qint64> GroupingByFolder::getSizesFolders(QString path) const
{
    QFileInfo folder(path);
    QMap<QString, qint64> FoldersList;
    auto fullPathDirectory = folder.absoluteFilePath();
    FoldersList.insert(fullPathDirectory, getSizeDirectory(fullPathDirectory));
    for (auto x : QDir(path).entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden, QDir::Name | QDir::Type))
    {
        auto fullPath = x.absoluteFilePath();
        FoldersList.insert(fullPath, GroupingByFolder::getSize(fullPath));
    }
    return FoldersList;
}

void GroupingByFolder::Print(const QMap<QString, qint64>& FoldersAndTypes, const  QMap<QString, double> FoldersAndPercentage) const
{
    QTextStream cout(stdout);
    foreach(QString path, FoldersAndPercentage.keys())
    {
        double percent = FoldersAndPercentage.value(path);
        cout << qSetFieldWidth(25) << path << qSetFieldWidth(10)  << FoldersAndTypes.value(path) / 1024 << qSetFieldWidth(5)<< "KB";
        if (percent < 0 || percent == 0)
        {
             cout << qSetFieldWidth(10) << "  < 0.01 %\n";
        }
        else
             cout << qSetFieldWidth(10) << QString::number(percent, 'f', 2).append(" %") << "\n";
     }
}

void GroupingByFolder::explore(const QString& path)
{
    auto FoldersList = getSizesFolders(path);
    auto fullSize = getSumSize(FoldersList);
    auto FoldersByPercentage = getFoldersByPercentage(fullSize, FoldersList);
    Print(FoldersList, FoldersByPercentage);
}

