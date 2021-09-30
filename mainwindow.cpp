#include "mainwindow.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    resize(1200, 800);
    createCenterView();
    createToolbar();
    show();
}

MainWindow::~MainWindow()
{
}

void MainWindow::createCenterView()
{
    m_pECGChart = new ECGChart;
    m_pECGChart->setTitle("Dynamic spline chart");
    m_pECGChart->legend()->hide();
    m_pECGChart->setAnimationOptions(QChart::AllAnimations);
    m_pECGChartView = new QChartView(m_pECGChart);
    m_pECGChartView->setRenderHint(QPainter::Antialiasing);
    setCentralWidget(m_pECGChartView);
}

void MainWindow::createToolbar()
{
    QToolBar* toolbar = new QToolBar;
    m_pPlayPauseAction = new QAction;
    m_pPlayPauseAction->setText("Play");
    toolbar->addAction(m_pPlayPauseAction);
    connect(m_pPlayPauseAction, SIGNAL(triggered()), this, SLOT(onPlayPauseTriggered()));

    m_pSetRawECG = new QAction;
    m_pSetRawECG->setText("Raw ECG");
    toolbar->addAction(m_pSetRawECG);
    connect(m_pSetRawECG, SIGNAL(triggered()), this, SIGNAL(setRawECG()));

    m_pSetFilteredECG = new QAction;
    m_pSetFilteredECG->setText("Filtered ECG");
    toolbar->addAction(m_pSetFilteredECG);
    connect(m_pSetFilteredECG, SIGNAL(triggered()), this, SIGNAL(setFilteredECG()));

    m_pResetGraph = new QAction;
    m_pResetGraph->setText("reset display");
    toolbar->addAction(m_pResetGraph);
    connect(m_pResetGraph, SIGNAL(triggered()), m_pECGChart, SLOT(onReset()));
    connect(m_pResetGraph, SIGNAL(triggered()), this, SIGNAL(resetCursor()));

    addToolBar(Qt::ToolBarArea::LeftToolBarArea, toolbar);
}

void MainWindow::onSetECGToView(QVector<qint16> t_ecgPoints, int t_pos)
{
    m_pECGChart->onUpdateChart(t_ecgPoints, t_pos);
}

void MainWindow::onPlayPauseTriggered()
{
    if(m_pPlayPauseAction->text() == "Play")
    {
        m_pPlayPauseAction->setText("Pause");
        emit playECG();
    }
    else
    {
        m_pPlayPauseAction->setText("Play");
        emit pauseECG();
    }
}

void MainWindow::onECGDisplayEnded()
{
    m_pPlayPauseAction->setText("Play");
}

