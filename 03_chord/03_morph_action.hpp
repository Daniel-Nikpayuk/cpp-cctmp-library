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
			{ t->define_op_arity(l->to_number()); }
	};

	template<auto... filler>
	struct T_chord_translation_action<CAAN::mor_arity_zero, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->define_op_arity(0); }
	};

// op:

	template<auto... filler>
	struct T_chord_translation_action<CAAN::mor_op_value, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->apply_begin(l->left_cselect()); }
			//	inc_args_if();
	};

// argpose:

	template<auto... filler>
	struct T_chord_translation_action<CAAN::mor_argpose_begin, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->refine_op_name(t->repl_name);
			t->refine_op_args();
			t->define_op_begin();
		}
	};

	template<auto... filler>
	struct T_chord_translation_action<CAAN::mor_argpose_end, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->apply_end();
			t->define_op_end();
		}
	};

	template<auto... filler>
	struct T_chord_translation_action<CAAN::mor_argpose_value, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->lookup_variadic_back_action(t->arg_pos(l->to_number()));
			t->inc_args_if();
		}
	};

// subpose:

/*
	template<auto... filler>
	struct T_chord_translation_action<CAAN::mor_subpose_begin, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
		}
	};

	template<auto... filler>
	struct T_chord_translation_action<CAAN::mor_subpose_end, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
		}
	};

	template<auto... filler>
	struct T_chord_translation_action<CAAN::mor_subpose_value, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
		}
	};
*/

// curry:

/*
	template<auto... filler>
	struct T_chord_translation_action<CAAN::mor_curry_begin, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
		}
	};

	template<auto... filler>
	struct T_chord_translation_action<CAAN::mor_curry_end, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
		}
	};

	template<auto... filler>
	struct T_chord_translation_action<CAAN::mor_curry_value, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
		}
	};
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace chord

