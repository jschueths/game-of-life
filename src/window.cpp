//////////////////////////////////////////////////////////////////////
/// @file window.cpp
/// @author jschueths
/// @brief This is the implementation of the Window class.
//////////////////////////////////////////////////////////////////////

#include <fstream>
#include <iostream>
#include <string>

#include <QtWidgets>

#include "window.hpp"


//////////////////////////////////////////////////////////////////////
/// @fn Window::Window(QWidget *parent)
/// @brief Constructor for the Window class.
/// @pre none
/// @post A new Window object is created.
//////////////////////////////////////////////////////////////////////
Window::Window(QWidget* parent) : QMainWindow(parent) {
	mBoard = new Board;

	mOpenAction = new QAction(tr("&Open"), this);
	mSaveAction = new QAction(tr("&Save"), this);
	mExitAction = new QAction(tr("E&xit"), this);

	connect(mOpenAction, &QAction::triggered, this, &Window::open);
	connect(mSaveAction, &QAction::triggered, this, &Window::save);
	connect(mExitAction, &QAction::triggered, qApp, &QApplication::quit);

	mFileMenu = menuBar()->addMenu(tr("&File"));
	mFileMenu->addAction(mOpenAction);
	mFileMenu->addAction(mSaveAction);
	mFileMenu->addSeparator();
	mFileMenu->addAction(mExitAction);

	setCentralWidget(mBoard);
	setWindowTitle(tr("Conway's Game of Life"));
}

//////////////////////////////////////////////////////////////////////
/// @fn void Window::open()
/// @brief Opens and reads in a file from disk.
/// @pre none
/// @post Sets the Field to the configuration that was stored
/// in the file.
//////////////////////////////////////////////////////////////////////
void Window::open() {
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Grid Files (*.grd)"));
	if(fileName != "") {
		QFile file(fileName);
		if(!file.open(QIODevice::ReadOnly)) {
			QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
			return;
		}

		// Read in and set the grid here.
		QTextStream stream(&file);
		for(int i = 0; i < 52; i++) {
			QString line;
			stream >> line;
			for(int j = 0; j < 52; j++) {
				mBoard->operator()(i,j) = line[j] == '1' ? true : false;
			}
		}
		file.close();
		repaint();
	}
}

//////////////////////////////////////////////////////////////////////
/// @fn void Window::save()
/// @brief Saves the current Field configuration to disk.
/// @pre none
/// @post A configuration file is saved to disk.
//////////////////////////////////////////////////////////////////////
void Window::save() {
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("Grid Files (*.grd)"));
	if(fileName != "") {
		QFile file(fileName);
		if(!file.open(QIODevice::WriteOnly)) {
			QMessageBox::critical(this, tr("Error"), tr("Could not save file"));
		} else {
			QTextStream stream(&file);
			// Write out the grid here.
			for(int i = 0; i < 52; i++) {
				for(int j = 0; j < 52; j++) {
					stream << mBoard->operator()(i, j);
				}
				stream << "\n";
			}
			stream.flush();
			file.close();
		}
	}
}
