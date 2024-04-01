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

			// param:

				param_type,

			// main:

				main_name,
				main_begin,
				main_end,
				main_arg,
				main_return,

			// port:

				op_port_lookup,
				port_deduce,
				port_lookup,

			// label:

				label_value,

			// jump:

				goto_delay,
				branch_delay,

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

			// side:

				side_begin,

			// swap:

				swap_begin,
				swap_value,

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

			// literal:

				literal_n_number,
				literal_r_number,

			// compound:

				// arity:

					pound_arity_value,
					pound_arity_zero,

			// morph:

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

			// cycle:

				// routine:

					cyc_rout_begin,
					cyc_rout_end,
					cyc_rout_op,
					cyc_rout_value,

				// combine:

					cyc_combine,
					cyc_combine_rest2,
					cyc_combine_rest1,

				// action:

					cyc_action,
					cyc_action_defs,
					cyc_action_rest,

				// mutate:

					cyc_mutate,
					cyc_mutate_defs,
					cyc_mutate_rest2,
					cyc_mutate_rest1,

				// predicate:

					cyc_predicate,
					cyc_predicate_defs,
					cyc_predicate_rest2,
					cyc_predicate_rest1,

				// interval:

					cyc_ival_fixed,
					cyc_ival_left_closed,
					cyc_ival_left_open,
					cyc_ival_init_closed,
					cyc_ival_init_open,
					cyc_ival_root_closed,
					cyc_ival_root_open,
					cyc_ival_rest_closed,
					cyc_ival_rest_open,

					cyc_ival_repeat,
					cyc_ival_map,
					cyc_ival_fold,
					cyc_ival_find,
					cyc_ival_sift,

				// note (iterator):

					cyc_note_inc_dec,
					cyc_note_dec_inc,
					cyc_note_defs,
					cyc_note_value,
					cyc_note_void,
					cyc_note_none,

				// tonic (iterator):

					cyc_tonic_inc_dec,
					cyc_tonic_dec_inc,
					cyc_tonic_defs,
					cyc_tonic_value,
					cyc_tonic_void,
					cyc_tonic_none,

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

				"Start  -> type Param Params \\; Main Body              ;"
				"       -> Main Body                                    ;"
				"Params -> Param Params                                 ;"
				"       -> empty                                        ;"
				"Param  -> identifier                      : param_type ;"

				// main:

					"Main     -> MainBeg MainArgs OpType MainEnd               ;"
					"MainBeg  -> identifier                      : main_name   ;"
					"MainEnd  -> \\;                                           ;"
					"MainArgs -> MainArg MainArgs                              ;"
					"         -> empty                                         ;"
					"MainArg  -> identifier                      : main_arg    ;"
					"MainRet  -> \\;                             : main_return ;"

					"OpType -> \\-\\> OpPort                  ;"
					"       -> empty                          ;"
					"OpPort -> identifier    : op_port_lookup ;"

				// body:

					"Body -> Block RecBlock : main_begin ;"

				// block:

					"Block    -> LabelBeg LabelEnd Instrs               ;"
					"RecBlock -> Block RecBlock                         ;"
					"         -> empty                    : main_end    ;"
					"LabelBeg -> label                    : label_value ;"
					"LabelEnd -> \\;                                    ;"

				// instruction:

					"Instrs      -> Instr RecInstr                                   ;"
					"            -> return UnitVal MainRet                           ;"
					"RecInstr    -> Instr RecInstr                                   ;"
					"            -> GotoBeg GotoVal GotoEnd                          ;"
					"            -> return UnitVal MainRet                           ;"
					"            -> empty                                            ;"
					"Instr       -> DecBeg DecArg DecArgs DecEnd                     ;"
					"            -> DefBeg DefArg DefArgs DefEnd                     ;"
					"            -> LeftVal RightInstr                               ;"
					"            -> TestInstr BranchInstr                            ;"
					"            -> ! SwapBeg \\= SubOp SwapArg SubArgs SwapEnd      ;"
					"            -> VoidBeg SubOp SubArgs VoidEnd                    ;"
					"LeftVal     -> identifier                          : left_value ;"
					"            -> .                                   : left_copy  ;"
					"RightInstr  -> ApplyBeg SubOp SubArgs ApplyEnd                  ;"
					"            -> AssignBeg UnitVal AssignEnd                      ;"
					"TestInstr   -> TestBeg SubOp SubArgs TestEnd                    ;"
					"BranchInstr -> BranchBeg BranchVal BranchEnd                    ;"

				// jump:

					"GotoBeg   -> goto                      ;"
					"GotoVal   -> identifier : goto_delay   ;"
					"GotoEnd   -> \\;                       ;"
					"BranchBeg -> branch                    ;"
					"BranchVal -> identifier : branch_delay ;"
					"BranchEnd -> \\;                       ;"

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

					"SwapBeg  -> identifier : swap_begin ;"
					"SwapArg  -> empty      : swap_value ;"
					"SwapEnd  -> \\;        : apply_end  ;"
					"VoidBeg  -> void       : side_begin ;"
					"VoidEnd  -> \\;        : apply_end  ;"
					"ApplyBeg -> \\=                     ;"
					"ApplyEnd -> \\;        : apply_end  ;"
					"TestBeg  -> test       : left_copy  ;"
					"TestEnd  -> \\;        : apply_end  ;"

				// assignment:

					"AssignBeg ->   #              ;"
					"AssignEnd -> \\; : assign_end ;"

				// argument:

					"SubOp   -> identifier       : subop_value  ;"
					"        -> _                : subop_paste  ;"
					"        -> quote            : subop_quote  ;"
					"SubArgs ->   SubArg SubArgs                ;"
					"        -> ! MutArg SubArgs                ;"
					"        -> empty                           ;"
					"SubArg  -> Literal                         ;"
					"        -> identifier       : subarg_value ;"
					"        -> _                : subarg_paste ;"
					"        -> quote            : subarg_quote ;"
					"MutArg  -> identifier       : mutarg_value ;"

				// unit:

					"UnitVal -> Literal                 ;"
					"        -> identifier : unit_value ;"
					"        -> _          : unit_paste ;"
					"        -> quote      : unit_quote ;"
					"        -> Morph                   ;"
					"        -> Cycle                   ;"

				// literal:

					"Literal -> Value Type                  ;"
					"Value   -> n_number : literal_n_number ;"
					"        -> r_number : literal_r_number ;"

					"Type -> \\: Port                 ;"
					"     -> empty      : port_deduce ;"
					"Port -> identifier : port_lookup ;"

			// compound:

				// arity:

					"Arity  -> [ Number ]                     ;"
					"       -> empty      : pound_arity_zero  ;"
					"Number -> n_number   : pound_arity_value ;"

			// morph:

				"Morph -> argpose Arity MorOpBeg MorOp    ArgposeVals MorOpEnd ;"
				"      -> subpose Arity MorOpBeg MorOpRng SubposeVals MorOpEnd ;"
				"      ->   curry Arity MorOpBeg MorOp      CurryVals MorOpEnd ;"

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
					"ArgposeVal  -> n_number               : mor_argpose_value ;"

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

				"Cycle -> repeat Arity  AMP         LRMIval RepeatIvals ;"
				"      -> map    Arity  AMP LRLIval LRMIval    MapIvals ;"
				"      -> fold   Arity CAMP   FIval LRMIval   FoldIvals ;"
				"      -> find   Arity  AMP   FIval LRMIval   FindIvals ;"
				"      -> sift   Arity  AMP   FIval LRMIval   SiftIvals ;"

				// routine:

					"CAMP -> CRBeg Combine CRBar Action CRBar Mutate CRBar Predicate CREnd ;"
					"AMP  -> CRBeg               Action CRBar Mutate CRBar Predicate CREnd ;"

					"CRBeg -> { : cyc_rout_begin ;"
					"CRBar -> | : cyc_rout_end   ;"
					"CREnd -> } : cyc_rout_end   ;"

					"CRMinOp -> identifier : cyc_rout_op    ;"
					"        -> *          : cyc_rout_op    ;"
					"        -> @          : cyc_rout_op    ;"
					"CROp    -> CRMinOp                     ;"
					"        -> +          : cyc_rout_op    ;"
					"        -> \\-        : cyc_rout_op    ;"
					"CRVal   -> identifier : cyc_rout_value ;"
					"        -> *          : cyc_rout_value ;"
					"        -> @          : cyc_rout_value ;"

					// combine:

						"Combine   -> CROp  CombRest2 : cyc_combine       ;"
						"CombRest2 -> CRVal CombRest1                     ;"
						"          -> empty           : cyc_combine_rest2 ;"
						"CombRest1 -> CRVal                               ;"
						"          -> empty           : cyc_combine_rest1 ;"

					// action:

						"Action  -> CRMinOp ActRest : cyc_action      ;"
						"        -> empty           : cyc_action_defs ;"
						"ActRest -> CRVal   ActRest                   ;"
						"        -> empty           : cyc_action_rest ;"

					// mutate:

						"Mutate   -> CROp  MutRest2 : cyc_mutate       ;"
						"         -> empty          : cyc_mutate_defs  ;"
						"MutRest2 -> CRVal MutRest1                    ;"
						"         -> empty          : cyc_mutate_rest2 ;"
						"MutRest1 -> CRVal                             ;"
						"         -> empty          : cyc_mutate_rest1 ;"

					// predicate:

						"Predicate -> CROp  PredRest2 : cyc_predicate       ;"
						"          -> empty           : cyc_predicate_defs  ;"
						"PredRest2 -> CRVal PredRest1                       ;"
						"          -> empty           : cyc_predicate_rest2 ;"
						"PredRest1 -> CRVal                                 ;"
						"          -> empty           : cyc_predicate_rest1 ;"

				// interval:

					"LRLIval -> LIval NoteIter             RLIval ;"
					"LRMIval -> LIval NoteIter , TonicIter RMIval ;"
					"LRRIval -> LIval NoteIter             RRIval ;"

					"FIval  -> < \\> : cyc_ival_fixed       ;"
					"LIval  -> [     : cyc_ival_left_closed ;"
					"       -> (     : cyc_ival_left_open   ;"
					"RLIval -> ]     : cyc_ival_init_closed ;"
					"       -> )     : cyc_ival_init_open   ;"
					"RMIval -> ]     : cyc_ival_root_closed ;"
					"       -> )     : cyc_ival_root_open   ;"
					"RRIval -> ]     : cyc_ival_rest_closed ;"
					"       -> )     : cyc_ival_rest_open   ;"

					"RepeatIvals -> FIval RepeatIvals                   ;"
					"            -> empty             : cyc_ival_repeat ;"
					"MapIvals    -> Ival MapIvals                       ;"
					"            -> empty             : cyc_ival_map    ;"
					"FoldIvals   -> Ival FoldIvals                      ;"
					"            -> empty             : cyc_ival_fold   ;"
					"FindIvals   -> Ival FindIvals                      ;"
					"            -> empty             : cyc_ival_find   ;"
					"SiftIvals   -> Ival SiftIvals                      ;"
					"            -> empty             : cyc_ival_sift   ;"

					"Ival ->   FIval ;"
					"     -> LRRIval ;"

				// note (iterator):

					"NoteIter ->   + | \\-           : cyc_note_inc_dec ;"
					"         -> \\- |   +           : cyc_note_dec_inc ;"
					"         -> NoteNext | NotePrev                    ;"
					"         -> empty               : cyc_note_defs    ;"
					"NoteNext -> identifier          : cyc_note_value   ;"
					"         -> ^ NoteVoid                             ;"
					"NoteVoid -> identifier          : cyc_note_void    ;"
					"NotePrev -> NoteNext                               ;"
					"         -> ~                   : cyc_note_none    ;"

				// tonic (iterator):

					"TonicIter ->   + | \\-             : cyc_tonic_inc_dec ;"
					"          -> \\- |   +             : cyc_tonic_dec_inc ;"
					"          -> TonicNext | TonicPrev                     ;"
					"          -> empty                 : cyc_tonic_defs    ;"
					"TonicNext -> identifier            : cyc_tonic_value   ;"
					"          -> ^ TonicVoid                               ;"
					"TonicVoid -> identifier            : cyc_tonic_void    ;"
					"TonicPrev -> TonicNext                                 ;"
					"          -> ~                     : cyc_tonic_none    ;"
		);}

		nik_ces auto map = cctmp::table
		(
			U_strlit_type, U_token_type,

			sxt_pair( " "          , Token::invalid    ),
			sxt_pair( "$"          , Token::prompt     ),
			sxt_pair( "\\-\\>"     , Token::op_type    ),
			sxt_pair( "\\:"        , Token::arg_type   ),

			sxt_pair( "type"       , Token::type       ),
			sxt_pair( "identifier" , Token::identifier ),
			sxt_pair( "n_number"   , Token::n_number   ),
			sxt_pair( "r_number"   , Token::r_number   ),
			sxt_pair( "declare"    , Token::declare    ),
			sxt_pair( "define"     , Token::define     ),
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

				// param:

					sxa_pair( "param_type" , ActName::param_type ),

				// main:

					sxa_pair( "main_name"   , ActName::main_name   ),
					sxa_pair( "main_begin"  , ActName::main_begin  ),
					sxa_pair( "main_end"    , ActName::main_end    ),
					sxa_pair( "main_arg"    , ActName::main_arg    ),
					sxa_pair( "main_return" , ActName::main_return ),

				// port:

					sxa_pair( "op_port_lookup" , ActName::op_port_lookup ),
					sxa_pair( "port_deduce"    , ActName::port_deduce    ),
					sxa_pair( "port_lookup"    , ActName::port_lookup    ),

				// label:

					sxa_pair( "label_value" , ActName::label_value ),

				// jump:

					sxa_pair( "goto_delay"   , ActName::goto_delay   ),
					sxa_pair( "branch_delay" , ActName::branch_delay ),

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

					sxa_pair( "apply_end"  , ActName::apply_end  ),

				// side:

					sxa_pair( "side_begin" , ActName::side_begin ),

				// swap:

					sxa_pair( "swap_begin" , ActName::swap_begin ),
					sxa_pair( "swap_value" , ActName::swap_value ),

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

				// literal:

					sxa_pair( "literal_n_number" , ActName::literal_n_number ),
					sxa_pair( "literal_r_number" , ActName::literal_r_number ),

			// compound:

				// arity:

					sxt_pair( "pound_arity_value" , ActName::pound_arity_value ),
					sxt_pair( "pound_arity_zero"  , ActName::pound_arity_zero  ),

			// morph:

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
					sxt_pair( "mor_curry_args"  , ActName::mor_curry_args  ),

			// cycle:

				// routine:

					sxt_pair( "cyc_rout_begin" , ActName::cyc_rout_begin ),
					sxt_pair( "cyc_rout_end"   , ActName::cyc_rout_end   ),
					sxt_pair( "cyc_rout_op"    , ActName::cyc_rout_op    ),
					sxt_pair( "cyc_rout_value" , ActName::cyc_rout_value ),

				// combine:

					sxt_pair( "cyc_combine"       , ActName::cyc_combine       ),
					sxt_pair( "cyc_combine_rest2" , ActName::cyc_combine_rest2 ),
					sxt_pair( "cyc_combine_rest1" , ActName::cyc_combine_rest1 ),

				// action:

					sxt_pair( "cyc_action"      , ActName::cyc_action      ),
					sxt_pair( "cyc_action_defs" , ActName::cyc_action_defs ),
					sxt_pair( "cyc_action_rest" , ActName::cyc_action_rest ),

				// mutate:

					sxt_pair( "cyc_mutate"       , ActName::cyc_mutate       ),
					sxt_pair( "cyc_mutate_defs"  , ActName::cyc_mutate_defs  ),
					sxt_pair( "cyc_mutate_rest2" , ActName::cyc_mutate_rest2 ),
					sxt_pair( "cyc_mutate_rest1" , ActName::cyc_mutate_rest1 ),

				// predicate:

					sxt_pair( "cyc_predicate"       , ActName::cyc_predicate       ),
					sxt_pair( "cyc_predicate_defs"  , ActName::cyc_predicate_defs  ),
					sxt_pair( "cyc_predicate_rest2" , ActName::cyc_predicate_rest2 ),
					sxt_pair( "cyc_predicate_rest1" , ActName::cyc_predicate_rest1 ),

				// interval:

					sxt_pair( "cyc_ival_fixed"       , ActName::cyc_ival_fixed       ),
					sxt_pair( "cyc_ival_left_closed" , ActName::cyc_ival_left_closed ),
					sxt_pair( "cyc_ival_left_open"   , ActName::cyc_ival_left_open   ),
					sxt_pair( "cyc_ival_init_closed" , ActName::cyc_ival_init_closed ),
					sxt_pair( "cyc_ival_init_open"   , ActName::cyc_ival_init_open   ),
					sxt_pair( "cyc_ival_root_closed" , ActName::cyc_ival_root_closed ),
					sxt_pair( "cyc_ival_root_open"   , ActName::cyc_ival_root_open   ),
					sxt_pair( "cyc_ival_rest_closed" , ActName::cyc_ival_rest_closed ),
					sxt_pair( "cyc_ival_rest_open"   , ActName::cyc_ival_rest_open   ),

					sxt_pair( "cyc_ival_repeat" , ActName::cyc_ival_repeat ),
					sxt_pair( "cyc_ival_map"    , ActName::cyc_ival_map    ),
					sxt_pair( "cyc_ival_fold"   , ActName::cyc_ival_fold   ),
					sxt_pair( "cyc_ival_find"   , ActName::cyc_ival_find   ),
					sxt_pair( "cyc_ival_sift"   , ActName::cyc_ival_sift   ),

				// note (iterator):

					sxt_pair( "cyc_note_inc_dec" , ActName::cyc_note_inc_dec ),
					sxt_pair( "cyc_note_dec_inc" , ActName::cyc_note_dec_inc ),
					sxt_pair( "cyc_note_defs"    , ActName::cyc_note_defs    ),
					sxt_pair( "cyc_note_value"   , ActName::cyc_note_value   ),
					sxt_pair( "cyc_note_void"    , ActName::cyc_note_void    ),
					sxt_pair( "cyc_note_none"    , ActName::cyc_note_none    ),

				// tonic (iterator):

					sxt_pair( "cyc_tonic_inc_dec" , ActName::cyc_tonic_inc_dec ),
					sxt_pair( "cyc_tonic_dec_inc" , ActName::cyc_tonic_dec_inc ),
					sxt_pair( "cyc_tonic_defs"    , ActName::cyc_tonic_defs    ),
					sxt_pair( "cyc_tonic_value"   , ActName::cyc_tonic_value   ),
					sxt_pair( "cyc_tonic_void"    , ActName::cyc_tonic_void    ),
					sxt_pair( "cyc_tonic_none"    , ActName::cyc_tonic_none    )
		);
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace chord

