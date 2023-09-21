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

	template<auto U>
	using T_store_U						= cctmp::T_store_U<U>;

	nik_ce auto _from_reference_				= cctmp::_from_reference_;

	template<auto Op, typename T>
	using modify_type					= cctmp::modify_type<Op, T>;

	using strlit_type					= cctmp::strlit_type;
	nik_ce auto U_strlit_type				= cctmp::U_strlit_type;

	using action_type					= cctmp::action_type;
	nik_ce auto U_action_type				= cctmp::U_action_type;

	using AN						= cctmp::AN;

	using sxt_pair						= cctmp::pair<strlit_type, token_type>;
	using sxa_pair						= cctmp::pair<strlit_type, action_type>;

	using symbol_type					= typename cctmp::symbol_type;
	using csymbol_type					= typename cctmp::csymbol_type;

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
		struct Total
       		{
			enum : gkey_type
			{
				line, arg, pad, tree, label, jump, morph, cycle,
				instr_1, instr_2, instr_3,
				dimension
			};
		};

		struct Cap { enum : gkey_type { tree, morph, cycle, dimension }; };

		using total_type    = cctmp::sequence<gindex_type, gindex_type{Total::dimension}>;
		using maximum_type  = cctmp::sequence<gindex_type, gindex_type{  Cap::dimension}>;
		using capacity_type = cctmp::sequence<gindex_type, gindex_type{  Cap::dimension}>;
		using csize_type    = typename total_type::csize_type;

		total_type total;
		maximum_type maximum;
		capacity_type capacity;

		gindex_type arg_size;
		gindex_type tag_size;
		gindex_type hierarchy_size;
		gindex_type target_size;

		nik_ce T_chord_assembly_scanner_ast() : arg_size{}, tag_size{}, hierarchy_size{}, target_size{}
		{
			total.fullsize();
			maximum.fullsize();
			capacity.fullsize();
		}

		nik_ce void increment_total   (csize_type pos) { ++total[pos]; }
		nik_ce void increment_maximum (csize_type pos) { ++maximum[pos]; }

		nik_ce void update_capacity(csize_type pos)
		{
			if (maximum[pos] > capacity[pos]) capacity[pos] = maximum[pos];
			maximum[pos] = 0;
		}

		nik_ce void update_accept()
		{
			arg_size = total[Total::arg] + total[Total::pad];
			tag_size = total[Total::label] + total[Total::jump];

			gindex_type level_2_size = total[Total::line] + 3;
			gindex_type level_1_size = total[Total::line] * (capacity[Cap::tree] + 3);
			gindex_type level_0_size = total[Total::tree] * 3;

			hierarchy_size = level_0_size + level_1_size + level_2_size;

			total[Total::instr_1] += total[Total::jump]; // instr1: test, void, goto, go into, branch
			total[Total::instr_2] += static_cast<bool>(total[Total::pad]); // instr2: pad
			total[Total::instr_3] += total[Total::pad]; // instr3: assign, apply, return

			target_size	= 1 // to parallel machine contrs.
					+ ( 1 * total[Total::instr_1] )
					+ ( 2 * total[Total::instr_2] )
					+ ( 3 * total[Total::instr_3] );
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
			nop = AN::nop,
			tree, label, jump, line_end, pad, instr_1, morph, cycle, arg,
			accept, instr_3, go_into, morph_arg, morph_cap, ival_arg, ival_cap,
			dimension
		};

	}; using CASAN = ChordAssemblyScannerActionName;

/***********************************************************************************************************************/

// nop:

	template<auto... filler>
	struct T_chord_assembly_scanner_translation_action<CASAN::nop, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l) { }
	};

// tree:

	template<auto... filler>
	struct T_chord_assembly_scanner_translation_action<CASAN::tree, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->increment_total(AST::Total::tree);
			t->increment_maximum(AST::Cap::tree);
		}
	};

// label:

	template<auto... filler>
	struct T_chord_assembly_scanner_translation_action<CASAN::label, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->increment_total(AST::Total::label);
			t->increment_total(AST::Total::tree);
			// increment maximum tree is optimized out.
		}
	};

// jump:

	template<auto... filler>
	struct T_chord_assembly_scanner_translation_action<CASAN::jump, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->increment_total(AST::Total::jump); }
	};

// line end:

	template<auto... filler>
	struct T_chord_assembly_scanner_translation_action<CASAN::line_end, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->increment_total(AST::Total::line);
			t->update_capacity(AST::Cap::tree);
		}
	};

// pad:

	template<auto... filler>
	struct T_chord_assembly_scanner_translation_action<CASAN::pad, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->increment_total(AST::Total::pad); }
	};

