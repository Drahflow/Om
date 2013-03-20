/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> header file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#ifndef Om_Operations_BackPullCharacterOperation_

	#define Om_Operations_BackPullCharacterOperation_ \
	Om::Operations::BackPullCharacterOperation

	#include "om/system.hpp"

	#define Om_Operations_BackPullCharacterOperation_GetName_() \
	"characters->"

namespace Om {

	namespace Operations {

		// MARK: - Om::Operations::BackPullCharacterOperation

		/*!
		\brief
			The \ref om__operations__back_pull_character_operation__ operation implementation.
		*/
		class BackPullCharacterOperation {

		public: // MARK: public (static)

			static char const * GetName();

			static void Give(Evaluation &);

			/*!
			\brief
				The callback for PullOperation.
			*/
			template <typename TheConsumer>
			static void Pull(
				Operator &,
				TheConsumer &
			);

		};

		namespace {

			static System::Definition<BackPullCharacterOperation> const theBackPullCharacterDefinition;

		}

	}

}

	#include "om/operations/back_pull_character_operation.cpp"

#endif
