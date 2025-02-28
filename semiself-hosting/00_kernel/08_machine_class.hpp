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

// machine class:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// virtual machine:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// model:

	template<typename> class machine_cfacade;
	template<typename> class machine_facade;

/***********************************************************************************************************************/

// mutable:

	template<typename Type, typename SizeType, SizeType CarrySize, SizeType VerseSize, SizeType StageSize>
	class machine
	{
		public:

			using facade				= machine; // method compatible.
			using cfacade_type			= machine_cfacade<machine>;
			using facade_type			= machine_facade<machine>;

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

			nik_ce machine() : _counter{} { }

			// equip:

				template<typename CMethod>
				nik_ce auto cequip() const -> CMethod
					{ return cfacade_type{static_cast<machine const*>(this)}; }

				template<typename Method>
				nik_ce auto equip() -> Method
					{ return facade_type{static_cast<machine*>(this)}; }

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

			// counter:

				nik_ce size_type counter() const { return _counter; }
				nik_ce void set_counter(size_ctype c)     { _counter  = c; }
				nik_ce void inc_counter(size_ctype n = 1) { _counter += n; }
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

			// carry:

				nik_ce carry_ctype_ref ccarry() const { return *model->ccarry(); }

			// verse:

				nik_ce verse_ctype_ref cverse() const { return *model->cverse(); }

			// stage:

				nik_ce stage_ctype_ref cstage() const { return *model->cstage(); }

			// counter:

				nik_ce size_type counter() const { return model->counter(); }
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

			// carry:

				nik_ce carry_ctype_ref ccarry() const { return *model->ccarry(); }
				nik_ce  carry_type_ref  carry()       { return *model-> carry(); }

			// verse:

				nik_ce verse_ctype_ref cverse() const { return *model->cverse(); }
				nik_ce  verse_type_ref  verse()       { return *model-> verse(); }

			// stage:

				nik_ce stage_ctype_ref cstage() const { return *model->cstage(); }
				nik_ce  stage_type_ref  stage()       { return *model-> stage(); }

			// counter:

				nik_ce size_type counter() const { return model->counter(); }
				nik_ce void set_counter(size_ctype c) { model->set_counter(c); }
				nik_ce void inc_counter(size_ctype n = 1) { model->inc_counter(n); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// action:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// atomic:

/***********************************************************************************************************************/

// instructions:

	struct AtomicInstr
	{
		enum : genum_type
		{
			// compare:

				equal, not_equal, l_than, l_than_or_eq, g_than, g_than_or_eq,

			// arithmetic:

				add, subtract, multiply, divide, modulo,

			// dimension

				dimension
		};
	};

	using AI = AtomicInstr;

/***********************************************************************************************************************/

// interface:

	template<typename Type, typename SizeType>
	struct atomic_action
	{
		nik_using_name_alias_scope_type		( type, Type)
		nik_using_name_alias_scope_ctype	(ctype, Type)

		nik_using_size_type_alias		(SizeType)

		using method_type			= type(*)(ctype, ctype);
		using action_type			= array<method_type, size_type, AI::dimension>;

		// compare:

			nik_ces type equal        (ctype v1, ctype v2) { return (v1 == v2); }
			nik_ces type not_equal    (ctype v1, ctype v2) { return (v1 != v2); }
			nik_ces type l_than       (ctype v1, ctype v2) { return (v1 <  v2); }
			nik_ces type l_than_or_eq (ctype v1, ctype v2) { return (v1 <= v2); }
			nik_ces type g_than       (ctype v1, ctype v2) { return (v1 >  v2); }
			nik_ces type g_than_or_eq (ctype v1, ctype v2) { return (v1 >= v2); }

		// arithmetic:

			nik_ces type add          (ctype v1, ctype v2) { return (v1  + v2); }
			nik_ces type subtract     (ctype v1, ctype v2) { return (v1  - v2); }
			nik_ces type multiply     (ctype v1, ctype v2) { return (v1  * v2); }
			nik_ces type divide       (ctype v1, ctype v2) { return (v1  / v2); }
			nik_ces type modulo       (ctype v1, ctype v2) { return (v1  % v2); }

		// action:

			nik_ces auto set_action() // call only once.
			{
				action_type action;
				action.fullsize();

				// compare:

					action[ AI::equal        ] = equal        ;
					action[ AI::not_equal    ] = not_equal    ;
					action[ AI::l_than       ] = l_than       ;
					action[ AI::l_than_or_eq ] = l_than_or_eq ;
					action[ AI::g_than       ] = g_than       ;
					action[ AI::g_than_or_eq ] = g_than_or_eq ;

				// arithmetic:

					action[ AI::add          ] = add          ;
					action[ AI::subtract     ] = subtract     ;
					action[ AI::multiply     ] = multiply     ;
					action[ AI::divide       ] = divide       ;
					action[ AI::modulo       ] = modulo       ;

				return action;
			}

			nik_ces auto action = set_action();
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// machine:

/***********************************************************************************************************************/

// instructions:

	struct MachineInstr : public AtomicInstr
	{
		enum : genum_type
		{
			// core:

				program = AI::dimension,
				define_argument, branch, invert, apply, constant, function, argument,
				memory_to_stack, memory_to_stage = memory_to_stack, memory_to_carry,

			// dimension

				dimension
		};
	};

	using MI = MachineInstr;

/***********************************************************************************************************************/

// policies:

	struct MachinePolicy { enum : genum_type { to_stack, to_stage = to_stack, to_carry, dimension }; };

	using MP = MachinePolicy;

/***********************************************************************************************************************/

// fields:

	struct MachineProgram		{ enum : genum_type { action,  lines, atomic,   next, dimension }; };
	struct MachineArgument		{ enum : genum_type { action,  index,  start, finish, dimension }; };
	struct MachineBranch		{ enum : genum_type { action,   line,   none,   next, dimension }; };
	struct MachineApply		{ enum : genum_type { action, offset, policy,   next, dimension }; };
	struct MachineValue		{ enum : genum_type { action,   line, policy,   next, dimension }; };
	struct MachineMove		{ enum : genum_type { action,  start, finish,   next, dimension }; };

	using MProg			= MachineProgram;
	using MArg			= MachineArgument;
	using MBran			= MachineBranch;
	using MAppl			= MachineApply;
	using MVal			= MachineValue;
	using MMove			= MachineMove;

/***********************************************************************************************************************/

// interface:

	template<typename EvalMethod, typename SizeType>
	struct machine_action
	{
		using eval_method_type		= EvalMethod;
		using eval_method_type_ptr	= typename alias<eval_method_type>::type_ptr;

		nik_using_size_type_alias	(SizeType)

		using method_type		= void(*)(eval_method_type_ptr);
		using action_type		= array<method_type, size_type, MI::dimension>;

		nik_ces void symbolic(eval_method_type_ptr) { } // do nothing.

		// atomic:

			template<size_type n>
			nik_ces void atomic(eval_method_type_ptr eval_method) { eval_method->atomic(n); }

		// core:

			nik_ces void branch(eval_method_type_ptr eval_method)
				{ eval_method->run_branch(); }

			nik_ces void invert(eval_method_type_ptr eval_method)
				{ eval_method->run_invert(); }

			nik_ces void apply(eval_method_type_ptr eval_method)
				{ eval_method->run_apply(); }

			nik_ces void constant(eval_method_type_ptr eval_method)
				{ eval_method->run_constant(); }

			nik_ces void function(eval_method_type_ptr eval_method)
				{ eval_method->run_function(); }

			nik_ces void argument(eval_method_type_ptr eval_method)
				{ eval_method->run_argument(); }

			nik_ces void memory_to_stage(eval_method_type_ptr eval_method)
				{ eval_method->run_memory_to_stage(); }

			nik_ces void memory_to_carry(eval_method_type_ptr eval_method)
				{ eval_method->run_memory_to_carry(); }

		// action:

			nik_ces auto set_action() // call only once.
			{
				action_type action;
				action.fullsize();

				// compare:

					action[ MI::equal        ] = atomic < AI::equal        >;
					action[ MI::not_equal    ] = atomic < AI::not_equal    >;
					action[ MI::l_than       ] = atomic < AI::l_than       >;
					action[ MI::l_than_or_eq ] = atomic < AI::l_than_or_eq >;
					action[ MI::g_than       ] = atomic < AI::g_than       >;
					action[ MI::g_than_or_eq ] = atomic < AI::g_than_or_eq >;

				// arithmetic:

					action[ MI::add          ] = atomic < AI::add          >;
					action[ MI::subtract     ] = atomic < AI::subtract     >;
					action[ MI::multiply     ] = atomic < AI::multiply     >;
					action[ MI::divide       ] = atomic < AI::divide       >;
					action[ MI::modulo       ] = atomic < AI::modulo       >;

				// core:

					action[ MI::program         ] = symbolic        ;
					action[ MI::define_argument ] = symbolic        ;
					action[ MI::branch          ] = branch          ;
					action[ MI::invert          ] = invert          ;
					action[ MI::apply           ] = apply           ;
					action[ MI::constant        ] = constant        ;
					action[ MI::function        ] = function        ;
					action[ MI::argument        ] = argument        ;
					action[ MI::memory_to_stage ] = memory_to_stage ;
					action[ MI::memory_to_carry ] = memory_to_carry ;

				return action;
			}

			nik_ces auto action = set_action();

			nik_ces void execute(size_ctype instr, eval_method_type_ptr eval_method)
				{ action[instr](eval_method); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

