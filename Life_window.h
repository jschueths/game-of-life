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
    LifeBoard *board;
    QMenu *fileMenu;
    QAction *openAction;
    QAction *saveAction;
    QAction *exitAction;

  private slots:
    void open();
    void save();
};

#endif
