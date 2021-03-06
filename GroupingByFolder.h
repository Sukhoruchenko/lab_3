#ifndef GROUPINGBYFOLDER_H
#define GROUPINGBYFOLDER_H
#include "FileExplorer.h"

class GroupingByFolder: public IExplorer
{
public:
    explicit GroupingByFolder() {};
    virtual ~GroupingByFolder() {};
    QList<Data> explore(const QString& path);
private:
    qint64 getSizeDir(const QString& path);
    qint64 getSize(QString const& path) const;
    qint64 getSumSize(const QMap<QString, qint64> sum) const;
    QMap<QString, qint64> getSizesFolders(QString path) const;
    QMap<QString, double> getFoldersByPercentage(qint64& fullSize, QMap<QString, qint64>& FoldersList) const;
};
#endif // GROUPINGBYFOLDER_H
