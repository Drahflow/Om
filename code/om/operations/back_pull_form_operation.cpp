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
#if defined( Om_Operations_BackPullFormOperation_ )

	#include "om/expression.hpp"
	#include "om/operations/pull_operation.hpp"

// MARK: Om::Operations::BackPullFormOperation

	#define Type_ Om::Operations::BackPullFormOperation

// MARK: public (static)

inline char const * Type_::GetName()
{
	return( Om_Operations_BackPullFormOperation_GetName_() );
}

inline void Type_::Give( Evaluation & theEvaluation )
{
	theEvaluation.TakeOperation(
		std::auto_ptr< Operation >(
			new PullOperation< Expression, BackPullFormOperation >
		)
	);
}

template< typename TheQueue >
inline void Type_::Pull( Expression & theExpression, TheQueue & theQueue )
{
	theExpression.BackGiveForm( theQueue );
}

	#undef Type_

#else
	#include "om/operations/back_pull_form_operation.hpp"

	#if defined( Om_Macros_Test_ )

		#include "om/environment.hpp"
		#include "UnitTest++.h"

namespace Om
{
	namespace Operations
	{
		// MARK: -
		SUITE( BackPullFormOperation )
		{
			TEST( General )
			{
				CHECK_EQUAL(
					"{4{5}{6}}{1{2}{3}}",
					Environment().Evaluate( "forms-> {1{2}{3}4{5}{6}}" )
				);

				CHECK_EQUAL(
					"{2}{1}",
					Environment().Evaluate( "forms-> {1 2}" )
				);

				CHECK_EQUAL(
					"{}{}",
					Environment().Evaluate( "forms-> {}" )
				);

				CHECK_EQUAL(
					"{only}{}",
					Environment().Evaluate( "forms-> {only}" )
				);

				// Flush
				CHECK_EQUAL(
					"forms->",
					Environment().Evaluate( "forms->" )
				);

				CHECK_EQUAL(
					"{a{b}{c}}{}",
					Environment().Evaluate( "forms->{a{b}{c}}" )
				);
			}
		}
	}
}

	#endif

#endif