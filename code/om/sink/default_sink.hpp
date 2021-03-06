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

#ifndef Om_Sink_DefaultSink_

	#define Om_Sink_DefaultSink_ \
	Om::Sink::DefaultSink

	#include "om/sink/sink.hpp"

	#ifndef Om_Macro_Precompilation_

		#include <iterator>

	#endif

namespace Om {

	namespace Sink {

		// MARK: - Om::Sink::DefaultSink

		/*!
		\brief
			A partial Sink implementation.
		*/
		template <
			typename ThisItem,
			typename ThisImplementation
		>
		class DefaultSink:
		public Sink<ThisItem>,
		public std::iterator<
			std::output_iterator_tag,
			ThisItem
		> {

		public: // MARK: public (non-static)

			virtual ~DefaultSink() = 0;

			ThisImplementation & operator ++();

			ThisImplementation operator ++(int);

		private: // MARK: private (non-static)

			DefaultSink & operator =(DefaultSink const &);

		};

	}

}

	#include "om/sink/default_sink.cpp"

#endif
