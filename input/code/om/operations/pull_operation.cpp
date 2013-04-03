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

#ifndef Om_Operations_PullOperation_

	#include "om/operations/pull_operation.hpp"

#else

// MARK: - Om::Operations::PullOperation

	#define Template_ \
	template < \
		typename ThisProgram, \
		typename ThisImplementation \
	>

	#define Type_ \
	Om::Operations::PullOperation< \
		ThisProgram, \
		ThisImplementation \
	>

// MARK: public (static)

Template_
template <typename ThePullOperation>
inline void Type_::GiveElements(
	ThePullOperation &,
	Consumer & theConsumer
) {
	theConsumer.TakeElement(
		GetOperator()
	);
}

// MARK: public (non-static)

Template_
inline bool Type_::ReadQuotedElements(
	Evaluation & theEvaluation,
	Parser & theParser
) {
	ThisProgram theProgram;
	theProgram.ReadElements(theParser);
	return this->TakeQuotedElements(
		theEvaluation,
		theProgram
	);
}

Template_
template <typename TheOperand>
inline bool Type_::TakeOperand(
	Evaluation & theEvaluation,
	TheOperand & theOperand
) {
	assert(
		!theOperand.IsEmpty()
	);
	return this->TakeQuotedProducer(
		theEvaluation,
		*theOperand.GetProgram()
	);
}

Template_
template <typename TheProducer>
inline bool Type_::TakeQuotedProducer(
	Evaluation & theEvaluation,
	TheProducer & theProducer
) {
	ThisProgram theProgramToPullFrom;
	theProgramToPullFrom.TakeElements(theProducer);

	ThisProgram thePulledProgram;
	ThisImplementation::Pull(
		theProgramToPullFrom,
		thePulledProgram
	);

	theEvaluation.TakeQuotedProducer(theProgramToPullFrom);
	theEvaluation.TakeQuotedProducer(thePulledProgram);
	return true;
}

// MARK: private (static)

Template_
inline Om::Operator const & Type_::GetOperator() {
	static Operator const theOperator(
		ThisImplementation::GetName()
	);
	return theOperator;
}

	#undef Type_
	#undef Template_

#endif
