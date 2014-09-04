
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
   cerr << "\nusage:  " << invoc
        << " [-b <beg>] [-c] [-d | -l | -u] -s <size>\n\n"
        << "Draw an Ulam spiral into a PPM image that is sent to the\n"
        << "standard output.\n\n"
        << "-b <beg>   Start with value <beg> at center.\n"
        << "-c         Draw clockwise.\n"
        << "-d         Move first downward.\n"
        << "-l         Move first to the left.\n"
        << "-u         Move first upward.\n"
        << "-s <size>  Draw spiral of width <size> cells.\n\n"
        << "By default, start with the beginning value 1 at the center, draw\n"
        << "counter-clockwise, and move first to the right.\n\n"
        << "If specified, <beg> must be a POSITIVE INTEGER.\n"
        << "Only ONE of the directions may be specified.\n"
        << "<size> MUST be specified and must be a POSITIVE INTEGER.\n"
        << endl;
   exit(-1);
}

CommandLine::CommandLine(int argc, char** argv)
   : invoc(argv[0]), begin(1), size(0), clockWise(false), initDir(RIGHT)
{
   int opt;
   while ((opt = getopt(argc, argv, "b:cdls:u")) != -1) {
      switch (opt) {
      case 'b':
         convert(begin);
         if (begin < 1) usage();
         break;
      case 'c':
         clockWise = true;
         break;
      case 'd':
         if (initDir != RIGHT && initDir != DOWN) {
            cerr << "\nCommandLine::CommandLine: ERROR: more than one "
                    "initial direction specified" << endl;
            usage();
         }
         initDir = DOWN;
         break;
      case 'l':
         if (initDir != RIGHT && initDir != LEFT) {
            cerr << "\nCommandLine::CommandLine: ERROR: more than one "
                    "initial direction specified" << endl;
            usage();
         }
         initDir = LEFT;
         break;
      case 'u':
         if (initDir != RIGHT && initDir != UP) {
            cerr << "\nCommandLine::CommandLine: ERROR: more than one "
                    "initial direction specified" << endl;
            usage();
         }
         initDir = UP;
         break;
      case 's':
         convert(size);
         if (size < 1) usage();
         break;
      default:
         usage();
      }
   }
   if (size == 0) usage();
}

