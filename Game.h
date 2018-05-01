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
#include "Map.h"

using std::string;
using std::vector;
using Sep::Field;
using FieldType = Field::FieldType;
using Sep::Map;

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
    
      //------------------------------------------------------------------------
      /// Changes the running state of the current game with a specified
      /// boolean value.
      ///
      /// @param running A boolean value indicating whether the game is running.
      //
      void setRunning(bool running);
    
      //------------------------------------------------------------------------
      /// Returns a boolean value whether the current game is running.
      //
      bool getRunning();
    
      //------------------------------------------------------------------------
      /// Builds a field with specified type at a specified position.
      ///
      /// @param type The type of the field to build.
      /// @param x The horizontal position of the field to build.
      /// @param y The vertical position of the field to build.
      ///
      /// @return bool A boolen value indicating whether the field was build
      ///              successfully.
      //
      bool build(const FieldType type, const int x, const int y);
    
      //------------------------------------------------------------------------
      /// Builds a field with specified type and size at a specified position.
      ///
      /// @param type The type of the field to build.
      /// @param x The horizontal position of the field to build.
      /// @param y The vertical position of the field to build.
      /// @param width The width of the field to build.
      /// @param height The height of the field to build.
      ///
      /// @return bool A boolen value indicating whether the field was build
      ///              successfully.
      bool build(const FieldType type, const int x, const int y, const int width,
                 const int height);
    
      //------------------------------------------------------------------------
      /// Destroys a field on the map at a specified position. All related
      /// fields will be destroyed too. Fields to destroy will be set to GRASS.
      ///
      /// @param x The horizontal position of the field to destroy.
      /// @param y The vertical position of the field to destroy.
      ///
      /// @return bool A boolean value indicating whether the destruction at the
      ///              specified positon was successfully.
      //
      bool destroy(const int x, const int y);
      
            //------------------------------------------------------------------------
      /// This function returns the current amount of available funds.
      /// 
      /// @return money_ The amount of money.
      //
      int getMoney()
      {
        return money_;
      }

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
      Sep::Map map_;
    
  };
}

#endif // GAME_H

