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

// evaluate:

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

	//	protected: // debugging:

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

			nik_ce auto contr_value(size_ctype row, size_ctype col) const
				{ return contr_csubmethod[row][col]; }

		public:

			nik_ce eval_cmethod_disjoint() : base{} { initialize(); }
			nik_ce eval_cmethod_disjoint(const facade & f) :

				base{f},
				contr_csubmethod{base::model->contr_csubequip()}
				{ initialize(); }
	};

	// syntactic sugar:

		template<typename Facade>
		using eval_cmethod =
			eval_cmethod_disjoint < Facade >;

/***********************************************************************************************************************/

// mutable:

	template<template<typename, typename, typename> typename Action, typename Base>
	class eval_method_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;
			using model_type		= typename facade::model_type;

			using machine_type		= typename model_type::machine_type;

			nik_using_name_scope_type	( type, base)
			nik_using_name_scope_ctype	(ctype, base)

			nik_using_size_type_scope	(base)

		protected:

			using contr_csubmethod_type	= typename base::contr_csubmethod_type;
			using action_type		= Action<eval_method_disjoint, contr_csubmethod_type, size_type>;

		//	using machine_method_type	= resolve_method<machine_type, machine_method>;

		//	machine_method_type machine_method;

	//	protected: // debugging.
		public:

			machine_type _machine;

		public:

			nik_ce eval_method_disjoint() : base{} { }//, machine_method{} { }
		//	nik_ce eval_method_disjoint(const base * b) : base{b} { }//, machine_method{} { }
			nik_ce eval_method_disjoint(const facade & f) :
				base{f}//,
			//	machine_method{_machine.template equip<machine_method_type>()},
				{ }

		protected:

			nik_ce auto contr_current_value(size_ctype col) const
				{ return base::contr_value(_machine.counter(), col); }

			nik_ce void execute()
			{
				size_ctype instr = contr_current_value(0);

				action_type::execute(instr, this, base::contr_csubmethod);
			}

		public:

			nik_ce auto again() const { return eval_method_disjoint{base::model}; }

			using carry_type = typename machine_type::carry_type;

				// assumes counter is set before calling.
			nik_ce auto run(ctype_ptr in, ctype_cptr end) -> carry_type
			{
				carry_type carry;

				_machine.verse()->push(in, end);

				while (contr_current_value(3))
				{
					_machine.inc_counter();
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

