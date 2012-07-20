// Life_board.h

#ifndef __LIFE_BOARD_H__
#define __LIFE_BOARD_H__

#include <QApplication>
#include "Life_field.h"

class LifeBoard : public QWidget
{
  Q_OBJECT
  
  public:
    LifeBoard(QWidget *parent = 0);
   
  protected slots:
    void toggleButtons();
  
  private:
    LifeField *field;
    QPushButton *startButton;
    QPushButton *stopButton;
    QPushButton *stepButton;
    QPushButton *clearButton;
    QRadioButton *slowButton;
    QRadioButton *normalButton;
    QRadioButton *fastButton;
};

#endif
