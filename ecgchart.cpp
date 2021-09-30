#include "ecgchart.hpp"

#include <QtCharts/QAbstractAxis>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>
#include <QtCore/QRandomGenerator>
#include <QtCore/QDebug>

ECGChart::ECGChart(QGraphicsItem *parent, Qt::WindowFlags wFlags):
    QChart(QChart::ChartTypeCartesian, parent, wFlags),
    m_series(0),
    m_axisX(new QValueAxis()),
    m_axisY(new QValueAxis()),
    m_step(0),
    m_x(0),
    m_y(0)
{
    m_series = new QSplineSeries(this);
    QPen pen(Qt::red);
    pen.setWidth(3);
    m_series->setPen(pen);
    //m_series->append(m_x, m_y);

    addSeries(m_series);

    addAxis(m_axisX,Qt::AlignBottom);
    addAxis(m_axisY,Qt::AlignLeft);
    m_series->attachAxis(m_axisX);
    m_series->attachAxis(m_axisY);
    m_axisX->setTickCount(30);
    m_axisX->setRange(0, 25);
    m_axisX->setMin(0);
    m_axisX->setMax(25);

    m_axisY->setTickCount(10);
    m_axisY->setRange(-10000, 10000);
    m_axisY->setMin(-10000);
    m_axisY->setMax(10000);
}

ECGChart::~ECGChart()
{
}

void ECGChart::onUpdateChart(QVector<qint16> t_ecgPoint, int t_pos)
{
    if(t_pos == 0)
    {
        m_series->clear();
    }
    for(int i = 0; i < t_ecgPoint.size(); ++i)
    {
        m_series->append((i+t_pos)*0.002, t_ecgPoint.at(i));
    }

//    int scrollValue = plotArea().width() / m_axisX->tickCount();
//    int totalPoints = m_series->pointsVector().size();
//    if(totalPoints >= 2900){
//        scroll(scrollValue, 0);
    //    }
}

void ECGChart::onReset()
{
    m_series->clear();
}
