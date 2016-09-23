//////////////////////////////////////////////////////////////////////
/// @file window.h
/// @author jschueths
/// @brief This is the class definition of the Window class.
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/// @class Window
/// @brief The Window class provides a QMainWindow wrapper to
/// bring in FileMenu functionality in a nice layout. 
//////////////////////////////////////////////////////////////////////
#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <QApplication>
#include <QtWidgets>

#include "board.h"

class Window : public QMainWindow {
	Q_OBJECT

	public:
		Window(QWidget *parent = 0);

	private:
		Board* mBoard;     ///< A pointer to the Board object
		QMenu* mFileMenu;      ///< A pointer to a QMenu object
		QAction* mOpenAction;  ///< A pointer to the Open action
		QAction* mSaveAction;  ///< A pointer to the Save action
		QAction* mExitAction;  ///< A pointer to the Exit action

	private slots:
		void open();
		void save();
};

#endif
