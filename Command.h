//------------------------------------------------------------------------------
// Command.h
//

//------------------------------------------------------------------------------
//

#ifndef COMMAND_H_INCLUDED
#define COMMAND_H_INCLUDED

#include <string>
#include <vector>
#include "Game.h"


//----------------------------------------------------------------------------
// GameHandler Class
// Baseclass for commands
// contains setter/getter for name and pure virtual execute method
//
class Command
{
  private:
    //--------------------------------------------------------------------------
    // Private copy constructor

    Command(const Command& original);

    //--------------------------------------------------------------------------
    // Private assignment operator

    Command& operator=(const Command& original);
    
    //--------------------------------------------------------------------------
    // Name of this command
    std::string command_name_;

  public:
    //--------------------------------------------------------------------------
    // Constructor
    Command();
    Command(std::string name);

    //--------------------------------------------------------------------------
    // Destructor

    virtual ~Command();

    //--------------------------------------------------------------------------
    // Executes the command.
    // @param game The game where action should be performed on
    // @param parameters Possible parameters neede for the execution
    // @return Integer representing the success of the action

    virtual int execute(Sep::Game& game,
                        std::vector<std::string>& parameters) = 0;
    
    //--------------------------------------------------------------------------
    // Getter Methods
    const std::string& getName() const;
    const void setName(std::string name) {command_name_ = name;}
    
};

#endif //COMMAND_H_INCLUDED
