
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

#include <cstdlib>   // for exit()
#include <iostream>  // for cerr

#include "Image.hpp"

using namespace std;

Image::Image(unsigned ww, unsigned hh)
   : mData(new Pixel[ww * hh]), mWidth(ww), mHeight(hh)
{
   if (!mData) {
      cerr << "Image::Image: ERROR allocating memory for image" << endl;
      exit(-1);
   }
}

