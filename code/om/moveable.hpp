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

#ifndef Om_Moveable_

	#define Om_Moveable_ \
	Om::Moveable

	#ifndef Om_Macro_Precompilation_

		#include <memory>

	#endif

namespace Om {

	// MARK: - Om::Moveable

	/*!
	\brief
		An object that can be passed to #Move to be moved.
	*/
	class Moveable {

		template <typename TheMoveable>
		friend std::auto_ptr<TheMoveable> Move(TheMoveable &);

	public: // MARK: public (non-static)

		virtual ~Moveable() = 0;

		/*!
		\return
			An owner pointer to a moved object.
		*/
		virtual std::auto_ptr<Moveable> Move() = 0;

	private: // MARK: private (non-static)

		Moveable & operator =(Moveable const &);

	};

	// MARK: - Om::

	/*!
	\return
		A polymorphic move of the object.
	*/
	template <typename TheMoveable>
	std::auto_ptr<TheMoveable> Move(TheMoveable &);

}

	#include "om/moveable.cpp"

#endif
