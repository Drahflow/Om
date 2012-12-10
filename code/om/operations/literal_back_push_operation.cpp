/*!
\file
	\brief
		Om cpp file.
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
*/
#if defined( Om_Operations_LiteralBackPushOperation_ )

	#include "om/operations/literal_front_push_operation.hpp"
	#include "om/operations/swap_operation.hpp"

// MARK: Om::Operations::LiteralBackPushOperation

	#define Type_ Om::Operations::LiteralBackPushOperation

// MARK: public (static)

inline char const * Type_::GetName()
{
	return( Om_Operations_LiteralBackPushOperation_GetName_() );
}

inline void Type_::Give( Expansion & theExpansion )
{
	LiteralFrontPushOperation::Give( theExpansion );
	SwapOperation::Give( theExpansion );
}

	#undef Type_

#else
	#include "om/operations/literal_back_push_operation.hpp"
#endif
