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

// memory class:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// (simulant) memory:

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
			// comparison:

				equal, not_equal, l_than, l_than_or_eq, g_than, g_than_or_eq,

			// arithmetic:

				add, subtract, multiply, divide, modulo,

			// dimension

				dimension
		};
	};

	using AI = AtomicInstr;

/***********************************************************************************************************************/

// operator:

	// comparison:

		// equal:

			template<typename...>
			struct T_equal
			{
				template<typename... Ts>
				nik_ces auto result(Ts... vs) { return (... == vs); }
			};

			template<typename T>
			struct T_equal<T>
			{
				template<typename... Ts>
				nik_ces auto result(Ts... vs) -> T { return (... == vs); }
			};

		// not equal:

			template<typename...>
			struct T_not_equal
			{
				template<typename... Ts>
				nik_ces auto result(Ts... vs) { return (... != vs); }
			};

			template<typename T>
			struct T_not_equal<T>
			{
				template<typename... Ts>
				nik_ces auto result(Ts... vs) -> T { return (... != vs); }
			};

		// less than:

			template<typename...>
			struct T_l_than
			{
				template<typename... Ts>
				nik_ces auto result(Ts... vs) { return (... < vs); }
			};

			template<typename T>
			struct T_l_than<T>
			{
				template<typename... Ts>
				nik_ces auto result(Ts... vs) -> T { return (... < vs); }
			};

		// less than or equal:

			template<typename...>
			struct T_l_than_or_eq
			{
				template<typename... Ts>
				nik_ces auto result(Ts... vs) { return (... <= vs); }
			};

			template<typename T>
			struct T_l_than_or_eq<T>
			{
				template<typename... Ts>
				nik_ces auto result(Ts... vs) -> T { return (... <= vs); }
			};

		// greater than:

			template<typename...>
			struct T_g_than
			{
				template<typename... Ts>
				nik_ces auto result(Ts... vs) { return (... > vs); }
			};

			template<typename T>
			struct T_g_than<T>
			{
				template<typename... Ts>
				nik_ces auto result(Ts... vs) -> T { return (... > vs); }
			};

		// greater than or equal:

			template<typename...>
			struct T_g_than_or_eq
			{
				template<typename... Ts>
				nik_ces auto result(Ts... vs) { return (... >= vs); }
			};

			template<typename T>
			struct T_g_than_or_eq<T>
			{
				template<typename... Ts>
				nik_ces auto result(Ts... vs) -> T { return (... >= vs); }
			};

	// arithmetic:

		// add:

			template<typename...>
			struct T_add
			{
				template<typename... Ts>
				nik_ces auto result(Ts... vs) { return (... + vs); }
			};

			template<typename T>
			struct T_add<T>
			{
				template<typename... Ts>
				nik_ces auto result(Ts... vs) -> T { return (... + vs); }
			};

		// subtract:

			template<typename...>
			struct T_subtract
			{
				template<typename... Ts>
				nik_ces auto result(Ts... vs) { return (... - vs); }
			};

			template<typename T>
			struct T_subtract<T>
			{
				template<typename... Ts>
				nik_ces auto result(Ts... vs) -> T { return (... - vs); }
			};

		// multiply:

			template<typename...>
			struct T_multiply
			{
				template<typename... Ts>
				nik_ces auto result(Ts... vs) { return (... * vs); }
			};

			template<typename T>
			struct T_multiply<T>
			{
				template<typename... Ts>
				nik_ces auto result(Ts... vs) -> T { return (... * vs); }
			};

		// divide:

			template<typename...>
			struct T_divide
			{
				template<typename... Ts>
				nik_ces auto result(Ts... vs) { return (... / vs); }
			};

			template<typename T>
			struct T_divide<T>
			{
				template<typename... Ts>
				nik_ces auto result(Ts... vs) -> T { return (... / vs); }
			};

		// modulo:

			template<typename...>
			struct T_modulo
			{
				template<typename... Ts>
				nik_ces auto result(Ts... vs) { return (... % vs); }
			};

			template<typename T>
			struct T_modulo<T>
			{
				template<typename... Ts>
				nik_ces auto result(Ts... vs) -> T { return (... % vs); }
			};

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

		// action:

			nik_ces auto set_action() // call only once.
			{
				action_type action;
				action.fullsize();

			// comparison:

				action[ AI::equal        ] = T_equal        <type>::template result<type, type>;
				action[ AI::not_equal    ] = T_not_equal    <type>::template result<type, type>;
				action[ AI::l_than       ] = T_l_than       <type>::template result<type, type>;
				action[ AI::l_than_or_eq ] = T_l_than_or_eq <type>::template result<type, type>;
				action[ AI::g_than       ] = T_g_than       <type>::template result<type, type>;
				action[ AI::g_than_or_eq ] = T_g_than_or_eq <type>::template result<type, type>;

			// arithmetic:

				action[ AI::add          ] = T_add          <type>::template result<type, type>;
				action[ AI::subtract     ] = T_subtract     <type>::template result<type, type>;
				action[ AI::multiply     ] = T_multiply     <type>::template result<type, type>;
				action[ AI::divide       ] = T_divide       <type>::template result<type, type>;
				action[ AI::modulo       ] = T_modulo       <type>::template result<type, type>;

				return action;
			}

			nik_ces auto action = set_action();
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// compound:

