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

// (generate) first:

namespace cctmp  {
namespace parser {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// context-free grammar:

	template<typename CharType, auto M, auto N>
	nik_ce auto context_free_grammar(const CharType (&srt)[M], const CharType (&str)[N])
	{
		return cctmp::pair(cctmp::string_literal(srt), cctmp::string_literal(str));
	}

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// parser parser:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// grammar:

/***********************************************************************************************************************/

	struct T_parser_generator_grammar
	{
		using ActName		= PGAN;
		using T_lexer		= T_parser_generator_lexer;
		using Token		= typename T_lexer::Token;
		nik_ces auto size	= Token::dimension;

		using sxt_pair		= cctmp::pair<strlit_type, token_type>;
		using sxa_pair		= cctmp::pair<strlit_type, action_type>;

		nik_ces auto source()
		{
			return context_free_grammar
			(
				"S",

				"S -> i F D     : l_value ;"
				"D -> i H D     : l_value ;"
				"  -> e         : accept  ;"
				"F -> a M A s B : front   ;"
				"  -> \\= I J K           ;"
				"H -> a M A s B : head    ;"
				"  -> \\= I J K           ;"
				"B -> a M A s B : body    ;"
				"  -> e                   ;"
				"M -> T N                 ;"
				"  -> m         : m_value ;"
				"N -> T N                 ;"
				"  -> e                   ;"
				"T -> i         : r_value ;"
				"A -> c C                 ;"
				"  -> e                   ;"
				"C -> i         : a_value ;"
				"J -> I J                 ;"
				"  -> e                   ;"
				"I -> i                   ;"
				"K -> s                   ;"
			);
		}

		nik_ces auto map = cctmp::table
		(
			U_strlit_type, U_token_type,

			sxt_pair(   " " , Token::invalid    ),
			sxt_pair(   "e" , Token::empty      ),
			sxt_pair(   "$" , Token::prompt     ),
			sxt_pair(   "i" , Token::identifier ),
			sxt_pair(   "m" , Token::none       ),
			sxt_pair(   "a" , Token::arrow      ),
			sxt_pair( "\\=" , Token::equal      ),
			sxt_pair(   "c" , Token::colon      ),
			sxt_pair(   "s" , Token::semicolon  )
		);

		nik_ces auto action = cctmp::table
		(
			U_strlit_type, U_action_type,

			sxa_pair( "l_value" , ActName::l_value ),
			sxa_pair( "m_value" , ActName::m_value ),
			sxa_pair( "r_value" , ActName::r_value ),
			sxa_pair( "a_value" , ActName::a_value ),
			sxa_pair( "front"   , ActName::front   ),
			sxa_pair( "head"    , ActName::head    ),
			sxa_pair( "body"    , ActName::body    ),
			sxa_pair( "accept"  , ActName::accept  )
		);

		struct Terminal
		{
			nik_ces auto symbol = cctmp::table
			(
				U_gchar_type, U_token_type,

				cctmp::pair( 'i' , Token::identifier ),
				cctmp::pair( 'a' , Token::arrow      ),
				cctmp::pair( ';' , Token::semicolon  ),
				cctmp::pair( ':' , Token::colon      ),
				cctmp::pair( 'm' , Token::empty      ), // empty, not none.
				cctmp::pair( '=' , Token::equal      ),
				cctmp::pair( '$' , Token::prompt     )
			);

			nik_ces auto invalid   = Token::invalid;
			nik_ces auto dimension = Token::dimension;

			nik_ces auto stack_finish = symbol_type{Sign::terminal, Token::prompt};
		};

		struct Nonterminal
		{
			enum : token_type
			{
				start         = 0,
				rec_declare   ,
				front_declare ,
				head_declare  ,
				body_declare  ,
				disp_name     ,
				rec_name      ,
				tok_name      ,
				action        ,
				call          ,
				rec_alias     ,
				tok_alias     ,
				end_alias     ,
				invalid       ,
				dimension
			};

			nik_ces auto symbol = cctmp::table
			(
				U_gchar_type, U_token_type,

				cctmp::pair( 'S' , start         ),
				cctmp::pair( 'D' , rec_declare   ),
				cctmp::pair( 'F' , front_declare ),
				cctmp::pair( 'H' , head_declare  ),
				cctmp::pair( 'B' , body_declare  ),
				cctmp::pair( 'M' , disp_name     ),
				cctmp::pair( 'N' , rec_name      ),
				cctmp::pair( 'T' , tok_name      ),
				cctmp::pair( 'A' , action        ),
				cctmp::pair( 'C' , call          ),
				cctmp::pair( 'J' , rec_alias     ),
				cctmp::pair( 'I' , tok_alias     ),
				cctmp::pair( 'K' , end_alias     )
			);

			nik_ces auto stack_start = symbol_type{Sign::nonterminal, start};
		};
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// pushdown automaton:

/***********************************************************************************************************************/

// char to symbol:

	template<typename T_grammar>
	struct T_char_to_symbol
	{
		using T = typename T_grammar::Terminal;
		using N = typename T_grammar::Nonterminal;

		nik_ces auto result(gcchar_type c)
		{
			auto s = Sign::terminal;
			auto t = T::symbol.lookup(c, T::invalid);

			if (t == T::invalid)
			{
				s = Sign::nonterminal;
				t = N::symbol.lookup(c, N::invalid);
			}

			return symbol_type{s, t};
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// parser:

/***********************************************************************************************************************/

// interface:

	template<typename T_action, typename T_grammar>
	struct T_parser_generator_parser
	{
		using T_ast		= typename T_action::T_ast;
		using T_pda		= T_parser_generator_pda<T_grammar>;
		using T_parser		= T_generic_parser<T_action, T_pda>;

		using parseme_type	= T_parseme<T_ast>;
		using parseme_ref	= parseme_type&;
		using cparseme_type	= parseme_type const;
		using cparseme_ref	= cparseme_type&;

		using parsoid_type	= T_parsoid<T_pda::stack_size, T_pda::prod_size>;
		using parsoid_ref	= parsoid_type&;
		using cparsoid_type	= parsoid_type const;
		using cparsoid_ref	= cparsoid_type&;

		parseme_type parseme;
		parsoid_type parsoid;

		nik_ce T_parser_generator_parser(const cselector<char> & s) :

			parseme{s}, parsoid{T_pda::stack_start, T_pda::stack_finish}

			{ parse(parseme, parsoid); }

		nik_ces void parse(parseme_ref p, parsoid_ref q)
			{ T_parser::parse(p, q); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// parsed:

/***********************************************************************************************************************/

// interface:

	template<auto static_scanned, auto static_grammar>
	struct T_parser_generator_parsed
	{
		using T_ast			= T_parser_generator_ast<static_scanned, static_grammar>;
		using T_action			= T_parser_generator_action<T_ast>;
		using T_grammar			= T_parser_generator_grammar;
		using T_parser			= T_parser_generator_parser<T_action, T_grammar>;

		nik_ces auto & src		= T_store_U<static_scanned>::src;
		nik_ces auto parser		= T_parser{src.cselect()};
		nik_ces auto & value		= parser.parseme.tree;
		nik_ces auto & start_str	= value.start_str;
		using type			= modify_type<_from_reference_, decltype(value)>;
	};

	template<auto static_scanned, auto static_grammar>
	nik_ce auto _parser_generator_parsed_ = U_store_T<T_parser_generator_parsed<static_scanned, static_grammar>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

}} // namespace cctmp::parser

