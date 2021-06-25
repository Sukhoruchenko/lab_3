#include "Form.h"
#include "ui_Form.h"

Form::~Form()
{
    delete ui;
    delete fModel;
    delete ObservationAdapter;
    delete FileModel;
    delete pie;
    delete bar;
    delete folder;
    delete type;
}

Form::Form(QMainWindow *parent) : QMainWindow(parent), ui(new Ui::Form),folder(new GroupingByFolder()),type(new GroupingByType()), group(folder)
{
    ui->setupUi(this);

    QString homePath = QDir::homePath();
    fModel =  new QFileSystemModel(this);
    fModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    fModel->setRootPath(homePath);

    ObservationAdapter = new Observation(ui->stackedWidget_7->layout());
    bar = new BarDrawing(ui->stackedWidget_7->layout());
    pie = new PieDrawing(ui->stackedWidget_7->layout());
    View = ObservationAdapter;
    group->Fix(View);

    ui->treeView_7->setModel(fModel);
    ui->treeView_7->header()->setSectionResizeMode(QHeaderView::ResizeToContents);

    connect(ui->comboBox_14, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Form::selecting);
    connect(ui->comboBox_13, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Form::selectStrategy);
    connect(ui->treeView_7->selectionModel(), &QItemSelectionModel::selectionChanged, this,  &Form::selectingModifiedSlot);
}

void Form::selectStrategy(int index)
{
    switch (index)
    {
    case 0:
        group = folder;
        break;
    case 1:
        group = type;
        break;
    }
    group->Fix(View);
    group->explore(path);
}

void Form::selectingModifiedSlot(const QItemSelection &selected, const QItemSelection &deselected)
{
    Q_UNUSED(deselected);

    QModelIndexList indexes = selected.indexes();
    path = fModel->filePath(indexes[0]);
    group->explore(path);
}


void Form::selecting(int index)
{
    switch(index)
    {
        case 0:
            View = ObservationAdapter;
            break;
        case 1:
            View = pie;
            break;
        case 2:
            View = bar;
            break;
    }
    group->Fix(View);
    group->explore(path);
    ui->stackedWidget_7->setCurrentIndex(index);
}

