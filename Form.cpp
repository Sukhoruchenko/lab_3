#include "Form.h"
#include "ui_Form.h"

Form::~Form()
{
    delete c;
    delete ui;
    delete model;
    delete FileModel;
}

Form::Form(QMainWindow *parent) : QMainWindow(parent), ui(new Ui::Form)
{
    ui->setupUi(this);

    QString homePath = QDir::homePath();

    model =  new QFileSystemModel(this);
    FileModel = new BrowserModel();

    model->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    model->setRootPath(homePath);

    ui->treeView->setModel(model);
    ui->tableView->setModel(FileModel);

    ui->treeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Form::selectStrategy);
    connect(ui->treeView->selectionModel(), &QItemSelectionModel::selectionChanged, this,  &Form::selectingModifiedSlot);

    c = new Context();
    strategy = Strategies::GroupingFolder;
}

void Form::selectStrategy(int index)
{
    switch (index)
    {
    case 0:
        strategy = Strategies::GroupingFolder;
        break;
    case 1:
        strategy = Strategies::GroupingType;
        break;
    }

    if (strategy == Strategies::GroupingType)
        c->setStrategy(new GroupingByType);
    else
       c->setStrategy(new GroupingByFolder);

    if (path.isEmpty())
        return;

    data = c->explore(path);
    FileModel->setModel(data);
}

void Form::selectingModifiedSlot(const QItemSelection &selected, const QItemSelection &deselected)
{
    Q_UNUSED(deselected);

    QModelIndexList indexes = selected.indexes();
    path = model->filePath(indexes[0]);

    if (strategy == Strategies::GroupingType)
        c->setStrategy(new GroupingByType);
    else
        c->setStrategy(new GroupingByFolder);

    if (path.isEmpty())
        return;

    data = c->explore(path);
    FileModel->setModel(data);
}

