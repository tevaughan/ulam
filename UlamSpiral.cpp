
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

/// Convert linear position on Ulam spiral to rectangular coordinates. Take the
/// Linear Position 1 to Rectangular Coordinate (0,0).
///
/// \param[in]  un  Linear position, such that 1 is the center of the spiral.
/// \param[out] xx  X coordinate.
/// \param[out] yy  Y coordinate.
void convert(unsigned un, int& xx, int& yy)
{
   // Code below takes un=0 -> (xx,yy)=(0,0), but smallest input will be un=1.
   // So decrement un before beginning.
   --un;
   if (un == 0) {
      xx = yy = 0;
      return;
   }
   int const mm = int(0.5 * (sqrt(un) + 1.0));
   int const kk = un - 4 * mm * (mm - 1);
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

UlamSpiral::UlamSpiral(UlamConfig const& config)
   : mConfig(config), mImage(config.size, config.size)
{
   unsigned const size = mConfig.size;
   cerr << "calculating prime factorization for first " << (size * size)
        << " naturals..." << flush;
   Natural::init(size * size);
   cerr << " done!" << endl;
#if 0
   for (unsigned ii = 1; ii <= size * size; ++ii ) {
      printf("%10u ", ii);
      Factors const& ff = Natural(ii).factors();
      if (ff.size() == 1) {
         printf("prime\n");
      } else if (ff.size() > 1) {
         printf("= ");
         for (unsigned jj = 0; jj < ff.size(); ++jj) {
            if (jj > 0) printf("*");
            printf("%u", ff[jj]);
         }
         printf("\n");
      } else if(ii > 1) {
         cerr << "UlamSpiral::UlamSpiral: ERROR: no factors" << endl;
         exit(-1);
      } else {
         printf("\n");
      }
   }
#endif
   unsigned num = 1;  // eventually mConfig.begin()
   int xx, yy;
   convert(num, xx, yy);
   unsigned col = size / 2 + xx;
   unsigned row = size / 2 + yy;
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
      convert(num, xx, yy);
      col = size / 2 + xx;
      row = size / 2 + yy;
   }
}

