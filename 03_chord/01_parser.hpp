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

namespace chord {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// action:

/***********************************************************************************************************************/

// name:

	struct ChordAssemblyActionName
	{
		enum : action_type
		{
			nop = generator::AN::nop,

			// main:

				main_name,
				main_arg,
				main_return,

			// label:

				label_delay,
				label_force,

			// goto:

			// tail:

			// declare:

				declare_op,

			// define:

				define_begin,
				define_end,
				define_arg,

			// left:

				left_value,
				left_copy,

			// apply:

				apply_end,

			// assign:

				assign_end,

			// subop:

				subop_value,
				subop_paste,
				subop_quote,

			// subarg:

				subarg_value,
				subarg_paste,
				subarg_quote,

			// mutarg:

				mutarg_value,

			// unit:

				unit_value,
				unit_paste,
				unit_quote,

			// morph:

				// arity:

					mor_arity_value,
					mor_arity_zero,

				// op:

					mor_op_begin,
					mor_op_end,
					mor_op,
					mor_op_range,

				// argpose:

					mor_argpose_value,

				// subpose:

					mor_subpose_value,

				// curry:

					mor_curry_value,
					mor_curry_args,

			// dimension:

				dimension
		};

	}; using CAAN = ChordAssemblyActionName;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// space:

/***********************************************************************************************************************/

// grammar:

	struct T_chord_grammar
	{
		using ActName		= CAAN;
		using T_lexer		= T_chord_lexer;
		using Token		= typename T_lexer::Token;
		nik_ces auto size	= Token::dimension;

