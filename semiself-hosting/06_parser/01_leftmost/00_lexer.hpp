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
namespace parser {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// engine:

	using engine::LambdaTuple;

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
				invalid,

				empty      ,
				arrow      ,
				semicolon  ,
				identifier ,
				empty_body ,
				colon      ,
				literal    ,
				prompt     ,

				dimension
			};
		};

		struct State
		{
			enum : size_type
			{
				empty      ,

				initial    ,
				identifier ,
				dash       ,
				rangle     ,
				colon      ,
				any        ,
				literal    ,
				semicolon  ,
				backslash  ,
				whitespace ,

				dimension
			};
		};

		struct Charset
		{
			enum : size_type
			{
				character  ,
				dash       ,
				rangle     ,
				colon      ,
				quote      ,
				semicolon  ,
				backslash  ,
				whitespace ,

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

			engine::pair( State::identifier , Token::identifier ),
			engine::pair( State::rangle     , Token::arrow      ),
			engine::pair( State::colon      , Token::colon      ),
			engine::pair( State::literal    , Token::literal    ),
			engine::pair( State::semicolon  , Token::semicolon  )
		);

		nik_ces auto charmap = engine::lookup
		(
			U_size_type, U_char_type, U_gkey_type,

			engine::pair( '-'  , Charset::dash      ),
			engine::pair( '>'  , Charset::rangle    ),
			engine::pair( ':'  , Charset::colon     ),
			engine::pair( '\'' , Charset::quote     ),
			engine::pair( ';'  , Charset::semicolon ),
			engine::pair( '\\' , Charset::backslash )
		);

		nik_ces gkey_type map(char_ctype c)
		{
			if (c.matches_whitespace()) return Charset::whitespace;
			else                        return charmap.lfind(c, Charset::character);
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

		using lexer_empty_short		= engine::lexer_keyword< char_type , size_type >;
		using lexer_empty_long		= engine::lexer_keyword< char_type , size_type >;

		nik_ces auto empty_short	= lexer_empty_short { "e"     , Token::empty };
		nik_ces auto empty_long		= lexer_empty_long  { "empty" , Token::empty };
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

		using table_type	= table<size_type, size_type, State::dimension, Charset::dimension>;

		constexpr static auto make()
		{
			table_type tab;
			for (size_type k = tab.length(); k != 0; --k) tab.push(State::empty);

			tab [ State::initial    ][ Charset::character  ] = State::identifier ;
			tab [ State::initial    ][ Charset::dash       ] = State::dash       ;
			tab [ State::initial    ][ Charset::colon      ] = State::colon      ;
			tab [ State::initial    ][ Charset::quote      ] = State::any        ;
			tab [ State::initial    ][ Charset::semicolon  ] = State::semicolon  ;
			tab [ State::initial    ][ Charset::backslash  ] = State::backslash  ;

			tab [ State::identifier ][ Charset::character  ] = State::identifier ;
			tab [ State::identifier ][ Charset::backslash  ] = State::backslash  ;

			tab [ State::dash       ][ Charset::rangle     ] = State::rangle     ;

			tab [ State::any        ][ Charset::character  ] = State::any        ;
			tab [ State::any        ][ Charset::dash       ] = State::any        ;
			tab [ State::any        ][ Charset::rangle     ] = State::any        ;
			tab [ State::any        ][ Charset::colon      ] = State::any        ;
			tab [ State::any        ][ Charset::quote      ] = State::literal    ;
			tab [ State::any        ][ Charset::semicolon  ] = State::any        ;
			tab [ State::any        ][ Charset::backslash  ] = State::any        ;
			tab [ State::any        ][ Charset::whitespace ] = State::any        ;

			tab [ State::backslash  ][ Charset::dash       ] = State::identifier ;
			tab [ State::backslash  ][ Charset::rangle     ] = State::identifier ;
			tab [ State::backslash  ][ Charset::colon      ] = State::identifier ;
			tab [ State::backslash  ][ Charset::quote      ] = State::identifier ;
			tab [ State::backslash  ][ Charset::semicolon  ] = State::identifier ;
			tab [ State::backslash  ][ Charset::backslash  ] = State::identifier ;

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
					{ if (s == Token::identifier) refine_identifier(s); }

				nik_ce void refine_identifier(size_type s)
				{
					s = check_keyword(base::cbegin(), base::ccurrent());
					symbol = (s != Token::invalid) ? s : Token::identifier;
				}

			// check:

				nik_ce size_type check_keyword(iter_ctype in, iter_ctype end) const
				{
					size_type val = Token::invalid;

					switch (base::left_size())
					{
						case 1 : { val = check_keyword_1 (in, end); break; }
						case 5 : { val = check_keyword_5 (in, end); break; }
					}

					return val;
				}

				nik_ce size_type check_keyword_1(iter_ctype in, iter_ctype end) const
				{
					if (keyword::empty_short.match(in, end)) return keyword::empty_short.token;
					else                                     return Token::invalid;
				}

				nik_ce size_type check_keyword_5(iter_ctype in, iter_ctype end) const
				{
					if (keyword::empty_long.match(in, end)) return keyword::empty_long.token;
					else                                    return Token::invalid;
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

}} // namespace cctmp::parser

