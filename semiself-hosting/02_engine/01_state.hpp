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

namespace assembly {

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

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// verse:

/***********************************************************************************************************************/

	struct T_verse
	{
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// stage:

/***********************************************************************************************************************/

	struct T_stage
	{
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// tree:

/***********************************************************************************************************************/

	template<typename SizeType>
	struct T_tree
	{
		using size_type		= SizeType;
		using csize_type	= size_type const;

		// literal (boolean):

			template<typename AST>
			nik_ces void push_literal_boolean(AST* t, csize_type n)
			{
				t->assembly_push_instr( AN::id      , AT::id      , 0 , 0 , 0 , 0 , 0 , 1 );
				t->assembly_push_instr( AN::type    , AT::boolean , 0 , 0 , 0 , 0 , 0 , 1 );
				t->assembly_push_instr( AN::literal , AT::first   , n , 0 , 0 , 0 , 0 , 1 );
				t->assembly_push_instr( AN::halt    , AT::first   , 0 , 0 , 0 , 0 , 0 , 1 );
			}

		// literal (character):

			template<typename AST>
			nik_ces void push_literal_character(AST* t, csize_type n)
			{
				t->assembly_push_instr( AN::id      , AT::id        , 0 , 0 , 0 , 0 , 0 , 1 );
				t->assembly_push_instr( AN::type    , AT::character , 0 , 0 , 0 , 0 , 0 , 1 );
				t->assembly_push_instr( AN::literal , AT::first     , n , 0 , 0 , 0 , 0 , 1 );
				t->assembly_push_instr( AN::halt    , AT::first     , 0 , 0 , 0 , 0 , 0 , 1 );
			}

		// literal (n number):

			template<typename AST>
			nik_ces void push_literal_n_number(AST* t, csize_type n)
			{
				t->assembly_push_instr( AN::id      , AT::id       , 0 , 0 , 0 , 0 , 0 , 1 );
				t->assembly_push_instr( AN::type    , AT::n_number , 0 , 0 , 0 , 0 , 0 , 1 );
				t->assembly_push_instr( AN::literal , AT::first    , n , 0 , 0 , 0 , 0 , 1 );
				t->assembly_push_instr( AN::halt    , AT::first    , 0 , 0 , 0 , 0 , 0 , 1 );
			}

		// literal (r number):

			template<typename AST>
			nik_ces void push_literal_r_number(AST* t, csize_type n, csize_type m)
			{
				t->assembly_push_instr( AN::id       , AT::id       , 0 , 0 , 0 , 0 , 0 , 1 );
				t->assembly_push_instr( AN::type     , AT::r_number , 0 , 0 , 0 , 0 , 0 , 1 );
				t->assembly_push_instr( AN::floating , AT::first    , n , 0 , m , 0 , 0 , 1 );
				t->assembly_push_instr( AN::halt     , AT::first    , 0 , 0 , 0 , 0 , 0 , 1 );
			}

		// literal (t number):

			template<typename AST>
			nik_ces void push_literal_t_number(AST* t, csize_type n)
			{
				t->assembly_push_instr( AN::id      , AT::id    , 0 , 0 , 0 , 0 , 0 , 1 );
				t->assembly_push_instr( AN::type    , AT::push  , 0 , 0 , 0 , 0 , 0 , 1 );
				t->assembly_push_instr( AN::literal , AT::first , n , 0 , 0 , 0 , 0 , 1 );
				t->assembly_push_instr( AN::halt    , AT::first , 0 , 0 , 0 , 0 , 0 , 1 );
			}

		// variable (universe):

			template<typename AST>
			nik_ces void push_variable_universe(AST* t, csize_type n)
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

// env(ironment) model:

/***********************************************************************************************************************/

// interface:

	template<typename CharType, typename SizeType, SizeType Size>
	class T_env_model : public T_list_model<SizeType, Size>
	{
		public:

			nik_ces SizeType length		= Size;

			using base			= T_list_model<SizeType, length>;
			using size_type			= typename base::size_type;
			using csize_type		= typename base::csize_type;
			using list_type			= typename base::list_type;
			using clist_type		= typename base::clist_type;
			using inhabit_type		= unit_stack<size_type, 1>;
			using Pair			= typename base::Pair;

