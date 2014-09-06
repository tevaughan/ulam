
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

using namespace std;

ostream& operator<<(ostream& os, Factor const& ff)
{
   os << ff.prime;
   if (ff.exponent > 1) os << "^" << ff.exponent;
   return os;
}

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
      Factor t1, t2;
      if (off1 < f1.size()) {
         cc += 1;
         t1 = f1[off1];
      }
      if (off2 < f2.size()) {
         cc += 2;
         t2 = f2[off2];
      }
      // Push at most one more prime factor onto new list.
      switch (cc) {
      case 0:
         done = true;  // no more prime factors in either list
         break;
      case 1:
         f3.push_back(t1);
         ++off1;
         break;
      case 2:
         f3.push_back(t2);
         ++off2;
         break;
      case 3:
         // When a factor from each list be available, and when the prime base
         // of one be smaller than that of the other, push the factor with the
         // smaller base. Otherwise, when the bases be equal, push them both.
         if (t1.prime < t2.prime) {
            f3.push_back(t1);
            ++off1;
         } else if (t1.prime > t2.prime) {
            f3.push_back(t2);
            ++off2;
         } else {
            f3.push_back(Factor(t1.prime, t1.exponent + t2.exponent));
            ++off1;
            ++off2;
         }
      }
   }
   return f3;
}

ostream& operator<<(ostream& os, Factors const& ff)
{
   if (ff.size() == 0) return os << 1;
   for (unsigned ii = 0; ii < ff.size(); ++ii) {
      if (ii > 0) os << "*";
      os << ff[ii];
   }
   return os;
}

