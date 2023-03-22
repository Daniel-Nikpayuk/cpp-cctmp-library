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

// generic transition table:

/***********************************************************************************************************************/

// attributes:

/***********************************************************************************************************************/

// symbol:

	using symbol_type  = gchar_type;
	using csymbol_type = symbol_type const;

/***********************************************************************************************************************/

// token kind:

	struct TokenKind { enum : gkey_type { nontoken = 0, nonterminal , terminal , dimension }; };

/***********************************************************************************************************************/

// action:

	using action_type  = gindex_type;
	using caction_type = action_type const;

	struct ActionName { enum : action_type { err = 0, nop , dimension }; };

/***********************************************************************************************************************/

// body:

	struct Body
	{
		using size_type  = gindex_type;
		using csize_type = size_type const;

		csymbol_type *symbol;
		size_type size;

		nik_ce Body() : symbol{}, size{} { }
		nik_ce Body(csymbol_type *_b, csize_type _s) : symbol{_b}, size{_s} { }
	};

/***********************************************************************************************************************/

// production:

	struct Production
	{
		Body body;
		action_type action;

		nik_ce Production() : body{}, action{ActionName::err} { }

		template<auto Size>
		nik_ce Production(gcchar_type (&str)[Size], caction_type _a = ActionName::nop) :
			body{str, Size - 1}, action{_a} { }
	};

/***********************************************************************************************************************/

// interface:

	struct T_generic_pdtt
	{
		// list:

			template<typename L, typename T>
			nik_ces T & list_entry(T (&l)[L::size], gcchar_type loc_c)
			{
				auto loc = numeric_find_pos(loc_c, L::symbol, L::finish);

				return l[loc];
			}

		// table:

			template<typename R, typename C, typename T>
			nik_ces T & table_entry(T (&t)[R::size][C::size], gcchar_type row_c, gcchar_type col_c)
			{
				auto row = numeric_find_pos(row_c, R::symbol, R::finish);
				auto col = numeric_find_pos(col_c, C::symbol, C::finish);

				return t[row][col];
			}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// generic parser:

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

		stack_type stack;
		prod_type prod;
		action_type action;
		lexeme word;

		nik_ce parsoid(ctoken_type start_symbol) :

			stack{start_symbol}, prod{}, action{}, word{} { }
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
		using NRAction		= typename act_type::NRAction;
		using TRAction		= typename act_type::TRAction;

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
					default                     : {      report(p, q)    ; break; }
				}
			}

			update_action(q, q.stack.front());
			terminal_update_action(p, q); // accept action.
		}

		// nonterminal:

			nik_ces bool is_nonterminal_err(const parsoid_type & q)
				{ return (q.prod->action == ActionName::err); }

			nik_ces void nonterminal(parseme_type & p, parsoid_type & q)
			{
				update_production(q);

				if (is_nonterminal_err(q)) nonterminal_recovery_action(p, q);
				else
				{
					nonterminal_update_stack(q);
					nonterminal_update_action(p, q);
				}
			}

			nik_ces void update_production(parsoid_type & q)
				{ q.prod = &pda.production(q.stack.front(), q.word.token); }

			nik_ces void nonterminal_update_stack(parsoid_type & q)
			{
				q.stack.pop();
				q.stack.push(q.prod->body.symbol, q.prod->body.size);
			}

			nik_ces void nonterminal_update_action(parseme_type & p, parsoid_type & q)
			{
				caction_type n = q.prod->action;

				if (n > NAction::nop)
				{
					auto update = act.nonterminal(n);

					update(p.tree, q.word);
				}
			}

			nik_ces void nonterminal_recovery_action(parseme_type & p, parsoid_type & q)
			{
				auto n      = pda.nonterminal_recovery(q.stack.front(), q.word.token);
				auto update = act.nonterminal_recovery(n);

				update(p.tree, q.word, q.stack);
			}

		// terminal:

			nik_ces bool is_terminal_err(const parsoid_type & q)
				{ return (q.action == ActionName::err) || (q.word.token != q.stack.front()); }

			nik_ces void terminal(parseme_type & p, parsoid_type & q, gcstring_type e)
			{
				update_action(q, q.word.token);

				if (is_terminal_err(q)) terminal_recovery_action(p, q);
				else
				{
					terminal_update_action(p, q);
					update_word(q, e);
					terminal_update_stack(q);
				}
			}

			nik_ces void update_action(parsoid_type & q, ctoken_type t)
				{ q.action = pda.action(t); }

			nik_ces void update_word(parsoid_type & q, gcstring_type e)
				{ T_lexer::lex(q.word, q.word.finish, e); }

			nik_ces void terminal_update_stack(parsoid_type & q)
				{ q.stack.pop(); }

			nik_ces void terminal_update_action(parseme_type & p, parsoid_type & q)
			{
				caction_type n = q.action;

				if (n > TAction::err)
				{
					auto update = act.terminal(n);

					update(p.tree, q.word);
				}
			}

			nik_ces void terminal_recovery_action(parseme_type & p, parsoid_type & q)
			{
				auto n      = pda.terminal_recovery(q.stack.front(), q.word.token);
				auto update = act.terminal_recovery(n);

				update(p.tree, q.word, q.stack);
			}

		// report:

			nik_ces void report(parseme_type & p, parsoid_type & q)
				{ } // nothing yet.
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// generic assembly:

