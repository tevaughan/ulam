
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

#include <cmath>     // for sqrt(), log()
#include <cstdlib>   // for exit()
#include <iostream>  // for cerr

#include "Natural.hpp"
#include "UlamSpiral.hpp"

using namespace std;

/// Convert non-central linear position on Ulam spiral to rectangular
/// coordinates.
///
/// \param[in]  lp  Linear position, such that 1 is the center of the spiral.
///                 For convertPositive(), lp must be at least 2.
///
/// \param[out] xx  X coordinate.
/// \param[out] yy  Y coordinate.
void convertPositive(unsigned lp, int& xx, int& yy)
{
   int const mm = int(0.5 * (sqrt(lp) + 1.0));
   int const kk = lp - 4 * mm * (mm - 1);
   if (kk < 1 || kk > 8 * mm) {
      cerr << "convert: ERROR: unexpected kk=" << kk << endl;
      exit(-1);
   } else if (kk <= 2 * mm) {
      xx = mm;
      yy = kk - mm;
   } else if (kk <= 4 * mm) {
      xx = 3 * mm - kk;
      yy = mm;
   } else if (kk <= 6 * mm) {
      xx = -mm;
      yy = 5 * mm - kk;
   } else if (kk <= 8 * mm) {
      xx = kk - 7 * mm;
      yy = -mm;
   }
}

void UlamSpiral::convert(unsigned lp, unsigned& col, unsigned& row)
{
   // convertPositive() implements a model in which lp=0 corresponds to the
   // center of the spiral. The caller of the present function implements the
   // model in which lp=1 corresponds to the center of the spiral.  So
   // decrement the local copy of lp before beginning.
   --lp;
   int xx, yy;
   if (lp == 0) {
      // This might for symmetry be implemented as a function, convertZero().
      xx = yy = 0;
   } else {
      convertPositive(lp, xx, yy);
   }
   unsigned const center = (mConfig.size - 1) / 2;
   col = center + xx;
   row = center + yy;
}

UlamSpiral::UlamSpiral(UlamConfig const& config)
   : mConfig(config), mImage(config.size, config.size)
{
   unsigned const size = mConfig.size;
   unsigned const numNats = size * size + mConfig.begin - 1;
   cerr << "calculating prime factorization for first " << numNats
        << " naturals..." << flush;
   Natural::init(numNats);
   cerr << " done!" << endl;
   unsigned num = mConfig.begin;
   unsigned col, row;
   convert(num - mConfig.begin + 1, col, row);
   while (col < size && row < size) {
      Factors const factors = Natural(num).factors();
      unsigned const nfac = factors.size();
      Pixel& pixel = mImage(col, row);
      float sum = 0.0f;  // Initialize sum of factors.
      switch (mConfig.outputType) {
      case UlamConfig::ASCII:
         pixel.r(nfac == 1 ? '@' : '-');
         break;
      case UlamConfig::PPM:
         switch (nfac) {
         case 0:
            // 1
            break;
         case 1:
            // prime
            pixel.r(1);
            break;
         default:
            // composite
            for (unsigned ii = 0; ii < nfac; ++ii) sum += factors[ii];
            pixel.g(log(*factors.rbegin()));
         }
         break;
      case UlamConfig::AUTO:
         cerr << "UlamSpiral::UlamSpiral: ERROR: outputType=AUTO" << endl;
         exit(-1);
      }
      // Advance to next number, and convert it to column and row coordinates.
      ++num;
      convert(num - mConfig.begin + 1, col, row);
   }
}

