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

// morph:

/***********************************************************************************************************************/

// arity:

	template<auto... filler>
	struct T_chord_translation_action<CAAN::mor_arity_value, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->delay_define_arity(l->to_number()); }
	};

	template<auto... filler>
	struct T_chord_translation_action<CAAN::mor_arity_zero, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->delay_define_arity(0); }
	};

// op:

	template<auto... filler>
	struct T_chord_translation_action<CAAN::mor_op_begin, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->force_define_compound(t->replace.name());
			t->force_define_arity();
			t->define_op_begin();
		}
	};

	template<auto... filler>
	struct T_chord_translation_action<CAAN::mor_op_end, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->apply_end();
			t->define_op_end();
		}
	};

	template<auto... filler>
	struct T_chord_translation_action<CAAN::mor_op, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->apply_begin(l->left_cselect());
			t->lookup_return(l->left_cselect());
		}
	};

	template<auto... filler>
	struct T_chord_translation_action<CAAN::mor_op_range, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->count.reset(); }
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
		{
			t->apply_begin(l->left_cselect());
			t->lookup_return(l->left_cselect());
			t->back_lookup_return(t->count.inc_size());
			t->stage.upsize();
			t->apply_end();
		}
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

