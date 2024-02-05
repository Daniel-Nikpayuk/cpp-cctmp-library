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

namespace chord {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// cctmp:

	template<auto U>
	using T_store_U						= cctmp::T_store_U<U>;

	template<auto... Vs>
	using T_pack_Vs						= cctmp::T_pack_Vs<Vs...>;

	template<typename T>
	nik_ce auto U_store_T					= cctmp::U_store_T<T>;

	template<template<auto...> typename B>
	nik_ce auto U_store_B					= cctmp::U_store_B<B>;

	template<typename... Ts>
	nik_ce auto U_pack_Ts					= cctmp::U_pack_Ts<Ts...>;

	template<auto V> nik_ce auto _static_callable_		= cctmp::_static_callable_<V>;

	template<auto U>
	nik_ce auto & member_value_U				= cctmp::member_value_U<U>;

	using gkey_type						= cctmp::gkey_type;
	using gckey_type					= cctmp::gckey_type;
	using gchar_type					= cctmp::gchar_type;
	using gcchar_type					= cctmp::gcchar_type;
	using gindex_type					= cctmp::gindex_type;
	using gcindex_type					= cctmp::gcindex_type;

	nik_ce auto U_gkey_type					= cctmp::U_gkey_type;
	nik_ce auto U_gchar_type				= cctmp::U_gchar_type;

	nik_ce auto _zero					= cctmp::_zero;
	nik_ce auto _one					= cctmp::_one;
	nik_ce auto _two					= cctmp::_two;
	nik_ce auto _three					= cctmp::_three;
	nik_ce auto _four					= cctmp::_four;
	nik_ce auto _five					= cctmp::_five;
	nik_ce auto _six					= cctmp::_six;
	nik_ce auto _seven					= cctmp::_seven;
	nik_ce auto _eight					= cctmp::_eight;
	nik_ce auto _nine					= cctmp::_nine;
	nik_ce auto _ten					= cctmp::_ten;

	template<auto... Vs>
	nik_ce auto _subarray_same_				= cctmp::_subarray_same_<Vs...>;

	template<auto f>
	nik_ce auto _wrap_					= cctmp::_wrap_<f>;

	template<auto Op, typename T>
	using modify_type					= cctmp::modify_type<Op, T>;

	nik_ce auto _from_const_				= cctmp::_from_const_;
	nik_ce auto _from_reference_				= cctmp::_from_reference_;

	template<auto... Vs> nik_ce auto car_			= cctmp::car_<Vs...>;
	template<auto... Vs> nik_ce auto cdr_			= cctmp::cdr_<Vs...>;
	template<auto... Vs> nik_ce auto push_			= cctmp::push_<Vs...>;
	template<auto... Vs> nik_ce auto unpack_		= cctmp::unpack_<Vs...>;
	template<auto... Vs> nik_ce auto map_			= cctmp::map_<Vs...>;

	using strlit_type					= cctmp::strlit_type;
	nik_ce auto U_strlit_type				= cctmp::U_strlit_type;

	template<typename T, typename S = gindex_type>
	using cselector						= cctmp::cselector<T, S>;

	template<typename Type, auto Size>
	using sequence						= cctmp::sequence<Type, Size>;

// assembly:

	using AN						= assembly::AN;
	using AT						= assembly::AT;
	using AAN						= assembly::AAN;
	using AAT						= assembly::AAT;

	template<auto... Vs>
	using T_assembly_compound				= assembly::T_assembly_compound<Vs...>;

// generator:

	using gstring_type					= generator::gstring_type;
	using gcstring_type					= generator::gcstring_type;

	using state_type					= generator::state_type;
	using cstate_type					= generator::cstate_type;
	using token_type					= generator::token_type;
	using ctoken_type					= generator::ctoken_type;

	using StateName						= generator::StateName;
	using TokenName						= generator::TokenName;

	nik_ce auto U_state_type				= generator::U_state_type;
	nik_ce auto U_token_type				= generator::U_token_type;