/***********************************************************************************************************************/

// instructions:

	struct CompoundInstr : public AtomicInstr
	{
		enum : genum_type
		{
			// core:

				// dimension == 11
				program = AI::dimension, halt,
				function_specs, argument_specs,
				argument, branch, invert, apply,
				atomic, constant, function, recursive,
				memory_to_stack, memory_to_stage = memory_to_stack, memory_to_carry,

			// dimension

				dimension
		};
	};

	using CI = CompoundInstr;

/***********************************************************************************************************************/

// policies:

	struct CompoundPolicy { enum : genum_type { to_stack, to_stage = to_stack, to_carry, dimension }; };

	using CP = CompoundPolicy;

/***********************************************************************************************************************/

// fields:

	struct CompoundProgram		{ enum : genum_type { action,  lines, atomic,   next, dimension }; };
	struct CompoundArgument		{ enum : genum_type { action,  index,  start, finish, dimension }; };
	struct CompoundBranch		{ enum : genum_type { action,   line,   none,   next, dimension }; };
	struct CompoundApply		{ enum : genum_type { action, offset, policy,   next, dimension }; };
	struct CompoundValue		{ enum : genum_type { action,   line, policy,   next, dimension }; };
	struct CompoundMove		{ enum : genum_type { action,  start, finish,   next, dimension }; };

	using CProg			= CompoundProgram;
	using CArg			= CompoundArgument;
	using CBran			= CompoundBranch;
	using CAppl			= CompoundApply;
	using CVal			= CompoundValue;
	using CMove			= CompoundMove;

/***********************************************************************************************************************/

// interface:

	template<typename EvalMethod, typename SizeType>
	struct memory_action
	{
		using eval_method_type		= EvalMethod;
		using eval_method_type_ptr	= typename alias<eval_method_type>::type_ptr;

		nik_using_size_type_alias	(SizeType)

		using method_type		= void(*)(eval_method_type_ptr);
		using action_type		= array<method_type, size_type, CI::dimension>;

	//	nik_ces void symbolic(eval_method_type_ptr) { } // do nothing.

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

				// comparison:

					action[ CI::equal        ] = atomic < AI::equal        >;
					action[ CI::not_equal    ] = atomic < AI::not_equal    >;
					action[ CI::l_than       ] = atomic < AI::l_than       >;
					action[ CI::l_than_or_eq ] = atomic < AI::l_than_or_eq >;
					action[ CI::g_than       ] = atomic < AI::g_than       >;
					action[ CI::g_than_or_eq ] = atomic < AI::g_than_or_eq >;

				// arithmetic:

					action[ CI::add          ] = atomic < AI::add          >;
					action[ CI::subtract     ] = atomic < AI::subtract     >;
					action[ CI::multiply     ] = atomic < AI::multiply     >;
					action[ CI::divide       ] = atomic < AI::divide       >;
					action[ CI::modulo       ] = atomic < AI::modulo       >;

				// core:

					action[ CI::argument        ] = argument        ;
					action[ CI::branch          ] = branch          ;
					action[ CI::invert          ] = invert          ;
					action[ CI::apply           ] = apply           ;
					action[ CI::constant        ] = constant        ;
					action[ CI::function        ] = function        ;
					action[ CI::memory_to_stage ] = memory_to_stage ;
					action[ CI::memory_to_carry ] = memory_to_carry ;

				return action;
			}

			nik_ces auto action = set_action();

			nik_ces void execute(size_ctype instr, eval_method_type_ptr eval_method)
				{ action[instr](eval_method); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// model:

	template<typename> class memory_cfacade;
	template<typename> class memory_facade;

/***********************************************************************************************************************/

// mutable:

	template<typename Type, typename SizeType, SizeType CarrySize, SizeType VerseSize, SizeType StageSize>
	class memory
	{
		public:

			using facade				= memory; // method compatible.
			using cfacade_type			= memory_cfacade<memory>;
			using facade_type			= memory_facade<memory>;

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

			nik_ce memory() : _counter{} { }

			// equip:

				template<typename CMethod>
				nik_ce auto cequip() const -> CMethod
					{ return cfacade_type{static_cast<memory const*>(this)}; }

				template<typename Method>
				nik_ce auto equip() -> Method
					{ return facade_type{static_cast<memory*>(this)}; }

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
	class memory_cfacade
	{
		public:

			using facade			= memory_cfacade; // method compatible.

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

			nik_ce memory_cfacade() : model{} { }
			nik_ce memory_cfacade(model_ctype_cptr m) : model{m} { }

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
	class memory_facade
	{
		public:

			using facade			= memory_facade; // method compatible.

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

			nik_ce memory_facade() : model{} { }
			nik_ce memory_facade(model_type_cptr m) : model{m} { }

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

} // namespace cctmp

