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

// interpret:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// eval:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// model:

	template<typename> class eval_cfacade;
	template<typename> class eval_facade;

/***********************************************************************************************************************/

// mutable:

	template
	<
		typename Type, typename SizeType,
		SizeType ContrSize, SizeType CarrySize, SizeType VerseSize, SizeType StageSize
	>
	class eval
	{
		public:

			using facade				= eval; // method compatible.
			using cfacade_type			= eval_cfacade<eval>;
			using facade_type			= eval_facade<eval>;

			using contr_type			= array<Type, SizeType, ContrSize>;
			using contr_ctype_ptr			= typename alias<contr_type>::ctype_ptr;

			using machine_type			= machine
								<
									Type, SizeType, CarrySize, VerseSize, StageSize
								>;

			nik_using_name_alias_scope_type		( type, Type)
			nik_using_name_alias_scope_ctype	(ctype, Type)

			nik_using_size_type_alias		(SizeType)

		public:

			using contr_csubmethod_type		= resolve_csubmethod<contr_type, table_csubmethod>;
			using machine_method_type		= resolve_method<machine_type, machine_method>;

		protected:

			contr_type  _contr;

		public:

			nik_ce eval() { }
			nik_ce eval(const contr_type & c) : _contr{c} { }

			// equip:

				template<typename CMethod>
				nik_ce auto cequip() const -> CMethod
					{ return cfacade_type{static_cast<eval const*>(this)}; }

				template<typename Method>
				nik_ce auto equip() -> Method
					{ return facade_type{static_cast<eval*>(this)}; }

			// contr:

				nik_ce contr_ctype_ptr ccontr() const { return &_contr; }

				nik_ce auto contr_csubequip() const
					{ return _contr.template csubequip<contr_csubmethod_type>(); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// facade:

/***********************************************************************************************************************/

// immutable:

	template<typename Model>
	class eval_cfacade
	{
		public:

			using facade			= eval_cfacade; // method compatible.

			using model_type		= Model;
			using model_ctype_ptr		= typename alias<model_type>::ctype_ptr;
			using model_ctype_cptr		= typename alias<model_type>::ctype_cptr;

			using contr_type		= typename model_type::contr_type;
			using contr_ctype_ref		= typename alias<contr_type>::ctype_ref;

			nik_using_name_scope_type	( type, model_type)
			nik_using_name_scope_ctype	(ctype, model_type)

			nik_using_size_type_scope	(model_type)

		protected:

			model_ctype_ptr model;

		public:

			nik_ce eval_cfacade() : model{} { }
			nik_ce eval_cfacade(model_ctype_cptr m) : model{m} { }

			// contr:

				nik_ce contr_ctype_ref ccontr() const { return *model->ccontr(); }
	};

/***********************************************************************************************************************/

// mutable:

	template<typename Model>
	class eval_facade
	{
		public:

			using facade			= eval_facade; // method compatible.

			using model_type		= Model;
			using model_type_ptr		= typename alias<model_type>::type_ptr;
			using model_type_cptr		= typename alias<model_type>::type_cptr;

			using contr_type		= typename model_type::contr_type;
			using contr_ctype_ref		= typename alias<contr_type>::ctype_ref;

			nik_using_name_scope_type	( type, model_type)
			nik_using_name_scope_ctype	(ctype, model_type)

			nik_using_size_type_scope	(model_type)

		protected:

			model_type_ptr model;

		public:

			nik_ce eval_facade() : model{} { }
			nik_ce eval_facade(model_type_cptr m) : model{m} { }

			// contr:

				nik_ce contr_ctype_ref ccontr() const { return *model->ccontr(); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// method:

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class eval_cmethod_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;
			using model_type		= typename facade::model_type;

			nik_using_name_scope_type	( type, base)
			nik_using_name_scope_ctype	(ctype, base)

			nik_using_size_type_scope	(base)

		protected:

			using contr_csubmethod_type	= typename model_type::contr_csubmethod_type;

			contr_csubmethod_type contr_csubmethod;

		protected:

			nik_ce void initialize() // call only once.
			{
				size_ctype row_size = (base::ccontr().size() >> 2);
				size_ctype col_size = 4;
				contr_csubmethod.full_set();
				contr_csubmethod.set_dimension(row_size, col_size);
			}

		public:

			nik_ce eval_cmethod_disjoint() : base{} { initialize(); }
			nik_ce eval_cmethod_disjoint(const facade & f) :

				base{f},
				contr_csubmethod{base::model->contr_csubequip()}
				{ initialize(); }

			// contr:

			nik_ce size_type contr_value(size_ctype row, size_ctype col) const
				{ return contr_csubmethod[row][col]; }
	};

	// syntactic sugar:

		template<typename Facade>
		using eval_cmethod =
			eval_cmethod_disjoint < Facade >;

/***********************************************************************************************************************/

// mutable:

	template
	<
		template<typename, typename> typename Atomic,
		template<typename, typename> typename Action,
		typename Base
	>
	class eval_method_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;
			using model_type		= typename facade::model_type;

			using machine_type		= typename model_type::machine_type;
			using carry_type		= typename machine_type::carry_type;
			using verse_type		= typename machine_type::verse_type;

			nik_using_name_scope_type	( type, base)
			nik_using_name_scope_ctype	(ctype, base)

			nik_using_size_type_scope	(base)

		protected:

			using atomic_action_type	= Atomic<type, size_type>;
			using action_type		= Action<eval_method_disjoint, size_type>;

			using machine_cmethod_type	= resolve_cmethod<machine_type, machine_cmethod>;
			using  machine_method_type	=  resolve_method<machine_type,  machine_method>;

			machine_cmethod_type mach_cmethod;
			machine_method_type   mach_method;

		protected:

			machine_type _machine;

		public:

			nik_ce eval_method_disjoint() : base{}, mach_cmethod{}, mach_method{} { }
			nik_ce eval_method_disjoint(const facade & f) : base{f}
			{
				mach_cmethod = _machine.template cequip<machine_cmethod_type>();
				mach_method  = _machine.template  equip< machine_method_type>();
			}

			// contr:

				nik_ce size_type instr_value(size_ctype col) const
					{ return base::contr_value(mach_method.counter(), col); }

			// carry:

				nik_ce auto rtn_cbegin () const { return mach_method.ccarry().cbegin (); }
				nik_ce auto rtn_cend   () const { return mach_method.ccarry().cend   (); }

		protected:

				template<typename F>
				nik_ce void atomic_binary(F f)
					{ mach_method.atomic_binary(f, instr_value(MAppl::policy)); }

				template<typename F>
				nik_ce void atomic_fold(F f, size_type m)
					{ mach_method.atomic_fold(f, instr_value(MAppl::policy), m); }

			// execute:

				nik_ce auto instantiate() const { return eval_method_disjoint{base::model}; }
				nik_ce void execute() { action_type::execute(instr_value(MAppl::action), this); }

		public:

			// atomic:

				nik_ce void atomic(size_ctype n)
					{ atomic_binary(atomic_action_type::action[n]); }

			// run:

				nik_ce void run_branch() { mach_method.branch(instr_value(MBran::line)); }
				nik_ce void run_invert() { mach_method.invert(instr_value(MBran::line)); }

				nik_ce void run_apply()
				{
					size_ctype offset  = instr_value(MAppl::offset);
					size_ctype policy  = instr_value(MAppl::policy);

					auto n_eval_method = instantiate();
					auto func_index    = mach_method.stage_cfunc(offset);
					auto value         = n_eval_method.run(mach_method.stage_cargs(), func_index);

					mach_method.pop_stage();
					mach_method.copy_interval(policy, value);
				}

				nik_ce void run_constant()
				{
					size_ctype policy = instr_value(MAppl::policy);
					size_ctype value  = instr_value(MAppl::offset);

					mach_method.copy_value(policy, value);
				}

				nik_ce void run_function()
				{
					size_ctype policy = instr_value(MVal::policy);
					size_ctype line   = instr_value(MVal::line);

					mach_method.copy_value(policy, line);
				}

				nik_ce void run_argument()
				{
					auto start  = base::contr_value(instr_value(MVal::line), MArg::start);
					auto finish = base::contr_value(instr_value(MVal::line), MArg::finish);

					mach_method.copy_interval(instr_value(MVal::policy), start, finish);
				}

				nik_ce void run_memory_to_stage()
				{
					size_ctype start  = instr_value(MMove::start);
					size_ctype finish = instr_value(MMove::finish);

					mach_method.interval_to_stage(start, finish);
				}

				nik_ce void run_memory_to_carry()
				{
					size_ctype start  = instr_value(MMove::start);
					size_ctype finish = instr_value(MMove::finish);

					mach_method.interval_to_carry(start, finish);
				}

				nik_ce auto run(ctype_ptr in, ctype_cptr end, size_ctype n = 0) -> carry_type
				{
					carry_type carry;

					verse_type verse; // designed for standalone virtual machine.
					verse.push(in, end);

					mach_method.initialize(n, verse);
					while (instr_value(MProg::next))
					{
						mach_method.inc_counter(instr_value(MProg::next));
						execute();
					}

					carry.push(_machine.carry()->cbegin(), _machine.carry()->cend());

					return carry;
				}

				// syntactic sugar:

					template<typename T>
					nik_ce auto run(const T & v, size_ctype n = 0)
						{ return run(v.cbegin(), v.cend(), n); }

					template<auto N>
					nik_ce auto run(ctype (&v)[N], size_ctype n = 0)
						{ return run(v, v + N, n); }
	};

	// syntactic sugar:

		template<typename Facade>
		using eval_method =
			eval_method_disjoint  < atomic_action , machine_action ,
			eval_cmethod_disjoint < Facade                         >>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

