/*!
\file
	\brief
		Om cpp file.
	\version
		0.1.1
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
#if defined( Om_Move_ )

// MARK: Om

template< typename TheMoveable >
inline std::auto_ptr< TheMoveable > Om::Move( TheMoveable & theMoveable )
{
	return(
		std::auto_ptr< TheMoveable >(
			static_cast< TheMoveable * >( theMoveable.Move() )
		)
	);
}

#else
	#include "om/move.hpp"
#endif