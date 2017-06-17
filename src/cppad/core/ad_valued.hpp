// $Id$
# ifndef CPPAD_CORE_AD_VALUED_HPP
# define CPPAD_CORE_AD_VALUED_HPP

/* --------------------------------------------------------------------------
CppAD: C++ Algorithmic Differentiation: Copyright (C) 2003-16 Bradley M. Bell

CppAD is distributed under multiple licenses. This distribution is under
the terms of the
                    Eclipse Public License Version 1.0.

A copy of this license is included in the COPYING file of this distribution.
Please visit http://www.coin-or.org/CppAD/ for information on other licenses.
-------------------------------------------------------------------------- */

/*
$begin ADValued$$
$spell
$$


$section AD Valued Operations and Functions$$

$comment atomic.omh includes atomic_base.omh which atomic_base.hpp$$
$childtable%
	cppad/core/arithmetic.hpp%
	cppad/core/standard_math.hpp%
	cppad/core/cond_exp.hpp%
	cppad/core/discrete.hpp%
	cppad/core/numeric_limits.hpp%
	omh/atomic.omh
%$$

$end
*/

// include MathOther.h after CondExp.h because some MathOther.h routines use
// CondExp.h and CondExp.h is not sufficently declared in Declare.h

# include "core/arithmetic.hpp"
# include "core/standard_math.hpp"
# include "core/azmul.hpp"
# include "core/cond_exp.hpp"
# include "core/discrete.hpp"
# include "core/atomic_base.hpp"
# include "core/checkpoint.hpp"
# include "core/old_atomic.hpp"

# endif
