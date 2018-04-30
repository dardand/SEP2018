//------------------------------------------------------------------------------
// main.cpp
//
// SEPCity is a simple city-building simulation. In this game, the player
// assumes the role of a small city mayor. He is responsible for building
// houses, supermarkets and hospitals and connecting them with roads. The
// supermarkets serve to supply the inhabitants. If enough homes and
// supermarkets are available, people are moving into SEPCity. The player gets
// taxes from the inhabitants of the city. Supermarkets and hospitals cost the
// city money. The goal of the game is to maximize the capital of the city.
//
// Group: Group 18762, study assistant: Philip Loibl
//
// Authors: Tutors
//------------------------------------------------------------------------------
//

#include "Interface.h"
#include "Field.h"
#include "Game.h"
#include "BadConfigException.h"

namespace Sep
{
  static constexpr int RETURN_OK = 0;
  static constexpr int RETURN_ERROR_BAD_CONFIG = -1;
  static constexpr int RETURN_ERROR_ALLOC = -2;
  static constexpr int RETURN_ERROR_FRAMEWORK = -3;
  static constexpr int RETURN_ERROR_ARGUMENT = -4;
}

//----------------------------------------------------------------------------
/// The main entry point of the application. Returns the exit code.
///
/// @param argc An number of arguments passed. Minimum is 1 for the name of
///             the executable.
/// @param argv The arguments passed on application launch.
///
/// @return An integer value indicating the reason of application exit.
///         Default is 0. -1 for errors concerning the config file. Allocation
///         errors are represented by -2. For errors which occurred in the
///         framework -3 is returned. And for errors due to wrong arguments -4
///         is returned.
//
int main(int argc, char *argv[])
{
  bool use_web = false;
  if(argc != 2 && argc != 3)
  {
    Sep::Interface::error(Sep::Interface::ERROR_WRONG_ARGUMENTS);
    return Sep::RETURN_ERROR_ARGUMENT;
  }
  
  if(argc == 3)
  {
    if(std::string(argv[2]) == "use_web")
    {
      use_web = true;
    }
    else
    {
      Sep::Interface::error(Sep::Interface::ERROR_WRONG_ARGUMENTS);
      return Sep::RETURN_ERROR_ARGUMENT;
    }
  }
  
  try
  {
    Sep::Interface::start(use_web);
    Sep::Interface io;
    Sep::Game game(io, std::string(argv[1]));
    game.run();
    Sep::Interface::stop();
    return Sep::RETURN_OK;
  }
  catch(Sep::BadConfigException &e)
  {
    Sep::Interface::error(e.what());
    Sep::Interface::stop();
    return Sep::RETURN_ERROR_BAD_CONFIG;
  }
  catch(std::bad_alloc &e)
  {
    Sep::Interface::error(Sep::Interface::ERROR_BAD_ALLOC);
    Sep::Interface::stop();
    return Sep::RETURN_ERROR_ALLOC;
  }
  catch(Web::InterfaceDisconnect &e)
  {
    Sep::Interface::error(e.what());
    Sep::Interface::stop();
    return Sep::RETURN_ERROR_FRAMEWORK;
  }
  catch(Web::InterfaceException &e)
  {
    Sep::Interface::error(e.what());
    Sep::Interface::stop();
    return Sep::RETURN_ERROR_FRAMEWORK;
  }
}
