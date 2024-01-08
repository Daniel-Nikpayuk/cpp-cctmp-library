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

// parser:

namespace scheme {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// cctmp:

	template<auto Op, typename T>
	using modify_type					= cctmp::modify_type<Op, T>;

	nik_ce auto _from_reference_				= cctmp::_from_reference_;

	using strlit_type					= cctmp::strlit_type;
	nik_ce auto U_strlit_type				= cctmp::U_strlit_type;

// generator:

	nik_ce auto U_action_type				= generator::U_action_type;

	using sxt_pair						= cctmp::pair<strlit_type, token_type>;
	using sxa_pair						= cctmp::pair<strlit_type, action_type>;

	using symbol_type					= generator::symbol_type;
	using csymbol_type					= generator::csymbol_type;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// grammar:

/***********************************************************************************************************************/

	struct T_scheme_grammar
	{
		using ActName		= SAAN;
		using T_lexer		= T_scheme_lexer;
		using Token		= typename T_lexer::Token;
		nik_ces auto size	= Token::dimension;

		nik_ces auto source() { return generator::context_free_grammar
		(
			// start:

				"Start",

			// scheme:

				"Start -> DefBeg define ( DefName DefArgs ) Expr0 DefEnd ;"

				"DefBeg  -> (              : define_begin ;"
				"DefEnd  -> )              : define_end   ;"
				"DefName -> identifier     : define_name  ;"
				"DefArgs -> DefArg DefArgs                ;"
				"        -> empty                         ;"
				"DefArg  -> identifier     : define_arg   ;"

				"Const -> boolean   : return_boolean   ;"
				"      -> number    : return_number    ;"
				"      -> character : return_character ;"
				"      -> string    : return_string    ;"

				"Expr0 -> Const                      ;"
				"      -> identifier : return_lookup ;"
				"      -> ( Expr1 )                  ;"

				"Expr1 -> Const                         ;"
				"      -> IfBeg Pred Ante Conse IfEnd   ;"
				"      -> define Var Val                ;"
				"      -> quote Expr0                   ;"
				"      -> begin Exprs                   ;"
				"      -> lambda LArgs LBody            ;"
				"      -> set! Var Val                  ;"
				"      -> Op OpArgs          : op_begin ;"

				"Exprs -> Expr0 Exprs ;"
				"      -> empty       ;"

				"IfBeg -> if               ;"
				"IfEnd -> empty : if_end   ;"
				"Pred  -> Expr0            ;"
				"Ante  -> Expr0 : if_ante  ;"
				"Conse -> Expr0 : if_conse ;"

				"Var -> identifier ;"
				"Val -> Expr0      ;"

				"LArgs -> Expr0 ;"
				"LBody -> Expr0 ;"

				"Op     -> identifier   : op_lookup   ;"
				"       -> +            : op_add      ;"
				"       -> *            : op_multiply ;"
				"       -> \\-          : op_subtract ;"
				"       -> /            : op_divide   ;"
				"OpArgs -> OpArg OpArgs               ;"
				"       -> empty        : op_end      ;"
				"OpArg  -> Expr0        : op_arg      ;"
		);}

		nik_ces auto map = cctmp::table
		(
			U_strlit_type, U_token_type,

			sxt_pair( " "          , Token::invalid    ),
			sxt_pair( "$"          , Token::prompt     ),
			sxt_pair( "identifier" , Token::identifier ),
			sxt_pair( "boolean"    , Token::boolean    ),
			sxt_pair( "number"     , Token::number     ),
			sxt_pair( "character"  , Token::character  ),
			sxt_pair( "string"     , Token::string     ),

			sxt_pair( "if"     , Token::if_    ),
			sxt_pair( "let"    , Token::let    ),
			sxt_pair( "car"    , Token::car    ),
			sxt_pair( "cdr"    , Token::cdr    ),
			sxt_pair( "cons"   , Token::cons   ),
			sxt_pair( "list"   , Token::list   ),
			sxt_pair( "begin"  , Token::begin  ),
			sxt_pair( "quote"  , Token::quote  ),
			sxt_pair( "define" , Token::define ),
			sxt_pair( "lambda" , Token::lambda ),

			sxt_pair( "eq?"    , Token::eq_      ),
			sxt_pair( "set!"   , Token::mu_table ),

			sxt_pair( "("   , Token::l_expr   ),
			sxt_pair( ")"   , Token::r_expr   ),
			sxt_pair( "+"   , Token::add      ),
			sxt_pair( "*"   , Token::multiply ),
			sxt_pair( "\\-" , Token::subtract ),
			sxt_pair( "/"   , Token::divide   ),

			sxt_pair( "empty" , Token::empty )
		);