	using lexeme						= generator::lexeme;
	using clexeme						= generator::clexeme;

	using action_type					= generator::action_type;
	nik_ce auto U_action_type				= generator::U_action_type;

	using sxt_pair						= cctmp::pair<strlit_type, token_type>;
	using sxa_pair						= cctmp::pair<strlit_type, action_type>;

	using symbol_type					= generator::symbol_type;
	using csymbol_type					= generator::csymbol_type;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// chord:

/***********************************************************************************************************************/

// transition table:

	struct T_chord_dftt
	{
		struct Token
		{
			enum : token_type
			{
				invalid     = TokenName::invalid,
				empty       = TokenName::dimension,
				prompt      ,
				identifier  ,
				number      ,
				declare     ,
				define      ,
				copy        ,
				paste       ,
				quote       ,
				statement   ,
				label       ,
				re_turn     ,
				go_to       ,
				tail        ,
				mu_table    ,
				apply       ,
				test        ,
				branch      ,
				vo_id       ,
				assign      ,

				l_scope     ,
				r_scope     ,
				bar         ,
				identity    ,
				dereference ,
				caret       ,
				increment   ,
				decrement   ,
				tilde       ,
				l_closed    ,
				r_closed    ,
				l_open      ,
				r_open      ,
				l_fixed     ,
				r_fixed     ,
				comma       ,

				argpose     ,
				subpose     ,
				curry       ,

				repeat      ,
				map         ,
				fold        ,
				find        ,
				sift        ,

			//	keyword_label_error ,

				dimension
			};
		};

		struct State
		{
			enum : state_type
			{
				empty         = StateName::empty,
				initial       = StateName::initial,
				ulan          , // underscore latin alphanumeric
				numeral       ,
				semicolon     ,
				octothorpe    ,
				equal         ,
				punctuation   ,
				period        ,
				colon         ,

				l_angle       ,
				r_angle       ,
				bar           ,
				at            ,
				star          ,
				caret         ,
				plus          ,
				dash          ,
				tilde         ,
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

			nik_ces auto accept = cctmp::table
			(
				U_state_type, U_token_type,

				cctmp::pair( ulan          , Token::identifier  ),
				cctmp::pair( numeral       , Token::number      ),
				cctmp::pair( semicolon     , Token::statement   ),
				cctmp::pair( octothorpe    , Token::assign      ),
				cctmp::pair( equal         , Token::apply       ),
				cctmp::pair( punctuation   , Token::mu_table    ),
				cctmp::pair( period        , Token::copy        ),
				cctmp::pair( colon         , Token::label       ),

				cctmp::pair( l_brace       , Token::l_scope     ),
				cctmp::pair( r_brace       , Token::r_scope     ),
				cctmp::pair( bar           , Token::bar         ),
				cctmp::pair( at            , Token::identity    ),
				cctmp::pair( star          , Token::dereference ),
				cctmp::pair( caret         , Token::caret       ),
				cctmp::pair( plus          , Token::increment   ),
				cctmp::pair( dash          , Token::decrement   ),
				cctmp::pair( tilde         , Token::tilde       ),
				cctmp::pair( l_bracket     , Token::l_closed    ),
				cctmp::pair( r_bracket     , Token::r_closed    ),
				cctmp::pair( l_parenthesis , Token::l_open      ),
				cctmp::pair( r_parenthesis , Token::r_open      ),
				cctmp::pair( l_angle       , Token::l_fixed     ),
				cctmp::pair( r_angle       , Token::r_fixed     ),
				cctmp::pair( comma         , Token::comma       ),

				cctmp::pair( r_quote       , Token::quote       )
			);
		};

		struct Charset
		{
			enum : gkey_type
			{
				other         = 0,
				ula           , // underscore latin alphabet
				digit         ,
				semicolon     ,
				octothorpe    ,
				equal         ,
				punctuation   ,
				period        ,
				colon         ,

