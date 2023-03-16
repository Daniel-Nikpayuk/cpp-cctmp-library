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

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// generic parser:

/***********************************************************************************************************************/

// attributes:

	using symbol_type  = gchar_type;
	using csymbol_type = symbol_type const;

	using action_type  = gindex_type;
	using caction_type = action_type const;

/***********************************************************************************************************************/

// token kind:

	struct TokenKind { enum : gkey_type { nontoken = 0, nonterminal , terminal , dimension }; };

/***********************************************************************************************************************/

// permission:

	struct Permission { enum : gkey_type { none = 0, string , stack , dimension }; };

/***********************************************************************************************************************/

// body:

	struct Body
	{
		using size_type  = gindex_type;
		using csize_type = size_type const;

		csymbol_type *symbol;
		size_type size;

		nik_ce Body()                                : symbol{    }, size{    } { }
		nik_ce Body(csymbol_type *_b, csize_type _s) : symbol{ _b }, size{ _s } { }
	};

/***********************************************************************************************************************/

// tenet:

	struct Tenet
	{
		action_type name;
		gkey_type note;

		nik_ce Tenet()                               : name{    }, note{    } { }
		nik_ce Tenet(caction_type _a, gckey_type _p) : name{ _a }, note{ _p } { }
	};

/***********************************************************************************************************************/

// production:

	struct Production
	{
		Body body;
		Tenet tenet;

		nik_ce Production()                                  : body{    }, tenet{    } { }
		nik_ce Production(const Body & _b, const Tenet & _t) : body{ _b }, tenet{ _t } { }
	};

/***********************************************************************************************************************/

// transition table:

	struct T_generic_pdtt
	{
		template<auto Size>
		nik_ces Production ntransition(gcchar_type (&str)[Size], caction_type act, gckey_type perm)
			{ return Production{Body(str, Size - 1), Tenet(act, perm)}; }

		nik_ces Tenet ttransition(caction_type act, gckey_type perm)
			{ return Tenet(act, perm); }

		template<typename N, typename T>
		nik_ces Production & table_entry(
				Production (&t)[N::size][T::size], gcchar_type row_c, gcchar_type col_c)
		{
			auto row = numeric_find_pos(row_c, N::symbol, N::finish);
			auto col = numeric_find_pos(col_c, T::symbol, T::finish);

			return t[row][col];
		}

		template<typename N, typename T>
		nik_ces const Production & production(
				const Production (&t)[N::size][T::size], gcchar_type row_c, gcchar_type col_c)
		{
			auto row = numeric_find_pos(row_c, N::symbol, N::finish);
			auto col = numeric_find_pos(col_c, T::symbol, T::finish);

			return t[row][col];
		}

		template<typename T>
		nik_ces Tenet & list_entry(Tenet (&l)[T::size], gcchar_type loc_c)
		{
			auto loc = numeric_find_pos(loc_c, T::symbol, T::finish);

			return l[loc];
		}

		template<typename T>
		nik_ces const Tenet & tenet(const Tenet (&l)[T::size], gcchar_type loc_c)
		{
			auto loc = numeric_find_pos(loc_c, T::symbol, T::finish);

			return l[loc];
		}
	};

/***********************************************************************************************************************/

// stack:

	template<auto Size>
	struct Stack
	{
		nik_ces auto length		= Size;
		using size_type			= decltype(Size);

		token_type token[length];
		ctoken_type *start;
		token_type *current;
		ctoken_type *finish;

		nik_ce Stack(ctoken_type s) : token{}, start{token}, current{token}, finish{token + length}
		{
			*   current = '\0';
			* ++current = s;
		}

		nik_ce ctoken_type & front() const { return *current; }
		nik_ce  token_type & front()       { return *current; }

		nik_ce void pop() { if (current != start) --current; }

		nik_ce void push(gcstring_type b, size_type size)
		{
			auto k = b + size;
			while (k != b) *++current = *--k;
		}

		nik_ce auto begin () const { return start;  }
		nik_ce auto end   () const { return finish; }
		nik_ce auto size  () const { return length; }
	};

