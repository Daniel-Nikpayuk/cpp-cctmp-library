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

// method:

/***********************************************************************************************************************/

// immutable:

	template
	<
		auto CarrySize, auto VerseSize, auto StageSize,
		template<typename, typename> typename Atomic,
		template<typename, typename> typename Action,
		typename Base
	>
	class eval_cmethod_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;
			using model_type		= typename facade::model_type;

			nik_using_name_scope_type	( type, model_type)
			nik_using_name_scope_ctype	(ctype, model_type)

			nik_using_size_type_scope	(model_type)

			using sign_type			= typename base::sign_type;
			using sign_ctype_ref		= typename base::sign_ctype_ref;

			using machine_type		= machine<type, size_type, CarrySize, VerseSize, StageSize>;
			using carry_type		= typename machine_type::carry_type;
			using verse_type		= typename machine_type::verse_type;

		protected:

			using contr_type		= typename base::contr_type;

			contr_type contr;

		protected:

			using atomic_action_type	= Atomic<type, size_type>;
			using action_type		= Action<eval_cmethod_disjoint, size_type>;

			using machine_cmethod_type	= resolve_cmethod<machine_type, machine_cmethod>;
			using  machine_method_type	=  resolve_method<machine_type,  machine_method>;

			machine_cmethod_type mach_cmethod;
			machine_method_type   mach_method;

		protected:

			machine_type _machine;

		public:

			nik_ce eval_cmethod_disjoint() : base{}, mach_cmethod{}, mach_method{} { }
			nik_ce eval_cmethod_disjoint(const facade & f) : base{f}
			{
				mach_cmethod = _machine.template cequip<machine_cmethod_type>();
				mach_method  = _machine.template  equip< machine_method_type>();
			}

			// contr:

				nik_ce size_type contr_value(size_ctype row, size_ctype col) const
					{ return contr[row][col]; }

				nik_ce size_type instr_value(size_ctype col) const
					{ return contr_value(mach_method.counter(), col); }

				nik_ce void set_contr(sign_ctype_ref sign) { contr = base::get_contr(sign); }

			// carry:

				nik_ce auto & rtn_cvalue() const { return mach_method.ccarry(); }
				nik_ce auto rtn_cat(size_ctype n) const { return mach_method.ccarry().cat(n); }

		protected:

				template<typename F>
				nik_ce void atomic_binary(F f)
					{ mach_method.atomic_binary(f, instr_value(MAppl::policy)); }

				template<typename F>
				nik_ce void atomic_fold(F f, size_type m)
					{ mach_method.atomic_fold(f, instr_value(MAppl::policy), m); }

			// execute:

				nik_ce void execute() { action_type::execute(instr_value(MAppl::action), this); }

		public:

			// atomic:

				nik_ce void atomic(size_ctype n)
					{ atomic_binary(atomic_action_type::action[n]); }

			// run:

				nik_ce void run_branch() { mach_method.branch(instr_value(MBran::line)); }
				nik_ce void run_invert() { mach_method.invert(instr_value(MBran::line)); }

				nik_ce void reset()
				{
					mach_method.carry().clear();
					mach_method.verse().clear();
					mach_method.stage().clear();
				}

				nik_ce void run_apply()
				{
					size_ctype offset    = instr_value(MAppl::offset);
					size_ctype policy    = instr_value(MAppl::policy);

					auto n_eval_cmethod  = eval_cmethod_disjoint{base::model};
					n_eval_cmethod.contr = contr;
					auto func_index      = mach_method.stage_cfunc(offset);
					n_eval_cmethod       . run(mach_method.stage_cargs(), func_index);

					mach_method.pop_stage();
					mach_method.copy_interval(policy, n_eval_cmethod.rtn_cvalue());
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
					auto start  = contr_value(instr_value(MVal::line), MArg::start);
					auto finish = contr_value(instr_value(MVal::line), MArg::finish);

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

		protected:

			template<typename T>
			nik_ce void run(const T & v, size_ctype n = 0)
			{
				mach_method.initialize(n, v);

				while (instr_value(MProg::next))
				{
					mach_method.inc_counter(instr_value(MProg::next));
					execute();
				}
			}

		public:

			template<auto N>
			nik_ce void apply(sign_ctype_ref sign, ctype (&v)[N])
			{
				set_contr(sign);

				run(verse_type{v});
			}
	};

	// syntactic sugar:

		template<typename Facade, auto CarrySize, auto VerseSize, auto StageSize>
		using eval_cmethod =
			eval_cmethod_disjoint   < CarrySize , VerseSize , StageSize , atomic_action , machine_action ,
			concord_function_method < Facade    >>;

		template<typename Container, auto CarrySize, auto VerseSize, auto StageSize>
		using resolve_eval_cmethod = eval_cmethod
		<
			typename Container::cfacade_type, CarrySize, VerseSize, StageSize
		>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

