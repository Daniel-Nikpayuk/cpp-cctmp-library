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

// action:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// machine:

/***********************************************************************************************************************/

// instructions:

	struct MachineInstr
	{
		enum : genum_type
		{
			// core:

				program, function, memory_to_stack, apply,

			// compare:

				equal, not_equal, l_than, l_than_or_eq, g_than, g_than_or_eq,

			// arithmetic:

				add, subtract, multiply, divide, modulo,

			// dimension

				dimension
		};
	};

	using MI = MachineInstr;

/***********************************************************************************************************************/

// policies:

	struct MachinePolicy { enum : genum_type { to_stack, to_carry, dimension }; };

	using MP = MachinePolicy;

/***********************************************************************************************************************/

// fields:

	struct MachineProgram		{ enum : genum_type { action,  lines, atomic, next, dimension }; };
	struct MachineFunction		{ enum : genum_type { action,   line, policy, next, dimension }; };
	struct MachineMemoryToStack	{ enum : genum_type { action,  begin,    end, next, dimension }; };
	struct MachineApply		{ enum : genum_type { action, offset, policy, next, dimension }; };

	using MProg			= MachineProgram;
	using MFunc			= MachineFunction;
	using MMtoS			= MachineMemoryToStack;
	using MAppl			= MachineApply;

/***********************************************************************************************************************/

