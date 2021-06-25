#include "Context.h"

Context::~Context()
{
    if (b) delete b;
}

Context::Context(Browser* strategy) : b(strategy) {}


void Context::explore(const QString& path)
{
     b->explore(path);
}

void Context::setStrategy(Browser* strategy)
{
    if (b) delete b;
    b = strategy;
}
