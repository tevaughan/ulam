
// Copyright 2014  Thomas E. Vaughan
//
// This file is part of Ulam.
//
// Ulam is free software: You can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the Free Software
// Foundation, either Version 3 of the License, or (at your option) any later
// version.
//
// Ulam is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
// details.
//
// You should have received a copy of the GNU General Public License along with
// Ulam.  If not, see <http://www.gnu.org/licenses/>.

#ifndef COMMAND_LINE_HPP
#define COMMAND_LINE_HPP

#include <iostream>  // for cerr, cout
#include <sstream>   // for istringstream
#include <unistd.h>  // for optarg, getopt()

/// Representation of values specified, explicitly or implicitly, on the
/// command line.
struct CommandLine
{
   char* invoc;     ///< Name of program as invoked on command line.
   int begin;       ///< Starting value at center of spiral.
   int size;        ///< Width of final image in pixels.
   bool clockWise;  ///< Flag set true only if spiral wrap clockwise.

   /// Initial direction away from center along spiral.
   enum InitDir { RIGHT, UP, LEFT, DOWN } initDir;

   /// Print out how to invoke the program, and exit with an indication of
   /// error to the operating system.
   void usage();

   /// Initialize from the command line.
   ///
   /// \param argc  Number of arguments (including invokation name) on command
   ///              line.
   ///
   /// \param argv  Array of strings, each representing a command-line option.
   CommandLine(int argc, char** argv);

private:
   /// Convert a command-line argument from a string into the specified type.
   ///
   /// \tparam TT   Type into which argument should be converted.
   ///
   /// \param  arg  Reference to object in which converted value should be
   ///              stored.
   template < typename TT >
   void convert(TT& arg)
   {
      std::istringstream iss(optarg);
      if (!(iss >> arg)) {
         std::cerr << "CommandLine::convert: ERROR converting '" << optarg
                   << "'" << std::endl;
         usage();
      }
   }
};

#endif  // ndef COMMAND_LINE_HPP

