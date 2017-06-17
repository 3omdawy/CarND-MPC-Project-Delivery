// $Id$
# ifndef CPPAD_CPPAD_HPP
# define CPPAD_CPPAD_HPP
/* --------------------------------------------------------------------------
CppAD: C++ Algorithmic Differentiation: Copyright (C) 2003-16 Bradley M. Bell

CppAD is distributed under multiple licenses. This distribution is under
the terms of the
                    Eclipse Public License Version 1.0.

A copy of this license is included in the COPYING file of this distribution.
Please visit http://www.coin-or.org/CppAD/ for information on other licenses.
-------------------------------------------------------------------------- */
/*!
\file cppad.hpp
\brief includes the entire CppAD package in the necessary order.

\namespace CppAD
\brief contains all the variables and functions defined by the CppAD package.
*/

# include "base_require.hpp" // all base type requirements
// ---------------------------------------------------------------------------
// CppAD general purpose library routines (can be included separately)
# include "utility.hpp"
// --------------------------------------------------------------------------
// System routines that can be used by rest of CppAD with out including

# include <cstddef>
# include <iostream>
# include <complex>
# include <cmath>

// ---------------------------------------------------------------------------
// definitions needed by rest of includes

// definitions that come from the installation
# include "configure.hpp"

// definitions that are local to the CppAD include files
# include "core/define.hpp"

// vectors used with CppAD
# include "core/testvector.hpp"

// deprecated vectors used with CppAD
# include "core/test_vector.hpp"

// Declare classes and fucntions that are used before defined
# include "local/declare_ad.hpp"

// ---------------------------------------------------------------------------
// declare the AD<Base> template class

# include "core/ad.hpp"

// ---------------------------------------------------------------------------

# include "core/user_ad.hpp"  // AD class methods available to the user
// tape that tape for AD<Base> acts as a user of Base operations
// so user_ad.hpp must come before op.hpp
# include "local/op.hpp"       // executes taped operations
# include "core/ad_fun.hpp"   // ADFun objects

// ---------------------------------------------------------------------------
// library routines that require the rest of CppAD
# include "core/lu_ratio.hpp"
# include "core/bender_quad.hpp"
# include "core/opt_val_hes.hpp"

// undo definitions in Define.h
# include "core/undef.hpp"

# endif
