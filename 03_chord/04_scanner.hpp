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

// scanner:

namespace chord {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// cctmp:

	template<auto Op, typename T>
	using modify_type					= cctmp::modify_type<Op, T>;

	nik_ce auto _from_reference_				= cctmp::_from_reference_;

	using strlit_type					= cctmp::strlit_type;
	nik_ce auto U_strlit_type				= cctmp::U_strlit_type;

	template<typename T, auto S>
	using sequence						= cctmp::sequence<T, S>;

// generator:

	nik_ce auto U_action_type				= generator::U_action_type;

	using sxt_pair						= cctmp::pair<strlit_type, token_type>;
	using sxa_pair						= cctmp::pair<strlit_type, action_type>;

	using symbol_type					= generator::symbol_type;
	using csymbol_type					= generator::csymbol_type;

// machine:

	template<auto... Vs>
	using T_lookup_action					= machine::T_lookup_action<Vs...>;

	template<auto... Vs>
	using T_chain_action					= machine::T_chain_action<Vs...>;

	template<auto... Vs>
	nik_ce auto chain_offset				= machine::chain_offset<Vs...>;

	template<auto... Vs>
	using T_cycle_action					= machine::T_cycle_action<Vs...>;

	template<auto... Vs>
	using T_assembly_action					= machine::T_assembly_action<Vs...>;

	template<auto... Vs>
	nik_ce auto assembly_offset				= machine::assembly_offset<Vs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// space:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// tree (table of contents):

/***********************************************************************************************************************/

// interface:

	struct T_chord_assembly_scanner_ast
	{
		struct Local { enum : gkey_type { offset, dimension }; };

		struct Global
		{
			enum : gkey_type { arg, pad, tag, jump, label, assembly, call, offset, total, dimension };
		};

		using local_seq  = sequence<gindex_type, gindex_type{Local::dimension}>;
		using global_seq = sequence<gindex_type, gindex_type{Global::dimension}>;
		using csize_type = typename global_seq::csize_type;

		local_seq local;
		global_seq global;

		nik_ce T_chord_assembly_scanner_ast()
		{
			local.fullsize();
			global.fullsize();
		}

		nik_ce auto max_call_size    () const { return 2; }
		nik_ce auto max_replace_size () const { return assembly_offset<AAN::replace, AAT::id>; }
		nik_ce auto max_value_size   () const { return chain_offset<CAN::non, CAT::lookup>; }

		nik_ce void increment_local  (csize_type pos, csize_type num = 1) { local  [pos] += num; }
		nik_ce void increment_global (csize_type pos, csize_type num = 1) { global [pos] += num; }

		nik_ce void update_offset()
		{
			gindex_type & loffset = local[Local::offset];
			gindex_type & goffset = global[Global::offset];

			if (loffset > goffset) goffset = loffset;
			loffset = 0;
		}

		nik_ce void update_accept()
		{
			global[Global::arg     ] += global[Global::pad];
			global[Global::tag     ]  = global[Global::label] + global[Global::jump];

			global[Global::offset  ] += chain_offset< CAN::begin, CAT::id >;
			global[Global::offset  ] += chain_offset< CAN::end  , CAT::id >;

			global[Global::assembly] += assembly_offset< AAN::begin , AAT::id >;
			global[Global::assembly] += assembly_offset< AAN::pad   , AAT::id >;
			global[Global::assembly] += assembly_offset< AAN::end   , AAT::id >;

			global[Global::total   ]  = global[Global::assembly];
			global[Global::total   ] += global[Global::call] * global[Global::offset];
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// action:

	template<action_type, auto...> struct T_chord_assembly_scanner_translation_action;

/***********************************************************************************************************************/

// name:

	struct ChordAssemblyScannerActionName
	{
		enum : action_type
		{
			nop = generator::AN::nop,

			// asm:

				asm_accept,
				asm_func_arg,
				asm_label, asm_label_goto,
				asm_unit,
				asm_jump,
				asm_left,
				asm_swap,
				asm_apply,
				asm_sub_value, asm_sub_paste, asm_sub_quote, asm_sub_end,

			// morph:

				// op value:

					mor_op_arity, mor_op_value, mor_op_id, mor_op_deref, mor_op_inc, mor_op_dec,

				// argpose:

					mor_argpose_begin, mor_argpose_end, mor_argpose_value,

				// subpose:

					mor_subpose_begin, mor_subpose_end, mor_subpose_value,
					mor_subpose_id, mor_subpose_deref, mor_subpose_inc, mor_subpose_dec,

				// curry:

					mor_curry_begin, mor_curry_end, mor_curry_value,

			// dimension:

				dimension
		};

	}; using CASAN = ChordAssemblyScannerActionName;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// nop:

/***********************************************************************************************************************/

	template<auto... filler>
	struct T_chord_assembly_scanner_translation_action<CASAN::nop, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l) { }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// asm:

/***********************************************************************************************************************/

// accept:

