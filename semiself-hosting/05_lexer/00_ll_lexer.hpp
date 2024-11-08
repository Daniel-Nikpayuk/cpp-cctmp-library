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

// ll(1) lexer:

namespace cctmp {
namespace lexer {

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

// attributes:

/***********************************************************************************************************************/

// state:

	using state_type  		= gindex_type;
	using cstate_type 		= state_type const;
	nik_ce auto U_state_type	= U_store_T<state_type>;
	nik_ce auto U_cstate_type	= U_store_T<cstate_type>;

	struct StateName
	{
		enum : state_type
		{
			empty = 0,
			initial ,
			dimension
		};
	};

/***********************************************************************************************************************/

// token:

	using token_type  		= gindex_type;
	using ctoken_type 		= token_type const;
	nik_ce auto U_token_type	= U_store_T<token_type>;
	nik_ce auto U_ctoken_type	= U_store_T<ctoken_type>;

	struct TokenName
	{
		enum : token_type
		{
			invalid = 0,
			dimension
		};
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// lexeme:

/***********************************************************************************************************************/

	template<typename Type, typename SizeType = gindex_type>
	class T_lexeme : public citerator<Type, SizeType>
	{
		protected:

			using base			= citerator<Type, SizeType>;

		public:

			using type			= typename base::type;
			using type_ptr			= typename base::type_ptr;
			using type_ref			= typename base::type_ref;
			using type_cptr			= typename base::type_cptr;

			using ctype			= typename base::ctype;
			using ctype_ptr			= typename base::ctype_ptr;
			using ctype_cptr		= typename base::ctype_cptr;
			using ctype_ref			= typename base::ctype_ref;

			using size_type			= typename base::size_type;
			using csize_type		= typename base::csize_type;

			using cselector_type		= typename base::base;
			using cselector_ctype		= cselector_type const;
			using cselector_ctype_ptr	= cselector_ctype*;
			using cselector_ctype_cptr	= cselector_ctype_ptr const;

		protected:

			nik_ces auto _to_builtin_	= _string_to_builtin_<U_store_T<size_type>>;

		public:

			token_type token;

			nik_ce T_lexeme() : base{}, token{} { }
			nik_ce T_lexeme(const cselector<Type> & s) : base{s.cbegin(), s.cend()}, token{} { }

			nik_ce const T_lexeme & find(ctype_ref v)
				{ base::current = apply<base::_find_>(base::start, base::finish, v); return *this; }

			template<typename T>
			nik_ce const T_lexeme & find(const T & v)
				{ base::current = apply<base::_find_same_>(base::start, base::finish, v); return *this; }

			nik_ce const T_lexeme & left_find(ctype_ref v)
				{ base::current = apply<base::_find_>(base::start, base::current, v); return *this; }

			template<typename T>
			nik_ce const T_lexeme & left_find(const T & v)
				{ base::current = apply<base::_find_same_>(base::start, base::current, v); return *this; }

			nik_ce const T_lexeme & right_find(ctype_ref v)
				{ base::current = apply<base::_find_>(base::current, base::finish, v); return *this; }

			template<typename T>
			nik_ce const T_lexeme & right_find(const T & v)
				{ base::current = apply<base::_find_same_>(base::current, base::finish, v); return *this; }

			nik_ce auto contains(ctype_ref v) const { T_lexeme l{*this}; return l.find(v); }

			template<typename T>
			nik_ce auto contains(const T & v) const { T_lexeme l{*this}; return l.template find<T const&>(v); }

			nik_ce auto left_contains(ctype_ref v) const { T_lexeme l{*this}; return l.left_find(v); }

			template<typename T>
			nik_ce auto left_contains(const T & v) const
				{ T_lexeme l{*this}; return l.template left_find<T const&>(v); }

			nik_ce auto right_contains(ctype_ref v) const { T_lexeme l{*this}; return l.right_find(v); }

			template<typename T>
			nik_ce auto right_contains(const T & v) const
				{ T_lexeme l{*this}; return l.template right_find<T const&>(v); }

			nik_ce T_lexeme & operator -= (csize_type num) { base::current -= num; return *this; }
			nik_ce T_lexeme & operator += (csize_type num) { base::current += num; return *this; }
			nik_ce T_lexeme & operator -- () { --base::current; return *this; }
			nik_ce T_lexeme & operator ++ () { ++base::current; return *this; }

