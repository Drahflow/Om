/*!
\file
	\brief
		<a href="http://github.com/sparist/Om">Om</a> source file.
	\version
		0.1.3
	\date
		2012-2014
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\author
		Jason Erb
*/

#ifndef Om_Language_Operation_FrontPullCharacterOperation_

	#include "om/language/operation/front_pull_character_operation.hpp"

	#ifdef Om_Macro_Test_

		#ifndef Om_Macro_Precompilation_

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	namespace Language {

		namespace Operation {

			BOOST_AUTO_TEST_SUITE(FrontPullCharacterOperationTest)

				BOOST_AUTO_TEST_CASE(DefinitionTest) {
					BOOST_CHECK_EQUAL(
						"{<-[characters]}",
						System::Get().Evaluate("drop find {<-[characters]} system")
					);
				}

				BOOST_AUTO_TEST_CASE(GeneralTest) {
					BOOST_CHECK_EQUAL(
						"{1}{`{2`}three}",
						System::Get().Evaluate("<-[characters] {1{2}three}")
					);

					BOOST_CHECK_EQUAL(
						"{` }{}",
						System::Get().Evaluate("<-[characters] {` }")
					);

					BOOST_CHECK_EQUAL(
						(
							"{"
							"\xC3\x98"
							"\xCC\x81"
							"}{a}"
						),
						System::Get().Evaluate(
							"<-[characters] {"
							"\xC7\xBE"
							"a}"
						)
					);

					BOOST_CHECK_EQUAL(
						"{` }{}",
						System::Get().Evaluate("<-[characters] { }")
					);

					BOOST_CHECK_EQUAL(
						"{}{}",
						System::Get().Evaluate("<-[characters] {}")
					);

					BOOST_CHECK_EQUAL(
						"<-[characters]",
						System::Get().Evaluate("<-[characters]")
					);
				}

				BOOST_AUTO_TEST_CASE(MultiCodePointCharacterTest) {
					BOOST_CHECK_EQUAL(
						(
							"{"
							"\xE1\x84\x80"
							"\xE1\x85\xA1"
							"}{"
							"\xE1\x84\x82"
							"}"
						),
						System::Get().Evaluate(
							"<-[characters]"
							"{"
							"\xE1\x84\x80"
							"\xE1\x85\xA1"
							"\xE1\x84\x82"
							"}"
						)
					);
				}

			BOOST_AUTO_TEST_SUITE_END()

		}

	}

}

	#endif

#else

	#include "om/language/operation/pull_operation.hpp"

// MARK: - Om::Language::Operation::FrontPullCharacterOperation

	#define Type_ \
	Om::Language::Operation::FrontPullCharacterOperation

// MARK: public (static)

inline char const * Type_::GetName() {
	return Om_Language_Operation_FrontPullCharacterOperation_GetName_();
}

inline void Type_::Give(Evaluation & theEvaluation) {
	theEvaluation.TakeOperation(
		std::auto_ptr<IncompleteOperation>(
			new PullOperation<
				Operator,
				FrontPullCharacterOperation
			>
		)
	);
}

template <typename TheConsumer>
inline void Type_::Pull(
	Operator & theOperator,
	TheConsumer & theConsumer
) {
	theOperator.FrontGiveSegment<boost::locale::boundary::character>(theConsumer);
}

	#undef Type_

#endif
