#ifndef FORM_H
#define FORM_H
#include <QDebug>
#include <memory>
#include <QWidget>
#include "Context.h"
#include "Drawing.h"
#include "Drawing.h"
#include <QMainWindow>
#include "Observation.h"
#include <QItemSelection>
#include "BrowserModel.h"
#include <QFileSystemModel>
#include "GroupingByType.h"
#include "GroupingByFolder.h"

namespace Ui
{
    class Form;
}

class Form : public QMainWindow
{
    Q_OBJECT
public:
public:
    explicit Form(QMainWindow *parent = nullptr);
    ~Form();
private:
    Ui::Form *ui;
    QFileSystemModel* fModel;
    BrowserModel* FileModel;
    QString path;
    Browser* folder;
    Browser* type;
    Browser* group;
    FileObserver* View;
    FileObserver* ObservationAdapter;
    FileObserver* pie;
    FileObserver* bar;
public slots:
    void selectStrategy(int index);
    void selectingModifiedSlot(const QItemSelection& selected, const QItemSelection& deselected);
    void selecting(int index);
};
#endif // FORM_H

