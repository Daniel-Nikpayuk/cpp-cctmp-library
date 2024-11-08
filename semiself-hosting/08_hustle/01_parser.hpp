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

// action:

/***********************************************************************************************************************/

// name:

	struct HustleAssemblyActionName
	{
		enum : action_type
		{
			nop = generator::AN::nop,

			// param:

				param_type,

			// main:

				main_begin,
				main_end,
				main_arg,
				main_deduce,
				main_port,

			// define:

				define_name,
				define_arg,
				define_begin,
				define_end,
				define_port,

			// port:

				port_deduce,
				port_lookup,

			// return:

				return_false,
				return_true,
				return_n_number,
				return_r_number,
				return_character,
				return_string,
				return_lookup,

			// apply:

				apply_begin_oper,
				apply_begin_expr,
				apply_end,
				apply_patch,
				apply_call,

			// if:

				if_begin,
				if_ante,
				if_conse,
				if_end,

			// dimension:

				dimension
		};

	}; using HAAN = HustleAssemblyActionName;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// space:

/***********************************************************************************************************************/

// grammar:

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

				"Start   -> ( Generic )                             ;"
				"Generic -> type Param Params ( Main )              ;"
				"        -> Main                                    ;"
				"Params  -> Param Params                            ;"
				"        -> empty                                   ;"
				"Param   -> identifier                 : param_type ;"

				// main:

					"Main      -> define ( MainSign ) MainType MainBody                ;"
					"MainSign  -> identifier MainArgs                   : main_begin   ;"
					"MainArgs  -> MainArg MainArgs                                     ;"
					"          -> empty                                                ;"
					"MainArg   -> identifier                            : main_arg     ;"
					"MainBody  -> Expr0 MainExprs                       : define_begin ;"
					"MainExprs -> Expr0 MainExprs                                      ;"
					"          -> empty                                 : main_end     ;"

					"MainType -> \\-\\> MainPort               ;"
					"         -> empty           : main_deduce ;"
					"MainPort -> identifier      : main_port   ;"

				// return:

					"Literal -> Value Type                    ;"
					"Value   -> #f         : return_false     ;"
					"        -> #t         : return_true      ;"
					"        -> n_number   : return_n_number  ;"
					"        -> r_number   : return_r_number  ;"
					"        -> character  : return_character ;"
					"        -> string     : return_string    ;"
					"Lookup  -> identifier : return_lookup    ;"
					"        -> \\=        : return_lookup    ;"
					"        -> <          : return_lookup    ;"
					"        -> <\\=       : return_lookup    ;"
					"        -> \\>        : return_lookup    ;"
					"        -> \\>\\=     : return_lookup    ;"
					"        -> +          : return_lookup    ;"
					"        -> *          : return_lookup    ;"
					"        -> \\-        : return_lookup    ;"
					"        -> /          : return_lookup    ;"

					"Type -> \\: Port                 ;"
					"     -> empty      : port_deduce ;"
					"Port -> identifier : port_lookup ;"

				// expression:

					"Expr0 -> Literal   ;"
					"      -> Lookup    ;"
					"      -> ( Expr1 ) ;"

					"Expr1 -> Literal                     ;"
					"      -> Op OpRest                   ;"
					"      -> IfBeg Pred Ante Conse IfEnd ;"
					"      -> define DefDisp              ;"
					"      -> quote Expr0                 ;"
					"      -> begin Exprs                 ;"
					"      -> lambda LArgs LBody          ;"
					"      -> set! VarExpr ValExpr        ;"

					"Exprs -> Expr0 Exprs ;"
					"      -> empty       ;"

				// define:

					"DefDisp  -> VarExpr ValExpr                   ;"
					"         -> ( DefSign ) DefType DefBody       ;"
					"DefSign  -> identifier DefArgs : define_name  ;"
					"DefArgs  -> DefArg DefArgs                    ;"
					"         -> empty                             ;"
					"DefArg   -> identifier         : define_arg   ;"
					"DefBody  -> Expr0 DefExprs     : define_begin ;"
					"DefExprs -> Expr0 DefExprs                    ;"
					"         -> empty              : define_end   ;"

					"DefType -> \\-\\> DefPort               ;"
					"        -> empty                        ;"
					"DefPort -> identifier     : define_port ;"

				// application:

					"Op     -> Lookup       : apply_begin_oper ;"
					"       -> ( Expr1 )    : apply_begin_expr ;"
					"OpRest -> Expr0 OpArgs : apply_patch      ;"
					"       -> empty        : apply_call       ;"
					"OpArgs -> Expr0 OpArgs                    ;"
					"       -> empty        : apply_end        ;"

				// conditional:

					"IfBeg   -> if        : if_begin ;"
					"Pred    -> Literal              ;"
					"        -> Lookup               ;"
					"        -> ( Expr1 )            ;"
					"Ante    -> Expr0     : if_ante  ;"
					"Conse   -> Expr0     : if_conse ;"
					"IfEnd   -> empty     : if_end   ;"

				// (other):

					"VarExpr -> identifier ;"
					"ValExpr -> Expr0      ;"

					"LArgs -> Expr0 ;"
					"LBody -> Expr0 ;"
		);}

		nik_ces auto map = table
		(
			U_strlit_type, U_token_type,

			sxt_pair( " "      , Token::invalid  ),
			sxt_pair( "$"      , Token::prompt   ),
			sxt_pair( "("      , Token::l_expr   ),
			sxt_pair( ")"      , Token::r_expr   ),
			sxt_pair( "\\-\\>" , Token::op_type  ),
			sxt_pair( "\\:"    , Token::arg_type ),

			sxt_pair( "identifier" , Token::identifier ),
			sxt_pair( "#f"         , Token::bool_f     ),
			sxt_pair( "#t"         , Token::bool_t     ),
			sxt_pair( "n_number"   , Token::n_number   ),
			sxt_pair( "r_number"   , Token::r_number   ),
			sxt_pair( "character"  , Token::character  ),
			sxt_pair( "string"     , Token::string     ),

			sxt_pair( "if"     , Token::if_    ),
			sxt_pair( "eq?"    , Token::eq_    ),
			sxt_pair( "let"    , Token::let    ),
			sxt_pair( "car"    , Token::car    ),
			sxt_pair( "cdr"    , Token::cdr    ),
			sxt_pair( "type"   , Token::type   ),
			sxt_pair( "set!"   , Token::set_   ),
			sxt_pair( "cons"   , Token::cons   ),
			sxt_pair( "list"   , Token::list   ),
			sxt_pair( "begin"  , Token::begin  ),
			sxt_pair( "quote"  , Token::quote  ),
			sxt_pair( "define" , Token::define ),
			sxt_pair( "lambda" , Token::lambda ),

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

		nik_ces auto action = table
		(
			U_strlit_type, U_action_type,

			// main:

				sxa_pair( "param_type" , ActName::param_type ),

			// main:

				sxa_pair( "main_begin"  , ActName::main_begin  ),
				sxa_pair( "main_end"    , ActName::main_end    ),
				sxa_pair( "main_arg"    , ActName::main_arg    ),
				sxa_pair( "main_deduce" , ActName::main_deduce ),
				sxa_pair( "main_port"   , ActName::main_port   ),

			// define:

				sxa_pair( "define_name"  , ActName::define_name  ),
				sxa_pair( "define_arg"   , ActName::define_arg   ),
				sxa_pair( "define_begin" , ActName::define_begin ),
				sxa_pair( "define_end"   , ActName::define_end   ),
				sxa_pair( "define_port"  , ActName::define_port  ),

			// port:

				sxa_pair( "port_deduce" , ActName::port_deduce ),
				sxa_pair( "port_lookup" , ActName::port_lookup ),

			// return:

				sxa_pair( "return_false"     , ActName::return_false     ),
				sxa_pair( "return_true"      , ActName::return_true      ),
				sxa_pair( "return_n_number"  , ActName::return_n_number  ),
				sxa_pair( "return_r_number"  , ActName::return_r_number  ),
				sxa_pair( "return_character" , ActName::return_character ),
				sxa_pair( "return_string"    , ActName::return_string    ),
				sxa_pair( "return_lookup"    , ActName::return_lookup    ),

			// apply:

				sxa_pair( "apply_begin_oper" , ActName::apply_begin_oper ),
				sxa_pair( "apply_begin_expr" , ActName::apply_begin_expr ),
				sxa_pair( "apply_end"        , ActName::apply_end        ),
				sxa_pair( "apply_patch"      , ActName::apply_patch      ),
				sxa_pair( "apply_call"       , ActName::apply_call       ),

			// if:

				sxa_pair( "if_begin" , ActName::if_begin ),
				sxa_pair( "if_ante"  , ActName::if_ante  ),
				sxa_pair( "if_conse" , ActName::if_conse ),
				sxa_pair( "if_end"   , ActName::if_end   )
		);
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// pushdown automaton:

/***********************************************************************************************************************/

// interface:

#ifdef NIK_HUSTLE_PARSER
#include NIK_HUSTLE_PARSER_OBJ
#else

	template<typename T_grammar>
	struct T_hustle_pda : public generator::T_generic_pda<T_grammar>
	{
		using base			= generator::T_generic_pda<T_grammar>;
		using ActName			= typename T_grammar::ActName;
		using T_lexer			= typename T_grammar::T_lexer;
		using Token			= typename T_grammar::Token;

		nik_ces auto prod_size		= string_literal("d(S)TB").size(); // needs refining.

		nik_ces auto stack_start	= symbol_type{generator::Sign::nonterminal, base::start_index};
		nik_ces auto stack_finish	= symbol_type{generator::Sign::terminal, Token::prompt};

		nik_ces auto stack_size		= literal("F{C|A|M|P}YPZ<>YPZYP,PZV;HGO").size(); // needs refining.
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

// translation action:

	template<action_type, auto...> struct T_hustle_translation_action;

	template<typename AST>
	struct T_hustle_ta :
		public generator::T_generic_translation_action<T_hustle_translation_action, AST, HAAN>
			{ };

	// interface:

		template<typename AST>
		struct T_hustle_action
		{
			using T_ast		= AST;

			nik_ces auto value	= T_hustle_ta<AST>{};
			using type		= decltype(value);
		};

/***********************************************************************************************************************/

// tree:

	template<auto... Vs> 
	struct T_hustle_syntax_tree : public assembly::T_syntax_tree<Vs...>
	{
		using base = assembly::T_syntax_tree<Vs...>;

		nik_ce T_hustle_syntax_tree() : base{} { }
	};

/***********************************************************************************************************************/

// interface:

	template
	<
		auto static_pg_parsed, auto static_source, auto static_env_lookup,
		auto contr_size, auto stack_size, auto model_size
	>
	struct T_hustle_parsed
	{
		using T_ast			= T_hustle_syntax_tree
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

