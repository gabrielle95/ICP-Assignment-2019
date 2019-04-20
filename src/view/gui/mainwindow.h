#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../../controller/Application.h"

namespace Ui
{
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

  void sl_onRequestAvailableCells(Position from);

  void sl_onRequestUnitsOnTurn(bool isWhitesTurn);

  void sl_onRequestUndo();

  void sl_onRequestRedo();

  void sl_onRequestSerializedData();

private:
  Ui::MainWindow *ui;
  int gameNumber;
  appPtr_t application;
  std::vector<int> gameIds;
};

#endif