			nik_ce T_lexeme operator  - (csize_type num) { T_lexeme l{*this}; return l -= num; }
			nik_ce T_lexeme operator  + (csize_type num) { T_lexeme l{*this}; return l += num; }
			nik_ce T_lexeme operator -- (int) { T_lexeme l{*this}; --base::current; return l; }
			nik_ce T_lexeme operator ++ (int) { T_lexeme l{*this}; ++base::current; return l; }

			nik_ce void pullback() { base::start = base::current; }
			nik_ce T_lexeme & retract() { pullback(); return *this; }

			nik_ce void skip_whitespace()
			{
				while (base::not_end() && matches_whitespace(base::operator * ()))
					base::operator ++ ();

				pullback();
			}

			nik_ce csize_type to_number() const
				{ return apply<_to_builtin_>(base::start, base::current); }
	};

	using lexeme  = T_lexeme<gchar_type>;
	using clexeme = lexeme const;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// deterministic finite automata:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// generic lexer:

/***********************************************************************************************************************/

// transition table:

	struct T_generic_lexer_tt
	{
		template<typename State, typename Charset, typename T, auto N, auto M>
		nik_ces void set_backslash_entries(T (&t)[N][M])
		{
			for (gindex_type column = 0; column != M; ++column)
			{
				t[ State::l_quote   ][ column             ] = State::no_quote;
				t[ State::backslash ][ column             ] = State::no_quote;
				t[ State::no_quote  ][ column             ] = State::no_quote;
			}

			// corrections:

				t[ State::l_quote   ][ Charset::backslash ] = State::backslash;
				t[ State::l_quote   ][ Charset::quote     ] = State::empty;

				t[ State::no_quote  ][ Charset::backslash ] = State::backslash;
				t[ State::no_quote  ][ Charset::quote     ] = State::r_quote;
		}
	};

/***********************************************************************************************************************/

// interface:

	template<typename T_dftt>
	struct T_generic_lexer
	{
		nik_ces auto & transition_table = member_value_T<T_dftt>;

		nik_ces void lex(lexeme & l) // assumes {b, e, b}
		{
			l.skip_whitespace();
			l.token = StateName::initial;

			while (l.not_end())
			{
				auto ns = transition_table.move(l.token, *l);

				if (ns == StateName::empty) break;
				else
				{
					l.token = ns;
					++l;
				}
			}
		}
	};

/***********************************************************************************************************************/

// recognizes:

	template<typename T_lexer>
	nik_ce gcbool_type recognizes(const cselector<char> & s)
	{
		lexeme l{s};

		T_lexer::lex(l);

		return (l.token != TokenName::invalid);
	}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// (generic) keyword:

/***********************************************************************************************************************/

// dfa charset:

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

/***********************************************************************************************************************/

// transition table:

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

/***********************************************************************************************************************/

// automaton:

	template<auto CharsetCallable>
	struct T_keyword_dfa
	{
		nik_ces auto value  = T_keyword_dftt<CharsetCallable>{};
		nik_ces auto accept = value.charset.length + 1;
	};

/***********************************************************************************************************************/

// interface:

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

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// parser generator:

/***********************************************************************************************************************/

// transition table:

	struct T_parser_generator_dftt
	{
		struct Token
		{
			enum : token_type
			{
				invalid = TokenName::invalid,
				empty = TokenName::dimension,
				prompt              ,
				identifier          ,
				none                ,
				arrow               ,
				equal               ,
				colon               ,
				semicolon           ,
				dimension
			};
		};

		struct State
		{
			enum : state_type
			{
				empty      = StateName::empty,
				initial    = StateName::initial,
				any        ,
				dash       ,
				rangle     ,
				equal      ,
				colon      ,
				semicolon  ,
				backslash  ,
				whitespace ,
				dimension
			};

			nik_ces auto accept = table
			(
				U_state_type, U_token_type,

				pair( any       , Token::identifier ),
				pair( rangle    , Token::arrow      ),
				pair( equal     , Token::equal      ),
				pair( colon     , Token::colon      ),
				pair( semicolon , Token::semicolon  )
			);
		};

