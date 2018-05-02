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
using Sep::Map;
using Sep::Field;
using Sep::Buildable;
using Sep::Destroyable;



// MARK: - Constants

static int MIN_WIDTH = 1;
static int MIN_HEIGHT = 1;
static int MAX_WIDTH = 100;
static int MAX_HEIGHT = 100;
static int MIN_MONEY = 1;
static int MAX_MONEY = INT_MAX;



// MARK: - Life cycle methods

//------------------------------------------------------------------------------
Game::Game(Interface &io, string config) : io_(io), config_(config)
{
  static char COMMENT_SIGN = '#';
  static string CONFIG_KEYWORD = "#SEPCITY";
  static string SIZE_KEYWORD = "SIZE:";
  static string MONEY_KEYWORD = "MONEY:";
  static string MAP_KEYWORD = "MAP:";
  
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
      file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
    else if (!keyword.compare(SIZE_KEYWORD) && !size_read)
    {
      file >> board_width_ >> board_height_;
      if (board_width_ < MIN_WIDTH || board_width_ > MAX_WIDTH
          || board_height_ < MIN_HEIGHT || board_height_ > MAX_HEIGHT)
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
      long money; // Use long in case the value in config file is greater than
                  // the maximum integer value.
      file >> money;
      if (money < MIN_MONEY || money > MAX_MONEY)
      {
        file.close();
        throw BadConfigException();
      }
      money_ = int(money);
      money_read = true;
      // Skips rest of line because only one keyword per line is allowed.
      file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
    else if (!keyword.compare(MAP_KEYWORD) && size_read && money_read)
    {
      string flat_map;
      for (int row = 0; row < board_height_; row++)
      {
        string map_row;
        file >> map_row;
        flat_map += map_row;
      }
      
      if (flat_map.length() != board_width_ * board_height_)
      {
        file.close();
        throw BadConfigException();
      }
      
      map_ = Map(flat_map, board_height_);
    }
    else
    {
      file.close();
      throw BadConfigException();
    }
  }
  
  file.close();
  
  io_.out(Interface::SETTING, "BOARDSIZE " + std::to_string(board_width_) + " "
          + std::to_string(board_height_));
  map_.print(io_);
}

//------------------------------------------------------------------------------
Game::Game(const Game &game) : io_(game.io_), config_(game.config_),
           map_(game.map_)
{
  running_ = game.running_;
  board_height_ = game.board_height_;
  board_width_ = game.board_width_;
  money_ = game.money_;
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

//------------------------------------------------------------------------------
bool Game::build(const FieldType type, const int x, const int y)
{
  return build(type, x, y, 1, 1);
}

//------------------------------------------------------------------------------
bool Game::build(const FieldType type, const int x, const int y,
                 const int width, const int height)
{
  // TODO: Check if type is buildable. Instantiate a Buildable object, calculate
  //       the construction cost by calling the provided method and set the
  //       Buildable object at the specified positon with specified size on the
  //       map by calling the private Game method setField if allowed.
  return false;
}

//------------------------------------------------------------------------------
bool Game::destroy(int x, int y)
{
  // TODO: Check if positon is on map and if the field at the specified position
  //       is a Destroyable object. Calculate it's destruction cost by calling
  //       the provided method and set each releated position on the map to
  //       grass by calling the private Game method setField if allowed.
  return false;
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
  if((x >= 0 && x <= board_width_) && (y >= 0 && y <= board_height_))
  {
    map_.setField(field, x, y);
    map_.print(io_);
    return true;
  }
  else
  {
    //std::cout << "OUT OF RANGE";
    return false;
  }
}

//------------------------------------------------------------------------------
void Game::setRunning(bool running)
{
  running_ = running;
}
