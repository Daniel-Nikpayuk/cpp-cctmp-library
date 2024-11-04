/************************************************************************************************************************
**
** Copyright 2022-2024 Daniel Nikpayuk, Inuit Nunangat, The Inuit Nation
**
** This file is part of cpp_cctmp_library.
**
** cpp_cctmp_library is free software: you can redistribute it and/or modify it under the terms
** of the GNU General Public License as published by the Free Software Foundation, either version 3
** of the License, or (at your option) any later version.
**
** cpp_cctmp_library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
** without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
** See the GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License along with cpp_cctmp_library.
** If not, see <http://www.gnu.org/licenses/>.
**
************************************************************************************************************************/

// lexer:

namespace cctmp  {
namespace engine {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// character sets:

	using global_string_type	= gchar_ctype*;
	using gstring_type		= global_string_type;
	using gstring_ctype		= global_string_type const;
	nik_ce auto U_gstring_type	= U_store_T<gstring_type>;
	nik_ce auto U_gstring_ctype	= U_store_T<gstring_ctype>;

/***********************************************************************************************************************/

// generic:

	nik_ce gchar_type whitespace  [] = { ' ', '\t', '\n' };
	nik_ce gchar_type latin_digit [] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

	nik_ce gchar_type latin_lowercase[] =
	{
		'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
		'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
		'u', 'v', 'w', 'x', 'y', 'z'
	};

	nik_ce gchar_type latin_uppercase[] =
	{
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
		'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
		'U', 'V', 'W', 'X', 'Y', 'Z'
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// numeric:

/***********************************************************************************************************************/

// find:

	template<typename T, typename In, typename End>
	nik_ce auto numeric_find(T n, In k, End e)
	{
		while (k != e) if (*k == n) break; else ++k;

		return k;
	}

/***********************************************************************************************************************/

// find pos:

	template<typename T, typename In, typename End>
	nik_ce auto numeric_find_pos(T n, In b, End e)
	{
		auto k = numeric_find(n, b, e);

		return k - b;
	}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// recognizers:

/***********************************************************************************************************************/

// matches:

	template<auto Size>
	nik_ce auto matches_charset(gchar_ctype c, gchar_ctype (&charset)[Size])
	{
		gstring_ctype e = charset + Size;
		gstring_ctype k = numeric_find(c, charset, e);

		return (k != e);
	}

/***********************************************************************************************************************/

// matches charset:

	// whitespace:

		nik_ce bool matches_whitespace(gchar_ctype c) { return matches_charset(c, whitespace); }

	// digit (optimization):

		nik_ce bool matches_digit(gchar_ctype c) { return ('0' <= c) && (c <= '9'); }

	// underscore:

		nik_ce bool matches_underscore(gchar_ctype c) { return (c == '_'); }

	// latin lowercase:

		nik_ce bool matches_latin_lowercase(gchar_ctype c) { return matches_charset(c, latin_lowercase); }

	// latin uppercase:

		nik_ce bool matches_latin_uppercase(gchar_ctype c) { return matches_charset(c, latin_uppercase); }

/***********************************************************************************************************************/

// matches identifier:

	// latin alphabet:

		nik_ce bool matches_la(gchar_ctype c)
			{ return matches_latin_lowercase(c) || matches_latin_uppercase(c); }

	// latin alphanumeric:

		nik_ce bool matches_lan(gchar_ctype c) { return matches_digit(c) || matches_la(c); }

	// underscore latin alphabet:

		nik_ce bool matches_ula(gchar_ctype c) { return matches_underscore(c) || matches_la(c); }

	// underscore latin alphanumeric:

		nik_ce bool matches_ulan(gchar_ctype c) { return matches_digit(c) || matches_ula(c); }

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// deterministic finite automata:

/***********************************************************************************************************************/

// keyword:

	template<typename CharType, typename SizeType>
	class lexer_keyword
	{
		public:

			using char_type			= CharType;
			using char_ctype		= char_type const;

			using size_type			= SizeType;
			using size_ctype		= size_type const;

			using strlit_type		= string_literal<char_type, size_type>;
			using strlit_ctype		= strlit_type const;
			using strlit_ctype_ref		= strlit_ctype &;

		protected:

			strlit_ctype keyword;

		public:

			size_ctype token;

			nik_ce lexer_keyword(strlit_ctype_ref k, size_ctype t) : keyword{k}, token{t} { }

			template<typename In, typename End>
			nik_ce bool match(In in, End end) const
			{
				for (auto k = keyword.cbegin(); k != keyword.cend(); ++k, ++in)
					if (*k != *in) break;

				return (in == end);
			}
	};

/***********************************************************************************************************************/

// automaton:

	template<typename State, typename Charset, typename IterType, typename SizeType>
	class lexer_automaton
	{
		public:

			using iter_type		= IterType;
			using iter_ctype	= iter_type const;

			using size_type		= SizeType;
			using size_ctype	= size_type const;

			using lit_type		= cctmp::array_literal<size_type, size_type>;
			using lit_ctype		= lit_type const;
			using lit_ctype_ref	= lit_ctype &;

		protected:

			lit_ctype table;

			iter_type start;
			iter_type current;
			iter_type finish;

			size_type mode;

		public:

			nik_ce lexer_automaton(lit_ctype_ref t, iter_ctype s, iter_ctype f) :
				table{t}, start{s}, current{s}, finish{f}, mode{}
					{ }

			nik_ce size_type left_size() const { return current - start; }

			nik_ce bool not_begin () const { return (current != start); }
			nik_ce bool not_end   () const { return (current != finish); }

			nik_ce auto cbegin    () const { return start; }
			nik_ce auto cprevious () const { return current - 1; }
			nik_ce auto ccurrent  () const { return current; }
			nik_ce auto cend      () const { return finish; }

			nik_ce size_type state() const { return mode; }

		protected:

			nik_ce auto skip_whitespace()
			{
				while (not_end() && matches_whitespace(*current)) ++current;

				return current;
			}

			nik_ce size_type table_at(size_ctype row, size_ctype col) const
				{ return table[row * Charset::dimension + col]; }

			nik_ce bool find_empty(size_type & peek, size_ctype col)
			{
				peek = table_at(mode, col);

				return (peek == State::empty);
			}

			nik_ce void increment(size_ctype next) { mode = next; }

		public:

			nik_ce void initialize()
			{
				start = skip_whitespace();
				mode  = State::initial;
			}

			template<typename Policy>
			nik_ce bool find()
			{
				size_type peek;

				while (not_end())
				{
					if (find_empty(peek, Policy::map(*current++))) break;

					increment(peek);
				}

				return not_begin();
			}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

}} // namespace cctmp::engine

