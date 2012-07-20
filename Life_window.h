#ifndef __LIFE_WINDOW_H__
#define __LIFE_WINDOW_H__

#include <QtGui>
#include <QApplication>
#include "Life_board.h"

class LifeWindow : public QMainWindow
{
  public:
    LifeWindow(QWidget *parent = 0);


  private:
    LifeBoard *board;

};

#endif
