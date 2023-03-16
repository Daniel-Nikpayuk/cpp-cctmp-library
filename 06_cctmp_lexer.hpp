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
	nik_ce auto U_gchar_type	= U_store_T<gchar_type>;
	nik_ce auto U_gcchar_type	= U_store_T<gcchar_type>;

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

// pointer:

/***********************************************************************************************************************/

	template<typename Type1, typename Type2>
	nik_ce auto ptr_diff_equal(const Type1 *b1, const Type1 *e1, const Type2 *b2, const Type2 *e2)
	{
		bool equal = ((e1 - b1) == (e2 - b2));

		while (equal && b1 != e1) equal = (*(b1++) == *(b2++));

		return equal;
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

	// latin lowercase:

		nik_ce bool matches_latin_lowercase(gcchar_type c) { return matches_charset(c, latin_lowercase); }

	// latin uppercase:

		nik_ce bool matches_latin_uppercase(gcchar_type c) { return matches_charset(c, latin_uppercase); }

/***********************************************************************************************************************/

// matches identifier:

	nik_ce bool matches_ula(gcchar_type c) // underscore latin alphabet
	{
		return (c == '_') || matches_latin_lowercase(c) || matches_latin_uppercase(c);
	}

	nik_ce bool matches_ulan(gcchar_type c) // underscore latin alphanumeric
	{
		return matches_digit(c) || matches_ula(c);
	}

/***********************************************************************************************************************/

// skip whitespace:

	nik_ce gstring_type skip_whitespace(gstring_type b, gcstring_type e)
	{
		while (b != e && matches_whitespace(*b)) ++b;

		return b;
	}

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
		using cstate_array = cstate_type*;

		enum : state_type
		{
			empty = 0,
			initial ,
			dimension
		};
	};

/***********************************************************************************************************************/

