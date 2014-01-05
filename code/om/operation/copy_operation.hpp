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

\defgroup om__operation__copy_operation__ copy
	\ingroup om__operation__
	\brief
		Copies an \ref om__operand__.
	\par Input
		<tt>{A}</tt>
	\par Output
		<tt>{A}{A}</tt>
	\par Implementation
		Om::Operation::CopyOperation
*/

#ifndef Om_Operation_CopyOperation_

	#define Om_Operation_CopyOperation_ \
	Om::Operation::CopyOperation

	#include "om/operation/default_incomplete_operation.hpp"
	#include "om/system.hpp"

	#define Om_Operation_CopyOperation_GetName_() \
	"copy"

namespace Om {

	namespace Operation {

		// MARK: - Om::Operation::CopyOperation

		/*!
		\brief
			The \ref om__operation__copy_operation__ operation implementation.
		*/
		class CopyOperation:
		public DefaultIncompleteOperation<CopyOperation> {

		public: // MARK: public (static)

			static char const * GetName();

			template <typename TheCopyOperation>
			static void GiveElements(
				TheCopyOperation &,
				Consumer &
			);

		public: // MARK: public (non-static)

			template <typename TheOperand>
			bool TakeOperand(
				Evaluation &,
				TheOperand &
			);

			template <typename TheProducer>
			bool TakeQuotedProducer(
				Evaluation &,
				TheProducer &
			);

		};

		namespace {

			static System::Definition<CopyOperation> const theCopyDefinition;

		}

	}

}

	#include "om/operation/copy_operation.cpp"

#endif
