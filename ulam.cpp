
#include <cstdlib>   // for exit()
#include <iostream>  // for cout, cerr
#include <sstream>   // for istringstream
#include <unistd.h>  // for getopt()

using namespace std;

struct CommandLine
{
   char* invoc;
   int begin;
   int size;
   bool clockWise;
   enum InitDir { RIGHT, UP, LEFT, DOWN } initDir;

   void usage()
   {
      cerr << "\nusage:  " << invoc
           << " [-b <beg>] [-c] [-d | -l | -u] -s <size>\n\n"
           << "Draw an Ulam spiral.\n\n"
           << "By default, start with the beginning value 1 at the center, \n"
           << "move first to the right, and draw counter-clockwise.\n\n"
           << "The size is a REQUIRED option.\n"
           << "If specified, <beg> must be a POSITIVE INTEGER.\n"
           << "Only ONE of the directions may be specified.\n"
           << "The <size> parameter must be a POSITIVE INTEGER.\n\n"
           << "-b <beg>   Start with value <beg> at center.\n"
           << "-c         Draw clockwise.\n"
           << "-d         Move first downward.\n"
           << "-l         Move first to the left.\n"
           << "-u         Move first upward.\n"
           << "-s <size>  Draw spiral of width <size> cells.\n"
           << endl;
      exit(-1);
   }

   template< typename TT >
   void convert(TT& arg)
   {
      istringstream iss(optarg);
      if (!(iss >> arg)) {
         cerr << "CommandLine::convert: ERROR converting '" << optarg << "'"
              << endl;
         usage();
      }
   }

   CommandLine(int argc, char** argv)
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
               cerr << "CommandLine::CommandLine: ERROR: more than one "
                       "initial direction specified" << endl;
               usage();
            }
            initDir = DOWN;
            break;
         case 'l':
            if (initDir != RIGHT && initDir != LEFT) {
               cerr << "CommandLine::CommandLine: ERROR: more than one "
                       "initial direction specified" << endl;
               usage();
            }
            initDir = LEFT;
            break;
         case 'u':
            if (initDir != RIGHT && initDir != UP) {
               cerr << "CommandLine::CommandLine: ERROR: more than one "
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
};

int main(int argc, char** argv)
{
   CommandLine cmdLine(argc, argv);
   return 0;
}

