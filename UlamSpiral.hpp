
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

#ifndef ULAM_SPIRAL_HPP
#define ULAM_SPIRAL_HPP

#include "Image.hpp"
#include "UlamConfig.hpp"

/// Image of an Ulam Spiral. The image is stored in a color image. If
/// 'config().outputType' be 'ASCII', then the image is stored only in the red
/// channel and as an ASCII plot.
class UlamSpiral
{
   UlamConfig mConfig;  ///< Configuration for spiral.
   Image mImage;        ///< Image of spiral.

   /// Convert linear position on Ulam spiral to rectangular coordinates. Take
   /// the Linear Position 1 to Rectangular Coordinate (0,0).
   ///
   /// \param[in]  lp  Linear position, such that 1 is the center of the
   ///                 spiral.
   ///
   /// \param[out] col  Column offset from lower-left corner.
   /// \param[out] row  Row offset from lower-left corner.
   void convert(unsigned lp, unsigned& col, unsigned& row);

public:
   /// Draw spiral into memory buffer.
   /// \param config  Configuration for spiral.
   UlamSpiral(UlamConfig const& config);

   /// \return  Configuration for spiral.
   UlamConfig const& config() const { return mConfig; }

   /// \return  Image of spiral.
   Image& image() { return mImage; }
};

#endif  // ndef ULAM_SPIRAL_HPP

