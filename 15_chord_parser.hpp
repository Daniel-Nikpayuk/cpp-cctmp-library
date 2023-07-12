/************************************************************************************************************************
**
** Copyright 2022-2023 Daniel Nikpayuk, Inuit Nunangat, The Inuit Nation
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

namespace chord {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

	template<auto Callable>
	nik_ce auto _static_callable_				= cctmp::_static_callable_<Callable>;

	nik_ce auto _array_length_				= cctmp::_array_length_;
	nik_ce auto _from_reference_				= cctmp::_from_reference_;

	template<auto Op, typename T>
	using modify_type					= cctmp::modify_type<Op, T>;

	using sxt_pair						= cctmp::pair<strlit_type, token_type>;
	using sxa_pair						= cctmp::pair<strlit_type, action_type>;

	using symbol_type					= typename cctmp::symbol_type;
	using csymbol_type					= typename cctmp::csymbol_type;
	nik_ce auto U_symbol_type				= cctmp::U_symbol_type;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// chord assembly:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// grammar:

/***********************************************************************************************************************/

	struct T_chord_assembly_grammar
	{
		using ActName		= CAAN;
		using T_lexer		= T_chord_assembly_lexer;
		using Token		= typename T_lexer::Token;
		nik_ces auto size	= Token::dimension;

		nik_ces auto source() { return cctmp::context_free_grammar
		(
		// start:

			"Start",

		// atomics:

			"Label     -> label      : label      ;"
			"Branch    -> identifier : branch     ;"
			"Goto      -> identifier : goto       ;"
			"MValue    -> identifier : mvalue     ;"
			"LValue    -> identifier : lvalue     ;"
			"          -> .          : copy       ;"
			"FirstLine -> \\;        : first_line ;"
			"NewLine   -> \\;        : new_line   ;"
			"PostLine  -> empty      : new_line   ;"

		// rules:

			"RValue -> identifier : rvalue ;"
			"       -> _          : paste  ;"
			"       -> quote      : quote  ;"
			"       -> CValue              ;"

			"Start     -> identifier Arg FirstLine Block RecBlock : define_name ;"
			"Arg       -> identifier Arg                          : define_arg  ;"
			"          -> empty                                   : end_arg     ;"
			"Block     -> Label NewLine Instrs                                  ;"
			"RecBlock  -> PostLine Block RecBlock                               ;"
			"          -> empty                                   : accept      ;"
			"Instrs    -> Instr NewLine RecInstr LastInstr                      ;"
			"          -> return RValue \\;                       : return      ;"
			"RecInstr  -> Instr NewLine RecInstr                                ;"
			"          -> empty                                                 ;"
			"LastInstr -> goto Goto \\;                                         ;"
			"          -> return RValue \\;                       : return      ;"
			"          -> Label NewLine Instrs                    : go_into     ;"
			"Instr     -> LValue Disp                                           ;"
			"          -> ! MValue \\= RValue Var                 : voidication ;"
			"          -> test RValue Var NewLine branch Branch   : conditional ;"
			"          -> void RValue Var                         : voidication ;"
			"Disp      -> # RValue                                : assignment  ;"
			"          -> \\= RValue Var                          : application ;"
			"Var       -> RValue Var                                            ;"
			"          -> ! MValue Var                                          ;"
			"          -> empty                                                 ;"

		// chord:

			"CValue -> repeat RepeatOpt RepeatOutEnd { }                      : repeat ;"
			"       -> fold   FoldOpt   { } FoldInEnd                         : fold   ;"
			"       -> find   FindOpt   FindOut FindInEnd                     : find   ;"
			"       -> sift   SiftOpt   SiftOut SiftInEnd                     : sift   ;"
			"       -> map    MapOpt    MapOut MapInEnd                       : map    ;"
			"       -> zip    ZipOpt    ZipOut ZipIn1 ZipIn2End2              : zip    ;"
			"       -> glide  GlideOpt  { } GlideIn1 GlideIn2End2             : glide  ;"
			"       -> fasten FastenOpt FastenOut { } FastenIn1 FastenIn2End2 : fasten ;"

		    // parameter:

			"RepeatOpt -> < UAction           | Mutate | LoopPred \\> ;"
			"FoldOpt   -> < Combine           | Mutate | LoopPred \\> ;"
			"FindOpt   -> < Pred              | Mutate | LoopPred \\> ;"
			"SiftOpt   -> < Pred              | Mutate | LoopPred \\> ;"
			"MapOpt    -> < UAction           | Mutate | LoopPred \\> ;"
			"ZipOpt    -> < BAction           | Mutate | LoopPred \\> ;"
			"GlideOpt  -> < BAction | Combine | Mutate | LoopPred \\> ;"

			"FastenOpt -> < BAction | BCarry | UCarry | UCarry | Mutate | LoopPred \\> ;"

			"UAction  -> ParValue 1Arg  : param_upsize    ;"
			"         -> empty          : param_action    ;"
			"BAction  -> ParIdent 2Args : param_upsize    ;"
			"Combine  -> ParIdent 2Args : param_upsize    ;"
			"Pred     -> ParValue 1Arg  : param_upsize    ;"
			"BCarry   -> ParIdent 2Args : param_upsize    ;"
			"UCarry   -> ParValue 1Arg  : param_upsize    ;"
			"Mutate   -> ParIdent 2Args : param_upsize    ;"
			"         -> empty          : param_mutate    ;"
			"LoopPred -> ParIdent 2Args : param_upsize    ;"
			"         -> empty          : param_loop_pred ;"
			"2Args    -> ParValue 1Arg                    ;"
			"         -> empty          : param_2args     ;"
			"1Arg     -> ParValue                         ;"
			"         -> empty          : param_1arg      ;"
			"ParIdent -> identifier     : param_value     ;"
			"ParValue -> identifier     : param_value     ;"
			"         -> @              : param_id        ;"
			"         -> *              : param_deref     ;"

		    // interval/iterator:

			"RepeatOutEnd  -> LIval NextIter ,          RIval ;"
			"FoldInEnd     -> LIval NextIter ,          RIval ;"
			"FindOut       -> LIval NextIter            RIval ;"
			"FindInEnd     -> LIval NextIter ,          RIval ;"
			"SiftOut       -> LIval NextIter            RIval ;"
			"SiftInEnd     -> LIval NextIter ,          RIval ;"
			"MapOut        -> LIval PairIter            RIval ;"
			"MapInEnd      -> LIval PairIter , PairIter RIval ;"
			"ZipOut        -> LIval PairIter            RIval ;"
			"ZipIn1        -> LIval PairIter            RIval ;"
			"ZipIn2End2    -> LIval PairIter , PairIter RIval ;"
			"GlideIn1      -> LIval PairIter            RIval ;"
			"GlideIn2End2  -> LIval PairIter , PairIter RIval ;"
			"FastenOut     -> LIval PairIter            RIval ;"
			"FastenIn1     -> LIval PairIter            RIval ;"
			"FastenIn2End2 -> LIval PairIter , PairIter RIval ;"

			"NextIter  -> IterValue            : iter_upsize  ;"
			"          -> +                    : iter_inc     ;"
			"          -> \\-                  : iter_dec     ;"
			"          -> empty                : iter_next    ;"
			"PairIter  -> + | \\-              : iter_inc_dec ;"
			"          -> \\- | +              : iter_dec_inc ;"
			"          -> IterValue | PrevIter : iter_upsize  ;"
			"          -> empty                : iter_pair    ;"
			"PrevIter  -> IterValue                           ;"
			"          -> ~                    : iter_none    ;"
			"IterValue -> identifier           : iter_value   ;"
			"          -> @                    : iter_id      ;"
			"          -> *                    : iter_deref   ;"

			"LIval -> [ : left_closed  ;"
			"      -> ( : left_open    ;"
			"RIval -> ] : right_closed ;"
			"      -> ) : right_open   ;"
		);}

		nik_ces auto map = cctmp::table
		(
			U_strlit_type, U_token_type,

			sxt_pair( " "          , Token::invalid    ),
			sxt_pair( "$"          , Token::prompt     ),
			sxt_pair( "identifier" , Token::identifier ),
			sxt_pair( "."          , Token::copy       ),
			sxt_pair( "_"          , Token::paste      ),
			sxt_pair( "quote"      , Token::quote      ),
			sxt_pair( "\\;"        , Token::statement  ),
			sxt_pair( "label"      , Token::label      ),
			sxt_pair( "return"     , Token::re_turn    ),
			sxt_pair( "goto"       , Token::go_to      ),
			sxt_pair( "!"          , Token::mu_table   ),
			sxt_pair( "\\="        , Token::apply      ),
			sxt_pair( "test"       , Token::test       ),
			sxt_pair( "branch"     , Token::branch     ),
			sxt_pair( "void"       , Token::vo_id      ),
			sxt_pair( "#"          , Token::assign     ),

			sxt_pair( "<"   , Token::l_option    ),
			sxt_pair( "["   , Token::l_closed    ),
			sxt_pair( "("   , Token::l_open      ),
			sxt_pair( "{"   , Token::l_fixed     ),
			sxt_pair( "\\>" , Token::r_option    ),
			sxt_pair( "]"   , Token::r_closed    ),
			sxt_pair( ")"   , Token::r_open      ),
			sxt_pair( "}"   , Token::r_fixed     ),
			sxt_pair( "~"   , Token::tilde       ),
			sxt_pair( "@"   , Token::identity    ),
			sxt_pair( "*"   , Token::dereference ),
			sxt_pair( "+"   , Token::increment   ),
			sxt_pair( "\\-" , Token::decrement   ),
			sxt_pair( "|"   , Token::bar         ),
			sxt_pair( ","   , Token::comma       ),

			sxt_pair( "repeat" , Token::repeat ),
			sxt_pair( "fold"   , Token::fold   ),
			sxt_pair( "find"   , Token::find   ),
			sxt_pair( "sift"   , Token::sift   ),
			sxt_pair( "map"    , Token::map    ),
			sxt_pair( "zip"    , Token::zip    ),
			sxt_pair( "glide"  , Token::glide  ),
			sxt_pair( "fasten" , Token::fasten ),

			sxt_pair( "empty"  , Token::empty  )
		);

		nik_ces auto action = cctmp::table
		(
			U_strlit_type, U_action_type,

			sxa_pair( "define_name" , ActName::define_name ),
			sxa_pair( "define_arg"  , ActName::define_arg  ),
			sxa_pair( "end_arg"     , ActName::end_arg     ),
			sxa_pair( "first_line"  , ActName::first_line  ),
			sxa_pair( "new_line"    , ActName::new_line    ),
			sxa_pair( "label"       , ActName::label       ),
			sxa_pair( "branch"      , ActName::branch      ),
			sxa_pair( "goto"        , ActName::go_to       ),
			sxa_pair( "go_into"     , ActName::go_into     ),
			sxa_pair( "return"      , ActName::re_turn     ),
			sxa_pair( "application" , ActName::application ),
			sxa_pair( "voidication" , ActName::voidication ),
			sxa_pair( "conditional" , ActName::conditional ),
			sxa_pair( "assignment"  , ActName::assignment  ),
			sxa_pair( "lvalue"      , ActName::lvalue      ),
			sxa_pair( "mvalue"      , ActName::mvalue      ),
			sxa_pair( "rvalue"      , ActName::rvalue      ),
			sxa_pair( "copy"        , ActName::copy        ),
			sxa_pair( "paste"       , ActName::paste       ),
			sxa_pair( "quote"       , ActName::quote       ),

			sxt_pair( "repeat" , ActName::repeat ),
			sxt_pair( "fold"   , ActName::fold   ),
			sxt_pair( "find"   , ActName::find   ),
			sxt_pair( "sift"   , ActName::sift   ),
			sxt_pair( "map"    , ActName::map    ),
			sxt_pair( "zip"    , ActName::zip    ),
			sxt_pair( "glide"  , ActName::glide  ),
			sxt_pair( "fasten" , ActName::fasten ),

			sxt_pair( "param_upsize"    , ActName::param_upsize    ),
			sxt_pair( "param_action"    , ActName::param_action    ),
			sxt_pair( "param_mutate"    , ActName::param_mutate    ),
			sxt_pair( "param_loop_pred" , ActName::param_loop_pred ),
			sxt_pair( "param_value"     , ActName::param_value     ),
			sxt_pair( "param_deref"     , ActName::param_deref     ),
			sxt_pair( "param_id"        , ActName::param_id        ),
			sxt_pair( "param_2args"     , ActName::param_2args     ),
			sxt_pair( "param_1arg"      , ActName::param_1arg      ),

			sxt_pair( "iter_upsize"  , ActName::iter_upsize  ),
			sxt_pair( "iter_next"    , ActName::iter_next    ),
			sxt_pair( "iter_pair"    , ActName::iter_pair    ),
			sxt_pair( "iter_inc"     , ActName::iter_inc     ),
			sxt_pair( "iter_dec"     , ActName::iter_dec     ),
			sxt_pair( "iter_inc_dec" , ActName::iter_inc_dec ),
			sxt_pair( "iter_dec_inc" , ActName::iter_dec_inc ),
			sxt_pair( "iter_value"   , ActName::iter_value   ),
			sxt_pair( "iter_deref"   , ActName::iter_deref   ),
			sxt_pair( "iter_id"      , ActName::iter_id      ),
			sxt_pair( "iter_none"    , ActName::iter_none    ),

			sxt_pair( "left_closed"  , ActName::left_closed  ),
			sxt_pair( "left_open"    , ActName::left_open    ),
			sxt_pair( "right_closed" , ActName::right_closed ),
			sxt_pair( "right_open"   , ActName::right_open   ),

			sxa_pair( "accept" , ActName::accept )
		);
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// pushdown automaton:

/***********************************************************************************************************************/

// interface:

#ifdef NIK_CHORD_ASSEMBLY_PDA
#include"transition_tables/01_chord_assembly_parser.hpp"
#else

	template<typename T_grammar>
	struct T_chord_assembly_pda : public cctmp::T_generic_pda<T_grammar>
	{
		using base			= cctmp::T_generic_pda<T_grammar>;
		using ActName			= typename T_grammar::ActName;
		using T_lexer			= typename T_grammar::T_lexer;
		using Token			= typename T_grammar::Token;

		nik_ces auto prod_size		= cctmp::string_literal("<B|B|U|U|B|B>").size(); // needs refining.

		nik_ces auto stack_start	= symbol_type{cctmp::Sign::nonterminal, base::start_index};
		nik_ces auto stack_finish	= symbol_type{cctmp::Sign::terminal, Token::prompt};

		nik_ces auto stack_size		= cctmp::literal("6<B|B|U|U|B|B>YPZ{}YPZYP,PZV;HGO").size(); // needs refining.
							// literal is intentional.
							// this is the longest possible sentential.
	};

#endif

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// parser:

/***********************************************************************************************************************/

// interface:

	template<auto static_pg_parsed, typename T_action, typename T_grammar>
	struct T_chord_assembly_parser
	{
		using T_ast		= typename T_action::T_ast;
		using T_pda		= T_chord_assembly_pda<T_grammar>;
		using T_parser		= cctmp::T_generic_parser<T_action, T_pda>;
		using parseme_type	= cctmp::T_parseme<T_ast>;
		using parsoid_type	= cctmp::T_parsoid<T_pda::stack_size, T_pda::prod_size>;

		nik_ces auto & pda	= T_parser::pda; static_assert(!pda.ambiguous, "ambiguous cfg!");

		parseme_type parseme;
		parsoid_type parsoid;

		nik_ce T_chord_assembly_parser(const cselector<char> & s) :

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

	template<auto static_pg_parsed, auto static_scanned>
	struct T_chord_assembly_parsed
	{
		using T_ast			= T_chord_assembly_ast<static_scanned>;
		using T_action			= T_chord_assembly_action<T_ast>;
		using T_grammar			= T_chord_assembly_grammar;
		using T_parser			= T_chord_assembly_parser<static_pg_parsed, T_action, T_grammar>;

		nik_ces auto & src		= T_store_U<static_scanned>::src;
		nik_ces auto parser		= T_parser{src.cselect()};
		nik_ces auto & value		= parser.parseme.tree;
		using type			= modify_type<_from_reference_, decltype(value)>;
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace chord

