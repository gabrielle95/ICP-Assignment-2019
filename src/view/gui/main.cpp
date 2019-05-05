/*
 * @file main.cpp
 *
 * Project name:
 * Chess 2019
 *
 * Description:
 * http://www.fit.vutbr.cz/study/courses/ICP/public/ICP-PRJ-zadani.html.cs
 *
 * Team:
 * @author Gabriela Pacakova (xpacak01)
 * @author Adam Lanicek (xlanic04)
 */
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
    mainWin.setWindowTitle("ICP Chess 2019");
    mainWin.show();

    return app.exec();
}
