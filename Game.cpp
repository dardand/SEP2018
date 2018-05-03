//------------------------------------------------------------------------------
// Game.cpp
//
// Group: Group 18762, study assistant: Philip Loibl
//
// Authors: Stefan Schnutt (11708769)
// Dardan Dermaku (01637087)
// Ermal Gashi (01635065)
//------------------------------------------------------------------------------
//

#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <climits>
#include <limits>
#include <sstream>
#include <algorithm>
#include <memory>
#include "Build.h"
#include "Game.h"
#include "Interface.h"
#include "BadConfigException.h"
#include "Quit.h"
#include "Buildable.h"
#include "Destroyable.h"

using std::string;
using Sep::Interface;
using Sep::Game;
using Sep::Buildable;
using Sep::Destroyable;



// MARK: - Constants

static const int MIN_WIDTH = 1;
static const int MIN_HEIGHT = 1;
static const int MAX_WIDTH = 100;
static const int MAX_HEIGHT = 100;
static const int MIN_MONEY = 1;
static const int MAX_MONEY = INT_MAX;
static const int MAX_BUILDING_WIDTH = 3;
static const int MAX_BUILDING_HEIGHT = 3;



// MARK: - Life cycle methods

//------------------------------------------------------------------------------
Game::Game(Interface &io, string config) : io_(io), config_(config)
{
  // Reads and validates the config file.
  vector<vector<FieldType>> field_types;
  readConfig(config, board_width_, board_height_, money_, field_types);
  
  // Creates the map.
  static const FieldType DEFAULT_FIELD_TYPE = FieldType::GRASS;
  map_ = Map(board_width_, board_height_, DEFAULT_FIELD_TYPE);
  
  for (int col = 0; col < board_width_; col++)
  {
    for (int row = 0; row < board_height_; row++)
    {
      FieldType type = field_types.at(col).at(row);
      if (type == DEFAULT_FIELD_TYPE)
      {
        continue;
      }
      
      int field_width = 1;
      int field_height = 1;
      
      // Calculates the field size in case of buildings.
      // Townhall is the only building supported in the config file yet.
      if (Field::isBuilding(type))
      {
        // Calculates height.
        // Counts the number of associated fields unterneath the current one by
        // checking for their type equality. The height of the current field is
        // beeing increased by that number of fields.
        while (row + field_height < board_height_
               && field_types.at(col).at(row + field_height) == type)
        {
          // The field underneath is beeing marked as associated field in order
          // to be skipped in further iterations.
          field_types.at(col).at(row + field_height) = DEFAULT_FIELD_TYPE;
          field_height++;
        }
        
        // Calculates width.
        // Checks if there are any fields to the right of the current field
        // which are of the same type. The width of the current field is beeing
        // increased by that number of fields.
        while (col + field_width < board_width_
               && field_types.at(col + field_width).at(row) == type)
        {
          // The field to the right is beeing marked as associated field in
          // order to be skipped in further iterations.
          field_types.at(col + field_width).at(row) = DEFAULT_FIELD_TYPE;
          
          // Checks if all field underneath also have the same type.
          // Only rectangle shapes are supported.
          for (int i = 1; i < field_height; i++)
          {
            if (field_types.at(col + field_width).at(row + i) != type)
            {
              throw BadConfigException(); // Not a rectangle shape.
            }
            // Otherwise the field has the same type and is beeing marked to be
            // skipped in future too.
            field_types.at(col + field_width).at(row + i) = DEFAULT_FIELD_TYPE;
          }
          field_width++;
        }
        
        if (field_width > MAX_BUILDING_WIDTH
            || field_height > MAX_BUILDING_HEIGHT)
        {
          throw BadConfigException();
        }
        
      } // Size calculation of buildings.
      
      field_types.at(col).at(row) = DEFAULT_FIELD_TYPE;
      Field *field = new Field(type, field_width, field_height);
      if (!map_.hasFreeBoundaries(*field, col, row)
          || !map_.hasFreeArea(*field, col, row))
      {
        throw BadConfigException();
      }
      
      map_.setField(*field, col, row);
    }
  }
  
  // Interface output.
  io_.out(Interface::SETTING, "BOARDSIZE " + std::to_string(board_width_) + " "
          + std::to_string(board_height_));
  io_.out(map_.getFieldTypes());
}

//------------------------------------------------------------------------------
Game::Game(const Game &game) : io_(game.io_), config_(game.config_),
  board_width_(game.board_width_), board_height_(game.board_height_),
  map_(game.map_), running_(game.running_), money_(game.money_)
{
}

//------------------------------------------------------------------------------
Game Game::operator = (const Game &game)
{
  running_ = game.running_;
  board_height_ = game.board_height_;
  board_width_ = game.board_width_;
  money_ = game.money_;
  config_ = game.config_;
  // TODO: Find alternative to io_ = game.io_;
  map_ = game.map_;
  return *this;
}

//------------------------------------------------------------------------------
Game::~Game()
{
}



// MARK: - Instance methods

