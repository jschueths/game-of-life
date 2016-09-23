//////////////////////////////////////////////////////////////////////
/// @file board.cpp
/// @author jschueths
/// @brief This is the implementation of the Board class.
//////////////////////////////////////////////////////////////////////

#include <QtGui>
#include "board.h"

//////////////////////////////////////////////////////////////////////
/// @fn Board::Board(QWidget *parent)
/// @brief Constructor for the Board class.
/// @pre none
/// @post A new Board object is created.
//////////////////////////////////////////////////////////////////////
Board::Board(QWidget *parent) : QWidget(parent) {
  field = new Field(this);
  startButton = new QPushButton(tr("Start"));
  stopButton = new QPushButton(tr("Stop"));
  stepButton = new QPushButton(tr("Step"));
  clearButton = new QPushButton(tr("Clear"));
  stopButton->setEnabled(false);
  
  slowButton = new QRadioButton(tr("Slow"));
  normalButton = new QRadioButton(tr("Normal"));
  fastButton = new QRadioButton(tr("Fast"));
  normalButton->setChecked(true);
  

  connect(startButton, SIGNAL(clicked()), field, SLOT(startGenerations()));
  connect(stopButton, SIGNAL(clicked()), field, SLOT(stopGenerations()));
  connect(stepButton, SIGNAL(clicked()), field, SLOT(nextGeneration()));
  connect(clearButton, SIGNAL(clicked()), field, SLOT(stopGenerations()));
  connect(clearButton, SIGNAL(clicked()), field, SLOT(clear()));

  connect(startButton, SIGNAL(clicked()), this, SLOT(toggleButtons()));
  connect(stopButton, SIGNAL(clicked()), this, SLOT(toggleButtons()));
  
  connect(slowButton, SIGNAL(clicked()), field, SLOT(setSlow()));
  connect(normalButton, SIGNAL(clicked()), field, SLOT(setNormal()));
  connect(fastButton, SIGNAL(clicked()), field, SLOT(setFast()));
  
  QHBoxLayout *buttonLayout = new QHBoxLayout;
  buttonLayout->addWidget(startButton);
  buttonLayout->addWidget(stepButton);
  buttonLayout->addWidget(stopButton);
  buttonLayout->addWidget(clearButton);
  
  QGroupBox *speedBox = new QGroupBox(tr("Simulation Speed"));
  QHBoxLayout *speedLayout = new QHBoxLayout;
  speedLayout->addWidget(slowButton);
  speedLayout->addWidget(normalButton);
  speedLayout->addWidget(fastButton);
  speedBox->setLayout(speedLayout);

  QFrame *lifeBox = new QFrame;
  QVBoxLayout *fieldLayout = new QVBoxLayout;
  fieldLayout->addWidget(field);
  lifeBox->setLayout(fieldLayout);
  
  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addWidget(lifeBox);
  mainLayout->addLayout(buttonLayout);
  mainLayout->addWidget(speedBox);
  mainLayout->setStretch(0, 1);
  setLayout(mainLayout);
  
  resize(550, 650);
  setFixedSize(550, 650);
  
}

//////////////////////////////////////////////////////////////////////
/// @fn void Board::toggleButtons()
/// @brief Enables and disables the control buttons based on state.
/// @pre none
/// @post The control buttons are toggled from their current state.
//////////////////////////////////////////////////////////////////////
void Board::toggleButtons() {
  startButton->setEnabled((startButton->isEnabled() ? false : true));
  stopButton->setEnabled((stopButton->isEnabled() ? false : true));
  stepButton->setEnabled((stepButton->isEnabled() ? false : true));
  clearButton->setEnabled((clearButton->isEnabled() ? false : true));
}

//////////////////////////////////////////////////////////////////////
/// @fn bool& Board::operator()(int x, int y)
/// @brief Mutator to the Field member.
/// @pre 'x' and 'y' must be greater than 0 and less than 52.
/// @post A reference to the boolean is returned.
/// @param x The x-coordinate
/// @param y The y-coordinate
//////////////////////////////////////////////////////////////////////
bool& Board::operator()(int x, int y) {
  return field->operator()(x, y);
}

//////////////////////////////////////////////////////////////////////
/// @fn const bool& Board::operator()(int x, int y) const
/// @brief Accessor to the Field member.
/// @pre 'x' and 'y' must be greater than 0 and less than 52.
/// @post A const reference to the boolean is returned.
/// @param x The x-coordinate
/// @param y The y-coordinate
//////////////////////////////////////////////////////////////////////
const bool& Board::operator()(const int x, const int y) const {
  return field->operator()(x, y);
}
