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

#include "Map.h"
#include "Point.h"

using Sep::Map;
using Sep::Point;



// MARK: - Life cycle methods

//------------------------------------------------------------------------------
Map::Map() : Map(0, 0)
{
}

//------------------------------------------------------------------------------
Map::Map(const int width, const int height, const FieldType type)
          : width_(width), height_(height)
{
  fields_ = vector<vector<Field *>> (width_,
                                     vector<Field *> (height_, NULL));
  
  for (int col = 0; col < width; col++)
  {
    for (int row = 0; row < height; row++)
    {
      fields_.at(col).at(row) = new Field(type);
    }
  }
}

//------------------------------------------------------------------------------
Map::Map(const Map &map)
          : width_(map.width_), height_(map.height_), fields_(map.fields_)
{
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



// MARK: - Getter methods

//------------------------------------------------------------------------------
Field *Map::getField(const int x, const int y)
{
  if (isWithinBounds(x, y))
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

//------------------------------------------------------------------------------
vector<vector<FieldType>> Map::getFieldTypes()
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
  return types;
}



// MARK: - Setter methods

//------------------------------------------------------------------------------
bool Map::setField(Field &field, const int x, const int y)
{
  // Checks overflow
  if (!isWithinBounds(field, x, y))
  {
    return false;
  }
  
  int firstCol = x;
  int firstRow = y;
  int lastCol = firstCol + field.getWidth() - 1;
  int lastRow = firstRow + field.getHeight() - 1;
  
  // Sets all related fields
  for (int col = firstCol; col <= lastCol; col++)
  {
    for (int row = firstRow; row <= lastRow; row++)
    {
      fields_.at(col).at(row) = &field;
    }
  }
  
  return true;
}



// MARK: - Validation methods

//------------------------------------------------------------------------------
bool Map::isWithinBounds(const int x, const int y)
{
  return x >= 0 && x < width_ && y >= 0 && y < height_;
}

//------------------------------------------------------------------------------
bool Map::isWithinBounds(Field &field, const int x, const int y)
{
  int lastX = x + field.getWidth() - 1;
  int lastY = y + field.getHeight() - 1;
  return (isWithinBounds(x, y) && isWithinBounds(lastX, lastY));
}

//------------------------------------------------------------------------------
bool Map::hasFreeArea(Field &field, const int x, const int y)
{
  // Checks overflow
  if (!isWithinBounds(field, x, y))
  {
    return false;
  }
  // Checks if building underground is free (grass).
  else if (Field::isBuilding(field.getType()) || Field::isGround(field.getType()))
  {
    int firstCol = x;
    int firstRow = y;
    int lastCol = firstCol + field.getWidth() - 1;
    int lastRow = firstRow + field.getHeight() - 1;
    
    // Checks whole building area
    for (int col = firstCol; col <= lastCol; col++)
    {
      for (int row = firstRow; row <= lastRow; row++)
      {
        if (fields_.at(col).at(row)->getType() != FieldType::GRASS)
        {
          return false; // Buildings can be only build on grass fields.
        }
      }
    }
  }
  return true;
}

//------------------------------------------------------------------------------
bool Map::hasFreeBoundaries(Field &field, const int x, const int y)
{
  // Checks overflow
  if (!isWithinBounds(field, x, y))
  {
    return false;
  }
  // Checks if building borders another building.
  else if (Field::isBuilding(field.getType()))
  {
    int firstCol = x;
    int firstRow = y;
    int lastCol = firstCol + field.getWidth() - 1;
    int lastRow = firstRow + field.getHeight() - 1;
    
    // Checks horizontally
    for (int col = firstCol - 1; col <= lastCol + 1; col++)
    {
      Field *upper_field = getField(col, firstRow - 1);
      Field *lower_field = getField(col, lastRow + 1);
      
      if ((upper_field && Field::isBuilding(upper_field->getType()))
          || (lower_field && Field::isBuilding(lower_field->getType())))
      {
        return false;
      }
    }
    
    // Checks vertically
    for (int row = firstRow - 1; row <= lastRow + 1; row++)
    {
      Field *left_field = getField(firstCol - 1, row);
      Field *right_field = getField(lastCol + 1, row);
      
      if ((left_field && Field::isBuilding(left_field->getType()))
          || (right_field && Field::isBuilding(right_field->getType())))
      {
        return false;
      }
    }
  }
  return true;
}
