
#ifndef NATURAL_HPP
#define NATURAL_HPP

#include <vector>

/// Model of a natural number with associated prime factorization.
///
/// WARNING: This class uses an unprotected static member and cannot be used in
/// a multi-threaded context.
class Natural
{
public:
   /// Type of prime factorization. At least when used by class Natural, each
   /// element in the vector is a prime number in the prime factorization of a
   /// natural number, and the list of primes is sorted, though there may be
   /// repeated values of the same prime as necessary for the factorization.
   typedef std::vector< unsigned > Factors;

private:
   /// Global vector of prime factorizations. The offset into the vector is one
   /// unit smaller than the corresponding natural number, and so the Number 1
   /// corresponds to the first element at Offset 0.
   static std::vector< Factors > mFactors;

   /// For the present instance of Natural, the corresponding offset into the
   /// vector of prime factorizations. The member mOffset is one unit smaller
   /// than the natural number represented by the present instance.
   unsigned mOffset;

public:
   /// Construct a Natural number from an unsigned integer. Issue an error and
   /// exit the program if the corresponding prime factorization be not yet
   /// initialized.
   ///
   /// \param nn  Natural number as unsigned integer; zero is not allowed.
   Natural(unsigned nn);

   /// Automatically convert the present instance into the corresponding
   /// representation as an unsigned integer.
   operator unsigned() const { return mOffset + 1; }

   /// \return  Prime factorization for present instance.
   Factors const& factors() const { return mFactors[mOffset]; }

   /// Multiply two Natural numbers. If the prime factorization of the product
   /// be not yet initialized, then initialize it.
   ///
   /// \param n1  Natural number.
   /// \param n2  Natural number.
   /// \return    Product as a Natural number.
   friend Natural operator*(Natural const& n1, Natural const& n2);

   /// Initialize the prime factorizations up to a limit. Use a modified
   /// version of the Sieve of Eratosthenes.
   ///
   /// \param max  The largest natural number with initialized factorization.
   static void init(unsigned max);
};

#endif  // ndef NATURAL_HPP
