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

#ifndef Om_Operation_QuoteOperation_

	#define Om_Operation_QuoteOperation_ \
	Om::Operation::QuoteOperation

	#include "om/operation/default_incomplete_operation.hpp"
	#include "om/system.hpp"

	#define Om_Operation_QuoteOperation_GetName_() \
	"quote"

namespace Om {

	namespace Operation {

		// MARK: - Om::Operation::QuoteOperation

		/*!
		\brief
			The \ref om__operation__quote_operation__ operation implementation.
		*/
		class QuoteOperation :
		public DefaultIncompleteOperation<QuoteOperation>
		{

		public: // MARK: public (static)

			static char const * GetName();

			template <typename TheQuoteOperation>
			static void GiveElements(
				TheQuoteOperation &,
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

			static System::Definition<QuoteOperation> const theQuoteDefinition;

		}

	}

}

	#include "om/operation/quote_operation.cpp"

#endif

