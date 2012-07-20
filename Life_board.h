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
    bool& operator()(int x, int y);
    const bool& operator()(const int x, const int y) const;
   
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
