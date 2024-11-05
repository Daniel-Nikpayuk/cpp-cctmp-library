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

	template<typename Trait>
	struct lexer_policy
	{
		using Token			= typename Trait::Token;
		using State			= typename Trait::State;
		using Charset			= typename Trait::Charset;

		using char_type			= typename Trait::char_type;
		using char_ctype		= typename Trait::char_ctype;

		using size_type			= typename Trait::size_type;
		using size_ctype		= typename Trait::size_ctype;

		nik_ces auto U_char_type	= U_store_T<char_type>;
		nik_ces auto U_size_type	= U_store_T<size_type>;

		nik_ces auto accept = engine::lookup
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

		nik_ces auto charmap = engine::lookup
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

// keyword:

	template<typename Trait>
	struct lexer_keyword
	{
		using Token			= typename Trait::Token;

		using char_type			= typename Trait::char_type;
		using char_ctype		= typename Trait::char_ctype;

		using size_type			= typename Trait::size_type;
		using size_ctype		= typename Trait::size_ctype;

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

		nik_ces auto if_		= lexer_if_    { "if"     , Token::if_    };
		nik_ces auto eq_		= lexer_eq_    { "eq"     , Token::eq_    };
		nik_ces auto let		= lexer_let    { "let"    , Token::let    };
		nik_ces auto car		= lexer_car    { "car"    , Token::car    };
		nik_ces auto cdr		= lexer_cdr    { "cdr"    , Token::cdr    };
		nik_ces auto type		= lexer_type   { "type"   , Token::type   };
		nik_ces auto set_		= lexer_set_   { "set"    , Token::set_   };
		nik_ces auto cons		= lexer_cons   { "cons"   , Token::cons   };
		nik_ces auto list		= lexer_list   { "list"   , Token::list   };
		nik_ces auto begin		= lexer_begin  { "begin"  , Token::begin  };
		nik_ces auto quote		= lexer_quote  { "quote"  , Token::quote  };
		nik_ces auto define		= lexer_define { "define" , Token::define };
		nik_ces auto lambda		= lexer_lambda { "lambda" , Token::lambda };
	};

/***********************************************************************************************************************/

// (transition) table:

	template<typename Trait>
	struct lexer_table
	{
		using State		= typename Trait::State;
		using Charset		= typename Trait::Charset;

		using size_type		= typename Trait::size_type;
		using size_ctype	= typename Trait::size_ctype;

		using table_type	= cctmp::table<size_type, size_type, State::dimension, Charset::dimension>;

		constexpr static auto make()
		{
			table_type tab;
			for (size_type k = tab.length(); k != 0; --k) tab.push(State::empty);

			tab [ State::initial    ][ Charset::ula         ] = State::identifier ;
			tab [ State::initial    ][ Charset::l_paren     ] = State::l_paren    ;
			tab [ State::initial    ][ Charset::r_paren     ] = State::r_paren    ;
			tab [ State::initial    ][ Charset::colon       ] = State::colon      ;
			tab [ State::initial    ][ Charset::octothorpe  ] = State::hash       ;
			tab [ State::initial    ][ Charset::digit       ] = State::n_numeral  ;
			tab [ State::initial    ][ Charset::period      ] = State::period     ;
			tab [ State::initial    ][ Charset::quote       ] = State::l_quote    ;
			tab [ State::initial    ][ Charset::equal       ] = State::equal      ;
			tab [ State::initial    ][ Charset::l_angle     ] = State::compare_lt ;
			tab [ State::initial    ][ Charset::r_angle     ] = State::compare_gt ;
			tab [ State::initial    ][ Charset::plus        ] = State::plus       ;
			tab [ State::initial    ][ Charset::star        ] = State::star       ;
			tab [ State::initial    ][ Charset::dash        ] = State::dash       ;
			tab [ State::initial    ][ Charset::slash       ] = State::slash      ;

			tab [ State::identifier ][ Charset::ula         ] = State::identifier ;
			tab [ State::identifier ][ Charset::digit       ] = State::identifier ;
			tab [ State::identifier ][ Charset::dash        ] = State::identifier ;
			tab [ State::identifier ][ Charset::question    ] = State::identifier ;
			tab [ State::identifier ][ Charset::punctuation ] = State::identifier ;

			tab [ State::hash       ][ Charset::ula         ] = State::boolean    ;

			tab [ State::n_numeral  ][ Charset::digit       ] = State::n_numeral  ;
			tab [ State::n_numeral  ][ Charset::period      ] = State::period     ;

			tab [ State::r_numeral  ][ Charset::digit       ] = State::r_numeral  ;

			tab [ State::period     ][ Charset::digit       ] = State::r_numeral  ;

			tab [ State::l_quote    ][ Charset::ula         ] = State::character  ;

			tab [ State::character  ][ Charset::ula         ] = State::string     ;

			tab [ State::string     ][ Charset::ula         ] = State::string     ;

			tab [ State::compare_lt ][ Charset::equal       ] = State::compare_le ;

			tab [ State::compare_gt ][ Charset::equal       ] = State::compare_ge ;

			tab [ State::dash       ][ Charset::r_angle     ] = State::arrow      ;

			return tab;
		}

		nik_ces auto value = make();
	};

/***********************************************************************************************************************/

// interface:

	template<typename Trait>
	class lexer : public engine::lexer_automaton
	<
		typename Trait::State,
		typename Trait::Charset,
		typename Trait::iter_type,
		typename Trait::size_type
	>
	{
		public:

			using Token		= typename Trait::Token;
			using State		= typename Trait::State;
			using Charset		= typename Trait::Charset;

			using char_type		= typename Trait::char_type;
			using char_ctype	= typename Trait::char_ctype;

			using iter_type		= typename Trait::iter_type;
			using iter_ctype	= typename Trait::iter_ctype;

			using size_type		= typename Trait::size_type;
			using size_ctype	= typename Trait::size_ctype;

			using base		= engine::lexer_automaton<State, Charset, iter_type, size_type>;
			using policy		= lexer_policy<Trait>;
			using keyword		= lexer_keyword<Trait>;

			using lit_type		= typename base::lit_type;
			using lit_ctype		= typename base::lit_ctype;
			using lit_ctype_ref	= typename base::lit_ctype_ref;

		protected:

			size_type symbol;

		public:

			nik_ce lexer(lit_ctype_ref t, iter_ctype s, iter_ctype f) :
				base{t, s, f}, symbol{Token::invalid}
					{ }

			nik_ce size_type token  () const { return symbol; }
			nik_ce size_type column () const { return token(); }

			nik_ce bool find()
			{
				base::initialize();

				if (base::template find<policy>())
					refine_symbol(policy::accept.lfind(base::state(), Token::invalid));

				return (symbol != Token::invalid);
			}

			// refine:

				nik_ce void refine_symbol(size_ctype s)
				{
					if      (s == Token::identifier) refine_identifier (s);
					else if (s == Token::boolean   ) refine_boolean    ( );
				}

				nik_ce void refine_identifier(size_type s)
				{
					s = check_keyword(base::cbegin(), base::ccurrent());
					symbol = (s != Token::invalid) ? s : Token::identifier;
				}

				nik_ce void refine_boolean()
				{
					switch (*base::cprevious())
					{
						case 'f' : { symbol = Token::bool_f  ; break; }
						case 't' : { symbol = Token::bool_t  ; break; }
						default  : { symbol = Token::invalid ; break; }
					}
				}

			// check:

				nik_ce size_type check_keyword(iter_ctype in, iter_ctype end) const
				{
					size_type val = Token::invalid;

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
					else                             return Token::invalid;
				}

				nik_ce size_type check_keyword_3(iter_ctype in, iter_ctype end) const
				{
					if      (keyword::eq_.match(in, end)) return keyword::eq_.token;
					else if (keyword::let.match(in, end)) return keyword::let.token;
					else if (keyword::car.match(in, end)) return keyword::car.token;
					else if (keyword::cdr.match(in, end)) return keyword::cdr.token;
					else                                  return Token::invalid;
				}

				nik_ce size_type check_keyword_4(iter_ctype in, iter_ctype end) const
				{
					if      (keyword::type.match(in, end)) return keyword::type.token;
					else if (keyword::set_.match(in, end)) return keyword::set_.token;
					else if (keyword::cons.match(in, end)) return keyword::cons.token;
					else if (keyword::list.match(in, end)) return keyword::list.token;
					else                                   return Token::invalid;
				}

				nik_ce size_type check_keyword_5(iter_ctype in, iter_ctype end) const
				{
					if      (keyword::begin.match(in, end)) return keyword::begin.token;
					else if (keyword::quote.match(in, end)) return keyword::quote.token;
					else                                    return Token::invalid;
				}

				nik_ce size_type check_keyword_6(iter_ctype in, iter_ctype end) const
				{
					if      (keyword::define.match(in, end)) return keyword::define.token;
					else if (keyword::lambda.match(in, end)) return keyword::lambda.token;
					else                                     return Token::invalid;
				}
	};

/***********************************************************************************************************************/

// syntactic sugar:

	template<typename CharType, typename SizeType, typename In, typename End>
	nik_ce auto make_lexer(In in, End end)
	{
		using trait_type		= lexer_trait<CharType, SizeType>;
		using table_type		= lexer_table<trait_type>;
		using lexer_type		= lexer<trait_type>;

		return lexer_type{table_type::value.origin(), in, end};
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

}} // namespace cctmp::hustle

