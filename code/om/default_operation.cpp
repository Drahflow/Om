/*!
\file
	\brief
		Om cpp file.
	\version
		0.1.1
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
#if defined( Om_DefaultOperation_ )

	#include "om/evaluator.hpp"

// MARK: Om::DefaultOperation

	#define Template_ template< typename ThisImplementation >

	#define Type_ Om::DefaultOperation< ThisImplementation >

// MARK: public (static)

Template_
inline Om::Operator const & Type_::GetOperator()
{
	static Operator const theOperator( ThisImplementation::GetName() );
	return( theOperator );
}

Template_
inline void Type_::Give( Evaluation & theEvaluation )
{
	theEvaluation.TakeOperation(
		std::auto_ptr< ThisImplementation >( new ThisImplementation )
	);
}

// MARK: public (non-static)

Template_
inline Type_::~DefaultOperation()
{
}

Template_
inline void Type_::GiveElements( Queue & theQueue )
{
	assert( dynamic_cast< ThisImplementation * >( this ) );
	ThisImplementation::GiveElements(
		static_cast< ThisImplementation & >( *this ),
		theQueue
	);
}

Template_
inline void Type_::GiveElements( Queue & theQueue ) const
{
	assert( dynamic_cast< ThisImplementation const * >( this ) );
	ThisImplementation::GiveElements(
		static_cast< ThisImplementation const & >( *this ),
		theQueue
	);
}

Template_
inline bool Type_::ReadQuotedElements(
	Evaluation & theEvaluation,
	Parser & theParser
)
{
	Literal theLiteral;
	theLiteral.ReadElements( theParser );
	return( this->TakeQuotedElements( theEvaluation, theLiteral ) );
}

Template_
inline bool Type_::TakeElement(
	Evaluation & theEvaluation,
	Operand & theOperand
)
{
	assert( !theOperand.IsEmpty() );
	assert( dynamic_cast< ThisImplementation * >( this ) );
	return(
		static_cast<
			ThisImplementation &
		>( *this ).TakeOperand( theEvaluation, theOperand )
	);
}

Template_
inline bool Type_::TakeElement(
	Evaluation & theEvaluation,
	Operand const & theOperand
)
{
	assert( !theOperand.IsEmpty() );
	assert( dynamic_cast< ThisImplementation * >( this ) );
	return(
		static_cast<
			ThisImplementation &
		>( *this ).TakeOperand( theEvaluation, theOperand )
	);
}

Template_
inline bool Type_::TakeQuotedElements(
	Evaluation & theEvaluation,
	Queue & theQueue
)
{
	assert( dynamic_cast< ThisImplementation * >( this ) );
	return(
		static_cast<
			ThisImplementation &
		>( *this ).TakeQuotedQueue( theEvaluation, theQueue )
	);
}

Template_
inline bool Type_::TakeQuotedElements(
	Evaluation & theEvaluation,
	Queue const & theQueue
)
{
	assert( dynamic_cast< ThisImplementation * >( this ) );
	return(
		static_cast<
			ThisImplementation &
		>( *this ).TakeQuotedQueue( theEvaluation, theQueue )
	);
}

	#undef Type_
	#undef Template_

#else
	#include "om/default_operation.hpp"
#endif