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
	mField = new Field(this);
	mStartButton = new QPushButton(tr("Start"));
	mStopButton = new QPushButton(tr("Stop"));
	mStepButton = new QPushButton(tr("Step"));

	mClearButton = new QPushButton(tr("Clear"));
	mStopButton->setEnabled(false);

	mSlowButton = new QRadioButton(tr("Slow"));
	mNormalButton = new QRadioButton(tr("Normal"));
	mFastButton = new QRadioButton(tr("Fast"));
	mNormalButton->setChecked(true);

	connect(mStartButton, SIGNAL(clicked()), mField, SLOT(startGenerations()));
	connect(mStopButton, SIGNAL(clicked()), mField, SLOT(stopGenerations()));
	connect(mStepButton, SIGNAL(clicked()), mField, SLOT(nextGeneration()));
	connect(mClearButton, SIGNAL(clicked()), mField, SLOT(stopGenerations()));
	connect(mClearButton, SIGNAL(clicked()), mField, SLOT(clear()));
	connect(mStartButton, SIGNAL(clicked()), this, SLOT(toggleButtons()));
	connect(mStopButton, SIGNAL(clicked()), this, SLOT(toggleButtons()));
  
	connect(mSlowButton, SIGNAL(clicked()), mField, SLOT(setSlow()));
	connect(mNormalButton, SIGNAL(clicked()), mField, SLOT(setNormal()));
	connect(mFastButton, SIGNAL(clicked()), mField, SLOT(setFast()));
  
	QHBoxLayout* buttonLayout = new QHBoxLayout;
	buttonLayout->addWidget(mStartButton);
	buttonLayout->addWidget(mStepButton);
	buttonLayout->addWidget(mStopButton);
	buttonLayout->addWidget(mClearButton);

	QGroupBox* speedBox = new QGroupBox(tr("Simulation Speed"));
	QHBoxLayout* speedLayout = new QHBoxLayout;
	speedLayout->addWidget(mSlowButton);
	speedLayout->addWidget(mNormalButton);
	speedLayout->addWidget(mFastButton);
	speedBox->setLayout(speedLayout);

	QFrame* lifeBox = new QFrame;
	QVBoxLayout* fieldLayout = new QVBoxLayout;
	fieldLayout->addWidget(mField);
	lifeBox->setLayout(fieldLayout);
  
	QVBoxLayout* mainLayout = new QVBoxLayout;
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
	mStartButton->setEnabled((mStartButton->isEnabled() ? false : true));
	mStopButton->setEnabled((mStopButton->isEnabled() ? false : true));
	mStepButton->setEnabled((mStepButton->isEnabled() ? false : true));
	mClearButton->setEnabled((mClearButton->isEnabled() ? false : true));
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
	return mField->operator()(x, y);
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
	return mField->operator()(x, y);
}
