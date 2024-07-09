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

namespace engine {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// character sets:

	using global_string_type	= gcchar_type*;
	using gstring_type		= global_string_type;
	using gcstring_type		= global_string_type const;
	nik_ce auto U_gstring_type	= U_store_T<gstring_type>;
	nik_ce auto U_gcstring_type	= U_store_T<gcstring_type>;

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
	nik_ce auto matches_charset(gcchar_type c, gcchar_type (&charset)[Size])
	{
		gcstring_type e = charset + Size;
		gcstring_type k = numeric_find(c, charset, e);

		return (k != e);
	}

/***********************************************************************************************************************/

// matches charset:

	// whitespace:

		nik_ce bool matches_whitespace(gcchar_type c) { return matches_charset(c, whitespace); }

	// digit (optimization):

		nik_ce bool matches_digit(gcchar_type c) { return ('0' <= c) && (c <= '9'); }

	// underscore:

		nik_ce bool matches_underscore(gcchar_type c) { return (c == '_'); }

	// latin lowercase:

		nik_ce bool matches_latin_lowercase(gcchar_type c) { return matches_charset(c, latin_lowercase); }

	// latin uppercase:

		nik_ce bool matches_latin_uppercase(gcchar_type c) { return matches_charset(c, latin_uppercase); }

/***********************************************************************************************************************/

// matches identifier:

	// latin alphabet:

		nik_ce bool matches_la(gcchar_type c)
			{ return matches_latin_lowercase(c) || matches_latin_uppercase(c); }

	// latin alphanumeric:

		nik_ce bool matches_lan(gcchar_type c) { return matches_digit(c) || matches_la(c); }

	// underscore latin alphabet:

		nik_ce bool matches_ula(gcchar_type c) { return matches_underscore(c) || matches_la(c); }

	// underscore latin alphanumeric:

		nik_ce bool matches_ulan(gcchar_type c) { return matches_digit(c) || matches_ula(c); }

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// deterministic finite automata:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// state:

	template<typename State, typename Charset, typename IterType, typename SizeType>
	class lexer_state
	{
		public:

			using iter_type			= IterType;
			using iter_ctype		= iter_type const;

			using size_type			= SizeType;
			using size_ctype		= size_type const;

			using literal_type		= literal<size_type, size_type>;
			using literal_ctype		= literal_type const;
			using literal_ctype_ref		= literal_ctype &;

		protected:

			literal_ctype table;

			iter_type start;
			iter_type current;
			iter_type finish;

			size_type state;

		public:

			nik_ce lexer_state(literal_ctype_ref t, iter_ctype s, iter_ctype f) :
				table{t}, start{s}, current{s}, finish{f}, state{}
					{ }

			nik_ce bool not_begin () const { return (current != start); }
			nik_ce bool not_end   () const { return (current != finish); }

			nik_ce auto cbegin   () const { return start; }
			nik_ce auto ccurrent () const { return current; }
			nik_ce auto cend     () const { return finish; }

		protected:

			nik_ce auto skip_whitespace()
			{
				while (not_end() && matches_whitespace(*current)) ++current;

				return current;
			}

			nik_ce void reinitialize()
			{
				start = skip_whitespace();
				state = State::initial;
			}

			nik_ce size_type table_at(size_ctype row, size_ctype col) const
				{ return table[row * Charset::dimension + col]; }

			nik_ce bool find(size_ctype col)
			{
				state = table_at(state, col);

				return (state == State::empty);
			}

		public:

			template<typename Policy>
			nik_ce bool lex()
			{
				reinitialize();

				while (not_end())
					if (find(Policy::map(*current))) break;
					else ++current;

				return not_begin();
			}
	};

/***********************************************************************************************************************/

// recognizes:

/*
	template<typename T_lexer>
	nik_ce gcbool_type recognizes(const cselector<char> & s)
	{
		lexeme l{s};

		T_lexer::lex(l);

		return (l.token != TokenName::invalid);
	}
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// (generic) keyword:

/***********************************************************************************************************************/

// dfa charset:

/*
	template<typename CharType, auto Size>
	struct dfa_charset
	{
		using char_type			= CharType;
		using string_type		= char_type const*;
		using size_type			= decltype(Size);

		nik_ces size_type length	= Size - 1;

		string_type string;
		char_type unique[length];
		char_type column[length];
		size_type size;

		nik_ce dfa_charset(const CharType (&s)[Size]) : string{s}, unique{}, column{}, size{}
		{
			string_type end = string + length;

			for (string_type j = string; j != end; ++j)
			{
				gcstring_type e = unique + size;
				gcstring_type k = numeric_find(*j, unique, e);

				if (k == e) unique[size++] = *j;
			}

			char_type *k = column;

			for (string_type j = string; j != end; ++j, ++k) *k = map(*j);
		}

			// Assumes map will return a non-zero index for each
			// character (equivalence) class, and will otherwise return
			// zero (for any other character).

		nik_ce gkey_type map(gcchar_type c) const
		{
			auto k = numeric_find_pos(c, unique, unique + size);

			if (k != size) return k + 1;
			else           return _zero;
		}
	};
*/

/***********************************************************************************************************************/

// transition table:

/*
	template<auto CharsetCallable>
	struct T_keyword_dftt
	{
		nik_ces auto static_charset		= _static_callable_<CharsetCallable>;
		nik_ces auto & charset			= member_value_U<static_charset>;
		nik_ces gkey_type state_size		= charset.length + 2;
		nik_ces gkey_type charset_size		= charset.size + 1;

		state_type table[state_size][charset_size];

		nik_ce T_keyword_dftt() : table{} // initializes the empty state.
		{
			for (gkey_type pos = StateName::initial; pos != charset.length + 1; ++pos)
				table[pos][charset.column[pos - 1]] = pos + 1;
		}

		nik_ce cstate_type & move(cstate_type s, gcchar_type c) const
		{
			return table[s][charset.map(c)];
		}
	};
*/

/***********************************************************************************************************************/

// automaton:

/*
	template<auto CharsetCallable>
	struct T_keyword_dfa
	{
		nik_ces auto value  = T_keyword_dftt<CharsetCallable>{};
		nik_ces auto accept = value.charset.length + 1;
	};
*/

/***********************************************************************************************************************/

// interface:

/*
	template<auto CharsetCallable, token_type Token>
	struct T_keyword_lexer
	{
		using T_dfa		= T_keyword_dfa<CharsetCallable>;
		nik_ces auto token	= Token;

		nik_ces void lex(lexeme & l)
		{
			T_generic_lexer<T_dfa>::lex(l);

			token_type t = (l.token == T_dfa::accept) ? Token : TokenName::invalid;

			l.token = static_cast<token_type>(t);
		}
	};
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace engine

