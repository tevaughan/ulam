
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
   unsigned size;   ///< Width (pixels) of image containing spiral.
   unsigned begin;  ///< Beginning number at center of spiral.

   /// Options for type of output.
   enum OutputType {
      ASCII,  ///< Output as an ASCII plot.
      PPM,    ///< Output as a PPM image.
      AUTO    ///< Output as ASCII for size < 20; otherwise as PPM.
   };
   
   OutputType outputType;  ///< Type of output.

   /// Initialize configuration.
   /// \param ss  Width (pixels) of image containing spiral.
   /// \param bb  Beginning number at center of spiral.
   /// \param ot  Type of output.
   UlamConfig(unsigned ss, unsigned bb = 1, OutputType ot = AUTO)
      : size(ss), begin(bb), outputType(ot)
   {
   }
};

#endif  // ndef ULAM_CONFIG_HPP

