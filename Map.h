//------------------------------------------------------------------------------
// Map.h
//
// Group: Group 18762, study assistant: Philip Loibl
//
// Authors: Stefan Schnutt (11708769)
// Dardan Dermaku (01637087)
// Ermal Gashi (01635065)
//------------------------------------------------------------------------------
//

#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <vector>
#include "Interface.h"
#include "Field.h"

using std::string;
using std::vector;
using Sep::Interface;

namespace Sep
{
  class Point;
  //----------------------------------------------------------------------------
  /// A Map object is a representation of the current playing field managed by a
  /// Game object.
  //
  class Map
  {
    public:
    
      //------------------------------------------------------------------------
      /// Creates a new Map instance.
      //
      Map();
    
      //------------------------------------------------------------------------
      /// Creates a new Map instance from a specified string representing the
      /// field map by concatenating the rows.
      ///
      /// @param flat_map The string reprentation of field types from whom to
      ///                 to generate the new Map instance. Each field type is
      ///                 represented by a specific character (e.g. G for Grass,
      ///                 etc). For more details see FieldType definition.
      ///                 Each map consists of a specific number of columns with
      ///                 a specific number of rows. In the string
      ///                 representation of the field types all rows of
      ///                 characters are concatenated.
      /// @param concatenations The number concatenated rows.
      //
      Map(const string flat_map, const int concatenations);
    
      //------------------------------------------------------------------------
      /// Creates a new Map instance by copying the attributes of a specified
      /// Map instance to the newly initialized object.
      ///
      /// @param map The Map instance to be copied.
      //
      Map(const Map &map);
    
      //------------------------------------------------------------------------
      /// Assigns the attributes of a specified Map instance to an already
      /// existing object.
      ///
      /// @param map The Map instance to be copied.
      //
      Map operator = (const Map &map);
    
      //------------------------------------------------------------------------
      /// Frees resources that the Map instance may have acquired during its
      /// lifetime. Called when the object is being deallocated.
      //
      ~Map();
    
      //------------------------------------------------------------------------
      /// Returns a pointer to a field at a specified position on the map. If
      /// the position is outside the bounds of the map, the pointer will be
      /// NULL.
      ///
      /// @param x The horizontal position of the Field.
      /// @param y The vertical position of the Field.
      ///
      /// @return Field * The pointer to a field instance.
      //
      Field *getField(const int x, const int y);
    
      //------------------------------------------------------------------------
      /// Returns a pointer to the origin point for a specified field on the
      /// map. If the field is not found on the map, the pointer will be NULL.
      ///
      /// @param field The reference to the field whose origi to return.
      ///
      /// @return Point * The pointer to the origin point. Has to be freed
      ///                 manually.
      //
      Point *getOrigin(Field &field);
    
      //------------------------------------------------------------------------
      /// Sets a specified field at a given position.
      ///
      /// @param field The field to set.
      /// @param x The horizontal position to set the field.
      /// @param y The vertical position to set the field.
      //
      void setField(Field &field, const int x, const int y);
    
      //------------------------------------------------------------------------
      /// Prints the map on a specified interface.
      ///
      /// @param io The interface where to print the map.
      //
      void print(const Interface &io);
    
    private:
    
      //------------------------------------------------------------------------
      /// The number of horizontally arranged fields.
      //
      int width_;
    
      //------------------------------------------------------------------------
      /// The number of vertically arranged fields.
      //
      int height_;
    
      //------------------------------------------------------------------------
      /// A two dimensional vector representing the map with a specified number
      /// of columns defined by the map's width. Each column is represented as
      /// as field vector with a specified number of fields defined by the map's
      /// height.
      //
      vector<vector<Field *>> fields_;
  };
}

#endif // MAP_H
