#include "Context.h"

Context::~Context()
{}

Context::Context(IExplorer* strategy) : p(strategy) {}


QList<Data> Context::explore(const QString& path)
{
    if (p)
        return p->explore(path);
    return QList<Data>();
}

void Context::setStrategy(IExplorer* strategy)
{
    if (p)
        delete p;
    p = strategy;
}
