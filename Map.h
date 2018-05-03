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

#include <vector>
#include "Field.h"

using std::string;
using std::vector;
using Sep::Field;
using FieldType = Sep::Field::FieldType;

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
      /// Creates a new Map instance with specified size. Each field in the
      /// newly instantiated map will be set to the specified type.
      ///
      /// @param width The number of columns.
      /// @param height The number of rows per column.
      /// @param type The type used to initialize the map's fields with. Default
      ///             type is GRASS.
      //
      Map(const int width, const int height,
          const FieldType type = FieldType::GRASS);
    
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
      /// Returns the field types of the map instance as two dimensional vector.
      ///
      /// @return vector<vector<FieldType>> The two dimensional field type
      ///                                   vector of the map.
      //
      vector<vector<FieldType>> getFieldTypes();
    
      //------------------------------------------------------------------------
      /// Sets a specified field at a given position.
      ///
      /// @param field The field to set.
      /// @param x The horizontal position to set the field.
      /// @param y The vertical position to set the field.
      ///
      /// @return bool A boolean value indicating whether the field was
      ///              successfully set at the specified position.
      //
      bool setField(Field &field, const int x, const int y);
    
      //------------------------------------------------------------------------
      /// Returns a boolean value indicating whether the specified coordinates
      /// are within the bounds of the map.
      ///
      /// @param x The horizontal position to check.
      /// @param y The vertical position to check.
      ///
      /// @return bool A boolean value indicating whether the specified
      ///              coordinates are within the map's bounds.
      //
      bool isWithinBounds(const int x, const int y);
    
      //------------------------------------------------------------------------
      /// Returns a boolean value indicating whether the specified field at the
      /// specified position is completely within the bounds of the map.
      ///
      /// @param field The field whose frame to check.
      /// @param x The horizontal position of the field.
      /// @param y The vertical position of the field.
      ///
      /// @return bool A boolean value indicating whether the specified field
      ///              at the specified coordinates is completely within the
      ///              map's bounds.
      //
      bool isWithinBounds(Field &field, const int x, const int y);
    
      //------------------------------------------------------------------------
      /// Returns a boolean value indicating whether a specified field at a
      /// specified position has a free area to be build. The area is free, if
      /// the field can be fully placed onto the map and if all fields affected
      /// by the field are of type GRASS.
      ///
      /// @param field The field whose area to check.
      /// @param x The horizontal position of the field.
      /// @param y The vertical position of the field.
      ///
      /// @return bool A boolean value indicating whether the specified field's
      ///              area is free.
      //
      bool hasFreeArea(Field &field, const int x, const int y);
    
      //------------------------------------------------------------------------
      /// Returns a boolean value indicating whether a specified field at a
      /// specified position borders another building. The boundaries are free,
      /// if no other buiding borders the field.
      ///
      /// @param field The field whose boundaries to check.
      /// @param x The horizontal position of the field.
      /// @param y The vertical position of the field.
      ///
      /// @return bool A boolean value indicating whether the specified field's
      ///              boundaries are free.
      //
      bool hasFreeBoundaries(Field &field, const int x, const int y);
    
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
