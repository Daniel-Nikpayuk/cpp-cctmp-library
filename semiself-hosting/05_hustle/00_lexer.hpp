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

	template<typename T>
	nik_ce auto U_store_T						= cctmp::U_store_T<T>;

	using gkey_type							= cctmp::gkey_type;

	nik_ce auto U_gkey_type						= cctmp::U_gkey_type;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// policy:

/***********************************************************************************************************************/

// interface:

	template<typename State, typename Charset, typename CharType, typename SizeType>
	struct lexer_policy
	{
		using char_type			= CharType;
		using char_ctype		= char_type const;

		using size_type			= SizeType;
		using size_ctype		= size_type const;

		nik_ces auto U_char_type	= U_store_T<char_type>;
		nik_ces auto U_size_type	= U_store_T<size_type>;

		struct Token
		{
			enum : size_type
			{
				invalid     ,
				empty       ,
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

				dimension
			};
		};

		nik_ces auto accept = engine::table
		(
			U_size_type, U_size_type, U_size_type,

			engine::pair( State::l_paren    , Token::l_expr     ),
			engine::pair( State::r_paren    , Token::r_expr     ),
			engine::pair( State::arrow      , Token::op_type    ),
			engine::pair( State::colon      , Token::arg_type   ),

			engine::pair( State::identifier , Token::identifier ),
			engine::pair( State::boolean    , Token::boolean    ),
			engine::pair( State::n_numeral  , Token::n_number   ),
			engine::pair( State::r_numeral  , Token::r_number   ),
			engine::pair( State::period     , Token::r_number   ),
			engine::pair( State::character  , Token::character  ),
			engine::pair( State::string     , Token::string     ),

			engine::pair( State::equal      , Token::equal      ),
			engine::pair( State::compare_lt , Token::compare_lt ),
			engine::pair( State::compare_le , Token::compare_le ),
			engine::pair( State::compare_gt , Token::compare_gt ),
			engine::pair( State::compare_ge , Token::compare_ge ),
			engine::pair( State::plus       , Token::add        ),
			engine::pair( State::star       , Token::multiply   ),
			engine::pair( State::dash       , Token::subtract   ),
			engine::pair( State::slash      , Token::divide     )
		);

		nik_ces auto charmap = engine::table
		(
			U_size_type, U_char_type, U_gkey_type,

			engine::pair( '\'' , Charset::quote       ),
			engine::pair( ':'  , Charset::colon       ),
			engine::pair( '.'  , Charset::period      ),
			engine::pair( '('  , Charset::l_paren     ),
			engine::pair( ')'  , Charset::r_paren     ),
			engine::pair( '?'  , Charset::question    ),
			engine::pair( '#'  , Charset::octothorpe  ),
			engine::pair( '!'  , Charset::punctuation ),

			engine::pair( '='  , Charset::equal       ),
			engine::pair( '<'  , Charset::l_angle     ),
			engine::pair( '>'  , Charset::r_angle     ),
			engine::pair( '+'  , Charset::plus        ),
			engine::pair( '*'  , Charset::star        ),
			engine::pair( '-'  , Charset::dash        ),
			engine::pair( '/'  , Charset::slash       ),

			engine::pair( '\\' , Charset::backslash   )
		);

		nik_ces gkey_type map(char_ctype c)
		{
			if      (engine::matches_ula(c))   return Charset::ula;
			else if (engine::matches_digit(c)) return Charset::digit;
			else                               return charmap.lfind(c, Charset::other);
		}
	};

/***********************************************************************************************************************/

// automaton:

/*
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
*/

/***********************************************************************************************************************/

// interface:

/*
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
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace hustle