			using char_type			= CharType;
			using cselect			= cselector<char_type, size_type>;
			using ccselect			= cselect const;
			using ccselect_ref		= ccselect &;
			using strlit_type		= string_literal<CharType, size_type>;
			using cstrlit_type		= strlit_type const;
			using cstrlit_ref		= cstrlit_type &;

		protected:

			cstrlit_type src;

		public:

			inhabit_type inhabit;

			nik_ce T_env_model(cstrlit_ref s) : base{}, src{s} { }

			nik_ce auto get_value(csize_type n) const { return base::get_value(inhabit.cvalue(), n); }
			nik_ce void set_value(csize_type n, csize_type v) { base::set_value(inhabit.cvalue(), n, v); }

		protected:

			// src:

				nik_ce auto start  (ccselect_ref s) const { return s.cbegin() - src.cbegin(); }
				nik_ce auto finish (ccselect_ref s) const { return src.cend() - s.cend(); }

			// env:

				nik_ce auto get_frame   (clist_type env) const { return base::car(env); }
				nik_ce auto get_binding (clist_type env) const { return base::car(get_frame(env)); }
				nik_ce auto get_entry   (clist_type env) const { return base::cdr(get_binding(env)); }

		public:

			// name:

				nik_ce auto get_name(csize_type binding) const
				{
					auto variable = base::car(binding);
					auto start    = base::get_value(variable, Pair::car);
					auto finish   = base::get_value(variable, Pair::cdr);

					return src.cselect(start, finish);
				}

		protected:

			// lookup:

				nik_ce void lookup_frame(ccselect_ref var, clist_type frame)
				{
					for (auto k = frame; inhabit.is_empty() && base::not_null(k); k = base::cdr(k))
						lookup_binding(var, base::car(k));
				}

				nik_ce void lookup_binding(ccselect_ref var, csize_type binding)
				{
					if (apply<_subarray_same_<>>(var, get_name(binding)))
						inhabit.push(base::cdr(binding));
				}

			// binding:

				nik_ce auto set_binding_variable(ccselect_ref var)
				{
					csize_type p = base::allocate(Pair::dimension);

					base::set_value(p, Pair::car, start(var));
					base::set_value(p, Pair::cdr, finish(var));

					return p;
				}

				template<typename In, typename End>
				nik_ce auto set_binding_value(In in, End end)
				{
					csize_type p = base::allocate(end - in);
					size_type  k = 0;

					while (in != end) base::set_value(p, k++, *in++);

					return p;
				}

				nik_ce void set_binding_entry(csize_type variable, csize_type value, clist_type env)
				{
					auto frame   = base::car(env);
					auto binding = base::cons(variable, value);
					auto nframe  = base::cons(binding, frame);

					base::set_value(env, Pair::car, nframe);
				}

		public:

			// list:

				nik_ce auto null_env     () const { return base::null_list(); }
				nik_ce auto null_frame   () const { return base::null_list(); }
				nik_ce auto null_binding () const { return base::null_list(); }

			// env:

				nik_ce bool lookup_variable(ccselect_ref var, clist_type env)
				{
					inhabit.clear();

					for (auto k = env; inhabit.is_empty() && base::not_null(k); k = base::cdr(k))
						lookup_frame(var, base::car(k));

					return inhabit.not_empty();
				}

				template<typename In, typename End>
				nik_ce void define_variable(ccselect_ref var, In in, End end, clist_type env)
				{
					auto variable = set_binding_variable(var);
					auto value    = set_binding_value(in, end);

					set_binding_entry(variable, value, env);
				}

				template<size_type N>
				nik_ce void define_variable(ccselect_ref var, csize_type (&ent)[N], clist_type env)
					{ define_variable(var, ent, ent + N, env); }

				template<typename In, typename End>
				nik_ce void set_variable(ccselect_ref var, In in, End end, clist_type env)
				{
					lookup_variable(var, env);

					if (inhabit.not_empty())

						for (size_type k = 0; in != end; ++in, ++k) set_value(k, *in);

					else { } // error.
				}

				nik_ce auto extend_env(clist_type env) { return base::cons(null_frame(), env); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace assembly

