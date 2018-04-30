//------------------------------------------------------------------------------
// Destroyable.cpp
//
// Group: Group 18762, study assistant: Philip Loibl
//
// Authors: Stefan Schnutt (11708769)
// Dardan Dermaku (01637087)
// Ermal Gashi (01635065)
//------------------------------------------------------------------------------
//

#include "Destroyable.h"

using Sep::Buildable;
using Sep::Destroyable;



// MARK: - Life cycle methods

//------------------------------------------------------------------------------
Destroyable::Destroyable(const Destroyable::FieldType type, const int width,
                         const int heigth)
                          : Buildable(Buildable::FieldType(type), width, heigth)
{
}

//------------------------------------------------------------------------------
Destroyable::Destroyable(const Destroyable &destroyable)
                          : Buildable(destroyable)
{
}

//------------------------------------------------------------------------------
Destroyable Destroyable::operator = (const Destroyable &destroyable)
{
  Buildable::operator=(destroyable);
  return *this;
}

//------------------------------------------------------------------------------
Destroyable::~Destroyable()
{
}



// MARK: - Getter methods

//------------------------------------------------------------------------------
const int Destroyable::getDestroyCost()
{
  switch (getType())
  {
    case Destroyable::FieldType::OBSTACLE:
      return 20;
    case Destroyable::FieldType::STREET:
      return 10;
    case Destroyable::FieldType::HOME:
    case Destroyable::FieldType::MARKET:
    case Destroyable::FieldType::CLINIC:
      return 100 * getSize();
    default:
      return 0;
  }
}
