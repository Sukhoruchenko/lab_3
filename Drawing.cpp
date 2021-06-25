#include "Drawing.h"

Drawing::~Drawing()
{
    delete view;
}

Drawing::Drawing(QLayout *l)
{
    model = new QChart();
    view = new QChartView();
    view->setChart(model);
    addWidget(l);
}

void Drawing::setChart(QList<Data> d) const
{
    qint64 size = 0;
    for (auto x : d)
    {
        size += x.size.toLongLong();
    }
    model->setTitle("");

    if (d.size() > 1)
    {
        qint64 size_ = 0;
        auto s = d.begin() + 2;
        while (s != d.end())
        {
            size_ += s->size.toLongLong();
            s = d.erase(s);
        }

        double percent = double(size_ * 100) / size;
        d.push_back(Data("Others", QString::number(size_), QString::number(percent, 'f', 2).append(" %"), (qreal)size_ / size));
    }

    setData(d);
}

void Drawing::addWidget(QLayout *l)
{
    l->addWidget(view);
}

void Drawing::Update(QList<Data> d) const
{
    setChart(d);
}

void Drawing::setData(QList<Data> d) const
{
    deleteSeries(model);
    QAbstractSeries* series = addData(d);
    addSeries(series);
}

void Drawing::deleteSeries(QChart *c) const
{
    c->removeAllSeries();
}

void Drawing::addSeries(QAbstractSeries *s) const
{
    model->addSeries(s);
}

BarDrawing::BarDrawing(QLayout *layout) : Drawing(layout) {}


QAbstractSeries *BarDrawing::addData(QList<Data> d) const
{
    QBarSeries* series = new QBarSeries();
    for (auto i : d)
    {
        QBarSet* set = new QBarSet(i.name + " (" + i.percent.toHtmlEscaped() + ")");
        set->append(i.proportion);
        series->append(set);
    }
    return series;
}

PieDrawing::PieDrawing(QLayout *l) : Drawing(l) {}

QAbstractSeries *PieDrawing::addData(QList<Data> d) const
{
    QPieSeries* series = new QPieSeries();
    for (auto i : d)
    {
        series->append(i.name + " (" + i.percent.toHtmlEscaped() + ")", i.proportion);
    }
    return series;
}
