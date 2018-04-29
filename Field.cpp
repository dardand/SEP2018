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
Field::Field()
{
  type_ = GRASS;
}

//------------------------------------------------------------------------------
Field::Field(const FieldType type)
{
  type_ = type;
}

//------------------------------------------------------------------------------
Field::Field(const Field &field)
{
  type_ = field.type_;
}

//------------------------------------------------------------------------------
Field Field::operator = (const Field &field)
{
  type_ = field.type_;
  return *this;
}

//------------------------------------------------------------------------------
Field::~Field()
{
}



// MARK: - Getter methods

//------------------------------------------------------------------------------
string Field::getName(const FieldType type)
{
  switch (type)
  {
    case GRASS:
      return "Grass";
    case WATER:
      return "Water";
    case OBSTACLE:
      return "Obstacle";
    case STREET:
      return "Street";
    case HOME:
      return "Home";
    case MARKET:
      return "Market";
    case CLINIC:
      return "Clinic";
    case TOWNHALL:
      return "Town Hall";
    default:
      return "Unknown";
  }
}

//------------------------------------------------------------------------------
Field::FieldType Field::getType()
{
  return type_;
}
