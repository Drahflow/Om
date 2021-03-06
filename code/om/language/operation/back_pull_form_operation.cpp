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

#ifndef Om_Language_Operation_BackPullFormOperation_

	#include "om/language/operation/back_pull_form_operation.hpp"

	#ifdef Om_Macro_Test_

		#include "om/language/system.hpp"

		#ifndef Om_Macro_Precompilation_

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	namespace Language {

		namespace Operation {

			BOOST_AUTO_TEST_SUITE(BackPullFormOperationTest)

				BOOST_AUTO_TEST_CASE(DefinitionTest) {
					BOOST_CHECK_EQUAL(
						"{[forms]->}",
						System::Get().Evaluate("drop find {[forms]->} system")
					);
				}

				BOOST_AUTO_TEST_CASE(GeneralTest) {
					BOOST_CHECK_EQUAL(
						"{4{5}{6}}{1{2}{3}}",
						System::Get().Evaluate("[forms]-> {1{2}{3}4{5}{6}}")
					);

					BOOST_CHECK_EQUAL(
						"{2}{1}",
						System::Get().Evaluate("[forms]-> {1 2}")
					);

					BOOST_CHECK_EQUAL(
						"{}{}",
						System::Get().Evaluate("[forms]-> {}")
					);

					BOOST_CHECK_EQUAL(
						"{only}{}",
						System::Get().Evaluate("[forms]-> {only}")
					);

					BOOST_CHECK_EQUAL(
						"[forms]->",
						System::Get().Evaluate("[forms]->")
					);

					BOOST_CHECK_EQUAL(
						"{a{b}{c}}{}",
						System::Get().Evaluate("[forms]->{a{b}{c}}")
					);
				}

			BOOST_AUTO_TEST_SUITE_END()

		}

	}

}

	#endif

#else

	#include "om/language/expression.hpp"
	#include "om/language/operation/pull_operation.hpp"

// MARK: - Om::Language::Operation::BackPullFormOperation

	#define Type_ \
	Om::Language::Operation::BackPullFormOperation

// MARK: public (static)

inline char const * Type_::GetName() {
	return Om_Language_Operation_BackPullFormOperation_GetName_();
}

inline void Type_::Give(Evaluation & theEvaluation) {
	theEvaluation.TakeOperation(
		std::auto_ptr<IncompleteOperation>(
			new PullOperation<
				Expression,
				BackPullFormOperation
			>
		)
	);
}

template <typename TheConsumer>
inline void Type_::Pull(
	Expression & theExpression,
	TheConsumer & theConsumer
) {
	theExpression.BackGiveForm(theConsumer);
}

	#undef Type_

#endif
