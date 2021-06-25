#include "Observation.h"

Observation::Observation(QLayout* l)
{
    Model = new BrowserModel();
    View = new QTableView();
    View->setModel(Model);
    l->addWidget(View);
}

Observation::~Observation()
{
    delete Model;
    delete View;
}

void Observation::Update(QList<Data> d) const
{
    Model->setModel(d);
}
