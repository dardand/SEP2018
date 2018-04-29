//
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
  
  
  if(parameters.size() != 0)
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
