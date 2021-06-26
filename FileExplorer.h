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
    QList<FileObserver* > observer;
public:
    virtual ~Browser()
    {
        for (auto i : observer)
            delete i;
    }
    virtual void explore(const QString& path) = 0;

    void Fix(FileObserver* o)
    {
        if (o && !observer.contains(o))
        {
            observer.push_back(o);
        }
    }

    void unFix(FileObserver* o)
    {
        observer.removeOne(o);
    }

    void Finish(const QList<Data>& d) const
    {
        for(auto i : observer)
            i->Update(d);
    }
};

#endif // FILEEXPLORER_H
