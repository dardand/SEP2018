//------------------------------------------------------------------------------
// Game.h
//
// Group: Group 18762, study assistant: Philip Loibl
//
// Authors: Stefan Schnutt (11708769)
// Dardan Dermaku (01637087)
// Ermal Gashi (01635065)
//------------------------------------------------------------------------------
//

#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <string>
#include <vector>
#include "Field.h"

using std::string;
using std::vector;
using Sep::Field;
using FieldType = Field::FieldType;

namespace Sep
{
  class Interface;
  
  //----------------------------------------------------------------------------
  /// A Game object is a representation of the current game played by the user.
  //
  class Game
  {
    public:
    
      //------------------------------------------------------------------------
      /// Returns a new Game instance with a specified interface and
      /// configuration file.
      ///
      /// @param io The type whose name to return.
      /// @param config The configuration file.
      //
      Game(Interface &io, std::string config);
    
      //------------------------------------------------------------------------
      /// Creates a new Game instance by copying the attributes of a specified
      /// Game instance to the newly initialized object.
      ///
      /// @param game The Game instance to be copied.
      //
      Game(const Game &game);
    
      //------------------------------------------------------------------------
      /// Assigns the attributes of a specified game instance to an already
      /// existing object.
      ///
      /// @param game The Game instance to be copied.
      //
      Game operator = (const Game &game);
    
      //------------------------------------------------------------------------
      /// Frees resources that the Game instance may have acquired during its
      /// lifetime. Called when the object is being deallocated.
      //
      ~Game();
    
      //------------------------------------------------------------------------
      /// Displays the current playing field.
      //
      void run();
      void setRunning(bool x);
      bool getRunning();
      //------------------------------------------------------------------------
      /// Sets the a specified field at given coordinates and returns whether
      /// the coordinates are inside the playing field.
      ///
      /// @param field The Field instance, whose type to set.
      /// @param x The x coordinate, where the field should be set.
      /// @param y The y coordinate, where the field should be set.
      ///
      /// @return If the x and y coordinates are inside the playing field, true
      ///         is returned, otherwise false.
      //
      bool setField(Field &field, int x, int y);
    
    private:
      bool running = 1;
      //------------------------------------------------------------------------
      /// The width of the current playing field.
      //
      int board_width_;
    
      //------------------------------------------------------------------------
      /// The height of the current playing field.
      //
      int board_height_;
    
      //------------------------------------------------------------------------
      /// The current budget.
      //
      int money_;
    
      //------------------------------------------------------------------------
      /// A reference to the used Interace instance.
      //
      Interface &io_;
    
      //------------------------------------------------------------------------
      /// The name of the configuration file.
      //
      string config_;
    
      //------------------------------------------------------------------------
      /// The current playing field.
      //
      vector<vector<FieldType>> map_;
  };
}

#endif // GAME_H

