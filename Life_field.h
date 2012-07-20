// Life_field.h


#ifndef __LIFE_FIELD_H__
#define __LIFE_FIELD_H__


#include <QApplication>
#include <QtGui>

class LifeField : public QWidget
{
  Q_OBJECT
  
  public:
    LifeField(QWidget *parent = 0);
    void setPoint(int i, int j, bool state);
    
  public slots:
    void nextGeneration();
    void clear();
    void startGenerations();
    void stopGenerations();
    void setFast();
    void setNormal();
    void setSlow();
    
  protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    virtual void resizeEvent(QResizeEvent *e);
    void mouseHandle(const QPoint &pos, bool state);
    
  private:
    enum {MAXSIZE = 50, MINSIZE = 10, BORDER = 5};
    enum {SLOW = 350, NORMAL = 150, FAST = 50};
    
    bool cell[2][MAXSIZE + 2][MAXSIZE + 2];
    int current;
    int maxi, maxj;
    int SCALE;
    int pos2index(int x);
    int index2pos(int x);
    int speed;
    QTimer *genTimer;
    
};
    
#endif