		nik_ces auto action = cctmp::table
		(
			U_strlit_type, U_action_type,

			// define:

				sxa_pair( "define_begin" , ActName::define_begin ),
				sxa_pair( "define_end"   , ActName::define_end   ),
				sxa_pair( "define_name"  , ActName::define_name  ),
				sxa_pair( "define_arg"   , ActName::define_arg   ),

			// return:

				sxa_pair( "return_boolean"   , ActName::return_boolean   ),
				sxa_pair( "return_number"    , ActName::return_number    ),
				sxa_pair( "return_character" , ActName::return_character ),
				sxa_pair( "return_string"    , ActName::return_string    ),
				sxa_pair( "return_lookup"    , ActName::return_lookup    ),

			// if:

				sxa_pair( "if_ante"  , ActName::if_ante  ),
				sxa_pair( "if_conse" , ActName::if_conse ),
				sxa_pair( "if_end"   , ActName::if_end   ),

			// op:

				sxa_pair( "op_begin"    , ActName::op_begin    ),
				sxa_pair( "op_end"      , ActName::op_end      ),
				sxa_pair( "op_lookup"   , ActName::op_lookup   ),
				sxa_pair( "op_add"      , ActName::op_add      ),
				sxa_pair( "op_multiply" , ActName::op_multiply ),
				sxa_pair( "op_subtract" , ActName::op_subtract ),
				sxa_pair( "op_divide"   , ActName::op_divide   ),
				sxa_pair( "op_arg"      , ActName::op_arg      )
		);
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// pushdown automaton:

/***********************************************************************************************************************/

// interface:

#ifdef NIK_SCHEME_PARSER
#include NIK_SCHEME_OBJ
#else

	template<typename T_grammar>
	struct T_scheme_pda : public generator::T_generic_pda<T_grammar>
	{
		using base			= generator::T_generic_pda<T_grammar>;
		using ActName			= typename T_grammar::ActName;
		using T_lexer			= typename T_grammar::T_lexer;
		using Token			= typename T_grammar::Token;

		nik_ces auto prod_size		= cctmp::string_literal("(d(NA)B)").size(); // needs refining.

		nik_ces auto stack_start	= symbol_type{generator::Sign::nonterminal, base::start_index};
		nik_ces auto stack_finish	= symbol_type{generator::Sign::terminal, Token::prompt};

		nik_ces auto stack_size		= cctmp::literal("F{C|A|M|P}YPZ<>YPZYP,PZV;HGO").size(); // needs refining.
							// literal is intentional.
							// this is the longest possible sentential.
							// might need updating.
	};

#endif

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// parser:

/***********************************************************************************************************************/

// interface:

	template<auto static_pg_parsed, typename T_action, typename T_grammar>
	struct T_scheme_parser
	{
		using T_ast		= typename T_action::T_ast;
		using T_pda		= T_scheme_pda<T_grammar>;
		using T_parser		= generator::T_generic_parser<T_action, T_pda>;
		using parseme_type	= generator::T_parseme<T_ast>;
		using parsoid_type	= generator::T_parsoid<T_pda::stack_size, T_pda::prod_size>;

		nik_ces auto & pda	= T_parser::pda; static_assert(!pda.ambiguous, "ambiguous cfg!");

		parseme_type parseme;
		parsoid_type parsoid;

		nik_ce T_scheme_parser(const cselector<char> & s) :

			parseme(s), parsoid{T_pda::stack_start, T_pda::stack_finish}

			{ parse(parseme, parsoid); }

		nik_ces void parse(parseme_type & p, parsoid_type & q)
			{ T_parser::parse(p, q); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// parsed:

/***********************************************************************************************************************/

// interface:

	template
	<
		auto static_pg_parsed, auto static_source, auto static_env_lookup,
		auto contr_size, auto stack_size, auto model_size
	>
	struct T_scheme_parsed
	{
		using T_ast			= T_scheme_ast
						<
							static_source, static_env_lookup,
							contr_size, stack_size, model_size
						>;
		using T_action			= T_scheme_action<T_ast>;
		using T_grammar			= T_scheme_grammar;
		using T_parser			= T_scheme_parser<static_pg_parsed, T_action, T_grammar>;

		nik_ces auto & src		= member_value_U<static_source>;
		nik_ces auto parser		= T_parser{src.cselect()};
		nik_ces auto & value		= parser.parseme.tree;
		using type			= modify_type<_from_reference_, decltype(value)>;
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace scheme

