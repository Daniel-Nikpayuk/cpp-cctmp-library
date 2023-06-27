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

namespace chord {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

	using gkey_type							= cctmp::gkey_type;

	using gindex_type						= cctmp::gindex_type;
	using gcindex_type						= cctmp::gcindex_type;

	using gchar_type						= cctmp::gchar_type;
	using gcchar_type						= cctmp::gcchar_type;

	using gstring_type						= cctmp::gstring_type;
	using gcstring_type						= cctmp::gcstring_type;

	nik_ce auto U_gkey_type						= cctmp::U_gkey_type;
	nik_ce auto U_gchar_type					= cctmp::U_gchar_type;

	using state_type						= cctmp::state_type;
	using cstate_type						= cctmp::cstate_type;
	using token_type						= cctmp::token_type;
	using ctoken_type						= cctmp::ctoken_type;

	using StateName							= cctmp::StateName;
	using TokenName							= cctmp::TokenName;

	nik_ce auto U_state_type					= cctmp::U_state_type;
	nik_ce auto U_token_type					= cctmp::U_token_type;

	template<typename T, typename S = gindex_type>
	using cselector							= cctmp::cselector<T, S>;

	using lexeme							= cctmp::lexeme;
	using clexeme							= cctmp::clexeme;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// generic assembly:

/***********************************************************************************************************************/

// transition table:

	struct T_generic_assembly_dftt
	{
		struct Token
		{
			enum : token_type
			{
				invalid = TokenName::invalid,
				empty = TokenName::dimension,
				prompt     ,
				identifier ,
				copy       ,
				paste      ,
				quote      ,
				statement  ,
				label      ,
				re_turn    ,
				go_to      ,
				mu_table   ,
				apply      ,
				test       ,
				branch     ,
				vo_id      ,
				assign     ,

			//	keyword_label_error ,

				dimension
			};
		};

		struct State
		{
			enum : state_type
			{
				empty       = StateName::empty,
				initial     = StateName::initial,
				ulan        , // underscore latin alphanumeric
				semicolon   ,
				octothorpe  ,
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

			nik_ces auto accept = cctmp::table
			(
				U_state_type, U_token_type,

				cctmp::pair( ulan        , Token::identifier  ),
				cctmp::pair( semicolon   , Token::statement   ),
				cctmp::pair( octothorpe  , Token::assign      ),
				cctmp::pair( equal       , Token::apply       ),
				cctmp::pair( punctuation , Token::mu_table    ),
				cctmp::pair( period      , Token::copy        ),
				cctmp::pair( colon       , Token::label       ),
				cctmp::pair( r_quote     , Token::quote       )
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
				octothorpe  ,
				equal       ,
				punctuation ,
				period      ,
				colon       ,
				quote       ,
				backslash   ,
				dimension
			};

			nik_ces auto charmap = cctmp::table // 00_grammar table
			(
				U_gchar_type, U_gkey_type,

				cctmp::pair( ';'  , Charset::semicolon   ),
				cctmp::pair( '#'  , Charset::octothorpe  ),
				cctmp::pair( '='  , Charset::equal       ),
				cctmp::pair( '!'  , Charset::punctuation ),
				cctmp::pair( '.'  , Charset::period      ),
				cctmp::pair( ':'  , Charset::colon       ),
				cctmp::pair( '\'' , Charset::quote       ),
				cctmp::pair( '\\' , Charset::backslash   )
			);

			nik_ces gkey_type map(gcchar_type c)
			{
				if      (cctmp::matches_ula(c))   return Charset::ula;
				else if (cctmp::matches_digit(c)) return Charset::digit;
				else                              return charmap.lookup(c, Charset::other);
			}
		};

		state_type table[State::dimension][Charset::dimension];

		nik_ce T_generic_assembly_dftt() : table{}
		{
			table[ State::initial ][ Charset::ula         ] = State::ulan;
			table[ State::initial ][ Charset::semicolon   ] = State::semicolon;
			table[ State::initial ][ Charset::octothorpe  ] = State::octothorpe;
			table[ State::initial ][ Charset::equal       ] = State::equal;
			table[ State::initial ][ Charset::punctuation ] = State::punctuation;
			table[ State::initial ][ Charset::period      ] = State::period;
			table[ State::initial ][ Charset::quote       ] = State::l_quote;

			table[ State::ulan    ][ Charset::ula         ] = State::ulan;
			table[ State::ulan    ][ Charset::digit       ] = State::ulan;
			table[ State::ulan    ][ Charset::colon       ] = State::colon;

			cctmp::T_generic_lexer_tt::set_backslash_entries<State, Charset>(table);
		}

