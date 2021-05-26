#ifndef FILEEXPLORER_H
#define FILEEXPLORER_H
#include <QDir>
#include <QFileInfo>
#include <QTextStream>

class IExplorer
{
public:
    virtual void explore(const QString& path) = 0;
    virtual ~IExplorer() {}
};

#endif // FILEEXPLORER_H
