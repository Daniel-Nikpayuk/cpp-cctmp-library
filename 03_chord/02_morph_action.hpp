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

// morph action:

namespace chord {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// morph:

/***********************************************************************************************************************/

// op:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::mor_op_arity, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->proc.last()->set_arity(l->to_number()); }
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::mor_op_value, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->set_op(l->left_cselect());

			t->proc_capture_op();
		}
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::mor_op_id, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ } // nothing yet.
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::mor_op_deref, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ } // nothing yet.
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::mor_op_inc, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ } // nothing yet.
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::mor_op_dec, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ } // nothing yet.
	};

// argpose:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::mor_argpose_begin, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->template assembly_action<AAN::apply, AAT::begin>(AT::cons_f); }
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::mor_argpose_end, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			auto arity    = t->proc.last()->arity();
			auto cap_size = t->proc.last()->size();
			auto dropsize = arity + cap_size;

			t->subop_capture_action(arity);

			t->template assembly_action<AAN::apply, AAT::end>(dropsize, t->op_note());
		}
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::mor_argpose_value, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->template chain_action<CAN::non, CAT::arg>(l->to_number()); }
	};

// subpose:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::mor_subpose_begin, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->line.set_sub(_zero);
			t->drop.clear();

			t->template assembly_action<AAN::apply, AAT::begin>(AT::cons_f);
		}
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::mor_subpose_end, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			auto arity    = t->proc.last()->arity();
			auto cap_size = t->proc.last()->size();
			auto dropsize = arity + cap_size;

			t->update_contr_arg_drops(cap_size);
			t->subop_capture_action(arity);

			t->template assembly_action<AAN::apply, AAT::end>(dropsize, t->op_note());
		}
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::mor_subpose_value, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->set_val(l->left_cselect());

			t->argop_capture_action();
		}
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::mor_subpose_id, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ } // nothing yet.
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::mor_subpose_deref, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ } // nothing yet.
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::mor_subpose_inc, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ } // nothing yet.
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::mor_subpose_dec, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ } // nothing yet.
	};

// curry:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::mor_curry_begin, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->template assembly_action<AAN::apply, AAT::begin>(AT::cons_f); }
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::mor_curry_end, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			auto arity    = t->proc.last()->arity();
			auto cap_size = t->proc.last()->size();
			auto dropsize = arity + cap_size;

			for (auto k = 0; k != arity; ++k) // variadic.
				t->template chain_action<CAN::non, CAT::arg>(k);

			t->subop_capture_action(arity);

			t->template assembly_action<AAN::apply, AAT::end>(dropsize, t->op_note());
		}
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::mor_curry_value, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->set_val(l->left_cselect());

			t->subval_capture_action();
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace chord

