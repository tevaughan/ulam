
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

void Image::normalizePerChannel()
{
   MinMaxPerChannel const minMax(*this);
   float const denR = minMax.maxR - minMax.minR;
   float const denG = minMax.maxG - minMax.minG;
   float const denB = minMax.maxB - minMax.minB;
   float const cR = (denR < FLT_MIN ? 255.0f : 255.0f / denR);
   float const cG = (denG < FLT_MIN ? 255.0f : 255.0f / denG);
   float const cB = (denB < FLT_MIN ? 255.0f : 255.0f / denB);
   unsigned const numPix = mWidth * mHeight;
   for (unsigned ii = 0; ii < numPix; ++ii) {
      Pixel& pixel = mData[ii];
      float const rr = pixel.r();
      float const gg = pixel.g();
      float const bb = pixel.b();
      pixel.r((rr - minMax.minR) * cR);
      pixel.g((gg - minMax.minG) * cG);
      pixel.b((bb - minMax.minB) * cB);
   }
}

void Image::normalize()
{
   MinMaxPerPixel const minMax(*this);
   float const den = minMax.max - minMax.min;
   float const cc = (den < FLT_MIN ? 255.0f : 255.0f / den);
   unsigned const numPix = mWidth * mHeight;
   for (unsigned ii = 0; ii < numPix; ++ii) {
      Pixel& pixel = mData[ii];
      float const rr = pixel.r();
      float const gg = pixel.g();
      float const bb = pixel.b();
      pixel.r((rr - minMax.min) * cc);
      pixel.g((gg - minMax.min) * cc);
      pixel.b((bb - minMax.min) * cc);
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

MinMaxPerChannel::MinMaxPerChannel(Image const& img)
   : minR(+FLT_MAX)
   , minG(+FLT_MAX)
   , minB(+FLT_MAX)
   , maxR(-FLT_MAX)
   , maxG(-FLT_MAX)
   , maxB(-FLT_MAX)
{
   for (unsigned ir = 0; ir < img.height(); ++ir) {
      for (unsigned ic = 0; ic < img.width(); ++ic) {
         Pixel const& pixel = img(ic, ir);
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
   }
}

MinMaxPerPixel::MinMaxPerPixel(Image const& img) : min(+FLT_MAX), max(-FLT_MAX)
{
#define COLOR_DEBUG 1
#if COLOR_DEBUG
   float minR, minG, minB, maxR, maxG, maxB;
   minR = minG = minB = +FLT_MAX;
   maxR = maxG = maxB = -FLT_MAX;
#endif
   for (unsigned ir = 0; ir < img.height(); ++ir) {
      for (unsigned ic = 0; ic < img.width(); ++ic) {
         Pixel const& pixel = img(ic, ir);
         float const rr = pixel.r();
         float const gg = pixel.g();
         float const bb = pixel.b();
         if (rr > max) max = rr;
         if (gg > max) max = gg;
         if (bb > max) max = bb;
         if (rr < min) min = rr;
         if (gg < min) min = gg;
         if (bb < min) min = bb;
#if COLOR_DEBUG
         if (rr > maxR) maxR = rr;
         if (gg > maxG) maxG = gg;
         if (bb > maxB) maxB = bb;
         if (rr < minR) minR = rr;
         if (gg < minG) minG = gg;
         if (bb < minB) minB = bb;
#endif
      }
   }
#if COLOR_DEBUG
   cerr << "minR=" << minR << " minG=" << minG << " minB=" << minB << endl;
   cerr << "maxR=" << maxR << " maxG=" << maxG << " maxB=" << maxB << endl;
#endif
}

