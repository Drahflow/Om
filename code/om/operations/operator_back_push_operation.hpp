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

\defgroup operator_back_push_operation operator<-
	\ingroup operations
	\brief
		Pushes the contents of an \ref operand onto the back of an \ref operator
		(quoted).
	\par Input
		<tt>{A} {B}</tt>
	\par Output
		<tt>{BA}</tt>
	\par Implementation
		Om#Operations#OperatorBackPushOperation
*/
#if !defined( Om_Operations_OperatorBackPushOperation_ )
	#define Om_Operations_OperatorBackPushOperation_ \
	Om::Operations::OperatorBackPushOperation

	#include "om/definition.hpp"

	#define Om_Operations_OperatorBackPushOperation_GetName_() "operator<-"

namespace Om
{
	namespace Operations
	{
		// MARK: - Om::Operations::OperatorBackPushOperation
		/*!
		\brief
			The \ref operator_back_push_operation Operation implementation.
		*/
		struct OperatorBackPushOperation
		{
		public: // MARK: public (static)

			static char const * GetName();

			static void Give( Expansion & );
		};

		namespace
		{
			static Definition<
				OperatorBackPushOperation
			> const theOperatorBackPushDefinition;
		}
	}
}

	#include "om/operations/operator_back_push_operation.cpp"
#endif