		nik_ces auto source() { return generator::context_free_grammar
		(
			// start:

				"Start",

			// assembly:

				"Start -> MainBeg MainArgs MainEnd Block RecBlock ;"

				// main:

					"MainBeg  -> identifier       : main_name   ;"
					"MainEnd  -> \\;                            ;"
					"MainArgs -> MainArg MainArgs               ;"
					"         -> empty                          ;"
					"MainArg  -> identifier       : main_arg    ;"
					"MainRet  -> \\;              : main_return ;"

				// block:

					"Block    -> LabelBeg LabelEnd Instrs               ;"
					"RecBlock -> Block RecBlock                         ;"
					"         -> empty                    : label_force ;"
					"LabelBeg -> label                    : label_delay ;"
					"LabelEnd -> \\;                                    ;"

				// instruction:

					"Instrs      -> Instr RecInstr                                   ;"
					"            -> return UnitVal MainRet                           ;"
					"RecInstr    -> Instr RecInstr                                   ;"
					"            -> GotoBeg GotoVal GotoEnd                          ;"
					"            -> TailBeg TailVal TailEnd                          ;"
					"            -> return UnitVal MainRet                           ;"
					"            -> empty                                            ;"
					"Instr       -> DecBeg DecArg DecArgs DecEnd                     ;"
					"            -> DefBeg DefArg DefArgs DefEnd                     ;"
					"            -> LeftVal RightInstr                               ;"
					"            -> TestInstr BranchInstr                            ;"
					"            -> ! SwapBeg \\= SubOp SubArgs SwapEnd              ;"
					"            -> VoidBeg SubOp SubArgs VoidEnd                    ;"
					"LeftVal     -> identifier                          : left_value ;"
					"            -> .                                   : left_copy  ;"
					"RightInstr  -> ApplyBeg SubOp SubArgs ApplyEnd                  ;"
					"            -> AssignBeg UnitVal AssignEnd                      ;"
					"TestInstr   -> TestBeg SubOp SubArgs TestEnd                    ;"
					"BranchInstr -> BranchBeg BranchVal BranchEnd                    ;"

				// jump:

					"GotoBeg   -> goto       ;" // : goto_begin   ;"
					"GotoVal   -> identifier ;" // : goto_value   ;"
					"GotoEnd   -> \\;        ;" // : goto_end     ;"
					"TailBeg   -> tail       ;" // : tail_begin   ;"
					"TailVal   -> identifier ;" // : tail_value   ;"
					"TailEnd   -> \\;        ;" // : tail_end     ;"
					"BranchBeg -> branch     ;" // : branch_begin ;"
					"BranchVal -> identifier ;" // : branch_value ;"
					"BranchEnd -> \\;        ;" // : branch_end   ;"

				// declare:

					"DecBeg  -> declare                     ;"
					"DecArgs -> DecArg DecArgs              ;"
					"        -> empty                       ;"
					"DecArg  -> identifier     : declare_op ;"
					"DecEnd  -> \\;                         ;"

				// define:

					"DefBeg  -> define         : define_begin ;"
					"DefArgs -> DefArg DefArgs                ;"
					"        -> empty                         ;"
					"DefArg  -> identifier     : define_arg   ;"
					"DefEnd  -> \\;            : define_end   ;"

				// application:

					"SwapBeg  -> identifier ;" // : swap_begin  ;"
					"SwapEnd  -> \\;        ;" // : swap_end    ;"
					"VoidBeg  -> void       ;" // : void_begin  ;"
					"VoidEnd  -> \\;        ;" // : void_end    ;"
					"ApplyBeg -> \\=        ;" // : apply_begin ;" // required still ?
					"ApplyEnd -> \\;              : apply_end   ;"
					"TestBeg  -> test       ;" // : test_begin  ;"
					"TestEnd  -> \\;        ;" // : test_end    ;"

				// assignment:

					"AssignBeg ->   # ;" // : assign_begin ;"
					"AssignEnd -> \\;       : assign_end   ;"

				// argument:

					"SubOp   -> identifier       : subop_value  ;"
					"        -> _                : subop_paste  ;"
					"        -> quote            : subop_quote  ;"
					"SubArgs ->   SubArg SubArgs                ;"
					"        -> ! MutArg SubArgs                ;"
					"        -> empty                           ;"
					"SubArg  -> identifier       : subarg_value ;"
					"        -> _                : subarg_paste ;"
					"        -> quote            : subarg_quote ;"
					"MutArg  -> identifier       : mutarg_value ;"

				// unit:

					"UnitVal -> identifier : unit_value ;"
					"        -> _          : unit_paste ;"
					"        -> quote      : unit_quote ;"
					"        -> Morph                   ;"
				//	"        -> Cycle                   ;"

			// morph:

				"Morph -> argpose MorArity MorOpBeg MorOp    ArgposeVals MorOpEnd ;"
				"      -> subpose MorArity MorOpBeg MorOpRng SubposeVals MorOpEnd ;"
				"      ->   curry MorArity MorOpBeg MorOp      CurryVals MorOpEnd ;"

				// arity:

					"MorArity  -> [ MorNumber ]                   ;"
					"          -> empty         : mor_arity_zero  ;"
					"MorNumber -> number        : mor_arity_value ;"

				// op:

					"MorOpBeg -> {          : mor_op_begin ;"
					"MorOpEnd -> }          : mor_op_end   ;"
					"MorOp    -> identifier : mor_op       ;"
					"         -> *          : mor_op       ;"
					"         -> +          : mor_op       ;"
					"         -> \\-        : mor_op       ;"
					"         -> @          : mor_op       ;"
					"MorOpRng -> MorOp      : mor_op_range ;"

				// argpose:

					"ArgposeVals -> ArgposeVal ArgposeVals                     ;"
					"            -> empty                                      ;"
					"ArgposeVal  -> number                 : mor_argpose_value ;"

				// subpose:

					"SubposeVals -> SubposeVal SubposeVals                     ;"
					"            -> empty                                      ;"
					"SubposeVal  -> identifier             : mor_subpose_value ;"
					"            -> *                      : mor_subpose_value ;"
					"            -> +                      : mor_subpose_value ;"
					"            -> \\-                    : mor_subpose_value ;"
					"            -> @                      : mor_subpose_value ;"

				// curry:

					"CurryVals -> CurryVal CurryVals                   ;"
					"          -> empty              : mor_curry_args  ;"
					"CurryVal  -> identifier         : mor_curry_value ;"

			// cycle:

			//	"Cycle -> repeat MorArity  AMPOpt        LMRIval RepeatIvals ;"
			//	"      -> map    MorArity  AMPOpt LRIval LMRIval    MapIvals ;"
			//	"      -> fold   MorArity CAMPOpt  FIval LMRIval   FoldIvals ;"
			//	"      -> find   MorArity  AMPOpt LRIval LMRIval   FindIvals ;"
			//	"      -> sift   MorArity  AMPOpt LRIval LMRIval   SiftIvals ;"

				// option:

				//	"CAMPOpt -> OptBeg Combine OptCont Action OptCont Mutate OptCont Predicate OptEnd  ;"
				//	"AMPOpt  -> OptBeg Action OptCont Mutate OptCont Predicate OptEnd : cyc_option_amp ;"

				//	"OptCont -> | : cyc_option_cont  ;"
				//	"OptBeg  -> { : cyc_option_begin ;"
				//	"OptEnd  -> } : cyc_option_end   ;"

					// op, val:

					//	"CycOp  -> identifier : cyc_op_value ;"
					//	"CycVal -> identifier : cyc_value    ;"
					//	"       -> @          : cyc_id       ;"
					//	"       -> *          : cyc_deref    ;"

					// combine:

					//	"Combine   -> CycOp  CombRest2                     ;"
					//	"CombRest2 -> CycVal CombRest1                     ;"
					//	"          -> empty            : cyc_combine_rest2 ;"
					//	"CombRest1 -> CycVal                               ;"
					//	"          -> empty            : cyc_combine_rest1 ;"

					// action:

					//	"Action  -> ActOp  ActRest                       ;"
					//	"        -> empty          : cyc_action_defs     ;"
					//	"ActRest -> CycVal ActRest                       ;"
					//	"        -> empty          : cyc_action_rest     ;"
					//	"ActOp   -> identifier     : cyc_action_op_value ;"
					//	"        -> @              : cyc_action_op_id    ;"
					//	"        -> *              : cyc_action_op_deref ;"

					// mutate:

					//	"Mutate   -> CycOp  MutRest2                    ;"
					//	"         -> empty           : cyc_mutate_defs  ;"
					//	"MutRest2 -> CycVal MutRest1                    ;"
					//	"         -> empty           : cyc_mutate_rest2 ;"
					//	"MutRest1 -> CycVal                             ;"
					//	"         -> empty           : cyc_mutate_rest1 ;"

					// predicate:

					//	"Predicate -> CycOp  PredRest2                       ;"
					//	"          -> empty            : cyc_predicate_defs  ;"
					//	"PredRest2 -> CycVal PredRest1                       ;"
					//	"          -> empty            : cyc_predicate_rest2 ;"
					//	"PredRest1 -> CycVal                                 ;"
					//	"          -> empty            : cyc_predicate_rest1 ;"

				// interval:

				//	"LRIval  -> LIval PairIter             RIval ;"
				//	"LMRIval -> LIval PairIter , TonicIter RIval ;"

				//	"LIval -> [     : cyc_ival_left_closed  ;"
				//	"      -> (     : cyc_ival_left_open    ;"
				//	"RIval -> ]     : cyc_ival_right_closed ;"
				//	"      -> )     : cyc_ival_right_open   ;"
				//	"FIval -> < \\> : cyc_ival_fixed        ;"

				//	"Ival ->  FIval ;"
				//	"     -> LRIval ;"

				// iterator:

				//	"PairIter ->   + | \\-          : cyc_iter_inc_dec ;"
				//	"         -> \\- |   +          : cyc_iter_dec_inc ;"
				//	"         -> IterVal | PrevIter : cyc_iter_upsize  ;"
				//	"         -> empty              : cyc_iter_pair    ;"
				//	"PrevIter -> IterVal                               ;"
				//	"         -> ~                  : cyc_iter_none    ;"
				//	"IterVal  -> identifier         : cyc_iter_value   ;"
				//	"         -> ^ VoidVal                             ;"
				//	"VoidVal  -> identifier         : cyc_iter_void    ;"

				// tonic:

				//	"TonicIter ->   + | \\-            : cyc_tonic_inc_dec ;"
				//	"          -> \\- |   +            : cyc_tonic_dec_inc ;"
				//	"          -> TonicVal | PrevTonic                     ;"
				//	"          -> empty                : cyc_tonic_pair    ;"
				//	"PrevTonic -> TonicVal                                 ;"
				//	"          -> ~                    : cyc_tonic_none    ;"
				//	"TonicVal  -> identifier           : cyc_tonic_value   ;"
				//	"          -> ^ VoidTonic                              ;"
				//	"VoidTonic -> identifier           : cyc_tonic_void    ;"

				// (accept):

				//	"RepeatIvals -> FIval RepeatIvals  ;"
				//	"            -> empty : cyc_repeat ;"
				//	"MapIvals    -> Ival MapIvals      ;"
				//	"            -> empty : cyc_map    ;"
				//	"FoldIvals   -> Ival FoldIvals     ;"
				//	"            -> empty : cyc_fold   ;"
				//	"FindIvals   -> Ival FindIvals     ;"
				//	"            -> empty : cyc_find   ;"
				//	"SiftIvals   -> Ival SiftIvals     ;"
				//	"            -> empty : cyc_sift   ;"
		);}

