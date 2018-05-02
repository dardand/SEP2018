//------------------------------------------------------------------------------
// Quit.h
//
// Group: Group 15631, study assistant Philip Loibl
//

//------------------------------------------------------------------------------
//

#ifndef BUILD_H_INCLUDED
#define BUILD_H_INCLUDED

#include <string>
#include <vector>
#include <iostream>
#include "Game.h"
#include "Command.h"
//----------------------------------------------------------------------------
// Build Class
// command quit
// quits the game and the running program.
//
class Build : public Command
{
  private:
    //--------------------------------------------------------------------------
    // Name of this command
    std::string command_name_;

  public:
    //--------------------------------------------------------------------------
    // Constructor
    Build();
    Build(std::string name);
    Sep::Field* getType(std::string type);
    //--------------------------------------------------------------------------
    // Destructor
    virtual ~Build();

    //--------------------------------------------------------------------------
    // Executes the command.
    // Quits the current session.
    // @param game The game where action should be performed on
    // @param params for this command the vector should be empty
    // @return Integer representing the success of the action

    int execute(Sep::Game& game, std::vector<std::string>& params);
    
    
};
#endif //BUILD_H_INCLUDED