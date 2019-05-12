/*
 * @file mainwindow.h
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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../../controller/Application.h"

namespace Ui
{
class MainWindow;
}

/**
 * @brief The class handling the main gui window
 *
 */
class MainWindow : public QMainWindow
{
  Q_OBJECT

public:

  /**
   * @brief Construct a new Main Window object
   *
   * @param parent The parent widget
   */
  explicit MainWindow(QWidget *parent = 0);

  /**
   * @brief Destroy the Main Window object
   *
   */
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
  void sl_onRequestDeserializedData();

  void sl_onRequestForward();
  void sl_onRequestBackward();

  void sl_onRequestRestart();

private:
  Ui::MainWindow *ui;
  int gameNumber;
  appPtr_t application;
  std::vector<int> gameIds;
};

#endif
