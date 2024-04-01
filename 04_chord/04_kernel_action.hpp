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

// kernel (generic, compound, morph) action:

namespace chord {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// generic:

/***********************************************************************************************************************/

// nop:

	template<auto... filler>
	struct T_chord_translation_action<CAAN::nop, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l) { }
	};

/***********************************************************************************************************************/

// param:

	// type:

		template<auto... filler>
		struct T_chord_translation_action<CAAN::param_type, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->param_type(l->left_cselect()); }
		};

/***********************************************************************************************************************/

// main:

	// name:

		template<auto... filler>
		struct T_chord_translation_action<CAAN::main_name, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->main_begin(l->left_cselect()); }
		};

	// begin:

		template<auto... filler>
		struct T_chord_translation_action<CAAN::main_begin, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->define_op_begin(); }
		};

	// end:

		template<auto... filler>
		struct T_chord_translation_action<CAAN::main_end, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				t->force_define_jumps();
				t->main_end();
			}
		};

	// arg:

		template<auto... filler>
		struct T_chord_translation_action<CAAN::main_arg, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->define_op_arg(l->left_cselect()); }
		};

	// return:

		template<auto... filler>
		struct T_chord_translation_action<CAAN::main_return, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->first_return(); }
		};

/***********************************************************************************************************************/

// op port:

	// lookup:

		template<auto... filler>
		struct T_chord_translation_action<CAAN::op_port_lookup, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->op_port_lookup(l->left_cselect()); }
		};

/***********************************************************************************************************************/

// port:

	// deduce:

		template<auto... filler>
		struct T_chord_translation_action<CAAN::port_deduce, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->force_literal_return(); }
		};

	// lookup:

		template<auto... filler>
		struct T_chord_translation_action<CAAN::port_lookup, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->port_lookup(l->left_cselect()); }
		};

/***********************************************************************************************************************/

// label:

	// value:

		template<auto... filler>
		struct T_chord_translation_action<CAAN::label_value, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->define_label(l->left_cselect(0, 1)); }
		};

/***********************************************************************************************************************/

// goto:

	// delay:

		template<auto... filler>
		struct T_chord_translation_action<CAAN::goto_delay, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->delay_define_goto(l->left_cselect()); }
		};

/***********************************************************************************************************************/

// branch:

	// delay:

		template<auto... filler>
		struct T_chord_translation_action<CAAN::branch_delay, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->delay_define_branch(l->left_cselect()); }
		};

/***********************************************************************************************************************/

// declare (function):

	// op:

		template<auto... filler>
		struct T_chord_translation_action<CAAN::declare_op, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->delay_define_compound(l->left_cselect()); }
		};

/***********************************************************************************************************************/

// define (variable):

	// begin:

		template<auto... filler>
		struct T_chord_translation_action<CAAN::define_begin, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				t->count.cache(t->verse.size());
				t->count.reset();
			}
		};

	// end:

		template<auto... filler>
		struct T_chord_translation_action<CAAN::define_end, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->define_arg_names(t->count.cache(), t->count.size()); }
		};

	// arg:

		template<auto... filler>
		struct T_chord_translation_action<CAAN::define_arg, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				t->define_arg_name(l->left_cselect());
				t->count.upsize();
			}
		};

/***********************************************************************************************************************/

// left:

	// value:

		template<auto... filler>
		struct T_chord_translation_action<CAAN::left_value, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->delay_replace(l->left_cselect()); }
		};

	// copy:

		template<auto... filler>
		struct T_chord_translation_action<CAAN::left_copy, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->copy_replace(); }
		};

/***********************************************************************************************************************/

// apply:

	// end:

		template<auto... filler>
		struct T_chord_translation_action<CAAN::apply_end, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				const bool not_side   = not t->stage.side.cvalue();
				const bool is_replace = not_side && t->replace.not_copy();

				t->apply_end();

				if (is_replace) t->force_replace();
			}
		};

/***********************************************************************************************************************/

// side:

	// begin:

		template<auto... filler>
		struct T_chord_translation_action<CAAN::side_begin, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->side_replace(); }
		};

/***********************************************************************************************************************/

// swap:

	// begin:

		template<auto... filler>
		struct T_chord_translation_action<CAAN::swap_begin, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->swap_replace(l->left_cselect()); }
		};

	// value:

		template<auto... filler>
		struct T_chord_translation_action<CAAN::swap_value, filler...>
		{
			nik_ces bool mute = true;

			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->lookup_return(t->replace.name(), mute); }
		};