	template<auto... filler>
	struct T_chord_assembly_scanner_translation_action<CASAN::asm_accept, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->update_accept(); }
	};

// function:

	template<auto... filler>
	struct T_chord_assembly_scanner_translation_action<CASAN::asm_func_arg, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->increment_global(AST::Global::arg); }
	};

// label:

	template<auto... filler>
	struct T_chord_assembly_scanner_translation_action<CASAN::asm_label, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->increment_global(AST::Global::label); }
	};

	template<auto... filler>
	struct T_chord_assembly_scanner_translation_action<CASAN::asm_label_goto, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->increment_global(AST::Global::jump);
			t->increment_global(AST::Global::assembly);

			t->increment_global(AST::Global::label);
		}
	};

// unit:

	template<auto... filler>
	struct T_chord_assembly_scanner_translation_action<CASAN::asm_unit, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->increment_global(AST::Global::call);
			t->increment_global(AST::Global::assembly, t->max_call_size());

			t->increment_global(AST::Global::call);
			t->increment_local(AST::Local::offset, t->max_value_size());
			t->update_offset();
		}
	};

// jump:

	template<auto... filler>
	struct T_chord_assembly_scanner_translation_action<CASAN::asm_jump, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->increment_global(AST::Global::jump);
			t->increment_global(AST::Global::assembly);
		}
	};

// left:

	template<auto... filler>
	struct T_chord_assembly_scanner_translation_action<CASAN::asm_left, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->increment_global(AST::Global::pad);
			t->increment_global(AST::Global::assembly, t->max_replace_size());
		}
	};

// swap:

	template<auto... filler>
	struct T_chord_assembly_scanner_translation_action<CASAN::asm_swap, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->increment_global(AST::Global::call);
			t->increment_global(AST::Global::assembly, t->max_call_size());

			t->increment_global(AST::Global::call);
			t->increment_local(AST::Local::offset, t->max_value_size());
		}
	};

// apply:

	template<auto... filler>
	struct T_chord_assembly_scanner_translation_action<CASAN::asm_apply, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->increment_global(AST::Global::call);
			t->increment_global(AST::Global::assembly, t->max_call_size());
		}
	};

// sub:

	template<auto... filler>
	struct T_chord_assembly_scanner_translation_action<CASAN::asm_sub_value, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->increment_global(AST::Global::call);
			t->increment_local(AST::Local::offset, t->max_value_size());
		}
	};

	template<auto... filler>
	struct T_chord_assembly_scanner_translation_action<CASAN::asm_sub_paste, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l) // refine ?
		{
			t->increment_global(AST::Global::call);
			t->increment_local(AST::Local::offset, t->max_value_size());
		}
	};

	template<auto... filler>
	struct T_chord_assembly_scanner_translation_action<CASAN::asm_sub_quote, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ } // nothing yet.
	};

	template<auto... filler>
	struct T_chord_assembly_scanner_translation_action<CASAN::asm_sub_end, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->update_offset(); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// morph:

/***********************************************************************************************************************/

// op:

	template<auto... filler>
	struct T_chord_assembly_scanner_translation_action<CASAN::mor_op_arity, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ } // nothing yet.
	};

	template<auto... filler>
	struct T_chord_assembly_scanner_translation_action<CASAN::mor_op_value, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ } // nothing yet.
	};

	template<auto... filler>
	struct T_chord_assembly_scanner_translation_action<CASAN::mor_op_id, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ } // nothing yet.
	};

	template<auto... filler>
	struct T_chord_assembly_scanner_translation_action<CASAN::mor_op_deref, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ } // nothing yet.
	};

	template<auto... filler>
	struct T_chord_assembly_scanner_translation_action<CASAN::mor_op_inc, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ } // nothing yet.
	};

	template<auto... filler>
	struct T_chord_assembly_scanner_translation_action<CASAN::mor_op_dec, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ } // nothing yet.
	};

