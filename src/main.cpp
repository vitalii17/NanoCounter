#include <QtGui/QApplication>
#include "mainwindow.h"
#include "volumekeys.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QCoreApplication::setOrganizationName("VS");
    QCoreApplication::setApplicationName("NanoCounter");

    MainWindow mainWindow;
//    mainWindow.setAttribute(Qt::WA_LockPortraitOrientation);
    mainWindow.showMaximized();

    VolumeKeys VolumeKeys(&mainWindow);

    return app.exec();
}
