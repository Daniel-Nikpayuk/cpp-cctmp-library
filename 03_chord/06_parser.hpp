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

				"Start      -> FuncBeg FuncArgs FuncEnd Block RecBlock                     ;"
				"FuncArgs   -> FuncArg FuncArgs                                            ;"
				"           -> empty                                                       ;"
				"Block      -> LabelBeg LabelEnd Instrs                                    ;"
				"RecBlock   -> Block RecBlock                                              ;"
				"           -> empty                                                       ;"
				"Instrs     -> Instr RecInstr LastInstr                                    ;"
				"           -> ReturnBeg UnitVal ReturnEnd                                 ;"
				"RecInstr   -> Instr RecInstr                                              ;"
				"           -> empty                                                       ;"
				"LastInstr  -> GotoBeg GotoVal GotoEnd                                     ;"
				"           -> TailBeg TailVal TailEnd                                     ;"
				"           -> ReturnBeg UnitVal ReturnEnd                                 ;"
				"           -> LabelGotoBeg LabelEnd Instr RecInstr LastInstr              ;"
				"Instr      -> LeftVal RightInstr                                          ;"
				"           -> ! SwapBeg \\= OpVal ArgVals SwapEnd                         ;"
				"           -> TestBeg OpVal ArgVals TestEnd BranchBeg BranchVal BranchEnd ;"
				"           -> VoidBeg OpVal ArgVals VoidEnd                               ;"
				"RightInstr -> ApplyBeg OpVal ArgVals ApplyEnd                             ;"
				"           -> AssignBeg UnitVal AssignEnd                                 ;"

				// function:

					"FuncBeg -> identifier : asm_func_begin ;"
					"FuncArg -> identifier : asm_func_arg   ;"
					"FuncEnd -> \\;        : asm_func_end   ;"

				// label:

					"LabelBeg     -> label : asm_label_begin      ;"
					"LabelGotoBeg -> label : asm_label_goto_begin ;"
					"LabelEnd     -> \\;                          ;"

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

				// op value:

					"OpVal -> identifier : asm_op_value ;"
					"      -> _          : asm_op_paste ;"
					"      -> quote      : asm_op_quote ;"

				// arg values:

					"ArgVals -> ArgVal ArgVals   ;"
					"        -> ! MutVal ArgVals ;"
					"        -> empty            ;"

				// arg value:

					"ArgVal -> identifier : asm_arg_value ;"
					"       -> _          : asm_arg_paste ;"
					"       -> quote      : asm_arg_quote ;"

				// mut value:

					"MutVal -> identifier : asm_mut_value ;"

				// unit value:

					"UnitVal -> identifier : asm_unit_value ;"
					"        -> _          : asm_unit_paste ;"
					"        -> quote      : asm_unit_quote ;"
					"        -> Morph      : asm_unit_morph ;"
				//	"        -> Cycle      : asm_unit_cycle ;"

			// morph:

				"Morph -> argpose [ MorOpArity ] ArgposeBeg MorOpVal ArgposeVals ArgposeEnd ;"
				"      -> subpose [ MorOpArity ] SubposeBeg MorOpVal SubposeVals SubposeEnd ;"
				"      ->   curry [ MorOpArity ]   CurryBeg MorOpVal   CurryVals   CurryEnd ;"

				// op:

					"MorOpArity -> number     : mor_op_arity ;"
					"MorOpVal   -> identifier : mor_op_value ;"
					"           -> @          : mor_op_id    ;"
					"           -> *          : mor_op_deref ;"
					"           -> +          : mor_op_inc   ;"
					"           -> \\-        : mor_op_dec   ;"

				// argpose:

					"ArgposeBeg -> { : mor_argpose_begin ;"
					"ArgposeEnd -> } : mor_argpose_end   ;"

					"ArgposeVals -> ArgposeVal ArgposeVals ;"
					"            -> empty                  ;"

					"ArgposeVal -> number : mor_argpose_value ;"

				// subpose:

					"SubposeBeg -> { : mor_subpose_begin ;"
					"SubposeEnd -> } : mor_subpose_end   ;"

					"SubposeVals -> SubposeVal SubposeVals ;"
					"            -> empty                  ;"

					"SubposeVal -> identifier : mor_subpose_value ;"
					"           -> @          : mor_subpose_id    ;"
					"           -> *          : mor_subpose_deref ;"
					"           -> +          : mor_subpose_inc   ;"
					"           -> \\-        : mor_subpose_dec   ;"

				// curry:

					"CurryBeg -> { : mor_curry_begin ;"
					"CurryEnd -> } : mor_curry_end   ;"

					"CurryVals -> CurryVal CurryVals ;"
					"          -> empty              ;"

					"CurryVal -> identifier : mor_curry_value ;"

			// cycle:

			//	"CValue -> repeat  AMLOpt         LMRIval FIvals ;"
			//	"       -> map     AMLOpt  LRIval LMRIval  Ivals ;"
			//	"       -> fold   ACMLOpt   FIval LMRIval  Ivals ;"
			//	"       -> find    AMLOpt  LRIval LMRIval  Ivals ;"
			//	"       -> sift    AMLOpt  LRIval LMRIval  Ivals ;"

			    // parameter:

			//	"AMLOpt  -> < Action |           Mutate | LoopPred \\> ;"
			//	"ACMLOpt -> < Action | Combine | Mutate | LoopPred \\> ;"

			//	"Action   -> ActValue PArgs                      ;"
			//	"         -> empty                               ;"
			//	"PArgs    -> ActValue PArgs                      ;"
			//	"         -> empty                               ;"
			//	"ActValue -> identifier     : cycle_action_value ;"
			//	"         -> @              : cycle_action_id    ;"
			//	"         -> *              : cycle_action_deref ;"

			//	"Combine  -> ParIdent P2Args : cycle_param_upsize    ;"
			//	"Mutate   -> ParIdent P2Args : cycle_param_upsize    ;"
			//	"         -> empty           : cycle_param_mutate    ;"
			//	"LoopPred -> ParIdent P2Args : cycle_param_upsize    ;"
			//	"         -> empty           : cycle_param_loop_pred ;"
			//	"P2Args   -> ParValue P1Arg                          ;"
			//	"         -> empty           : cycle_param_2args     ;"
			//	"P1Arg    -> ParValue                                ;"
			//	"         -> empty           : cycle_param_1arg      ;"
			//	"ParIdent -> identifier      : cycle_param_value     ;"
			//	"ParValue -> identifier      : cycle_param_value     ;"
			//	"         -> @               : cycle_param_id        ;"
			//	"         -> *               : cycle_param_deref     ;"

			    // interval:

			//	"FIvals -> FIval FIvals                     ;"
			//	"       -> empty        : cycle_ival_action ;"
			//	"FIval  -> { }          : cycle_ival_fixed  ;"

			//	"Ivals -> Ival Ivals                     ;"
			//	"      -> empty      : cycle_ival_action ;"
			//	"Ival  ->  FIval                         ;"
			//	"      -> LRIval                         ;"

			//	"LRIval  -> LIval PairIter             RIval ;"
			//	"LMRIval -> LIval PairIter , TonicIter RIval ;"

			//	"LIval -> [ : cycle_ival_left_closed  ;"
			//	"      -> ( : cycle_ival_left_open    ;"
			//	"RIval -> ] : cycle_ival_right_closed ;"
			//	"      -> ) : cycle_ival_right_open   ;"

			    // iterator:

			//	"PairIter  ->   + | \\-            : cycle_iter_inc_dec ;"
			//	"          -> \\- |   +            : cycle_iter_dec_inc ;"
			//	"          -> IterValue | PrevIter : cycle_iter_upsize  ;"
			//	"          -> empty                : cycle_iter_pair    ;"
			//	"PrevIter  -> IterValue                                 ;"
			//	"          -> ~                    : cycle_iter_none    ;"
			//	"IterValue -> identifier           : cycle_iter_value   ;"
			//	"          -> ^ VoidValue                               ;"
			//	"VoidValue -> identifier           : cycle_iter_void    ;"

			//	"TonicIter  ->   + | \\-              : cycle_tonic_inc_dec ;"
			//	"           -> \\- |   +              : cycle_tonic_dec_inc ;"
			//	"           -> TonicValue | PrevTonic                       ;"
			//	"           -> empty                  : cycle_tonic_pair    ;"
			//	"PrevTonic  -> TonicValue                                   ;"
			//	"           -> ~                      : cycle_tonic_none    ;"
			//	"TonicValue -> identifier             : cycle_tonic_value   ;"
			//	"           -> ^ VoidTonic                                  ;"
			//	"VoidTonic  -> identifier             : cycle_tonic_void    ;"
		);}

		nik_ces auto & map = T_chord_assembly_scanner_grammar::map;

		nik_ces auto action = cctmp::table
		(
			U_strlit_type, U_action_type,

			// asm:

				// function:

					sxa_pair( "asm_func_begin" , ActName::asm_func_begin ),
					sxa_pair( "asm_func_arg"   , ActName::asm_func_arg   ),
					sxa_pair( "asm_func_end"   , ActName::asm_func_end   ),

				// label:

					sxa_pair( "asm_label_begin"      , ActName::asm_label_begin      ),
					sxa_pair( "asm_label_goto_begin" , ActName::asm_label_goto_begin ),

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

				// op value:

					sxa_pair( "asm_op_value" , ActName::asm_op_value ),
					sxa_pair( "asm_op_paste" , ActName::asm_op_paste ),
					sxa_pair( "asm_op_quote" , ActName::asm_op_quote ),

				// arg value:

					sxa_pair( "asm_arg_value" , ActName::asm_arg_value ),
					sxa_pair( "asm_arg_paste" , ActName::asm_arg_paste ),
					sxa_pair( "asm_arg_quote" , ActName::asm_arg_quote ),

				// mut value:

					sxa_pair( "asm_mut_value" , ActName::asm_mut_value ),

				// unit value:

					sxa_pair( "asm_unit_value" , ActName::asm_unit_value ),
					sxa_pair( "asm_unit_paste" , ActName::asm_unit_paste ),
					sxa_pair( "asm_unit_quote" , ActName::asm_unit_quote ),
					sxa_pair( "asm_unit_morph" , ActName::asm_unit_morph ),
					sxa_pair( "asm_unit_cycle" , ActName::asm_unit_cycle ),

			// morph:

				// op:

					sxt_pair( "mor_op_arity" , ActName::mor_op_arity ),
					sxt_pair( "mor_op_value" , ActName::mor_op_value ),
					sxt_pair( "mor_op_id"    , ActName::mor_op_id    ),
					sxt_pair( "mor_op_deref" , ActName::mor_op_deref ),
					sxt_pair( "mor_op_inc"   , ActName::mor_op_inc   ),
					sxt_pair( "mor_op_dec"   , ActName::mor_op_dec   ),

				// argpose:

					sxt_pair( "mor_argpose_begin" , ActName::mor_argpose_begin ),
					sxt_pair( "mor_argpose_end"   , ActName::mor_argpose_end   ),

					sxt_pair( "mor_argpose_value" , ActName::mor_argpose_value ),

				// subpose:

					sxt_pair( "mor_subpose_begin" , ActName::mor_subpose_begin ),
					sxt_pair( "mor_subpose_end"   , ActName::mor_subpose_end   ),

					sxt_pair( "mor_subpose_value" , ActName::mor_subpose_value ),
					sxt_pair( "mor_subpose_id"    , ActName::mor_subpose_id    ),
					sxt_pair( "mor_subpose_deref" , ActName::mor_subpose_deref ),
					sxt_pair( "mor_subpose_inc"   , ActName::mor_subpose_inc   ),
					sxt_pair( "mor_subpose_dec"   , ActName::mor_subpose_dec   ),

				// curry:

					sxt_pair( "mor_curry_begin" , ActName::mor_curry_begin ),
					sxt_pair( "mor_curry_end"   , ActName::mor_curry_end   ),

					sxt_pair( "mor_curry_value" , ActName::mor_curry_value )//,

			// cycle:

				// action:

			//	sxt_pair( "cycle_action_value" , ActName::cycle_action_value ),
			//	sxt_pair( "cycle_action_id"    , ActName::cycle_action_id    ),
			//	sxt_pair( "cycle_action_deref" , ActName::cycle_action_deref ),

				// param:

			//	sxt_pair( "cycle_param_upsize"    , ActName::cycle_param_upsize    ),
			//	sxt_pair( "cycle_param_mutate"    , ActName::cycle_param_mutate    ),
			//	sxt_pair( "cycle_param_loop_pred" , ActName::cycle_param_loop_pred ),
			//	sxt_pair( "cycle_param_2args"     , ActName::cycle_param_2args     ),
			//	sxt_pair( "cycle_param_1arg"      , ActName::cycle_param_1arg      ),
			//	sxt_pair( "cycle_param_value"     , ActName::cycle_param_value     ),
			//	sxt_pair( "cycle_param_id"        , ActName::cycle_param_id        ),
			//	sxt_pair( "cycle_param_deref"     , ActName::cycle_param_deref     ),

				// ival:

			//	sxt_pair( "cycle_ival_action"       , ActName::cycle_ival_action       ),
			//	sxt_pair( "cycle_ival_fixed"        , ActName::cycle_ival_fixed        ),
			//	sxt_pair( "cycle_ival_left_closed"  , ActName::cycle_ival_left_closed  ),
			//	sxt_pair( "cycle_ival_left_open"    , ActName::cycle_ival_left_open    ),
			//	sxt_pair( "cycle_ival_right_closed" , ActName::cycle_ival_right_closed ),
			//	sxt_pair( "cycle_ival_right_open"   , ActName::cycle_ival_right_open   ),

				// iter:

			//	sxt_pair( "cycle_iter_inc_dec" , ActName::cycle_iter_inc_dec ),
			//	sxt_pair( "cycle_iter_dec_inc" , ActName::cycle_iter_dec_inc ),
			//	sxt_pair( "cycle_iter_upsize"  , ActName::cycle_iter_upsize  ),
			//	sxt_pair( "cycle_iter_pair"    , ActName::cycle_iter_pair    ),
			//	sxt_pair( "cycle_iter_none"    , ActName::cycle_iter_none    ),
			//	sxt_pair( "cycle_iter_value"   , ActName::cycle_iter_value   ),
			//	sxt_pair( "cycle_iter_void"    , ActName::cycle_iter_void    ),

				// tonic:

			//	sxt_pair( "cycle_tonic_inc_dec" , ActName::cycle_tonic_inc_dec ),
			//	sxt_pair( "cycle_tonic_dec_inc" , ActName::cycle_tonic_dec_inc ),
			//	sxt_pair( "cycle_tonic_pair"    , ActName::cycle_tonic_pair    ),
			//	sxt_pair( "cycle_tonic_none"    , ActName::cycle_tonic_none    ),
			//	sxt_pair( "cycle_tonic_value"   , ActName::cycle_tonic_value   ),
			//	sxt_pair( "cycle_tonic_void"    , ActName::cycle_tonic_void    )
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

		nik_ces auto prod_size		= 8;//cctmp::string_literal("<A|C|M|L>").size();

		nik_ces auto stack_start	= symbol_type{generator::Sign::nonterminal, base::start_index};
		nik_ces auto stack_finish	= symbol_type{generator::Sign::terminal, Token::prompt};

		nik_ces auto stack_size		= 100;//cctmp::literal("F<A|C|M|L>YPZ{}YPZYP,PZV;HGO").size(); // needs refining.
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

// morph:

//	template<auto static_parsed>
//	struct T_chord_assembly_morph
//	{
//		nik_ces auto & parsed		= member_value_U<static_parsed>;
//		nik_ces auto & value		= parsed.morph_level;
//		using type			= modify_type<_from_reference_, decltype(value)>;
//	};

/***********************************************************************************************************************/

// cycle:

//	template<auto static_parsed>
//	struct T_chord_assembly_cycle
//	{
//		nik_ces auto & parsed		= member_value_U<static_parsed>;
//		nik_ces auto & value		= parsed.cycle_level;
//		using type			= modify_type<_from_reference_, decltype(value)>;
//	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace chord