				l_angle       ,
				r_angle       ,
				bar           ,
				at            ,
				star          ,
				caret         ,
				plus          ,
				dash          ,
				tilde         ,
				l_bracket     ,
				r_bracket     ,
				l_parenthesis ,
				r_parenthesis ,
				l_brace       ,
				r_brace       ,
				comma         ,

				quote         ,
				backslash     ,
				dimension
			};

			nik_ces auto charmap = cctmp::table // 00_grammar table
			(
				U_gchar_type, U_gkey_type,

				cctmp::pair( ';'  , Charset::semicolon     ),
				cctmp::pair( '#'  , Charset::octothorpe    ),
				cctmp::pair( '='  , Charset::equal         ),
				cctmp::pair( '!'  , Charset::punctuation   ),
				cctmp::pair( '.'  , Charset::period        ),
				cctmp::pair( ':'  , Charset::colon         ),

				cctmp::pair( '<'  , Charset::l_angle       ),
				cctmp::pair( '>'  , Charset::r_angle       ),
				cctmp::pair( '|'  , Charset::bar           ),
				cctmp::pair( '@'  , Charset::at            ),
				cctmp::pair( '*'  , Charset::star          ),
				cctmp::pair( '^'  , Charset::caret         ),
				cctmp::pair( '+'  , Charset::plus          ),
				cctmp::pair( '-'  , Charset::dash          ),
				cctmp::pair( '~'  , Charset::tilde         ),
				cctmp::pair( '['  , Charset::l_bracket     ),
				cctmp::pair( ']'  , Charset::r_bracket     ),
				cctmp::pair( '('  , Charset::l_parenthesis ),
				cctmp::pair( ')'  , Charset::r_parenthesis ),
				cctmp::pair( '{'  , Charset::l_brace       ),
				cctmp::pair( '}'  , Charset::r_brace       ),
				cctmp::pair( ','  , Charset::comma         ),

				cctmp::pair( '\'' , Charset::quote         ),
				cctmp::pair( '\\' , Charset::backslash     )
			);

			nik_ces gkey_type map(gcchar_type c)
			{
				if      (generator::matches_ula(c))   return Charset::ula;
				else if (generator::matches_digit(c)) return Charset::digit;
				else                                  return charmap.lookup(c, Charset::other);
			}
		};

		state_type table[State::dimension][Charset::dimension];

		nik_ce T_chord_dftt() : table{}
		{
			table[ State::initial ][ Charset::ula           ] = State::ulan;
			table[ State::initial ][ Charset::digit         ] = State::numeral;
			table[ State::initial ][ Charset::semicolon     ] = State::semicolon;
			table[ State::initial ][ Charset::octothorpe    ] = State::octothorpe;
			table[ State::initial ][ Charset::equal         ] = State::equal;
			table[ State::initial ][ Charset::punctuation   ] = State::punctuation;
			table[ State::initial ][ Charset::period        ] = State::period;

			table[ State::initial ][ Charset::l_angle       ] = State::l_angle;
			table[ State::initial ][ Charset::r_angle       ] = State::r_angle;
			table[ State::initial ][ Charset::bar           ] = State::bar;
			table[ State::initial ][ Charset::at            ] = State::at;
			table[ State::initial ][ Charset::star          ] = State::star;
			table[ State::initial ][ Charset::caret         ] = State::caret;
			table[ State::initial ][ Charset::plus          ] = State::plus;
			table[ State::initial ][ Charset::dash          ] = State::dash;
			table[ State::initial ][ Charset::tilde         ] = State::tilde;
			table[ State::initial ][ Charset::l_bracket     ] = State::l_bracket;
			table[ State::initial ][ Charset::r_bracket     ] = State::r_bracket;
			table[ State::initial ][ Charset::l_parenthesis ] = State::l_parenthesis;
			table[ State::initial ][ Charset::r_parenthesis ] = State::r_parenthesis;
			table[ State::initial ][ Charset::l_brace       ] = State::l_brace;
			table[ State::initial ][ Charset::r_brace       ] = State::r_brace;
			table[ State::initial ][ Charset::comma         ] = State::comma;

			table[ State::initial ][ Charset::quote         ] = State::l_quote;

			table[ State::ulan    ][ Charset::ula           ] = State::ulan;
			table[ State::ulan    ][ Charset::digit         ] = State::ulan;
			table[ State::ulan    ][ Charset::colon         ] = State::colon;

			table[ State::numeral ][ Charset::digit         ] = State::numeral;

			generator::T_generic_lexer_tt::set_backslash_entries<State, Charset>(table);
		}

