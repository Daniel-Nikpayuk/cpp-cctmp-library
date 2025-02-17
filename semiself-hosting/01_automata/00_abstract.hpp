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

// abstract:

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

	template<typename Type, typename SizeType, SizeType CarrySize, SizeType VerseSize, SizeType StageSize>
	class machine_model
	{
		public:

			using facade				= machine_model; // method compatible.

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

			using carry_csubmethod_type		= resolve_csubmethod<carry_type, array_csubmethod>;
			using  carry_submethod_type		=  resolve_submethod<carry_type,  array_submethod>;

			using verse_csubmethod_type		= resolve_csubmethod<verse_type, array_csubmethod>;
			using  verse_submethod_type		=  resolve_submethod<verse_type,  array_submethod>;

			using stage_csubmethod_type		= resolve_csubmethod<stage_type, array_csubmethod>;
			using  stage_submethod_type		=  resolve_submethod<stage_type,  array_submethod>;

		protected:

			carry_type _carry;
			verse_type _verse;
			stage_type _stage;
			size_type  _counter;

		public:

			nik_ce machine_model() : _counter{} { }

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

	template<typename Type, typename SizeType, SizeType CarrySize, SizeType VerseSize, SizeType StageSize>
	class machine : public machine_model<Type, SizeType, CarrySize, VerseSize, StageSize>
	{
		public:

			using base			= machine_model<Type, SizeType, CarrySize, VerseSize, StageSize>;
			using model_type		= base;
			using cfacade_type		= machine_cfacade<model_type>;
			using facade_type		= machine_facade<model_type>;

			nik_using_name_scope_type	( type, base)
			nik_using_name_scope_ctype	(ctype, base)

			nik_using_size_type_scope	(base)

		public:

			nik_ce machine() : base{} { }

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

			using carry_csubmethod_type  = typename model_type::carry_csubmethod_type;
			using verse_csubmethod_type  = typename model_type::verse_csubmethod_type;
			using stage_csubmethod_type  = typename model_type::stage_csubmethod_type;

			carry_csubmethod_type  carry_csubmethod;
			verse_csubmethod_type  verse_csubmethod;
			stage_csubmethod_type  stage_csubmethod;

		protected:

			nik_ce void initialize() // call only once.
			{
			//	carry_csubmethod.fast_full_set();
			//	verse_csubmethod.fast_full_set();
			//	stage_csubmethod.fast_full_set();
			}

		public:

			nik_ce machine_cmethod_disjoint() : base{} { initialize(); }
			nik_ce machine_cmethod_disjoint(const facade & f) :

				base{f},
				carry_csubmethod {base::model->carry_csubequip()},
				verse_csubmethod {base::model->verse_csubequip()},
				stage_csubmethod {base::model->stage_csubequip()}
				{ initialize(); }

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

	template<typename EvalMethod, typename Contr, typename SizeType>
	struct machine_action
	{
		using eval_method_type		= EvalMethod;
		using eval_method_type_ptr	= typename alias<eval_method_type>::type_ptr;

		using contr_ctype_ref		= Contr const&;

		using method_type		= void(*)(eval_method_type_ptr, contr_ctype_ref);
		using action_type		= array<method_type, SizeType, MI::dimension>;

		nik_using_size_type_alias	(SizeType)

		// utility:

			nik_ces auto & machine(eval_method_type_ptr eval_method) { return eval_method->_machine; }

		// core:

			nik_ces void program(eval_method_type_ptr eval_method, contr_ctype_ref contr)
				{ } // nothing.

			nik_ces void function(eval_method_type_ptr eval_method, contr_ctype_ref contr)
			{
				size_ctype value  = contr[machine(eval_method).counter()][1];
				size_ctype policy = contr[machine(eval_method).counter()][2];

				if      (policy == MP::to_stack) { machine(eval_method).stage()->push(value); }
				else if (policy == MP::to_carry) { machine(eval_method).carry()->push(value); }
			}

			nik_ces void memory_to_stack(eval_method_type_ptr eval_method, contr_ctype_ref contr)
			{
				auto begin = machine(eval_method).cverse()->citer(contr[eval_method->_machine.counter()][1]);
				auto end   = machine(eval_method).cverse()->citer(contr[eval_method->_machine.counter()][2]);

				machine(eval_method).stage()->push(begin, end);
			}

			nik_ces void apply(eval_method_type_ptr eval_method, contr_ctype_ref contr)
			{
				size_ctype offset = contr[machine(eval_method).counter()][1];
				size_ctype policy = contr[machine(eval_method).counter()][2];

				auto subeval      = eval_method->again();
				auto stage_start  = offset;
				auto stage_finish = machine(eval_method).cstage()->size();

				machine(&subeval).set_counter(machine(eval_method).cstage()->cat(stage_start));
				auto stage_begin = machine(eval_method).cstage()->citer(stage_start + 1);
				auto stage_end   = machine(eval_method).cstage()->citer(stage_finish);
				auto carry       = subeval.run(stage_begin, stage_end);

				auto subcarry_begin = machine(&subeval).ccarry()->cbegin();
				auto subcarry_end   = machine(&subeval).ccarry()->cend();

				if (policy == MP::to_stack)
				{
					machine(eval_method).stage()->downsize(stage_finish - stage_start);
					machine(eval_method).stage()->push(subcarry_begin, subcarry_end);
				}
				else if (policy == MP::to_carry)
				{
					machine(eval_method).carry()->push(subcarry_begin, subcarry_end);
				}
			}

		// ring:

			nik_ces void add(eval_method_type_ptr eval_method, contr_ctype_ref contr)
			{
				machine(eval_method).carry()->clear();

				auto b = machine(eval_method).cverse()->cbegin();
				auto e = machine(eval_method).cverse()->cend();

				size_type k = 0;
				while (b != e) { k += *b++; }

				machine(eval_method).carry()->push(k);
			}

			nik_ces void subtract(eval_method_type_ptr eval_method, contr_ctype_ref contr)
			{
			}

			nik_ces void multiply(eval_method_type_ptr eval_method, contr_ctype_ref contr)
			{
				machine(eval_method).carry()->clear();

				auto b = machine(eval_method).cverse()->cbegin();
				auto e = machine(eval_method).cverse()->cend();

				size_type k = 1;
				while (b != e) { k *= *b++; }

				machine(eval_method).carry()->push(k);
			}

			nik_ces void divide(eval_method_type_ptr eval_method, contr_ctype_ref contr)
			{
			}

			nik_ces void modulo(eval_method_type_ptr eval_method, contr_ctype_ref contr)
			{
			}

		// action:

			nik_ces auto set_action() // call only once.
			{
				action_type action;
				action.fullsize();

				action[ MI::program         ] = program         ;
				action[ MI::function        ] = function        ;
				action[ MI::memory_to_stack ] = memory_to_stack ;
				action[ MI::apply           ] = apply           ;
				action[ MI::add             ] = add             ;
				action[ MI::subtract        ] = subtract        ;
				action[ MI::multiply        ] = multiply        ;
				action[ MI::divide          ] = divide          ;
				action[ MI::modulo          ] = modulo          ;

				return action;
			}

			nik_ces auto action = set_action();

			nik_ces void execute(size_ctype instr, eval_method_type_ptr eval_method, contr_ctype_ref contr)
				{ action[instr](eval_method, contr); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

