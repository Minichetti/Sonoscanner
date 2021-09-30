#ifndef MAINAPPLICATION_HPP
#define MAINAPPLICATION_HPP

#include <QApplication>
#include <QObject>
#include <QThread>

#include "mainwindow.hpp"
#include "ecgdata.hpp"
#include "ecgmanager.hpp"

class MainApplication : public QObject
{
    Q_OBJECT

public:
    MainApplication(QObject *parent = nullptr);
    ~MainApplication();

    void createMainWindow();

public slots:

private:
    //UI Widgets
    MainWindow*                 m_pMainWindow;

    //Managers
    ECGManager*                 m_pECGManager;


};
#endif // MAINAPPLICATION_HPP
