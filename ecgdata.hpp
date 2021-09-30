#ifndef ECGDATA_H
#define ECGDATA_H

#include <QObject>

class ECGData : public QObject
{
    Q_OBJECT
public:
    explicit ECGData(QObject *parent = nullptr);

    QVector<qint16> getRawECGPoints() const;
    QVector<qint16> getFilteredECGPoints() const;
    void append(qint16 t_point);
    QVector<qint16> mid(int t_pos, int t_lenght);
    int getCursor() const { return m_cursor; };
    void setCursor(int t_value) { m_cursor = t_value; }
    int getRawNbPoints() const { return m_rawECGPoints.size(); }
    int getFilteredNbPoints() const { return m_filteredECGPoints.size(); }

    void filterECG(int t_nbEchantillons);

signals:

private:
    QVector<qint16>     m_filteredECGPoints;
    QVector<qint16>     m_rawECGPoints;
    int                 m_cursor;

};

#endif // ECGDATA_H
