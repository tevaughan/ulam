
#include <iostream>  // for cout

#include "CommandLine.hpp"
#include "Natural.hpp"

using namespace std;

/// Draw an Ulam spiral, and write it out to a PPM file.
///
/// \param argc  Number of arguments (including invokation name) on command
///              line.
///
/// \param argv  Array of strings, each representing a command-line option.
int main(int argc, char** argv)
{
   CommandLine cmdLine(argc, argv);
   unsigned const size = cmdLine.size;
   cout << "calculating prime factorization for first " << size* size
        << " naturals..." << flush;
   Natural::init(size*size);
   cout << " done!" << endl;
   /// TBS: Code that does something useful.
   return 0;
}