		struct Charset
		{
			enum : gkey_type
			{
				any        = 0,
				dash       ,
				rangle     ,
				equal      ,
				colon      ,
				semicolon  ,
				backslash  ,
				whitespace ,
				dimension
			};

			nik_ces auto charmap = table
			(
				U_gchar_type, U_gkey_type,

				pair( '-'  , Charset::dash      ),
				pair( '>'  , Charset::rangle    ),
				pair( '='  , Charset::equal     ),
				pair( ':'  , Charset::colon     ),
				pair( ';'  , Charset::semicolon ),
				pair( '\\' , Charset::backslash )
			);

			nik_ces gkey_type map(gcchar_type c)
			{
				if (matches_whitespace(c)) return Charset::whitespace;
				else                       return charmap.lookup(c, Charset::any);
			}
		};

		state_type table[State::dimension][Charset::dimension];

		nik_ce T_parser_generator_dftt() : table{}
		{
			table[ State::initial   ][ Charset::any       ] = State::any;
			table[ State::initial   ][ Charset::dash      ] = State::dash;
			table[ State::initial   ][ Charset::equal     ] = State::equal;
			table[ State::initial   ][ Charset::colon     ] = State::colon;
			table[ State::initial   ][ Charset::semicolon ] = State::semicolon;
			table[ State::initial   ][ Charset::backslash ] = State::backslash;

			table[ State::any       ][ Charset::any       ] = State::any;
			table[ State::any       ][ Charset::backslash ] = State::backslash;

			table[ State::backslash ][ Charset::dash      ] = State::any;
			table[ State::backslash ][ Charset::rangle    ] = State::any;
			table[ State::backslash ][ Charset::equal     ] = State::any;
			table[ State::backslash ][ Charset::colon     ] = State::any;
			table[ State::backslash ][ Charset::semicolon ] = State::any;
			table[ State::backslash ][ Charset::backslash ] = State::any;

			table[ State::dash      ][ Charset::rangle    ] = State::rangle;
		}

		nik_ce cstate_type move(cstate_type s, gcchar_type c) const
			{ return table[s][Charset::map(c)]; }
	};

/***********************************************************************************************************************/

// automaton:

	struct T_parser_generator_dfa
	{
		using T_dftt		= T_parser_generator_dftt;
		using Token		= typename T_dftt::Token;
		nik_ces auto value	= T_dftt{};
		nik_ces auto & accept	= T_dftt::State::accept;

		nik_ces auto short_empty_charset () { return dfa_charset("e"); }
		nik_ces auto long_empty_charset  () { return dfa_charset("empty"); }
	};

/***********************************************************************************************************************/

// interface:

	struct T_parser_generator_lexer
	{
		using T_dfa			= T_parser_generator_dfa;
		using Token			= typename T_dfa::Token;
		using T_short_empty_lexer	= T_keyword_lexer< T_dfa::short_empty_charset , Token::empty >;
		using T_long_empty_lexer	= T_keyword_lexer< T_dfa::long_empty_charset  , Token::empty >;

		nik_ces void lex(lexeme & l)
		{
			T_generic_lexer<T_dfa>::lex(l);

					// here l.token is the state.
			token_type t = T_dfa::accept.lookup(l.token, Token::invalid);

			keyword_check(l, t);
		}

		nik_ces void keyword_check(lexeme & l, token_type t) // is actually a state type.
		{
			switch (t)
			{
				case Token::identifier:
				{
					ctoken_type t0 = keyword(l.left_cselect());
					if (t0 != Token::invalid) t = t0;
					break;
				}
			}

			l.token = t;
		}

		nik_ces token_type keyword(const cselector<char> & s)
		{
			token_type val = Token::invalid;

			switch (s.size())
			{
				case 1 : { val = keyword_1(s); break; }
				case 5 : { val = keyword_5(s); break; }
			}

			return val;
		}

		nik_ces token_type keyword_1(const cselector<char> & s)
		{
			if (recognizes<T_short_empty_lexer>(s)) return T_short_empty_lexer::token;
			else                                    return Token::invalid;
		}

		nik_ces token_type keyword_5(const cselector<char> & s)
		{
			if (recognizes<T_long_empty_lexer>(s)) return T_long_empty_lexer::token;
			else                                   return Token::invalid;
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

}} // namespace cctmp::lexer

