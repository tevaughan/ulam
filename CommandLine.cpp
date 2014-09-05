
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

#include <cstdlib>  // for exit()
#include "CommandLine.hpp"

using namespace std;

void CommandLine::usage()
{
   cerr << "\nusage:  " << invoc << " [-b <beg>] [-a | -p] -s <size>\n\n"
        << "Draw an Ulam spiral into an image that is sent to the standard\n"
        << "output.\n\n"
        << "-b <beg>   Start with value <beg> at center.\n"
        << "-a         Output an ASCII plot.\n"
        << "-p         Output a PPM image.\n"
        << "-s <size>  Draw spiral in a square of width <size> cells.\n\n"
        << "By default, start with the beginning value 1 at the center, and\n"
        << "decide on the basis of <size> what output format to use. Without\n"
        << "specification of '-a' or '-p', output as an ASCII plot for\n"
        << "<size> smaller than 24; otherwise output a PPM image.\n\n"
        << "If specified, <beg> must be a POSITIVE INTEGER.\n"
        << "<size> MUST be specified and must be a POSITIVE INTEGER.\n"
        << endl;
   exit(-1);
}

CommandLine::CommandLine(int argc, char** argv)
   : invoc(argv[0]), ulamConfig(0)
{
   int opt;
   UlamConfig::OutputType& type = ulamConfig.outputType;
   while ((opt = getopt(argc, argv, "b:aps:")) != -1) {
      switch (opt) {
      case 'b':
         convert(ulamConfig.begin);
         if (ulamConfig.begin < 1) usage();
         break;
      case 'a':
         if (type == UlamConfig::PPM) {
            cerr << "\nCommandLine::CommandLine: ERROR: both output types "
                    "specified" << endl;
            usage();
         }
         type = UlamConfig::ASCII;
         break;
      case 'p':
         if (type == UlamConfig::ASCII) {
            cerr << "\nCommandLine::CommandLine: ERROR: both output types "
                    "specified" << endl;
            usage();
         }
         type = UlamConfig::PPM;
         break;
      case 's':
         convert(ulamConfig.size);
         if (ulamConfig.size < 1) usage();
         break;
      default:
         usage();
      }
   }
   if (ulamConfig.size == 0) usage();
   if (type == UlamConfig::AUTO) {
      type = (ulamConfig.size < 24 ? UlamConfig::ASCII : UlamConfig::PPM);
   }
}

