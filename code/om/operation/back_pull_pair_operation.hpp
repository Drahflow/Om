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

\defgroup om__operation__back_pull_pair_operation__ [pairs]->
	\ingroup om__operation__
	\brief
		Pops the last pair (a non-empty list of zero or one \ref om__operator__ "Operator(s)", followed by zero or one \ref om__operand__ "Operand(s)"), quoted.
	\par Implementation
		Om::Operation::BackPullPairOperation
*/

#ifndef Om_Operation_BackPullPairOperation_

	#define Om_Operation_BackPullPairOperation_ \
	Om::Operation::BackPullPairOperation

	#include "om/system.hpp"

	#define Om_Operation_BackPullPairOperation_GetName_() \
	"[pairs]->"

namespace Om {

	//! \cond
	class Lexicon;
	//! \endcond

	namespace Operation {

		// MARK: - Om::Operation::BackPullPairOperation

		/*!
		\brief
			The \ref om__operation__back_pull_pair_operation__ operation implementation.
		*/
		class BackPullPairOperation {

		public: // MARK: public (static)

			static char const * GetName();

			static void Give(Evaluation &);

			/*!
			\brief
				The callback for PullOperation.
			*/
			template <typename TheConsumer>
			static void Pull(
				Lexicon &,
				TheConsumer &
			);

		};

		namespace {

			static System::Definition<BackPullPairOperation> const theBackPullPairDefinition;

		}

	}

}

	#include "om/operation/back_pull_pair_operation.cpp"

#endif