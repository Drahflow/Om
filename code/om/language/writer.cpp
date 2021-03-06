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

#ifndef Om_Language_Writer_

	#include "om/language/writer.hpp"

	#ifdef Om_Macro_Test_

		#ifndef Om_Macro_Precompilation_

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	namespace Language {

		BOOST_AUTO_TEST_SUITE(WriterTest)

			BOOST_AUTO_TEST_CASE(GeneralTest) {
				char const theCode[] = "\n\t {\n\t {\n\t }\n\t }\n\t";
				std::string theResult;
				{
					Om::Sink::CodePointSink<
						std::back_insert_iterator<std::string>
					> theCodePointSink(
						std::back_inserter(theResult)
					);
					Writer theWriter(theCodePointSink);

					Om::Source::CodePointSource<> theCodePointSource(theCode);
					Reader theReader(theCodePointSource);
					theWriter.ParseElements(theReader);
				}
				BOOST_CHECK_EQUAL(
					"\n\t {\n\t {\n\t }\n\t }\n\t",
					theResult
				);
			}

		BOOST_AUTO_TEST_SUITE_END()

	}

}

	#endif

#else

	#include "om/language/operator.hpp"
	#include "om/language/symbol/operator_symbol.hpp"
	#include "om/language/symbol/separator_symbol.hpp"
	#include "om/sink/sink.hpp"
	#include "om/source/code_point_source.hpp"

// MARK: - Om::Language::Writer

	#define Type_ \
	Om::Language::Writer

// MARK: public (non-static)

inline Type_::Writer(
	Om::Sink::Sink<CodePoint const> & theCodePointSink
):
thisCodePointSink(theCodePointSink) {}

inline void Type_::ParseElements(Reader & theReader) {
	for (
		;
		theReader;
		theReader.Pop()
	) {
		this->thisCodePointSink.Push(*theReader);
	}
}

inline void Type_::ParseQuotedElements(Reader & theReader) {
	this->thisCodePointSink.Push(Symbol::theStartOperandSymbol);
	this->ParseElements(theReader);
	this->thisCodePointSink.Push(Symbol::theEndOperandSymbol);
}

template <typename TheOperand>
inline void Type_::TakeOperand(TheOperand & theOperand) {
	assert(
		!theOperand.IsEmpty()
	);
	this->TakeQuotedProducer(
		*theOperand.GetProgram()
	);
}

template <typename TheOperator>
inline void Type_::TakeOperator(TheOperator & theOperator) {
	assert(
		!theOperator.IsEmpty()
	);
	std::string const & theString = theOperator.GetString();
	for (
		Om::Source::CodePointSource<std::string::const_iterator> theCodePointSource(
			theString.begin(),
			theString.end()
		);
		theCodePointSource;
		theCodePointSource.Pop()
	) {
		switch (CodePoint const theCodePoint = *theCodePointSource) {
		Om_Language_Symbol_SeparatorSymbol_GetCases_():
			// Fall through.
		Om_Language_Symbol_OperandSymbol_GetCases_():
			// Fall through.
		case Symbol::theEncodeOperatorSymbol:
			this->thisCodePointSink.Push(Symbol::theEncodeOperatorSymbol);
			// Fall through.
		default:
			this->thisCodePointSink.Push(theCodePoint);
			// Fall through.
		}
	}
}

template <typename TheProducer>
inline void Type_::TakeQuotedProducer(TheProducer & theProducer) {
	this->thisCodePointSink.Push(Symbol::theStartOperandSymbol);
	theProducer.GiveElements(*this);
	this->thisCodePointSink.Push(Symbol::theEndOperandSymbol);
}

template <typename TheSeparator>
inline void Type_::TakeSeparator(TheSeparator & theSeparator) {
	assert(
		!theSeparator.IsEmpty()
	);
	std::string const & theString = theSeparator.GetString();
	for (
		Om::Source::CodePointSource<std::string::const_iterator> theCodePointSource(
			theString.begin(),
			theString.end()
		);
		theCodePointSource;
		theCodePointSource.Pop()
	) {
		this->thisCodePointSink.Push(*theCodePointSource);
	}
}

	#undef Type_

#endif
