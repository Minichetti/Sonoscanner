#include "ecgdata.hpp"
#include "ecgdata.hpp"
#include "ecgmanager.hpp"

/***************************************
 * Default constructor
 * ************************************/
ECGManager::ECGManager(QObject *parent) :
    QObject(parent),
    m_pEcgObj(new ECGData)
{
}

/***************************************
 * Function called when ECG Manager thead
 * is started and loads the ecg data from
 * files
 * ************************************/
void ECGManager::onStart()
{
    m_pEcgTimer = new QTimer();
    m_pEcgTimer->setInterval(200);
    connect(m_pEcgTimer, SIGNAL(timeout()), this, SLOT(onECGUpdate()));

    loadEcgPoints();
    m_pEcgObj->filterECG(3);
}

/***************************************
 * Get the all the files in the data folder
 * sort the files
 * then start to load each file
 * ************************************/
void ECGManager::loadEcgPoints()
{
    QVector<QString> fileList;
    QString pathToECGData = QDir::currentPath()+"/../data";

    QDir dir(pathToECGData);
    QDir::Filters fileFilters = QDir::Files;
    for(QString filePath : dir.entryList(fileFilters)) {
        QFileInfo fi(dir, filePath);
        if(fi.completeSuffix() == "txt")
        {
            fileList.append(fi.baseName());
        }
    }

    //sort file names
    auto sortAscending = [](QString t_fileA, QString t_fileB) { return t_fileA.midRef(4).toInt() < t_fileB.midRef(4).toInt(); };
    std::sort(fileList.begin(), fileList.end(), sortAscending);

    addDataFromFiles(fileList);
}

/***************************************
 * add ecg data from a single file
 * ************************************/
void ECGManager::addDataFromFile(QString t_file)
{
    QFile file(t_file);
    if(!file.open(QIODevice::ReadOnly)) {
        qWarning() << "error" << file.errorString();
    }

    QTextStream in(&file);

    in.readLine(); // skip the first line, we won't need nbData in this case
    while(!in.atEnd()) {
        QString line = in.readLine();
        qint16 ecgpoint = line.toInt();
        m_pEcgObj->append(ecgpoint);
    }

    file.close();
}

/***************************************
 * add ecg data from multiple files
 * ************************************/
void ECGManager::addDataFromFiles(QVector<QString> t_fileList)
{
    for(size_t i = 0; i < t_fileList.size(); ++i)
    {
        addDataFromFile("../data/"+ t_fileList.at(i) + ".txt");
    }
}

/***************************************
 * Start ECG display on chart
 * ************************************/
void ECGManager::onPlayECG()
{
    m_pEcgTimer->start();
}

/***************************************
 * Stop ECG display on chart
 * ************************************/
void ECGManager::onPauseECG()
{
    m_pEcgTimer->stop();
}

/***************************************
 * Updates data to plot
 * ************************************/
void ECGManager::onECGUpdate()
{
    int cursor = m_pEcgObj->getCursor();
    int totalSize = m_pEcgObj->getFilteredNbPoints();
    QVector<qint16> subPoints = m_pEcgObj->mid(m_pEcgObj->getCursor(), 100);
    emit setECGToView(subPoints, cursor);
    m_pEcgObj->setCursor(cursor + 100);
    if(totalSize < cursor){
        m_pEcgTimer->stop();
        emit EGCDisplayEnded();
        m_pEcgObj->setCursor(0);
    }
}

void ECGManager::onSetRawECG()
{
    QVector<qint16> rawPoints = m_pEcgObj->getRawECGPoints();
    emit setECGToView(rawPoints, 0);
}

void ECGManager::onSetFilteredECG()
{
    QVector<qint16> filteredPoints = m_pEcgObj->getFilteredECGPoints();
    emit setECGToView(filteredPoints, 0);
}

void ECGManager::onResetCursor()
{
    m_pEcgTimer->stop();
    emit EGCDisplayEnded();
    m_pEcgObj->setCursor(0);
}
