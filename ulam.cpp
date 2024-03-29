
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

#include <iostream>  // for cout

#include "CommandLine.hpp"
#include "UlamSpiral.hpp"

using namespace std;

/// Draw an Ulam spiral, and write it out to a PPM file.
///
/// \param argc  Number of arguments (including invokation name) on command
///              line.
///
/// \param argv  Array of strings, each representing a command-line option.
int main(int argc, char** argv)
{
   CommandLine const cmdLine(argc, argv);
   UlamSpiral ulamSpiral(cmdLine.ulamConfig);
   switch (ulamSpiral.config().outputType) {
   case UlamConfig::ASCII:
      ulamSpiral.image().writeAscii(0);
      break;
   case UlamConfig::PPM:
      ulamSpiral.image().writePpm();
      break;
   case UlamConfig::AUTO:
      cerr << "main: ERROR: outputType=AUTO" << endl;
      return -1;
   }
   return 0;
}

