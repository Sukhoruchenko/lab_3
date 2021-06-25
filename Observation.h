#ifndef OBSERVATION_H
#define OBSERVATION_H
#include <QLayout>
#include <QTableView>
#include <QHeaderView>
#include "BrowserModel.h"
class Observation : public FileObserver
{
private:
    BrowserModel* Model;
    QTableView* View;
public:
    explicit Observation(QLayout* l);
    ~Observation();
    void Update(QList<Data> d) const;
};

#endif // OBSERVATION_H




