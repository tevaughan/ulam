
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
   unsigned char c[3];  ///< Red, green, and blue components.

   /// Initialize a single pixel.
   /// \param rr  Value of red component.
   /// \param gg  Value of green component.
   /// \param bb  Value of blue component.
   Pixel(unsigned char rr = 0, unsigned char gg = 0, unsigned char bb = 0)
   {
      c[0] = rr;
      c[1] = gg;
      c[2] = bb;
   }

   unsigned char r() const { return c[0]; }  ///< \return  Red   component.
   unsigned char g() const { return c[1]; }  ///< \return  Green component.
   unsigned char b() const { return c[2]; }  ///< \return  Blue  component.

   /// Set red component.
   /// \param rr  New value for red component.
   void r(unsigned char rr) { c[0] = rr; }

   /// Set green component.
   /// \param gg  New value for green component.
   void g(unsigned char rr) { c[1] = rr; }

   /// Set blue component.
   /// \param bb  New value for blue component.
   void b(unsigned char rr) { c[2] = rr; }
};

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
};

#endif  // ndef IMAGE_HPP

