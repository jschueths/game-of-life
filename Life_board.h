//////////////////////////////////////////////////////////////////////
/// @file Life_board.h
/// @author jschueths
/// @brief This is the class definition of the LifeBoard class.
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/// @class LifeBoard
/// @brief The LifeBoard class is a wrapper around the LifeField
/// class and the input controls to affect the LifeField. 
//////////////////////////////////////////////////////////////////////
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
    LifeField *field;           ///< Pointer to the LifeField object
    QPushButton *startButton;   ///< Pointer to the Start button
    QPushButton *stopButton;    ///< Pointer to the Stop button
    QPushButton *stepButton;    ///< Pointer to the Step button
    QPushButton *clearButton;   ///< Pointer to the Clear button
    QRadioButton *slowButton;   ///< Pointer to the Slow radio button
    QRadioButton *normalButton; ///< Pointer to the Normal radio button
    QRadioButton *fastButton;   ///< Pointer to the Fast radio button
};

#endif
