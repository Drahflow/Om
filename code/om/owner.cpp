/*!
\file
	\brief
		<a href="http://github.com/sparist/Om">Om</a> source file.
	\version
		0.1.3
	\date
		2012-2014
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\author
		Jason Erb
*/

#ifndef Om_Owner_

	#include "om/owner.hpp"

	#ifdef Om_Macro_Test_

		#include "om/default_copyable.hpp"
		#include "om/shareable.hpp"

		#ifndef Om_Macro_Precompilation_

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	BOOST_AUTO_TEST_SUITE(OwnerTest)

		namespace {

			class TestValue:
			public DefaultCopyable<TestValue>,
			public Shareable<> {

			public:

				explicit TestValue(int const theNumber):
				thisNumber(theNumber) {}

				bool operator ==(TestValue const theTestValue) const {
					return this->thisNumber == theTestValue.thisNumber;
				}

				int thisNumber;

			};

		}

		BOOST_AUTO_TEST_CASE(LazinessTest) {
			Owner<TestValue> theFirst(
				std::auto_ptr<TestValue>(
					new TestValue(1)
				)
			);
			assert(theFirst);

			Owner<TestValue> const & theConstFirst = theFirst;
			TestValue const & theFirstValue = *theConstFirst;

			Owner<TestValue> theSecond(theFirst);

			Owner<TestValue> const & theConstSecond = theSecond;
			TestValue const & theSecondValue = *theConstSecond;

			BOOST_CHECK_EQUAL(
				&theFirstValue,
				&theSecondValue
			);
		}

		BOOST_AUTO_TEST_CASE(CopyTest) {
			Owner<TestValue> theFirst(
				std::auto_ptr<TestValue>(
					new TestValue(1)
				)
			);
			assert(theFirst);

			TestValue & theFirstValue = *theFirst;
			BOOST_CHECK_EQUAL(
				1,
				theFirstValue.thisNumber
			);
			theFirstValue.thisNumber = 2;
			BOOST_CHECK_EQUAL(
				2,
				theFirstValue.thisNumber
			);

			Owner<TestValue> theSecond(theFirst);

			TestValue & theSecondValue = *theSecond;
			BOOST_CHECK_EQUAL(
				2,
				theFirstValue.thisNumber
			);
			BOOST_CHECK_EQUAL(
				2,
				theSecondValue.thisNumber
			);

			theSecondValue.thisNumber = 3;
			theFirstValue.thisNumber = 4;

			Owner<TestValue> theThird(theFirst);
			Owner<TestValue> theFourth(theThird);

			TestValue & theThirdValue = *theThird;
			Owner<TestValue> const & theConstFourth = theFourth;
			TestValue const & theFourthValue = *theConstFourth;
			BOOST_CHECK_EQUAL(
				4,
				theFirstValue.thisNumber
			);
			BOOST_CHECK_EQUAL(
				3,
				theSecondValue.thisNumber
			);
			BOOST_CHECK_EQUAL(
				4,
				theThirdValue.thisNumber
			);
			BOOST_CHECK_EQUAL(
				4,
				theFourthValue.thisNumber
			);

			theThirdValue.thisNumber = 5;
			BOOST_CHECK_EQUAL(
				4,
				theFirstValue.thisNumber
			);
			BOOST_CHECK_EQUAL(
				3,
				theSecondValue.thisNumber
			);
			BOOST_CHECK_EQUAL(
				5,
				theThirdValue.thisNumber
			);
			BOOST_CHECK_EQUAL(
				4,
				theFourthValue.thisNumber
			);
		}

	BOOST_AUTO_TEST_SUITE_END()

}

	#endif

#else

	#ifndef Om_Macro_Precompilation_

		#include "boost/swap.hpp"

	#endif

// MARK: - Om::Owner

	#define Template_ \
	template <typename ThisValue>

	#define Type_ \
	Om::Owner<ThisValue>

// MARK: public (non-static)

Template_
inline Type_::Owner():
thisValue(),
thisWasExposed() {}

Template_
inline Type_::Owner(Owner const & theOwner):
thisValue(),
thisWasExposed() {
	if (theOwner.thisWasExposed) {
		assert(theOwner.thisValue);
		this->thisValue.reset(
			Copy(*theOwner.thisValue).release()
		);
	} else {
		this->thisValue = theOwner.thisValue;
	}
}

Template_
template <typename TheValue>
inline Type_::Owner(
	std::auto_ptr<TheValue> theValue
):
thisValue(
	theValue.release()
),
thisWasExposed() {}

Template_
inline Type_ & Type_::operator =(Owner theOwner) {
	this->Swap(theOwner);
	return *this;
}

Template_
inline ThisValue & Type_::operator *() {
	assert(this->thisValue);
	if (
		1 < this->thisValue->GetOwnerCount()
	) {
		this->thisValue.reset(
			Copy(*this->thisValue).release()
		);
		assert(this->thisValue);
	}
	this->thisWasExposed = true;
	return *this->thisValue;
}

Template_
inline ThisValue const & Type_::operator *() const {
	assert(this->thisValue);
	return *this->thisValue;
}

Template_
inline ThisValue * Type_::operator ->() {
	return &**this;
}

Template_
inline ThisValue const * Type_::operator ->() const {
	return &**this;
}

Template_
inline bool Type_::operator !() const {
	return !this->thisValue;
}

Template_
inline Type_::operator Boolean() const {
	return (
		this->thisValue ?
		&Owner::UncomparableBoolean :
		0
	);
}

Template_
inline void Type_::Clear() {
	this->thisValue.reset();
	this->thisWasExposed = false;
}

Template_
ThisValue * Type_::GetValue() {
	return (
		this->thisValue ?
		&**this :
		0
	);
}

Template_
ThisValue const * Type_::GetValue() const {
	return this->thisValue.get();
}

Template_
bool Type_::IsEmpty() const {
	return !this->thisValue;
}

Template_
template <typename TheValue>
inline void Type_::SetValue(
	std::auto_ptr<TheValue> theValue
) {
	this->thisValue.reset(
		theValue.release()
	);
	this->thisWasExposed = false;
}

Template_
inline void Type_::Swap(Owner & theOwner) {
	this->thisValue.swap(theOwner.thisValue);
	boost::swap(
		this->thisWasExposed,
		theOwner.thisWasExposed
	);
}

// MARK: private (non-static)

Template_
inline void Type_::UncomparableBoolean() const {}

	#undef Type_
	#undef Template_

// MARK: - boost::

template <typename TheValue>
inline void boost::swap(
	Om::Owner<TheValue> & theFirst,
	Om::Owner<TheValue> & theSecond
) {
	theFirst.Swap(theSecond);
}

#endif
