/************************************************************************************************************************
**
** Copyright 2022-2023 Daniel Nikpayuk, Inuit Nunangat, The Inuit Nation
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

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// character sets:

	using global_char_type		= char;
	using gchar_type		= global_char_type;
	using gcchar_type		= global_char_type const;

	using global_string_type	= gcchar_type*;
	using gstring_type		= global_string_type;
	using gcstring_type		= global_string_type const;

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

// recognizers:

/***********************************************************************************************************************/

// generic charset:

	nik_ce auto charset_find(gcchar_type c, gstring_type k, gcstring_type e)
	{
		while (k != e) if (*k == c) break; else ++k;

		return k;
	}

	template<auto Size>
	nik_ce auto matches_charset(gcchar_type c, gcchar_type (&charset)[Size])
	{
		gcstring_type e = charset + Size;
		gcstring_type k = charset_find(c, charset, e);

		return (k != e);
	}

/***********************************************************************************************************************/

// matches charset:

	// whitespace:

		nik_ce bool matches_whitespace(gcchar_type c) { return matches_charset(c, whitespace); }

	// digit (optimization):

		nik_ce bool matches_digit(gcchar_type c) { return ('0' <= c) && (c <= '9'); }

	// latin lowercase:

		nik_ce bool matches_latin_lowercase(gcchar_type c) { return matches_charset(c, latin_lowercase); }

	// latin uppercase:

		nik_ce bool matches_latin_uppercase(gcchar_type c) { return matches_charset(c, latin_uppercase); }

/***********************************************************************************************************************/

// matches identifier:

	nik_ce bool matches_underscore_latin_alphabet(gcchar_type c)
	{
		return (c == '_') || matches_latin_lowercase(c) || matches_latin_uppercase(c);
	}

	nik_ce bool matches_underscore_latin_alphanumeric(gcchar_type c)
	{
		return matches_digit(c) || matches_underscore_latin_alphabet(c);
	}

/***********************************************************************************************************************/

// skip whitespace:

	nik_ce gstring_type skip_whitespace(gstring_type b, gstring_type e)
	{
		while (b != e && matches_whitespace(*b)) ++b;

		return b;
	}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// attributes:

