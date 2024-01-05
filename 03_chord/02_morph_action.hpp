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

// morph action:

namespace chord {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// subsource:

	using T_def_subsrc = cctmp::T_default_subsource;

/***********************************************************************************************************************/

// subpose:

	// begin:

		struct T_subpose_begin
		{
			template<typename AST>
			nik_ces void result(AST *t)
			{
				t->line.set_sub(_zero);
				t->drop.clear();
			}
		};

	// end:

		struct T_subpose_end
		{
			template<typename AST, typename RecordType>
			nik_ces void result(AST *t, const RecordType & record)
			{
				t->tag_arg_drops(record.cap_size);
				t->paste_compound_subop(record.arity);
			}

			template<typename AST>
			nik_ces void result(AST *t) { result(t, t->pound.clast()->record()); }
		};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// morph:

/***********************************************************************************************************************/

// arity:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::mor_arity_id, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->pound.last()->set_arity(_zero); }
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::mor_arity_value, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->pound.last()->set_arity(l->to_number()); }
	};

// op:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::mor_op_value, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->copy_op(l->left_cselect());

			t->capture_op();
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
			auto record = t->pound.clast()->record();

			t->paste_compound_subop(record.arity);

			t->template assembly_action<AAN::apply, AAT::end>(record.dropsize, t->op_note());
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
			t->template assembly_action<AAN::apply, AAT::begin>(AT::cons_f);

			T_subpose_begin::template result<AST>(t);
		}
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::mor_subpose_end, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			auto record = t->pound.clast()->record();

			T_subpose_end::template result<AST>(t, record);

			t->template assembly_action<AAN::apply, AAT::end>(record.dropsize, t->op_note());
		}
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::mor_subpose_value, filler...>
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
			auto record = t->pound.clast()->record();

			for (auto k = 0; k != record.arity; ++k) // variadic.
				t->template chain_action<CAN::non, CAT::arg>(k);

			t->paste_compound_subop(record.arity);

			t->template assembly_action<AAN::apply, AAT::end>(record.dropsize, t->op_note());
		}
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::mor_curry_value, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->copy_val(l->left_cselect());

			t->paste_subval();
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace chord

