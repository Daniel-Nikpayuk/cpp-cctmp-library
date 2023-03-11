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
		nik_ces void nop(AST & toc, clexeme & l) { }

		template<typename AST>
		nik_ces void new_definition(AST & toc, clexeme & l)
			{ toc.set_kind(Context::define); }

		template<typename AST>
		nik_ces void new_coordinate(AST & toc, clexeme & l)
			{ toc.set_kind(Context::label); }

		template<typename AST>
		nik_ces void new_conditional(AST & toc, clexeme & l)
			{ toc.set_kind(Context::test); }

		template<typename AST>
		nik_ces void new_application(AST & toc, clexeme & l)
			{ toc.set_kind(Context::apply); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// terminal:

/***********************************************************************************************************************/

// (context) define:

	struct T_generic_assembly_tta_context_define
	{
		// identifier:

			template<typename AST>
			nik_ces void identifier_entry(AST & toc, clexeme & l)
				{ toc.set_current_entry(l, Sign::carg); }

		// statement (end of line):

			template<typename AST>
			nik_ces void statement_first(AST & toc)
				{ toc.set_current_sign_at(_zero, Sign::na); }

			template<typename AST>
			nik_ces void statement_rest(AST & toc)
			{
				auto line = toc.page.line;

				for (auto k = line->array + 1; k != line->end(); ++k)
				{
					k->index = toc.arg_index;
					toc.increment_arg_index();
				}
			}

			template<typename AST>
			nik_ces void statement_entry(AST & toc, clexeme & l)
			{
				statement_first(toc);
				statement_rest(toc);
			}
	};

/***********************************************************************************************************************/

// (context) apply:

	struct T_generic_assembly_tta_context_apply
	{
		// identifier:

			template<typename AST>
			nik_ces void identifier_arg(AST & toc, clexeme & l, gcindex_type index)
			{
				auto sign  = toc.has_side() ? Sign::marg : Sign::carg;
				auto shift = toc.has_paste() ? _one : _zero;

				toc.unset_side();
				toc.set_current_entry(l, sign, index + shift);
			}

			template<typename AST>
			nik_ces void identifier_lookup(AST & toc, clexeme & l)
			{
				auto j = toc.match_name(l.start, l.finish);
				auto s = j ? Sign::recurse : Sign::lookup;

				toc.update_lookup();
				toc.set_current_entry(l, s);
			}

			template<typename AST>
			nik_ces void identifier_entry(AST & toc, clexeme & l)
			{
				auto k = toc.match_arguments(l.start, l.finish);
				if (toc.is_arg_match(k)) identifier_arg(toc, l, k->index);
				else identifier_lookup(toc, l);
			}

		// copy:

			template<typename AST>
			nik_ces void copy_entry(AST & toc, clexeme & l)
			{
				toc.set_current_entry(l, Sign::copy);
				toc.set_copy();
			}

		// paste:

			template<typename AST>
			nik_ces void paste_entry(AST & toc, clexeme & l)
				{ toc.set_current_entry(l, Sign::paste); }

		// statement (end of line):

			template<typename AST>
			nik_ces void statement_first_index(AST & toc)
			{
				if (toc.has_paste())
				{
					auto shift = toc.current_index_at(_zero) - 1;

					toc.set_current_index_at(_zero, shift);
				}
			}

			template<typename AST>
			nik_ces void statement_first_void(AST & toc)
				{ toc.set_void(); }

			template<typename AST>
			nik_ces void statement_first_variable(AST & toc)
			{
				toc.set_current_sign_at(_zero, Sign::var);
				toc.set_current_index_at(_zero, toc.arg_index);

				toc.set_arg_start(toc.current_start_at(_zero));
				toc.set_arg_finish(toc.current_finish_at(_zero));
				toc.set_arg_sign(Sign::carg);
				toc.set_arg_index(toc.arg_index);

				toc.increment_arg_index();
				toc.increment_arg_entry();
			}

			template<typename AST>
			nik_ces void statement_first(AST & toc)
			{
				auto sign = toc.current_sign_at(_zero);

				if (Sign::is_carg(sign)) statement_first_index(toc);
				if (Sign::is_marg(sign)) statement_first_void(toc);
				else if (Sign::is_lookup(sign)) statement_first_variable(toc);
			}

			template<typename AST>
			nik_ces void statement_second_arg_op(AST & toc)
				{ toc.set_arg_op(); }

			template<typename AST>
			nik_ces void statement_second(AST & toc)
			{
				auto sign = toc.current_sign_at(_one);

				if (Sign::is_carg(sign)) statement_second_arg_op(toc);
			}

			template<typename AST>
			nik_ces void statement_entry(AST & toc, clexeme & l)
			{
				statement_first(toc);
				statement_second(toc);
			}
	};

/***********************************************************************************************************************/

// (context) re_turn:

	struct T_generic_assembly_tta_context_return
	{
		// identifier:

			template<typename AST>
			nik_ces void identifier_entry(AST & toc, clexeme & l)
			{
				auto k = toc.match_arguments(l.start, l.finish);
				if (toc.is_arg_match(k)) toc.set_current_entry(l, Sign::carg, k->index);
				else
				{
					toc.update_lookup(); // can assume at most one lookup.
					toc.set_current_entry(l, Sign::lookup);
				}
			}

		// paste:

			template<typename AST>
			nik_ces void paste_entry(AST & toc, clexeme & l)
				{ toc.set_current_entry(l, Sign::paste); }
	};

/***********************************************************************************************************************/

// (context) test:

	struct T_generic_assembly_tta_context_test
	{
		using Application = T_generic_assembly_tta_context_apply;

		template<typename AST>
		nik_ces void set(AST & toc, clexeme & l)
			{ toc.set_current_entry(l, Sign::copy); }

		template<typename AST>
		nik_ces void increment(AST & toc, clexeme & l)
			{ toc.increment_entry(); }

		// identifier:

			template<typename AST>
			nik_ces void identifier_entry(AST & toc, clexeme & l)
				{ Application::identifier_entry(toc, l); }

		// paste:

			template<typename AST>
			nik_ces void paste_entry(AST & toc, clexeme & l)
				{ toc.set_current_entry(l, Sign::paste); }

		// statement (end of line):

			template<typename AST>
			nik_ces void statement_entry(AST & toc, clexeme & l)
				{ Application::statement_second(toc); }
	};

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

		// identifier:

			template<typename AST>
			nik_ces void identifier_entry(AST & toc, clexeme & l)
				{ toc.set_current_entry(l, Sign::jump); }
	};

