#ifndef FILEEXPLORER_H
#define FILEEXPLORER_H
#include <QDir>
#include <QFileInfo>
#include <QTextStream>
#include "SomeData.h"

class IExplorer
{
public:
    virtual QList<Data> explore(const QString& path) = 0;
    virtual ~IExplorer() {}
};

#endif // FILEEXPLORER_H