		nik_ce cstate_type move(cstate_type s, gcchar_type c) const
			{ return table[s][Charset::map(c)]; }
	};

/***********************************************************************************************************************/

// automaton:

	struct T_generic_assembly_dfa
	{
		using T_dftt			= T_generic_assembly_dftt;
		using Token			= typename T_dftt::Token;
		nik_ces auto value		= T_dftt{};
		nik_ces auto accept		= T_dftt::State::accept;

		nik_ces auto paste_charset  () { return cctmp::dfa_charset("_");      }
		nik_ces auto void_charset   () { return cctmp::dfa_charset("void");   }
		nik_ces auto test_charset   () { return cctmp::dfa_charset("test");   }
		nik_ces auto goto_charset   () { return cctmp::dfa_charset("goto");   }
		nik_ces auto branch_charset () { return cctmp::dfa_charset("branch"); }
		nik_ces auto return_charset () { return cctmp::dfa_charset("return"); }
	};

/***********************************************************************************************************************/

// interface:

	struct T_generic_assembly_lexer
	{
		using T_dfa			= T_generic_assembly_dfa;
		using Token			= typename T_dfa::Token;

		using T_paste_lexer		= cctmp::T_keyword_lexer< T_dfa::paste_charset  , Token::paste   >;
		using T_void_lexer		= cctmp::T_keyword_lexer< T_dfa::void_charset   , Token::vo_id   >;
		using T_test_lexer		= cctmp::T_keyword_lexer< T_dfa::test_charset   , Token::test    >;
		using T_goto_lexer		= cctmp::T_keyword_lexer< T_dfa::goto_charset   , Token::go_to   >;
		using T_branch_lexer		= cctmp::T_keyword_lexer< T_dfa::branch_charset , Token::branch  >;
		using T_return_lexer		= cctmp::T_keyword_lexer< T_dfa::return_charset , Token::re_turn >;

		nik_ces void lex(lexeme & l)
		{
			cctmp::T_generic_lexer<T_dfa>::lex(l);

			token_type t = T_dfa::accept.lookup(l.token, TokenName::invalid);

			return keyword_check(l, t);
		}

		nik_ces void keyword_check(lexeme & l, ctoken_type t)
		{
			token_type rt = t;

			auto csel = l.left_cselect();

			switch (t)
			{
				case Token::identifier:
				{
					ctoken_type t0 = keyword(csel);
					rt = (t0 == TokenName::invalid) ? t : t0;
					break;
				}
				case Token::label:
				{
					csel.downright();
					ctoken_type t0 = keyword(csel);
				//	ctoken_type t1 = Token::keyword_label_error;
				//	rt = (t0 == TokenName::invalid) ? t : t1;
					rt = (t0 == TokenName::invalid) ? t : t0;
					break;
				}
			}

			l.token = (gindex_type) rt;
		}

		nik_ces token_type keyword(const cselector<char> & s)
		{
			token_type val = TokenName::invalid;

			switch (s.size())
			{
				case  1 : { val = keyword_1  (s); break; }
				case  4 : { val = keyword_4  (s); break; }
				case  6 : { val = keyword_6  (s); break; }
			}

			return val;
		}

		nik_ces token_type keyword_1(const cselector<char> & s)
		{
			if   (cctmp::recognizes< T_paste_lexer >(s)) return T_paste_lexer::token;
			else                                         return TokenName::invalid;
		}

		nik_ces token_type keyword_4(const cselector<char> & s)
		{
			if      (cctmp::recognizes< T_void_lexer >(s)) return T_void_lexer::token;
			else if (cctmp::recognizes< T_test_lexer >(s)) return T_test_lexer::token;
			else if (cctmp::recognizes< T_goto_lexer >(s)) return T_goto_lexer::token;
			else                                           return TokenName::invalid;
		}

		nik_ces token_type keyword_6(const cselector<char> & s)
		{
			if      (cctmp::recognizes< T_branch_lexer >(s)) return T_branch_lexer::token;
			else if (cctmp::recognizes< T_return_lexer >(s)) return T_return_lexer::token;
			else                                             return TokenName::invalid;
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace chord