		nik_ces auto map = cctmp::table
		(
			U_strlit_type, U_token_type,

			sxt_pair( " "          , Token::invalid    ),
			sxt_pair( "$"          , Token::prompt     ),
			sxt_pair( "identifier" , Token::identifier ),
			sxt_pair( "number"     , Token::number     ),
			sxt_pair( "declare"    , Token::declare    ),
			sxt_pair( "define"     , Token::define     ),
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

			// generic:

				// main:

					sxa_pair( "main_name"   , ActName::main_name   ),
					sxa_pair( "main_arg"    , ActName::main_arg    ),
					sxa_pair( "main_return" , ActName::main_return ),

				// label:

					sxa_pair( "label_delay" , ActName::label_delay ),
					sxa_pair( "label_force" , ActName::label_force ),

				// goto:

				//	sxa_pair( "goto_begin" , ActName::goto_begin ),
				//	sxa_pair( "goto_value" , ActName::goto_value ),
				//	sxa_pair( "goto_end"   , ActName::goto_end   ),

				// tail:

				//	sxa_pair( "tail_begin" , ActName::tail_begin ),
				//	sxa_pair( "tail_value" , ActName::tail_value ),
				//	sxa_pair( "tail_end"   , ActName::tail_end   ),

				// declare:

					sxa_pair( "declare_op" , ActName::declare_op ),

				// define:

					sxa_pair( "define_begin" , ActName::define_begin ),
					sxa_pair( "define_end"   , ActName::define_end   ),
					sxa_pair( "define_arg"   , ActName::define_arg   ),

				// left:

					sxa_pair( "left_value" , ActName::left_value ),
					sxa_pair( "left_copy"  , ActName::left_copy  ),

				// apply:

					sxa_pair( "apply_end" , ActName::apply_end ),

				// assign:

					sxa_pair( "assign_end" , ActName::assign_end ),

				// subop:

					sxa_pair( "subop_value" , ActName::subop_value ),
					sxa_pair( "subop_paste" , ActName::subop_paste ),
					sxa_pair( "subop_quote" , ActName::subop_quote ),

				// subarg:

					sxa_pair( "subarg_value" , ActName::subarg_value ),
					sxa_pair( "subarg_paste" , ActName::subarg_paste ),
					sxa_pair( "subarg_quote" , ActName::subarg_quote ),

				// mutarg:

					sxa_pair( "mutarg_value" , ActName::mutarg_value ),

				// unit:

					sxa_pair( "unit_value" , ActName::unit_value ),
					sxa_pair( "unit_paste" , ActName::unit_paste ),
					sxa_pair( "unit_quote" , ActName::unit_quote ),

			// morph:

				// arity:

					sxt_pair( "mor_arity_value" , ActName::mor_arity_value ),
					sxt_pair( "mor_arity_zero"  , ActName::mor_arity_zero  ),

				// op:

					sxt_pair( "mor_op_begin" , ActName::mor_op_begin ),
					sxt_pair( "mor_op_end"   , ActName::mor_op_end   ),
					sxt_pair( "mor_op"       , ActName::mor_op       ),
					sxt_pair( "mor_op_range" , ActName::mor_op_range ),

				// argpose:

					sxt_pair( "mor_argpose_value" , ActName::mor_argpose_value ),

				// subpose:

					sxt_pair( "mor_subpose_value" , ActName::mor_subpose_value ),

				// curry:

					sxt_pair( "mor_curry_value" , ActName::mor_curry_value ),
					sxt_pair( "mor_curry_args"  , ActName::mor_curry_args  )//,

			// cycle:

				// option:

				//	sxt_pair( "cyc_option_begin" , ActName::cyc_option_begin ),
				//	sxt_pair( "cyc_option_end"   , ActName::cyc_option_end   ),
				//	sxt_pair( "cyc_option_amp"   , ActName::cyc_option_amp   ),
				//	sxt_pair( "cyc_option_cont"  , ActName::cyc_option_cont  ),

				// op, val:

				//	sxt_pair( "cyc_op_value" , ActName::cyc_op_value ),
				//	sxt_pair( "cyc_value"    , ActName::cyc_value    ),
				//	sxt_pair( "cyc_id"       , ActName::cyc_id       ),
				//	sxt_pair( "cyc_deref"    , ActName::cyc_deref    ),

				// combine:

				//	sxt_pair( "cyc_combine_rest2" , ActName::cyc_combine_rest2 ),
				//	sxt_pair( "cyc_combine_rest1" , ActName::cyc_combine_rest1 ),

				// action:

				//	sxt_pair( "cyc_action_defs"     , ActName::cyc_action_defs     ),
				//	sxt_pair( "cyc_action_rest"     , ActName::cyc_action_rest     ),
				//	sxt_pair( "cyc_action_op_value" , ActName::cyc_action_op_value ),
				//	sxt_pair( "cyc_action_op_id"    , ActName::cyc_action_op_id    ),
				//	sxt_pair( "cyc_action_op_deref" , ActName::cyc_action_op_deref ),

				// mutate:

				//	sxt_pair( "cyc_mutate_defs"  , ActName::cyc_mutate_defs  ),
				//	sxt_pair( "cyc_mutate_rest2" , ActName::cyc_mutate_rest2 ),
				//	sxt_pair( "cyc_mutate_rest1" , ActName::cyc_mutate_rest1 ),

				// predicate:

				//	sxt_pair( "cyc_predicate_defs"  , ActName::cyc_predicate_defs  ),
				//	sxt_pair( "cyc_predicate_rest2" , ActName::cyc_predicate_rest2 ),
				//	sxt_pair( "cyc_predicate_rest1" , ActName::cyc_predicate_rest1 ),

				// interval:

				//	sxt_pair( "cyc_ival_left_closed"  , ActName::cyc_ival_left_closed  ),
				//	sxt_pair( "cyc_ival_left_open"    , ActName::cyc_ival_left_open    ),
				//	sxt_pair( "cyc_ival_right_closed" , ActName::cyc_ival_right_closed ),
				//	sxt_pair( "cyc_ival_right_open"   , ActName::cyc_ival_right_open   ),
				//	sxt_pair( "cyc_ival_fixed"        , ActName::cyc_ival_fixed        ),

				// iterator:

				//	sxt_pair( "cyc_iter_inc_dec" , ActName::cyc_iter_inc_dec ),
				//	sxt_pair( "cyc_iter_dec_inc" , ActName::cyc_iter_dec_inc ),
				//	sxt_pair( "cyc_iter_upsize"  , ActName::cyc_iter_upsize  ),
				//	sxt_pair( "cyc_iter_pair"    , ActName::cyc_iter_pair    ),
				//	sxt_pair( "cyc_iter_none"    , ActName::cyc_iter_none    ),
				//	sxt_pair( "cyc_iter_value"   , ActName::cyc_iter_value   ),
				//	sxt_pair( "cyc_iter_void"    , ActName::cyc_iter_void    ),

				// tonic:

				//	sxt_pair( "cyc_tonic_inc_dec" , ActName::cyc_tonic_inc_dec ),
				//	sxt_pair( "cyc_tonic_dec_inc" , ActName::cyc_tonic_dec_inc ),
				//	sxt_pair( "cyc_tonic_pair"    , ActName::cyc_tonic_pair    ),
				//	sxt_pair( "cyc_tonic_none"    , ActName::cyc_tonic_none    ),
				//	sxt_pair( "cyc_tonic_value"   , ActName::cyc_tonic_value   ),
				//	sxt_pair( "cyc_tonic_void"    , ActName::cyc_tonic_void    ),

				// (accept):

				//	sxt_pair( "cyc_repeat" , ActName::cyc_repeat ),
				//	sxt_pair( "cyc_map"    , ActName::cyc_map    ),
				//	sxt_pair( "cyc_fold"   , ActName::cyc_fold   ),
				//	sxt_pair( "cyc_find"   , ActName::cyc_find   ),
				//	sxt_pair( "cyc_sift"   , ActName::cyc_sift   )
		);
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// pushdown automaton:

/***********************************************************************************************************************/

// interface:

#ifdef NIK_CHORD_PARSER
#include NIK_CHORD_OBJ
#else

