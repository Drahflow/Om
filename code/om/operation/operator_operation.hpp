/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> header file.
	\version
		0.1.3
	\date
		2012-2014
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\author
		Jason Erb

\defgroup om__operation__operator_operation__ operator
	\ingroup om__operation__
	\brief
		Normalizes the \ref om__operand__ as a quoted \ref om__operator__.
	\par Implementation
		Om::Operation::OperatorOperation
*/

#ifndef Om_Operation_OperatorOperation_

	#define Om_Operation_OperatorOperation_ \
	Om::Operation::OperatorOperation

	#include "om/operation/program_operation.hpp"
	#include "om/system.hpp"

namespace Om {

	namespace Operation {

		/*!
		\brief
			The \ref om__operation__operator_operation__ operation implementation.
		*/
		typedef ProgramOperation<Operator> OperatorOperation;

		namespace {

			static System::Definition<OperatorOperation> const theOperatorDefinition;

		}

	}

}

#endif
