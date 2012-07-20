//////////////////////////////////////////////////////////////////////
/// @file main.cpp
/// @author jschueths
/// @brief This is the basic Qt main file to begin the Qt app.
//////////////////////////////////////////////////////////////////////

#include <QApplication>
#include "Life_window.h"

//////////////////////////////////////////////////////////////////////
/// @fn int main(int argc, char *argv[])
/// @brief Main function for the Game of Life. Creates an instance 
/// of the LifeWindow class and displays it on screen.
/// @pre none
/// @post The program runs and then exits.
/// @param argc The number of command line arguments passed in.
/// @param argv An array of chars holding the command line arguments.
//////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  LifeWindow mainWindow;
  mainWindow.show();
  return app.exec();
}
