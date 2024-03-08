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

// cycle action:

namespace chord {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// cycle action:

/***********************************************************************************************************************/

// routine:

	template<auto... filler>
	struct T_chord_translation_action<CAAN::cyc_rout_begin, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->force_define_compound(t->replace.name());
			t->force_define_arity();
			t->define_op_begin();
			t->internal_defs_begin();
		}
	};

	template<auto... filler>
	struct T_chord_translation_action<CAAN::cyc_rout_end, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->act_subpose_end(); }
	};

	template<auto... filler>
	struct T_chord_translation_action<CAAN::cyc_rout_op, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->act_subpose_op(l->left_cselect()); }
	};

	template<auto... filler>
	struct T_chord_translation_action<CAAN::cyc_rout_value, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->subpose_value(l->left_cselect()); }
	};

/***********************************************************************************************************************/

// combine:

	template<auto... filler>
	struct T_chord_translation_action<CAAN::cyc_combine, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			nik_ce auto arity = 2;

			t->set_combine();
			t->act_subpose_begin(arity);
		}
	};

	template<auto... filler>
	struct T_chord_translation_action<CAAN::cyc_combine_rest2, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->subpose_value(t->cselect_deref());
			t->subpose_value(t->cselect_deref());
		}
	};

	template<auto... filler>
	struct T_chord_translation_action<CAAN::cyc_combine_rest1, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->subpose_value(t->cselect_deref());
		}
	};

/***********************************************************************************************************************/

// action:

	template<auto... filler>
	struct T_chord_translation_action<CAAN::cyc_action, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->set_action();
			t->act_subpose_begin(t->pound.arity());
		}
	};

	template<auto... filler>
	struct T_chord_translation_action<CAAN::cyc_action_defs, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->set_action();
			t->act_subpose_begin(t->pound.arity());
			t->act_subpose_op(t->cselect_first());
			t->act_subpose_values(t->cselect_deref(), 0, t->pound.arity());
		}
	};

	template<auto... filler>
	struct T_chord_translation_action<CAAN::cyc_action_rest, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->act_subpose_values(t->cselect_deref(), t->count.size(), t->pound.arity());
		}
	};

/***********************************************************************************************************************/

// mutate:

	template<auto... filler>
	struct T_chord_translation_action<CAAN::cyc_mutate, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			nik_ce auto arity = 2;

			t->set_mutate();
			t->act_subpose_begin(arity);
		}
	};

	template<auto... filler>
	struct T_chord_translation_action<CAAN::cyc_mutate_defs, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			nik_ce auto arity = 2;
			nik_ce bool mute  = true;

			t->set_mutate();
			t->act_subpose_begin(arity);
			t->act_subpose_op(t->cselect_appoint());
			t->subpose_value(t->cselect_id(), mute);
			t->subpose_value(t->cselect_id());
		}
	};

	template<auto... filler>
	struct T_chord_translation_action<CAAN::cyc_mutate_rest2, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->subpose_value(t->cselect_deref());
			t->subpose_value(t->cselect_id());
		}
	};

	template<auto... filler>
	struct T_chord_translation_action<CAAN::cyc_mutate_rest1, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->subpose_value(t->cselect_id());
		}
	};

/***********************************************************************************************************************/

// predicate:

	template<auto... filler>
	struct T_chord_translation_action<CAAN::cyc_predicate, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			nik_ce auto arity = 2;

			t->set_predicate();
			t->act_subpose_begin(arity);
		}
	};

	template<auto... filler>
	struct T_chord_translation_action<CAAN::cyc_predicate_defs, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			nik_ce auto arity = 2;

			t->set_predicate();
			t->act_subpose_begin(arity);
			t->act_subpose_op(t->cselect_not_equal());
			t->act_subpose_values(t->cselect_id());
		}
	};

	template<auto... filler>
	struct T_chord_translation_action<CAAN::cyc_predicate_rest2, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->subpose_value(t->cselect_id());
			t->subpose_value(t->cselect_id());
		}
	};

	template<auto... filler>
	struct T_chord_translation_action<CAAN::cyc_predicate_rest1, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->subpose_value(t->cselect_id());
		}
	};

/***********************************************************************************************************************/

// interval:

	template<auto... filler>
	struct T_chord_translation_action<CAAN::cyc_ival_left_closed, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->interval.upsize();
			t->interval.last()->set_left_closed();
		}
	};

	template<auto... filler>
	struct T_chord_translation_action<CAAN::cyc_ival_left_open, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->interval.upsize();
			t->interval.last()->set_left_open();
		}
	};

	template<auto... filler>
	struct T_chord_translation_action<CAAN::cyc_ival_right_closed, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->interval.last()->set_right_closed(); }
	};

	template<auto... filler>
	struct T_chord_translation_action<CAAN::cyc_ival_right_open, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->interval.last()->set_right_open(); }
	};

	template<auto... filler>
	struct T_chord_translation_action<CAAN::cyc_ival_fixed, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->interval.upsize();
			t->interval.last()->set_fixed();
		}
	};

/***********************************************************************************************************************/

// iterator:

	template<auto... filler>
	struct T_chord_translation_action<CAAN::cyc_iter_inc_dec, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ }
	};

	template<auto... filler>
	struct T_chord_translation_action<CAAN::cyc_iter_dec_inc, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->push_dec();
			t->push_inc();
		}
	};

	template<auto... filler>
	struct T_chord_translation_action<CAAN::cyc_iter_upsize, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ }
	};

	template<auto... filler>
	struct T_chord_translation_action<CAAN::cyc_iter_pair, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->push_inc();
			t->push_dec();
		}
	};

	template<auto... filler>
	struct T_chord_translation_action<CAAN::cyc_iter_none, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ }
	};

	template<auto... filler>
	struct T_chord_translation_action<CAAN::cyc_iter_value, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ }
	};

	template<auto... filler>
	struct T_chord_translation_action<CAAN::cyc_iter_void, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ }
	};

/***********************************************************************************************************************/

// tonic:

	template<auto... filler>
	struct T_chord_translation_action<CAAN::cyc_tonic_inc_dec, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ }
	};

	template<auto... filler>
	struct T_chord_translation_action<CAAN::cyc_tonic_dec_inc, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ }
	};

	template<auto... filler>
	struct T_chord_translation_action<CAAN::cyc_tonic_pair, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->push_tonic(); }
	};

	template<auto... filler>
	struct T_chord_translation_action<CAAN::cyc_tonic_none, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ }
	};

	template<auto... filler>
	struct T_chord_translation_action<CAAN::cyc_tonic_value, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ }
	};

	template<auto... filler>
	struct T_chord_translation_action<CAAN::cyc_tonic_void, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ }
	};

/***********************************************************************************************************************/

// compose:

	template<auto... filler>
	struct T_chord_translation_action<CAAN::cyc_comp_repeat, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->define_repeat();
			t->define_op_end();
		}
	};

	template<auto... filler>
	struct T_chord_translation_action<CAAN::cyc_comp_map, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->define_map();
			t->define_op_end();
		}
	};

	template<auto... filler>
	struct T_chord_translation_action<CAAN::cyc_comp_fold, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->define_fold();
			t->define_op_end();
		}
	};

	template<auto... filler>
	struct T_chord_translation_action<CAAN::cyc_comp_find, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->define_find();
			t->define_op_end();
		}
	};

	template<auto... filler>
	struct T_chord_translation_action<CAAN::cyc_comp_sift, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->define_sift();
			t->define_op_end();
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace chord

