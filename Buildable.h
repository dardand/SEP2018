//------------------------------------------------------------------------------
// Buildable.h
//
// Group: Group 18762, study assistant: Philip Loibl
//
// Authors: Stefan Schnutt (11708769)
// Dardan Dermaku (01637087)
// Ermal Gashi (01635065)
//------------------------------------------------------------------------------
//

#ifndef BUILDABLE_H
#define BUILDABLE_H

#include <stdio.h>
#include "Field.h"

namespace Sep
{
  //----------------------------------------------------------------------------
  /// The Buildable class represents a buildable field on the board of the game.
  /// The buildable can represent water, obstacles, streets, homes, markets or
  /// clinics.
  //
  class Buildable : public Field
  {
    public:
    
      //------------------------------------------------------------------------
      /// Represents a buildable field type.
      //
      enum FieldType
      {
        WATER = 'W',
        OBSTACLE = 'O',
        STREET ='S',
        HOME = 'H',
        MARKET = 'M',
        CLINIC = 'C'
      };
    
      //------------------------------------------------------------------------
      /// Creates a new Buildable instance with a specified field type.
      ///
      /// @param type The field type of the new Buildable instance.
      /// @param width The width of the new Buildable instance.
      /// @param height The height of the new Buildable instance.
      //
      Buildable(const Buildable::FieldType type, const int width,
                const int height);
    
      //------------------------------------------------------------------------
      /// Creates a new Buildable instance by copying the attributes of a
      /// specified Buildable instance to the newly initialized object.
      ///
      /// @param buildable The Buildable instance to be copied.
      //
      Buildable(const Buildable &buildable);
    
      //------------------------------------------------------------------------
      /// Assigns the attributes of a specified Buildable instance to an already
      /// existing object.
      ///
      /// @param buildable The Buildable instance to be copied.
      //
      Buildable operator = (const Buildable &buildable);
    
      //------------------------------------------------------------------------
      /// Frees resources that the Buildable instance may have acquired during
      /// its lifetime. Called when the object is being deallocated.
      //
      ~Buildable();
    
      //------------------------------------------------------------------------
      /// Returns the construction cost of the buildable.
      //
      const int getBuildCost();
  };
}

#endif // BUILDABLE_H
