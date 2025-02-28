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

// machine method:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// method:

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class machine_cmethod_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;
			using model_type		= typename facade::model_type;

			nik_using_name_scope_type	( type, base)
			nik_using_name_scope_ctype	(ctype, base)

			nik_using_size_type_scope	(base)

		protected:

			using carry_csubmethod_type	= typename model_type::carry_csubmethod_type;
			using verse_csubmethod_type	= typename model_type::verse_csubmethod_type;
			using stage_csubmethod_type	= typename model_type::stage_csubmethod_type;

			carry_csubmethod_type carry_csubmethod;
			verse_csubmethod_type verse_csubmethod;
			stage_csubmethod_type stage_csubmethod;

		public:

			nik_ce machine_cmethod_disjoint() : base{} { }
			nik_ce machine_cmethod_disjoint(const facade & f) :

				base{f},
				carry_csubmethod {base::model->carry_csubequip()},
				verse_csubmethod {base::model->verse_csubequip()},
				stage_csubmethod {base::model->stage_csubequip()}
				{ }

			// verse:

				nik_ce auto & verse_cinterval() const { return verse_csubmethod; }

				nik_ce void set_verse_cinterval(size_ctype start, size_ctype finish)
					{ verse_csubmethod.mid_set(start, finish); }

			// stage:

				nik_ce auto & stage_cinterval() const { return stage_csubmethod; }

				nik_ce auto stage_cfunc(size_ctype n)
				{
					stage_csubmethod.right_set(n);

					return stage_csubmethod[0];
				}

				nik_ce auto stage_cargs() const
				{
					auto method = stage_csubmethod;
					method.left_inward();

					return method;
				}
	};

	// syntactic sugar:

		template<typename Facade>
		using machine_cmethod =
			machine_cmethod_disjoint < Facade >;

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class machine_method_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;
			using model_type		= typename facade::model_type;

			nik_using_name_scope_type	( type, base)
			nik_using_name_scope_ctype	(ctype, base)

			nik_using_size_type_scope	(base)

		protected:

			using carry_submethod_type	= typename model_type::carry_submethod_type;
			using verse_submethod_type	= typename model_type::verse_submethod_type;
			using stage_submethod_type	= typename model_type::stage_submethod_type;

			carry_submethod_type carry_submethod;
			verse_submethod_type verse_submethod;
			stage_submethod_type stage_submethod;

		public:

			nik_ce machine_method_disjoint() : base{} { }
			nik_ce machine_method_disjoint(const facade & f) :

				base{f},
				carry_submethod{base::model->carry_subequip()},
				verse_submethod{base::model->verse_subequip()},
				stage_submethod{base::model->stage_subequip()}
				{ }

			// carry:

				nik_ce void value_to_carry(size_ctype value) { base::carry().push(value); }

				template<typename T>
				nik_ce void interval_to_carry(const T & v)
					{ base::carry().push(v.cbegin(), v.cend()); }

				nik_ce void interval_to_carry(size_ctype start, size_ctype finish)
				{
					base::set_verse_cinterval(start, finish);
					interval_to_carry(base::verse_cinterval());
				}

			// stage:

				nik_ce void value_to_stage(size_ctype value) { base::stage().push(value); }

				template<typename T>
				nik_ce void interval_to_stage(const T & v)
					{ base::stage().push(v.cbegin(), v.cend()); }

				nik_ce void interval_to_stage(size_ctype start, size_ctype finish)
				{
					base::set_verse_cinterval(start, finish);
					interval_to_stage(base::verse_cinterval());
				}

				nik_ce void pop_stage()
					{ base::stage().downsize(base::stage_cinterval().size()); }

			// run:

				template<typename T>
				nik_ce void initialize(size_ctype n, const T & v)
				{
					base::set_counter(n);
					base::verse().push(v.cbegin(), v.cend());
				}

			// copy value:

				nik_ce void copy_value(size_ctype policy, size_ctype value)
				{
					if      (policy == MP::to_stage) { value_to_stage(value); }
					else if (policy == MP::to_carry) { value_to_carry(value); }
				}

				template<typename T>
				nik_ce void copy_interval(size_ctype policy, const T & v)
				{
					if      (policy == MP::to_stage) { interval_to_stage(v); }
					else if (policy == MP::to_carry) { interval_to_carry(v); }
				}

				nik_ce void copy_interval(size_ctype policy, size_ctype start, size_ctype finish)
				{
					base::set_verse_cinterval(start, finish);
					copy_interval(policy, base::verse_cinterval());
				}

			// atomic:

				template<typename F>
				nik_ce void atomic_binary(F f, size_ctype n)
					{ copy_value(n, f(base::cverse().cat(0), base::cverse().cat(1))); }

				template<typename F>
				nik_ce void atomic_fold(F f, size_type n, size_type m)
				{
					for (auto k = base::cverse().cbegin(); k != base::cverse().cend(); ++k)
						{ m = f(m, *k); }

					copy_value(n, m);
				}

			// goto:

				nik_ce void branch(size_ctype n)
					{ if (base::carry().pop()) { base::set_counter(n); } }

				nik_ce void invert(size_ctype n)
					{ if (not base::carry().pop()) { base::set_counter(n); } }
	};

	// syntactic sugar:

		template<typename Facade>
		using machine_method =
			machine_method_disjoint  <
			machine_cmethod_disjoint < Facade >>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

