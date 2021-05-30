#include <iostream>
#include "Context.h"
#include "FileExplorer.h"
#include "GroupingByType.h"
#include "GroupingByFolder.h"
#include <QCoreApplication>

QTextStream cout(stdout), cin(stdin);

int main()
{
    IExplorer* f = new GroupingByFolder();
    Context* e = new Context(f);
    cout << "Enter path folder:" << Qt::endl;
    QString path;
    path = cin.readLine();
    e->explore(path);
    f = new GroupingByType();
    e->setStrategy(f);
    e->explore(path);
    delete f;
    delete e;
    return 0;
}
