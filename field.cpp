//////////////////////////////////////////////////////////////////////
/// @file field.cpp
/// @author jschueths
/// @brief This is the implementation of the Field class.
//////////////////////////////////////////////////////////////////////

#include "field.h"

//////////////////////////////////////////////////////////////////////
/// @fn Field::Field(QWidget *parent)
/// @brief Constructor for the Field class
/// @pre none
/// @post A Field object is created.
//////////////////////////////////////////////////////////////////////
Field::Field(QWidget* parent) : QWidget(parent) {
	mSCALE = 10;
	mMaxI = MAXSIZE;
	mMaxJ = MAXSIZE;
	mCurrent = 0;
	mSpeed = NORMAL;

	setMinimumSize(MINSIZE * mSCALE + 2 * BORDER, MINSIZE * mSCALE + 2 * BORDER);
	setMaximumSize(MAXSIZE * mSCALE + 2 * BORDER, MAXSIZE * mSCALE + 2 * BORDER);
	setSizeIncrement(mSCALE, mSCALE);

	mGenTimer = new QTimer(this);
	connect(mGenTimer, SIGNAL(timeout()), this, SLOT(nextGeneration()));

	clear();
	resize(MAXSIZE * mSCALE + 2 * BORDER, MAXSIZE * mSCALE + 2 * BORDER);
	repaint();
}

//////////////////////////////////////////////////////////////////////
/// @fn void Field::setPoint(int i, int j, bool state)
/// @brief Mutator to the Field member.
/// @pre 'i' and 'j' must be greater than 0 and less than 52.
/// @post The boolean at (i, j) is set to state.
/// @param i The x-coordinate
/// @param j The y-coordinate
/// @param state The boolean state to change the cell
//////////////////////////////////////////////////////////////////////
void Field::setPoint(int i, int j, bool state) {
	if(i < 1 || i > mMaxI || j < 1 || j > mMaxJ) {
		return;
	}
	mCell[mCurrent][i][j] = state;
	repaint(index2pos(i), index2pos(j), mSCALE, mSCALE);
}

//////////////////////////////////////////////////////////////////////
/// @fn void Field::nextGeneration()
/// @brief Generates the next generation of cells following 
/// Conway's four rules.
/// @pre none
/// @post The next set of cells is set.
//////////////////////////////////////////////////////////////////////
void Field::nextGeneration() {
	for(int i = 1; i <= MAXSIZE; i++) {
		for(int j = 1; j <= MAXSIZE; j++) {
			  int t = mCell[mCurrent][i - 1][j - 1]
			  + mCell[mCurrent][i - 1][j]
			  + mCell[mCurrent][i - 1][j + 1]
			  + mCell[mCurrent][i][j - 1]
			  + mCell[mCurrent][i][j + 1]
			  + mCell[mCurrent][i + 1][j - 1]
			  + mCell[mCurrent][i + 1][j]
			  + mCell[mCurrent][i + 1][j + 1];

			  mCell[!mCurrent][i][j] = (t == 3 || (t == 2 && mCell[mCurrent][i][j]));
		}
	}
	mCurrent = !mCurrent;
	repaint();
}

//////////////////////////////////////////////////////////////////////
/// @fn void Field::startGenerations()
/// @brief Starts a repeating timer to refresh the next generation.
/// @pre none
/// @post genTimer is started with a delay of speed.
//////////////////////////////////////////////////////////////////////
void Field::startGenerations() {
	if(!mGenTimer->isActive()) {
		mGenTimer->start(mSpeed);
	}
}

//////////////////////////////////////////////////////////////////////
/// @fn void Field::stopGenerations();
/// @brief Stops the repeating timer from refreshing the next
/// generation.
/// @pre none
/// @post genTimer is stopped
//////////////////////////////////////////////////////////////////////
void Field::stopGenerations() {
	mGenTimer->stop();
}

//////////////////////////////////////////////////////////////////////
/// @fn void Field::setFast()
/// @brief Changes the simulation speed to the FAST setting.
/// @pre none
/// @post The speed and timer interval are set to FAST.
//////////////////////////////////////////////////////////////////////
void Field::setFast() {
	mSpeed = FAST;
	mGenTimer->setInterval(mSpeed);
}

//////////////////////////////////////////////////////////////////////
/// @fn void Field::setNormal()
/// @brief Changes the simulation speed to the NORMAL setting.
/// @pre none
/// @post The speed and timer interval are set to NORMAL.
//////////////////////////////////////////////////////////////////////
void Field::setNormal() {
	mSpeed = NORMAL;
	mGenTimer->setInterval(mSpeed);
}

//////////////////////////////////////////////////////////////////////
/// @fn void Field::setSlow()
/// @brief Changes the simulation speed to the SLOW setting.
/// @pre none
/// @post The speed and timer interval are set to SLOW.
//////////////////////////////////////////////////////////////////////
void Field::setSlow() {
	mSpeed = SLOW;
	mGenTimer->setInterval(mSpeed);
}

//////////////////////////////////////////////////////////////////////
/// @fn void Field::clear()
/// @brief Wipes the cells.
/// @pre none
/// @post All the boolean cells are set to false.
//////////////////////////////////////////////////////////////////////
void Field::clear() {
	mCurrent = 0;
	for(int t = 0; t < 2; t++) {
		for(int i = 0; i < MAXSIZE + 2; i++) {
			for(int j = 0; j < MAXSIZE + 2; j++) {
				mCell[t][i][j] = false;
			}
		}
	}
	repaint();
}

