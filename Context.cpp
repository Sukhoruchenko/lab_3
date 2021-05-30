#include "Context.h"

Context::~Context()
{}

Context::Context(IExplorer* strategy) : p(strategy) {}


void Context::explore(const QString& path)
{
    if (p)
    p->explore(path);
}

void Context::setStrategy(IExplorer* strategy)
{
    p = strategy;
}
