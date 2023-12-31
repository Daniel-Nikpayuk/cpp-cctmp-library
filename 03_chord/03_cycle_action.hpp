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

// cycle action:

namespace chord {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// subpose:

	// begin:

		struct T_cyc_subpose_begin
		{
			template<typename AST>
			nik_ces void result(AST *t)
			{
				t->contr.push_machine();
				t->cycle.subroutine().push_subcontr(t->contr.instr_at());
				t->cycle.subroutine().push_compound(t->pound.allocate());

				T_subpose_begin::template result<AST>(t);
			}
		};

	// end:

		struct T_cyc_subpose_end
		{
			template<typename AST>
			nik_ces void result(AST *t)
			{
				T_subpose_end::template result<AST>(t);
				t->contr.pop_machine();
			}
		};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// cycle:

/***********************************************************************************************************************/

// default argop:

	template<gindex_type start, gindex_type finish>
	struct T_cyc_def_argop
	{
		template<typename AST>
		nik_ces void result(AST *t)
		{
			auto aux_at = t->contr.aux_at;
			auto arg_at = t->line.sub_at();
			t->line.inc_sub();

			t->template chain_action< CAN::generic , CAT::lookup >(CT::pull, aux_at, start, finish);
			t->template chain_action< CAN::generic , CAT::arg    >(CT::push, arg_at);
		}
	};

	using T_cyc_id_argop      = T_cyc_def_argop< T_def_subsrc::id_start      , T_def_subsrc::id_finish      >;
	using T_cyc_deref_argop   = T_cyc_def_argop< T_def_subsrc::deref_start   , T_def_subsrc::deref_finish   >;
	using T_cyc_appoint_argop = T_cyc_def_argop< T_def_subsrc::appoint_start , T_def_subsrc::appoint_finish >;
	using T_cyc_equal_argop   = T_cyc_def_argop< T_def_subsrc::equal_start   , T_def_subsrc::equal_finish   >;

// option:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::cyc_option_amp, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l) // ast alignment with camp:
		{
			t->cycle.subroutine().push_subcontr(_zero);
			t->cycle.subroutine().push_compound(_zero);
		}
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::cyc_option_cont, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			T_cyc_subpose_end::template result<AST>(t);
			T_cyc_subpose_begin::template result<AST>(t);
		}
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::cyc_option_begin, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ T_cyc_subpose_begin::template result<AST>(t); }
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::cyc_option_end, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ T_cyc_subpose_end::template result<AST>(t); }
	};

// op, val:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::cyc_op_value, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->copy_op(l->left_cselect());

			t->capture_op();
		}
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::cyc_value, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->copy_val(l->left_cselect());

			t->capture_argop();
			t->paste_argop();
		}
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::cyc_id, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ T_cyc_id_argop::template result<AST>(t); }
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::cyc_deref, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ T_cyc_deref_argop::template result<AST>(t); }
	};

// combine:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::cyc_combine_rest2, filler...>
	{
		using T_cyc_combine_rest1 = T_chord_assembly_translation_action<CAAN::cyc_combine_rest1, filler...>;

		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			T_cyc_deref_argop::template result<AST>(t);
			T_cyc_combine_rest1::template result<AST>(t, l);
		}
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::cyc_combine_rest1, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ T_cyc_id_argop::template result<AST>(t); }
	};

// action:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::cyc_action_defs, filler...>
	{
		using T_cyc_action_rest = T_chord_assembly_translation_action<CAAN::cyc_action_rest, filler...>;

		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			T_cyc_deref_argop::template result<AST>(t);
			T_cyc_action_rest::template result<AST>(t, l);
		}
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::cyc_action_rest, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			auto pound = t->pound[t->cycle.clast()->compound_at()];
			auto arity = pound.arity();

			for (auto k = 0; k != arity + 1; ++k)
				T_cyc_deref_argop::template result<AST>(t);
		}
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::cyc_action_op_value, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->copy_op(l->left_cselect());

			t->capture_op();
		}
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::cyc_action_op_id, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ }
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::cyc_action_op_deref, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ }
	};

// mutate:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::cyc_mutate_defs, filler...>
	{
		using T_cyc_mutate_rest2 = T_chord_assembly_translation_action<CAAN::cyc_mutate_rest2, filler...>;

		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			T_cyc_appoint_argop::template result<AST>(t);
			T_cyc_mutate_rest2::template result<AST>(t, l);
		}
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::cyc_mutate_rest2, filler...>
	{
		using T_cyc_mutate_rest1 = T_chord_assembly_translation_action<CAAN::cyc_mutate_rest1, filler...>;

		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			T_cyc_id_argop::template result<AST>(t);
			T_cyc_mutate_rest1::template result<AST>(t, l);
		}
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::cyc_mutate_rest1, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ T_cyc_id_argop::template result<AST>(t); }
	};

// predicate:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::cyc_predicate_defs, filler...>
	{
		using T_cyc_predicate_rest2 = T_chord_assembly_translation_action<CAAN::cyc_predicate_rest2, filler...>;

		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			T_cyc_equal_argop::template result<AST>(t);
			T_cyc_predicate_rest2::template result<AST>(t, l);
		}
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::cyc_predicate_rest2, filler...>
	{
		using T_cyc_predicate_rest1 = T_chord_assembly_translation_action<CAAN::cyc_predicate_rest1, filler...>;

		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			T_cyc_id_argop::template result<AST>(t);
			T_cyc_predicate_rest1::template result<AST>(t, l);
		}
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::cyc_predicate_rest1, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ T_cyc_id_argop::template result<AST>(t); }
	};

// interval:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::cyc_ival_left_closed, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ }
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::cyc_ival_left_open, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ }
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::cyc_ival_right_closed, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ }
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::cyc_ival_right_open, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ }
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::cyc_ival_fixed, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ }
	};

// iterator:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::cyc_iter_inc_dec, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ }
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::cyc_iter_dec_inc, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ }
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::cyc_iter_upsize, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ }
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::cyc_iter_pair, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ }
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::cyc_iter_none, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ }
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::cyc_iter_value, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ }
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::cyc_iter_void, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ }
	};

// tonic:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::cyc_tonic_inc_dec, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ }
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::cyc_tonic_dec_inc, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ }
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::cyc_tonic_pair, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ }
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::cyc_tonic_none, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ }
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::cyc_tonic_value, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ }
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::cyc_tonic_void, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ }
	};

// (accept):

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::cyc_repeat, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ }
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::cyc_map, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ }
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::cyc_fold, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->template machine_action<MAN::push, MAT::id>(AN::cycle, AT::cons_f);
			t->template machine_action<MAN::pop, MAT::id>(); // debugging.
		}
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::cyc_find, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ }
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::cyc_sift, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace chord

