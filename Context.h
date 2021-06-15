#ifndef CONTEXT_H
#define CONTEXT_H
#include <FileExplorer.h>

class Context
{
private:
    IExplorer *p;
public:
    Context() = default;
    explicit Context(IExplorer* strategy);
     ~Context();
    QList<Data> explore(const QString& path);
    void setStrategy(IExplorer* strategy);
};

#endif // CONTEXT_H
