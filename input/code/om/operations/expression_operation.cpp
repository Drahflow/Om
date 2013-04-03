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

#ifndef Om_Operations_ExpressionOperation_

	#include "om/operations/expression_operation.hpp"

	#ifdef Om_Macros_Test_

		#ifndef Om_Macros_Precompilation_

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	namespace Operations {

		BOOST_AUTO_TEST_SUITE(ExpressionOperationTest)

			BOOST_AUTO_TEST_CASE(DefinitionTest) {
				BOOST_CHECK_EQUAL(
					"{expression}",
					System::Get().Evaluate("drop find {expression} system")
				);
			}

			BOOST_AUTO_TEST_CASE(BasicTest) {
				BOOST_CHECK_EQUAL(
					(
						"{"
						"1{2}{5}\n"
						"6{7 {8}}"
						"}"
					),
					System::Get().Evaluate("expression {1{2}{5}6{7 {8}}   }")
				);
			}

		BOOST_AUTO_TEST_SUITE_END()

	}

}

	#endif

#endif
