#ifndef FILEEXPLORER_H
#define FILEEXPLORER_H
#include <QDir>
#include "Data.h"
#include <QString>
#include <QVector>
#include <QFileInfo>
#include <QTextStream>

class FileObserver
{
public:
    FileObserver() {}
    virtual void Update(QList<Data> d) const = 0;
    virtual ~FileObserver() = default;
};

class Browser
{
private:
    FileObserver* observer;
public:
    virtual ~Browser() {}
    virtual void explore(const QString& path) = 0;

    void Fix(FileObserver* o)
    {
        if (o) observer = o;
    }

    void Finish(const QList<Data>& d) const
    {
        observer->Update(d);
    }
};

#endif // FILEEXPLORER_H
