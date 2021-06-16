#include "Form.h"
#include <iostream>
#include "Context.h"
#include <QApplication>
#include "FileExplorer.h"
#include "GroupingByType.h"
#include "GroupingByFolder.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Form t;
    t.show();

    return a.exec();
}

