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

		nik_ces auto source() { return generator::context_free_grammar
		(
			// start:

				"Start",

			// assembly:

				"Start      -> DefBeg DefArgs DefEnd Block RecBlock                        ;"
				"DefArgs    -> DefArg DefArgs                                              ;"
				"           -> empty                                                       ;"
				"Block      -> LabelBeg LabelEnd Instrs                                    ;"
				"RecBlock   -> Block RecBlock                                              ;"
				"           -> empty                                          : asm_accept ;"
				"Instrs     -> Instr RecInstr                                              ;"
				"           -> ReturnBeg UnitVal ReturnEnd                                 ;"
				"RecInstr   -> Instr RecInstr                                              ;"
				"           -> GotoBeg GotoVal GotoEnd                                     ;"
				"           -> TailBeg TailVal TailEnd                                     ;"
				"           -> ReturnBeg UnitVal ReturnEnd                                 ;"
				"           -> empty                                                       ;"
				"Instr      -> LeftVal RightInstr                                          ;"
				"           -> ! SwapBeg \\= SubOp SubArgs SwapEnd                         ;"
				"           -> TestBeg SubOp SubArgs TestEnd BranchBeg BranchVal BranchEnd ;"
				"           -> VoidBeg SubOp SubArgs VoidEnd                               ;"
				"RightInstr -> ApplyBeg SubOp SubArgs ApplyEnd                             ;"
				"           -> AssignBeg UnitVal AssignEnd                                 ;"

				// define:

					"DefBeg -> identifier : asm_define_begin ;"
					"DefArg -> identifier : asm_define_arg   ;"
					"DefEnd -> \\;        : asm_define_end   ;"

				// label:

					"LabelBeg -> label : asm_label_begin ;"
					"LabelEnd -> \\;                     ;"

				// return:

					"ReturnBeg -> return : asm_return_begin ;"
					"ReturnEnd -> \\;    : asm_return_end   ;"

				// goto:

					"GotoBeg -> goto       : asm_goto_begin ;"
					"GotoVal -> identifier : asm_goto_value ;"
					"GotoEnd -> \\;        : asm_goto_end   ;"

				// tail:

					"TailBeg -> tail       : asm_tail_begin ;"
					"TailVal -> identifier : asm_tail_value ;"
					"TailEnd -> \\;        : asm_tail_end   ;"

				// left:

					"LeftVal -> identifier : asm_left_value ;"
					"        -> .          : asm_left_copy  ;"

				// swap:

					"SwapBeg -> identifier : asm_swap_begin ;"
					"SwapEnd -> \\;        : asm_swap_end   ;"

				// test:

					"TestBeg -> test : asm_test_begin ;"
					"TestEnd -> \\;  : asm_test_end   ;"

				// branch:

					"BranchBeg -> branch     : asm_branch_begin ;"
					"BranchVal -> identifier : asm_branch_value ;"
					"BranchEnd -> \\;        : asm_branch_end   ;"

				// void:

					"VoidBeg -> void : asm_void_begin ;"
					"VoidEnd -> \\;  : asm_void_end   ;"

				// apply:

					"ApplyBeg -> \\= : asm_apply_begin ;"
					"ApplyEnd -> \\; : asm_apply_end   ;"

				// assign:

					"AssignBeg ->   # : asm_assign_begin ;"
					"AssignEnd -> \\; : asm_assign_end   ;"

				// sub op:

					"SubOp -> identifier : asm_subop_value ;"
					"      -> _          : asm_subop_paste ;"
					"      -> quote      : asm_subop_quote ;"

				// sub args:

					"SubArgs ->   SubArg SubArgs ;"
					"        -> ! MutArg SubArgs ;"
					"        -> empty            ;"

				// sub arg:

					"SubArg -> identifier : asm_subarg_value ;"
					"       -> _          : asm_subarg_paste ;"
					"       -> quote      : asm_subarg_quote ;"

				// mut arg:

					"MutArg -> identifier : asm_mutarg_value ;"

				// unit value:

					"UnitVal -> identifier : asm_unit_value ;"
					"        -> _          : asm_unit_paste ;"
					"        -> quote      : asm_unit_quote ;"
					"        -> Morph      : asm_unit_morph ;"
					"        -> Cycle      : asm_unit_cycle ;"

			// morph:

				"Morph -> argpose MorArity ArgposeBeg MorOp ArgposeVals ArgposeEnd ;"
				"      -> subpose MorArity SubposeBeg MorOp SubposeVals SubposeEnd ;"
				"      ->   curry MorArity   CurryBeg MorOp   CurryVals   CurryEnd ;"

				// arity:

					"MorArity  -> [ MorNumber ]            ;"
					"          -> empty  : mor_arity_id    ;"
					"MorNumber -> number : mor_arity_value ;"

				// op:

					"MorOp -> identifier : mor_op_value ;"
					"      -> @          : mor_op_id    ;"
					"      -> *          : mor_op_deref ;"
					"      -> +          : mor_op_inc   ;"
					"      -> \\-        : mor_op_dec   ;"

				// argpose:

					"ArgposeVals -> ArgposeVal ArgposeVals     ;"
					"            -> empty                      ;"
					"ArgposeVal  -> number : mor_argpose_value ;"
					"ArgposeBeg  -> {      : mor_argpose_begin ;"
					"ArgposeEnd  -> }      : mor_argpose_end   ;"

				// subpose:

					"SubposeVals -> SubposeVal SubposeVals         ;"
					"            -> empty                          ;"
					"SubposeVal  -> identifier : mor_subpose_value ;"
					"            -> @          : mor_subpose_id    ;"
					"            -> *          : mor_subpose_deref ;"
					"            -> +          : mor_subpose_inc   ;"
					"            -> \\-        : mor_subpose_dec   ;"
					"SubposeBeg  -> {          : mor_subpose_begin ;"
					"SubposeEnd  -> }          : mor_subpose_end   ;"

				// curry:

					"CurryVals -> CurryVal CurryVals           ;"
					"          -> empty                        ;"
					"CurryVal  -> identifier : mor_curry_value ;"
					"CurryBeg  -> {          : mor_curry_begin ;"
					"CurryEnd  -> }          : mor_curry_end   ;"

			// cycle:

				"Cycle -> repeat MorArity  AMPOpt        LMRIval RepeatIvals ;"
				"      -> map    MorArity  AMPOpt LRIval LMRIval    MapIvals ;"
				"      -> fold   MorArity CAMPOpt  FIval LMRIval   FoldIvals ;"
				"      -> find   MorArity  AMPOpt LRIval LMRIval   FindIvals ;"
				"      -> sift   MorArity  AMPOpt LRIval LMRIval   SiftIvals ;"

				// option:

					"CAMPOpt -> OptBeg Combine OptCont Action OptCont Mutate OptCont Predicate OptEnd  ;"
					"AMPOpt  -> OptBeg Action OptCont Mutate OptCont Predicate OptEnd : cyc_option_amp ;"

					"OptCont -> | : cyc_option_cont  ;"
					"OptBeg  -> { : cyc_option_begin ;"
					"OptEnd  -> } : cyc_option_end   ;"

					// op, val:

						"CycOp  -> identifier : cyc_op_value ;"
						"CycVal -> identifier : cyc_value    ;"
						"       -> @          : cyc_id       ;"
						"       -> *          : cyc_deref    ;"

					// combine:

						"Combine   -> CycOp  CombRest2                     ;"
						"CombRest2 -> CycVal CombRest1                     ;"
						"          -> empty            : cyc_combine_rest2 ;"
						"CombRest1 -> CycVal                               ;"
						"          -> empty            : cyc_combine_rest1 ;"

					// action:

						"Action  -> ActOp  ActRest                       ;"
						"        -> empty          : cyc_action_defs     ;"
						"ActRest -> CycVal ActRest                       ;"
						"        -> empty          : cyc_action_rest     ;"
						"ActOp   -> identifier     : cyc_action_op_value ;"
						"        -> @              : cyc_action_op_id    ;"
						"        -> *              : cyc_action_op_deref ;"

					// mutate:

						"Mutate   -> CycOp  MutRest2                    ;"
						"         -> empty           : cyc_mutate_defs  ;"
						"MutRest2 -> CycVal MutRest1                    ;"
						"         -> empty           : cyc_mutate_rest2 ;"
						"MutRest1 -> CycVal                             ;"
						"         -> empty           : cyc_mutate_rest1 ;"

					// predicate:

						"Predicate -> CycOp  PredRest2                       ;"
						"          -> empty            : cyc_predicate_defs  ;"
						"PredRest2 -> CycVal PredRest1                       ;"
						"          -> empty            : cyc_predicate_rest2 ;"
						"PredRest1 -> CycVal                                 ;"
						"          -> empty            : cyc_predicate_rest1 ;"

				// interval:

					"LRIval  -> LIval PairIter             RIval ;"
					"LMRIval -> LIval PairIter , TonicIter RIval ;"

					"LIval -> [     : cyc_ival_left_closed  ;"
					"      -> (     : cyc_ival_left_open    ;"
					"RIval -> ]     : cyc_ival_right_closed ;"
					"      -> )     : cyc_ival_right_open   ;"
					"FIval -> < \\> : cyc_ival_fixed        ;"

					"Ival ->  FIval ;"
					"     -> LRIval ;"

				// iterator:

					"PairIter ->   + | \\-          : cyc_iter_inc_dec ;"
					"         -> \\- |   +          : cyc_iter_dec_inc ;"
					"         -> IterVal | PrevIter : cyc_iter_upsize  ;"
					"         -> empty              : cyc_iter_pair    ;"
					"PrevIter -> IterVal                               ;"
					"         -> ~                  : cyc_iter_none    ;"
					"IterVal  -> identifier         : cyc_iter_value   ;"
					"         -> ^ VoidVal                             ;"
					"VoidVal  -> identifier         : cyc_iter_void    ;"

				// tonic:

					"TonicIter ->   + | \\-            : cyc_tonic_inc_dec ;"
					"          -> \\- |   +            : cyc_tonic_dec_inc ;"
					"          -> TonicVal | PrevTonic                     ;"
					"          -> empty                : cyc_tonic_pair    ;"
					"PrevTonic -> TonicVal                                 ;"
					"          -> ~                    : cyc_tonic_none    ;"
					"TonicVal  -> identifier           : cyc_tonic_value   ;"
					"          -> ^ VoidTonic                              ;"
					"VoidTonic -> identifier           : cyc_tonic_void    ;"

				// (accept):

					"RepeatIvals -> FIval RepeatIvals  ;"
					"            -> empty : cyc_repeat ;"
					"MapIvals    -> Ival MapIvals      ;"
					"            -> empty : cyc_map    ;"
					"FoldIvals   -> Ival FoldIvals     ;"
					"            -> empty : cyc_fold   ;"
					"FindIvals   -> Ival FindIvals     ;"
					"            -> empty : cyc_find   ;"
					"SiftIvals   -> Ival SiftIvals     ;"
					"            -> empty : cyc_sift   ;"
		);}

		nik_ces auto map = cctmp::table
		(
			U_strlit_type, U_token_type,

			sxt_pair( " "          , Token::invalid    ),
			sxt_pair( "$"          , Token::prompt     ),
			sxt_pair( "identifier" , Token::identifier ),
			sxt_pair( "number"     , Token::number     ),
			sxt_pair( "."          , Token::copy       ),
			sxt_pair( "_"          , Token::paste      ),
			sxt_pair( "quote"      , Token::quote      ),
			sxt_pair( "\\;"        , Token::statement  ),
			sxt_pair( "label"      , Token::label      ),
			sxt_pair( "return"     , Token::re_turn    ),
			sxt_pair( "goto"       , Token::go_to      ),
			sxt_pair( "tail"       , Token::tail       ),
			sxt_pair( "!"          , Token::mu_table   ),
			sxt_pair( "\\="        , Token::apply      ),
			sxt_pair( "test"       , Token::test       ),
			sxt_pair( "branch"     , Token::branch     ),
			sxt_pair( "void"       , Token::vo_id      ),
			sxt_pair( "#"          , Token::assign     ),

			sxt_pair( "<"   , Token::l_fixed     ),
			sxt_pair( "["   , Token::l_closed    ),
			sxt_pair( "("   , Token::l_open      ),
			sxt_pair( "{"   , Token::l_scope     ),
			sxt_pair( "\\>" , Token::r_fixed     ),
			sxt_pair( "]"   , Token::r_closed    ),
			sxt_pair( ")"   , Token::r_open      ),
			sxt_pair( "}"   , Token::r_scope     ),
			sxt_pair( "~"   , Token::tilde       ),
			sxt_pair( "@"   , Token::identity    ),
			sxt_pair( "*"   , Token::dereference ),
			sxt_pair( "^"   , Token::caret       ),
			sxt_pair( "+"   , Token::increment   ),
			sxt_pair( "\\-" , Token::decrement   ),
			sxt_pair( "|"   , Token::bar         ),
			sxt_pair( ","   , Token::comma       ),

			sxt_pair( "argpose" , Token::argpose ),
			sxt_pair( "subpose" , Token::subpose ),
			sxt_pair( "curry"   , Token::curry   ),

			sxt_pair( "repeat" , Token::repeat ),
			sxt_pair( "map"    , Token::map    ),
			sxt_pair( "fold"   , Token::fold   ),
			sxt_pair( "find"   , Token::find   ),
			sxt_pair( "sift"   , Token::sift   ),

			sxt_pair( "empty"  , Token::empty  )
		);

		nik_ces auto action = cctmp::table
		(
			U_strlit_type, U_action_type,

			// asm:

				sxa_pair( "asm_accept" , ActName::asm_accept ),

				// define:

					sxa_pair( "asm_define_begin" , ActName::asm_define_begin ),
					sxa_pair( "asm_define_arg"   , ActName::asm_define_arg   ),
					sxa_pair( "asm_define_end"   , ActName::asm_define_end   ),

				// label:

					sxa_pair( "asm_label_begin" , ActName::asm_label_begin ),

				// return:

					sxa_pair( "asm_return_begin" , ActName::asm_return_begin ),
					sxa_pair( "asm_return_end"   , ActName::asm_return_end   ),

				// goto:

					sxa_pair( "asm_goto_begin" , ActName::asm_goto_begin ),
					sxa_pair( "asm_goto_value" , ActName::asm_goto_value ),
					sxa_pair( "asm_goto_end"   , ActName::asm_goto_end   ),

				// tail:

					sxa_pair( "asm_tail_begin" , ActName::asm_tail_begin ),
					sxa_pair( "asm_tail_value" , ActName::asm_tail_value ),
					sxa_pair( "asm_tail_end"   , ActName::asm_tail_end   ),

				// left:

					sxa_pair( "asm_left_value" , ActName::asm_left_value ),
					sxa_pair( "asm_left_copy"  , ActName::asm_left_copy  ),

				// swap:

					sxa_pair( "asm_swap_begin" , ActName::asm_swap_begin ),
					sxa_pair( "asm_swap_end"   , ActName::asm_swap_end   ),

				// test:

					sxa_pair( "asm_test_begin" , ActName::asm_test_begin ),
					sxa_pair( "asm_test_end"   , ActName::asm_test_end   ),

				// branch:

					sxa_pair( "asm_branch_begin" , ActName::asm_branch_begin ),
					sxa_pair( "asm_branch_value" , ActName::asm_branch_value ),
					sxa_pair( "asm_branch_end"   , ActName::asm_branch_end   ),

				// void:

					sxa_pair( "asm_void_begin" , ActName::asm_void_begin ),
					sxa_pair( "asm_void_end"   , ActName::asm_void_end   ),

				// apply:

					sxa_pair( "asm_apply_begin" , ActName::asm_apply_begin ),
					sxa_pair( "asm_apply_end"   , ActName::asm_apply_end   ),

				// assign:

					sxa_pair( "asm_assign_begin" , ActName::asm_assign_begin ),
					sxa_pair( "asm_assign_end"   , ActName::asm_assign_end   ),

				// sub op:

					sxa_pair( "asm_subop_value" , ActName::asm_subop_value ),
					sxa_pair( "asm_subop_paste" , ActName::asm_subop_paste ),
					sxa_pair( "asm_subop_quote" , ActName::asm_subop_quote ),

				// sub arg:

					sxa_pair( "asm_subarg_value" , ActName::asm_subarg_value ),
					sxa_pair( "asm_subarg_paste" , ActName::asm_subarg_paste ),
					sxa_pair( "asm_subarg_quote" , ActName::asm_subarg_quote ),

				// sub mut:

					sxa_pair( "asm_mutarg_value" , ActName::asm_mutarg_value ),

				// unit value:

					sxa_pair( "asm_unit_value" , ActName::asm_unit_value ),
					sxa_pair( "asm_unit_paste" , ActName::asm_unit_paste ),
					sxa_pair( "asm_unit_quote" , ActName::asm_unit_quote ),
					sxa_pair( "asm_unit_morph" , ActName::asm_unit_morph ),
					sxa_pair( "asm_unit_cycle" , ActName::asm_unit_cycle ),

			// morph:

				// arity:

					sxt_pair( "mor_arity_id"    , ActName::mor_arity_id    ),
					sxt_pair( "mor_arity_value" , ActName::mor_arity_value ),

				// op:

					sxt_pair( "mor_op_value" , ActName::mor_op_value ),
					sxt_pair( "mor_op_id"    , ActName::mor_op_id    ),
					sxt_pair( "mor_op_deref" , ActName::mor_op_deref ),
					sxt_pair( "mor_op_inc"   , ActName::mor_op_inc   ),
					sxt_pair( "mor_op_dec"   , ActName::mor_op_dec   ),

				// argpose:

					sxt_pair( "mor_argpose_value" , ActName::mor_argpose_value ),
					sxt_pair( "mor_argpose_begin" , ActName::mor_argpose_begin ),
					sxt_pair( "mor_argpose_end"   , ActName::mor_argpose_end   ),

				// subpose:

					sxt_pair( "mor_subpose_value" , ActName::mor_subpose_value ),
					sxt_pair( "mor_subpose_id"    , ActName::mor_subpose_id    ),
					sxt_pair( "mor_subpose_deref" , ActName::mor_subpose_deref ),
					sxt_pair( "mor_subpose_inc"   , ActName::mor_subpose_inc   ),
					sxt_pair( "mor_subpose_dec"   , ActName::mor_subpose_dec   ),
					sxt_pair( "mor_subpose_begin" , ActName::mor_subpose_begin ),
					sxt_pair( "mor_subpose_end"   , ActName::mor_subpose_end   ),

				// curry:

					sxt_pair( "mor_curry_value" , ActName::mor_curry_value ),
					sxt_pair( "mor_curry_begin" , ActName::mor_curry_begin ),
					sxt_pair( "mor_curry_end"   , ActName::mor_curry_end   ),

			// cycle:

				// option:

					sxt_pair( "cyc_option_amp"   , ActName::cyc_option_amp   ),
					sxt_pair( "cyc_option_cont"  , ActName::cyc_option_cont  ),
					sxt_pair( "cyc_option_begin" , ActName::cyc_option_begin ),
					sxt_pair( "cyc_option_end"   , ActName::cyc_option_end   ),

				// op, val:

					sxt_pair( "cyc_op_value" , ActName::cyc_op_value ),
					sxt_pair( "cyc_value"    , ActName::cyc_value    ),
					sxt_pair( "cyc_id"       , ActName::cyc_id       ),
					sxt_pair( "cyc_deref"    , ActName::cyc_deref    ),

				// combine:

					sxt_pair( "cyc_combine_rest2" , ActName::cyc_combine_rest2 ),
					sxt_pair( "cyc_combine_rest1" , ActName::cyc_combine_rest1 ),

				// action:

					sxt_pair( "cyc_action_defs"     , ActName::cyc_action_defs     ),
					sxt_pair( "cyc_action_rest"     , ActName::cyc_action_rest     ),
					sxt_pair( "cyc_action_op_value" , ActName::cyc_action_op_value ),
					sxt_pair( "cyc_action_op_id"    , ActName::cyc_action_op_id    ),
					sxt_pair( "cyc_action_op_deref" , ActName::cyc_action_op_deref ),

				// mutate:

					sxt_pair( "cyc_mutate_defs"  , ActName::cyc_mutate_defs  ),
					sxt_pair( "cyc_mutate_rest2" , ActName::cyc_mutate_rest2 ),
					sxt_pair( "cyc_mutate_rest1" , ActName::cyc_mutate_rest1 ),

				// predicate:

					sxt_pair( "cyc_predicate_defs"  , ActName::cyc_predicate_defs  ),
					sxt_pair( "cyc_predicate_rest2" , ActName::cyc_predicate_rest2 ),
					sxt_pair( "cyc_predicate_rest1" , ActName::cyc_predicate_rest1 ),

				// interval:

					sxt_pair( "cyc_ival_left_closed"  , ActName::cyc_ival_left_closed  ),
					sxt_pair( "cyc_ival_left_open"    , ActName::cyc_ival_left_open    ),
					sxt_pair( "cyc_ival_right_closed" , ActName::cyc_ival_right_closed ),
					sxt_pair( "cyc_ival_right_open"   , ActName::cyc_ival_right_open   ),
					sxt_pair( "cyc_ival_fixed"        , ActName::cyc_ival_fixed        ),

				// iterator:

					sxt_pair( "cyc_iter_inc_dec" , ActName::cyc_iter_inc_dec ),
					sxt_pair( "cyc_iter_dec_inc" , ActName::cyc_iter_dec_inc ),
					sxt_pair( "cyc_iter_upsize"  , ActName::cyc_iter_upsize  ),
					sxt_pair( "cyc_iter_pair"    , ActName::cyc_iter_pair    ),
					sxt_pair( "cyc_iter_none"    , ActName::cyc_iter_none    ),
					sxt_pair( "cyc_iter_value"   , ActName::cyc_iter_value   ),
					sxt_pair( "cyc_iter_void"    , ActName::cyc_iter_void    ),

				// tonic:

					sxt_pair( "cyc_tonic_inc_dec" , ActName::cyc_tonic_inc_dec ),
					sxt_pair( "cyc_tonic_dec_inc" , ActName::cyc_tonic_dec_inc ),
					sxt_pair( "cyc_tonic_pair"    , ActName::cyc_tonic_pair    ),
					sxt_pair( "cyc_tonic_none"    , ActName::cyc_tonic_none    ),
					sxt_pair( "cyc_tonic_value"   , ActName::cyc_tonic_value   ),
					sxt_pair( "cyc_tonic_void"    , ActName::cyc_tonic_void    ),

				// (accept):

					sxt_pair( "cyc_repeat" , ActName::cyc_repeat ),
					sxt_pair( "cyc_map"    , ActName::cyc_map    ),
					sxt_pair( "cyc_fold"   , ActName::cyc_fold   ),
					sxt_pair( "cyc_find"   , ActName::cyc_find   ),
					sxt_pair( "cyc_sift"   , ActName::cyc_sift   )
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
	struct T_chord_assembly_pda : public generator::T_generic_pda<T_grammar>
	{
		using base			= generator::T_generic_pda<T_grammar>;
		using ActName			= typename T_grammar::ActName;
		using T_lexer			= typename T_grammar::T_lexer;
		using Token			= typename T_grammar::Token;

		nik_ces auto prod_size		= cctmp::string_literal("{C|A|M|P}").size(); // needs refining.

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
	struct T_chord_assembly_parser
	{
		using T_ast		= typename T_action::T_ast;
		using T_pda		= T_chord_assembly_pda<T_grammar>;
		using T_parser		= generator::T_generic_parser<T_action, T_pda>;
		using parseme_type	= generator::T_parseme<T_ast>;
		using parsoid_type	= generator::T_parsoid<T_pda::stack_size, T_pda::prod_size>;

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

