#ifndef __LIFE_WINDOW_H__
#define __LIFE_WINDOW_H__

#include <QtGui>
#include <QApplication>
#include "Life_board.h"

class LifeWindow : public QMainWindow
{
  public:
    LifeWindow(QWidget *parent = 0);

  private slots:
    void open();
    void save();

  private:
    LifeBoard *board;
    QMenu *fileMenu;
    QAction *openAction;
    QAction *saveAction;
    QAction *exitAction;
};

#endif
