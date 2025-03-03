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

namespace cctmp {
namespace chord {

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

				type        ,
				identifier  ,
				n_number    ,
				r_number    ,
				declare     ,
				define      ,
				copy        ,
				paste       ,
				quote       ,
				statement   ,
				label       ,
				re_turn     ,
				go_to       ,
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

				dimension
			};
		};

		nik_ces auto accept = engine::table
		(
			U_size_type, U_size_type, U_size_type,

			engine::pair( State::arrow         , Token::op_type     ),
			engine::pair( State::colon         , Token::arg_type    ),

			engine::pair( State::ulan          , Token::identifier  ),
			engine::pair( State::n_numeral     , Token::n_number    ),
			engine::pair( State::r_numeral     , Token::r_number    ),
			engine::pair( State::semicolon     , Token::statement   ),
			engine::pair( State::octothorpe    , Token::assign      ),
			engine::pair( State::equal         , Token::apply       ),
			engine::pair( State::punctuation   , Token::mu_table    ),
			engine::pair( State::period        , Token::copy        ),
			engine::pair( State::label         , Token::label       ),

			engine::pair( State::l_brace       , Token::l_scope     ),
			engine::pair( State::r_brace       , Token::r_scope     ),
			engine::pair( State::bar           , Token::bar         ),
			engine::pair( State::at            , Token::identity    ),
			engine::pair( State::star          , Token::dereference ),
			engine::pair( State::caret         , Token::caret       ),
			engine::pair( State::plus          , Token::increment   ),
			engine::pair( State::dash          , Token::decrement   ),
			engine::pair( State::tilde         , Token::tilde       ),
			engine::pair( State::l_bracket     , Token::l_closed    ),
			engine::pair( State::r_bracket     , Token::r_closed    ),
			engine::pair( State::l_parenthesis , Token::l_open      ),
			engine::pair( State::r_parenthesis , Token::r_open      ),
			engine::pair( State::l_angle       , Token::l_fixed     ),
			engine::pair( State::r_angle       , Token::r_fixed     ),
			engine::pair( State::comma         , Token::comma       ),

			engine::pair( State::r_quote       , Token::quote       )
		);

		nik_ces auto charmap = engine::table
		(
			U_size_type, U_char_type, U_gkey_type,

			engine::pair( ':'  , Charset::colon         ),
			engine::pair( ';'  , Charset::semicolon     ),
			engine::pair( '#'  , Charset::octothorpe    ),
			engine::pair( '='  , Charset::equal         ),
			engine::pair( '!'  , Charset::punctuation   ),
			engine::pair( '.'  , Charset::period        ),

			engine::pair( '<'  , Charset::l_angle       ),
			engine::pair( '>'  , Charset::r_angle       ),
			engine::pair( '|'  , Charset::bar           ),
			engine::pair( '@'  , Charset::at            ),
			engine::pair( '*'  , Charset::star          ),
			engine::pair( '^'  , Charset::caret         ),
			engine::pair( '+'  , Charset::plus          ),
			engine::pair( '-'  , Charset::dash          ),
			engine::pair( '~'  , Charset::tilde         ),
			engine::pair( '['  , Charset::l_bracket     ),
			engine::pair( ']'  , Charset::r_bracket     ),
			engine::pair( '('  , Charset::l_parenthesis ),
			engine::pair( ')'  , Charset::r_parenthesis ),
			engine::pair( '{'  , Charset::l_brace       ),
			engine::pair( '}'  , Charset::r_brace       ),
			engine::pair( ','  , Charset::comma         ),

			engine::pair( '\'' , Charset::quote         ),
			engine::pair( '\\' , Charset::backslash     )
		);

		nik_ces gkey_type map(gcchar_type c)
		{
			if      (engine::matches_ula(c))   return Charset::ula;
			else if (engine::matches_digit(c)) return Charset::digit;
			else                               return charmap.lfind(c, Charset::other);
		}
	};

/***********************************************************************************************************************/

// automaton:

/*
	struct T_chord_dfa
	{
		using T_dftt			= T_chord_dftt;
		using Token			= typename T_dftt::Token;
		nik_ces auto value		= T_dftt{};
		nik_ces auto accept		= T_dftt::State::accept;

		nik_ces auto paste_charset      () { return generator::dfa_charset("_");      }
		nik_ces auto type_charset       () { return generator::dfa_charset("type");   }
		nik_ces auto void_charset       () { return generator::dfa_charset("void");   }
		nik_ces auto test_charset       () { return generator::dfa_charset("test");   }
		nik_ces auto goto_charset       () { return generator::dfa_charset("goto");   }
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
*/

/***********************************************************************************************************************/

// interface:

/*
	struct T_chord_lexer
	{
		using T_dfa			= T_chord_dfa;
		using Token			= typename T_dfa::Token;

		using T_paste_lexer		= generator::T_keyword_lexer< T_dfa::paste_charset  , Token::paste   >;
		using T_type_lexer		= generator::T_keyword_lexer< T_dfa::type_charset   , Token::type    >;
		using T_void_lexer		= generator::T_keyword_lexer< T_dfa::void_charset   , Token::vo_id   >;
		using T_test_lexer		= generator::T_keyword_lexer< T_dfa::test_charset   , Token::test    >;
		using T_goto_lexer		= generator::T_keyword_lexer< T_dfa::goto_charset   , Token::go_to   >;
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
			if      (generator::recognizes< T_type_lexer >(s)) return T_type_lexer::token;
			else if (generator::recognizes< T_void_lexer >(s)) return T_void_lexer::token;
			else if (generator::recognizes< T_test_lexer >(s)) return T_test_lexer::token;
			else if (generator::recognizes< T_goto_lexer >(s)) return T_goto_lexer::token;
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
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

}} // namespace cctmp::chord

