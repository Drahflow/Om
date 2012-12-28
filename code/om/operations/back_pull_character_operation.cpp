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
#if defined( Om_Operations_BackPullCharacterOperation_ )

	#include "om/operations/pull_operation.hpp"

// MARK: Om::Operations::BackPullCharacterOperation

	#define Type_ Om::Operations::BackPullCharacterOperation

// MARK: public (static)

inline char const * Type_::GetName()
{
	return( Om_Operations_BackPullCharacterOperation_GetName_() );
}

inline void Type_::Give( Evaluation & theEvaluation )
{
	theEvaluation.TakeOperation(
		std::auto_ptr< Operation >(
			new PullOperation< Operator, BackPullCharacterOperation >
		)
	);
}

template< typename TheQueue >
inline void Type_::Pull( Operator & theOperator, TheQueue & theQueue )
{
	theOperator.BackGiveSegment< boost::locale::boundary::character >(
		theQueue
	);
}

	#undef Type_

#else
	#include "om/operations/back_pull_character_operation.hpp"

	#if defined( Om_Macros_Test_ )

		#include "om/system.hpp"
		#include "UnitTest++.h"

namespace Om
{
	namespace Operations
	{
		// MARK: -
		SUITE( BackPullCharacterOperation )
		{
			TEST( General )
			{
				CHECK_EQUAL(
					"{e}{1`{2`}thre}",
					System::Get().Evaluate( "character-> {1{2}three}" )
				);

				CHECK_EQUAL(
					"{` }{}",
					System::Get().Evaluate( "character-> {` }" )
				);

				CHECK_EQUAL(
					"{" "\xC3\x98" "\xCC\x81" "}{a}",
					System::Get().Evaluate( "character-> {a" "\xC7\xBE" "}" )
				);

				CHECK_EQUAL(
					"{` }{}",
					System::Get().Evaluate( "character-> { }" )
				);

				CHECK_EQUAL(
					"{}{}",
					System::Get().Evaluate( "character-> {}" )
				);

				CHECK_EQUAL(
					"character->",
					System::Get().Evaluate( "character->" )
				);
			}

			TEST( MultiCodePointCharacter )
			{
				CHECK_EQUAL(
					(
						"{"
							"\xE1\x84\x80" "\xE1\x85\xA1"
						"}{" "\xE1\x86\xAB" "}"
					),
					System::Get().Evaluate(
						"character->"
						"{" "\xE1\x86\xAB" "\xE1\x84\x80" "\xE1\x85\xA1" "}"
					)
				);
			}
		}
	}
}

	#endif

#endif
