//------------------------------------------------------------------------------
// Quit.cpp
//
// Group: Group 15631, study assistant Philip Loibl
//
//------------------------------------------------------------------------------
//

#include "Quit.h"
#include "Interface.h"

//------------------------------------------------------------------------------
Quit::Quit()
{
}

//------------------------------------------------------------------------------
Quit::Quit(std::string name) : Command(name)
{
}




//------------------------------------------------------------------------------
Quit::~Quit()
{
}

//------------------------------------------------------------------------------
int Quit::execute(Sep::Game& game, std::vector<std::string>& parameters)
{
  Sep::Interface output_engine;
  
  
  if(parameters.size() != 0)
  {
    std::cout << "[ERR] Usage: quit\n";
  }
  else
  {
    std::cout << "Going out of business!\n";
    game.setRunning(false);
  }
  return -1;
}