// argpose:

	template<auto... filler>
	struct T_chord_assembly_scanner_translation_action<CASAN::mor_argpose_begin, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ } // nothing yet.
	};

	template<auto... filler>
	struct T_chord_assembly_scanner_translation_action<CASAN::mor_argpose_end, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ } // nothing yet.
	};

	template<auto... filler>
	struct T_chord_assembly_scanner_translation_action<CASAN::mor_argpose_value, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ } // nothing yet.
	};

// subpose:

	template<auto... filler>
	struct T_chord_assembly_scanner_translation_action<CASAN::mor_subpose_begin, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ } // nothing yet.
	};

	template<auto... filler>
	struct T_chord_assembly_scanner_translation_action<CASAN::mor_subpose_end, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ } // nothing yet.
	};

	template<auto... filler>
	struct T_chord_assembly_scanner_translation_action<CASAN::mor_subpose_value, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ } // nothing yet.
	};

	template<auto... filler>
	struct T_chord_assembly_scanner_translation_action<CASAN::mor_subpose_id, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ } // nothing yet.
	};

	template<auto... filler>
	struct T_chord_assembly_scanner_translation_action<CASAN::mor_subpose_deref, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ } // nothing yet.
	};

	template<auto... filler>
	struct T_chord_assembly_scanner_translation_action<CASAN::mor_subpose_inc, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ } // nothing yet.
	};

	template<auto... filler>
	struct T_chord_assembly_scanner_translation_action<CASAN::mor_subpose_dec, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ } // nothing yet.
	};

// curry:

	template<auto... filler>
	struct T_chord_assembly_scanner_translation_action<CASAN::mor_curry_begin, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ } // nothing yet.
	};

	template<auto... filler>
	struct T_chord_assembly_scanner_translation_action<CASAN::mor_curry_end, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ } // nothing yet.
	};

	template<auto... filler>
	struct T_chord_assembly_scanner_translation_action<CASAN::mor_curry_value, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ } // nothing yet.
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// interface:

	template<typename AST>
	struct T_chord_assembly_scanner_ta :
		public generator::T_generic_translation_action<T_chord_assembly_scanner_translation_action, AST, CASAN>
			{ };

	// interface:

		template<typename AST>
		struct T_chord_assembly_scanner_action
		{
			using T_ast		= AST;

			nik_ces auto value	= T_chord_assembly_scanner_ta<AST>{};
			using type		= decltype(value);
		};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// grammar:

