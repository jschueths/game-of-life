// Life_board.cpp

#include <QtGui>
#include "Life_window.h"

LifeWindow::LifeWindow(QWidget *parent) : QMainWindow(parent)
{
  board = new LifeBoard;

  openAction = new QAction(tr("&Open"), this);
  saveAction = new QAction(tr("&Save"), this);
  exitAction = new QAction(tr("E&xit"), this);

  connect(openAction, SIGNAL(triggered()), this, SLOT(open()));
  connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));
  connect(exitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

  fileMenu = menuBar()->addMenu(tr("&File"));
  fileMenu->addAction(openAction);
  fileMenu->addAction(saveAction);
  fileMenu->addSeparator();
  fileMenu->addAction(exitAction);

  setCentralWidget(board);
  setWindowTitle(tr("Conway's Game of Life"));

}

void LifeWindow::open()
{
  QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Grid Files (*.grd)"));
  if(fileName != "")
  {
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
    {
      QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
      return;
    }
    // Read in and set the grid here.
    file.close();
  }
  return;
}

void LifeWindow::save()
{
  QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("Grid Files (*.grd)"));
  if(fileName != "")
  {
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly))
    {
      QMessageBox::critical(this, tr("Error"), tr("Could not save file"));
    }
    else
    {
      QTextStream stream(&file);
      // Write out the grid here.
      for(int i = 0; i < 52; i++)
      {
        for(int j = 0; j < 52; j++)
        {
          stream << board(i, j);
        }
        stream << "\n";
      }
      stream.flush();
      file.close();
    }
  }
  return;
}
