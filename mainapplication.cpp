#include "mainapplication.hpp"

/***************************************
 * Default constructor
 * ************************************/
MainApplication::MainApplication(QObject *parent) :
    QObject(parent)
{
    m_pMainWindow = new MainWindow();

    //ECG Manager
    m_pECGManager = new ECGManager();
    QThread* ECGManagerThread = new QThread();
    m_pECGManager->moveToThread(ECGManagerThread);
    connect(ECGManagerThread, SIGNAL(started()), m_pECGManager, SLOT(onStart()));
    ECGManagerThread->start();

    qRegisterMetaType<QVector<qint16>>("QVector<qint16>");
    connect(m_pECGManager, SIGNAL(setECGToView(QVector<qint16>, int)), m_pMainWindow, SLOT(onSetECGToView(QVector<qint16>, int)));
    connect(m_pECGManager, SIGNAL(EGCDisplayEnded()), m_pMainWindow, SLOT(onECGDisplayEnded()));

    connect(m_pMainWindow, SIGNAL(playECG()), m_pECGManager, SLOT(onPlayECG()));
    connect(m_pMainWindow, SIGNAL(pauseECG()), m_pECGManager, SLOT(onPauseECG()));

    connect(m_pMainWindow, SIGNAL(setRawECG()), m_pECGManager, SLOT(onSetRawECG()));
    connect(m_pMainWindow, SIGNAL(setFilteredECG()), m_pECGManager, SLOT(onSetFilteredECG()));
    connect(m_pMainWindow, SIGNAL(resetCursor()), m_pECGManager, SLOT(onResetCursor()));
}

/***************************************
 * Destructor
 * ************************************/
MainApplication::~MainApplication()
{
}


