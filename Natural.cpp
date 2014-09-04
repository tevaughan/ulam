
#include <cstdio>    // for printf()
#include <cstdlib>   // for exit()
#include <iostream>  // for cerr

#include "Natural.hpp"

using namespace std;

vector< Natural::Factors > Natural::mFactors;

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

Natural operator*(Natural const& n1, Natural const& n2)
{
   unsigned const n3 = unsigned(n1) * unsigned(n2);
   if (n3 > Natural::mFactors.size()) {
      cerr << "op*(Natural,Natural): product larger than initialized range"
           << endl;
      exit(-1);
   }
   typedef Natural::Factors Factors;
   Factors& f3 = Natural::mFactors[n3 - 1];
   if (n3 > 1 && f3.size() == 0) {
      // Initialize new natural as product of existing naturals.
      Factors const& f1 = n1.factors();
      Factors const& f2 = n2.factors();
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
   }
   return n3;
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
      vector<unsigned>& factors = mFactors[current - 1];
      if (factors.size() == 0) {
         // The current number is prime because its factorization is null.
         primes.push_back(current);
         factors.push_back(current);
      }
      for (unsigned ii = 0; ii < primes.size(); ++ii) {
         Multiple& prime = primes[ii];
         if (prime.mult() <= current && prime.mult() + prime.base() <= max) {
            prime.incFact();
            Natural(prime.base()) * Natural(prime.fact());
         }
      }
      if (factors.size() == 0) {
         cerr << "Natural::init: ERROR: no factors for " << current << endl;
         exit(1);
      }
   }
}

