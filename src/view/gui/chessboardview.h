/*
 * @file chessboardview.h
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
#ifndef CHESSBOARDVIEW_H
#define CHESSBOARDVIEW_H

#include <array>
#include <QWidget>
#include "../../common/Position.h"
#include "../../common/CommandStructure.h"
#include "styles.h"
#include "qchesscell.h"

const int MAX_CELLS = 8;
const int MAX_CAPTURED = 32;

namespace Ui
{
class chessBoardView;
}

/**
 * @brief The class representing chess board gui
 *
 */
class chessBoardView : public QWidget
{
  Q_OBJECT

public:

  /**
   * @brief Construct a new chess Board View object
   *
   * @param id The id of the view corresponding to the game instance id
   * @param parent The parent widget
   */
  explicit chessBoardView(int id, QWidget *parent = 0);

  /**
   * @brief Destroy the chess Board View object
   *
   */
  ~chessBoardView();

  /**
   * @brief Set corresponding styles to all cells
   *
   */
  void draw();

  /**
   * @brief Get the view id
   *
   * @return int The id of the view
   */
  int Id() const
  {
    return this->id_;
  }

  /**
   * @brief Determines if the white team is on turn
   *
   * @return true The white team goes
   * @return false The black team goes
   */
  bool isWhitesTurn() const
  {
    return this->itsWhitesTurn_;
  }

  /**
   * @brief Set the Serialized Data to a privaate property
   *
   * @param data The loaded data to set
   */
  void setSerializedData(std::string data)
  {
    serializedData_ = data;
  }

  /**
   * @brief Get the Serialized Data from a property
   *
   * @return std::string The serialized data
   */
  std::string getSerializedData() const
  {
    return serializedData_;
  }

  /**
   * @brief Execute move after the validity request has been evaluated as true
   *
   */
  void executePendingMove();

  /**
   * @brief Mark green the cells that were evaluated as available to move by unit
   *
   * @param cellPositions All the cells that are available
   */
  void markAvailableCellsForMove(std::vector<Position> cellPositions);

  /**
   * @brief Set cells checkable according to whose move it is
   *
   * @param positions The obtained positions of the checkable cells
   */
  void setTheseCellsCheckable(std::vector<Position> positions);

  /**
   * @brief Execute an undo move
   *
   * @param data The data to execute the move according to
   */
  void executeUndoMove(CommandStructure data);

  /**
   * @brief Execute a redo move
   *
   * @param data The data to execute the move according to
   */
  void executeRedoMove(CommandStructure data);

  /**
   * @brief Handles the ending of the game, displays msgbox of game ending
   *
   */
  void onGameFinish();

signals:
  void sig_emitClickedCell(QChessCell *cell);
  void sig_emitMoveRequest(Position from, Position to);
  void sig_emitAvailableCellsRequest(Position from);
  void sig_emitRequestUnitsOnTurn(bool isWhitesTurn);
  void sig_emitRequestUndo();
  void sig_emitRequestRedo();
  void sig_emitRequestSerializedData();
  void sig_emitRequestDeserializedData();
  void sig_emitRequestForward();
  void sig_emitRequestBackward();

private slots:
  void sl_cellWasClicked();
  void sl_undoClicked();
  void sl_redoClicked();
  void sl_requestSerializedData();
  void sl_requestDeserializedData();
  void sl_saveGameToFile();
  void sl_openGameFromFile();
  void sl_forwardClicked();
  void sl_backwardClicked();

private:
  void onCellSelectionChanged(QChessCell *from, QChessCell *to);
  void onRequestAvailableMoves(QChessCell *from);
  void initStyles_();
  void moveUnitStyle_();
  Position getCellPosition_(QChessCell *cell);
  void clearAvailableForMove_();
  QPushButton *generateAppButton_(QString style, QString tooltip);
  void moveCursor_(int position);

  Ui::chessBoardView *ui;
  std::array<std::array<QChessCell *, MAX_CELLS>, MAX_CELLS> qCellBoard_;
  std::vector<QChessCell *> qCapturedBoard_;

  int id_;

  QChessCell *pendingFrom;
  QChessCell *pendingTo;

  QChessCell *previouslyClickedCell;

  bool itsWhitesTurn_;

  // variable to save loaded data and data before saving
  std::string serializedData_;

  int commandCounter_;
};

#endif // CHESSBOARDVIEW_H
