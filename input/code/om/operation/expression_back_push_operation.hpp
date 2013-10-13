/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> header file.
	\version
		0.1.3
	\date
		2012-2013
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#ifndef Om_Operation_ExpressionBackPushOperation_

	#define Om_Operation_ExpressionBackPushOperation_ \
	Om::Operation::ExpressionBackPushOperation

	#include "om/system.hpp"

	#define Om_Operation_ExpressionBackPushOperation_GetName_() \
	"expression<-"

namespace Om {

	namespace Operation {

		// MARK: - Om::Operation::ExpressionBackPushOperation

		/*!
		\brief
			The \ref om__operation__expression_back_push_operation__ operation implementation.
		*/
		class ExpressionBackPushOperation {

		public: // MARK: public (static)

			static char const * GetName();

			static void Give(Evaluation &);

		};

		namespace {

			static System::Definition<ExpressionBackPushOperation> const theExpressionBackPushDefinition;

		}

	}

}

	#include "om/operation/expression_back_push_operation.cpp"

#endif
