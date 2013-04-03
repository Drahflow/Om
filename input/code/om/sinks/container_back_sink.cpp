/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> source file.
	\version
		0.1.3
	\date
		2012-2013
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#ifndef Om_Sinks_ContainerBackSink_

	#include "om/sinks/container_back_sink.hpp"

	#ifdef Om_Macros_Test_

		#ifndef Om_Macros_Precompilation_

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	namespace Sinks {

		BOOST_AUTO_TEST_SUITE(ContainerBackSinkTest)

			BOOST_AUTO_TEST_CASE(GeneralTest) {
				std::string theSinkString("01");
				ContainerBackSink<
					char const,
					std::string
				> theSink(theSinkString);

				*theSink++ = '2';
				BOOST_CHECK_EQUAL(
					"012",
					theSinkString
				);
				*++theSink = '3';
				BOOST_CHECK_EQUAL(
					"0123",
					theSinkString
				);
				*theSink = '4';
				BOOST_CHECK_EQUAL(
					"01234",
					theSinkString
				);
			}

		BOOST_AUTO_TEST_SUITE_END()

	}

}

	#endif

#else

// MARK: - Om::Sinks::ContainerBackSink

	#define Template_ \
	template < \
		typename ThisItem, \
		typename ThisContainer \
	>

	#define Type_ \
	Om::Sinks::ContainerBackSink< \
		ThisItem, \
		ThisContainer \
	>

// MARK: public (non-static)

Template_
inline Type_::ContainerBackSink(ThisContainer & theContainer):
thisContainer(theContainer) {}

Template_
inline Type_ & Type_::operator =(ContainerBackSink theContainerBackSink) {
	this->Swap(theContainerBackSink);
	return *this;
}

Template_
inline void Type_::Push(ThisItem & thisItem) {
	this->thisContainer.push_back(thisItem);
}

Template_
inline void Type_::Swap(ContainerBackSink & theContainerBackSink) {
	boost::swap(
		this->thisContainer,
		theContainerBackSink.thisContainer
	);
}

	#undef Type_
	#undef Template_

// MARK: - boost::

template <
	typename TheItem,
	typename TheContainer
>
inline void boost::swap(
	Om::Sinks::ContainerBackSink<
		TheItem,
		TheContainer
	> & theFirst,
	Om::Sinks::ContainerBackSink<
		TheItem,
		TheContainer
	> & theSecond
) {
	theFirst.Swap(theSecond);
}

#endif
