
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

#ifndef IMAGE_HPP
#define IMAGE_HPP

/// Color components of a pixel.
struct Pixel
{
   float c[3];  ///< Red, green, and blue components.

   /// Initialize a single pixel.
   /// \param rr  Value of red component.
   /// \param gg  Value of green component.
   /// \param bb  Value of blue component.
   Pixel(float rr = 0, float gg = 0, float bb = 0)
   {
      c[0] = rr;
      c[1] = gg;
      c[2] = bb;
   }

   float r() const { return c[0]; }  ///< \return  Red   component.
   float g() const { return c[1]; }  ///< \return  Green component.
   float b() const { return c[2]; }  ///< \return  Blue  component.

   /// Set red component.
   /// \param rr  New value for red component.
   void r(float rr) { c[0] = rr; }

   /// Set green component.
   /// \param gg  New value for green component.
   void g(float rr) { c[1] = rr; }

   /// Set blue component.
   /// \param bb  New value for blue component.
   void b(float rr) { c[2] = rr; }
};

/// Color image.
class Image
{
   Pixel* mData;                    ///< Storage for pixel data.
   unsigned mWidth;                 ///< Width (pixels) of image.
   unsigned mHeight;                ///< Height (pixels) of image.
   Image(Image const&);             ///< Disable default copying.
   Image& operator=(Image const&);  ///< Disable default assignment.

public:
   /// Allocate memory and initialize to black.
   /// \param ww  Width  (pixels) of image.
   /// \param hh  Height (pixels) of image.
   Image(unsigned ww, unsigned hh);

   /// Deallocate memory.
   ~Image()
   {
      if (mData) delete[] mData;
   }

   unsigned width() const { return mWidth; }
   unsigned height() const { return mHeight; }

   /// Select a pixel by column and row such that (col,row) = (0,0) is at the
   /// lower-left corner of the window.
   ///
   /// \param cc  Column offset of pixel.
   /// \param rr  Row    offset of pixel.
   /// \return    Reference to immutable pixel.
   Pixel const& operator()(unsigned cc, unsigned rr) const
   {
      return mData[cc + (mHeight - 1 - rr)*mWidth];
   }

   /// Select a pixel by column and row such that (col,row) = (0,0) is at the
   /// lower-left corner of the window.
   ///
   /// \param cc  Column offset of pixel.
   /// \param rr  Row    offset of pixel.
   /// \return    Reference to pixel.
   Pixel& operator()(unsigned cc, unsigned rr)
   {
      return mData[cc + (mHeight - 1 - rr)*mWidth];
   }

   /// Scale each color component so that the minimum for the component is 0,
   /// and the maximum for the component is 255.
   void normalizePerChannel();

   void normalize();

   void writePpm();  ///< Write PPM file to standard output.

   /// Write one of the color channels to standard output as an ASCII plot.
   /// This should be called if terminal-printable characters were encoded into
   /// the channel's data.
   ///
   /// \param channel  Color channel to print. Red is Channel 0; green,
   ///                 Channel 1; and blue, Channel 2.
   void writeAscii(int channel) const;
};

struct MinMaxPerChannel
{
   float minR;
   float minG;
   float minB;
   float maxR;
   float maxG;
   float maxB;

   MinMaxPerChannel(Image const& img);
};

struct MinMaxPerPixel
{
   float min;
   float max;

   MinMaxPerPixel(Image const& img);
};

#endif  // ndef IMAGE_HPP

