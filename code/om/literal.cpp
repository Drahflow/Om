/*!
\file
	\brief
		Om cpp file.
	\version
		0.1
	\date
		2012
	\copyright
		Copyright (c) Jason Erb.
		All rights reserved.  This program and the accompanying materials are
		made available under the terms of the
		<a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse
		Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/
#if defined( Om_Literal_ )

	#include "om/operator.hpp"
	#include "om/separator.hpp"

// MARK: Om::Literal

	#define Type_ Om::Literal

// MARK: public (static)

inline char const * Type_::GetName()
{
	return( Om_Literal_GetName_() );
}

// MARK: public (non-static)

inline Type_::~Literal()
{
	// Flatten the ElementDeque to avoid recursive destructor calls.
	try{
		while( !this->thisElementDeque.empty() ){
			std::auto_ptr< Element > theElement(
				this->thisElementDeque.pop_front().release()
			);
			assert( theElement.get() );
			theElement->GetChildProgram().GiveElements( *this );
		}
	} catch( ... ){}
}

inline Type_::Literal()
:
thisElementDeque()
{
}

inline Type_ & Type_::operator =( Literal theLiteral )
{
	this->Swap( theLiteral );
	return( *this );
}

inline void Type_::BackGiveElement( Queue & theQueue )
{
	if( !this->thisElementDeque.empty() ){
		this->thisElementDeque.pop_back()->GiveElements( theQueue );
	}
}

inline void Type_::Clear()
{
	this->thisElementDeque.clear();
}

inline void Type_::FrontGiveElement( Queue & theQueue )
{
	if( !this->thisElementDeque.empty() ){
		this->thisElementDeque.pop_front()->GiveElements( theQueue );
	}
}

inline std::auto_ptr< Om::Source< Om::Element > > Type_::GetElementRange()
{
	return(
		std::auto_ptr< Source< Element > >(
			new ElementRange< Literal >( *this )
		)
	);
}

inline std::auto_ptr<
	Om::Source< Om::Element const >
> Type_::GetElementRange() const
{
	return(
		std::auto_ptr< Source< Element const > >(
			new ElementRange< Literal const >( *this )
		)
	);
}

inline void Type_::GiveElements( Queue & theQueue )
{
	this->GiveElements(
		theQueue,
		this->thisElementDeque.begin(),
		this->thisElementDeque.end()
	);
	this->thisElementDeque.clear();
}

inline void Type_::GiveElements( Queue & theQueue ) const
{
	this->GiveElements(
		theQueue,
		this->thisElementDeque.begin(),
		this->thisElementDeque.end()
	);
}

inline bool Type_::IsEmpty() const
{
	return( this->thisElementDeque.empty() );
}

inline void Type_::ReadElements( Parser & theParser )
{
	std::stack< Literal * > theStack;
	theStack.push( this );

	while( theParser ){
		switch( *theParser ){
		case Symbols::theEndOperandSymbol:
			assert( !theStack.empty() && this != theStack.top() );
			theStack.pop();
			break;
		case Symbols::theStartOperandSymbol:
			{
				std::auto_ptr< Literal > theLiteral( new Literal );
				Literal * theLiteralPointer = theLiteral.get();
				{
					Operand theOperand( theLiteral );
					theStack.top()->TakeOperand( theOperand );
				}
				theStack.push( theLiteralPointer );
			}
			break;
		Om_Symbols_SeparatorSymbol_GetCases_():
			assert( !theStack.empty() && theStack.top() );
			{
				Separator theSeparator( theParser );
				theStack.top()->TakeSeparator( theSeparator );
			}
			continue;
		default:
			assert( !theStack.empty() && theStack.top() );
			{
				Operator theOperator( theParser );
				theStack.top()->TakeOperator( theOperator );
			}
			continue;
		}
		theParser.Pop();
	}
}

inline void Type_::ReadQuotedElements( Parser & theParser )
{
	Literal theLiteral;
	theLiteral.ReadElements( theParser );
	this->TakeQuotedQueue( theLiteral );
}

inline void Type_::Swap( Literal & theLiteral )
{
	this->thisElementDeque.swap( theLiteral.thisElementDeque );
}

template< typename TheOperand >
inline void Type_::TakeOperand( TheOperand & theOperand )
{
	this->thisElementDeque.push_back( Give( theOperand ) );
}

template< typename TheOperator >
inline void Type_::TakeOperator( TheOperator & theOperator )
{
	this->TakeAtom( theOperator );
}

template< typename TheQueue >
inline void Type_::TakeQuotedQueue( TheQueue & theQueue )
{
	this->thisElementDeque.push_back( new Operand( theQueue.GiveProgram() ) );
}

template< typename TheSeparator >
inline void Type_::TakeSeparator( TheSeparator & theSeparator )
{
	this->TakeAtom( theSeparator );
}

// MARK: private (static)

template< typename TheElementIterator >
inline void Type_::GiveElements(
	Queue & theQueue,
	TheElementIterator theStart,
	TheElementIterator const theEnd
)
{
	for( ; theEnd != theStart; ++theStart ){
		theStart->GiveElements( theQueue );
	}
}

// MARK: private (non-static)

template< typename TheAtom >
inline void Type_::TakeAtom( TheAtom & theAtom )
{
	assert( !theAtom.IsEmpty() );
	if(
		this->thisElementDeque.empty() ||
		!this->thisElementDeque.back().Merge( theAtom )
	){ this->thisElementDeque.push_back( Give( theAtom ) ); }
}

	#undef Type_

// MARK: -
// MARK: Om::Literal::ElementRange

	#define Type_ Om::Literal::ElementRange

// MARK: public (non-static)

inline Type_< Om::Literal >::ElementRange( Literal & theLiteral )
:
Sources::CollectionFrontSource< Element, ElementDeque::iterator >(
	theLiteral.thisElementDeque
)
{
}

inline Type_< Om::Literal const >::ElementRange( Literal const & theLiteral )
:
Sources::CollectionFrontSource< Element const, ElementDeque::const_iterator >(
	theLiteral.thisElementDeque
)
{
}

	#undef Type_

// MARK: -
// MARK: boost

template<>
inline void boost::swap( Om::Literal & theFirst, Om::Literal & theSecond )
{
	theFirst.Swap( theSecond );
}

#else
	#include "om/literal.hpp"

	#if defined( Om_Macros_Test_ )

		#include "om/environment.hpp"
		#include "UnitTest++.h"

namespace Om
{
	// MARK: -
	SUITE( Literal )
	{
		TEST( Equality )
		{
			// Positive match
			CHECK_EQUAL(
				"{{a{b}{c}\nd{e}}}",
				Environment().Evaluate(
					"= {a{b}{c}\nd{e}} {a{b}{c}\nd{e}}"
				)
			);

			// Negative match
			CHECK_EQUAL(
				"{}",
				Environment().Evaluate( "= {a{b}{c}} {a{b}{d}}" )
			);

			// Empty match
			CHECK_EQUAL(
				"{}",
				Environment().Evaluate( "= {} {a{b}{c}}" )
			);

			// Empty match
			CHECK_EQUAL( "{{}}", Environment().Evaluate( "= {} {}" ) );
		}

		TEST( Recursion )
		{
			size_t const theDepth = 50000;

			std::string theString;
			for( size_t theLevel = theDepth; theLevel; --theLevel ){
				theString = "{" + theString + "}";
			}

			Sources::CodePointSource<
				std::string::const_iterator
			> theCodePointSource( theString.begin(), theString.end() );
			Parser theParser( theCodePointSource );
			Literal theLiteral;
			theLiteral.ReadElements( theParser );

			Literal theCopy( theLiteral );
		}
	}
}

	#endif

#endif
