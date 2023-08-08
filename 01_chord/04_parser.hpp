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
			"Tail      -> identifier : tail       ;"
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
			"       -> HValue     : morph  ;"
			"       -> CValue     : cycle  ;"

			"SValue -> identifier : svalue ;"
			"       -> _          : paste  ;"
			"       -> quote      : quote  ;"
			"       -> HValue     : morph  ;"
			"       -> CValue     : cycle  ;"

			"Start     -> identifier DArgs FirstLine Block RecBlock : define_name ;"
			"DArgs     -> identifier DArgs                          : define_arg  ;"
			"          -> empty                                                   ;"
			"Block     -> Label NewLine Instrs                                    ;"
			"RecBlock  -> PostLine Block RecBlock                                 ;"
			"          -> empty                                     : accept      ;"
			"Instrs    -> Instr NewLine RecInstr LastInstr                        ;"
			"          -> return RValue \\;                         : return      ;"
			"RecInstr  -> Instr NewLine RecInstr                                  ;"
			"          -> empty                                                   ;"
			"LastInstr -> goto Goto \\;                                           ;"
			"          -> tail Tail \\;                                           ;"
			"          -> return RValue \\;                         : return      ;"
			"          -> Label NewLine Instr                                      "
			"                   NewLine RecInstr LastInstr          : go_into     ;"
			"Instr     -> LValue Disp                                             ;"
			"          -> ! MValue \\= SValue Vars                  : voidication ;"
			"          -> test SValue Vars NewLine branch Branch    : conditional ;"
			"          -> void SValue Vars                          : voidication ;"
			"Disp      -> # RValue                                  : assignment  ;"
			"          -> \\= SValue Vars                           : application ;"
			"Vars      -> RValue Vars                                             ;"
			"          -> ! MValue Vars                                           ;"
			"          -> empty                                                   ;"

		// morph:

			"HValue -> compose < MorValue MorValue MArgs \\> ;"
			"       -> subpose < MorValue MorValue MArgs \\> ;"
			"       -> curry   < MorValue MorValue MArgs \\> ;"

			"MArgs    -> MorValue MArgs              ;"
			"         -> empty                       ;"
			"MorValue -> identifier    : morph_value ;"
			"         -> @             : morph_id    ;"
			"         -> *             : morph_deref ;"
			"         -> +             : morph_inc   ;"
			"         -> \\-           : morph_dec   ;"

		// cycle:

			"CValue -> repeat  AMLOpt         LMRIval FIvals ;"
			"       -> map     AMLOpt  LRIval LMRIval  Ivals ;"
			"       -> fold   ACMLOpt   FIval LMRIval  Ivals ;"
			"       -> find    AMLOpt  LRIval LMRIval  Ivals ;"
			"       -> sift    AMLOpt  LRIval LMRIval  Ivals ;"

		    // parameter:

			"AMLOpt  -> < Action |           Mutate | LoopPred \\> ;"
			"ACMLOpt -> < Action | Combine | Mutate | LoopPred \\> ;"

			"Action   -> ActValue PArgs                      ;"
			"         -> empty                               ;"
			"PArgs    -> ActValue PArgs                      ;"
			"         -> empty                               ;"
			"ActValue -> identifier     : cycle_action_value ;"
			"         -> @              : cycle_action_id    ;"
			"         -> *              : cycle_action_deref ;"

			"Combine  -> ParIdent P2Args : cycle_param_upsize    ;"
			"Mutate   -> ParIdent P2Args : cycle_param_upsize    ;"
			"         -> empty           : cycle_param_mutate    ;"
			"LoopPred -> ParIdent P2Args : cycle_param_upsize    ;"
			"         -> empty           : cycle_param_loop_pred ;"
			"P2Args   -> ParValue P1Arg                          ;"
			"         -> empty           : cycle_param_2args     ;"
			"P1Arg    -> ParValue                                ;"
			"         -> empty           : cycle_param_1arg      ;"
			"ParIdent -> identifier      : cycle_param_value     ;"
			"ParValue -> identifier      : cycle_param_value     ;"
			"         -> @               : cycle_param_id        ;"
			"         -> *               : cycle_param_deref     ;"

		    // interval:

			"FIvals -> FIval FIvals                     ;"
			"       -> empty        : cycle_ival_action ;"
			"FIval  -> { }          : cycle_ival_fixed  ;"

			"Ivals -> Ival Ivals                     ;"
			"      -> empty      : cycle_ival_action ;"
			"Ival  ->  FIval                         ;"
			"      -> LRIval                         ;"

			"LRIval  -> LIval PairIter             RIval ;"
			"LMRIval -> LIval PairIter , TonicIter RIval ;"

			"LIval -> [ : cycle_ival_left_closed  ;"
			"      -> ( : cycle_ival_left_open    ;"
			"RIval -> ] : cycle_ival_right_closed ;"
			"      -> ) : cycle_ival_right_open   ;"

		    // iterator:

			"PairIter  ->   + | \\-            : cycle_iter_inc_dec ;"
			"          -> \\- |   +            : cycle_iter_dec_inc ;"
			"          -> IterValue | PrevIter : cycle_iter_upsize  ;"
			"          -> empty                : cycle_iter_pair    ;"
			"PrevIter  -> IterValue                                 ;"
			"          -> ~                    : cycle_iter_none    ;"
			"IterValue -> identifier           : cycle_iter_value   ;"
			"          -> ^ VoidValue                               ;"
			"VoidValue -> identifier           : cycle_iter_void    ;"

			"TonicIter  ->   + | \\-              : cycle_tonic_inc_dec ;"
			"           -> \\- |   +              : cycle_tonic_dec_inc ;"
			"           -> TonicValue | PrevTonic                       ;"
			"           -> empty                  : cycle_tonic_pair    ;"
			"PrevTonic  -> TonicValue                                   ;"
			"           -> ~                      : cycle_tonic_none    ;"
			"TonicValue -> identifier             : cycle_tonic_value   ;"
			"           -> ^ VoidTonic                                  ;"
			"VoidTonic  -> identifier             : cycle_tonic_void    ;"
		);}

		nik_ces auto & map = T_chord_assembly_scanner_grammar::map;

		nik_ces auto action = cctmp::table
		(
			U_strlit_type, U_action_type,

		// atomics:

			sxa_pair( "label"      , ActName::label      ),
			sxa_pair( "branch"     , ActName::branch     ),
			sxa_pair( "goto"       , ActName::go_to      ),
			sxa_pair( "tail"       , ActName::tail       ),
			sxa_pair( "mvalue"     , ActName::mvalue     ),
			sxa_pair( "lvalue"     , ActName::lvalue     ),
			sxa_pair( "copy"       , ActName::copy       ),
			sxa_pair( "first_line" , ActName::first_line ),
			sxa_pair( "new_line"   , ActName::new_line   ),

		// rules:

			sxa_pair( "rvalue" , ActName::rvalue ),
			sxa_pair( "svalue" , ActName::svalue ),
			sxa_pair( "paste"  , ActName::paste  ),
			sxa_pair( "quote"  , ActName::quote  ),
			sxt_pair( "morph"  , ActName::morph  ),
			sxt_pair( "cycle"  , ActName::cycle  ),

			sxa_pair( "define_name" , ActName::define_name ),
			sxa_pair( "define_arg"  , ActName::define_arg  ),
			sxa_pair( "accept"      , ActName::accept      ),
			sxa_pair( "return"      , ActName::re_turn     ),
			sxa_pair( "go_into"     , ActName::go_into     ),
			sxa_pair( "voidication" , ActName::voidication ),
			sxa_pair( "conditional" , ActName::conditional ),
			sxa_pair( "assignment"  , ActName::assignment  ),
			sxa_pair( "application" , ActName::application ),

		// morph:

			sxt_pair( "morph_value" , ActName::morph_value ),
			sxt_pair( "morph_id"    , ActName::morph_id    ),
			sxt_pair( "morph_deref" , ActName::morph_deref ),
			sxt_pair( "morph_inc"   , ActName::morph_inc   ),
			sxt_pair( "morph_dec"   , ActName::morph_dec   ),

		// cycle:

			// action:

			sxt_pair( "cycle_action_value" , ActName::cycle_action_value ),
			sxt_pair( "cycle_action_id"    , ActName::cycle_action_id    ),
			sxt_pair( "cycle_action_deref" , ActName::cycle_action_deref ),

			// param:

			sxt_pair( "cycle_param_upsize"    , ActName::cycle_param_upsize    ),
			sxt_pair( "cycle_param_mutate"    , ActName::cycle_param_mutate    ),
			sxt_pair( "cycle_param_loop_pred" , ActName::cycle_param_loop_pred ),
			sxt_pair( "cycle_param_2args"     , ActName::cycle_param_2args     ),
			sxt_pair( "cycle_param_1arg"      , ActName::cycle_param_1arg      ),
			sxt_pair( "cycle_param_value"     , ActName::cycle_param_value     ),
			sxt_pair( "cycle_param_id"        , ActName::cycle_param_id        ),
			sxt_pair( "cycle_param_deref"     , ActName::cycle_param_deref     ),

			// ival:

			sxt_pair( "cycle_ival_action"       , ActName::cycle_ival_action       ),
			sxt_pair( "cycle_ival_fixed"        , ActName::cycle_ival_fixed        ),
			sxt_pair( "cycle_ival_left_closed"  , ActName::cycle_ival_left_closed  ),
			sxt_pair( "cycle_ival_left_open"    , ActName::cycle_ival_left_open    ),
			sxt_pair( "cycle_ival_right_closed" , ActName::cycle_ival_right_closed ),
			sxt_pair( "cycle_ival_right_open"   , ActName::cycle_ival_right_open   ),

			// iter:

			sxt_pair( "cycle_iter_inc_dec" , ActName::cycle_iter_inc_dec ),
			sxt_pair( "cycle_iter_dec_inc" , ActName::cycle_iter_dec_inc ),
			sxt_pair( "cycle_iter_upsize"  , ActName::cycle_iter_upsize  ),
			sxt_pair( "cycle_iter_pair"    , ActName::cycle_iter_pair    ),
			sxt_pair( "cycle_iter_none"    , ActName::cycle_iter_none    ),
			sxt_pair( "cycle_iter_value"   , ActName::cycle_iter_value   ),
			sxt_pair( "cycle_iter_void"    , ActName::cycle_iter_void    ),

			// tonic:

			sxt_pair( "cycle_tonic_inc_dec" , ActName::cycle_tonic_inc_dec ),
			sxt_pair( "cycle_tonic_dec_inc" , ActName::cycle_tonic_dec_inc ),
			sxt_pair( "cycle_tonic_pair"    , ActName::cycle_tonic_pair    ),
			sxt_pair( "cycle_tonic_none"    , ActName::cycle_tonic_none    ),
			sxt_pair( "cycle_tonic_value"   , ActName::cycle_tonic_value   ),
			sxt_pair( "cycle_tonic_void"    , ActName::cycle_tonic_void    )
		);
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// pushdown automaton:

/***********************************************************************************************************************/

// interface:

#ifdef NIK_CHORD_ASSEMBLY_PARSER
#include NIK_CHORD_ASSEMBLY_PARSER_OBJ
#else

	template<typename T_grammar>
	struct T_chord_assembly_pda : public cctmp::T_generic_pda<T_grammar>
	{
		using base			= cctmp::T_generic_pda<T_grammar>;
		using ActName			= typename T_grammar::ActName;
		using T_lexer			= typename T_grammar::T_lexer;
		using Token			= typename T_grammar::Token;

		nik_ces auto prod_size		= cctmp::string_literal("<A|C|M|L>").size();

		nik_ces auto stack_start	= symbol_type{cctmp::Sign::nonterminal, base::start_index};
		nik_ces auto stack_finish	= symbol_type{cctmp::Sign::terminal, Token::prompt};

		nik_ces auto stack_size		= cctmp::literal("F<A|C|M|L>YPZ{}YPZYP,PZV;HGO").size(); // needs refining.
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

