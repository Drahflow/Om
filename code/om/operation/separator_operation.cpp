/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> source file.
	\version
		0.1.3
	\date
		2012-2014
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\author
		Jason Erb
*/

#ifndef Om_Operation_SeparatorOperation_

	#include "om/operation/separator_operation.hpp"

	#ifdef Om_Macro_Test_

		#ifndef Om_Macro_Precompilation_

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	namespace Operation {

		BOOST_AUTO_TEST_SUITE(SeparatorOperationTest)

			BOOST_AUTO_TEST_CASE(DefinitionTest) {
				BOOST_CHECK_EQUAL(
					"{separator}",
					System::Get().Evaluate("drop find {separator} system")
				);
			}

			BOOST_AUTO_TEST_CASE(GeneralTest) {
				BOOST_CHECK_EQUAL(
					"{}",
					System::Get().Evaluate("separator{}")
				);

				BOOST_CHECK_EQUAL(
					"{ \n\t }",
					System::Get().Evaluate("separator{ \n\t }")
				);

				BOOST_CHECK_EQUAL(
					"{   \n\t   }",
					System::Get().Evaluate("separator{ a {b} \n\t {c} d }")
				);

				BOOST_CHECK_EQUAL(
					"{   \n\t   }",
					System::Get().Evaluate("drop swap separator copy{ a {b} \n\t {c} d }")
				);
			}

		BOOST_AUTO_TEST_SUITE_END()

	}

}

	#endif

#endif
