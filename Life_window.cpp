// Life_board.cpp

#include <QtGui>
#include "Life_board.h"
#include "Life_window.h"

LifeWindow::LifeWindow(QWidget *parent) : QMainWindow(parent)
{
  board = new LifeBoard;

  setCentralWidget(board);

}