		nik_ce cstate_type move(cstate_type s, gcchar_type c) const
			{ return table[s][Charset::map(c)]; }
	};

/***********************************************************************************************************************/

// automaton:

	struct T_chord_dfa
	{
		using T_dftt			= T_chord_dftt;
		using Token			= typename T_dftt::Token;
		nik_ces auto value		= T_dftt{};
		nik_ces auto accept		= T_dftt::State::accept;

		nik_ces auto paste_charset      () { return generator::dfa_charset("_");      }
		nik_ces auto void_charset       () { return generator::dfa_charset("void");   }
		nik_ces auto test_charset       () { return generator::dfa_charset("test");   }
		nik_ces auto goto_charset       () { return generator::dfa_charset("goto");   }
		nik_ces auto tail_charset       () { return generator::dfa_charset("tail");   }
		nik_ces auto branch_charset     () { return generator::dfa_charset("branch"); }
		nik_ces auto return_charset     () { return generator::dfa_charset("return"); }

		nik_ces auto declare_charset    () { return generator::dfa_charset("declare"); }
		nik_ces auto define_charset     () { return generator::dfa_charset("define");  }
		nik_ces auto argpose_charset    () { return generator::dfa_charset("argpose"); }
		nik_ces auto subpose_charset    () { return generator::dfa_charset("subpose"); }
		nik_ces auto curry_charset      () { return generator::dfa_charset("curry");   }

		nik_ces auto repeat_charset     () { return generator::dfa_charset("repeat"); }
		nik_ces auto map_charset        () { return generator::dfa_charset("map");    }
		nik_ces auto fold_charset       () { return generator::dfa_charset("fold");   }
		nik_ces auto find_charset       () { return generator::dfa_charset("find");   }
		nik_ces auto sift_charset       () { return generator::dfa_charset("sift");   }
	};

/***********************************************************************************************************************/

// interface:

	struct T_chord_lexer
	{
		using T_dfa			= T_chord_dfa;
		using Token			= typename T_dfa::Token;

		using T_paste_lexer		= generator::T_keyword_lexer< T_dfa::paste_charset  , Token::paste   >;
		using T_void_lexer		= generator::T_keyword_lexer< T_dfa::void_charset   , Token::vo_id   >;
		using T_test_lexer		= generator::T_keyword_lexer< T_dfa::test_charset   , Token::test    >;
		using T_goto_lexer		= generator::T_keyword_lexer< T_dfa::goto_charset   , Token::go_to   >;
		using T_tail_lexer		= generator::T_keyword_lexer< T_dfa::tail_charset   , Token::tail    >;
		using T_branch_lexer		= generator::T_keyword_lexer< T_dfa::branch_charset , Token::branch  >;
		using T_return_lexer		= generator::T_keyword_lexer< T_dfa::return_charset , Token::re_turn >;

		using T_declare_lexer		= generator::T_keyword_lexer< T_dfa::declare_charset , Token::declare >;
		using T_define_lexer		= generator::T_keyword_lexer< T_dfa::define_charset  , Token::define  >;
		using T_argpose_lexer		= generator::T_keyword_lexer< T_dfa::argpose_charset , Token::argpose >;
		using T_subpose_lexer		= generator::T_keyword_lexer< T_dfa::subpose_charset , Token::subpose >;
		using T_curry_lexer		= generator::T_keyword_lexer< T_dfa::curry_charset   , Token::curry   >;

