/*!
\file
	\brief
		Om hpp file.
	\version
		0.1
	\date
		2012
	\copyright
		Copyright (c) Jason Erb.
		All rights reserved.  This program and the accompanying materials are
		made available under the terms of the
		<a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse
		Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.

\defgroup front_pull_form_operation <-form
	\ingroup operations
	\brief
		Pops the first form (a non-empty list of zero or one
		\ref operator "Operator(s)", followed by zero or more
		\ref operand "Operands"), quoted.
	\par Implementation
		Om#Operations#FrontPullFormOperation
*/
#if !defined( Om_Operations_FrontPullFormOperation_ )
	#define Om_Operations_FrontPullFormOperation_ \
	Om::Operations::FrontPullFormOperation

	#include "om/definition.hpp"

	#define Om_Operations_FrontPullFormOperation_GetName_() "<-form"

namespace Om
{
	//! \cond
	struct Expression;
	//! \endcond

	namespace Operations
	{
		// MARK: - Om::Operations::FrontPullFormOperation
		/*!
		\brief
			The \ref front_pull_form_operation Operation implementation.
		*/
		struct FrontPullFormOperation
		{
		public: // MARK: public (static)

			static char const * GetName();

			static void Give( Evaluation & );

			//! The callback for PullOperation.
			template< typename TheQueue >
			static void Pull( Expression &, TheQueue & );
		};

		namespace
		{
			static Definition<
				FrontPullFormOperation
			> const theFrontPullFormDefinition;
		}
	}
}

	#include "om/operations/front_pull_form_operation.cpp"
#endif
