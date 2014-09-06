
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

#include <cstdio>    // for printf()
#include <cstdlib>   // for exit()
#include <iostream>  // for cerr

#include "Natural.hpp"

using namespace std;

vector< Factors > Natural::mFactors;

Natural::Natural(unsigned nn) : mOffset(nn - 1)
{
   if (nn == 0) {
      cerr << "Natural::Natural: Zero is not a natural number." << endl;
      exit(-1);
   }
   if (nn > mFactors.size() || (nn > 1 && mFactors[mOffset].size() == 0)) {
      cerr << "Natural::Natural: " << nn << " not initialized" << endl;
      exit(-1);
   }
}

/// Unsigned multiple of an unsigned base value. The base is fixed at
/// construction, but the factor can be modified.
class Multiple
{
   unsigned mBase;  ///< Base value.
   unsigned mMult;  ///< Multiple (base*factor).
   unsigned mFact;  ///< Factor.

public:
   /// \param bb  Base value.
   /// \param ff  Factor.
   Multiple(unsigned bb = 0, unsigned ff = 1)
      : mBase(bb), mMult(bb * ff), mFact(ff)
   {
   }

   unsigned base() const { return mBase; }  ///< \return  Base value.
   unsigned mult() const { return mMult; }  ///< \return  Multiple (base*fact).
   unsigned fact() const { return mFact; }  ///< \return  Factor.

   /// Set factor.
   /// \param ff  New value for factor.
   void fact(unsigned ff)
   {
      mFact = ff;
      mMult = mBase * ff;
   }

   void incFact() { mMult = mBase * (++mFact); }  ///< Increment factor.
};

void Natural::init(unsigned max)
{
   if (max == 0) {
      cerr << "Natural::init: ERROR: Maximum must be positive." << endl;
      exit(-1);
   }
   mFactors.clear();
   mFactors.resize(max);
   if (max == 1) return;
   vector< Multiple > primes;
   for (unsigned current = 2; current <= max; ++current) {
      vector<Factor>& factors = mFactors[current - 1];
      if (factors.size() == 0) {
         // The current number is prime because its factorization is null.
         primes.push_back(current);
         factors.push_back(current);
      }
      for (unsigned ii = 0; ii < primes.size(); ++ii) {
         Multiple& prime = primes[ii];
         if (prime.mult() <= current && prime.mult() + prime.base() <= max) {
            prime.incFact();
            unsigned const base = prime.base();
            unsigned const fact = prime.fact();
            Factors const& fA = Natural(base).factors();
            Factors const& fB = Natural(fact).factors();
            mFactors[base * fact - 1] = fA * fB;
         }
      }
      if (factors.size() == 0) {
         cerr << "Natural::init: ERROR: no factors for " << current << endl;
         exit(1);
      }
   }
}

