/*!
\file
	\brief
		Om cpp file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) Jason Erb.
		All rights reserved.  This program and the accompanying materials are
		made available under the terms of the
		<a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse
		Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/
#if defined( Om_Sinks_DefaultSink_ )

// MARK: Om::Sinks::DefaultSink

	#define Template_ template< \
		typename ThisItem, \
		typename ThisImplementation \
	>

	#define Type_ Om::Sinks::DefaultSink< ThisItem, ThisImplementation >

// MARK: public (non-static)

Template_
inline Type_::~DefaultSink()
{
}

Template_
inline ThisImplementation & Type_::operator ++()
{
	assert( dynamic_cast< ThisImplementation * >( this ) );
	return( static_cast< ThisImplementation & >( *this ) );
}

Template_
inline ThisImplementation Type_::operator ++( int )
{
	assert( dynamic_cast< ThisImplementation * >( this ) );
	return( static_cast< ThisImplementation & >( *this ) );
}

	#undef Type_
	#undef Template_

#else
	#include "om/sinks/default_sink.hpp"
#endif
