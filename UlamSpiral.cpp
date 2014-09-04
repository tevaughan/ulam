
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

#include <iostream>  // for cout

#include "Natural.hpp"
#include "UlamSpiral.hpp"

using namespace std;

UlamSpiral::UlamSpiral(UlamConfig const& config)
   : mConfig(config), mImage(config.size, config.size)
{
   unsigned const size = mConfig.size;
   cout << "calculating prime factorization for first " << (size * size)
        << " naturals..." << flush;
   Natural::init(size * size);
   cout << " done!" << endl;
}

