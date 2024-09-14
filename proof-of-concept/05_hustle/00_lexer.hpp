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

namespace hustle {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// cctmp:

	using cctmp::T_store_U;
	using cctmp::T_pack_Vs;

	using cctmp::U_store_T;
	using cctmp::U_store_B;
	using cctmp::U_pack_Ts;
	using cctmp::_static_callable_;
	using cctmp::member_value_U;

	using cctmp::gkey_type;
	using cctmp::gckey_type;
	using cctmp::gchar_type;
	using cctmp::gcchar_type;
	using cctmp::gindex_type;
	using cctmp::gcindex_type;

	using cctmp::U_gkey_type;
	using cctmp::U_gchar_type;

	using cctmp::_zero;
	using cctmp::_one;
	using cctmp::_two;
	using cctmp::_three;
	using cctmp::_four;
	using cctmp::_five;
	using cctmp::_six;
	using cctmp::_seven;
	using cctmp::_eight;
	using cctmp::_nine;
	using cctmp::_ten;

	using cctmp::_subarray_same_;
	using cctmp::_wrap_;

	using cctmp::modify_type;

	using cctmp::_from_const_;
	using cctmp::_from_reference_;

	using cctmp::car_;
	using cctmp::cdr_;
	using cctmp::push_;
	using cctmp::unpack_;
	using cctmp::map_;

	using cctmp::strlit_type;
	using cctmp::U_strlit_type;

	using cctmp::cselector;
	using cctmp::sequence;

// assembly:

	using assembly::AN;
	using assembly::AT;
	using assembly::AAN;
	using assembly::AAT;

	using assembly::T_assembly_compound;

// generator:

	using generator::gstring_type;
	using generator::gcstring_type;

	using generator::state_type;
	using generator::cstate_type;
	using generator::token_type;
	using generator::ctoken_type;

	using generator::StateName;
	using generator::TokenName;

	using generator::U_state_type;
	using generator::U_token_type;

	using generator::lexeme;
	using generator::clexeme;

	using generator::action_type;
	using generator::U_action_type;

	using generator::symbol_type;
	using generator::csymbol_type;

	// syntactic sugar:

		using sxt_pair = cctmp::pair<strlit_type, token_type>;
		using sxa_pair = cctmp::pair<strlit_type, action_type>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// hustle assembly:

/***********************************************************************************************************************/

// transition table:

	struct T_hustle_dftt
	{
		struct Token
		{
			enum : token_type
			{
				invalid     = TokenName::invalid,
				empty       = TokenName::dimension,
				prompt      ,
				op_type     ,
				arg_type    ,

				identifier  ,
				octothorpe  ,
				boolean     ,
				bool_f      , // specialization
				bool_t      , // specialization
				n_number    ,
				r_number    ,
				character   ,
				string      ,

				if_         ,
				eq_         ,
				let         ,
				car         ,
				cdr         ,
				type        ,
				set_        ,
				cons        ,
				list        ,
				begin       ,
				quote       ,
				define      ,
				lambda      ,

				l_expr      ,
				r_expr      ,
				equal       ,
				compare_lt  ,
				compare_le  ,
				compare_gt  ,
				compare_ge  ,
				add         ,
				multiply    ,
				subtract    ,
				divide      ,

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
				l_paren     ,
				r_paren     ,
				arrow       ,
				colon       ,

				identifier  ,
				hash        , // # (boolean)
				boolean     ,
				n_numeral   ,
				r_numeral   ,
				period      ,
				character   ,
				string      ,

				equal       ,
				compare_lt  ,
				compare_le  ,
				compare_gt  ,
				compare_ge  ,
				plus        ,
				star        ,
				dash        ,
				slash       ,
				l_quote     ,

				dimension
			};

			nik_ces auto accept = cctmp::table
			(
				U_state_type, U_token_type,

				cctmp::pair( l_paren    , Token::l_expr     ),
				cctmp::pair( r_paren    , Token::r_expr     ),
				cctmp::pair( arrow      , Token::op_type    ),
				cctmp::pair( colon      , Token::arg_type   ),

				cctmp::pair( identifier , Token::identifier ),
				cctmp::pair( boolean    , Token::boolean    ),
				cctmp::pair( n_numeral  , Token::n_number   ),
				cctmp::pair( r_numeral  , Token::r_number   ),
				cctmp::pair( period     , Token::r_number   ),
				cctmp::pair( character  , Token::character  ),
				cctmp::pair( string     , Token::string     ),

				cctmp::pair( equal      , Token::equal      ),
				cctmp::pair( compare_lt , Token::compare_lt ),
				cctmp::pair( compare_le , Token::compare_le ),
				cctmp::pair( compare_gt , Token::compare_gt ),
				cctmp::pair( compare_ge , Token::compare_ge ),
				cctmp::pair( plus       , Token::add        ),
				cctmp::pair( star       , Token::multiply   ),
				cctmp::pair( dash       , Token::subtract   ),
				cctmp::pair( slash      , Token::divide     )
			);
		};