		using T_repeat_lexer		= generator::T_keyword_lexer< T_dfa::repeat_charset , Token::repeat >;
		using T_map_lexer		= generator::T_keyword_lexer< T_dfa::map_charset    , Token::map    >;
		using T_fold_lexer		= generator::T_keyword_lexer< T_dfa::fold_charset   , Token::fold   >;
		using T_find_lexer		= generator::T_keyword_lexer< T_dfa::find_charset   , Token::find   >;
		using T_sift_lexer		= generator::T_keyword_lexer< T_dfa::sift_charset   , Token::sift   >;

		nik_ces void lex(lexeme & l)
		{
			generator::T_generic_lexer<T_dfa>::lex(l);

			token_type t = T_dfa::accept.lookup(l.token, Token::invalid);

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
					if (t0 != Token::invalid) rt = t0;
					break;
				}
				case Token::label:
				{
					csel.downright();
					ctoken_type t0 = keyword(csel);
				//	ctoken_type t1 = Token::keyword_label_error;
				//	rt = (t0 == Token::invalid) ? t : t1;
					if (t0 != Token::invalid) rt = t0;
					break;
				}
			}

			l.token = static_cast<gindex_type>(rt);
		}

		nik_ces token_type keyword(const cselector<char> & s)
		{
			token_type val = Token::invalid;

			switch (s.size())
			{
				case 1 : { val = keyword_1 (s); break; }
				case 3 : { val = keyword_3 (s); break; }
				case 4 : { val = keyword_4 (s); break; }
				case 5 : { val = keyword_5 (s); break; }
				case 6 : { val = keyword_6 (s); break; }
				case 7 : { val = keyword_7 (s); break; }
			}

			return val;
		}

		nik_ces token_type keyword_1(const cselector<char> & s)
		{
			if (generator::recognizes< T_paste_lexer >(s)) return T_paste_lexer::token;
			else                                           return Token::invalid;
		}

		nik_ces token_type keyword_3(const cselector<char> & s)
		{
			if (generator::recognizes< T_map_lexer >(s)) return T_map_lexer::token;
			else                                         return Token::invalid;
		}

		nik_ces token_type keyword_4(const cselector<char> & s)
		{
			if      (generator::recognizes< T_void_lexer >(s)) return T_void_lexer::token;
			else if (generator::recognizes< T_test_lexer >(s)) return T_test_lexer::token;
			else if (generator::recognizes< T_goto_lexer >(s)) return T_goto_lexer::token;
			else if (generator::recognizes< T_tail_lexer >(s)) return T_tail_lexer::token;
			else if (generator::recognizes< T_fold_lexer >(s)) return T_fold_lexer::token;
			else if (generator::recognizes< T_find_lexer >(s)) return T_find_lexer::token;
			else if (generator::recognizes< T_sift_lexer >(s)) return T_sift_lexer::token;
			else                                               return Token::invalid;
		}

		nik_ces token_type keyword_5(const cselector<char> & s)
		{
			if (generator::recognizes< T_curry_lexer >(s)) return T_curry_lexer::token;
			else                                           return Token::invalid;
		}

		nik_ces token_type keyword_6(const cselector<char> & s)
		{
			if      (generator::recognizes< T_define_lexer >(s)) return T_define_lexer::token;
			else if (generator::recognizes< T_branch_lexer >(s)) return T_branch_lexer::token;
			else if (generator::recognizes< T_return_lexer >(s)) return T_return_lexer::token;
			else if (generator::recognizes< T_repeat_lexer >(s)) return T_repeat_lexer::token;
			else                                                 return Token::invalid;
		}

		nik_ces token_type keyword_7(const cselector<char> & s)
		{
			if      (generator::recognizes< T_declare_lexer >(s)) return T_declare_lexer::token;
			else if (generator::recognizes< T_argpose_lexer >(s)) return T_argpose_lexer::token;
			else if (generator::recognizes< T_subpose_lexer >(s)) return T_subpose_lexer::token;
			else                                                  return Token::invalid;
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace chord

