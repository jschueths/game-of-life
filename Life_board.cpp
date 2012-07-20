// Life_board.cpp

#include <QtGui>
#include "Life_board.h"

LifeBoard::LifeBoard(QWidget *parent) : QWidget(parent)
{
  field = new LifeField(this);
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

void LifeBoard::toggleButtons()
{
  startButton->setEnabled((startButton->isEnabled() ? false : true));
  stopButton->setEnabled((stopButton->isEnabled() ? false : true));
  stepButton->setEnabled((stepButton->isEnabled() ? false : true));
  clearButton->setEnabled((clearButton->isEnabled() ? false : true));
  return;
}

bool& LifeBoard::operator()(int x, int y)
{
  return field(x, y);
}

const bool& LifeBoard::operator()(const int x, const int y) const
{
  return field(x, y);
}
