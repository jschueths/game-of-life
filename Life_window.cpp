//////////////////////////////////////////////////////////////////////
/// @file Life_window.cpp
/// @author jschueths
/// @brief This is the implementation of the LifeWindow class.
//////////////////////////////////////////////////////////////////////

#include <QtGui>
#include "Life_window.h"


//////////////////////////////////////////////////////////////////////
/// @fn LifeWindow::LifeWindow(QWidget *parent)
/// @brief Constructor for the LifeWindow class.
/// @pre none
/// @post A new LifeWindow object is created.
//////////////////////////////////////////////////////////////////////
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

//////////////////////////////////////////////////////////////////////
/// @fn void LifeWindow::open()
/// @brief Opens and reads in a file from disk.
/// @pre none
/// @post Sets the LifeField to the configuration that was stored
/// in the file.
//////////////////////////////////////////////////////////////////////
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

//////////////////////////////////////////////////////////////////////
/// @fn void LifeWindow::save()
/// @brief Saves the current LifeField configuration to disk.
/// @pre none
/// @post A configuration file is saved to disk.
//////////////////////////////////////////////////////////////////////
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
          stream << board->operator()(i, j);
        }
        stream << "\n";
      }
      stream.flush();
      file.close();
    }
  }
  return;
}
