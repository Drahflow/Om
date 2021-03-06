/*!
\file
	\brief
		<a href="http://github.com/sparist/Om">Om</a> header file.
	\version
		0.1.3
	\date
		2012-2014
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\author
		Jason Erb
*/

#ifndef Om_Language_Operation_ProgramOperation_

	#define Om_Language_Operation_ProgramOperation_ \
	Om::Language::Operation::ProgramOperation

	#include "om/language/operation/default_incomplete_operation.hpp"

namespace Om {

	namespace Language {

		namespace Operation {

			// MARK: - Om::Language::Operation::ProgramOperation

			/*!
			\brief
				An Operation that normalizes a Program to a specific type.
			*/
			template <typename ThisProgram>
			class ProgramOperation:
			public DefaultIncompleteOperation<
				ProgramOperation<ThisProgram>
			> {

			public: // MARK: public (static)

				static char const * GetName();

				template <typename TheProgramOperation>
				static void GiveElements(
					TheProgramOperation &,
					Consumer &
				);

			public: // MARK: public (non-static)

				virtual bool ParseQuotedElements(
					Evaluation &,
					Reader &
				);

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

		}

	}

}

	#include "om/language/operation/program_operation.cpp"

#endif