/***********************************************************************************************************************/

	struct LexerName
	{
		enum : gkey_type
		{
			empty = 0,
			initial ,
			dimension
		};
	};

	struct LexerToken
	{
		enum : gkey_type
		{
			invalid = 0,

			statement , period     , underscore , equal   ,
			test      , go_to      , branch     , re_turn ,
			label     , identifier ,
		};
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// state:

/***********************************************************************************************************************/

	struct state
	{
		gkey_type name;
		gkey_type token;

		nik_ce state() :
			name{LexerName::empty}, token{LexerToken::invalid} { }

		nik_ce state(gckey_type _v, gckey_type _t) :
			name{_v}, token{_t} { }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// lexeme:

/***********************************************************************************************************************/

	struct lexeme
	{
		gstring_type start;
		gstring_type finish;

		gkey_type token;

		nik_ce lexeme() :

			start  {                     },
			finish {                     },
			token  { LexerToken::invalid }

			{ }

		nik_ce lexeme(gstring_type _s, gstring_type _f, gckey_type _t) :

			start  { _s },
			finish { _f },
			token  { _t }

			{ }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// deterministic finite automata:

/***********************************************************************************************************************/

// dfa charset:

	template<typename CharType, auto Size>
	struct dfa_charset
	{
		using char_type			= CharType;
		using string_type		= char_type const *;
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
				gcstring_type k = charset_find(*j, unique, e);

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
			gcstring_type e = unique + size;
			gcstring_type k = charset_find(c, unique, e);

			if (k != e) return (k - unique) + 1;
			else        return _zero;
		}
	};

/***********************************************************************************************************************/

// (generic) keyword:

	template<auto CharsetFunction, gkey_type Token>
	struct KeywordDFA
	{
		nik_ces auto      charset		= CharsetFunction();
		nik_ces gkey_type keyword_size		= charset.length;
		nik_ces gkey_type name_size		= keyword_size + 2;
		nik_ces gkey_type charset_size		= charset.size + 1;

		// table:

			state table[name_size][charset_size];

			nik_ce KeywordDFA() : table{} // initializes the empty state.
			{
				gkey_type name_pos = 1;

				while (name_pos != keyword_size)
				{
					gkey_type char_pos  = charset.column[name_pos - 1];
					gkey_type next_name = name_pos + 1;

					table[name_pos++][char_pos] = state{next_name, LexerToken::invalid};
				}

				gkey_type char_pos  = charset.column[name_pos - 1];
				gkey_type next_name = name_pos + 1;

				table[name_pos][char_pos] = state{next_name, Token};
			}

			nik_ce const state & move(const state & s, gcchar_type c) const
			{
				return table[s.name][charset.map(c)];
			}

			nik_ce lexeme lex(gstring_type b, gstring_type e) const
			{
				b = skip_whitespace(b, e);
				gstring_type m = b;

				state s = state{LexerName::initial, LexerToken::invalid};

				while (m != e && s.name != LexerName::empty) s = move(s, *(m++));

				return lexeme{b, m, s.token};
			}
	};

	template<auto U_dfa>
	nik_ce bool recognized_by(lexeme & c)
	{
		using DFA = T_store_U<U_dfa>;

		DFA dfa{};

		return true;
	}

/***********************************************************************************************************************/

// statement:

	nik_ce auto statement_dfa() { return dfa_charset(";"); }

	using T_statement_dfa       = KeywordDFA<statement_dfa, LexerToken::statement>;
	nik_ce auto U_statement_dfa = U_store_T<T_statement_dfa>;

/***********************************************************************************************************************/

// period:

	nik_ce auto period_dfa() { return dfa_charset("."); }

	using T_period_dfa       = KeywordDFA<period_dfa, LexerToken::period>;
	nik_ce auto U_period_dfa = U_store_T<T_period_dfa>;

/***********************************************************************************************************************/

// underscore:

	nik_ce auto underscore_dfa() { return dfa_charset("_"); }

	using T_underscore_dfa       = KeywordDFA<underscore_dfa, LexerToken::underscore>;
	nik_ce auto U_underscore_dfa = U_store_T<T_underscore_dfa>;

/***********************************************************************************************************************/

// equal:

	nik_ce auto equal_dfa() { return dfa_charset("="); }

	using T_equal_dfa       = KeywordDFA<equal_dfa, LexerToken::equal>;
	nik_ce auto U_equal_dfa = U_store_T<T_equal_dfa>;

/***********************************************************************************************************************/

// test:

	nik_ce auto test_dfa() { return dfa_charset("test"); }

	using T_test_dfa       = KeywordDFA<test_dfa, LexerToken::test>;
	nik_ce auto U_test_dfa = U_store_T<T_test_dfa>;

/***********************************************************************************************************************/

// goto:

	nik_ce auto goto_dfa() { return dfa_charset("goto"); }

	using T_goto_dfa       = KeywordDFA<goto_dfa, LexerToken::go_to>;
	nik_ce auto U_goto_dfa = U_store_T<T_goto_dfa>;

/***********************************************************************************************************************/

// branch:

	nik_ce auto branch_dfa() { return dfa_charset("branch"); }

	using T_branch_dfa       = KeywordDFA<branch_dfa, LexerToken::branch>;
	nik_ce auto U_branch_dfa = U_store_T<T_branch_dfa>;

/***********************************************************************************************************************/

// return:

	nik_ce auto return_dfa() { return dfa_charset("return"); }

	using T_return_dfa       = KeywordDFA<return_dfa, LexerToken::re_turn>;
	nik_ce auto U_return_dfa = U_store_T<T_return_dfa>;

/***********************************************************************************************************************/

// generic assembly:

	struct GenericAssemblyDFA
	{
		// name:

			nik_ces gkey_type name_empty				= 0;
			nik_ces gkey_type name_initial				= 1;

			nik_ces gkey_type name_underscore_latin_alphanumeric	= 2;
			nik_ces gkey_type name_ulan 				= name_underscore_latin_alphanumeric;
			nik_ces gkey_type name_colon				= 3;

			nik_ces gkey_type name_size				= 4;

		// state:

			nik_ces state state_empty     { name_empty   , LexerToken::invalid    };
			nik_ces state state_initial   { name_initial , LexerToken::invalid    };

			nik_ces state state_ulan      { name_ulan    , LexerToken::identifier };
			nik_ces state state_colon     { name_colon   , LexerToken::label      };

		// charset:

			nik_ces gkey_type charset_any				= 0;

			nik_ces gkey_type charset_underscore_latin_alphabet	= 1;
			nik_ces gkey_type charset_ula				= charset_underscore_latin_alphabet;
			nik_ces gkey_type charset_digit				= 2;
			nik_ces gkey_type charset_colon				= 3;

			nik_ces gkey_type charset_size				= 4;

			nik_ces gkey_type charset(gcchar_type c)
			{
				if      (matches_digit(c)                    ) return charset_digit;
				else if (matches_underscore_latin_alphabet(c)) return charset_ula;
				else if (c == ':'                            ) return charset_colon;
				else                                           return charset_any;
			}

		// table:

			state table[name_size][charset_size];

			nik_ce GenericAssemblyDFA() : table{}
			{
				table [ name_initial ][ charset_ula   ] = state_ulan;

				table [ name_ulan    ][ charset_ula   ] = state_ulan;
				table [ name_ulan    ][ charset_digit ] = state_ulan;
				table [ name_ulan    ][ charset_colon ] = state_colon;
			}

			nik_ce auto move(const state & s, gcchar_type c) const
			{
				return table[s.name][charset(c)];
			}

			nik_ce auto lex(gstring_type b, gstring_type e) const
			{
				lexeme current{b, e, LexerToken::invalid};

				if      (recognized_by< U_statement_dfa  >(current)) statement_action  (current);
				else if (recognized_by< U_period_dfa     >(current)) period_action     (current);
				else if (recognized_by< U_underscore_dfa >(current)) underscore_action (current);
				else if (recognized_by< U_equal_dfa      >(current)) equal_action      (current);

				else if (recognized_by< U_test_dfa       >(current)) test_action       (current);
				else if (recognized_by< U_goto_dfa       >(current)) goto_action       (current);
				else if (recognized_by< U_branch_dfa     >(current)) branch_action     (current);
				else if (recognized_by< U_return_dfa     >(current)) return_action     (current);

				else                                                 lex_action        (current);

				return current;
			}

			nik_ce void statement_action(lexeme & c) const
			{
			//	auto statement_lexeme = statement_dfa.lex(c.start, c.finish);

			//	if (_lexeme.token == LexerToken::) ;
			}

			nik_ce void period_action(lexeme & c) const
			{
			//	auto period_lexeme = period_dfa.lex(c.start, c.finish);
			}

			nik_ce void underscore_action(lexeme & c) const
			{
			//	auto underscore_lexeme = underscore_dfa.lex(c.start, c.finish);
			}

			nik_ce void equal_action(lexeme & c) const
			{
			//	auto equal_lexeme = equal_dfa.lex(c.start, c.finish);
			}

			nik_ce void test_action(lexeme & c) const
			{
			//	auto test_lexeme = test_dfa.lex(c.start, c.finish);
			}

			nik_ce void goto_action(lexeme & c) const
			{
			//	auto goto_lexeme = goto_dfa.lex(c.start, c.finish);
			}

			nik_ce void branch_action(lexeme & c) const
			{
			//	auto branch_lexeme = branch_dfa.lex(c.start, c.finish);
			}

			nik_ce void return_action(lexeme & c) const
			{
			//	auto return_lexeme = return_dfa.lex(c.start, c.finish);
			}

			nik_ce void lex_action(lexeme & c) const
			{
			//	gstring_type m = b;

			//	state s = state{LexerName::initial, LexerToken::invalid};

			//	while (m != e && s.name != LexerName::empty) s = move(s, *(m++));
			}
	};

	nik_ce auto generic_assembly_dfa = GenericAssemblyDFA{};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // cctmp_generics

