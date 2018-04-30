//------------------------------------------------------------------------------
// Field.cpp
//
// Group: Group 18762, study assistant: Philip Loibl
//
// Authors: Stefan Schnutt (11708769)
// Dardan Dermaku (01637087)
// Ermal Gashi (01635065)
//------------------------------------------------------------------------------
//

#include "Field.h"

using Sep::Field;



// MARK: - Life cycle methods

//------------------------------------------------------------------------------
Field::Field() : Field(FieldType::GRASS, 1, 1)
{
}

//------------------------------------------------------------------------------
Field::Field(const FieldType type, const int width, const int heigth)
{
  type_ = type;
  width_ = width;
  height_ = heigth;
}

//------------------------------------------------------------------------------
Field::Field(const Field &field)
{
  type_ = field.type_;
  width_ = field.width_;
  height_ = field.height_;
}

//------------------------------------------------------------------------------
Field Field::operator = (const Field &field)
{
  type_ = field.type_;
  width_ = field.width_;
  height_ = field.height_;
  return *this;
}

//------------------------------------------------------------------------------
Field::~Field()
{
}



// MARK: - Getter methods

//------------------------------------------------------------------------------
const string Field::getName(const FieldType type)
{
  switch (type)
  {
    case FieldType::GRASS:
      return "Grass";
    case FieldType::WATER:
      return "Water";
    case FieldType::OBSTACLE:
      return "Obstacle";
    case FieldType::STREET:
      return "Street";
    case FieldType::HOME:
      return "Home";
    case FieldType::MARKET:
      return "Market";
    case FieldType::CLINIC:
      return "Clinic";
    case FieldType::TOWNHALL:
      return "Town Hall";
    default:
      return "Unknown";
  }
}

//------------------------------------------------------------------------------
const Field::FieldType Field::getType()
{
  return type_;
}

//------------------------------------------------------------------------------
const int Field::getWidth()
{
  return width_;
}

//------------------------------------------------------------------------------
const int Field::getHeight()
{
  return height_;
}

//------------------------------------------------------------------------------
const int Field::getSize()
{
  return width_ * height_;
}
