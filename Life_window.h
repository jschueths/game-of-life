//////////////////////////////////////////////////////////////////////
/// @file Life_window.h
/// @author jschueths
/// @brief This is the class definition of the LifeWindow class.
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/// @class LifeWindow
/// @brief The LifeWindow class provides a QMainWindow wrapper to
/// bring in FileMenu functionality in a nice layout. 
//////////////////////////////////////////////////////////////////////
#ifndef __LIFE_WINDOW_H__
#define __LIFE_WINDOW_H__

#include <QtGui>
#include <QApplication>
#include "Life_board.h"

class LifeWindow : public QMainWindow
{
  Q_OBJECT

  public:
    LifeWindow(QWidget *parent = 0);

  private:
    LifeBoard *board;     ///< A pointer to the LifeBoard object
    QMenu *fileMenu;      ///< A pointer to a QMenu object
    QAction *openAction;  ///< A pointer to the Open action
    QAction *saveAction;  ///< A pointer to the Save action
    QAction *exitAction;  ///< A pointer to the Exit action

  private slots:
    void open();
    void save();
};

#endif