	template<typename T_grammar>
	struct T_chord_pda : public generator::T_generic_pda<T_grammar>
	{
		using base			= generator::T_generic_pda<T_grammar>;
		using ActName			= typename T_grammar::ActName;
		using T_lexer			= typename T_grammar::T_lexer;
		using Token			= typename T_grammar::Token;

		nik_ces auto prod_size		= cctmp::string_literal("!B=OAE").size(); // needs refining.
	//	nik_ces auto prod_size		= cctmp::string_literal("{C|A|M|P}").size(); // needs refining.

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
	struct T_chord_parser
	{
		using T_ast		= typename T_action::T_ast;
		using T_pda		= T_chord_pda<T_grammar>;
		using T_parser		= generator::T_generic_parser<T_action, T_pda>;
		using parseme_type	= generator::T_parseme<T_ast>;
		using parsoid_type	= generator::T_parsoid<T_pda::stack_size, T_pda::prod_size>;

		nik_ces auto & pda	= T_parser::pda; static_assert(!pda.ambiguous, "ambiguous cfg!");

		parseme_type parseme;
		parsoid_type parsoid;

		nik_ce T_chord_parser(const cselector<char> & s) :

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

	template<action_type, auto...> struct T_chord_translation_action;

	template<typename AST>
	struct T_chord_ta :
		public generator::T_generic_translation_action<T_chord_translation_action, AST, CAAN>
			{ };