// token:

	using token_type  		= gchar_type;
	using ctoken_type 		= token_type const;
	nik_ce auto U_token_type	= U_store_T<token_type>;
	nik_ce auto U_ctoken_type	= U_store_T<ctoken_type>;

	struct TokenName
	{
		enum : token_type
		{
			invalid = '\0',
			keyword_label_error,
			dimension
		};
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// lexeme:

/***********************************************************************************************************************/

	struct lexeme
	{
		gstring_type  start;
		gstring_type finish;
		gindex_type   token;

		nik_ce lexeme() : start{}, finish{}, token{} { }
	};

	using clexeme = lexeme const;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// deterministic finite automata:

/***********************************************************************************************************************/

// generic lexer:

	template<typename T_dftt>
	struct T_generic_lexer
	{
		nik_ces auto transition_table = member_value_T<T_dftt>;

		nik_ces void lex(lexeme & l, gstring_type b, gstring_type e)
		{
			l.start = skip_whitespace(b, e);
			b       = l.start;

			state_type s = StateName::initial;

			while (b != e)
			{
				auto ns = transition_table.move(s, *b);

				if (ns == StateName::empty) break;
				else
				{
					s = ns;
					++b;
				}
			}

			l.finish = b;
			l.token  = s;
		}
	};

/***********************************************************************************************************************/

// recognizes:

	template<typename T_lexer>
	nik_ce gcbool_type recognizes(gstring_type b, gstring_type e)
	{
		lexeme l;

		T_lexer::lex(l, b, e);

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
		nik_ces auto charset			= member_value_U<static_charset>;
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

	template<auto CharsetCallable, auto Token>
	struct T_keyword_lexer
	{
		using T_dfa		= T_keyword_dfa<CharsetCallable>;
		nik_ces auto token	= Token;

		nik_ces void lex(lexeme & l, gstring_type b, gstring_type e)
		{
			T_generic_lexer<T_dfa>::lex(l, b, e);

			token_type t = (l.token == T_dfa::accept) ? Token : TokenName::invalid;

			l.token = (gindex_type) t;
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// generic assembly:

/***********************************************************************************************************************/

// transition table:

	struct T_generic_assembly_dftt
	{
		struct State
		{
			enum : state_type
			{
				empty       = StateName::empty,
				initial     = StateName::initial,
				ulan        , // underscore latin alphanumeric
				semicolon   ,
				equal       ,
				punctuation ,
				period      ,
				colon       ,
				backslash   ,
				no_quote    ,
				l_quote     ,
				r_quote     ,
				dimension
			};

			nik_ces auto status = table
			(
				U_state_type, U_gchar_type,

				pair( ulan        , 'i' ),
				pair( semicolon   , ';' ),
				pair( equal       , '=' ),
				pair( punctuation , '!' ),
				pair( period      , '.' ),
				pair( colon       , 'l' ),
				pair( r_quote     , 'q' )
			);
		};

		struct Charset
		{
			enum : gkey_type
			{
				other       = 0,
				ula         , // underscore latin alphabet
				digit       ,
				semicolon   ,
				equal       ,
				punctuation ,
				period      ,
				colon       ,
				backslash   ,
				quote       ,
				dimension
			};

			nik_ces auto charmap = table // 00_grammar table
			(
				U_gchar_type, U_gkey_type,

				pair( ';'  , Charset::semicolon   ),
				pair( '='  , Charset::equal       ),
				pair( '!'  , Charset::punctuation ),
				pair( '.'  , Charset::period      ),
				pair( ':'  , Charset::colon       ),
				pair( '\'' , Charset::quote       ),
				pair( '\\' , Charset::backslash   )
			);

			nik_ces gkey_type map(gcchar_type c)
			{
				if      (matches_ula(c))   return Charset::ula;
				else if (matches_digit(c)) return Charset::digit;
				else                       return charmap.lookup(c, Charset::other);
			}
		};

		state_type table[State::dimension][Charset::dimension];

		nik_ce T_generic_assembly_dftt() : table{}
		{
			table [ State::initial   ][ Charset::ula         ] = State::ulan;
			table [ State::initial   ][ Charset::semicolon   ] = State::semicolon;
			table [ State::initial   ][ Charset::equal       ] = State::equal;
			table [ State::initial   ][ Charset::punctuation ] = State::punctuation;
			table [ State::initial   ][ Charset::period      ] = State::period;
			table [ State::initial   ][ Charset::quote       ] = State::l_quote;

			table [ State::ulan      ][ Charset::ula         ] = State::ulan;
			table [ State::ulan      ][ Charset::digit       ] = State::ulan;
			table [ State::ulan      ][ Charset::colon       ] = State::colon;

			table [ State::l_quote   ][ Charset::ula         ] = State::no_quote;
			table [ State::l_quote   ][ Charset::digit       ] = State::no_quote;
			table [ State::l_quote   ][ Charset::semicolon   ] = State::no_quote;
			table [ State::l_quote   ][ Charset::equal       ] = State::no_quote;
			table [ State::l_quote   ][ Charset::punctuation ] = State::no_quote;
			table [ State::l_quote   ][ Charset::period      ] = State::no_quote;
			table [ State::l_quote   ][ Charset::colon       ] = State::no_quote;
			table [ State::l_quote   ][ Charset::backslash   ] = State::backslash;
			table [ State::l_quote   ][ Charset::other       ] = State::no_quote;

			table [ State::backslash ][ Charset::ula         ] = State::no_quote;
			table [ State::backslash ][ Charset::digit       ] = State::no_quote;
			table [ State::backslash ][ Charset::semicolon   ] = State::no_quote;
			table [ State::backslash ][ Charset::equal       ] = State::no_quote;
			table [ State::backslash ][ Charset::punctuation ] = State::no_quote;
			table [ State::backslash ][ Charset::period      ] = State::no_quote;
			table [ State::backslash ][ Charset::colon       ] = State::no_quote;
			table [ State::backslash ][ Charset::backslash   ] = State::no_quote;
			table [ State::backslash ][ Charset::quote       ] = State::no_quote;
			table [ State::backslash ][ Charset::other       ] = State::no_quote;

			table [ State::no_quote  ][ Charset::ula         ] = State::no_quote;
			table [ State::no_quote  ][ Charset::digit       ] = State::no_quote;
			table [ State::no_quote  ][ Charset::semicolon   ] = State::no_quote;
			table [ State::no_quote  ][ Charset::equal       ] = State::no_quote;
			table [ State::no_quote  ][ Charset::punctuation ] = State::no_quote;
			table [ State::no_quote  ][ Charset::period      ] = State::no_quote;
			table [ State::no_quote  ][ Charset::colon       ] = State::no_quote;
			table [ State::no_quote  ][ Charset::backslash   ] = State::backslash;
			table [ State::no_quote  ][ Charset::quote       ] = State::r_quote;
			table [ State::no_quote  ][ Charset::other       ] = State::no_quote;
		}

		nik_ce cstate_type move(cstate_type s, gcchar_type c) const
			{ return table[s][Charset::map(c)]; }
	};

/***********************************************************************************************************************/

// automaton:

	struct T_generic_assembly_dfa
	{
		using T_dftt			= T_generic_assembly_dftt;
		nik_ces auto value		= T_dftt{};
		nik_ces auto status		= T_dftt::State::status;

		nik_ces auto paste_charset      () { return dfa_charset("_");      }
		nik_ces auto void_charset       () { return dfa_charset("void");   }
		nik_ces auto test_charset       () { return dfa_charset("test");   }
		nik_ces auto goto_charset       () { return dfa_charset("goto");   }
		nik_ces auto branch_charset     () { return dfa_charset("branch"); }
		nik_ces auto return_charset     () { return dfa_charset("return"); }

		nik_ces auto repeat_charset     () { return dfa_charset("repeat"); }
		nik_ces auto map_charset        () { return dfa_charset("map"); }
		nik_ces auto fold_charset       () { return dfa_charset("fold"); }
		nik_ces auto find_first_charset () { return dfa_charset("find_first"); }
		nik_ces auto find_all_charset   () { return dfa_charset("find_all"); }
		nik_ces auto zip_charset        () { return dfa_charset("zip"); }
		nik_ces auto fasten_charset     () { return dfa_charset("fasten"); }
		nik_ces auto glide_charset      () { return dfa_charset("glide"); }
	};

/***********************************************************************************************************************/

// interface:

	struct T_generic_assembly_lexer
	{
		using T_dfa			= T_generic_assembly_dfa;

		using T_paste_lexer		= T_keyword_lexer< T_dfa::paste_charset      , '_' >;
		using T_void_lexer		= T_keyword_lexer< T_dfa::void_charset       , 'v' >;
		using T_test_lexer		= T_keyword_lexer< T_dfa::test_charset       , 't' >;
		using T_goto_lexer		= T_keyword_lexer< T_dfa::goto_charset       , 'g' >;
		using T_branch_lexer		= T_keyword_lexer< T_dfa::branch_charset     , 'b' >;
		using T_return_lexer		= T_keyword_lexer< T_dfa::return_charset     , 'r' >;

		using T_repeat_lexer		= T_keyword_lexer< T_dfa::repeat_charset     , '0' >;
		using T_map_lexer		= T_keyword_lexer< T_dfa::map_charset        , '1' >;
		using T_fold_lexer		= T_keyword_lexer< T_dfa::fold_charset       , '2' >;
		using T_find_first_lexer	= T_keyword_lexer< T_dfa::find_first_charset , '3' >;
		using T_find_all_lexer		= T_keyword_lexer< T_dfa::find_all_charset   , '4' >;
		using T_zip_lexer		= T_keyword_lexer< T_dfa::zip_charset        , '5' >;
		using T_fasten_lexer		= T_keyword_lexer< T_dfa::fasten_charset     , '6' >;
		using T_glide_lexer		= T_keyword_lexer< T_dfa::glide_charset      , '7' >;

		nik_ces void lex(lexeme & l, gstring_type b, gstring_type e)
		{
			T_generic_lexer<T_dfa>::lex(l, b, e);

			token_type t = T_dfa::status.lookup(l.token, TokenName::invalid);

			return keyword_check(l, t);
		}

		nik_ces void keyword_check(lexeme & l, ctoken_type t)
		{
			token_type rt = t;

			switch (t)
			{
				case 'i':
				{
					ctoken_type t0 = keyword(l.start, l.finish);
					rt = (t0 == TokenName::invalid) ? t : t0;
					break;
				}
				case 'l':
				{
					ctoken_type t0 = keyword(l.start, l.finish - 1);
					ctoken_type t1 = TokenName::keyword_label_error;
					rt = (t0 == TokenName::invalid) ? t : t1;
					break;
				}
			}

			l.token = (gindex_type) rt;
		}

		nik_ces token_type keyword(gstring_type b, gstring_type e)
		{
			token_type val = TokenName::invalid;

			switch (e - b)
			{
				case  1 : { val = keyword_1  (b, e); break; }
				case  3 : { val = keyword_3  (b, e); break; }
				case  4 : { val = keyword_4  (b, e); break; }
				case  5 : { val = keyword_5  (b, e); break; }
				case  6 : { val = keyword_6  (b, e); break; }
				case  8 : { val = keyword_8  (b, e); break; }
				case 10 : { val = keyword_10 (b, e); break; }
			}

			return val;
		}

		nik_ces token_type keyword_1(gstring_type b, gstring_type e)
		{
			if   (recognizes< T_paste_lexer >(b, e)) return T_paste_lexer::token;
			else                                     return TokenName::invalid;
		}

		nik_ces token_type keyword_3(gstring_type b, gstring_type e)
		{
			if      (recognizes< T_map_lexer >(b, e)) return T_map_lexer::token;
			else if (recognizes< T_zip_lexer >(b, e)) return T_zip_lexer::token;
			else                                      return TokenName::invalid;
		}

		nik_ces token_type keyword_4(gstring_type b, gstring_type e)
		{
			if      (recognizes< T_void_lexer >(b, e)) return T_void_lexer::token;
			else if (recognizes< T_test_lexer >(b, e)) return T_test_lexer::token;
			if      (recognizes< T_test_lexer >(b, e)) return T_test_lexer::token;
			else if (recognizes< T_goto_lexer >(b, e)) return T_goto_lexer::token;
			else if (recognizes< T_fold_lexer >(b, e)) return T_fold_lexer::token;
			else                                       return TokenName::invalid;
		}

		nik_ces token_type keyword_5(gstring_type b, gstring_type e)
		{
			if   (recognizes< T_glide_lexer >(b, e)) return T_glide_lexer::token;
			else                                     return TokenName::invalid;
		}

		nik_ces token_type keyword_6(gstring_type b, gstring_type e)
		{
			if      (recognizes< T_branch_lexer >(b, e)) return T_branch_lexer::token;
			else if (recognizes< T_return_lexer >(b, e)) return T_return_lexer::token;
			else if (recognizes< T_repeat_lexer >(b, e)) return T_repeat_lexer::token;
			else if (recognizes< T_fasten_lexer >(b, e)) return T_fasten_lexer::token;
			else                                         return TokenName::invalid;
		}

		nik_ces token_type keyword_8(gstring_type b, gstring_type e)
		{
			if   (recognizes< T_find_all_lexer >(b, e)) return T_find_all_lexer::token;
			else                                        return TokenName::invalid;
		}

		nik_ces token_type keyword_10(gstring_type b, gstring_type e)
		{
			if   (recognizes< T_find_first_lexer >(b, e)) return T_find_first_lexer::token;
			else                                          return TokenName::invalid;
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// chord assembly:

/***********************************************************************************************************************/

// transition table:

	struct T_chord_assembly_dftt
	{
		struct State
		{
			enum : state_type
			{
				empty         = StateName::empty,
				initial       = StateName::initial,
				ulan          , // underscore latin alphanumeric
				l_angle       ,
				r_angle       ,
				bar           ,
				at            ,
				star          ,
				plus          ,
				minus         ,
				l_bracket     ,
				r_bracket     ,
				l_parenthesis ,
				r_parenthesis ,
				l_brace       ,
				r_brace       ,
				comma         ,
				backslash     ,
				no_quote      ,
				l_quote       ,
				r_quote       ,
				dimension
			};

			nik_ces auto status = table
			(
				U_state_type, U_gchar_type,

				pair( ulan          , 'i' ),
				pair( l_angle       , '<' ),
				pair( r_angle       , '>' ),
				pair( bar           , '|' ),
				pair( at            , '@' ),
				pair( star          , '*' ),
				pair( plus          , '+' ),
				pair( minus         , '-' ),
				pair( l_bracket     , '[' ),
				pair( r_bracket     , ']' ),
				pair( l_parenthesis , '(' ),
				pair( r_parenthesis , ')' ),
				pair( l_brace       , '{' ),
				pair( r_brace       , '}' ),
				pair( comma         , ',' ),
				pair( r_quote       , 'q' )
			);
		};

		struct Charset
		{
			enum : gkey_type
			{
				other = 0,
				ula           , // underscore latin alphabet
				digit         ,
				l_angle       ,
				r_angle       ,
				bar           ,
				at            ,
				star          ,
				plus          ,
				minus         ,
				l_bracket     ,
				r_bracket     ,
				l_parenthesis ,
				r_parenthesis ,
				l_brace       ,
				r_brace       ,
				comma         ,
				backslash     ,
				quote         ,
				dimension
			};

			nik_ces auto charmap = table // 00_grammar table
			(
				U_gchar_type, U_gkey_type,

				pair( '<'  , Charset::l_angle       ),
				pair( '>'  , Charset::r_angle       ),
				pair( '|'  , Charset::bar           ),
				pair( '@'  , Charset::at            ),
				pair( '*'  , Charset::star          ),
				pair( '+'  , Charset::plus          ),
				pair( '-'  , Charset::minus         ),
				pair( '['  , Charset::l_bracket     ),
				pair( ']'  , Charset::r_bracket     ),
				pair( '('  , Charset::l_parenthesis ),
				pair( ')'  , Charset::r_parenthesis ),
				pair( '{'  , Charset::l_brace       ),
				pair( '}'  , Charset::r_brace       ),
				pair( ','  , Charset::comma         ),
				pair( '\'' , Charset::quote         ),
				pair( '\\' , Charset::backslash     )
			);

			nik_ces gkey_type map(gcchar_type c)
			{
				if      (matches_ula(c))   return Charset::ula;
				else if (matches_digit(c)) return Charset::digit;
				else                       return charmap.lookup(c, Charset::other);
			}
		};

		state_type table[State::dimension][Charset::dimension];

		nik_ce T_chord_assembly_dftt() : table{}
		{
		//	table [ State::initial   ][ Charset::ula         ] = State::ulan;
		//	table [ State::initial   ][ Charset::semicolon   ] = State::semicolon;
		//	table [ State::initial   ][ Charset::equal       ] = State::equal;
		//	table [ State::initial   ][ Charset::punctuation ] = State::punctuation;
		//	table [ State::initial   ][ Charset::period      ] = State::period;
		//	table [ State::initial   ][ Charset::quote       ] = State::l_quote;

		//	table [ State::ulan      ][ Charset::ula         ] = State::ulan;
		//	table [ State::ulan      ][ Charset::digit       ] = State::ulan;
		//	table [ State::ulan      ][ Charset::colon       ] = State::colon;

		//	table [ State::l_quote   ][ Charset::ula         ] = State::no_quote;
		//	table [ State::l_quote   ][ Charset::digit       ] = State::no_quote;
		//	table [ State::l_quote   ][ Charset::semicolon   ] = State::no_quote;
		//	table [ State::l_quote   ][ Charset::equal       ] = State::no_quote;
		//	table [ State::l_quote   ][ Charset::punctuation ] = State::no_quote;
		//	table [ State::l_quote   ][ Charset::period      ] = State::no_quote;
		//	table [ State::l_quote   ][ Charset::colon       ] = State::no_quote;
		//	table [ State::l_quote   ][ Charset::backslash   ] = State::backslash;
		//	table [ State::l_quote   ][ Charset::other       ] = State::no_quote;

		//	table [ State::backslash ][ Charset::ula         ] = State::no_quote;
		//	table [ State::backslash ][ Charset::digit       ] = State::no_quote;
		//	table [ State::backslash ][ Charset::semicolon   ] = State::no_quote;
		//	table [ State::backslash ][ Charset::equal       ] = State::no_quote;
		//	table [ State::backslash ][ Charset::punctuation ] = State::no_quote;
		//	table [ State::backslash ][ Charset::period      ] = State::no_quote;
		//	table [ State::backslash ][ Charset::colon       ] = State::no_quote;
		//	table [ State::backslash ][ Charset::backslash   ] = State::no_quote;
		//	table [ State::backslash ][ Charset::quote       ] = State::no_quote;
		//	table [ State::backslash ][ Charset::other       ] = State::no_quote;

		//	table [ State::no_quote  ][ Charset::ula         ] = State::no_quote;
		//	table [ State::no_quote  ][ Charset::digit       ] = State::no_quote;
		//	table [ State::no_quote  ][ Charset::semicolon   ] = State::no_quote;
		//	table [ State::no_quote  ][ Charset::equal       ] = State::no_quote;
		//	table [ State::no_quote  ][ Charset::punctuation ] = State::no_quote;
		//	table [ State::no_quote  ][ Charset::period      ] = State::no_quote;
		//	table [ State::no_quote  ][ Charset::colon       ] = State::no_quote;
		//	table [ State::no_quote  ][ Charset::backslash   ] = State::backslash;
		//	table [ State::no_quote  ][ Charset::quote       ] = State::r_quote;
		//	table [ State::no_quote  ][ Charset::other       ] = State::no_quote;
		}

		nik_ce cstate_type move(cstate_type s, gcchar_type c) const
			{ return table[s][Charset::map(c)]; }
	};

/***********************************************************************************************************************/

// automaton:

	struct T_chord_assembly_dfa
	{
		using T_dftt		= T_chord_assembly_dftt;
		nik_ces auto value	= T_dftt{};
		nik_ces auto status	= T_dftt::State::status;
	};

/***********************************************************************************************************************/

// interface:

	struct T_chord_assembly_lexer
	{
		using T_dfa = T_chord_assembly_dfa;

		nik_ces void lex(lexeme & l, gstring_type b, gstring_type e)
		{
			T_generic_lexer<T_dfa>::lex(l, b, e);

			token_type t = T_dfa::status.lookup(l.token, TokenName::invalid);

			return T_generic_assembly_lexer::keyword_check(l, t);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

