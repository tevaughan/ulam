
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

#include <cmath>     // for sqrt()
#include <cstdlib>   // for exit()
#include <iostream>  // for cerr

#include "Natural.hpp"
#include "UlamSpiral.hpp"

using namespace std;

void convert(unsigned un, int& xx, int& yy)
{
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
   unsigned num = 1;  // eventually mConfig.begin()
   int xx, yy;
   convert(num, xx, yy);
   unsigned col = size/2 + xx;
   unsigned row = size/2 + yy;
   while (col < size && row < size) {
      Natural const nNum(num);
      Pixel& pixel = mImage(col, row);
      pixel.r(nNum.factors().size() == 1 ? 1 : 0);
      pixel.g(nNum.factors().size());
      ++num;
      convert(num, xx, yy);
      col = size/2 + xx;
      row = size/2 + yy;
   }
   mImage.writePpm();
}

