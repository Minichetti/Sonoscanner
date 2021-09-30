#ifndef ECGCHART_HPP
#define ECGCHART_HPP

#include <QtCharts/QChart>
#include <QObject>

QT_CHARTS_BEGIN_NAMESPACE
class QSplineSeries;
class QValueAxis;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class ECGChart : public QChart
{
    Q_OBJECT
public:
    ECGChart(QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = {});
    virtual ~ECGChart();

public slots:
    void onUpdateChart(QVector<qint16> t_ecgPoint, int t_pos);
    void onReset();

private:
    QSplineSeries *m_series;
    QStringList m_titles;
    QValueAxis *m_axisX;
    QValueAxis *m_axisY;
    qreal m_step;
    qreal m_x;
    qreal m_y;
};

#endif // ECGCHART_HPP
