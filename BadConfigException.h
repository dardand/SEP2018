//------------------------------------------------------------------------------
// BadConfigException.h
//
// Group: Group 18762, study assistant: Philip Loibl
//
// Authors: Stefan Schnutt (11708769)
// Dardan Dermaku (01637087)
// Ermal Gashi (01635065)
//------------------------------------------------------------------------------
//

#ifndef BAD_CONFIG_EXCEPTION_H
#define BAD_CONFIG_EXCEPTION_H

#include <exception>

namespace Sep
{
  //----------------------------------------------------------------------------
  /// A BadConfigException is an object that represents the special condition of
  /// an invalid config file that interrupts the normal flow of program
  /// execution.
  //
  class BadConfigException : public std::exception
  {
    public:
    
      //------------------------------------------------------------------------
      /// Returns a pointer to a null-terminated string with explanatory
      /// information. The pointer is guaranteed to be valid at least until the
      /// exception object from which it is obtained is destroyed, or until a
      /// non-const member function on the exception object is called.
      ///
      /// @return const char The explanatory string of the thrown exception.
      //
      const char *what()
      {
        return "Invalid Config File!\n";
      }
  };
}

#endif // BAD_CONFIG_EXCEPTION_H
