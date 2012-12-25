/*!
\file
	\brief
		Om cpp file.
	\version
		0.1
	\date
		2012
	\copyright
		Copyright (c) Jason Erb.
		All rights reserved.  This program and the accompanying materials are
		made available under the terms of the
		<a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse
		Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/
#if defined( Om_Operations_FrontPullPairOperation_ )

	#include "om/lexicon.hpp"
	#include "om/operations/pull_operation.hpp"

// MARK: Om::Operations::FrontPullPairOperation

	#define Type_ Om::Operations::FrontPullPairOperation

// MARK: public (static)

inline char const * Type_::GetName()
{
	return( Om_Operations_FrontPullPairOperation_GetName_() );
}

inline void Type_::Give( Evaluation & theEvaluation )
{
	theEvaluation.TakeOperation(
		std::auto_ptr< Operation >(
			new PullOperation< Lexicon, FrontPullPairOperation >
		)
	);
}

template< typename TheQueue >
inline void Type_::Pull( Lexicon & theLexicon, TheQueue & theQueue )
{
	theLexicon.FrontGivePair( theQueue );
}

	#undef Type_

#else
	#include "om/operations/front_pull_pair_operation.hpp"

	#if defined( Om_Macros_Test_ )

		#include "om/environment.hpp"
		#include "UnitTest++.h"

namespace Om
{
	namespace Operations
	{
		// MARK: -
		SUITE( FrontPullPairOperation )
		{
			TEST( General )
			{
				CHECK_EQUAL(
					"{1{2}}{4{5}}",
					Environment().Evaluate( "<-pairs {1{2}4{5}}" )
				);

				CHECK_EQUAL(
					"{1}{2}",
					Environment().Evaluate( "<-pairs {1 2}" )
				);

				CHECK_EQUAL(
					"{{2}}{}",
					Environment().Evaluate( "<-pairs {{1}{2}}" )
				);

				CHECK_EQUAL(
					"{}{}",
					Environment().Evaluate( "<-pairs {}" )
				);

				CHECK_EQUAL(
					"{only}{}",
					Environment().Evaluate( "<-pairs {only}" )
				);

				CHECK_EQUAL(
					"{a{b}}{{c}}",
					Environment().Evaluate( "<-pairs{a{b}{c}}" )
				);

				CHECK_EQUAL(
					"{{c}}{a{b}}",
					Environment().Evaluate( "<-pairs{{c}a{b}}" )
				);
			}

			TEST( Flush )
			{
				CHECK_EQUAL( "<-pairs", Environment().Evaluate( "<-pairs" ) );
			}
		}
	}
}

	#endif

#endif