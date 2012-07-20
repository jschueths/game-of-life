//////////////////////////////////////////////////////////////////////
/// @file Life_field.cpp
/// @author jschueths
/// @brief This is the implementation of the LifeField class.
//////////////////////////////////////////////////////////////////////

#include "Life_field.h"

//////////////////////////////////////////////////////////////////////
/// @fn LifeField::LifeField(QWidget *parent)
/// @brief Constructor for the LifeField class
/// @pre none
/// @post A LifeField object is created.
//////////////////////////////////////////////////////////////////////
LifeField::LifeField(QWidget *parent) : QWidget(parent)
{
  SCALE = 10;
  maxi = MAXSIZE;
  maxj = MAXSIZE;
  current = 0;
  speed = NORMAL;
  
  setMinimumSize(MINSIZE * SCALE + 2 * BORDER, MINSIZE * SCALE + 2 * BORDER);
  setMaximumSize(MAXSIZE * SCALE + 2 * BORDER, MAXSIZE * SCALE + 2 * BORDER);
  setSizeIncrement(SCALE, SCALE);
  
  genTimer = new QTimer(this);
  connect(genTimer, SIGNAL(timeout()), this, SLOT(nextGeneration()));
  
  clear();
  resize(MAXSIZE * SCALE + 2 * BORDER, MAXSIZE * SCALE + 2 * BORDER);
  repaint();
}

//////////////////////////////////////////////////////////////////////
/// @fn void LifeField::setPoint(int i, int j, bool state)
/// @brief Mutator to the LifeField member.
/// @pre 'i' and 'j' must be greater than 0 and less than 52.
/// @post The boolean at (i, j) is set to state.
/// @param i The x-coordinate
/// @param j The y-coordinate
/// @param state The boolean state to change the cell
//////////////////////////////////////////////////////////////////////
void LifeField::setPoint(int i, int j, bool state)
{
  if(i < 1 || i > maxi || j < 1 || j > maxj)
    return;
  cell[current][i][j] = state;
  repaint(index2pos(i), index2pos(j), SCALE, SCALE);
}

//////////////////////////////////////////////////////////////////////
/// @fn void LifeField::nextGeneration()
/// @brief Generates the next generation of cells following 
/// Conway's four rules.
/// @pre none
/// @post The next set of cells is set.
//////////////////////////////////////////////////////////////////////
void LifeField::nextGeneration()
{
  for(int i = 1; i <= MAXSIZE; i++)
  {
    for(int j = 1; j <= MAXSIZE; j++)
    {
      int t = cell[current][i - 1][j - 1]
      + cell[current][i - 1][j]
      + cell[current][i - 1][j + 1]
      + cell[current][i][j - 1]
      + cell[current][i][j + 1]
      + cell[current][i + 1][j - 1]
      + cell[current][i + 1][j]
      + cell[current][i + 1][j + 1];
      
      cell[!current][i][j] = (t == 3 || (t == 2 && cell[current][i][j]));
    }
  }
  current = !current;
  repaint();
  return;
}

//////////////////////////////////////////////////////////////////////
/// @fn void LifeField::startGenerations()
/// @brief Starts a repeating timer to refresh the next generation.
/// @pre none
/// @post genTimer is started with a delay of speed.
//////////////////////////////////////////////////////////////////////
void LifeField::startGenerations()
{
  if(!genTimer->isActive())
    genTimer->start(speed);
  return;
}

//////////////////////////////////////////////////////////////////////
/// @fn void LifeField::stopGenerations();
/// @brief Stops the repeating timer from refreshing the next
/// generation.
/// @pre none
/// @post genTimer is stopped
//////////////////////////////////////////////////////////////////////
void LifeField::stopGenerations()
{
  genTimer->stop();
  return;
}

//////////////////////////////////////////////////////////////////////
/// @fn void LifeField::setFast()
/// @brief Changes the simulation speed to the FAST setting.
/// @pre none
/// @post The speed and timer interval are set to FAST.
//////////////////////////////////////////////////////////////////////
void LifeField::setFast()
{
  speed = FAST;
  genTimer->setInterval(speed);
  return;
}

//////////////////////////////////////////////////////////////////////
/// @fn void LifeField::setNormal()
/// @brief Changes the simulation speed to the NORMAL setting.
/// @pre none
/// @post The speed and timer interval are set to NORMAL.
//////////////////////////////////////////////////////////////////////
void LifeField::setNormal()
{
  speed = NORMAL;
  genTimer->setInterval(speed);
  return;
}

//////////////////////////////////////////////////////////////////////
/// @fn void LifeField::setSlow()
/// @brief Changes the simulation speed to the SLOW setting.
/// @pre none
/// @post The speed and timer interval are set to SLOW.
//////////////////////////////////////////////////////////////////////
void LifeField::setSlow()
{
  speed = SLOW;
  genTimer->setInterval(speed);
  return;
}

//////////////////////////////////////////////////////////////////////
/// @fn void LifeField::clear()
/// @brief Wipes the cells.
/// @pre none
/// @post All the boolean cells are set to false.
//////////////////////////////////////////////////////////////////////
void LifeField::clear()
{
  current = 0;
  for(int t = 0; t < 2; t++)
  {
    for(int i = 0; i < MAXSIZE + 2; i++)
    {
      for(int j = 0; j < MAXSIZE + 2; j++)
        cell[t][i][j] = false;
    }
  }
  
  repaint();
  return;
}