	// interface:

		template<typename AST>
		struct T_chord_action
		{
			using T_ast		= AST;

			nik_ces auto value	= T_chord_ta<AST>{};
			using type		= decltype(value);
		};

/***********************************************************************************************************************/

// tree:

	template<auto... Vs> 
	struct T_chord_syntax_tree : public assembly::T_syntax_tree<Vs...>
	{
		using base		= assembly::T_syntax_tree<Vs...>;
		using size_type		= typename base::size_type;
		using csize_type	= typename base::csize_type;

		nik_ce T_chord_syntax_tree() : base{} { }

		// label:

			// add in label tracking/resolution here.
	};

/***********************************************************************************************************************/

// interface:

	template
	<
		auto static_pg_parsed, auto static_source, auto static_env_lookup,
		auto contr_size, auto stack_size, auto model_size
	>
	struct T_chord_parsed
	{
		using T_ast			= T_chord_syntax_tree
						<
							static_source, static_env_lookup,
							contr_size, stack_size, model_size
						>;
		using T_action			= T_chord_action<T_ast>;
		using T_grammar			= T_chord_grammar;
		using T_parser			= T_chord_parser<static_pg_parsed, T_action, T_grammar>;

		nik_ces auto & src		= member_value_U<static_source>;
		nik_ces auto parser		= T_parser{src.cselect()};
		nik_ces auto & value		= parser.parseme.tree;
		using type			= modify_type<_from_reference_, decltype(value)>;
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace chord

