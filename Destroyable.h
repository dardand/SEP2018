//------------------------------------------------------------------------------
// Destroyable.h
//
// Group: Group 18762, study assistant: Philip Loibl
//
// Authors: Stefan Schnutt (11708769)
// Dardan Dermaku (01637087)
// Ermal Gashi (01635065)
//------------------------------------------------------------------------------
//

#ifndef DESTROYABLE_H
#define DESTROYABLE_H

#include "Buildable.h"

namespace Sep
{
  //----------------------------------------------------------------------------
  /// The Destroyable class represents a destroyable field on the board of the
  /// game. The destroyable can represent obstacles, streets, homes, markets or
  /// clinics.
  //
  class Destroyable : public Buildable
  {
    public:
    
      //------------------------------------------------------------------------
      /// Represents a destroyable field type.
      //
      enum FieldType
      {
        OBSTACLE = 'O',
        STREET ='S',
        HOME = 'H',
        MARKET = 'M',
        CLINIC = 'C'
      };
    
      //------------------------------------------------------------------------
      /// Creates a new Destroyable instance with a specified field type.
      ///
      /// @param type The field type of the new Destroyable instance.
      /// @param width The width of the new Destroyable instance.
      /// @param height The height of the new Destroyable instance.
      //
      Destroyable(const Destroyable::FieldType type, const int width,
                  const int height);
    
      //------------------------------------------------------------------------
      /// Creates a new Destroyable instance by copying the attributes of a
      /// specified Destroyable instance to the newly initialized object.
      ///
      /// @param destroyable The Destroyable instance to be copied.
      //
      Destroyable(const Destroyable &destroyable);
    
      //------------------------------------------------------------------------
      /// Assigns the attributes of a specified Destroyable instance to an
      /// already existing object.
      ///
      /// @param destroyable The Destroyable instance to be copied.
      //
      Destroyable operator = (const Destroyable &destroyable);
    
      //------------------------------------------------------------------------
      /// Frees resources that the Destroyable instance may have acquired during
      /// its lifetime. Called when the object is being deallocated.
      //
      ~Destroyable();
    
      //------------------------------------------------------------------------
      /// Returns the destruction cost of the destroyable.
      //
      const int getDestroyCost();
  };
}

#endif // DESTROYABLE_H