/***********************************************************************************************************************/

	struct T_chord_assembly_scanner_grammar
	{
		using ActName		= CASAN;
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
				"           -> empty                                          : asm_accept ;"
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

					"FuncBeg -> identifier                ;"
					"FuncArg -> identifier : asm_func_arg ;"
					"FuncEnd -> \\;                       ;"

				// label:

					"LabelBeg     -> label : asm_label      ;"
					"LabelGotoBeg -> label : asm_label_goto ;"
					"LabelEnd     -> \\;                    ;"

				// return:

					"ReturnBeg -> return : asm_unit ;"
					"ReturnEnd -> \\;               ;"

				// goto:

					"GotoBeg -> goto       : asm_jump ;"
					"GotoVal -> identifier            ;"
					"GotoEnd -> \\;                   ;"

				// tail:

					"TailBeg -> tail       : asm_jump ;"
					"TailVal -> identifier            ;"
					"TailEnd -> \\;                   ;"

				// left:

					"LeftVal -> identifier : asm_left ;"
					"        -> .                     ;"

				// swap:

					"SwapBeg -> identifier : asm_swap ;"
					"SwapEnd -> \\;                   ;"

				// test:

					"TestBeg -> test : asm_apply ;"
					"TestEnd -> \\;              ;"

				// branch:

					"BranchBeg -> branch     : asm_jump ;"
					"BranchVal -> identifier            ;"
					"BranchEnd -> \\;                   ;"

				// void:

					"VoidBeg -> void : asm_apply ;"
					"VoidEnd -> \\;              ;"

				// apply:

					"ApplyBeg -> \\= : asm_apply ;"
					"ApplyEnd -> \\;             ;"

				// assign:

					"AssignBeg -> #   : asm_unit ;"
					"AssignEnd -> \\;            ;"

				// op value:

					"OpVal -> identifier : asm_sub_value ;"
					"      -> _          : asm_sub_paste ;"
					"      -> quote      : asm_sub_quote ;"

				// arg values:

					"ArgVals -> ArgVal ArgVals                 ;"
					"        -> ! MutVal ArgVals               ;"
					"        -> empty            : asm_sub_end ;"

				// arg value:

					"ArgVal -> identifier : asm_sub_value ;"
					"       -> _          : asm_sub_paste ;"
					"       -> quote      : asm_sub_quote ;"

				// mut value:

					"MutVal -> identifier : asm_sub_value ;"

				// unit value:

					"UnitVal -> identifier ;"
					"        -> _          ;"
					"        -> quote      ;"
					"        -> Morph      ;"
				//	"        -> Cycle      ;"

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

				sxa_pair( "asm_accept"     , ActName::asm_accept     ),

				sxa_pair( "asm_func_arg"   , ActName::asm_func_arg   ),
				sxa_pair( "asm_label"      , ActName::asm_label      ),
				sxa_pair( "asm_label_goto" , ActName::asm_label_goto ),
				sxa_pair( "asm_unit"       , ActName::asm_unit       ),
				sxa_pair( "asm_jump"       , ActName::asm_jump       ),
				sxa_pair( "asm_left"       , ActName::asm_left       ),
				sxa_pair( "asm_swap"       , ActName::asm_swap       ),
				sxa_pair( "asm_apply"      , ActName::asm_apply      ),

				sxa_pair( "asm_sub_value"  , ActName::asm_sub_value  ),
				sxa_pair( "asm_sub_paste"  , ActName::asm_sub_paste  ),
				sxa_pair( "asm_sub_quote"  , ActName::asm_sub_quote  ),
				sxa_pair( "asm_sub_end"    , ActName::asm_sub_end    ),

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
		);
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// pushdown automaton:

/***********************************************************************************************************************/

// interface:

#ifdef NIK_CHORD_ASSEMBLY_SCANNER_PARSER
#include NIK_CHORD_ASSEMBLY_SCANNER_PARSER_OBJ
#else

	template<typename T_grammar>
	struct T_chord_assembly_scanner_pda : public generator::T_generic_pda<T_grammar>
	{
		using base			= generator::T_generic_pda<T_grammar>;
		using ActName			= typename T_grammar::ActName;
		using T_lexer			= typename T_grammar::T_lexer;
		using Token			= typename T_grammar::Token;

		nik_ces auto prod_size		= 8;//cctmp::string_literal("<A|C|B|B>").size();

		nik_ces auto stack_start	= symbol_type{generator::Sign::nonterminal, base::start_index};
		nik_ces auto stack_finish	= symbol_type{generator::Sign::terminal, Token::prompt};

		nik_ces auto stack_size		= cctmp::literal("F<A|C|B|B>YPZ{}YPZYP,PZV;HGO").size(); // needs refining.
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
	struct T_chord_assembly_scanner_parser
	{
		using T_ast		= typename T_action::T_ast;
		using T_pda		= T_chord_assembly_scanner_pda<T_grammar>;
		using T_parser		= generator::T_generic_parser<T_action, T_pda>;
		using parseme_type	= generator::T_parseme<T_ast>;
		using parsoid_type	= generator::T_parsoid<T_pda::stack_size, T_pda::prod_size>;

		nik_ces auto & pda	= T_parser::pda; static_assert(!pda.ambiguous, "ambiguous cfg!");

		parseme_type parseme;
		parsoid_type parsoid;

		nik_ce T_chord_assembly_scanner_parser(const cselector<char> & s) :

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

	template<auto static_pg_parsed, auto static_source>
	struct T_chord_assembly_scanner_parsed
	{
		using T_ast			= T_chord_assembly_scanner_ast;
		using T_action			= T_chord_assembly_scanner_action<T_ast>;
		using T_grammar			= T_chord_assembly_scanner_grammar;
		using T_parser			= T_chord_assembly_scanner_parser<static_pg_parsed, T_action, T_grammar>;

		nik_ces auto & src		= member_value_U<static_source>;
		nik_ces auto parser		= T_parser{src.cselect()};
		nik_ces auto & value		= parser.parseme.tree;
		using type			= modify_type<_from_reference_, decltype(value)>;
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace chord