//------------------------------------------------------------------------------
void Game::readConfig(const string config, int &width, int &height, int &money,
                      vector<vector<FieldType>> &field_types)
{
  static const char COMMENT_SIGN = '#';
  static const string CONFIG_KEYWORD = "#SEPCITY";
  static const string SIZE_KEYWORD = "SIZE:";
  static const string MONEY_KEYWORD = "MONEY:";
  static const string MAP_KEYWORD = "MAP:";
  
  // Open config
  std::ifstream file;
  file.open(config);
  if (!file)
  {
    throw BadConfigException();
  }
  
  // Check config
  string keyword;
  file >> keyword;
  if (keyword.compare(CONFIG_KEYWORD))
  {
    file.close();
    throw BadConfigException();
  }
  
  // Read config
  bool size_read = false;
  bool money_read = false;
  while (file >> keyword)
  {
    if (keyword[0] == COMMENT_SIGN)
    {
      // Skips rest on line in case of a comment.
      file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
    else if (!keyword.compare(SIZE_KEYWORD) && !size_read)
    {
      file >> width >> height;
      if (width < MIN_WIDTH || width > MAX_WIDTH
          || height < MIN_HEIGHT || height > MAX_HEIGHT)
      {
        file.close();
        throw BadConfigException();
      }
      size_read = true;
      // Skips rest of line because only one keyword per line is allowed.
      file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
    else if (!keyword.compare(MONEY_KEYWORD) && !money_read)
    {
      long config_money; // Use long in case the value in config file is
                         // greater than the maximum integer value.
      file >> config_money;
      if (config_money < MIN_MONEY || config_money > MAX_MONEY)
      {
        file.close();
        throw BadConfigException();
      }
      money = int(config_money);
      money_read = true;
      // Skips rest of line because only one keyword per line is allowed.
      file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
    else if (!keyword.compare(MAP_KEYWORD) && size_read && money_read)
    {
      string flat_map;
      for (int row = 0; row < height; row++)
      {
        string map_row;
        file >> map_row;
        flat_map += map_row;
      }
      
      // Checks size
      if(flat_map.length() != width * height)
      {
        file.close();
        throw BadConfigException();
      }
      
      // Checks flat map
      static const vector<FieldType> supported_types =
      {
        FieldType::GRASS,
        FieldType::WATER,
        FieldType::OBSTACLE,
        FieldType::TOWNHALL
      };
      int number_of_townhalls = 0;
      
      vector<vector<FieldType>> types;
      for (int col = 0; col < width; col++)
      {
        vector<FieldType> col_types;
        for (int row = 0; row < height; row++)
        {
          int pos = row * width + col;
          FieldType type = FieldType(flat_map[pos]);
          
          // Checks for unsupported characters
          if (std::find(supported_types.begin(),
                        supported_types.end(),
                        type) == supported_types.end())
          {
            file.close();
            throw BadConfigException();
          }
          
          // Counts townhalls
          if (type == FieldType::TOWNHALL)
          {
            number_of_townhalls++;
          }
          
          col_types.push_back(type);
        }
        types.push_back(col_types);
      }
      
      // Checks presence of townhalls
      if (number_of_townhalls == 0)
      {
        file.close();
        throw BadConfigException();
      }
      
      field_types = types;
    }
    else // Invalid or missing keywords
    {
      file.close();
      throw BadConfigException();
    }
  }
  
  file.close();
}

//------------------------------------------------------------------------------
void Game::run()
{
  bool found = false;
  std::string input;
  std::vector<std::string> string_vector;
  Quit *quit = new Quit;
  quit->setName("quit");
  std::shared_ptr<Quit> command_quit (quit);
  Build *build = new Build;
  build->setName("build");
  std::shared_ptr<Build> command_build (build);
  std::vector<std::shared_ptr<Command>> commands = 
  {
    command_quit, command_build
  };
  while(this->getRunning())
  {
     input = io_.in();
     std::vector <string> tokens;
     std::vector <string> command_parameters;
     std::stringstream stream(input);
     string intermediate;
     while(stream >> intermediate)
     {
       std::transform(intermediate.begin(), intermediate.end(),
                      intermediate.begin(), ::tolower);
       tokens.push_back(intermediate);
     }
     if(tokens.size() == 0)
     {
       continue;
     }
     for(unsigned int i = 1; i < tokens.size(); i++)
     {
       command_parameters.push_back(tokens[i]);
     }
     for(auto const& command : commands)
     {
       if(command->getName() == tokens[0])
       {
         command->execute(*this, command_parameters);
         found = true;
         break;
       }
     }
     if(found == false)
     {
       io_.out(Sep::Interface::WARNING, "Unknown command!");
     }
     found = false;
  }
}



// MARK: - Getter methods

//------------------------------------------------------------------------------
bool Game::getRunning()
{
  return running_;
}



// MARK: - Setter methods

//------------------------------------------------------------------------------
bool Game::setField(Field &field, int x, int y)
{
  bool right_input = true;
  if (!map_.isWithinBounds(field, x, y))
  {
    io_.out(Sep::Interface::INFO, "Coordinates are outside the board!");
    right_input = false;
  }
  else if (!map_.hasFreeArea(field, x, y))
  {
    io_.out(Sep::Interface::INFO, "Can only build on Grass!");
    right_input = false;
  }
  else if(!map_.hasFreeBoundaries(field, x, y))
  {
    io_.out(Sep::Interface::INFO, "Can not build directly next to other building!");
    right_input = false;
  }
  else
  {
    map_.setField(field, x, y);
    io_.out(map_.getFieldTypes());
    return true;
  }
  return right_input;
}

//------------------------------------------------------------------------------
void Game::setRunning(bool running)
{
  running_ = running;
}