		struct Charset
		{
			enum : gkey_type
			{
				other       = 0,
				ula         , // underscore latin alphabet
				digit       ,
				quote       ,
				colon       ,
				period      ,
				l_paren     ,
				r_paren     ,
				question    ,
				octothorpe  ,
				punctuation ,

				equal       ,
				l_angle     ,
				r_angle     ,
				plus        ,
				star        ,
				dash        ,
				slash       ,

				backslash   ,
				dimension
			};

			nik_ces auto charmap = cctmp::table // 00_grammar table
			(
				U_gchar_type, U_gkey_type,

				cctmp::pair( '\'' , Charset::quote       ),
				cctmp::pair( ':'  , Charset::colon       ),
				cctmp::pair( '.'  , Charset::period      ),
				cctmp::pair( '('  , Charset::l_paren     ),
				cctmp::pair( ')'  , Charset::r_paren     ),
				cctmp::pair( '?'  , Charset::question    ),
				cctmp::pair( '#'  , Charset::octothorpe  ),
				cctmp::pair( '!'  , Charset::punctuation ),

				cctmp::pair( '='  , Charset::equal       ),
				cctmp::pair( '<'  , Charset::l_angle     ),
				cctmp::pair( '>'  , Charset::r_angle     ),
				cctmp::pair( '+'  , Charset::plus        ),
				cctmp::pair( '*'  , Charset::star        ),
				cctmp::pair( '-'  , Charset::dash        ),
				cctmp::pair( '/'  , Charset::slash       ),

				cctmp::pair( '\\' , Charset::backslash   )
			);

			nik_ces gkey_type map(gcchar_type c)
			{
				if      (generator::matches_ula(c))   return Charset::ula;
				else if (generator::matches_digit(c)) return Charset::digit;
				else                                  return charmap.lookup(c, Charset::other);
			}
		};

		state_type table[State::dimension][Charset::dimension];

		nik_ce T_hustle_dftt() : table{}
		{
			table[ State::initial    ][ Charset::ula         ] = State::identifier;
			table[ State::initial    ][ Charset::l_paren     ] = State::l_paren;
			table[ State::initial    ][ Charset::r_paren     ] = State::r_paren;
			table[ State::initial    ][ Charset::colon       ] = State::colon;
			table[ State::initial    ][ Charset::octothorpe  ] = State::hash;
			table[ State::initial    ][ Charset::digit       ] = State::n_numeral;
			table[ State::initial    ][ Charset::period      ] = State::period;
			table[ State::initial    ][ Charset::quote       ] = State::l_quote;
			table[ State::initial    ][ Charset::equal       ] = State::equal;
			table[ State::initial    ][ Charset::l_angle     ] = State::compare_lt;
			table[ State::initial    ][ Charset::r_angle     ] = State::compare_gt;
			table[ State::initial    ][ Charset::plus        ] = State::plus;
			table[ State::initial    ][ Charset::star        ] = State::star;
			table[ State::initial    ][ Charset::dash        ] = State::dash;
			table[ State::initial    ][ Charset::slash       ] = State::slash;

			table[ State::identifier ][ Charset::ula         ] = State::identifier;
			table[ State::identifier ][ Charset::digit       ] = State::identifier;
			table[ State::identifier ][ Charset::dash        ] = State::identifier;
			table[ State::identifier ][ Charset::question    ] = State::identifier;
			table[ State::identifier ][ Charset::punctuation ] = State::identifier;

			table[ State::hash       ][ Charset::ula         ] = State::boolean;

			table[ State::n_numeral  ][ Charset::digit       ] = State::n_numeral;
			table[ State::n_numeral  ][ Charset::period      ] = State::period;

			table[ State::r_numeral  ][ Charset::digit       ] = State::r_numeral;

			table[ State::period     ][ Charset::digit       ] = State::r_numeral;

			table[ State::l_quote    ][ Charset::ula         ] = State::character;

			table[ State::character  ][ Charset::ula         ] = State::string;

			table[ State::string     ][ Charset::ula         ] = State::string;

			table[ State::compare_lt ][ Charset::equal       ] = State::compare_le;

			table[ State::compare_gt ][ Charset::equal       ] = State::compare_ge;

			table[ State::dash       ][ Charset::r_angle     ] = State::arrow;

			// generator::T_generic_lexer_tt::set_backslash_entries<State, Charset>(table);
		}

		nik_ce cstate_type move(cstate_type s, gcchar_type c) const
			{ return table[s][Charset::map(c)]; }
	};

/***********************************************************************************************************************/

// automaton:

	struct T_hustle_dfa
	{
		using T_dftt			= T_hustle_dftt;
		using Token			= typename T_dftt::Token;
		nik_ces auto value		= T_dftt{};
		nik_ces auto accept		= T_dftt::State::accept;

