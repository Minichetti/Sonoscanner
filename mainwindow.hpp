#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QChartView>
#include <QPushButton>
#include <QToolBar>
#include "ecgchart.hpp"
#include <QDebug>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void createCenterView();
    void createToolbar();

signals:
    void playECG();
    void pauseECG();

    void setRawECG();
    void setFilteredECG();
    void resetCursor();

public slots:
    void onSetECGToView(QVector<qint16>, int t_pos);
    void onPlayPauseTriggered();
    void onECGDisplayEnded();

private:
    ECGChart*       m_pECGChart;
    QChartView*     m_pECGChartView;
    QPushButton*    m_pPlayPauseECGButton;
    QAction*        m_pPlayPauseAction;
    QAction*        m_pSetRawECG;
    QAction*        m_pSetFilteredECG;
    QAction*        m_pResetGraph;

};

#endif // MAINWINDOW_H
