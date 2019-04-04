#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include "mainwindow.h"

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);
    QCoreApplication::setOrganizationName("ICP Project");
    QCoreApplication::setApplicationName("Chess");
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);

    MainWindow mainWin;
    mainWin.setWindowIcon(QIcon(":/res/chess_icons/knight_black.svg"));
    mainWin.show();

    return app.exec();
}
