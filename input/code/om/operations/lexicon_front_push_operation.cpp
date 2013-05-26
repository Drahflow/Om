/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> source file.
	\version
		0.1.3
	\date
		2012-2013
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#ifndef Om_Operations_LexiconFrontPushOperation_

	#include "om/operations/lexicon_front_push_operation.hpp"

	#ifdef Om_Macros_Test_

		#ifndef Om_Macros_Precompilation_

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	namespace Operations {

		BOOST_AUTO_TEST_SUITE(LexiconFrontPushOperationTest)

			BOOST_AUTO_TEST_CASE(DefinitionTest) {
				BOOST_CHECK_EQUAL(
					"{->lexicon}",
					System::Get().Evaluate("drop find {->lexicon} system")
				);
			}

			BOOST_AUTO_TEST_CASE(GeneralTest) {
				BOOST_CHECK_EQUAL(
					"{a{B}}",
					System::Get().Evaluate("->lexicon {a{A}} {a{B}}")
				);

				BOOST_CHECK_EQUAL(
					"{a{B}}",
					System::Get().Evaluate("->lexicon {a} {a{B}}")
				);

				BOOST_CHECK_EQUAL(
					"{a}",
					System::Get().Evaluate("->lexicon {a{A}} {a}")
				);

				BOOST_CHECK_EQUAL(
					(
						"{"
						"a\n"
						"b{C}"
						"}"
					),
					System::Get().Evaluate("->lexicon {a{A}} {a{B} a b{C}}")
				);
			}

		BOOST_AUTO_TEST_SUITE_END()

	}

}

	#endif

#else

	#include "om/lexicon.hpp"
	#include "om/operations/front_push_operation.hpp"

// MARK: - Om::Operations::LexiconFrontPushOperation

	#define Type_ \
	Om::Operations::LexiconFrontPushOperation

// MARK: public (static)

inline char const * Type_::GetName() {
	return Om_Operations_LexiconFrontPushOperation_GetName_();
}

inline void Type_::Give(Evaluation & theEvaluation) {
	theEvaluation.TakeOperation(
		std::auto_ptr<Operation>(
			new FrontPushOperation<
				Lexicon,
				LexiconFrontPushOperation
			>
		)
	);
}

	#undef Type_

#endif