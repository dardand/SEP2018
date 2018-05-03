//------------------------------------------------------------------------------
// Point.m
//
// Group: Group 18762, study assistant: Philip Loibl
//
// Authors: Stefan Schnutt (11708769)
// Dardan Dermaku (01637087)
// Ermal Gashi (01635065)
//------------------------------------------------------------------------------
//

#include "Point.h"

using Sep::Point;



// MARK: - Life cycle methods

//------------------------------------------------------------------------------
Point::Point() : Point(0, 0)
{
}

//------------------------------------------------------------------------------
Point::Point(const int x, const int y) : x_(x), y_(y)
{
}

//------------------------------------------------------------------------------
Point::Point(const Point &point)  : x_(point.x_), y_(point.y_)
{
}

//------------------------------------------------------------------------------
Point Point::operator = (const Point &point)
{
  x_ = point.x_;
  y_ = point.y_;
  return *this;
}

//------------------------------------------------------------------------------
Point::~Point()
{
}


//------------------------------------------------------------------------------
int Point::getX()
{
  return x_;
}

//------------------------------------------------------------------------------
int Point::getY()
{
  return y_;
}

// MARK: - Setter methods

//------------------------------------------------------------------------------
void Point::setX(const int x)
{
  x_ = x;
}

//------------------------------------------------------------------------------
void Point::setY(const int y)
{
  y_ = y;
}
