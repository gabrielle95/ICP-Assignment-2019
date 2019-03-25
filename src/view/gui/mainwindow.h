#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../../controller/Application.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_tabWidget_tabCloseRequested(int index);

    void on_addtab_btn_clicked();

    void sl_onMoveRequest(Position from, Position to);

private:
    int gameNumber;
    Ui::MainWindow *ui;

    appPtr_t application;
    std::vector<int> gameIds;
};

#endif