// instr 1:

	template<auto... filler>
	struct T_chord_assembly_scanner_translation_action<CASAN::instr_1, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->increment_total(AST::Total::instr_1); }
	};

// morph:

	template<auto... filler>
	struct T_chord_assembly_scanner_translation_action<CASAN::morph, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->increment_total(AST::Total::morph);
			t->increment_total(AST::Total::tree);
			t->increment_maximum(AST::Cap::tree);
		}
	};

// cycle:

	template<auto... filler>
	struct T_chord_assembly_scanner_translation_action<CASAN::cycle, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->increment_total(AST::Total::cycle);
			t->increment_total(AST::Total::tree);
			t->increment_maximum(AST::Cap::tree);
		}
	};

// arg:

	template<auto... filler>
	struct T_chord_assembly_scanner_translation_action<CASAN::arg, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->increment_total(AST::Total::arg); }
	};

// accept:

	template<auto... filler>
	struct T_chord_assembly_scanner_translation_action<CASAN::accept, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->update_accept(); }
	};

// instr 3:

	template<auto... filler>
	struct T_chord_assembly_scanner_translation_action<CASAN::instr_3, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->increment_total(AST::Total::instr_3); }
	};

// go into:

	template<auto... filler>
	struct T_chord_assembly_scanner_translation_action<CASAN::go_into, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->increment_total(AST::Total::line);
			t->increment_total(AST::Total::tree);
			t->increment_total(AST::Total::jump);
			// increment maximum tree is optimized out.
		}
	};

// morph arg:

	template<auto... filler>
	struct T_chord_assembly_scanner_translation_action<CASAN::morph_arg, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->increment_maximum(AST::Cap::morph); }
	};

// morph cap:

	template<auto... filler>
	struct T_chord_assembly_scanner_translation_action<CASAN::morph_cap, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->update_capacity(AST::Cap::morph); }
	};

// ival arg:

	template<auto... filler>
	struct T_chord_assembly_scanner_translation_action<CASAN::ival_arg, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->increment_maximum(AST::Cap::cycle); }
	};

// ival cap:

	template<auto... filler>
	struct T_chord_assembly_scanner_translation_action<CASAN::ival_cap, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->update_capacity(AST::Cap::cycle); }
	};

/***********************************************************************************************************************/

