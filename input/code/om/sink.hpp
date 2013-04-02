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

#ifndef Om_Sink_

	#define Om_Sink_ \
	Om::Sink

namespace Om {

	// MARK: - Om::Sink

	/*!
	\brief
		Any object that items can be pushed to.
	*/
	template <typename ThisItem>
	class Sink {

	public: // MARK: public (non-static)

		virtual ~Sink() = 0;

		/*!
		\brief
			Pushes to the Sink.
		\return
			\c *this
		*/
		Sink & operator =(ThisItem &);

		/*!
		\return
			\c *this
		*/
		Sink & operator *();

		/*!
		\return
			\c this
		*/
		Sink * operator ->();

		/*!
		\brief
			Pushes an item.
		*/
		virtual void Push(ThisItem &) = 0;

	private: // MARK: private (non-static)

		Sink & operator =(Sink const &);

	};

}

	#include "om/sink.cpp"

#endif