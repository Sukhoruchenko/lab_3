#ifndef CONTEXT_H
#define CONTEXT_H
#include <FileExplorer.h>

class Context
{
private:
    IExplorer *p;
public:
    explicit Context(IExplorer* strategy);
     ~Context();
    void explore(const QString& path);
    void setStrategy(IExplorer* strategy);
};

#endif // CONTEXT_H
