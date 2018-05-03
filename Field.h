//------------------------------------------------------------------------------
// Field.h
//
// Group: Group 18762, study assistant: Philip Loibl
//
// Authors: Stefan Schnutt (11708769)
// Dardan Dermaku (01637087)
// Ermal Gashi (01635065)
//------------------------------------------------------------------------------
//

#ifndef FIELD_H
#define FIELD_H

#include <string>

using std::string;

namespace Sep
{
  //----------------------------------------------------------------------------
  /// The Field class represents a field on the board of the game.
  /// The field can represent grass, water, obstacles, streets, homes, markets,
  /// clinics or town halls.
  //
  class Field
  {
    public:
    
      //------------------------------------------------------------------------
      /// Represents the type of a Field instance.
      //
      enum FieldType
      {
        GRASS = 'G',
        WATER = 'W',
        OBSTACLE = 'O',
        STREET ='S',
        HOME = 'H',
        MARKET = 'M',
        CLINIC = 'C',
        TOWNHALL = 'T',
        UNKNOWN = 'U'
      };
    
      //------------------------------------------------------------------------
      /// Creates a new Field instance of field type GRASS.
      //
      Field();
      
      //------------------------------------------------------------------------
      /// Creates a new Field instance with a specified field type.
      ///
      /// @param type The field type of the new Field instance.
      /// @param width The width of the new Field instance.
      /// @param height The height of the new Field instance.
      //
      Field(const FieldType type, const int width = 1, const int height = 1);
    
      //------------------------------------------------------------------------
      /// Creates a new Field instance by copying the attributes of a specified
      /// Field instance to the newly initialized object.
      ///
      /// @param field The Field instance to be copied.
      //
      Field(const Field &field);

      //------------------------------------------------------------------------
      /// Assigns the attributes of a specified Field instance to an already
      /// existing object.
      ///
      /// @param field The Field instance to be copied.
      //
      Field operator = (const Field &field);
    
      //------------------------------------------------------------------------
      /// Frees resources that the Field instance may have acquired during its
      /// lifetime. Called when the object is being deallocated.
      //
      ~Field();

      //------------------------------------------------------------------------
      /// Returns the display name of a specified field type.
      ///
      /// @param type The type whose name to return.
      ///
      /// @return string The name of a specified field type.
      //
      static const string getName(const FieldType type);
    
      //------------------------------------------------------------------------
      /// Returns the field type of a Field instance.
      ///
      /// @return FieldType The field type of the receiver.
      //
      const FieldType getType();
    
      //------------------------------------------------------------------------
      /// Returns the width of a Field instance.
      ///
      /// @return int The width of the receiver.
      //
      const int getWidth();
    
      //------------------------------------------------------------------------
      /// Returns the height of a Field instance.
      ///
      /// @return int The height of the receiver.
      //
      const int getHeight();
    
      //------------------------------------------------------------------------
      /// Returns the size of a Field instance.
      ///
      /// @return int The size of the receiver.
      //
      const int getSize();
    
      //------------------------------------------------------------------------
      /// Returns a boolean value indicating whether fields of a specified field
      /// type are ground fields.
      ///
      /// @param type The field type to check.
      ///
      /// @return bool The boolean value indicating whether fields of the
      ///              specified field type are ground fields.
      //
      static const bool isGround(FieldType type);
    
      //------------------------------------------------------------------------
      /// Returns a boolean value indicating whether fields of a specified field
      /// type are building fields.
      ///
      /// @param type The field type to check.
      ///
      /// @return bool The boolean value indicating whether fields of the
      ///              specified field type are building fields.
      //
      static const bool isBuilding(FieldType type);
    
    private:
    
      //------------------------------------------------------------------------
      /// The field's type.
      //
      FieldType type_;
    
      //------------------------------------------------------------------------
      /// The field's width on the map.
      //
      int width_;
    
      //------------------------------------------------------------------------
      /// The field's heigth on the map.
      //
      int height_;
  };
}

#endif // FIELD_H
