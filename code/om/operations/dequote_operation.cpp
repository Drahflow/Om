/*!
\file
	\brief
		Om cpp file.
	\version
		0.1.1
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
#if defined( Om_Operations_DequoteOperation_ )

// MARK: Om::Operations::DequoteOperation

	#define Type_ Om::Operations::DequoteOperation

// MARK: public (static)

inline char const * Type_::GetName()
{
	return( Om_Operations_DequoteOperation_GetName_() );
}

template< typename TheDequoteOperation >
inline void Type_::GiveElements( TheDequoteOperation &, Queue & theQueue )
{
	theQueue.TakeElement( GetOperator() );
}

// MARK: public (non-static)

template< typename TheOperand >
inline bool Type_::TakeOperand(
	Evaluation & theEvaluation,
	TheOperand & theOperand
)
{
	assert( !theOperand.IsEmpty() );
	return( this->TakeQuotedQueue( theEvaluation, *theOperand.GetProgram() ) );
}

template< typename TheQueue >
inline bool Type_::TakeQuotedQueue(
	Evaluation & theEvaluation,
	TheQueue & theQueue
)
{
	theEvaluation.TakeQueue( theQueue );
	return( true );
}

	#undef Type_

#else
	#include "om/operations/dequote_operation.hpp"

	#if defined( Om_Macros_Test_ )

		#include "om/system.hpp"
		#include "UnitTest++.h"

namespace Om
{
	namespace Operations
	{
		// MARK: -
		SUITE( DequoteOperation )
		{
			TEST( Definition )
			{
				CHECK_EQUAL(
					"{dequote}",
					System::Get().Evaluate( "drop find {dequote} system" )
				);
			}

			TEST( Simple )
			{
				CHECK_EQUAL(
					(
						"1{2}\n"
						"3"
					),
					System::Get().Evaluate( "dequote {1{2}3}" )
				);
			}

			TEST( SimpleDequoteThenEvaluate )
			{
				CHECK_EQUAL(
					(
						"A{b}\n"
						"c"
					),
					System::Get().Evaluate( "define {a {A}} {dequote {a{b}c}}" )
				);
			}
		}
	}
}

	#endif

#endif