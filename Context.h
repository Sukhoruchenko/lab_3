#ifndef CONTEXT_H
#define CONTEXT_H
#include <FileExplorer.h>

class Context
{
private:
    Browser *b;
public:
    Context() = default;
    explicit Context(Browser* strategy);
    ~Context();
    void explore(const QString& path);
    void setStrategy(Browser* strategy);
};

#endif // CONTEXT_H
