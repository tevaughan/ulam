
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

#ifndef FACTORS_HPP
#define FACTORS_HPP

#include <vector>

/// Factors of a non-negative integer.
struct Factors : public std::vector< unsigned >
{
   /// Combine factors fA of a number A corresponding to the present instance
   /// with factors fB of a number B to produce a set of factors of A*B. If the
   /// factors in each of fA and fB be sorted from least to greatest, then the
   /// factors is the result will also be sorted from least to greatest.
   ///
   /// \param fB  Factors of a number B.
   /// \return    Factors of A*B, where A corresponds to the present instance.
   Factors operator*(Factors const& fB) const;

   /// \return  Number corresponding to present instance and the product of the
   ///          factors stored in the present instance.
   unsigned product() const;
};

#endif  // ndef FACTORS_HPP

