//------------------------------------------------------------------------------
// Point.h
//
// Group: Group 18762, study assistant: Philip Loibl
//
// Authors: Stefan Schnutt (11708769)
// Dardan Dermaku (01637087)
// Ermal Gashi (01635065)
//------------------------------------------------------------------------------
//

#ifndef POINT_H
#define POINT_H

namespace Sep
{
  //----------------------------------------------------------------------------
  /// A Point object represents a position in a two dimensional coordinate
  /// system.
  //
  class Point
  {
    public:
    
      //------------------------------------------------------------------------
      /// Creates a new Point instance at position (0,0).
      //
      Point();
    
      //------------------------------------------------------------------------
      /// Creates a new Point instance at a specified position.
      ///
      /// @param x The horizontal position.
      /// @param y The vertical position.
      //
      Point(const int x, const int y);
    
      //------------------------------------------------------------------------
      /// Creates a new Point instance by copying the attributes of a specified
      /// Point instance to the newly initialized object.
      ///
      /// @param point The Point instance to be copied.
      //
      Point(const Point &point);
    
      //------------------------------------------------------------------------
      /// Assigns the attributes of a specified Point instance to an already
      /// existing object.
      ///
      /// @param point The Point instance to be copied.
      //
      Point operator = (const Point &point);
    
      //------------------------------------------------------------------------
      /// Frees resources that the Point instance may have acquired during its
      /// lifetime. Called when the object is being deallocated.
      //
      ~Point();
    
      //------------------------------------------------------------------------
      /// Sets the horizontal positon of the point object.
      ///
      /// @param x The horizontal positon to set.
      //
      void setX(const int x);
    
      //------------------------------------------------------------------------
      /// Sets the vertical positon of the point object.
      ///
      /// @param y The vertical positon to set.
      //
      void setY(const int y);
    
      //------------------------------------------------------------------------
      /// Returns the horizontal positon of the point object.
      ///
      /// @return x The horizontal positon.
      //
      int getX();
    
      //------------------------------------------------------------------------
      /// Returns the vertical positon of the point object.
      ///
      /// @return y The vertical positon.
      //
      int getY();
    
    private:
    
      //------------------------------------------------------------------------
      /// The point's horizontal position.
      //
      int x_;
    
      //------------------------------------------------------------------------
      /// The point's vertical position.
      //
      int y_;
  };
}

#endif // POINT_H