// interface:

	template<typename EvalMethod, typename SizeType>
	struct machine_action
	{
		using eval_method_type		= EvalMethod;
		using eval_method_type_ptr	= typename alias<eval_method_type>::type_ptr;

		using method_type		= void(*)(eval_method_type_ptr);
		using action_type		= array<method_type, SizeType, MI::dimension>;

		nik_using_size_type_alias	(SizeType)

		// utility:

			// nothing yet.

		// core:

			nik_ces void program(eval_method_type_ptr eval_method)
				{ } // nothing.

			nik_ces void function(eval_method_type_ptr eval_method)
			{
				size_ctype value  = eval_method->instr_value(MFunc::line);
				size_ctype policy = eval_method->instr_value(MFunc::policy);

				if      (policy == MP::to_stack) { eval_method->stage()->push(value); }
				else if (policy == MP::to_carry) { eval_method->carry()->push(value); }
			}

			nik_ces void memory_to_stack(eval_method_type_ptr eval_method)
			{
				auto begin = eval_method->cverse()->citer(eval_method->instr_value(MMtoS::begin));
				auto end   = eval_method->cverse()->citer(eval_method->instr_value(MMtoS::end  ));

				eval_method->stage()->push(begin, end);
			}

			nik_ces void apply(eval_method_type_ptr eval_method)
			{
				size_ctype offset = eval_method->instr_value(MAppl::offset);
				size_ctype policy = eval_method->instr_value(MAppl::policy);

				auto n_eval_method  = eval_method->again();
				auto stage_start    = offset;
				auto stage_finish   = eval_method->cstage()->size();

				n_eval_method       . set_counter(eval_method->cstage()->cat(stage_start));
				auto stage_begin    = eval_method->cstage()->citer(stage_start + 1);
				auto stage_end      = eval_method->cstage()->citer(stage_finish);
				auto carry          = n_eval_method.run(stage_begin, stage_end);

				auto subcarry_begin = n_eval_method.ccarry()->cbegin();
				auto subcarry_end   = n_eval_method.ccarry()->cend();

				if (policy == MP::to_stack)
				{
					eval_method->stage()->downsize(stage_finish - stage_start);
					eval_method->stage()->push(subcarry_begin, subcarry_end);
				}
				else if (policy == MP::to_carry)
				{
					eval_method->carry()->push(subcarry_begin, subcarry_end);
				}
			}

		// compare:

			nik_ces void equal        (eval_method_type_ptr eval_method) { eval_method->equal        (); }
			nik_ces void not_equal    (eval_method_type_ptr eval_method) { eval_method->not_equal    (); }
			nik_ces void l_than       (eval_method_type_ptr eval_method) { eval_method->l_than       (); }
			nik_ces void l_than_or_eq (eval_method_type_ptr eval_method) { eval_method->l_than_or_eq (); }
			nik_ces void g_than       (eval_method_type_ptr eval_method) { eval_method->g_than       (); }
			nik_ces void g_than_or_eq (eval_method_type_ptr eval_method) { eval_method->g_than_or_eq (); }

		// arithmetic:

			nik_ces void add      (eval_method_type_ptr eval_method) { eval_method->add     ( ); }
			nik_ces void subtract (eval_method_type_ptr eval_method) { eval_method->subtract( ); }
			nik_ces void multiply (eval_method_type_ptr eval_method) { eval_method->multiply( ); }
			nik_ces void divide   (eval_method_type_ptr eval_method) { eval_method->divide  ( ); }
			nik_ces void modulo   (eval_method_type_ptr eval_method) { eval_method->modulo  ( ); }

		// action:

			nik_ces auto set_action() // call only once.
			{
				action_type action;
				action.fullsize();

				// core:

					action[ MI::program         ] = program         ;
					action[ MI::function        ] = function        ;
					action[ MI::memory_to_stack ] = memory_to_stack ;
					action[ MI::apply           ] = apply           ;

				// compare:

					action[ MI::equal           ] = equal           ;
					action[ MI::not_equal       ] = not_equal       ;
					action[ MI::l_than          ] = l_than          ;
					action[ MI::l_than_or_eq    ] = l_than_or_eq    ;
					action[ MI::g_than          ] = g_than          ;
					action[ MI::g_than_or_eq    ] = g_than_or_eq    ;

				// arithmetic:

					action[ MI::add             ] = add             ;
					action[ MI::subtract        ] = subtract        ;
					action[ MI::multiply        ] = multiply        ;
					action[ MI::divide          ] = divide          ;
					action[ MI::modulo          ] = modulo          ;

				return action;
			}

			nik_ces auto action = set_action();

			nik_ces void execute(size_ctype instr, eval_method_type_ptr eval_method)
				{ action[instr](eval_method); }
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

			nik_ce auto contr_value(size_ctype row, size_ctype col) const
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

				nik_ce auto instr_value(size_ctype col) const
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

			nik_ce void execute()
			{
				size_ctype action = instr_value(MAppl::action);

				action_type::execute(action, this);
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

				template<typename F>
				nik_ce void atomic_binary(F f) // test against size
				{
					auto v1 = _machine.cverse()->cat(0);
					auto v2 = _machine.cverse()->cat(1);

					_machine.carry()->push(f(v1, v2));
				}

				template<typename F>
				nik_ce void atomic_fold(F f, size_type k)
				{
					auto b = _machine.cverse()->cbegin();
					auto e = _machine.cverse()->cend();

					_machine.carry()->clear();
					while (b != e) { k = f(k, *b++); }
					_machine.carry()->push(k);
				}

		public:

			// compare:

				nik_ce void equal        () { atomic_binary (atomic_equal       ); }
				nik_ce void not_equal    () { atomic_binary (atomic_not_equal   ); }
				nik_ce void l_than       () { atomic_binary (atomic_l_than      ); }
				nik_ce void l_than_or_eq () { atomic_binary (atomic_l_than_or_eq); }
				nik_ce void g_than       () { atomic_binary (atomic_g_than      ); }
				nik_ce void g_than_or_eq () { atomic_binary (atomic_g_than_or_eq); }

			// arithmetic:

				nik_ce void add      () { atomic_fold   (atomic_add      , 0); }
				nik_ce void subtract () { atomic_binary (atomic_subtract    ); }
				nik_ce void multiply () { atomic_fold   (atomic_multiply , 1); }
				nik_ce void divide   () { atomic_binary (atomic_divide      ); }
				nik_ce void modulo   () { atomic_binary (atomic_modulo      ); }

			// run:

						// rename!
				nik_ce auto again() const { return eval_method_disjoint{base::model}; }

					// assumes counter is set before calling.
				nik_ce auto run(ctype_ptr in, ctype_cptr end) -> carry_type
				{
					carry_type carry;

					_machine.verse()->push(in, end);

					while (instr_value(MProg::next))
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