/***********************************************************************************************************************/

// parseme:

	template<typename T_ast>
	struct parseme
	{
		gstring_type  start;
		gstring_type finish;
		T_ast         tree;

		nik_ce parseme() : start{}, finish{}, tree{} { }
	};

/***********************************************************************************************************************/

// parsoid:

	template<auto Size>
	struct parsoid
	{
		using stack_type	= Stack<Size>;
		using prod_type		= Production const*;
		using tenet_type	= Tenet const*;

		stack_type stack;
		prod_type production;
		tenet_type tenet;
		lexeme word;

		nik_ce parsoid(ctoken_type start_symbol) : stack{start_symbol}, production{}, tenet{}, word{} { }
	};

/***********************************************************************************************************************/

// interface:

	template<typename T_action, typename T_ast, typename T_pda, typename T_lexer>
	struct T_generic_parser
	{
		nik_ces auto act	= member_value_T<T_action>;
		nik_ces auto pda	= member_value_T<T_pda>;

		using act_type		= member_type_T<T_action>;
		using NAction		= typename act_type::NAction;
		using TAction		= typename act_type::TAction;

		using parseme_type	= parseme<T_ast>;
		using parsoid_type	= parsoid<T_pda::stack_size>;

		nik_ces void parse(parseme_type & p, gcstring_type b, gcstring_type e)
		{
			parsoid_type q{T_pda::nonterminal_start};

			T_lexer::lex(q.word, b, e);

			while (q.stack.front() != '\0')
			{
				switch (T_pda::token_kind(q.stack.front()))
				{
					case TokenKind::nonterminal : { nonterminal(p, q)    ; break; }
					case TokenKind::terminal    : {    terminal(p, q, e) ; break; }
					default                     : {       error(p, q)    ; break; }
				}
			}

			update_tenet(q, q.stack.front());
			terminal_action(p, q, q.tenet->name); // accept action.
		}

		nik_ces void nonterminal(parseme_type & p, parsoid_type & q)
		{
			update_production(q);
			nonterminal_update_stack(q);
			nonterminal_update_action(p, q);
		}

		nik_ces void terminal(parseme_type & p, parsoid_type & q, gcstring_type e)
		{
			if (q.stack.front() != q.word.token) ; // error.
			else
			{
				update_tenet(q, q.word.token);
				terminal_update_action(p, q);
				update_word(q, e);
				terminal_update_stack(q);
			}
		}

		nik_ces void error(parseme_type & p, parsoid_type & q)
		{
			// nothing yet.
		}

		nik_ces void update_production(parsoid_type & q)
		{
			q.production = &pda.production(q.stack.front(), q.word.token);
			// if (production == empty) error;
		}

		nik_ces void update_tenet(parsoid_type & q, ctoken_type t)
			{ q.tenet = &pda.tenet(t); }

		nik_ces void nonterminal_update_stack(parsoid_type & q)
		{
			q.stack.pop();
			q.stack.push(q.production->body.symbol, q.production->body.size);
		}

		nik_ces void update_word(parsoid_type & q, gcstring_type e)
			{ T_lexer::lex(q.word, q.word.finish, e); }

		nik_ces void terminal_update_stack(parsoid_type & q)
			{ q.stack.pop(); }

		nik_ces void nonterminal_action(parseme_type & p, parsoid_type & q, caction_type n)
		{
			if (n != NAction::nop)
			{
				auto update = act.nonterminal_action(n);

				update(p.tree, q.word);
			}
		}

		nik_ces void terminal_action(parseme_type & p, parsoid_type & q, caction_type n)
		{
			if (n != TAction::nop)
			{
				auto update = act.terminal_action(n);

				update(p.tree, q.word);
			}
		}

		nik_ces void string_action(parseme_type & p, parsoid_type & q, caction_type n)
		{
			auto update = act.string_action(n);

			update(p.tree, q.word);
		}

		nik_ces void stack_action(parseme_type & p, parsoid_type & q, caction_type n)
		{
			auto update = act.stack_action(n);

			update(p.tree, q.word, q.stack);
		}

		nik_ces void nonterminal_update_action(parseme_type & p, parsoid_type & q)
		{
			switch (q.production->tenet.note)
			{
				case Permission::none   : { nonterminal_action(p, q, q.production->tenet.name); break; }
				case Permission::string : {      string_action(p, q, q.production->tenet.name); break; }
				case Permission::stack  : {       stack_action(p, q, q.production->tenet.name); break; }
			}
		}

		nik_ces void terminal_update_action(parseme_type & p, parsoid_type & q)
		{
			switch (q.tenet->note)
			{
				case Permission::none   : { terminal_action(p, q, q.tenet->name); break; }
				case Permission::string : {   string_action(p, q, q.tenet->name); break; }
				case Permission::stack  : {    stack_action(p, q, q.tenet->name); break; }
			}
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// generic assembly:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// pushdown automaton:

/***********************************************************************************************************************/

// transition table:

	struct T_generic_assembly_pdtt
	{
		using ArraySize	= T_store_U<_array_size_>;

		struct String
		{
			struct Action
			{
				enum : action_type
				{
					parse_repeat     , parse_map      , parse_fold ,
					parse_find_first , parse_find_all , parse_zip  ,
					parse_fasten     , parse_glide    ,
					dimension
				};
			};

		}; using RAction = typename String::Action;

		struct Stack
		{
			struct Action
			{
				enum : action_type
				{
					instr_label , instr_return ,
					dimension
				};
			};

		}; using SAction = typename Stack::Action;

		struct Nonterminal
		{
			struct Action
			{
				enum : action_type
				{
					nop = 0,
					new_definition  , new_coordinate  ,
					new_conditional , new_application ,
					dimension
				};
			};

			nik_ces gchar_type symbol[] = "VMOJINTECBS";

			nik_ces auto size   = ArraySize::template result<>(symbol) - 1;
			nik_ces auto finish = symbol + size;
			nik_ces auto start  = 'S';

		}; using NAction = typename Nonterminal::Action;

		struct Terminal
		{
			struct Action
			{
				enum : action_type
				{
					nop = 0,
					resolve_identifier , resolve_void      , resolve_return  ,
					resolve_paste      , resolve_copy      , resolve_mutable ,
					resolve_test       , resolve_branch    , resolve_goto    ,
					resolve_label      , resolve_statement , resolve_quote   ,
					resolve_repeat     , resolve_map       , resolve_fold    ,
					resolve_find_first , resolve_find_all  , resolve_zip     ,
					resolve_fasten     , resolve_glide     ,
					resolve_accept     ,
					dimension
				};
			};

			nik_ces gchar_type symbol[] = ";i!q=._lgvtbr01234567";

			nik_ces auto size   = ArraySize::template result<>(symbol); // recognizes '\0'.
			nik_ces auto finish = symbol + size;

		}; using TAction = typename Terminal::Action;

		nik_ces auto t_entry = T_generic_pdtt::template table_entry<Nonterminal, Terminal>;
		nik_ces auto l_entry = T_generic_pdtt::template list_entry<Terminal>;

		template<auto Size>
		nik_ces Production ntransition(gcchar_type (&str)[Size],
			caction_type act = NAction::nop, gckey_type perm = Permission::none)
				{ return T_generic_pdtt::ntransition(str, act, perm); }

		nik_ces Tenet ttransition(caction_type act = TAction::nop, gckey_type perm = Permission::none)
			{ return T_generic_pdtt::ttransition(act, perm); }

		Production table[Nonterminal::size][Terminal::size];
		Tenet list[Terminal::size];

		nik_ce T_generic_assembly_pdtt() : table{}, list{}
		{
			t_entry(table, 'S',  'i') = ntransition( "iN;BC"   , NAction::new_definition  );
			t_entry(table, 'N',  'i') = ntransition( "iN"                                 );
			t_entry(table, 'N',  ';') = ntransition( ""                                   );
			t_entry(table, 'C',  'l') = ntransition( "BC"                                 );
			t_entry(table, 'C', '\0') = ntransition( ""                                   );
			t_entry(table, 'B',  'l') = ntransition( "l;E"     , NAction::new_coordinate  );
			t_entry(table, 'E',  'i') = ntransition( "IJgi;"                              );
			t_entry(table, 'E',  '!') = ntransition( "IJgi;"                              );
			t_entry(table, 'E',  '.') = ntransition( "IJgi;"                              );
			t_entry(table, 'E',  't') = ntransition( "IJgi;"                              );
			t_entry(table, 'E',  'v') = ntransition( "IJgi;"                              );
			t_entry(table, 'E',  'r') = ntransition( "rM;"                                );
			t_entry(table, 'J',  'i') = ntransition( "IJ"                                 );
			t_entry(table, 'J',  '!') = ntransition( "IJ"                                 );
			t_entry(table, 'J',  '.') = ntransition( "IJ"                                 );
			t_entry(table, 'J',  't') = ntransition( "IJ"                                 );
			t_entry(table, 'J',  'v') = ntransition( "IJ"                                 );
			t_entry(table, 'J',  'g') = ntransition( ""                                   );
			t_entry(table, 'J',  'l') = ntransition( ""        , SAction::instr_label     ,  Permission::stack );
			t_entry(table, 'J',  'r') = ntransition( ""        , SAction::instr_return    ,  Permission::stack );
			t_entry(table, 'I',  'i') = ntransition( "T=OV;"   , NAction::new_application );
			t_entry(table, 'I',  '!') = ntransition( "T=OV;"   , NAction::new_application );
			t_entry(table, 'I',  '.') = ntransition( "T=OV;"   , NAction::new_application );
			t_entry(table, 'I',  't') = ntransition( "tOV;bi;" , NAction::new_conditional );
			t_entry(table, 'I',  'v') = ntransition( "vOV;"    , NAction::new_application );
			t_entry(table, 'V',  'i') = ntransition( "MV"                                 );
			t_entry(table, 'V',  '!') = ntransition( "MV"                                 );
			t_entry(table, 'V',  'q') = ntransition( "MV"                                 );
			t_entry(table, 'V',  '_') = ntransition( "MV"                                 );
			t_entry(table, 'V',  ';') = ntransition( ""                                   );
			t_entry(table, 'T',  'i') = ntransition( "i"                                  );
			t_entry(table, 'T',  '!') = ntransition( "!i"                                 );
			t_entry(table, 'T',  '.') = ntransition( "."                                  );
			t_entry(table, 'O',  'i') = ntransition( "i"                                  );
			t_entry(table, 'O',  'q') = ntransition( "q"                                  );
			t_entry(table, 'O',  '0') = ntransition( "0"                                  );
			t_entry(table, 'O',  '1') = ntransition( "1"                                  );
			t_entry(table, 'O',  '2') = ntransition( "2"                                  );
			t_entry(table, 'O',  '3') = ntransition( "3"                                  );
			t_entry(table, 'O',  '4') = ntransition( "4"                                  );
			t_entry(table, 'O',  '5') = ntransition( "5"                                  );
			t_entry(table, 'O',  '6') = ntransition( "6"                                  );
			t_entry(table, 'O',  '7') = ntransition( "7"                                  );
			t_entry(table, 'M',  'i') = ntransition( "i"                                  );
			t_entry(table, 'M',  '!') = ntransition( "!i"                                 );
			t_entry(table, 'M',  'q') = ntransition( "q"                                  );
			t_entry(table, 'M',  '_') = ntransition( "_"                                  );

			l_entry(list,  'i') = ttransition( TAction::resolve_identifier );
			l_entry(list,  'v') = ttransition( TAction::resolve_void       );
			l_entry(list,  'r') = ttransition( TAction::resolve_return     );
			l_entry(list,  '_') = ttransition( TAction::resolve_paste      );
			l_entry(list,  '.') = ttransition( TAction::resolve_copy       );
			l_entry(list,  '!') = ttransition( TAction::resolve_mutable    );
			l_entry(list,  't') = ttransition( TAction::resolve_test       );
			l_entry(list,  'b') = ttransition( TAction::resolve_branch     );
			l_entry(list,  'g') = ttransition( TAction::resolve_goto       );
			l_entry(list,  'l') = ttransition( TAction::resolve_label      );
			l_entry(list,  ';') = ttransition( TAction::resolve_statement  );
			l_entry(list,  'q') = ttransition( TAction::resolve_quote      );
			l_entry(list,  '0') = ttransition( RAction::parse_repeat       ,  Permission::string );
			l_entry(list,  '1') = ttransition( RAction::parse_map          ,  Permission::string );
			l_entry(list,  '2') = ttransition( RAction::parse_fold         ,  Permission::string );
			l_entry(list,  '3') = ttransition( RAction::parse_find_first   ,  Permission::string );
			l_entry(list,  '4') = ttransition( RAction::parse_find_all     ,  Permission::string );
			l_entry(list,  '5') = ttransition( RAction::parse_zip          ,  Permission::string );
			l_entry(list,  '6') = ttransition( RAction::parse_fasten       ,  Permission::string );
			l_entry(list,  '7') = ttransition( RAction::parse_glide        ,  Permission::string );
			l_entry(list, '\0') = ttransition( TAction::resolve_accept     );
		}

		nik_ce const Production & production(gcchar_type row_c, gcchar_type col_c) const
			{ return T_generic_pdtt::template production<Nonterminal, Terminal>(table, row_c, col_c); }

		nik_ce const Tenet & tenet(gcchar_type loc_c) const
			{ return T_generic_pdtt::template tenet<Terminal>(list, loc_c); }
	};

/***********************************************************************************************************************/

// interface:

	struct T_generic_assembly_pda
	{
		using ArraySize				= T_store_U<_array_size_>;
		using T_pdtt				= T_generic_assembly_pdtt;

		nik_ces auto value			= T_pdtt{};
		nik_ces auto nonterminal_symbol		= T_pdtt::Nonterminal::symbol;
		nik_ces auto nonterminal_finish		= T_pdtt::Nonterminal::finish;
		nik_ces auto nonterminal_start		= T_pdtt::Nonterminal::start;
		nik_ces auto terminal_symbol		= T_pdtt::Terminal::symbol;
		nik_ces auto terminal_finish		= T_pdtt::Terminal::finish;
		nik_ces auto stack_size			= ArraySize::template result<>("tOV;bi;Jgi;C$") - 1;
								// this literal is the longest possible sentential.

		nik_ces bool is_nonterminal(ctoken_type t)
		{
			auto loc = numeric_find(t, nonterminal_symbol, nonterminal_finish);

			return (loc != nonterminal_finish);
		}

		nik_ces bool is_terminal(ctoken_type t)
		{
			auto loc = numeric_find(t, terminal_symbol, terminal_finish);

			return (loc != terminal_finish);
		}

		nik_ces auto token_kind(ctoken_type t)
		{
			if      (is_nonterminal(t)) return TokenKind::nonterminal;
			else if (is_terminal(t)   ) return TokenKind::terminal;
			else                        return TokenKind::nontoken;
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// chord assembly:

/***********************************************************************************************************************/

// pushdown automaton:

/***********************************************************************************************************************/

// transition table:

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

