//////////////////////////////////////////////////////////////////////
/// @file board.h
/// @author jschueths
/// @brief This is the class definition of the Board class.
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/// @class Board
/// @brief The Board class is a wrapper around the Field
/// class and the input controls to affect the Field. 
//////////////////////////////////////////////////////////////////////
#ifndef __BOARD_H__
#define __BOARD_H__

#include <QApplication>

#include "field.h"

class Board : public QWidget {
	Q_OBJECT
  
	public:
		Board(QWidget* parent = 0);
		bool& operator()(int x, int y);
		const bool& operator()(const int x, const int y) const;

	protected slots:
		void toggleButtons();
  
	private:
		Field* mField;           ///< Pointer to the Field object
		QPushButton* mStartButton;   ///< Pointer to the Start button
		QPushButton* mStopButton;    ///< Pointer to the Stop button
		QPushButton* mStepButton;    ///< Pointer to the Step button
		QPushButton* mClearButton;   ///< Pointer to the Clear button
		QRadioButton* mSlowButton;   ///< Pointer to the Slow radio button
		QRadioButton* mNormalButton; ///< Pointer to the Normal radio button
		QRadioButton* mFastButton;   ///< Pointer to the Fast radio button
};

#endif

