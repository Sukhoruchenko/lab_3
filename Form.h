#ifndef FORM_H
#define FORM_H
#include <QWidget>
#include "Context.h"
#include <QMainWindow>
#include "BrowserModel.h"
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
    enum Strategies
    {
        GroupingFolder,
        GroupingType
    };
    ~Form();
    explicit Form(QMainWindow *parent = nullptr);
private:
    Ui::Form *ui;
    QFileSystemModel* model;
    BrowserModel* FileModel;
    Strategies strategy;
    Context* c;
    QString path;
    QList<Data> data;
public slots:
    void selectStrategy(int index);
    void selectingModifiedSlot(const QItemSelection& selected, const QItemSelection& deselected);
};
#endif // FORM_H
