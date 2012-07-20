// Life_field.cpp

#include "Life_field.h"

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

void LifeField::setPoint(int i, int j, bool state)
{
  if(i < 1 || i > maxi || j < 1 || j > maxj)
    return;
  cell[current][i][j] = state;
  repaint(index2pos(i), index2pos(j), SCALE, SCALE);
}
 
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

void LifeField::startGenerations()
{
  if(!genTimer->isActive())
    genTimer->start(speed);
  return;
}

void LifeField::stopGenerations()
{
  genTimer->stop();
  return;
}

void LifeField::setFast()
{
  speed = FAST;
  genTimer->setInterval(speed);
  return;
}

void LifeField::setNormal()
{
  speed = NORMAL;
  genTimer->setInterval(speed);
  return;
}

void LifeField::setSlow()
{
  speed = SLOW;
  genTimer->setInterval(speed);
  return;
}

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

void LifeField::resizeEvent(QResizeEvent *e)
{
    return;
}

void LifeField::mousePressEvent(QMouseEvent *e)
{
  if(e->button() == Qt::LeftButton)
    mouseHandle(e->pos(), true);
  if(e->button() == Qt::RightButton)
    mouseHandle(e->pos(), false);
  return;
}

void LifeField::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons() == Qt::LeftButton)
      mouseHandle(e->pos(), true);
    if(e->buttons() == Qt::RightButton)
      mouseHandle(e->pos(), false);
  return;
}

void LifeField::mouseHandle(const QPoint &pos, bool state)
{
  int i = pos2index(pos.x());
  int j = pos2index(pos.y());
  setPoint(i, j, state);
}

int LifeField::pos2index(int x)
{
  return (x - BORDER) / SCALE + 1;
}

int LifeField::index2pos(int x)
{
  return (x - 1) * SCALE + BORDER;
}

bool& LifeField::operator()(int x, int y)
{
  return cell[current][x][y];
}

const bool& LifeField::operator()(const int x, const int y) const
{
  return cell[current][x][y];
}

