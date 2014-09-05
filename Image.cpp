
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

#include <cfloat>    // for FLT_MAX
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
   float maxR = -FLT_MAX, maxG = -FLT_MAX, maxB = -FLT_MAX;
   float minR = +FLT_MAX, minG = +FLT_MAX, minB = +FLT_MAX;
   for (unsigned ii = 0; ii < numPix; ++ii) {
      Pixel const& pixel = mData[ii];
      float const rr = pixel.r();
      float const gg = pixel.g();
      float const bb = pixel.b();
      if (rr > maxR) maxR = rr;
      if (gg > maxG) maxG = gg;
      if (bb > maxB) maxB = bb;
      if (rr < minR) minR = rr;
      if (gg < minG) minG = gg;
      if (bb < minB) minB = bb;
   }
   float denR = maxR - minR;
   float denG = maxG - minG;
   float denB = maxB - minB;
   if (denR < FLT_MIN) denR = 1.0f;
   if (denG < FLT_MIN) denG = 1.0f;
   if (denB < FLT_MIN) denB = 1.0f;
   for (unsigned ii = 0; ii < numPix; ++ii) {
      Pixel& pixel = mData[ii];
      float const rr = pixel.r();
      float const gg = pixel.g();
      float const bb = pixel.b();
      pixel.r((rr - minR)*255.0/denR);
      pixel.g((gg - minG)*255.0/denG);
      pixel.b((bb - minB)*255.0/denB);
   }
}

void Image::writePpm()
{
   normalize();
   cout << "P6\n" << mWidth << " " << mHeight << "\n255\n";
   unsigned const numPix = mWidth * mHeight;
   for (unsigned ii = 0; ii < numPix; ++ii) {
      Pixel const& pixel = mData[ii];
      cout.put(unsigned(pixel.r() + 0.5) & 0xFF);
      cout.put(unsigned(pixel.g() + 0.5) & 0xFF);
      cout.put(unsigned(pixel.b() + 0.5) & 0xFF);
   }
}

void Image::writeAscii(int chan) const
{
   if (chan < 0 || chan > 2) {
      cerr << "Image::writeAscii: ERROR: illegal Channel " << chan << endl;
      exit(-1);
   }
   int off = -1;
   for (unsigned row = 0; row < mHeight; ++row) {
      for (unsigned col = 0; col < mWidth; ++col) {
         cout << " " << char(unsigned(mData[++off].c[chan] + 0.5) & 0xFF);
      }
      cout << "\n";
   }
}