/***********************************************************************************************************************/

// transition table:

	struct T_generic_assembly_pdtt
	{
		using ArraySize	= T_store_U<_array_size_>;

		struct Nonterminal
		{
			struct Action
			{
				enum : action_type
				{
					err = ActionName::err, nop = ActionName::nop,

					new_definition , new_def_arg     , new_label       , new_goto        ,
					new_assignment , new_application , new_conditional , new_jvalue      ,
					new_mvalue     , new_lvalue      , new_rvalue      ,
					new_copy       , new_paste       , new_return      , new_quote       ,
					dimension
				};
			};


			nik_ces gchar_type symbol[] = "VMPTOJINECBS";

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
					err = ActionName::err, nop = ActionName::nop,

					resolve_identifier , resolve_void      , resolve_return  ,
					resolve_paste      , resolve_copy      , resolve_mutable ,
					resolve_test       , resolve_branch    , resolve_goto    ,
					resolve_label      , resolve_statement , resolve_quote   ,
					resolve_accept     ,
					dimension
				};
			};

			nik_ces gchar_type symbol[] = ";i!q#=._lgvtbr";

			nik_ces auto size   = ArraySize::template result<>(symbol); // recognizes '\0'.
			nik_ces auto finish = symbol + size;

		}; using TAction = typename Terminal::Action;

		struct NonterminalRecovery
		{
			struct Action
			{
				enum : action_type
				{
					err = ActionName::err,

					instr_label , instr_return ,
					dimension
				};
			};

		}; using NRAction = typename NonterminalRecovery::Action;

		struct TerminalRecovery
		{
			struct Action
			{
				enum : action_type
				{
					err = ActionName::err,

					assign_to_apply ,
					dimension
				};
			};

		}; using TRAction = typename TerminalRecovery::Action;

		nik_ces auto   n_entry = T_generic_pdtt::template table_entry<Nonterminal, Terminal, Production>;
		nik_ces auto  cn_entry = T_generic_pdtt::template table_entry<Nonterminal, Terminal, Production const>;
		nik_ces auto   t_entry = T_generic_pdtt::template list_entry<Terminal, action_type>;
		nik_ces auto  ct_entry = T_generic_pdtt::template list_entry<Terminal, caction_type>;
		nik_ces auto  nr_entry = T_generic_pdtt::template table_entry<Nonterminal, Terminal, action_type>;
		nik_ces auto cnr_entry = T_generic_pdtt::template table_entry<Nonterminal, Terminal, caction_type>;
		nik_ces auto  tr_entry = T_generic_pdtt::template table_entry<Terminal, Terminal, action_type>;
		nik_ces auto ctr_entry = T_generic_pdtt::template table_entry<Terminal, Terminal, caction_type>;

		Production   n_base [Nonterminal::size][Terminal::size];
		action_type  t_base [   Terminal::size];
		action_type nr_base [Nonterminal::size][Terminal::size];
		action_type tr_base [   Terminal::size][Terminal::size];

		nik_ce T_generic_assembly_pdtt() : n_base{}, t_base{}, nr_base{}, tr_base{}
		{
			n_entry(n_base, 'S',  'i') = Production{ "iN;BC"   , NAction::new_definition  };
			n_entry(n_base, 'N',  'i') = Production{ "iN"      , NAction::new_def_arg     };
			n_entry(n_base, 'N',  ';') = Production{ ""                                   };
			n_entry(n_base, 'C',  'l') = Production{ "BC"                                 };
			n_entry(n_base, 'C', '\0') = Production{ ""                                   };
			n_entry(n_base, 'B',  'l') = Production{ "l;E"     , NAction::new_label       };
			n_entry(n_base, 'E',  'i') = Production{ "IJgO;"                              };
			n_entry(n_base, 'E',  '.') = Production{ "IJgO;"                              };
			n_entry(n_base, 'E',  '!') = Production{ "IJgO;"                              };
			n_entry(n_base, 'E',  't') = Production{ "IJgO;"                              };
			n_entry(n_base, 'E',  'v') = Production{ "IJgO;"                              };
			n_entry(n_base, 'E',  'r') = Production{ "rM;"     , NAction::new_return      };
			n_entry(n_base, 'J',  'i') = Production{ "IJ"                                 };
			n_entry(n_base, 'J',  '.') = Production{ "IJ"                                 };
			n_entry(n_base, 'J',  '!') = Production{ "IJ"                                 };
			n_entry(n_base, 'J',  't') = Production{ "IJ"                                 };
			n_entry(n_base, 'J',  'v') = Production{ "IJ"                                 };
			n_entry(n_base, 'J',  'g') = Production{ ""        , NAction::new_goto        };
			n_entry(n_base, 'I',  'i') = Production{ "P#M;"    , NAction::new_assignment  };
			n_entry(n_base, 'I',  '.') = Production{ "P#M;"    , NAction::new_assignment  };
			n_entry(n_base, 'I',  '!') = Production{ "!T=MV;"  , NAction::new_application };
			n_entry(n_base, 'I',  't') = Production{ "tMV;bO;" , NAction::new_conditional };
			n_entry(n_base, 'I',  'v') = Production{ "vMV;"    , NAction::new_application };
			n_entry(n_base, 'V',  'i') = Production{ "MV"                                 };
			n_entry(n_base, 'V',  '!') = Production{ "!TV"                                };
			n_entry(n_base, 'V',  '_') = Production{ "MV"                                 };
			n_entry(n_base, 'V',  'q') = Production{ "MV"                                 };
			n_entry(n_base, 'V',  ';') = Production{ ""                                   };
			n_entry(n_base, 'T',  'i') = Production{ "i"       , NAction::new_mvalue      };
			n_entry(n_base, 'O',  'i') = Production{ "i"       , NAction::new_jvalue      };
			n_entry(n_base, 'P',  'i') = Production{ "i"       , NAction::new_lvalue      };
			n_entry(n_base, 'P',  '.') = Production{ "."       , NAction::new_copy        };
			n_entry(n_base, 'M',  'i') = Production{ "i"       , NAction::new_rvalue      };
			n_entry(n_base, 'M',  '_') = Production{ "_"       , NAction::new_paste       };
			n_entry(n_base, 'M',  'q') = Production{ "q"       , NAction::new_quote       };

			t_entry(t_base,  '#') = TAction::nop                ;
			t_entry(t_base,  '=') = TAction::nop                ;
			t_entry(t_base,  'r') = TAction::nop                ;
			t_entry(t_base,  '!') = TAction::nop                ;
			t_entry(t_base,  'i') = TAction::resolve_identifier ;
			t_entry(t_base,  'v') = TAction::resolve_void       ;
			t_entry(t_base,  '_') = TAction::resolve_paste      ;
			t_entry(t_base,  '.') = TAction::resolve_copy       ;
			t_entry(t_base,  't') = TAction::resolve_test       ;
			t_entry(t_base,  'b') = TAction::resolve_branch     ;
			t_entry(t_base,  'g') = TAction::resolve_goto       ;
			t_entry(t_base,  'l') = TAction::resolve_label      ;
			t_entry(t_base,  ';') = TAction::resolve_statement  ;
			t_entry(t_base,  'q') = TAction::resolve_quote      ;
			t_entry(t_base, '\0') = TAction::resolve_accept     ;

			nr_entry(nr_base, 'J',  'l') = NRAction::instr_label  ;
			nr_entry(nr_base, 'J',  'r') = NRAction::instr_return ;

			tr_entry(tr_base, '#', '=') = TRAction::assign_to_apply ;
		}

		nik_ce const Production & production(gcchar_type row_c, gcchar_type col_c) const
			{ return cn_entry(n_base, row_c, col_c); }

		nik_ce caction_type & action(gcchar_type loc_c) const
			{ return ct_entry(t_base, loc_c); }

		nik_ce caction_type & nonterminal_recovery(gcchar_type row_c, gcchar_type col_c) const
			{ return cnr_entry(nr_base, row_c, col_c); }

		nik_ce caction_type & terminal_recovery(gcchar_type row_c, gcchar_type col_c) const
			{ return ctr_entry(tr_base, row_c, col_c); }
	};

/***********************************************************************************************************************/

// pushdown automaton:

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

// transition table:

/***********************************************************************************************************************/

// pushdown automaton:

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