/***********************************************************************************************************************/

// (context) go_to:

	struct T_generic_assembly_tta_context_goto
	{
		template<typename AST>
		nik_ces void set(AST & toc, clexeme & l)
			{ toc.set_kind(Context::go_to); }

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

		// identifier:

			template<typename AST>
			nik_ces void identifier_entry(AST & toc, clexeme & l)
				{ toc.set_current_entry(l, Sign::jump); }
	};

/***********************************************************************************************************************/

// (context) label:

	struct T_generic_assembly_tta_context_label
	{
		template<typename AST>
		nik_ces void set(AST & toc, clexeme & l)
			{ toc.set_current_entry(l, Sign::label, toc.label_index++); }

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

		using Definition	= T_generic_assembly_tta_context_define;
		using Application	= T_generic_assembly_tta_context_apply;
		using Return		= T_generic_assembly_tta_context_return;
		using Test		= T_generic_assembly_tta_context_test;
		using Branch		= T_generic_assembly_tta_context_branch;
		using Goto		= T_generic_assembly_tta_context_goto;
		using Label		= T_generic_assembly_tta_context_label;
		using Accept		= T_generic_assembly_tta_context_accept;

		template<typename AST>
		nik_ces void nop(AST & toc, clexeme & l) { }

		// resolve:

			template<typename AST>
			nik_ces void resolve_identifier(AST & toc, clexeme & l)
			{
				switch (toc.kind())
				{
					case Context::apply   : { Application::identifier_entry (toc, l); break; }
					case Context::re_turn : { Return::identifier_entry      (toc, l); break; }
					case Context::test    : { Test::identifier_entry        (toc, l); break; }
					case Context::branch  : { Branch::identifier_entry      (toc, l); break; }
					case Context::go_to   : { Goto::identifier_entry        (toc, l); break; }
					case Context::define  : { Definition::identifier_entry  (toc, l); break; }
				}

				toc.increment_entry();
			}

			template<typename AST>
			nik_ces void resolve_mutable(AST & toc, clexeme & l)
				{ toc.set_side(); }

			template<typename AST>
			nik_ces void resolve_copy(AST & toc, clexeme & l)
			{
				switch (toc.kind())
				{
					case Context::apply : { Application::copy_entry (toc, l); break; }
				}

				toc.increment_entry();
			}

			template<typename AST>
			nik_ces void resolve_paste(AST & toc, clexeme & l)
			{
				switch (toc.kind())
				{
					case Context::apply   : { Application::paste_entry (toc, l); break; }
					case Context::test    : { Test::paste_entry        (toc, l); break; }
					case Context::re_turn : { Return::paste_entry      (toc, l); break; }
				}

				toc.increment_entry();
			}

			template<typename AST>
			nik_ces void resolve_return(AST & toc, clexeme & l)
				{ toc.set_kind(Context::re_turn); }

			template<typename AST>
			nik_ces void resolve_quote(AST & toc, clexeme & l)
				{ }

			template<typename AST>
			nik_ces void resolve_label(AST & toc, clexeme & l)
			{ 
				Label::set(toc, l);
				Label::bookmark(toc, l);
				Label::increment(toc, l);
			}

			template<typename AST>
			nik_ces void resolve_test(AST & toc, clexeme & l)
			{
				Test::set(toc, l);
				Test::increment(toc, l);
			}

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
				Goto::set(toc, l);
				Goto::bookmark(toc, l);
				Goto::increment(toc, l);
			}

			template<typename AST>
			nik_ces void resolve_statement(AST & toc, clexeme & l)
			{
				switch (toc.kind())
				{
					case Context::apply   : { Application::statement_entry (toc, l); break; }
					case Context::test    : { Test::statement_entry        (toc, l); break; }
					case Context::define  : { Definition::statement_entry  (toc, l); break; }
				}

				toc.increment_line();
				toc.update_copy_paste();
			}

			template<typename AST>
			nik_ces void resolve_accept(AST & toc, clexeme & l)
			{
				Accept::link(toc, toc.go_to);
				Accept::link(toc, toc.branch);
			}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// letter:

/***********************************************************************************************************************/

// action:

	struct T_generic_assembly_lta
	{
	//	using Application = T_generic_assembly_tta_context_apply;

		template<typename AST>
		using signature = void(*)(AST&); // needs to be updated.

		template<typename AST>
		nik_ces void parse_repeat(AST & toc)
		{
		//	Application::identifier_entry(toc, l);
		//	toc.repeat_options(toc, s);
		}

		template<typename AST>
		nik_ces void parse_map(AST & toc)
		{
		//	Application::identifier_entry(toc, l);
		//	toc.map_options(toc, s);
		}

		template<typename AST>
		nik_ces void parse_fold(AST & toc)
		{
		//	Application::identifier_entry(toc, l);
		//	toc.fold_options(toc, s);
		}

		template<typename AST>
		nik_ces void parse_find_first(AST & toc)
		{
		//	Application::identifier_entry(toc, l);
		//	toc.find_first_options(toc, s);
		}

		template<typename AST>
		nik_ces void parse_find_all(AST & toc)
		{
		//	Application::identifier_entry(toc, l);
		//	toc.find_all_options(toc, s);
		}

		template<typename AST>
		nik_ces void parse_zip(AST & toc)
		{
		//	Application::identifier_entry(toc, l);
		//	toc.zip_options(toc, s);
		}

		template<typename AST>
		nik_ces void parse_fasten(AST & toc)
		{
		//	Application::identifier_entry(toc, l);
		//	toc.fasten_options(toc, s);
		}

		template<typename AST>
		nik_ces void parse_glide(AST & toc)
		{
		//	Application::identifier_entry(toc, l);
		//	toc.glide_options(toc, s);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// stack:

/***********************************************************************************************************************/

// action:

	struct T_generic_assembly_sta
	{
		template<typename AST, typename Stack>
		using signature = void(*)(AST&, clexeme&, Stack&);

		template<typename AST, typename Stack> // can assume "gi;" is the current stack front.
		nik_ces void instr_label(AST & toc, clexeme & l, Stack & s)
		{
			*(s.current    ) = 'l';
			*(s.current - 1) = ';';
			*(s.current - 2) = 'E';

			T_generic_assembly_nta::new_coordinate(toc, l);
		}

		template<typename AST, typename Stack> // can assume "gi;" is the current stack front.
		nik_ces void instr_return(AST & toc, clexeme & l, Stack & s)
		{
			*(s.current    ) = 'r';
			*(s.current - 1) = 'M';
			*(s.current - 2) = ';';
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

		using LTA		= T_generic_assembly_lta;
		using l_action_type	= typename LTA::template signature<AST>;
		using LAction		= typename T_generic_assembly_pdtt::LAction;

		using STA		= T_generic_assembly_sta;
		using s_action_type	= typename STA::template signature<AST, Stack>;
		using SAction		= typename T_generic_assembly_pdtt::SAction;

		n_action_type n_array[NAction::dimension];
		t_action_type t_array[TAction::dimension];
		l_action_type l_array[LAction::dimension];
		s_action_type s_array[SAction::dimension];

		nik_ce T_generic_assembly_ta() : n_array{}, t_array{}, l_array{}, s_array{}
		{
			n_array[ NAction::nop                ] = NTA::template nop                <AST>;
			n_array[ NAction::new_definition     ] = NTA::template new_definition     <AST>;
			n_array[ NAction::new_coordinate     ] = NTA::template new_coordinate     <AST>;
			n_array[ NAction::new_conditional    ] = NTA::template new_conditional    <AST>;
			n_array[ NAction::new_application    ] = NTA::template new_application    <AST>;

			t_array[ TAction::nop                ] = TTA::template nop                <AST>;
			t_array[ TAction::resolve_identifier ] = TTA::template resolve_identifier <AST>;
			t_array[ TAction::resolve_mutable    ] = TTA::template resolve_mutable    <AST>;
			t_array[ TAction::resolve_paste      ] = TTA::template resolve_paste      <AST>;
			t_array[ TAction::resolve_copy       ] = TTA::template resolve_copy       <AST>;
			t_array[ TAction::resolve_test       ] = TTA::template resolve_test       <AST>;
			t_array[ TAction::resolve_branch     ] = TTA::template resolve_branch     <AST>;
			t_array[ TAction::resolve_goto       ] = TTA::template resolve_goto       <AST>;
			t_array[ TAction::resolve_return     ] = TTA::template resolve_return     <AST>;
			t_array[ TAction::resolve_label      ] = TTA::template resolve_label      <AST>;
			t_array[ TAction::resolve_statement  ] = TTA::template resolve_statement  <AST>;
			t_array[ TAction::resolve_quote      ] = TTA::template resolve_quote      <AST>;
		//	t_array[ TAction::resolve_repeat     ] = TTA::template resolve_repeat     <AST>;
		//	t_array[ TAction::resolve_map        ] = TTA::template resolve_map        <AST>;
		//	t_array[ TAction::resolve_fold       ] = TTA::template resolve_fold       <AST>;
		//	t_array[ TAction::resolve_find_first ] = TTA::template resolve_find_first <AST>;
		//	t_array[ TAction::resolve_find_all   ] = TTA::template resolve_find_all   <AST>;
		//	t_array[ TAction::resolve_zip        ] = TTA::template resolve_zip        <AST>;
		//	t_array[ TAction::resolve_fasten     ] = TTA::template resolve_fasten     <AST>;
		//	t_array[ TAction::resolve_glide      ] = TTA::template resolve_glide      <AST>;
			t_array[ TAction::resolve_accept     ] = TTA::template resolve_accept     <AST>;

			l_array[ LAction::parse_repeat       ] = LTA::template parse_repeat       <AST>;
			l_array[ LAction::parse_map          ] = LTA::template parse_map          <AST>;
			l_array[ LAction::parse_fold         ] = LTA::template parse_fold         <AST>;
			l_array[ LAction::parse_find_first   ] = LTA::template parse_find_first   <AST>;
			l_array[ LAction::parse_find_all     ] = LTA::template parse_find_all     <AST>;
			l_array[ LAction::parse_zip          ] = LTA::template parse_zip          <AST>;
			l_array[ LAction::parse_fasten       ] = LTA::template parse_fasten       <AST>;
			l_array[ LAction::parse_glide        ] = LTA::template parse_glide        <AST>;

			s_array[ SAction::instr_label        ] = STA::template instr_label        <AST, Stack>;
			s_array[ SAction::instr_return       ] = STA::template instr_return       <AST, Stack>;
		}

		nik_ce const n_action_type nonterminal_action(gcindex_type pos) const { return n_array[pos]; }
		nik_ce const t_action_type    terminal_action(gcindex_type pos) const { return t_array[pos]; }
		nik_ce const l_action_type      letter_action(gcindex_type pos) const { return l_array[pos]; }
		nik_ce const s_action_type       stack_action(gcindex_type pos) const { return s_array[pos]; }
	};

	// interface:

		template<typename AST, typename Stack>
		struct T_generic_assembly_translator { nik_ces auto value = T_generic_assembly_ta<AST, Stack>{}; };

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

