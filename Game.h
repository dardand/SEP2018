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

#include "Map.h"

using std::string;
using std::vector;

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
      /// Returns a boolean value whether the current game is running.
      //
      bool getRunning();
    
      //------------------------------------------------------------------------
      /// Changes the running state of the current game with a specified
      /// boolean value.
      ///
      /// @param running A boolean value indicating whether the game is running.
      //
      void setRunning(bool running);
    
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
    
      //------------------------------------------------------------------------
      /// Runs the game by displaying a custom command line for user input. The
      /// game runs until the user quits it with the therfore designated
      /// command.
      //
      void run();
    
      /// This function sets the amount of money.
      /// 
      /// @return none
      //
      void setMoney(int money)
      {
        money_ = money;
      }

      /// This function returns the current amount of available funds.
      /// 
      /// @return money_ The amount of money.
      //
      int getMoney()
      {
        return money_;
      }
    private:
    
      //------------------------------------------------------------------------
      /// A boolean value indicating whether the game is running.
      //
      bool running_ = true;
    
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
      Map map_;
    
      //------------------------------------------------------------------------
      /// Reads a specified config file and sets the read values into the
      /// specified references.
      ///
      /// @param config The config file to read.
      /// @param width The integer reference to store the read width in.
      /// @param height The integer reference to store the read height in.
      /// @param money The integer reference to store the read money in.
      /// @param field_types The two dimensional field type vector to store
      ///                    the field types in.
      //
      static void readConfig(const string config,
                             int &width, int &height, int &money,
                             vector<vector<Field::FieldType>> &field_types);
  };
}

#endif // GAME_H

