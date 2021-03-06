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

#ifndef Om_Source_DefaultSource_

	#define Om_Source_DefaultSource_ \
	Om::Source::DefaultSource

	#include "om/source/source.hpp"

	#ifndef Om_Macro_Precompilation_

		#include <iterator>

	#endif

namespace Om {

	namespace Source {

		// MARK: - Om::Source::DefaultSource

		/*!
		\brief
			A partial implementation of Source.
		*/
		template <
			typename ThisItem,
			typename ThisImplementation
		>
		class DefaultSource:
		public Source<ThisItem>,
		public std::iterator<
			std::input_iterator_tag,
			ThisItem
		> {

		public: // MARK: public (non-static)

			virtual ~DefaultSource() = 0;

			/*!
			\brief
				Pulls the next item from the Source.
			\pre
				The Source cannot be empty.
			\return
				A reference to the derivation.
			*/
			ThisImplementation & operator ++();

			/*!
			\brief
				\overload
			\return
				A copy of the derivation.
			*/
			ThisImplementation operator ++(int);

			/*!
			\return
				True if equal.
			\note
				This is only required to test equality in the context of the pointer-like STL iterator; doesn't take end into account.
			*/
			virtual bool Equals(
				Source<ThisItem> const &
			) const;

			/*!
			\note
				This is a non-virtual declaration that will force a link error if undefined (which could cause infinite recursion in the other form).
			*/
			bool Equals(ThisImplementation const &) const;

		private: // MARK: private (non-static)

			DefaultSource & operator =(DefaultSource const &);

		};

	}

}

	#include "om/source/default_source.cpp"

#endif
