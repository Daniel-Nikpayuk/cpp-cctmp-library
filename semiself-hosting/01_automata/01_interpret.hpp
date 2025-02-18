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

/***********************************************************************************************************************/

// mutable:

	template
	<
		typename Type, typename SizeType,
		SizeType ContrSize, SizeType CarrySize, SizeType VerseSize, SizeType StageSize
	>
	class eval_model
	{
		public:

			using facade				= eval_model; // method compatible.

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

			nik_ce eval_model() { }
			nik_ce eval_model(const contr_type & c) : _contr{c} { }

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

// interface:

/***********************************************************************************************************************/

// mutable:

	template
	<
		typename Type, typename SizeType,
		SizeType ContrSize, SizeType CarrySize, SizeType VerseSize, SizeType StageSize
	>
	class eval : public eval_model<Type, SizeType, ContrSize, CarrySize, VerseSize, StageSize>
	{
		public:

			using base			= eval_model
							<
								Type, SizeType,
								ContrSize, CarrySize, VerseSize, StageSize
							>;
			using model_type		= base;
			using cfacade_type		= eval_cfacade<model_type>;
			using facade_type		= eval_facade<model_type>;

			using contr_type		= typename model_type::contr_type;

			nik_using_name_scope_type	( type, base)
			nik_using_name_scope_ctype	(ctype, base)

			nik_using_size_type_scope	(base)

		public:

			nik_ce eval() : base{} { }
			nik_ce eval(const contr_type & c) : base{c} { }

			// equip:

				template<typename CMethod>
				nik_ce auto cequip() const -> CMethod
					{ return cfacade_type{static_cast<model_type const*>(this)}; }

				template<typename Method>
				nik_ce auto equip() -> Method
					{ return facade_type{static_cast<model_type*>(this)}; }
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
				contr_csubmethod.fast_full_set();
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

	template<template<typename, typename> typename Action, typename Base>
	class eval_method_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;
			using model_type		= typename facade::model_type;

			using machine_type		= typename model_type::machine_type;
			using carry_type		= typename machine_type::carry_type;

			nik_using_name_scope_type	( type, base)
			nik_using_name_scope_ctype	(ctype, base)

			nik_using_size_type_scope	(base)

		protected:

			using action_type		= Action<eval_method_disjoint, size_type>;

		protected:

			machine_type _machine;

		public:

			nik_ce eval_method_disjoint() : base{} { }
			nik_ce eval_method_disjoint(const facade & f) : base{f} { }

			// contr:

				nik_ce size_type instr_value(size_ctype col) const
					{ return base::contr_value(_machine.counter(), col); }

			// counter:

				nik_ce void set_counter(size_ctype n) { _machine.set_counter(n); }

			// carry:

				nik_ce auto ccarry() const { return _machine.ccarry(); }
				nik_ce auto  carry()       { return _machine. carry(); }

			// verse:

				nik_ce auto cverse() const { return _machine.cverse(); }
				nik_ce auto  verse()       { return _machine. verse(); }

			// stage:

				nik_ce auto cstage() const { return _machine.cstage(); }
				nik_ce auto  stage()       { return _machine. stage(); }

		protected:

			// value:

				nik_ce void value_to_stack(size_ctype start, size_ctype finish)
					{ stage()->push(cverse()->citer(start), cverse()->citer(finish)); }

				nik_ce void value_to_carry(size_ctype start, size_ctype finish)
					{ carry()->push(cverse()->citer(start), cverse()->citer(finish)); }

				nik_ce void move(size_ctype policy, size_ctype value)
				{
					if      (policy == MP::to_stack) { stage()->push(value); }
					else if (policy == MP::to_carry) { carry()->push(value); }
				}

				nik_ce void move(size_ctype policy, size_ctype start, size_ctype finish)
				{
					if      (policy == MP::to_stack) { value_to_stack(start, finish); }
					else if (policy == MP::to_carry) { value_to_carry(start, finish); }
				}

			// atomic:

				// compare:

					nik_ces bool atomic_equal        (ctype v1, ctype v2) { return v1 == v2; }
					nik_ces bool atomic_not_equal    (ctype v1, ctype v2) { return v1 != v2; }
					nik_ces bool atomic_l_than       (ctype v1, ctype v2) { return v1 <  v2; }
					nik_ces bool atomic_l_than_or_eq (ctype v1, ctype v2) { return v1 <= v2; }
					nik_ces bool atomic_g_than       (ctype v1, ctype v2) { return v1 >  v2; }
					nik_ces bool atomic_g_than_or_eq (ctype v1, ctype v2) { return v1 >= v2; }

				// arithmetic:

					nik_ces type atomic_add      (ctype v1, ctype v2) { return v1 + v2; }
					nik_ces type atomic_subtract (ctype v1, ctype v2) { return v1 - v2; }
					nik_ces type atomic_multiply (ctype v1, ctype v2) { return v1 * v2; }
					nik_ces type atomic_divide   (ctype v1, ctype v2) { return v1 / v2; }
					nik_ces type atomic_modulo   (ctype v1, ctype v2) { return v1 % v2; }

				template<typename F> // generalize for policy
				nik_ce void atomic_binary(F f) // test against size
				{
					auto v1 = _machine.cverse()->cat(0);
					auto v2 = _machine.cverse()->cat(1);

					_machine.carry()->push(f(v1, v2));
				}

				template<typename F> // generalize for policy
				nik_ce void atomic_fold(F f, size_type k)
				{
					auto b = _machine.cverse()->cbegin();
					auto e = _machine.cverse()->cend();

					_machine.carry()->clear();
					while (b != e) { k = f(k, *b++); }
					_machine.carry()->push(k);
				}

			// execute:

				nik_ce void execute() { action_type::execute(instr_value(MAppl::action), this); }

		public:

			// compare:

				nik_ce void equal        () { atomic_binary (atomic_equal       ); }
				nik_ce void not_equal    () { atomic_binary (atomic_not_equal   ); }
				nik_ce void l_than       () { atomic_binary (atomic_l_than      ); }
				nik_ce void l_than_or_eq () { atomic_binary (atomic_l_than_or_eq); }
				nik_ce void g_than       () { atomic_binary (atomic_g_than      ); }
				nik_ce void g_than_or_eq () { atomic_binary (atomic_g_than_or_eq); }

			// arithmetic:


				nik_ce void constant() { move(instr_value(MAppl::policy), instr_value(MAppl::offset)); }

				nik_ce void add      () { atomic_fold   (atomic_add      , 0); }
				nik_ce void subtract () { atomic_binary (atomic_subtract    ); }
				nik_ce void multiply () { atomic_fold   (atomic_multiply , 1); }
				nik_ce void divide   () { atomic_binary (atomic_divide      ); }
				nik_ce void modulo   () { atomic_binary (atomic_modulo      ); }

			// run:

				nik_ce void run_branch()
					{ if (carry()->pop()) { _machine.set_counter(instr_value(MBran::line)); } }

				nik_ce void run_invert()
					{ if (not carry()->pop()) { _machine.set_counter(instr_value(MBran::line)); } }

				nik_ce void run_apply()
				{
					size_ctype offset   = instr_value(MAppl::offset);
					size_ctype policy   = instr_value(MAppl::policy);

					auto n_eval_method  = again();
					auto stage_start    = offset;
					auto stage_finish   = cstage()->size();

					n_eval_method       . set_counter(cstage()->cat(stage_start));
					auto stage_begin    = cstage()->citer(stage_start + 1);
					auto stage_end      = cstage()->citer(stage_finish);
					auto value          = n_eval_method.run(stage_begin, stage_end);

					auto subcarry_begin = n_eval_method.ccarry()->cbegin();
					auto subcarry_end   = n_eval_method.ccarry()->cend();

					stage()->downsize(stage_finish - stage_start);

					if (policy == MP::to_stack)
					{
						stage()->push(subcarry_begin, subcarry_end);
					}
					else if (policy == MP::to_carry)
					{
						carry()->push(subcarry_begin, subcarry_end);
					}
				}

				nik_ce void run_function()
					{ move(instr_value(MVal::policy), instr_value(MVal::line)); }

				nik_ce void run_argument()
				{
					auto start  = base::contr_value(instr_value(MVal::line), MArg::start);
					auto finish = base::contr_value(instr_value(MVal::line), MArg::finish);

					move(instr_value(MVal::policy), start, finish);
				}

				nik_ce void run_memory_to_stack()
					{ value_to_stack(instr_value(MMove::start), instr_value(MMove::finish)); }

				nik_ce void run_memory_to_carry()
					{ value_to_carry(instr_value(MMove::start), instr_value(MMove::finish)); }

						// rename!
				nik_ce auto again() const { return eval_method_disjoint{base::model}; }

					// assumes counter is set before calling.
				nik_ce auto run(ctype_ptr in, ctype_cptr end) -> carry_type
				{
					carry_type carry;

					_machine.verse()->push(in, end);

					while (instr_value(MProg::next))
					{
						_machine.inc_counter(instr_value(MProg::next));
						execute();
					}

					carry.push(_machine.carry()->cbegin(), _machine.carry()->cend());

					return carry;
				}

				template<auto N> // const verse_type & ?
				nik_ce auto run(ctype (&v)[N]) { return run(v, v + N); }
	};

	// syntactic sugar:

		template<typename Facade>
		using eval_method =
			eval_method_disjoint  < machine_action ,
			eval_cmethod_disjoint < Facade         >>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

