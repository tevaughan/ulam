
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

#include "Factors.hpp"

Factors Factors::operator*(Factors const& f2) const
{
   Factors f3;  // Return value.
   Factors const& f1 = *this;
   unsigned off1 = 0;  // offset into list of prime factors
   unsigned off2 = 0;  // offset into list of prime factors.
   bool done = false;
   // Combine prime factors into new list; preserve sorting.
   while (!done) {
      int cc = 0;  // case number
      unsigned p1, p2;
      if (off1 < f1.size()) {
         cc += 1;
         p1 = f1[off1];
      }
      if (off2 < f2.size()) {
         cc += 2;
         p2 = f2[off2];
      }
      // Push at most one more prime factor onto new list.
      switch (cc) {
      case 0:
         done = true;  // no more prime factors in either list
         break;
      case 1:
         f3.push_back(p1);
         ++off1;
         break;
      case 2:
         f3.push_back(p2);
         ++off2;
         break;
      case 3:
         // When a factor from each list be available, push the smaller.
         if (p1 < p2) {
            f3.push_back(p1);
            ++off1;
         } else {
            f3.push_back(p2);
            ++off2;
         }
      }
   }
   return f3;
}

unsigned Factors::product() const
{
   unsigned prod = 1;
   for (unsigned ii = 0; ii < size(); ++ii) prod *= (*this)[ii];
   return prod;
}

