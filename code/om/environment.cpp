/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> source file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) Jason Erb.  All rights reserved.  This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#if !defined( Om_Environment_ )

	#include "om/environment.hpp"

	#if defined( Om_Macros_Test_ )

		#include "UnitTest++.h"

namespace Om {

	SUITE( Environment ) {}

}

	#endif

#else

// MARK: - Om::Environment

	#define Type_ \
	Om::Environment

// MARK: public (non-static)

inline Type_::Environment():
thisTranslatorVector() {}

inline void Type_::GiveElements( Queue & theQueue ) const {
	if(
		!this->IsEmpty()
	) {
		typedef TranslatorVector::const_iterator Iterator;
		Iterator const theEnd = this->thisTranslatorVector.end();
		for(
			Iterator theCurrent = this->thisTranslatorVector.begin();
			;
			theQueue.TakeElement(
				Separator::GetLineSeparator()
			)
		) {
			assert( *theCurrent );
			Translator const & theTranslator = **theCurrent;
			assert(
				!theTranslator.IsEmpty()
			);
			theTranslator.GiveElements( theQueue );
			if( theEnd == ++theCurrent ) {
				return;
			}
		}
	}
}

inline bool Type_::IsEmpty() const {
	return(
		this->thisTranslatorVector.empty()
	);
}

inline void Type_::Push( Translator const & theTranslator ) {
	Translator const * theTranslatorPointer = &theTranslator;
	for(
		std::stack< Translator const * > theStack;
		;
		theStack.pop()
	) {
		assert( theTranslatorPointer );
		if(
			Environment const * const theEnvironment = dynamic_cast< Environment const * >( theTranslatorPointer )
		) {
			typedef TranslatorVector::const_reverse_iterator Iterator;
			Iterator const theEnd = theEnvironment->thisTranslatorVector.rend();
			for(
				Iterator theCurrent = theEnvironment->thisTranslatorVector.rbegin();
				theEnd != theCurrent;
				++theCurrent
			) {
				assert(
					*theCurrent &&
					!( *theCurrent )->IsEmpty()
				);
				theStack.push( *theCurrent );
			}
		} else if(
			this->IsEmpty() ||
			this->thisTranslatorVector.back() != theTranslatorPointer
		) {
			this->thisTranslatorVector.push_back( theTranslatorPointer );
		}
		if(
			theStack.empty()
		) {
			return;
		}
		theTranslatorPointer = theStack.top();
	}
}

inline bool Type_::Translate(
	Evaluation & theEvaluation,
	Operator const & theOperator
) const {
	typedef TranslatorVector::const_reverse_iterator Iterator;
	Iterator const theEnd = this->thisTranslatorVector.rend();
	for(
		Iterator theCurrent = this->thisTranslatorVector.rbegin();
		theEnd != theCurrent;
		++theCurrent
	) {
		if(
			( *theCurrent )->Translate(
				theEvaluation,
				theOperator
			)
		) {
			return( true );
		}
	}
	return( false );
}

	#undef Type_

#endif