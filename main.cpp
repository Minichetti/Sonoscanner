#include "mainwindow.hpp"
#include "mainapplication.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainApplication maiApp;
    return app.exec();
}
