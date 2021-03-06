/*!
\file
	\brief
		<a href="http://github.com/sparist/Om">Om</a> header file.
	\version
		0.1.3
	\date
		2012-2014
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>.
		All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\author
		Jason Erb

\defgroup om__separator__ Separator
	\ingroup om__program__
	\brief
		An atomic \ref om__program__ element that serves to separate other elements.
	\par Interpretation
		A \ref om__program__ is interpreted as a \ref om__separator__ by treating only separator code points (line, tab, and space) as significant.
	\par Normalization
		A \ref om__program__ is normalized as a \ref om__separator__ by discarding all non-separator code points.
	\par Implementation
		Om::Language::Separator
*/

#ifndef Om_Language_Separator_

	#define Om_Language_Separator_ \
	Om::Language::Separator

	#include "om/language/default_atom.hpp"
	#include "om/language/symbol/separator_symbol.hpp"

	#define Om_Language_Separator_GetName_() \
	"separator"

namespace Om {

	namespace Language {

		// MARK: - Om::Language::Separator

		/*!
		\brief
			The \ref om__separator__ implementation.

		An Atom defined by a string containing only Symbol::SeparatorSymbol characters.

		As a Consumer, the Separator filters out all top-level Element instances except Separator.
		*/
		class Separator:
		public DefaultAtom<Separator> {

		public: // MARK: public (static)

			/*!
			\return
				A Separator comprised of a single Symbol::theLineSeparatorSymbol.
			*/
			static Separator const & GetLineSeparator();

			static char const * GetName();

		public: // MARK: public (non-static)

			Separator();

			explicit Separator(
				Om::Source::Source<CodePoint const> &
			);

			/*!
			\param theSeparatorSymbol
				The Symbol::SeparatorSymbol to copy directly into the Separator.
			*/
			explicit Separator(Symbol::SeparatorSymbol const theSeparatorSymbol);

			Separator & operator =(Separator);

			virtual void ParseElements(Reader &);

			virtual void ParseQuotedElements(Reader &);

			template <typename TheOperand>
			void TakeOperand(TheOperand &);

			template <typename TheOperator>
			void TakeOperator(TheOperator &);

			template <typename TheProducer>
			void TakeQuotedProducer(TheProducer &);

			template <typename TheSeparator>
			void TakeSeparator(TheSeparator &);

			void TakeSeparatorSymbol(Symbol::SeparatorSymbol const);

		};

	}

}

namespace boost {

	// MARK: - boost::

	template <>
	void swap(
		Om::Language::Separator &,
		Om::Language::Separator &
	);

}

	#include "om/language/separator.cpp"

#endif