// interface:

	template<typename AST>
	struct T_chord_assembly_scanner_ta :
		public cctmp::T_generic_translation_action<T_chord_assembly_scanner_translation_action, AST, CASAN>
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

		nik_ces auto source() { return cctmp::context_free_grammar
		(
		// start:

			"Start",

		// atomics:

			"IValue -> identifier : tree ;"
			"Copy   -> .          : tree ;"
			"Paste  -> _          : tree ;"
			"Test   -> test       : tree ;"
			"Quote  -> quote      : tree ;"

			"Label  -> label  : label ;"
			"Branch -> branch : jump  ;"
			"Goto   -> goto   : jump  ;"
			"Tail   -> tail   : jump  ;"

			"LineEnd -> \\; : line_end ;"

		// rules:

			"LValue -> IValue : pad     ;" // upper bound.
			"       -> Copy   : instr_1 ;"
			"RValue -> IValue           ;"
			"       -> Paste            ;"
			"       -> Quote            ;"
			"       -> HValue : morph   ;"
			"       -> CValue : cycle   ;"

			"Start     -> identifier DArgs \\; Block RecBlock                      ;"
			"DArgs     -> identifier DArgs                               : arg     ;"
			"          -> empty                                                    ;"
			"Block     -> Label LineEnd Instrs                                     ;"
			"RecBlock  -> Block RecBlock                                           ;"
			"          -> empty                                          : accept  ;"
			"Instrs    -> Instr LineEnd RecInstr LastInstr                         ;"
			"          -> return RValue LineEnd                          : instr_3 ;"
			"RecInstr  -> Instr LineEnd RecInstr                                   ;"
			"          -> empty                                                    ;"
			"LastInstr -> Goto IValue LineEnd                                      ;"
			"          -> Tail IValue LineEnd                                      ;"
			"          -> return RValue LineEnd                          : instr_3 ;"
			"          -> Label LineEnd Instr LineEnd RecInstr LastInstr : go_into ;"
			"Instr     -> LValue Disp                                              ;"
			"          -> ! IValue \\= Vars                              : instr_1 ;"
			"          -> Test RValue Vars LineEnd Branch IValue         : instr_1 ;"
			"          -> void RValue Vars                               : instr_1 ;"
			"Disp      -> # RValue                                                 ;"
			"          -> \\= RValue Vars                                          ;"
			"Vars      -> RValue Vars                                              ;"
			"          -> ! IValue Vars                                            ;"
			"          -> empty                                                    ;"

		// morph:

			"HValue -> argpose < MArgs \\> ;"
			"       -> subpose < MArgs \\> ;"
			"       -> curry   < MArgs \\> ;"

			"MArgs    -> MorValue MArgs : morph_arg ;"
			"         -> empty          : morph_cap ;"
			"MorValue -> identifier                 ;"
			"         -> @                          ;"
			"         -> *                          ;"
			"         -> +                          ;"
			"         -> \\-                        ;"

		// cycle:

			"CValue -> repeat  AMLOpt        LMRIval Ivals ;"
			"       -> map     AMLOpt LRIval LMRIval Ivals ;"
			"       -> fold   ACMLOpt  FIval LMRIval Ivals ;"
			"       -> find    AMLOpt LRIval LMRIval Ivals ;"
			"       -> sift    AMLOpt LRIval LMRIval Ivals ;"

		    // parameter:

			"AMLOpt  -> < PArgs |           Binary | Binary \\> ;"
			"ACMLOpt -> < PArgs | Combine | Binary | Binary \\> ;"

			"PArgs    -> ParValue PArgs    ;"
			"         -> empty             ;"
			"Combine  -> identifier P2Args ;"
			"Binary   -> identifier P2Args ;"
			"         -> empty             ;"
			"P2Args   -> ParValue P1Arg    ;"
			"         -> empty             ;"
			"P1Arg    -> ParValue          ;"
			"         -> empty             ;"
			"ParValue -> identifier        ;"
			"         -> @                 ;"
			"         -> *                 ;"

		    // interval:

			"Ivals   -> Ival Ivals                      : ival_arg ;"
			"        -> empty                           : ival_cap ;"
			"Ival    -> LRIval                                     ;"
			"        ->  FIval                                     ;"
			"LRIval  -> LIval PairIter            RIval            ;"
			"LMRIval -> LIval PairIter , PairIter RIval : ival_arg ;"
			"FIval   -> { }                                        ;"

			"LIval -> [ ;"
			"      -> ( ;"
			"RIval -> ] ;"
			"      -> ) ;"

		    // iterator:

			"PairIter  ->   + | \\-            ;"
			"          -> \\- |   +            ;"
			"          -> IterValue | PrevIter ;"
			"          -> empty                ;"
			"PrevIter  -> IterValue            ;"
			"          -> ~                    ;"
			"IterValue -> identifier           ;"
			"          -> ^ identifier         ;"
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

			sxa_pair( "tree"       , ActName::tree       ),
			sxa_pair( "label"      , ActName::label      ),
			sxa_pair( "jump"       , ActName::jump       ),
			sxa_pair( "line_end"   , ActName::line_end   ),
			sxa_pair( "pad"        , ActName::pad        ),
			sxa_pair( "instr_1"    , ActName::instr_1    ),
			sxa_pair( "morph"      , ActName::morph      ),
			sxa_pair( "cycle"      , ActName::cycle      ),
			sxa_pair( "arg"        , ActName::arg        ),
			sxa_pair( "accept"     , ActName::accept     ),
			sxa_pair( "instr_3"    , ActName::instr_3    ),
			sxa_pair( "go_into"    , ActName::go_into    ),
			sxa_pair( "morph_arg"  , ActName::morph_arg  ),
			sxa_pair( "morph_cap"  , ActName::morph_cap  ),
			sxa_pair( "ival_arg"   , ActName::ival_arg   ),
			sxa_pair( "ival_cap"   , ActName::ival_cap   )
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
	struct T_chord_assembly_scanner_pda : public cctmp::T_generic_pda<T_grammar>
	{
		using base			= cctmp::T_generic_pda<T_grammar>;
		using ActName			= typename T_grammar::ActName;
		using T_lexer			= typename T_grammar::T_lexer;
		using Token			= typename T_grammar::Token;

		nik_ces auto prod_size		= cctmp::string_literal("<A|C|B|B>").size();

		nik_ces auto stack_start	= symbol_type{cctmp::Sign::nonterminal, base::start_index};
		nik_ces auto stack_finish	= symbol_type{cctmp::Sign::terminal, Token::prompt};

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
		using T_parser		= cctmp::T_generic_parser<T_action, T_pda>;
		using parseme_type	= cctmp::T_parseme<T_ast>;
		using parsoid_type	= cctmp::T_parsoid<T_pda::stack_size, T_pda::prod_size>;

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

