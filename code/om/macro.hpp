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

#ifndef Om_Macro_

	#ifndef Om_Macro_Precompilation_

		#include "boost/preprocessor/stringize.hpp"

	#endif

	/*!
	\brief
		Defines a namespace for all global macros, aside from include guards.

	All global preprocessor definitions (excluding include guards) should use this namespace to avoid clashes, regardless of where they are physically defined.
	*/
	#define Om_Macro_ \
	Om::Macro

	/*!
	\brief
		Prepends <code>0x</code>.
	*/
	#define Om_Macro_PrependZeroX_(theArgument) \
	0x ##theArgument

	/*!
	\brief
		Prepends <code>\\x</code> and converts the result to a string literal.
	*/
	#define Om_Macro_PrependSlashXAndStringize_(theArgument) \
	BOOST_PP_STRINGIZE(\x ##theArgument)

	/*!
	\brief
		Converts a bare hexadecimal to a numeric literal.
	*/
	#define Om_Macro_GetNumber_(theHex) \
	Om_Macro_PrependZeroX_(theHex)

	/*!
	\brief
		Converts a bare hexadecimal to a string literal.
	*/
	#define Om_Macro_GetString_(theHex) \
	Om_Macro_PrependSlashXAndStringize_(theHex)

namespace Om {

	/*!
	\brief
		A namespace for all code used to implement global macros.
	*/
	namespace Macro {}

}

#endif
