//------------------------------------------------------------------------------
// Map.cpp
//
// Group: Group 18762, study assistant: Philip Loibl
//
// Authors: Stefan Schnutt (11708769)
// Dardan Dermaku (01637087)
// Ermal Gashi (01635065)
//------------------------------------------------------------------------------
//

#include <string>
#include <iostream>
#include "Map.h"
#include "BadConfigException.h"
#include "Point.h"

using Sep::Map;
using Sep::Field;
using FieldType = Sep::Field::FieldType;
using Sep::Point;



// MARK: - Life cycle methods

//------------------------------------------------------------------------------
Map::Map() : Map(string(1, FieldType::TOWNHALL), 1)
{
}

//------------------------------------------------------------------------------
Map::Map(const string flat_map, const int concatenations)
{
  if (flat_map.length() % concatenations != 0)
  {
    throw std::invalid_argument("Flat map and concatenations do not match.");
  }
  
  width_ = int(flat_map.length()) / concatenations;
  height_ = concatenations;
  
  // Creates two dimensional vector from flat map for easier iteration.
  vector<vector<char>> types;
  for (int col = 0; col < width_; col++)
  {
    vector<char> col_chars;
    for (int row = 0; row < height_; row++)
    {
      int pos = row * width_ + col;
      col_chars.push_back(flat_map[pos]);
    }
    types.push_back(col_chars);
  }
  
  static const char SKIP_CHAR = 'X';
  Field *fields[width_][height_];
  int number_of_townhalls = 0;
  
  for (int col = 0; col < width_; col++)
  {
    for (int row = 0; row < height_; row++)
    {
      char abbreviation = types.at(col).at(row);
      if (abbreviation == SKIP_CHAR)
      {
        continue;
      }
      
      FieldType type = FieldType(abbreviation);
      // TODO: Check if abbreviation is a valid field type.
      int field_width = 1;
      int field_height = 1;
      
      // Calculates the field size in case of buildings.
      // Townhall is the only building supported in the config file yet.
      if (type == FieldType::TOWNHALL)
      {
        number_of_townhalls++;
        
        // Calculates height.
        // Counts the number of associated fields unterneath the current one by
        // checking for their type equality. The height of the current field is
        // beeing increased by that number of fields.
        while (row + field_height < height_
               && types.at(col).at(row + field_height) == abbreviation)
        {
          // The field underneath is beeing marked as associated field in order
          // to be skipped in further iterations.
          types.at(col).at(row + field_height) = SKIP_CHAR;
          field_height++;
        }
        
        // Calculates width.
        // Checks if there are any fields to the right of the current field
        // which are of the same type. The width of the current field is beeing
        // increased by that number of fields.
        while (col + field_width < width_
               && types.at(col + field_width).at(row) == abbreviation)
        {
          // The field to the right is beeing marked as associated field in
          // order to be skipped in further iterations.
          types.at(col + field_width).at(row) = SKIP_CHAR;
          
          // Checks if all field underneath also have the same type.
          // Only rectangle shapes are supported.
          for (int i = 1; i < field_height; i++)
          {
            if (types.at(col + field_width).at(row + i) != abbreviation)
            {
              throw BadConfigException(); // Not a rectangle shape
            }
            // Otherwise the field has the same type and is beeing marked to be
            // skipped in future too.
            types.at(col + field_width).at(row + i) = SKIP_CHAR;
          }
          field_width++;
        }
      } // Size calculation of buildings.
      
      types.at(col).at(row) = SKIP_CHAR;
      Field *field = new Field(type, field_width, field_height);
      
      for (int x = 0; x < field_width; x++)
      {
        for (int y = 0; y < field_height; y++)
        {
          fields[x + col][y + row] = field;
        }
      }
    }
  }
  
  if (number_of_townhalls == 0)
  {
    throw BadConfigException();
  }
  
  // Creates vector from fields array.
  vector<vector<Field *>> map;
  for (int col = 0; col < width_; col++)
  {
    vector<Field *> map_col;
    for (int row = 0; row < height_; row++)
    {
      map_col.push_back(fields[col][row]);
    }
    map.push_back(map_col);
  }
  
  fields_ = map;
}

//------------------------------------------------------------------------------
Map::Map(const Map &map)
{
  width_ = map.width_;
  height_ = map.height_;
  fields_ = map.fields_;
}

//------------------------------------------------------------------------------
Map Map::operator = (const Map &map)
{
  width_ = map.width_;
  height_ = map.height_;
  fields_ = map.fields_;
  return *this;
}

//------------------------------------------------------------------------------
Map::~Map()
{
}



// MARK: - Instance methods

//------------------------------------------------------------------------------
void Map::print(const Interface &io)
{
  vector<vector<FieldType>> types;
  for (int col = 0; col < fields_.size(); col++)
  {
    vector<FieldType> col_types;
    for (int row = 0; row < fields_.at(col).size(); row++)
    {
      col_types.push_back(fields_.at(col).at(row)->getType());
    }
    types.push_back(col_types);
  }
  io.out(types);
}



// MARK: - Getter methods

//------------------------------------------------------------------------------
Field *Map::getField(const int x, const int y)
{
  if (x <= width_ && y <= height_)
  {
    return fields_.at(x).at(y);
  }
  return NULL;
}

//------------------------------------------------------------------------------
Point *Map::getOrigin(Field &field)
{
  for (int col = 0; col < fields_.size(); col++)
  {
    for (int row = 0; row < fields_.at(col).size(); row++)
    {
      if (fields_.at(col).at(row) == &field)
      {
        return new Point(col, row);
      }
    }
  }
  return NULL;
}



// MARK: - Setter methods

//------------------------------------------------------------------------------
void Map::setField(Field &field, const int x, const int y)
{
  for (int col = 0; col < field.getWidth(); col++)
  {
    for (int row = 0; row < field.getHeight(); row++)
    {
      fields_.at(x + col).at(y + row) = &field;
    }
  }
}
