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

// assembly action:

namespace chord {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// machine:

	// machine (temporary?):

		using MAN					= machine::MAN;
		using MAT					= machine::MAT;

	// literal:

		using LN					= machine::LN;
		using LT					= machine::LT;
		using LAN					= machine::LAN;
		using LAT					= machine::LAT;

	// chain:

		using CN					= machine::CN;
		using CT					= machine::CT;
		using CAN					= machine::CAN;
		using CAT					= machine::CAT;

	// assembly:

		using AN					= machine::AN;
		using AT					= machine::AT;
		using AAN					= machine::AAN;
		using AAT					= machine::AAT;

// generator:

	using action_type					= generator::action_type;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// translation action:

	template<action_type, auto...> struct T_chord_assembly_translation_action;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// name:

	struct ChordAssemblyActionName
	{
		enum : action_type
		{
			nop = generator::AN::nop,

			// asm:

				asm_accept,

				// define:

					asm_define_begin, asm_define_arg, asm_define_end,

				// label:

					asm_label_begin,

				// return:

					asm_return_begin, asm_return_end,

				// goto:

					asm_goto_begin, asm_goto_value, asm_goto_end,

				// tail:

					asm_tail_begin, asm_tail_value, asm_tail_end,

				// left:

					asm_left_value, asm_left_copy,

				// swap:

					asm_swap_begin, asm_swap_end,

				// test:

					asm_test_begin, asm_test_end,

				// branch:

					asm_branch_begin, asm_branch_value, asm_branch_end,

				// void:

					asm_void_begin, asm_void_end,

				// assign:

					asm_assign_begin, asm_assign_end,

				// apply:

					asm_apply_begin, asm_apply_end,

				// sub op:

					asm_subop_value, asm_subop_paste, asm_subop_quote,

				// sub arg:

					asm_subarg_value, asm_subarg_paste, asm_subarg_quote,

				// sub mut:

					asm_mutarg_value,

				// unit value:

					asm_unit_value, asm_unit_paste, asm_unit_quote, asm_unit_morph, asm_unit_cycle,

			// morph:

				// arity:

					mor_arity_id, mor_arity_value,

				// op:

					mor_op_value, mor_op_id, mor_op_deref, mor_op_inc, mor_op_dec,

				// argpose:

					mor_argpose_begin, mor_argpose_end, mor_argpose_value,

				// subpose:

					mor_subpose_begin, mor_subpose_end, mor_subpose_value,
					mor_subpose_id, mor_subpose_deref, mor_subpose_inc, mor_subpose_dec,

				// curry:

					mor_curry_begin, mor_curry_end, mor_curry_value,

			// cycle:

				// option:

					cyc_option_amp, cyc_option_cont, cyc_option_begin, cyc_option_end,

				// op, val:

					cyc_op_value, cyc_value, cyc_id, cyc_deref,

				// combine:

					cyc_combine_rest2, cyc_combine_rest1,

				// action:

					cyc_action_defs, cyc_action_rest,
					cyc_action_op_value, cyc_action_op_id, cyc_action_op_deref,

				// mutate:

					cyc_mutate_defs, cyc_mutate_rest2, cyc_mutate_rest1,

				// predicate:

					cyc_predicate_defs, cyc_predicate_rest2, cyc_predicate_rest1,

				// interval:

					cyc_ival_left_closed, cyc_ival_left_open,
					cyc_ival_right_closed, cyc_ival_right_open, cyc_ival_fixed,

				// iterator:

					cyc_iter_inc_dec, cyc_iter_dec_inc, cyc_iter_upsize,
					cyc_iter_pair, cyc_iter_none, cyc_iter_value, cyc_iter_void,

				// tonic:

					cyc_tonic_inc_dec, cyc_tonic_dec_inc, cyc_tonic_pair,
					cyc_tonic_none, cyc_tonic_value, cyc_tonic_void,

				// (accept):

					cyc_repeat, cyc_map, cyc_fold, cyc_find, cyc_sift,

			// dimension:

				dimension
		};

	}; using CAAN = ChordAssemblyActionName;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// space:

/***********************************************************************************************************************/

// interface:

	template<typename AST>
	struct T_chord_assembly_ta :
		public generator::T_generic_translation_action<T_chord_assembly_translation_action, AST, CAAN>
			{ };

	// interface:

		template<typename AST>
		struct T_chord_assembly_action
		{
			using T_ast		= AST;

			nik_ces auto value	= T_chord_assembly_ta<AST>{};
			using type		= decltype(value);
		};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// nop:

/***********************************************************************************************************************/

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::nop, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l) { }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// asm:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// accept:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_accept, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->tag_label_jumps(); }
	};

// function:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_define_begin, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->vars.push_name(l->left_cselect());
			t->template assembly_action<AAN::begin, AAT::id>();
		}
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_define_arg, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->vars.append(l->left_cselect()); }
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_define_end, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->template assembly_action<AAN::pad, AAT::id>(t->vars.padding()); }
	};

// label:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_label_begin, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			auto sans_colon = l->left_cselect(0, 1);

			t->label.append(sans_colon, t->contr.instr_prev());
		}
	};

// branch:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_branch_begin, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->template assembly_action<AAN::jump, AAT::branch>(); }
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_branch_value, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->jump.push(l->left_cselect(), t->contr.instr_prev()); }
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_branch_end, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ } // nothing yet.
	};

// goto:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_goto_begin, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->template assembly_action<AAN::jump, AAT::go_to>(); }
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_goto_value, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->jump.append(l->left_cselect(), t->contr.instr_prev()); }
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_goto_end, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ } // nothing yet.
	};

// tail:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_tail_begin, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ } // nothing yet.
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_tail_value, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ } // nothing yet.
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_tail_end, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ } // nothing yet.
	};

// left:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_left_value, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			auto s = l->left_cselect();
			auto k = t->vars.match(s);

			if (k.not_end()) t->line.left.set_sign(k.left_size());
			else t->line.set_left_unknown(s);
		}
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_left_copy, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->line.left.set_sign(_zero); }
	};

// apply:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_apply_begin, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			if (t->line.left.is_unknown()) { } // error.
			else t->template assembly_action<AAN::apply, AAT::begin>(AT::call_f);
		}
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_apply_end, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->paste_compound_op();

			t->template assembly_action<AAN::apply, AAT::end>(t->vars.dropsize(), t->op_note());
			t->non_zero_replace(t->line.left.arg_at());
		}
	};

// test:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_test_begin, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->template assembly_action<AAN::apply, AAT::begin>(AT::call_f); }
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_test_end, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->paste_compound_op();

			t->template assembly_action<AAN::apply, AAT::end>(t->vars.dropsize(), t->op_note());
		}
	};

// swap:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_swap_begin, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->template assembly_action<AAN::apply, AAT::begin>(AT::void_f);

			t->copy_val(l->left_cselect());
			t->paste_val_mut();
		}
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_swap_end, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->paste_compound_op();

			t->template assembly_action<AAN::apply, AAT::end>(t->vars.dropsize(), t->op_note());
		}
	};

// void:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_void_begin, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->template assembly_action<AAN::apply, AAT::begin>(AT::void_f); }
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_void_end, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->paste_compound_op();

			t->template assembly_action<AAN::apply, AAT::end>(t->vars.dropsize(), t->op_note());
		}
	};

// assign:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_assign_begin, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			if (t->line.left.is_unknown()) t->assign_unknown();
			else { } // error.
		}
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_assign_end, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->template assembly_action<AAN::replace, AAT::id>(t->line.left.arg_at());

			t->line.left.reset();
		}
	};

// return:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_return_begin, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ } // nothing yet.
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_return_end, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->template assembly_action<AAN::end, AAT::id>(AT::first); }
	};

// sub op:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_subop_value, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->copy_op(l->left_cselect()); }
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_subop_paste, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->template chain_action<CAN::arg, CAT::non>(_zero); }
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_subop_quote, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
		}
	};

// sub arg:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_subarg_value, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->copy_val(l->left_cselect());
			t->paste_val();
		}
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_subarg_paste, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->template chain_action<CAN::non, CAT::arg>(_zero); }
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_subarg_quote, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
		}
	};

// mut arg:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_mutarg_value, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->copy_val(l->left_cselect());
			t->paste_val_mut();
		}
	};

// unit value:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_unit_value, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->copy_val(l->left_cselect());
			t->paste_val_unit();
		}
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_unit_paste, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ } // do nothing given return end, assign end.
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_unit_quote, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ } // nothing yet.
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_unit_morph, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->push_compound(); }
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_unit_cycle, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->push_cycle(); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace chord

