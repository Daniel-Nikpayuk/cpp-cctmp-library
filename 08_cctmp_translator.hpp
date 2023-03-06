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

	struct T_generic_assembly_ntta
	{
		template<typename AST, typename Stack>
		using signature = void(*)(AST &, clexeme &, Stack &);

		template<typename AST, typename Stack>
		nik_ces void nop(AST & toc, clexeme & l, Stack & s) { }

		template<typename AST, typename Stack>
		nik_ces void new_definition(AST & toc, clexeme & l, Stack & s)
			{ toc.set_kind(Context::define); }

		template<typename AST, typename Stack>
		nik_ces void new_coordinate(AST & toc, clexeme & l, Stack & s)
			{ toc.set_kind(Context::label); }

		template<typename AST, typename Stack>
		nik_ces void new_conditional(AST & toc, clexeme & l, Stack & s)
			{ toc.set_kind(Context::test); }

		template<typename AST, typename Stack>
		nik_ces void new_application(AST & toc, clexeme & l, Stack & s)
			{ toc.set_kind(Context::apply); }

		template<typename AST, typename Stack> // can assume "gi;" is the current stack front.
		nik_ces void recover_instr_label(AST & toc, clexeme & l, Stack & s)
		{
			*(s.current    ) = 'l';
			*(s.current - 1) = ';';
			*(s.current - 2) = 'E';

			new_coordinate(toc, l, s);
		}

		template<typename AST, typename Stack> // can assume "gi;" is the current stack front.
		nik_ces void recover_instr_return(AST & toc, clexeme & l, Stack & s)
		{
			*(s.current    ) = 'r';
			*(s.current - 1) = 'M';
			*(s.current - 2) = ';';
		}
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
		template<typename AST, typename Stack>
		using signature = void(*)(AST &, clexeme &);

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

// interface:

/***********************************************************************************************************************/

	template<typename AST, typename Stack>
	struct T_generic_assembly_ta
	{
		using NTTA			= T_generic_assembly_ntta;
		using nonterminal_type		= typename NTTA::template signature<AST, Stack>;
		using TTA			= T_generic_assembly_tta;
		using terminal_type		= typename TTA::template signature<AST, Stack>;
		using NAction			= typename T_generic_assembly_pdtt::NAction;
		using TAction			= typename T_generic_assembly_pdtt::TAction;

		nonterminal_type nonterminal[NAction::dimension];
		   terminal_type    terminal[TAction::dimension];

		nik_ce T_generic_assembly_ta() : nonterminal{}, terminal{}
		{
			nonterminal[ NAction::nop                  ] = NTTA::template nop                  <AST, Stack>;
			nonterminal[ NAction::new_definition       ] = NTTA::template new_definition       <AST, Stack>;
			nonterminal[ NAction::new_coordinate       ] = NTTA::template new_coordinate       <AST, Stack>;
			nonterminal[ NAction::new_conditional      ] = NTTA::template new_conditional      <AST, Stack>;
			nonterminal[ NAction::new_application      ] = NTTA::template new_application      <AST, Stack>;
			nonterminal[ NAction::recover_instr_label  ] = NTTA::template recover_instr_label  <AST, Stack>;
			nonterminal[ NAction::recover_instr_return ] = NTTA::template recover_instr_return <AST, Stack>;

			terminal[ TAction::nop                ] = TTA::template nop                <AST>;
			terminal[ TAction::resolve_identifier ] = TTA::template resolve_identifier <AST>;
			terminal[ TAction::resolve_mutable    ] = TTA::template resolve_mutable    <AST>;
			terminal[ TAction::resolve_paste      ] = TTA::template resolve_paste      <AST>;
			terminal[ TAction::resolve_copy       ] = TTA::template resolve_copy       <AST>;
			terminal[ TAction::resolve_test       ] = TTA::template resolve_test       <AST>;
			terminal[ TAction::resolve_branch     ] = TTA::template resolve_branch     <AST>;
			terminal[ TAction::resolve_goto       ] = TTA::template resolve_goto       <AST>;
			terminal[ TAction::resolve_return     ] = TTA::template resolve_return     <AST>;
			terminal[ TAction::resolve_label      ] = TTA::template resolve_label      <AST>;
			terminal[ TAction::resolve_statement  ] = TTA::template resolve_statement  <AST>;
			terminal[ TAction::resolve_quote      ] = TTA::template resolve_quote      <AST>;
			terminal[ TAction::resolve_accept     ] = TTA::template resolve_accept     <AST>;
		}

		nik_ce nonterminal_type nonterminal_action(gcindex_type pos) const { return nonterminal[pos]; }
		nik_ce    terminal_type    terminal_action(gcindex_type pos) const { return    terminal[pos]; }
	};

	// interface:

		template<typename AST, typename Stack>
		struct T_generic_assembly_translator { nik_ces auto value = T_generic_assembly_ta<AST, Stack>{}; };

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

