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

namespace hustle {

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

	struct T_hustle_grammar
	{
		using ActName		= HAAN;
		using T_lexer		= T_hustle_lexer;
		using Token		= typename T_lexer::Token;
		nik_ces auto size	= Token::dimension;

		nik_ces auto source() { return generator::context_free_grammar
		(
			// start:

				"Start",

			// hustle:

				"Start -> MainBeg MainType ( MainSign ) MainBody MainEnd ;"

				"MainBeg  -> (                   : main_begin ;"
				"MainEnd  -> )                   : main_end   ;"
				"MainType -> define                           ;"
				"         -> type Type                        ;"
				"MainSign -> identifier MainArgs : main_name  ;"
				"MainArgs -> MainArg MainArgs                 ;"
				"         -> empty                            ;"
				"MainArg  -> identifier          : main_arg   ;"
				"MainBody -> Expr0 Exprs                      ;"

				"Type  -> number : type_number ;"
				"Exprs -> Expr0 Exprs          ;"
				"      -> empty                ;"

				"Const  -> boolean    : return_boolean   ;"
				"       -> number     : return_number    ;"
				"       -> character  : return_character ;"
				"       -> string     : return_string    ;"
				"Lookup -> identifier : return_lookup    ;"

				"Expr0 -> Const     ;"
				"      -> Lookup    ;"
				"      -> ( Expr1 ) ;"

				"Expr1 -> Const                         ;"
				"      -> IfBeg Pred Ante Conse IfEnd   ;"
				"      -> define DefDisp                ;"
				"      -> type Type ( DefSign ) DefBody ;"
				"      -> quote Expr0                   ;"
				"      -> begin Exprs                   ;"
				"      -> lambda LArgs LBody            ;"
				"      -> set! Var Val                  ;"
				"      -> Op OpArgs                     ;"

				"IfBeg   -> if                    ;"
				"IfEnd   -> empty : if_end        ;"
				"Pred    -> Const                 ;"
				"        -> Lookup                ;"
				"        -> PredBeg Expr1 PredEnd ;"
				"PredBeg -> (                     ;"
				"PredEnd -> )     : pred_end      ;"
				"Ante    -> Expr0 : if_ante       ;"
				"Conse   -> Expr0 : if_conse      ;"

				"DefDisp  -> Var Val                           ;"
				"         -> ( DefSign ) DefBody               ;"
				"DefSign  -> identifier DefArgs  : define_name ;"
				"DefArgs  -> DefArg DefArgs                    ;"
				"         -> empty                             ;"
				"DefArg   -> identifier          : define_arg  ;"
				"DefBody  -> Expr0 DefExprs      : define_body ;"
				"DefExprs -> Expr0 DefExprs                    ;"
				"         -> empty               : define_end  ;"

				"Var -> identifier ;"
				"Val -> Expr0      ;"

				"LArgs -> Expr0 ;"
				"LBody -> Expr0 ;"

				"Op -> identifier : op_lookup ;"
				"   -> \\=        : op_lookup ;"
				"   -> <          : op_lookup ;"
				"   -> <\\=       : op_lookup ;"
				"   -> \\>        : op_lookup ;"
				"   -> \\>\\=     : op_lookup ;"
				"   -> +          : op_lookup ;"
				"   -> *          : op_lookup ;"
				"   -> \\-        : op_lookup ;"
				"   -> /          : op_lookup ;"

				"OpArgs -> Expr0 OpArgs      ;"
				"       -> empty : op_return ;"
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
			sxt_pair( "type"   , Token::type   ),
			sxt_pair( "cons"   , Token::cons   ),
			sxt_pair( "list"   , Token::list   ),
			sxt_pair( "begin"  , Token::begin  ),
			sxt_pair( "quote"  , Token::quote  ),
			sxt_pair( "define" , Token::define ),
			sxt_pair( "lambda" , Token::lambda ),

			sxt_pair( "eq?"    , Token::eq_      ),
			sxt_pair( "set!"   , Token::mu_table ),

			sxt_pair( "("      , Token::l_expr     ),
			sxt_pair( ")"      , Token::r_expr     ),
			sxt_pair( "\\="    , Token::equal      ),
			sxt_pair( "<"      , Token::compare_lt ),
			sxt_pair( "<\\="   , Token::compare_le ),
			sxt_pair( "\\>"    , Token::compare_gt ),
			sxt_pair( "\\>\\=" , Token::compare_ge ),
			sxt_pair( "+"      , Token::add        ),
			sxt_pair( "*"      , Token::multiply   ),
			sxt_pair( "\\-"    , Token::subtract   ),
			sxt_pair( "/"      , Token::divide     ),

			sxt_pair( "empty" , Token::empty )
		);

		nik_ces auto action = cctmp::table
		(
			U_strlit_type, U_action_type,

			// main:

				sxa_pair( "main_begin" , ActName::main_begin ),
				sxa_pair( "main_end"   , ActName::main_end   ),
				sxa_pair( "main_name"  , ActName::main_name  ),
				sxa_pair( "main_arg"   , ActName::main_arg   ),

			// define:

				sxa_pair( "define_name" , ActName::define_name ),
				sxa_pair( "define_arg"  , ActName::define_arg  ),
				sxa_pair( "define_body" , ActName::define_body ),
				sxa_pair( "define_end"  , ActName::define_end  ),

			// type:

				sxa_pair( "type_number" , ActName::type_number ),
			//	sxa_pair( "type_zero"   , ActName::type_zero   ),

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

			// pred:

				sxa_pair( "pred_end" , ActName::pred_end ),

			// op:

				sxa_pair( "op_lookup" , ActName::op_lookup ),
				sxa_pair( "op_return" , ActName::op_return )
		);
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// pushdown automaton:

/***********************************************************************************************************************/

// interface:

#ifdef NIK_HUSTLE_PARSER
#include NIK_HUSTLE_OBJ
#else

	template<typename T_grammar>
	struct T_hustle_pda : public generator::T_generic_pda<T_grammar>
	{
		using base			= generator::T_generic_pda<T_grammar>;
		using ActName			= typename T_grammar::ActName;
		using T_lexer			= typename T_grammar::T_lexer;
		using Token			= typename T_grammar::Token;

		nik_ces auto prod_size		= cctmp::string_literal("(T(S)B)").size(); // needs refining.

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
	struct T_hustle_parser
	{
		using T_ast		= typename T_action::T_ast;
		using T_pda		= T_hustle_pda<T_grammar>;
		using T_parser		= generator::T_generic_parser<T_action, T_pda>;
		using parseme_type	= generator::T_parseme<T_ast>;
		using parsoid_type	= generator::T_parsoid<T_pda::stack_size, T_pda::prod_size>;

		nik_ces auto & pda	= T_parser::pda; static_assert(!pda.ambiguous, "ambiguous cfg!");

		parseme_type parseme;
		parsoid_type parsoid;

		nik_ce T_hustle_parser(const cselector<char> & s) :

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
	struct T_hustle_parsed
	{
		using T_ast			= T_hustle_ast
						<
							static_source, static_env_lookup,
							contr_size, stack_size, model_size
						>;
		using T_action			= T_hustle_action<T_ast>;
		using T_grammar			= T_hustle_grammar;
		using T_parser			= T_hustle_parser<static_pg_parsed, T_action, T_grammar>;

		nik_ces auto & src		= member_value_U<static_source>;
		nik_ces auto parser		= T_parser{src.cselect()};
		nik_ces auto & value		= parser.parseme.tree;
		using type			= modify_type<_from_reference_, decltype(value)>;
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace hustle

