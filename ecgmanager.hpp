#ifndef ECGMANAGER_H
#define ECGMANAGER_H

#include <QObject>
#include <ecgdata.hpp>
#include "qdir.h"
#include <QTextStream>
#include <QDebug>
#include <QTimer>

class ECGManager : public QObject
{
    Q_OBJECT
public:
    explicit ECGManager(QObject *parent = nullptr);
    void loadEcgPoints();
    void addDataFromFile(QString t_file);
    void addDataFromFiles(QVector<QString> t_fileList);

signals:
    void setECGToView(QVector<qint16> t_pointlist, int t_pos);
    void EGCDisplayEnded();

public slots:
    void onStart();
    void onPlayECG();
    void onPauseECG();
    void onECGUpdate();

    void onSetRawECG();
    void onSetFilteredECG();
    void onResetCursor();

private:
    ECGData*            m_pEcgObj;
    QTimer*             m_pEcgTimer;

};

#endif // ECGMANAGER_H
