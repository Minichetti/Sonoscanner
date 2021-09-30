#include "ecgdata.hpp"

/***************************************
 * Mean average of window size 2n+1 where n is the offset
 * ************************************/
qint16 GetMeanAverage(size_t index, const QVector<qint16>& t_points, int t_offsset){
    if(index < t_offsset || index >= t_points.size() - 1 - t_offsset){
         return t_points.at(index);
     }
     qint16 Sum = 0;
     for(size_t i = (index - t_offsset); i <= (index + t_offsset); i++){
         Sum += t_points[i];
     }
     return Sum / ((t_offsset*2)+1);
}

/***************************************
 * Calculate moving average
 * ************************************/
QVector<qint16> CalculateMovingAverage(const QVector<qint16>& t_points, int t_offsset){
    QVector<qint16> result;
    for(size_t i = 0; i < t_points.size(); i++){
         result.push_back(GetMeanAverage(i, t_points, t_offsset));
    }
    return result;
}

/***************************************
 * Default constructor
 * ************************************/
ECGData::ECGData(QObject *parent) : QObject(parent), m_cursor(0)
{
}

/***************************************
 * getter | returns the filtered ECG data points
 * ************************************/
QVector<qint16> ECGData::getFilteredECGPoints() const
{
    return m_filteredECGPoints;
}

/***************************************
 * getter | returns the raw ECG data points
 * ************************************/
QVector<qint16> ECGData::getRawECGPoints() const
{
    return m_rawECGPoints;
}

void ECGData::append(qint16 t_point)
{
    m_rawECGPoints.append(t_point);
}

/***************************************
 * returns sub vector from posistion
 * 't_pos' and of lenght 't_lenght'
 * ************************************/
QVector<qint16> ECGData::mid(int t_pos, int t_lenght)
{
    return m_filteredECGPoints.mid(t_pos, t_lenght);
}

/***************************************
 * nbEchantillons = 2n+1   n = offset
 * ************************************/
void ECGData::filterECG(int t_offset)
{
    m_filteredECGPoints = CalculateMovingAverage(m_rawECGPoints, t_offset);
}


