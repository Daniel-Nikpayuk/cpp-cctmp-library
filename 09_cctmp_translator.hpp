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

// translator:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// translation action:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// nonterminal:

/***********************************************************************************************************************/

// action:

	struct T_generic_assembly_nta
	{
		template<typename AST>
		using signature = void(*)(AST&, clexeme&);

		template<typename AST>
		nik_ces void err(AST & toc, clexeme & l) { }

		template<typename AST>
		nik_ces void nop(AST & toc, clexeme & l) { }

		// definition:

			template<typename AST>
			nik_ces void new_definition(AST & toc, clexeme & l)
			{
				toc.set_kind(Context::define);
				toc.set_current_entry(l, Sign::na);
			}

		// def(inition) arg(ument):

			template<typename AST>
			nik_ces void new_def_arg(AST & toc, clexeme & l)
			{
				toc.set_current_entry(l, Sign::carg, toc.arg_size);
				toc.increment_arg_size();
			}

		// def(inition) size:

			template<typename AST>
			nik_ces void new_def_end(AST & toc, clexeme & l)
				{ toc.set_arity(toc.arg_size); }

		// label:

			template<typename AST>
			nik_ces void new_label(AST & toc, clexeme & l)
			{
				toc.set_kind(Context::label);
				toc.set_current_entry(l, Sign::label, toc.label_size);
				toc.increment_label_size();
			}

		// goto:

			template<typename AST>
			nik_ces void new_goto(AST & toc, clexeme & l)
				{ toc.set_kind(Context::go_to); }

		// assignment:

			template<typename AST>
			nik_ces void new_assignment(AST & toc, clexeme & l)
			{
				toc.set_kind(Context::assign);
				toc.update_lookup();
			}

		// application:

			template<typename AST>
			nik_ces void new_application(AST & toc, clexeme & l)
			{
				toc.set_kind(Context::apply);
				toc.set_void(); // cfg optimization.
				toc.update_lookup();
			}

		// conditional:

			template<typename AST>
			nik_ces void new_conditional(AST & toc, clexeme & l)
			{
				toc.set_kind(Context::test);
				toc.set_current_entry(l, Sign::copy);
				toc.update_lookup();
			}

		// jvalue:

			template<typename AST>
			nik_ces void new_jvalue(AST & toc, clexeme & l)
				{ toc.set_current_entry(l, Sign::jump); }

		// mvalue:

			template<typename AST>
			nik_ces void new_mvalue_identifier(AST & toc, clexeme & l, gcindex_type index)
			{
				auto shift = toc.has_paste() ? _one : _zero;

				toc.set_current_entry(l, Sign::marg, index + shift);
			}

			template<typename AST>
			nik_ces void new_mvalue(AST & toc, clexeme & l)
			{
				auto k = toc.match_arguments(l.start, l.finish);
				if (toc.is_arg_match(k)) new_mvalue_identifier(toc, l, k->index);
				// else error
			}

		// lvalue:

			template<typename AST>
			nik_ces void new_lvalue_identifier(AST & toc, clexeme & l, gcindex_type index)
				{ toc.set_current_entry(l, Sign::carg, index); }

			template<typename AST>
			nik_ces void new_lvalue_variable(AST & toc, clexeme & l)
			{
				toc.set_current_entry(l, Sign::carg, toc.arg_size);
				toc.set_arg_start(toc.current_start_at(_zero));
				toc.set_arg_finish(toc.current_finish_at(_zero));
				toc.set_arg_sign(Sign::carg);
				toc.set_arg_index(toc.arg_size);

				toc.increment_arg_size();
				toc.increment_arg_entry();
			}

			template<typename AST>
			nik_ces void new_lvalue_unknown(AST & toc, clexeme & l)
			{
				if (toc.match_name(l.start, l.finish)) // Sign::recurse:
				{
					// error.
				}
				else new_lvalue_variable(toc, l);
			}

			template<typename AST>
			nik_ces void new_lvalue(AST & toc, clexeme & l)
			{
				auto k = toc.match_arguments(l.start, l.finish);
				if (toc.is_arg_match(k)) new_lvalue_identifier(toc, l, k->index);
				else new_lvalue_unknown(toc, l);
			}

		// rvalue:

			template<typename AST>
			nik_ces void new_rvalue_identifier(AST & toc, clexeme & l, gcindex_type index)
			{
				auto shift = toc.has_paste() ? _one : _zero;

				toc.set_current_entry(l, Sign::carg, index + shift);
			}

			template<typename AST>
			nik_ces void new_rvalue_unknown(AST & toc, clexeme & l)
			{
				auto j = toc.match_name(l.start, l.finish);
				auto s = j ? Sign::recurse : Sign::env;

				toc.set_current_entry(l, s);
				toc.update_lookup();
			}

			template<typename AST>
			nik_ces void new_rvalue(AST & toc, clexeme & l)
			{
				auto k = toc.match_arguments(l.start, l.finish);
				if (toc.is_arg_match(k)) new_rvalue_identifier(toc, l, k->index);
				else new_rvalue_unknown(toc, l);
			}

		// copy:

			template<typename AST>
			nik_ces void new_copy(AST & toc, clexeme & l)
			{
				toc.set_current_entry(l, Sign::copy);
				toc.set_copy();
			}

		// paste:

			template<typename AST>
			nik_ces void new_paste(AST & toc, clexeme & l)
				{ toc.set_current_entry(l, Sign::paste); }

		// return:

			template<typename AST>
			nik_ces void new_return(AST & toc, clexeme & l)
				{ toc.set_kind(Context::re_turn); }

		// quote:

			template<typename AST>
			nik_ces void new_quote(AST & toc, clexeme & l)
				{ } // nothing yet.
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// terminal:

/***********************************************************************************************************************/

// (context) branch:

	struct T_generic_assembly_tta_context_branch
	{
		template<typename AST>
		nik_ces void set(AST & toc, clexeme & l)
			{ toc.set_kind(Context::branch); }

		template<typename AST>
		nik_ces void bookmark(AST & toc, clexeme & l)
		{
			toc.bookmark_graph();
			toc.bookmark_dependency();
			toc.bookmark_branch();
		}

		template<typename AST>
		nik_ces void increment(AST & toc, clexeme & l)
		{
			toc.increment_graph();
			toc.increment_depend();
			toc.increment_branch();
		}
	};

/***********************************************************************************************************************/

// (context) go_to:

	struct T_generic_assembly_tta_context_goto
	{
		template<typename AST>
		nik_ces void bookmark(AST & toc, clexeme & l)
		{
			toc.bookmark_graph();
			toc.bookmark_dependency();
			toc.bookmark_goto();
		}

		template<typename AST>
		nik_ces void increment(AST & toc, clexeme & l)
		{
			toc.increment_graph();
			toc.increment_depend();
			toc.increment_goto();
		}
	};

/***********************************************************************************************************************/

// (context) label:

	struct T_generic_assembly_tta_context_label
	{
		template<typename AST>
		nik_ces void bookmark(AST & toc, clexeme & l)
		{
			toc.bookmark_graph();
			toc.bookmark_label();
		}

		template<typename AST>
		nik_ces void increment(AST & toc, clexeme & l)
		{
			toc.increment_entry();
			toc.increment_graph();
			toc.increment_label();
		}
	};

/***********************************************************************************************************************/

// (context) accept:

	struct T_generic_assembly_tta_context_accept
	{
		template<typename AST, typename SubpageType>
		nik_ces void link(AST & toc, SubpageType & subpage)
		{
			for (auto k = subpage.begin(); k != subpage.end(); ++k)
			{
				auto j = (*k)->begin();
				auto l = toc.match_label(j->start, j->finish);
				if (l == toc.label.end()) ; // error
				else (*k)->array->index = (*l)->begin()->index;
			}
		}
	};

/***********************************************************************************************************************/

// action:

	struct T_generic_assembly_tta
	{
		template<typename AST>
		using signature = void(*)(AST&, clexeme&);

		using NTA		= T_generic_assembly_nta;
		using Branch		= T_generic_assembly_tta_context_branch;
		using Goto		= T_generic_assembly_tta_context_goto;
		using Label		= T_generic_assembly_tta_context_label;
		using Accept		= T_generic_assembly_tta_context_accept;

		template<typename AST>
		nik_ces void err(AST & toc, clexeme & l) { }

		template<typename AST>
		nik_ces void nop(AST & toc, clexeme & l) { }

		// resolve:

			template<typename AST>
			nik_ces void resolve_identifier(AST & toc, clexeme & l)
				{ toc.increment_entry(); }

			template<typename AST>
			nik_ces void resolve_void(AST & toc, clexeme & l)
				{ toc.increment_entry(); } // symbolic entry.

			template<typename AST>
			nik_ces void resolve_test(AST & toc, clexeme & l)
				{ toc.increment_entry(); } // symbolic entry.

			template<typename AST>
			nik_ces void resolve_copy(AST & toc, clexeme & l)
				{ toc.increment_entry(); }

			template<typename AST>
			nik_ces void resolve_paste(AST & toc, clexeme & l)
				{ toc.increment_entry(); }

			template<typename AST>
			nik_ces void resolve_branch(AST & toc, clexeme & l)
			{
				Branch::set(toc, l);
				Branch::bookmark(toc, l);
				Branch::increment(toc, l);
			}

			template<typename AST>
			nik_ces void resolve_goto(AST & toc, clexeme & l)
			{
				Goto::bookmark(toc, l);
				Goto::increment(toc, l);
			}

			template<typename AST>
			nik_ces void resolve_label(AST & toc, clexeme & l)
			{ 
				Label::bookmark(toc, l);
				Label::increment(toc, l);
			}

			template<typename AST>
			nik_ces void resolve_statement(AST & toc, clexeme & l)
			{
				toc.increment_line();
				toc.update_copy_paste();
			}

			template<typename AST>
			nik_ces void resolve_quote(AST & toc, clexeme & l)
				{ } // nothing yet.

			template<typename AST>
			nik_ces void resolve_accept(AST & toc, clexeme & l)
			{
				Accept::link(toc, toc.go_to);
				Accept::link(toc, toc.branch);
			}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// nonterminal recovery:

/***********************************************************************************************************************/

// action:

	struct T_generic_assembly_nrta
	{
		template<typename AST, typename Stack>
		using signature = void(*)(AST&, clexeme&, Stack&);

		template<typename AST, typename Stack>
		nik_ces void err(AST & toc, clexeme & l, Stack & s) { }

		template<typename AST, typename Stack> // should confirm "Jgi;" is the current stack front.
		nik_ces void instr_label(AST & toc, clexeme & l, Stack & s)
		{
			s.pop();

			*(s.current    ) = 'l';
			*(s.current - 1) = ';';
			*(s.current - 2) = 'E';

			T_generic_assembly_nta::new_label(toc, l);
		}

		template<typename AST, typename Stack> // should confirm "Jgi;" is the current stack front.
		nik_ces void instr_return(AST & toc, clexeme & l, Stack & s)
		{
			s.pop();

			*(s.current    ) = 'r';
			*(s.current - 1) = 'M';

			T_generic_assembly_nta::new_return(toc, l);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// terminal recovery:

/***********************************************************************************************************************/

// action:

	struct T_generic_assembly_trta
	{
		template<typename AST, typename Stack>
		using signature = void(*)(AST&, clexeme&, Stack&);

		template<typename AST, typename Stack>
		nik_ces void err(AST & toc, clexeme & l, Stack & s) { }

		template<typename AST, typename Stack>
		nik_ces void assign_to_apply(AST & toc, clexeme & l, Stack & s)
		{
			if (toc.kind() == Context::assign) // can assume "#M;" is the current stack front:
			{
				toc.set_kind(Context::apply);

				*(s.current    ) = 'M';
				*(s.current - 1) = 'V';

				s.push("=", _one);
			}
			// else ; // error
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// interface:

/***********************************************************************************************************************/

	template<typename AST, typename Stack>
	struct T_generic_assembly_ta
	{
		using NTA		= T_generic_assembly_nta;
		using n_action_type	= typename NTA::template signature<AST>;
		using NAction		= typename T_generic_assembly_pdtt::NAction;

		using TTA		= T_generic_assembly_tta;
		using t_action_type	= typename TTA::template signature<AST>;
		using TAction		= typename T_generic_assembly_pdtt::TAction;

		using NRTA		= T_generic_assembly_nrta;
		using nr_action_type	= typename NRTA::template signature<AST, Stack>;
		using NRAction		= typename T_generic_assembly_pdtt::NRAction;

		using TRTA		= T_generic_assembly_trta;
		using tr_action_type	= typename TRTA::template signature<AST, Stack>;
		using TRAction		= typename T_generic_assembly_pdtt::TRAction;

		 n_action_type  n_array[ NAction::dimension];
		 t_action_type  t_array[ TAction::dimension];
		nr_action_type nr_array[NRAction::dimension];
		tr_action_type tr_array[TRAction::dimension];

		nik_ce T_generic_assembly_ta() : n_array{}, t_array{}, nr_array{}, tr_array{}
		{
			n_array [ NAction::err             ] = NTA::template err             <AST>;
			n_array [ NAction::nop             ] = NTA::template nop             <AST>;
			n_array [ NAction::new_definition  ] = NTA::template new_definition  <AST>;
			n_array [ NAction::new_def_arg     ] = NTA::template new_def_arg     <AST>;
			n_array [ NAction::new_def_end     ] = NTA::template new_def_end     <AST>;
			n_array [ NAction::new_label       ] = NTA::template new_label       <AST>;
			n_array [ NAction::new_goto        ] = NTA::template new_goto        <AST>;
			n_array [ NAction::new_assignment  ] = NTA::template new_assignment  <AST>;
			n_array [ NAction::new_application ] = NTA::template new_application <AST>;
			n_array [ NAction::new_conditional ] = NTA::template new_conditional <AST>;
			n_array [ NAction::new_jvalue      ] = NTA::template new_jvalue      <AST>;
			n_array [ NAction::new_mvalue      ] = NTA::template new_mvalue      <AST>;
			n_array [ NAction::new_lvalue      ] = NTA::template new_lvalue      <AST>;
			n_array [ NAction::new_rvalue      ] = NTA::template new_rvalue      <AST>;
			n_array [ NAction::new_copy        ] = NTA::template new_copy        <AST>;
			n_array [ NAction::new_paste       ] = NTA::template new_paste       <AST>;
			n_array [ NAction::new_return      ] = NTA::template new_return      <AST>;
			n_array [ NAction::new_quote       ] = NTA::template new_quote       <AST>;

			t_array [ TAction::err                ] = TTA::template err                <AST>;
			t_array [ TAction::nop                ] = TTA::template nop                <AST>;
			t_array [ TAction::resolve_identifier ] = TTA::template resolve_identifier <AST>;
			t_array [ TAction::resolve_void       ] = TTA::template resolve_void       <AST>;
			t_array [ TAction::resolve_paste      ] = TTA::template resolve_paste      <AST>;
			t_array [ TAction::resolve_copy       ] = TTA::template resolve_copy       <AST>;
			t_array [ TAction::resolve_test       ] = TTA::template resolve_test       <AST>;
			t_array [ TAction::resolve_branch     ] = TTA::template resolve_branch     <AST>;
			t_array [ TAction::resolve_goto       ] = TTA::template resolve_goto       <AST>;
			t_array [ TAction::resolve_label      ] = TTA::template resolve_label      <AST>;
			t_array [ TAction::resolve_statement  ] = TTA::template resolve_statement  <AST>;
			t_array [ TAction::resolve_quote      ] = TTA::template resolve_quote      <AST>;
			t_array [ TAction::resolve_accept     ] = TTA::template resolve_accept     <AST>;

			nr_array [ NRAction::err          ] = NRTA::template err          <AST, Stack>;
			nr_array [ NRAction::instr_label  ] = NRTA::template instr_label  <AST, Stack>;
			nr_array [ NRAction::instr_return ] = NRTA::template instr_return <AST, Stack>;

			tr_array [ TRAction::err             ] = TRTA::template err             <AST, Stack>;
			tr_array [ TRAction::assign_to_apply ] = TRTA::template assign_to_apply <AST, Stack>;
		}

		nik_ce const  n_action_type nonterminal          (gcindex_type pos) const { return  n_array[pos]; }
		nik_ce const  t_action_type    terminal          (gcindex_type pos) const { return  t_array[pos]; }
		nik_ce const nr_action_type nonterminal_recovery (gcindex_type pos) const { return nr_array[pos]; }
		nik_ce const tr_action_type    terminal_recovery (gcindex_type pos) const { return tr_array[pos]; }
	};

	// interface:

		template<typename AST, typename Stack>
		struct T_generic_assembly_translator
		{
			nik_ces auto value = T_generic_assembly_ta<AST, Stack>{};
			using type         = decltype(value);
		};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

