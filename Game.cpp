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
#include <memory>
#include "Quit.h"
#include <iostream>
#include <string>
#include <sstream>
#include "Game.h"
#include "Interface.h"
#include "Build.h"
using std::string;
using Sep::Interface;
using Sep::Game;
using Sep::Field;



// MARK: - Life cycle methods

//------------------------------------------------------------------------------
Game::Game(Interface &io, string config) : io_(io), config_(config)
{
  board_width_ = 20;
  board_height_ = 10;
  money_ = 100;
  std::vector<FieldType> col_types;
  for (int col = 0; col < board_width_; col++)
  {
    for (int row = 0; row < board_height_; row++)
    {
      col_types.push_back(Field::GRASS);
    }
    map_.push_back(col_types);
  }
  
  io_.out(Interface::SETTING, "BOARDSIZE " + std::to_string(board_width_) + " "
          + std::to_string(board_height_));
  io_.out(map_);
}

//------------------------------------------------------------------------------
Game::Game(const Game &game) : io_(game.io_), config_(game.config_),
           map_(game.map_)
{
  board_height_ = game.board_height_;
  board_width_ = game.board_width_;
  money_ = game.money_;
}

//------------------------------------------------------------------------------
Game Game::operator = (const Game &game) 
{
  board_height_ = game.board_height_;
  board_width_ = game.board_width_;
  money_ = game.money_;
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
  bool found = true;
  std::string input;
  std::vector<std::string> v;
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
     std::vector<string> command_parameters;
     string intermediate;
     std::stringstream check1(input);
     while(getline(check1, intermediate, ' '))
     {
       tokens.push_back(intermediate);
     }
     //std::cout << tokens.size();
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
       std::cout << "Unknown Command" << std::endl;
     }
  }
  io_.out(map_);
}



// MARK: - Setter methods

//------------------------------------------------------------------------------
bool Game::setField(Field &field, int x, int y)
{
  if((x >= 0 && x <= board_width_) && (y >= 0 && y <= board_height_))
  {
    map_.at(x).at(y) = field.getType();
    io_.out(map_);
    return true;
  }
  else
  {
    return false;
  }
}
void Game::setRunning(bool x)
{
  running = x;
}
bool Game::getRunning()
{
  return running;
}

