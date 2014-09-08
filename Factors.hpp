
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

#include <iostream>  // for ostream
#include <vector>

/// Factor corresponding to one prime number in a prime factorization. For
/// example, 12 = 2^2*3^1 (where '*' indicates multiplication, and '^'
/// indicates exponentiation) has two such factors:
/// -# 2^2 and
/// -# 3^1.
/// Each such factor has a prime number for the base and a positive exponent.
struct Factor
{
   unsigned prime;     ///< Prime number.
   unsigned exponent;  ///< Positive exponent of prime number.

   /// Initialize.
   /// \param prime     Prime number.
   /// \param exponent  Positive exponent of prime number.
   Factor(unsigned pp = 0, unsigned ee = 1) : prime(pp), exponent(ee) {}
};

/// Print an instance of Factor on an output stream.
/// \param os  Reference to output stream.
/// \param ff  Reference to immutable instance of Factor.
std::ostream& operator<<(std::ostream& os, Factor const& ff);

/// Prime factorization of a positive integer.
struct Factors : public std::vector< Factor >
{
   /// Combine factors fA of a number A, corresponding to the present instance,
   /// with factors fB of a number B to produce a set of factors of A*B. If the
   /// factors in each of fA and fB be sorted from least to greatest, then the
   /// factors is the result will also be sorted from least to greatest.
   ///
   /// \param fB  Factors of a number B.
   /// \return    Factors of A*B, where A corresponds to the present instance.
   Factors operator*(Factors const& fB) const;

   unsigned maxExp() const;  ///< Maximum exponent in factorization.
   unsigned sumExp() const;  ///< Number of atomic prime factors.
};

/// Print an instance of Factors on an output stream.
/// \param os  Reference to output stream.
/// \param ff  Reference to immutable instance of Factors.
std::ostream& operator<<(std::ostream& os, Factors const& ff);

#endif  // ndef FACTORS_HPP