		nik_ces auto if_charset         () { return generator::dfa_charset("if");     }
		nik_ces auto eq__charset        () { return generator::dfa_charset("eq?");    }
		nik_ces auto let_charset        () { return generator::dfa_charset("let");    }
		nik_ces auto car_charset        () { return generator::dfa_charset("car");    }
		nik_ces auto cdr_charset        () { return generator::dfa_charset("cdr");    }
		nik_ces auto type_charset       () { return generator::dfa_charset("type");   }
		nik_ces auto set__charset       () { return generator::dfa_charset("set!");   }
		nik_ces auto cons_charset       () { return generator::dfa_charset("cons");   }
		nik_ces auto list_charset       () { return generator::dfa_charset("list");   }
		nik_ces auto begin_charset      () { return generator::dfa_charset("begin");  }
		nik_ces auto quote_charset      () { return generator::dfa_charset("quote");  }
		nik_ces auto define_charset     () { return generator::dfa_charset("define"); }
		nik_ces auto lambda_charset     () { return generator::dfa_charset("lambda"); }
	};

/***********************************************************************************************************************/

// interface:

	struct T_hustle_lexer
	{
		using T_dfa			= T_hustle_dfa;
		using Token			= typename T_dfa::Token;

		using T_if_lexer		= generator::T_keyword_lexer< T_dfa::if_charset     , Token::if_     >;
		using T_eq__lexer		= generator::T_keyword_lexer< T_dfa::eq__charset    , Token::eq_     >;
		using T_let_lexer		= generator::T_keyword_lexer< T_dfa::let_charset    , Token::let     >;
		using T_car_lexer		= generator::T_keyword_lexer< T_dfa::car_charset    , Token::car     >;
		using T_cdr_lexer		= generator::T_keyword_lexer< T_dfa::cdr_charset    , Token::cdr     >;
		using T_type_lexer		= generator::T_keyword_lexer< T_dfa::type_charset   , Token::type    >;
		using T_set__lexer		= generator::T_keyword_lexer< T_dfa::set__charset   , Token::set_    >;
		using T_cons_lexer		= generator::T_keyword_lexer< T_dfa::cons_charset   , Token::cons    >;
		using T_list_lexer		= generator::T_keyword_lexer< T_dfa::list_charset   , Token::list    >;
		using T_begin_lexer		= generator::T_keyword_lexer< T_dfa::begin_charset  , Token::begin   >;
		using T_quote_lexer		= generator::T_keyword_lexer< T_dfa::quote_charset  , Token::quote   >;
		using T_define_lexer		= generator::T_keyword_lexer< T_dfa::define_charset , Token::define  >;
		using T_lambda_lexer		= generator::T_keyword_lexer< T_dfa::lambda_charset , Token::lambda  >;

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
				case Token::boolean:
				{
					auto c = *csel.clast();
					rt = (c == 'f') ? Token::bool_f :
					     (c == 't') ? Token::bool_t : Token::invalid ;
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
				case 2 : { val = keyword_2 (s); break; }
				case 3 : { val = keyword_3 (s); break; }
				case 4 : { val = keyword_4 (s); break; }
				case 5 : { val = keyword_5 (s); break; }
				case 6 : { val = keyword_6 (s); break; }
			}

			return val;
		}

		nik_ces token_type keyword_2(const cselector<char> & s)
		{
			if (generator::recognizes< T_if_lexer >(s)) return T_if_lexer::token;
			else                                        return Token::invalid;
		}

		nik_ces token_type keyword_3(const cselector<char> & s)
		{
			if      (generator::recognizes< T_eq__lexer >(s)) return T_eq__lexer::token;
			else if (generator::recognizes< T_let_lexer >(s)) return T_let_lexer::token;
			else if (generator::recognizes< T_car_lexer >(s)) return T_car_lexer::token;
			else if (generator::recognizes< T_cdr_lexer >(s)) return T_cdr_lexer::token;
			else                                              return Token::invalid;
		}

		nik_ces token_type keyword_4(const cselector<char> & s)
		{
			if      (generator::recognizes< T_type_lexer >(s)) return T_type_lexer::token;
			else if (generator::recognizes< T_set__lexer >(s)) return T_set__lexer::token;
			else if (generator::recognizes< T_cons_lexer >(s)) return T_cons_lexer::token;
			else if (generator::recognizes< T_list_lexer >(s)) return T_list_lexer::token;
			else                                               return Token::invalid;
		}

		nik_ces token_type keyword_5(const cselector<char> & s)
		{
			if      (generator::recognizes< T_begin_lexer >(s)) return T_begin_lexer::token;
			else if (generator::recognizes< T_quote_lexer >(s)) return T_quote_lexer::token;
			else                                                return Token::invalid;
		}

		nik_ces token_type keyword_6(const cselector<char> & s)
		{
			if      (generator::recognizes< T_define_lexer >(s)) return T_define_lexer::token;
			else if (generator::recognizes< T_lambda_lexer >(s)) return T_lambda_lexer::token;
			else                                                 return Token::invalid;
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace hustle

