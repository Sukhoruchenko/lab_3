#ifndef GROUPINGBYTYPE_H
#define GROUPINGBYTYPE_H
#include "FileExplorer.h"

class GroupingByType : public Browser
{
public:
    explicit GroupingByType() {};
    virtual ~GroupingByType() {};
    void explore(const QString& path);
private:
    qint64 getSize(QString const& path) const;
    qint64 getSumSize(const QMap<QString, qint64> sum) const;
    void getTypesAndSizesFiles(const QString& path, QMap<QString, qint64>& FileTypesList);
    QMap<QString, double> getTypesFilesByPercentage(qint64& fullSize, QMap<QString, qint64>& FileTypesList) const;
};

#endif // GROUPINGBYTYPE_H
