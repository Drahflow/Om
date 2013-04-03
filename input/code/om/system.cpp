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

#ifndef Om_System_

	#include "om/system.hpp"

#else

	#include "om/lexicon.hpp"
	#include "om/operator.hpp"

	#ifndef Om_Macros_Precompilation_

		#include "boost/locale/generator.hpp"
		#include "boost/locale/info.hpp"

	#endif

// MARK: - Om::System

	#define Type_ \
	Om::System

// MARK: public (static)

inline Type_ & Type_::Get() {
	static System theSystem;
	return theSystem;
}

// MARK: public (non-static)

inline Om::Lexicon const & Type_::GetLexicon() const {
	static Lexicon theLexicon;
	if (
		theLexicon.IsEmpty()
	) {
		this->GiveElements(theLexicon);
	}
	return theLexicon;
}

inline void Type_::GiveElements(Consumer & theConsumer) const {
	if (
		!this->IsEmpty()
	) {
		Map::const_iterator const theEnd = this->thisMap.end();
		for (
			Map::const_iterator theCurrent = this->thisMap.begin();
			;
			theConsumer.TakeElement(
				Separator::GetLineSeparator()
			)
		) {
			assert(theEnd != theCurrent);
			Operator theOperator(theCurrent->first);
			theConsumer.TakeElement(theOperator);
			if (theEnd == ++theCurrent) {
				return;
			}
		}
	}
}

inline void Type_::Initialize(
	char const theLocaleCodeUnitIterator[]
) {
	// Set the global locale.
	{
		boost::locale::generator theGenerator;
		theGenerator.characters(boost::locale::char_facet);
		std::locale::global(
			theGenerator(theLocaleCodeUnitIterator)
		);
		assert(
			std::use_facet<boost::locale::info>(
				std::locale()
			).utf8()
		);
	}

	#ifndef NDEBUG
	// Assert that the name keys are NFD-normalized.
	{
		Map::const_iterator const theEnd = this->thisMap.end();
		for (
			Map::const_iterator theCurrent = this->thisMap.begin();
			theEnd != theCurrent;
			++theCurrent
		) {
			assert(
				boost::locale::normalize(
					theCurrent->first,
					boost::locale::norm_nfd
				) == theCurrent->first
			);
		}
	}
	#endif
}

inline bool Type_::IsEmpty() const {
	return this->thisMap.empty();
}

inline bool Type_::Translate(
	Evaluation & theEvaluation,
	Operator const & theOperator
) const {
	Map::const_iterator theIterator(
		this->thisMap.find(
			theOperator.GetString()
		)
	);
	if (
		this->thisMap.end() == theIterator
	) {
		return false;
	}
	assert(theIterator->second);
	(*theIterator->second)(theEvaluation);
	return true;
}

// MARK: private (non-static)

inline Type_::System():
thisMap() {}

	#undef Type_

// MARK: - Om::System::Definition

	#define Template_ \
	template <typename ThisOperation>

	#define Type_ \
	Om::System::Definition<ThisOperation>

// MARK: public (non-static)

Template_
inline Type_::Definition() {
	System::Get().thisMap[
		ThisOperation::GetName()
	] = &ThisOperation::Give;
}

	#undef Type_
	#undef Template_

#endif
