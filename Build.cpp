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
#include "Build.h"
#include "Interface.h"

//------------------------------------------------------------------------------
Build::Build()
{
}

//------------------------------------------------------------------------------
Build::Build(std::string name) : Command(name)
{
}

//------------------------------------------------------------------------------
Build::~Build()
{
}

//------------------------------------------------------------------------------
int Build::execute(Sep::Game& game, std::vector<std::string>& parameters)
{
  Sep::Interface output_engine;
  
  
  if(parameters.size() != 3)
  {
    std::cout << "[ERR] Usage: build\n";
    return -1;
  }
  bool is_not_number = false;
  for(int i = 1; i < parameters.size(); i++)
  {
    for(int j = 0; j < parameters[i].length(); j++)
    {
      if(!(isdigit(parameters[i][j])))
      {
        is_not_number = true;
        break;
      }
    }
  }
  
  if(is_not_number)
  {
    std::cout << "[ERR] Usage: build\n";
  }
  else
  {
    std::cout << "Build found!\n";
    game.setRunning(false);
  }
  return -1;
}
