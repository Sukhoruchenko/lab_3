#ifndef DRAWING_H
#define DRAWING_H
#include <memory>
#include <QBarSet>
#include <QLayout>
#include <QWidget>
#include <QBarSeries>
#include <QPieSeries>
#include <QChartView>
#include "FileObserver.h"
#include <QGraphicsLayout>
#include <QtCharts/QChartGlobal>
#include <QtCharts/QAbstractSeries>

QT_CHARTS_BEGIN_NAMESPACE
class QChartView;
class QChart;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class Drawing: public FileObserver
{
private:
    QChartView* view;
    QChart* model;
public:
    Drawing() = default;
    virtual ~Drawing();
    Drawing(QLayout* l);
    void addWidget(QLayout* l);
    void Update(QList<Data> d) const;
    void setData(QList<Data> d) const;
    void setChart(QList<Data> d) const;
    void deleteSeries(QChart* c) const;
    void addSeries(QAbstractSeries* s) const;
    virtual QAbstractSeries* addData( QList<Data> d) const = 0;
};

class PieDrawing : public Drawing
{
public:
    explicit PieDrawing(QLayout* l);
    PieDrawing() = default;
    QAbstractSeries * addData(QList<Data> d) const;
};

class BarDrawing : public Drawing
{
public:
    explicit BarDrawing(QLayout* l);
    BarDrawing() = default;
    QAbstractSeries * addData(QList<Data> d) const;
};
#endif // DRAWING_H




