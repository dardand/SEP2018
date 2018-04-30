//------------------------------------------------------------------------------
// Buildable.cpp
//
// Group: Group 18762, study assistant: Philip Loibl
//
// Authors: Stefan Schnutt (11708769)
// Dardan Dermaku (01637087)
// Ermal Gashi (01635065)
//------------------------------------------------------------------------------
//

#include "Buildable.h"

using Sep::Field;
using Sep::Buildable;



// MARK: - Life cycle methods

//------------------------------------------------------------------------------
Buildable::Buildable(const Buildable::FieldType type, const int width,
                     const int heigth)
                      : Field(Field::FieldType(type), width, heigth)
{
}

//------------------------------------------------------------------------------
Buildable::Buildable(const Buildable &buildable) : Field(buildable)
{
}

//------------------------------------------------------------------------------
Buildable Buildable::operator = (const Buildable &buildable)
{
  Field::operator=(buildable);
  return *this;
}

//------------------------------------------------------------------------------
Buildable::~Buildable()
{
}



// MARK: - Getter methods

//------------------------------------------------------------------------------
const int Buildable::getBuildCost()
{
  switch (getType())
  {
    case Buildable::FieldType::WATER:
    case Buildable::FieldType::OBSTACLE:
      return 10;
    case Buildable::FieldType::STREET:
      return 20;
    case Buildable::FieldType::HOME:
      return 100 * getSize();
    case Buildable::FieldType::MARKET:
      return 150 * getSize();
    case Buildable::FieldType::CLINIC:
      return 200 * getSize();
    default:
      return 0;
  }
}
