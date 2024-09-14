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

namespace cctmp  {
namespace hustle {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// space:

/***********************************************************************************************************************/

// trait:

	template<typename CharType, typename SizeType>
	struct lexer_trait
	{
		using char_type		= CharType;
		using char_ctype	= char_type const;

		using iter_type		= char_ctype *;
		using iter_ctype	= iter_type const;

		using size_type		= SizeType;
		using size_ctype	= size_type const;

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

		struct State
		{
			enum : size_type
			{
				empty       ,
				initial     ,
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
		};

		struct Charset
		{
			enum : size_type
			{
				other       ,
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
		};
	};

/***********************************************************************************************************************/

// policy:

	template<typename LexerTrait>
	struct lexer_policy
	{
		using trait			= LexerTrait;
		using token_name		= typename trait::Token;
		using state_name		= typename trait::State;
		using charset_name		= typename trait::Charset;

		using char_type			= typename trait::char_type;
		using char_ctype		= typename trait::char_ctype;

		using size_type			= typename trait::size_type;
		using size_ctype		= typename trait::size_ctype;

		nik_ces auto U_char_type	= U_store_T<char_type>;
		nik_ces auto U_size_type	= U_store_T<size_type>;

		nik_ces auto accept = engine::table
		(
			U_size_type, U_size_type, U_size_type,

			engine::pair( state_name::l_paren    , token_name::l_expr     ),
			engine::pair( state_name::r_paren    , token_name::r_expr     ),
			engine::pair( state_name::arrow      , token_name::op_type    ),
			engine::pair( state_name::colon      , token_name::arg_type   ),

			engine::pair( state_name::identifier , token_name::identifier ),
			engine::pair( state_name::boolean    , token_name::boolean    ),
			engine::pair( state_name::n_numeral  , token_name::n_number   ),
			engine::pair( state_name::r_numeral  , token_name::r_number   ),
			engine::pair( state_name::period     , token_name::r_number   ),
			engine::pair( state_name::character  , token_name::character  ),
			engine::pair( state_name::string     , token_name::string     ),

			engine::pair( state_name::equal      , token_name::equal      ),
			engine::pair( state_name::compare_lt , token_name::compare_lt ),
			engine::pair( state_name::compare_le , token_name::compare_le ),
			engine::pair( state_name::compare_gt , token_name::compare_gt ),
			engine::pair( state_name::compare_ge , token_name::compare_ge ),
			engine::pair( state_name::plus       , token_name::add        ),
			engine::pair( state_name::star       , token_name::multiply   ),
			engine::pair( state_name::dash       , token_name::subtract   ),
			engine::pair( state_name::slash      , token_name::divide     )
		);

		nik_ces auto charmap = engine::table
		(
			U_size_type, U_char_type, U_gkey_type,

			engine::pair( '\'' , charset_name::quote       ),
			engine::pair( ':'  , charset_name::colon       ),
			engine::pair( '.'  , charset_name::period      ),
			engine::pair( '('  , charset_name::l_paren     ),
			engine::pair( ')'  , charset_name::r_paren     ),
			engine::pair( '?'  , charset_name::question    ),
			engine::pair( '#'  , charset_name::octothorpe  ),
			engine::pair( '!'  , charset_name::punctuation ),

			engine::pair( '='  , charset_name::equal       ),
			engine::pair( '<'  , charset_name::l_angle     ),
			engine::pair( '>'  , charset_name::r_angle     ),
			engine::pair( '+'  , charset_name::plus        ),
			engine::pair( '*'  , charset_name::star        ),
			engine::pair( '-'  , charset_name::dash        ),
			engine::pair( '/'  , charset_name::slash       ),

			engine::pair( '\\' , charset_name::backslash   )
		);

		nik_ces gkey_type map(char_ctype c)
		{
			if      (engine::matches_ula(c))   return charset_name::ula;
			else if (engine::matches_digit(c)) return charset_name::digit;
			else                               return charmap.lfind(c, charset_name::other);
		}
	};

/***********************************************************************************************************************/

// keyword:

	template<typename LexerTrait>
	struct lexer_keyword
	{
		using trait			= LexerTrait;
		using token_name		= typename trait::Token;

		using char_type			= typename trait::char_type;
		using char_ctype		= typename trait::char_ctype;

		using size_type			= typename trait::size_type;
		using size_ctype		= typename trait::size_ctype;

		using lexer_if_			= engine::lexer_keyword< char_type , size_type >;
		using lexer_eq_			= engine::lexer_keyword< char_type , size_type >;
		using lexer_let			= engine::lexer_keyword< char_type , size_type >;
		using lexer_car			= engine::lexer_keyword< char_type , size_type >;
		using lexer_cdr			= engine::lexer_keyword< char_type , size_type >;
		using lexer_type		= engine::lexer_keyword< char_type , size_type >;
		using lexer_set_		= engine::lexer_keyword< char_type , size_type >;
		using lexer_cons		= engine::lexer_keyword< char_type , size_type >;
		using lexer_list		= engine::lexer_keyword< char_type , size_type >;
		using lexer_begin		= engine::lexer_keyword< char_type , size_type >;
		using lexer_quote		= engine::lexer_keyword< char_type , size_type >;
		using lexer_define		= engine::lexer_keyword< char_type , size_type >;
		using lexer_lambda		= engine::lexer_keyword< char_type , size_type >;

