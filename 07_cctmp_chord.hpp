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

// chord:

namespace cctmp {

/***********************************************************************************************************************/
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
				empty   = StateName::empty,
				initial = StateName::initial,
				underscore_latin_alphanumeric,
				ulan    = underscore_latin_alphanumeric,
				semicolon, equal, punctuation, period,
				colon, backslash, no_quote, l_quote, r_quote,
				dimension
			};

			nik_ces state_type accept[] =
			{
				ulan, semicolon, equal, punctuation, period, colon, r_quote
			};

			nik_ces token_type token[] =
			{
				'i', ';', '=', '!', '.', 'l', 'q'
			};
		};

		struct Charset
		{
			enum : gkey_type
			{
				other = 0,

				underscore_latin_alphabet,
				ula = underscore_latin_alphabet,
				digit, semicolon, equal, punctuation,
				period, colon, backslash, quote,

				l_angle, r_angle, l_brace, r_brace,
				l_bracket, r_bracket, l_parenthesis, r_parenthesis,
				comma, at, asterisk, plus, minus, bar, octothorpe,

				dimension
			};

			nik_ces gkey_type map(gcchar_type c)
			{
				if      (matches_underscore_latin_alphabet(c)) return Charset::ula;
				else if (matches_digit(c)                    ) return Charset::digit;
				else if (c == ';'                            ) return Charset::semicolon;
				else if (c == '='                            ) return Charset::equal;
				else if (c == '!'                            ) return Charset::punctuation;
				else if (c == '.'                            ) return Charset::period;
				else if (c == ':'                            ) return Charset::colon;
				else if (c == '\''                           ) return Charset::quote;
				else if (c == '\\'                           ) return Charset::backslash;
				else                                           return Charset::other;
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
		using T_dftt		= T_generic_assembly_dftt;

		using ArrayEnd		= T_store_U< _array_end_  >;
		using ArraySize		= T_store_U< _array_size_ >;

		nik_ces auto value	= T_dftt{};
		nik_ces auto accept	= T_dftt::State::accept;
		nik_ces auto end	= ArrayEnd::template result<>(T_dftt::State::accept);
		nik_ces auto size	= ArraySize::template result<>(T_dftt::State::accept);
		nik_ces auto token	= T_dftt::State::token;

		nik_ces auto paste_charset      () { return dfa_charset("_");      }
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

		nik_ces auto find_pos(cstate_type n) { return numeric_find_pos(n, accept, end); }
		nik_ces auto is_final(cstate_type n) { return (n != size); }
	};

/***********************************************************************************************************************/

// interface:

	struct T_generic_assembly_lexer
	{
		using T_dfa		= T_generic_assembly_dfa;

		using T_paste_lexer	= T_keyword_lexer< T_dfa::paste_charset  , '_' >;
		using T_test_lexer	= T_keyword_lexer< T_dfa::test_charset   , 't' >;
		using T_goto_lexer	= T_keyword_lexer< T_dfa::goto_charset   , 'g' >;
		using T_branch_lexer	= T_keyword_lexer< T_dfa::branch_charset , 'b' >;
		using T_return_lexer	= T_keyword_lexer< T_dfa::return_charset , 'r' >;

		nik_ces lexeme lex(gstring_type b, gstring_type e)
		{
			auto l = recognize<T_dfa>(b, e);
			auto n = T_dfa::find_pos(l.value);

			token_type t = TokenName::invalid;
			if (T_dfa::is_final(n)) t = T_dfa::token[n];

			return keyword_check(l.start, l.finish, t);
		}

		nik_ces lexeme keyword_check(gstring_type b, gstring_type e, ctoken_type t)
		{
			token_type rt = t;

			switch (t)
			{
				case 'i':
				{
					ctoken_type t0 = keyword(b, e);
					rt = (t0 == TokenName::invalid) ? t : t0;
					break;
				}
				case 'l':
				{
					ctoken_type t0 = keyword(b, e - 1);
					ctoken_type t1 = TokenName::keyword_label_error;
					rt = (t0 == TokenName::invalid) ? t : t1;
					break;
				}
			}

			return lexeme{b, e, (gindex_type) rt};
		}

		nik_ces token_type keyword(gstring_type b, gstring_type e)
		{
			token_type val = TokenName::invalid;

			switch (e - b)
			{
				case 1  : { val = keyword_1(b, e); break; }
				case 4  : { val = keyword_4(b, e); break; }
				case 6  : { val = keyword_6(b, e); break; }
			}

			return val;
		}

		nik_ces token_type keyword_1(gstring_type b, gstring_type e)
		{
			if   (recognizes< T_paste_lexer >(b, e)) return T_paste_lexer::token;
			else                                     return TokenName::invalid;
		}

		nik_ces token_type keyword_4(gstring_type b, gstring_type e)
		{
			if      (recognizes< T_test_lexer >(b, e)) return T_test_lexer::token;
			else if (recognizes< T_goto_lexer >(b, e)) return T_goto_lexer::token;
			else                                       return TokenName::invalid;
		}

		nik_ces token_type keyword_6(gstring_type b, gstring_type e)
		{
			if      (recognizes< T_branch_lexer >(b, e)) return T_branch_lexer::token;
			else if (recognizes< T_return_lexer >(b, e)) return T_return_lexer::token;
			else                                         return TokenName::invalid;
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