/***********************************************************************************************************************/

// assign:

	// end:

		template<auto... filler>
		struct T_chord_translation_action<CAAN::assign_end, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ if (t->replace.not_copy()) t->force_replace(); }
		};

/***********************************************************************************************************************/

// subop:

	// value:

		template<auto... filler>
		struct T_chord_translation_action<CAAN::subop_value, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				t->apply_begin(l->left_cselect(), t->replace.reset_side());
				t->lookup_return(l->left_cselect());
			}
		};

	// paste:

		template<auto... filler>
		struct T_chord_translation_action<CAAN::subop_paste, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l) // clean up!
				{ t->template assembly_action<AAN::lookup, AAT::variable>(AT::back, false, 0); }
		};

	// quote:

		template<auto... filler>
		struct T_chord_translation_action<CAAN::subop_quote, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
			}
		};

/***********************************************************************************************************************/

// subarg:

	// value:

		template<auto... filler>
		struct T_chord_translation_action<CAAN::subarg_value, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->lookup_return(l->left_cselect()); }
		};

	// paste:

		template<auto... filler>
		struct T_chord_translation_action<CAAN::subarg_paste, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l) // clean up!
				{ t->template assembly_action<AAN::lookup, AAT::variable>(AT::back, false, 0); }
		};

	// quote:

		template<auto... filler>
		struct T_chord_translation_action<CAAN::subarg_quote, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
			}
		};

/***********************************************************************************************************************/

// mutarg:

	// value:

		template<auto... filler>
		struct T_chord_translation_action<CAAN::mutarg_value, filler...>
		{
			nik_ces bool mute = true;

			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->lookup_return(l->left_cselect(), mute); }
		};

/***********************************************************************************************************************/

// unit:

	// value:

		template<auto... filler>
		struct T_chord_translation_action<CAAN::unit_value, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->lookup_return(l->left_cselect()); }
		};

	// paste:

		template<auto... filler>
		struct T_chord_translation_action<CAAN::unit_paste, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ } // do nothing ?
		};

	// quote:

		template<auto... filler>
		struct T_chord_translation_action<CAAN::unit_quote, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
			}
		};

/***********************************************************************************************************************/

// literal:

	// n_number:

		template<auto... filler>
		struct T_chord_translation_action<CAAN::literal_n_number, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->delay_n_number_return(l->cbegin(), l->ccurrent()); }
		};

	// r_number:

		template<auto... filler>
		struct T_chord_translation_action<CAAN::literal_r_number, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->delay_r_number_return(l->cbegin(), l->ccurrent()); }
		};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// compound action:

/***********************************************************************************************************************/

// arity:

	template<auto... filler>
	struct T_chord_translation_action<CAAN::pound_arity_value, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->delay_define_arity(l->to_number()); }
	};

	template<auto... filler>
	struct T_chord_translation_action<CAAN::pound_arity_zero, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->delay_define_arity(0); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// morph action:

/***********************************************************************************************************************/

// op:

	template<auto... filler>
	struct T_chord_translation_action<CAAN::mor_op_begin, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->morph_op_begin(t->replace.name()); }
	};

	template<auto... filler>
	struct T_chord_translation_action<CAAN::mor_op_end, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->morph_op_end(); }
	};

	template<auto... filler>
	struct T_chord_translation_action<CAAN::mor_op, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->morph_op_return(l->left_cselect()); }
	};

	template<auto... filler>
	struct T_chord_translation_action<CAAN::mor_op_range, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->morph_op_range(); }
	};

// argpose:

	template<auto... filler>
	struct T_chord_translation_action<CAAN::mor_argpose_value, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->back_lookup_return(l->to_number());
			t->stage.upsize();
		}
	};

// subpose:

	template<auto... filler>
	struct T_chord_translation_action<CAAN::mor_subpose_value, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->subpose_value(l->left_cselect()); }
	};

// curry:

	template<auto... filler>
	struct T_chord_translation_action<CAAN::mor_curry_value, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->lookup_return(l->left_cselect()); }
	};

	template<auto... filler>
	struct T_chord_translation_action<CAAN::mor_curry_args, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			for (auto k = 0; k != t->pound.arity(); ++k)
			{
				t->back_lookup_return(k);
				t->stage.upsize();
			}
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace chord

