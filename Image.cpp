
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

void Image::normalize()
{
   unsigned const numPix = mWidth * mHeight;
   unsigned maxR = 0, maxG = 0, maxB = 0;
   unsigned minR = 255, minG = 255, minB = 255;
   for (unsigned ii = 0; ii < numPix; ++ii) {
      Pixel const& pixel = mData[ii];
      unsigned const rr = pixel.r();
      unsigned const gg = pixel.g();
      unsigned const bb = pixel.b();
      if (rr > maxR) maxR = rr;
      if (gg > maxG) maxG = gg;
      if (bb > maxB) maxB = bb;
      if (rr < minR) minR = rr;
      if (gg < minG) minG = gg;
      if (bb < minB) minB = bb;
   }
   unsigned denR = maxR - minR;
   unsigned denG = maxG - minG;
   unsigned denB = maxB - minB;
   if (denR == 0) denR = 1;
   if (denG == 0) denG = 1;
   if (denB == 0) denB = 1;
   for (unsigned ii = 0; ii < numPix; ++ii) {
      Pixel& pixel = mData[ii];
      unsigned const rr = pixel.r();
      unsigned const gg = pixel.g();
      unsigned const bb = pixel.b();
      pixel.r(unsigned((rr - minR)*255.0/denR + 0.5) & 0xFF);
      pixel.g(unsigned((gg - minG)*255.0/denG + 0.5) & 0xFF);
      pixel.b(unsigned((bb - minB)*255.0/denB + 0.5) & 0xFF);
   }
}

void Image::writePpm()
{
   normalize();
   cout << "P6\n" << mWidth << " " << mHeight << "\n255\n";
   unsigned const numPix = mWidth * mHeight;
   for (unsigned ii = 0; ii < numPix; ++ii) {
      Pixel const& pixel = mData[ii];
      cout.put(pixel.r());
      cout.put(pixel.g());
      cout.put(pixel.b());
   }
}