//////////////////////////////////////////////////////////////////////
/// @fn void LifeField::paintEvent(QPaintEvent *e)
/// @brief Called everytime the screen needs to be repainted.
/// @pre none
/// @post The LifeField on screen is refreshed.
/// @param e The QPaintEvent that was system generated.
//////////////////////////////////////////////////////////////////////
void LifeField::paintEvent(QPaintEvent *e)
{
  int starti = pos2index(e->rect().left());
  int stopi = pos2index(e->rect().right());
  int startj = pos2index(e->rect().top());
  int stopj = pos2index(e->rect().bottom());
  
  stopi = (stopi > maxi) ? maxi : stopi;
  stopj = (stopj > maxj) ? maxj : stopj;
  
  QPainter paint(this);
  paint.setPen(Qt::NoPen);

  for(int i = starti; i <= stopi; i++)
  {
    for(int j = startj; j <= stopj; j++)
    {
      if(cell[current][i][j])
        paint.setBrush(Qt::green);
      else
        paint.setBrush(Qt::black);
      paint.drawRect(index2pos(i), index2pos(j), SCALE - 1, SCALE - 1);
    }
  }
  return;
}

//////////////////////////////////////////////////////////////////////
/// @fn void LifeField::resizeEvent(QResizeEvent *e)
/// @brief Stubbed out for compilation. Nonfunctional for now.
/// @pre none
/// @post none
/// @param e The QResizeEvent
//////////////////////////////////////////////////////////////////////
void LifeField::resizeEvent(QResizeEvent *e)
{
  return;
}

//////////////////////////////////////////////////////////////////////
/// @fn void LifeField::mousePressEvent(QMouseEvent *e)
/// @brief Catches where the mouse was pressed and which mouse
/// button was pressed.
/// @pre none
/// @post A call to mouseHandle() is made.
/// @param e The QMouseEvent that was captured.
//////////////////////////////////////////////////////////////////////
void LifeField::mousePressEvent(QMouseEvent *e)
{
  if(e->button() == Qt::LeftButton)
    mouseHandle(e->pos(), true);
  if(e->button() == Qt::RightButton)
    mouseHandle(e->pos(), false);
  return;
}

//////////////////////////////////////////////////////////////////////
/// @fn void LifeField::mouseMoveEvent(QMouseEvent *e)
/// @brief Catches where the mouse was moved while a mouse
/// button was pressed.
/// @pre none
/// @post A call to mouseHandle() is made.
/// @param e The QMouseEvent that was captured.
//////////////////////////////////////////////////////////////////////
void LifeField::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons() == Qt::LeftButton)
      mouseHandle(e->pos(), true);
    if(e->buttons() == Qt::RightButton)
      mouseHandle(e->pos(), false);
  return;
}

//////////////////////////////////////////////////////////////////////
/// @fn void LifeField::mouseHandle(const QPoint &pos, bool state)
/// @brief Converts the mouse position to a cell and passes it
/// on to setPoint().
/// @pre none
/// @post A call to setPoint() is made.
/// @param pos The QPoint that the mouse is on.
/// @param state The boolean state to change the cell to.
//////////////////////////////////////////////////////////////////////
void LifeField::mouseHandle(const QPoint &pos, bool state)
{
  int i = pos2index(pos.x());
  int j = pos2index(pos.y());
  setPoint(i, j, state);
}

//////////////////////////////////////////////////////////////////////
/// @fn int LifeField::pos2index(int x)
/// @brief Converts a screen position to an index position.
/// @pre x is on the screen
/// @post The screen position is converted to an index position.
/// @param x The coordinate of the position.
//////////////////////////////////////////////////////////////////////
int LifeField::pos2index(int x)
{
  return (x - BORDER) / SCALE + 1;
}

//////////////////////////////////////////////////////////////////////
/// @fn int LifeField::index2pos(int x)
/// @brief Converts an index position to a screen position.
/// @pre x must be with the cell grid.
/// @post The index position is converted to a screen position.
/// @param x The index coordinate.
//////////////////////////////////////////////////////////////////////
int LifeField::index2pos(int x)
{
  return (x - 1) * SCALE + BORDER;
}

//////////////////////////////////////////////////////////////////////
/// @fn bool& LifeField::operator()(int x, int y)
/// @brief Mutator to the boolean cells.
/// @pre 'x' and 'y' must be greater than 0 and less than 52.
/// @post A reference to the boolean is returned.
/// @param x The x-coordinate
/// @param y The y-coordinate
//////////////////////////////////////////////////////////////////////
bool& LifeField::operator()(int x, int y)
{
  return cell[current][x][y];
}

//////////////////////////////////////////////////////////////////////
/// @fn const bool& LifeField::operator()(int x, int y) const
/// @brief Accessor to the boolean cells.
/// @pre 'x' and 'y' must be greater than 0 and less than 52.
/// @post A const reference to the boolean is returned.
/// @param x The x-coordinate
/// @param y The y-coordinate
//////////////////////////////////////////////////////////////////////
const bool& LifeField::operator()(const int x, const int y) const
{
  return cell[current][x][y];
}

