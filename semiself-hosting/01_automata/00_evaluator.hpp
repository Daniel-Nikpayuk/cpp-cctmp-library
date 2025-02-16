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

// evaluator:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// machine:

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
	class machine_model
	{
		public:

			using facade				= machine_model; // method compatible.

			using contr_type			= array<Type, SizeType, ContrSize>;
			using contr_ctype_ptr			= typename alias<contr_type>::ctype_ptr;

			using carry_type			= array<Type, SizeType, CarrySize>;
			using carry_type_ptr			= typename alias<carry_type>::type_ptr;
			using carry_ctype_ptr			= typename alias<carry_type>::ctype_ptr;

			using verse_type			= array<Type, SizeType, VerseSize>;
			using verse_type_ptr			= typename alias<verse_type>::type_ptr;
			using verse_ctype_ptr			= typename alias<verse_type>::ctype_ptr;

			using stage_type			= array<Type, SizeType, StageSize>;
			using stage_type_ptr			= typename alias<stage_type>::type_ptr;
			using stage_ctype_ptr			= typename alias<stage_type>::ctype_ptr;

			nik_using_name_alias_scope_type		( type, Type)
			nik_using_name_alias_scope_ctype	(ctype, Type)

			nik_using_size_type_alias		(SizeType)

		public:

			using contr_csubmethod_type		= resolve_csubmethod<contr_type, table_csubmethod>;

			using carry_csubmethod_type		= resolve_csubmethod<carry_type, array_csubmethod>;
			using  carry_submethod_type		=  resolve_submethod<carry_type,  array_submethod>;

			using verse_csubmethod_type		= resolve_csubmethod<verse_type, array_csubmethod>;
			using  verse_submethod_type		=  resolve_submethod<verse_type,  array_submethod>;

			using stage_csubmethod_type		= resolve_csubmethod<stage_type, array_csubmethod>;
			using  stage_submethod_type		=  resolve_submethod<stage_type,  array_submethod>;

		protected:

			contr_type  _contr;
			size_type   _counter;

			carry_type  _carry;
			verse_type  _verse;
			stage_type  _stage;

		public:

			nik_ce machine_model() : _counter{} { }
			nik_ce machine_model(const contr_type & c) : _contr{c}, _counter{} { }

			// contr:

				nik_ce contr_ctype_ptr ccontr() const { return &_contr; }

				nik_ce auto contr_csubequip() const
					{ return _contr.template csubequip<contr_csubmethod_type>(); }

			// counter:

				nik_ce size_type counter() const { return _counter; }
				nik_ce void set_counter(size_ctype c)     { _counter  = c; }
				nik_ce void inc_counter(size_ctype n = 1) { _counter += n; }

			// carry:

				nik_ce carry_ctype_ptr ccarry() const { return &_carry; }
				nik_ce  carry_type_ptr  carry()       { return &_carry; }

				nik_ce auto carry_csubequip() const
					{ return _carry.template csubequip<carry_csubmethod_type>(); }

				nik_ce auto carry_subequip()
					{ return _carry.template subequip<carry_submethod_type>(); }

			// verse:

				nik_ce verse_ctype_ptr cverse() const { return &_verse; }
				nik_ce  verse_type_ptr  verse()       { return &_verse; }

				nik_ce auto verse_csubequip() const
					{ return _verse.template csubequip<verse_csubmethod_type>(); }

				nik_ce auto verse_subequip()
					{ return _verse.template subequip<verse_submethod_type>(); }

			// stage:

				nik_ce stage_ctype_ptr cstage() const { return &_stage; }
				nik_ce  stage_type_ptr  stage()       { return &_stage; }

				nik_ce auto stage_csubequip() const
					{ return _stage.template csubequip<stage_csubmethod_type>(); }

				nik_ce auto stage_subequip()
					{ return _stage.template subequip<stage_submethod_type>(); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// facade:

/***********************************************************************************************************************/

// immutable:

	template<typename Model>
	class machine_cfacade
	{
		public:

			using facade			= machine_cfacade; // method compatible.

			using model_type		= Model;
			using model_ctype_ptr		= typename alias<model_type>::ctype_ptr;
			using model_ctype_cptr		= typename alias<model_type>::ctype_cptr;

			using contr_type		= typename model_type::contr_type;
			using contr_ctype_ref		= typename alias<contr_type>::ctype_ref;

			using carry_type		= typename model_type::carry_type;
			using carry_ctype_ref		= typename alias<carry_type>::ctype_ref;

			using verse_type		= typename model_type::verse_type;
			using verse_ctype_ref		= typename alias<verse_type>::ctype_ref;

			using stage_type		= typename model_type::stage_type;
			using stage_ctype_ref		= typename alias<stage_type>::ctype_ref;

			nik_using_name_scope_type	( type, model_type)
			nik_using_name_scope_ctype	(ctype, model_type)

			nik_using_size_type_scope	(model_type)

		protected:

			model_ctype_ptr model;

		public:

			nik_ce machine_cfacade() : model{} { }
			nik_ce machine_cfacade(model_ctype_cptr m) : model{m} { }

			// contr:

				nik_ce contr_ctype_ref ccontr() const { return *model->ccontr(); }

			// counter:

				nik_ce size_type counter() const { return model->counter(); }

			// carry:

				nik_ce carry_ctype_ref ccarry() const { return *model->ccarry(); }

			// verse:

				nik_ce verse_ctype_ref cverse() const { return *model->cverse(); }

			// stage:

				nik_ce stage_ctype_ref cstage() const { return *model->cstage(); }
	};

/***********************************************************************************************************************/

// mutable:

	template<typename Model>
	class machine_facade
	{
		public:

			using facade			= machine_facade; // method compatible.

			using model_type		= Model;
			using model_type_ptr		= typename alias<model_type>::type_ptr;
			using model_type_cptr		= typename alias<model_type>::type_cptr;

			using contr_type		= typename model_type::contr_type;
			using contr_ctype_ref		= typename alias<contr_type>::ctype_ref;

			using carry_type		= typename model_type::carry_type;
			using carry_type_ref		= typename alias<carry_type>::type_ref;
			using carry_ctype_ref		= typename alias<carry_type>::ctype_ref;

			using verse_type		= typename model_type::verse_type;
			using verse_type_ref		= typename alias<verse_type>::type_ref;
			using verse_ctype_ref		= typename alias<verse_type>::ctype_ref;

			using stage_type		= typename model_type::stage_type;
			using stage_type_ref		= typename alias<stage_type>::type_ref;
			using stage_ctype_ref		= typename alias<stage_type>::ctype_ref;

			nik_using_name_scope_type	( type, model_type)
			nik_using_name_scope_ctype	(ctype, model_type)

			nik_using_size_type_scope	(model_type)

		protected:

			model_type_ptr model;

		public:

			nik_ce machine_facade() : model{} { }
			nik_ce machine_facade(model_type_cptr m) : model{m} { }

			// contr:

				nik_ce contr_ctype_ref ccontr() const { return *model->ccontr(); }

			// counter:

				nik_ce size_type counter() const { return model->counter(); }
				nik_ce void set_counter(size_ctype c) { model->set_counter(c); }
				nik_ce void inc_counter(size_ctype n = 1) { model->inc_counter(n); }

			// carry:

				nik_ce carry_ctype_ref ccarry() const { return *model->ccarry(); }
				nik_ce  carry_type_ref  carry()       { return *model-> carry(); }

			// verse:

				nik_ce verse_ctype_ref cverse() const { return *model->cverse(); }
				nik_ce  verse_type_ref  verse()       { return *model-> verse(); }

			// stage:

				nik_ce stage_ctype_ref cstage() const { return *model->cstage(); }
				nik_ce  stage_type_ref  stage()       { return *model-> stage(); }
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
	class machine : public machine_model<Type, SizeType, ContrSize, CarrySize, VerseSize, StageSize>
	{
		public:

			using base			= machine_model
							<
								Type, SizeType,
								ContrSize, CarrySize, VerseSize, StageSize
							>;
			using model_type		= base;
			using cfacade_type		= machine_cfacade<model_type>;
			using facade_type		= machine_facade<model_type>;

			using contr_type		= typename model_type::contr_type;

			nik_using_name_scope_type	( type, base)
			nik_using_name_scope_ctype	(ctype, base)

			nik_using_size_type_scope	(base)

		public:

			nik_ce machine() : base{} { }
			nik_ce machine(const contr_type & c) : base{c} { }

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
	class machine_cmethod_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;
			using model_type		= typename facade::model_type;

			nik_using_name_scope_type	( type, base)
			nik_using_name_scope_ctype	(ctype, base)

			nik_using_size_type_scope	(base)

	//	protected: // debugging:

			using contr_csubmethod_type  = typename model_type::contr_csubmethod_type;

			using carry_csubmethod_type  = typename model_type::carry_csubmethod_type;
			using verse_csubmethod_type  = typename model_type::verse_csubmethod_type;
			using stage_csubmethod_type  = typename model_type::stage_csubmethod_type;

			contr_csubmethod_type  contr_csubmethod;

			carry_csubmethod_type  carry_csubmethod;
			verse_csubmethod_type  verse_csubmethod;
			stage_csubmethod_type  stage_csubmethod;

		protected:

			nik_ce void initialize() // call only once.
			{
				size_ctype row_size = (base::ccontr().size() >> 2);
				size_ctype col_size = 4;
				contr_csubmethod.fast_full_set();
				contr_csubmethod.set_dimension(row_size, col_size);

			//	carry_csubmethod.fast_full_set();
			//	verse_csubmethod.fast_full_set();
			//	stage_csubmethod.fast_full_set();
			}

		public:

			nik_ce machine_cmethod_disjoint() : base{} { initialize(); }
			nik_ce machine_cmethod_disjoint(const facade & f) :

				base{f},
				contr_csubmethod {base::model->contr_csubequip()},
				carry_csubmethod {base::model->carry_csubequip()},
				verse_csubmethod {base::model->verse_csubequip()},
				stage_csubmethod {base::model->stage_csubequip()}
				{ initialize(); }

			nik_ce auto contr_value(size_ctype row, size_ctype col) const
				{ return contr_csubmethod[row][col]; }

			nik_ce auto contr_current_value(size_ctype col) const
				{ return contr_value(base::counter(), col); }

			// carry:

				nik_ce auto rtn_cbegin () const { return base::ccarry().cbegin (); }
				nik_ce auto rtn_cend   () const { return base::ccarry().cend   (); }
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

			using carry_submethod_type = typename model_type::carry_submethod_type;
			using verse_submethod_type = typename model_type::verse_submethod_type;
			using stage_submethod_type = typename model_type::stage_submethod_type;

			carry_submethod_type carry_submethod;
			verse_submethod_type verse_submethod;
			stage_submethod_type stage_submethod;

		protected:

			nik_ce void initialize() // call only once.
			{
			//	carry_submethod.fast_full_set();
			//	verse_submethod.fast_full_set();
			//	stage_submethod.fast_full_set();
			}

		public:

			nik_ce machine_method_disjoint() : base{} { initialize(); }
			nik_ce machine_method_disjoint(const facade & f) :

				base{f},
				carry_submethod{base::model->carry_subequip()},
				verse_submethod{base::model->verse_subequip()},
				stage_submethod{base::model->stage_subequip()}
				{ initialize(); }

			// reset:

				nik_ce void reset()
				{
					base::set_counter(0);

					base::carry().clear();
					base::verse().clear();
					base::stage().clear();
				}
	};

	// syntactic sugar:

		template<typename Facade>
		using machine_method =
			machine_method_disjoint  <
			machine_cmethod_disjoint < Facade >>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// action:

/***********************************************************************************************************************/

// instructions:

	struct MachineInstruction
	{
		enum : genum_type
		{
			// core:

				program, function, memory_to_stack, apply,

			// ring:

				add, subtract, multiply, divide, modulo,

				dimension
		};
	};

	using MI = MachineInstruction;

/***********************************************************************************************************************/

// policies:

	struct MachinePolicy { enum : genum_type { to_stack, to_carry, dimension }; };

	using MP = MachinePolicy;

/***********************************************************************************************************************/

// interface:

	template<typename Eval, typename Contr, typename SizeType>
	struct MachineAction
	{
		using eval_type			= Eval;
		using eval_type_ptr		= typename alias<eval_type>::type_ptr;

		using contr_ctype_ref		= Contr const&;

		using method_type		= void(*)(eval_type_ptr, contr_ctype_ref);

		nik_using_size_type_alias	(SizeType)

		// utility:

			nik_ces auto & machine(eval_type_ptr eval) { return eval->_machine; }

		// core:

			nik_ces void program(eval_type_ptr eval, contr_ctype_ref contr)
				{ } // nothing.

			nik_ces void function(eval_type_ptr eval, contr_ctype_ref contr)
			{
				size_ctype value  = contr[machine(eval).counter()][1];
				size_ctype policy = contr[machine(eval).counter()][2];

				if      (policy == MP::to_stack) { machine(eval).stage()->push(value); }
				else if (policy == MP::to_carry) { machine(eval).carry()->push(value); }
			}

			nik_ces void memory_to_stack(eval_type_ptr eval, contr_ctype_ref contr)
			{
				auto begin = machine(eval).cverse()->citer(contr[eval->_machine.counter()][1]);
				auto end   = machine(eval).cverse()->citer(contr[eval->_machine.counter()][2]);

				machine(eval).stage()->push(begin, end);
			}

			nik_ces void apply(eval_type_ptr eval, contr_ctype_ref contr)
			{
				size_ctype offset = contr[machine(eval).counter()][1];
				size_ctype policy = contr[machine(eval).counter()][2];

				auto subeval      = eval_type{*machine(eval).ccontr()};
				auto stage_start  = offset;
				auto stage_finish = machine(eval).cstage()->size();

				machine(&subeval).set_counter(machine(eval).cstage()->cat(stage_start));
				auto stage_begin = machine(eval).cstage()->citer(stage_start + 1);
				auto stage_end   = machine(eval).cstage()->citer(stage_finish);
				subeval.run(stage_begin, stage_end);

				auto subcarry_begin = machine(&subeval).ccarry()->cbegin();
				auto subcarry_end   = machine(&subeval).ccarry()->cend();

				if (policy == MP::to_stack)
				{
					machine(eval).stage()->downsize(stage_finish - stage_start);
					machine(eval).stage()->push(subcarry_begin, subcarry_end);
				}
				else if (policy == MP::to_carry)
				{
					machine(eval).carry()->push(subcarry_begin, subcarry_end);
				}
			}

		// ring:

			nik_ces void add(eval_type_ptr eval, contr_ctype_ref contr)
			{
				machine(eval).carry()->clear();

				auto b = machine(eval).cverse()->cbegin();
				auto e = machine(eval).cverse()->cend();

				size_type k = 0;
				while (b != e) { k += *b++; }

				machine(eval).carry()->push(k);
			}

			nik_ces void subtract(eval_type_ptr eval, contr_ctype_ref contr)
			{
			}

			nik_ces void multiply(eval_type_ptr eval, contr_ctype_ref contr)
			{
				machine(eval).carry()->clear();

				auto b = machine(eval).cverse()->cbegin();
				auto e = machine(eval).cverse()->cend();

				size_type k = 1;
				while (b != e) { k *= *b++; }

				machine(eval).carry()->push(k);
			}

			nik_ces void divide(eval_type_ptr eval, contr_ctype_ref contr)
			{
			}

			nik_ces void modulo(eval_type_ptr eval, contr_ctype_ref contr)
			{
			}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// eval:

/***********************************************************************************************************************/

// interface:

	template
	<
		typename Type, typename SizeType,
		SizeType ContrSize, SizeType CarrySize, SizeType VerseSize, SizeType StageSize
	>
	class eval
	{
		public:

			using machine_type		= machine
							<
								Type, SizeType,
								ContrSize, CarrySize, VerseSize, StageSize
							>;
			using machine_method_type	= resolve_method<machine_type, machine_method>;

			nik_using_name_scope_type	( type, machine_type)
			nik_using_name_scope_ctype	(ctype, machine_type)

			nik_using_size_type_scope	(machine_type)

		protected:

			using machine_model_type	= typename machine_type::model_type;
			using contr_csubmethod_type	= typename machine_model_type::contr_csubmethod_type;
			using contr_type		= typename machine_model_type::contr_type;
			using ma_type			= MachineAction<eval, contr_csubmethod_type, size_type>;

		public:

			using action_method_type	= typename ma_type::method_type;
			using action_type		= array<action_method_type, SizeType, MI::dimension>;

			using action_csubmethod_type	= resolve_csubmethod<action_type, array_csubmethod>;

	//	protected: // debugging.

			machine_type _machine;
			action_type _action;

		protected:

			nik_ce void initialize() { set_action(); } // call only once.

			nik_ce void set_action() // call only once.
			{
				_action.fullsize();

				_action[ MI::program         ] = ma_type::program         ;
				_action[ MI::function        ] = ma_type::function        ;
				_action[ MI::memory_to_stack ] = ma_type::memory_to_stack ;
				_action[ MI::apply           ] = ma_type::apply           ;
				_action[ MI::add             ] = ma_type::add             ;
				_action[ MI::subtract        ] = ma_type::subtract        ;
				_action[ MI::multiply        ] = ma_type::multiply        ;
				_action[ MI::divide          ] = ma_type::divide          ;
				_action[ MI::modulo          ] = ma_type::modulo          ;
			}

		public:

			nik_ce eval() : _machine{}, _action{} { initialize(); }
			nik_ce eval(const contr_type & c) : _machine{c}, _action{} { initialize(); }

		protected:

			nik_ce auto make_machine_method() { return _machine.template equip<machine_method_type>(); }

			nik_ce void execute()
			{
				auto mach_method = make_machine_method();
				size_ctype instr = mach_method.contr_current_value(0);

				_action[instr](this, mach_method.contr_csubmethod);
			}

		public:

			nik_ce void run(ctype_ptr in, ctype_cptr end) // assumes counter is set before calling.
			{
				auto mach_method = make_machine_method();

				_machine.verse()->push(in, end);

				while (mach_method.contr_current_value(3))
				{
					_machine.inc_counter();
					execute();
				}
			}

			template<auto N> // const verse_type & ?
			nik_ce void run(ctype (&v)[N]) { run(v, v + N); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

