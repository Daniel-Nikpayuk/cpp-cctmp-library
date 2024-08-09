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

// state:

	// instead of generic list, make specific varieties. Notably applications. Will we still require
	// an unknown (indeterminate?) application for when the operator is a non-trivial expression?
	// should we wrap atomic operators as compound? If so, how to correct for when it's not treated
	// as an operator but a value? How to return it from the main function?

	// if you do wrap atomic functions, you'd keep specialized instructions as the body of the compound.
	// you could assume 0 context, and the args would already be there so you could just push the atomic
	// operator to the front and apply.

	// if an application's operator is indeterminate, add a special instruction to compile time test
	// if atomic or compound, record it as a template parameter and dispatch accordingly during the apply?
	// is this the best possible solution?

namespace engine {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// universe:

/***********************************************************************************************************************/

	struct universe
	{
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// stage:

/***********************************************************************************************************************/

	struct stage
	{
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// tree:

/***********************************************************************************************************************/

	template<typename SizeType>
	struct tree
	{
		using size_type		= SizeType;
		using size_ctype	= size_type const;

		// literal (boolean):

			template<typename AST>
			nik_ces void push_literal_boolean(AST* t, size_ctype n)
			{
				t->assembly_push_instr( AN::id      , AT::id      , 0 , 0 , 0 , 0 , 0 , 1 );
				t->assembly_push_instr( AN::type    , AT::boolean , 0 , 0 , 0 , 0 , 0 , 1 );
				t->assembly_push_instr( AN::literal , AT::first   , n , 0 , 0 , 0 , 0 , 1 );
				t->assembly_push_instr( AN::halt    , AT::first   , 0 , 0 , 0 , 0 , 0 , 1 );
			}

		// literal (character):

			template<typename AST>
			nik_ces void push_literal_character(AST* t, size_ctype n)
			{
				t->assembly_push_instr( AN::id      , AT::id        , 0 , 0 , 0 , 0 , 0 , 1 );
				t->assembly_push_instr( AN::type    , AT::character , 0 , 0 , 0 , 0 , 0 , 1 );
				t->assembly_push_instr( AN::literal , AT::first     , n , 0 , 0 , 0 , 0 , 1 );
				t->assembly_push_instr( AN::halt    , AT::first     , 0 , 0 , 0 , 0 , 0 , 1 );
			}

		// literal (n number):

			template<typename AST>
			nik_ces void push_literal_n_number(AST* t, size_ctype n)
			{
				t->assembly_push_instr( AN::id      , AT::id       , 0 , 0 , 0 , 0 , 0 , 1 );
				t->assembly_push_instr( AN::type    , AT::n_number , 0 , 0 , 0 , 0 , 0 , 1 );
				t->assembly_push_instr( AN::literal , AT::first    , n , 0 , 0 , 0 , 0 , 1 );
				t->assembly_push_instr( AN::halt    , AT::first    , 0 , 0 , 0 , 0 , 0 , 1 );
			}

		// literal (r number):

			template<typename AST>
			nik_ces void push_literal_r_number(AST* t, size_ctype n, size_ctype m)
			{
				t->assembly_push_instr( AN::id       , AT::id       , 0 , 0 , 0 , 0 , 0 , 1 );
				t->assembly_push_instr( AN::type     , AT::r_number , 0 , 0 , 0 , 0 , 0 , 1 );
				t->assembly_push_instr( AN::floating , AT::first    , n , 0 , m , 0 , 0 , 1 );
				t->assembly_push_instr( AN::halt     , AT::first    , 0 , 0 , 0 , 0 , 0 , 1 );
			}

		// literal (t number):

			template<typename AST>
			nik_ces void push_literal_t_number(AST* t, size_ctype n)
			{
				t->assembly_push_instr( AN::id      , AT::id    , 0 , 0 , 0 , 0 , 0 , 1 );
				t->assembly_push_instr( AN::type    , AT::push  , 0 , 0 , 0 , 0 , 0 , 1 );
				t->assembly_push_instr( AN::literal , AT::first , n , 0 , 0 , 0 , 0 , 1 );
				t->assembly_push_instr( AN::halt    , AT::first , 0 , 0 , 0 , 0 , 0 , 1 );
			}

		// variable (universe):

			template<typename AST>
			nik_ces void push_variable_universe(AST* t, size_ctype n)
			{
				t->assembly_push_instr( AN::id   , AT::id     , 0 , 0 , 0 , 0 , 0 , 1 );
				t->assembly_push_instr( AN::arg  , AT::select , n , 0 , 0 , 0 , 0 , 1 );
				t->assembly_push_instr( AN::arg  , AT::drop   , 0 , 0 , 0 , 0 , 0 , 1 );
				t->assembly_push_instr( AN::halt , AT::first  , 0 , 0 , 0 , 0 , 0 , 1 );
			}

		// variable (lookup):

			template<typename AST>
			nik_ces void push_variable_lookup(AST* t)
			{
				t->assembly_push_instr( AN::id     , AT::id    , 0 , 0 , 0 , 0 , 0 , 1 );
				t->assembly_push_instr( AN::lookup , AT::first , 0 , 0 , 0 , 0 , 0 , 1 );
				t->assembly_push_instr( AN::halt   , AT::first , 0 , 0 , 0 , 0 , 0 , 1 );
			}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace engine

