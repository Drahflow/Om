/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> header file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>.  All rights reserved.  This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#if !defined( Om_DefaultAtom_ )

	#define Om_DefaultAtom_ \
	Om::DefaultAtom

	#include "om/atom.hpp"
	#include "om/default_element.hpp"

namespace Om {

	// MARK: - Om::DefaultAtom
	/*!
	\brief
		A partial implementation of Atom.
	*/
	template< typename ThisImplementation >
	class DefaultAtom:
	public DefaultElement<
		ThisImplementation,
		Atom
	> {
	public: // MARK: public (non-static)

		virtual ~DefaultAtom() = 0;

		/*!
		\brief
			Compares with a Atom; required for use as index in containers.
		\return
			True if this Atom string precedes the argument Atom string in a byte-wise ordering.
		*/
		bool operator <( DefaultAtom const & );

		bool operator ==( ThisImplementation const & ) const;

		virtual void Clear();

		virtual std::auto_ptr<
			Source< Element >
		> GetElementRange();

		virtual std::auto_ptr<
			Source< Element const >
		> GetElementRange() const;

		/*!
		\return
			The string that defines this Atom.
		*/
		std::string const & GetString() const;

		/*!
		\return
			True if empty.

		An empty Atom cannot be represented in Om code, but can be handy as an efficient "null" representation in implementation (e.g. the result after a move).
		*/
		virtual bool IsEmpty() const;

		using DefaultElement<
			ThisImplementation,
			Atom
		>::Merge;

		/*!
		\return
			True if the Atom was merged.
		*/
		virtual bool Merge( ThisImplementation & );

		/*!
		\overload
		*/
		virtual bool Merge( ThisImplementation const & );

		void Swap( ThisImplementation & );

	protected: // MARK: protected (non-static)

		DefaultAtom();

		/*!
		\param theCodeUnitIterator
			A non-null pointer to the null-terminated code unit array to copy.
		*/
		explicit DefaultAtom(
			char const theCodeUnitIterator[]
		);

		/*!
		\param theCodeUnit
			The ASCII #CodePoint to copy.
		*/
		explicit DefaultAtom( char const theCodeUnit );

		/*!
		\brief
			The NFD-normalized string that defines the Atom.
		*/
		std::string thisString;

	private: // MARK: private (non-static)

		DefaultAtom & operator =( DefaultAtom const & );

	};

}

	#include "om/default_atom.cpp"

#endif