//////////////////////////////////////////////////////////////////////
/// @fn void Field::paintEvent(QPaintEvent *e)
/// @brief Called everytime the screen needs to be repainted.
/// @pre none
/// @post The Field on screen is refreshed.
/// @param e The QPaintEvent that was system generated.
//////////////////////////////////////////////////////////////////////
void Field::paintEvent(QPaintEvent* e) {
	int starti = pos2index(e->rect().left());
	int stopi = pos2index(e->rect().right());
	int startj = pos2index(e->rect().top());
	int stopj = pos2index(e->rect().bottom());

	stopi = (stopi > mMaxI) ? mMaxI : stopi;
	stopj = (stopj > mMaxJ) ? mMaxJ : stopj;

	QPainter paint(this);
	paint.setPen(Qt::NoPen);

	for(int i = starti; i <= stopi; i++) {
		for(int j = startj; j <= stopj; j++) {
			if(mCell[mCurrent][i][j]) {
				paint.setBrush(Qt::green);
			} else {
				paint.setBrush(Qt::black);
			}
			paint.drawRect(index2pos(i), index2pos(j), mSCALE - 1, mSCALE - 1);
		}
	}
}

//////////////////////////////////////////////////////////////////////
/// @fn void Field::resizeEvent(QResizeEvent *e)
/// @brief Stubbed out for compilation. Nonfunctional for now.
/// @pre none
/// @post none
/// @param e The QResizeEvent
//////////////////////////////////////////////////////////////////////
void Field::resizeEvent(QResizeEvent* e) {
}

//////////////////////////////////////////////////////////////////////
/// @fn void Field::mousePressEvent(QMouseEvent *e)
/// @brief Catches where the mouse was pressed and which mouse
/// button was pressed.
/// @pre none
/// @post A call to mouseHandle() is made.
/// @param e The QMouseEvent that was captured.
//////////////////////////////////////////////////////////////////////
void Field::mousePressEvent(QMouseEvent* e) {
	if(e->button() == Qt::LeftButton) {
		mouseHandle(e->pos(), true);
	}
	if(e->button() == Qt::RightButton) {
		mouseHandle(e->pos(), false);
	}
}

//////////////////////////////////////////////////////////////////////
/// @fn void Field::mouseMoveEvent(QMouseEvent *e)
/// @brief Catches where the mouse was moved while a mouse
/// button was pressed.
/// @pre none
/// @post A call to mouseHandle() is made.
/// @param e The QMouseEvent that was captured.
//////////////////////////////////////////////////////////////////////
void Field::mouseMoveEvent(QMouseEvent* e) {
	if(e->buttons() == Qt::LeftButton) {
		mouseHandle(e->pos(), true);
	}
	if(e->buttons() == Qt::RightButton) {
		mouseHandle(e->pos(), false);
	}
}

//////////////////////////////////////////////////////////////////////
/// @fn void Field::mouseHandle(const QPoint &pos, bool state)
/// @brief Converts the mouse position to a cell and passes it
/// on to setPoint().
/// @pre none
/// @post A call to setPoint() is made.
/// @param pos The QPoint that the mouse is on.
/// @param state The boolean state to change the cell to.
//////////////////////////////////////////////////////////////////////
void Field::mouseHandle(const QPoint &pos, bool state) {
	int i = pos2index(pos.x());
	int j = pos2index(pos.y());
	setPoint(i, j, state);
}

//////////////////////////////////////////////////////////////////////
/// @fn int Field::pos2index(int x)
/// @brief Converts a screen position to an index position.
/// @pre x is on the screen
/// @post The screen position is converted to an index position.
/// @param x The coordinate of the position.
//////////////////////////////////////////////////////////////////////
int Field::pos2index(int x) {
	return (x - BORDER) / mSCALE + 1;
}

//////////////////////////////////////////////////////////////////////
/// @fn int Field::index2pos(int x)
/// @brief Converts an index position to a screen position.
/// @pre x must be with the cell grid.
/// @post The index position is converted to a screen position.
/// @param x The index coordinate.
//////////////////////////////////////////////////////////////////////
int Field::index2pos(int x) {
	return (x - 1) * mSCALE + BORDER;
}

//////////////////////////////////////////////////////////////////////
/// @fn bool& Field::operator()(int x, int y)
/// @brief Mutator to the boolean cells.
/// @pre 'x' and 'y' must be greater than 0 and less than 52.
/// @post A reference to the boolean is returned.
/// @param x The x-coordinate
/// @param y The y-coordinate
//////////////////////////////////////////////////////////////////////
bool& Field::operator()(int x, int y) {
	return mCell[mCurrent][x][y];
}

//////////////////////////////////////////////////////////////////////
/// @fn const bool& Field::operator()(int x, int y) const
/// @brief Accessor to the boolean cells.
/// @pre 'x' and 'y' must be greater than 0 and less than 52.
/// @post A const reference to the boolean is returned.
/// @param x The x-coordinate
/// @param y The y-coordinate
//////////////////////////////////////////////////////////////////////
const bool& Field::operator()(const int x, const int y) const {
	return mCell[mCurrent][x][y];
}