		nik_ces auto if_		= lexer_if_    { "if"     , token_name::if_    };
		nik_ces auto eq_		= lexer_eq_    { "eq"     , token_name::eq_    };
		nik_ces auto let		= lexer_let    { "let"    , token_name::let    };
		nik_ces auto car		= lexer_car    { "car"    , token_name::car    };
		nik_ces auto cdr		= lexer_cdr    { "cdr"    , token_name::cdr    };
		nik_ces auto type		= lexer_type   { "type"   , token_name::type   };
		nik_ces auto set_		= lexer_set_   { "set"    , token_name::set_   };
		nik_ces auto cons		= lexer_cons   { "cons"   , token_name::cons   };
		nik_ces auto list		= lexer_list   { "list"   , token_name::list   };
		nik_ces auto begin		= lexer_begin  { "begin"  , token_name::begin  };
		nik_ces auto quote		= lexer_quote  { "quote"  , token_name::quote  };
		nik_ces auto define		= lexer_define { "define" , token_name::define };
		nik_ces auto lambda		= lexer_lambda { "lambda" , token_name::lambda };
	};

/***********************************************************************************************************************/

// interface:

	template<typename LexerTrait>
	class lexer : public engine::lexer_automaton
	<
		typename LexerTrait::State,
		typename LexerTrait::Charset,
		typename LexerTrait::iter_type,
		typename LexerTrait::size_type
	>
	{
		public:

			using trait		= LexerTrait;
			using token_name	= typename trait::Token;
			using state_name	= typename trait::State;
			using charset_name	= typename trait::Charset;

			using char_type		= typename trait::char_type;
			using char_ctype	= typename trait::char_ctype;

			using iter_type		= typename trait::iter_type;
			using iter_ctype	= typename trait::iter_ctype;

			using size_type		= typename trait::size_type;
			using size_ctype	= typename trait::size_ctype;

			using base		= engine::lexer_automaton<state_name, charset_name, iter_type, size_type>;
			using policy		= lexer_policy<trait>;
			using keyword		= lexer_keyword<trait>;

			using lit_type		= typename base::lit_type;
			using lit_ctype		= typename base::lit_ctype;
			using lit_ctype_ref	= typename base::lit_ctype_ref;

		protected:

			size_type token;

		public:

			nik_ce lexer(lit_ctype_ref t, iter_ctype s, iter_ctype f) :
				base{t, s, f}, token{token_name::invalid}
					{ }

			nik_ce size_type column() const { return token; }

			nik_ce bool find()
			{
				base::initialize();

				if (base::template find<policy>())
					refine_token(policy::accept.lfind(base::state(), token_name::invalid));

				return (token != token_name::invalid);
			}

			// refine:

				nik_ce void refine_token(size_ctype t)
				{
					if      (t == token_name::identifier) refine_identifier (t);
					else if (t == token_name::boolean   ) refine_boolean    ( );
				}

				nik_ce void refine_identifier(size_type t)
				{
					t = check_keyword(base::cbegin(), base::ccurrent());
					token = (t != token_name::invalid) ? t : token_name::identifier;
				}

				nik_ce void refine_boolean()
				{
					switch (*base::cprevious())
					{
						case 'f' : { token = token_name::bool_f  ; break; }
						case 't' : { token = token_name::bool_t  ; break; }
						default  : { token = token_name::invalid ; break; }
					}
				}

			// check:

				nik_ce size_type check_keyword(iter_ctype in, iter_ctype end) const
				{
					size_type val = token_name::invalid;

					switch (base::left_size())
					{
						case 2 : { val = check_keyword_2 (in, end); break; }
						case 3 : { val = check_keyword_3 (in, end); break; }
						case 4 : { val = check_keyword_4 (in, end); break; }
						case 5 : { val = check_keyword_5 (in, end); break; }
						case 6 : { val = check_keyword_6 (in, end); break; }
					}

					return val;
				}

				nik_ce size_type check_keyword_2(iter_ctype in, iter_ctype end) const
				{
					if (keyword::if_.match(in, end)) return keyword::if_.token;
					else                             return token_name::invalid;
				}

				nik_ce size_type check_keyword_3(iter_ctype in, iter_ctype end) const
				{
					if      (keyword::eq_.match(in, end)) return keyword::eq_.token;
					else if (keyword::let.match(in, end)) return keyword::let.token;
					else if (keyword::car.match(in, end)) return keyword::car.token;
					else if (keyword::cdr.match(in, end)) return keyword::cdr.token;
					else                                  return token_name::invalid;
				}

				nik_ce size_type check_keyword_4(iter_ctype in, iter_ctype end) const
				{
					if      (keyword::type.match(in, end)) return keyword::type.token;
					else if (keyword::set_.match(in, end)) return keyword::set_.token;
					else if (keyword::cons.match(in, end)) return keyword::cons.token;
					else if (keyword::list.match(in, end)) return keyword::list.token;
					else                                   return token_name::invalid;
				}

				nik_ce size_type check_keyword_5(iter_ctype in, iter_ctype end) const
				{
					if      (keyword::begin.match(in, end)) return keyword::begin.token;
					else if (keyword::quote.match(in, end)) return keyword::quote.token;
					else                                    return token_name::invalid;
				}

				nik_ce size_type check_keyword_6(iter_ctype in, iter_ctype end) const
				{
					if      (keyword::define.match(in, end)) return keyword::define.token;
					else if (keyword::lambda.match(in, end)) return keyword::lambda.token;
					else                                     return token_name::invalid;
				}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

}} // namespace cctmp::hustle

