
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

#ifndef ULAM_CONFIG_HPP
#define ULAM_CONFIG_HPP

/// Configuration for Ulam spiral.
struct UlamConfig
{
   /// Options for initial direction away from center along spiral.
   enum InitDir {
      RIGHT,  ///< Spiral originates toward right from central point.
      UP,     ///< Spiral originates upward       from central point.
      LEFT,   ///< Spiral originates toward left  from central point.
      DOWN    ///< Spiral originates downward     from central point.
   };

   unsigned size;    ///< Width (pixels) of image containing spiral.
   unsigned begin;   ///< Beginning number at center of spiral.
   bool clockWise;   ///< True only if spiral should be drawn clockwise.
   InitDir initDir;  ///< Initial direction away from center along spiral.

   /// Initialize configuration.
   /// \param ss  Width (pixels) of image containing spiral.
   /// \param bb  Beginning number at center of spiral.
   /// \param cc  True only if sprial should be drawn clockwise.
   /// \param dd  Initial direction away from center along spiral.
   UlamConfig(unsigned ss, unsigned bb = 1, bool cc = false,
              InitDir dd = RIGHT)
      : size(ss), begin(bb), clockWise(cc), initDir(dd)
   {
   }
};

#endif  // ndef ULAM_CONFIG_HPP

