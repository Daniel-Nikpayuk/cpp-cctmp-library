/************************************************************************************************************************
**
** Copyright 2022-2023 Daniel Nikpayuk, Inuit Nunangat, The Inuit Nation
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

// control:

namespace machine {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// cctmp:

	template<auto U>
	using T_store_U						= cctmp::T_store_U<U>;

	template<auto U>
	nik_ce auto & member_value_U				= cctmp::member_value_U<U>;

	using gcbool_type					= cctmp::gcbool_type;
	using gcchar_type					= cctmp::gcchar_type;
	using gkey_type						= cctmp::gkey_type;
	using gindex_type					= cctmp::gindex_type;
	using gcindex_type					= cctmp::gcindex_type;

	template<auto... Vs>
	nik_ce auto _subarray_same_				= cctmp::_subarray_same_<Vs...>;

	template<auto... Vs>
	nik_ce auto eval					= cctmp::eval<Vs...>;

	template<auto... Vs>
	nik_ce auto if_then_else_				= cctmp::if_then_else_<Vs...>;

	nik_ce auto _read_only_					= cctmp::_read_only_;

	template<typename T, typename S>
	using cselector						= cctmp::cselector<T, S>;

	template<typename T, typename S>
	using string_literal					= cctmp::string_literal<T, S>;

	template<typename T0, typename T1>
	using pair						= cctmp::pair<T0, T1>;

	template<typename T, auto S>
	using unit_stack					= cctmp::unit_stack<T, S>;

	template<typename T, auto S>
	using sequence						= cctmp::sequence<T, S>;

	using Instr						= cctmp::Instr;
	using instr_type					= cctmp::instr_type;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// env(ironment) model:

/***********************************************************************************************************************/

// entry:

	template<typename SizeType, SizeType Size = 3>
	struct T_env_model_entry : public cctmp::T_list_model_entry<SizeType, Size>
	{
		using base		= cctmp::T_list_model_entry<SizeType, Size>;
		using size_type		= typename base::size_type;
		using csize_type	= typename base::csize_type;
		using Entry		= typename base::Entry;

		struct Type     { enum : size_type { constant, variadic, compound, dimension }; };
		struct Constant { enum : size_type { type = Entry::type, pos, dimension }; };
		struct Variadic { enum : size_type { type = Entry::type, pos, dimension }; };
		struct Compound { enum : size_type { type = Entry::type, arity, pos, dimension }; };

		nik_ce T_env_model_entry(csize_type t) : base{t} { }
	};

/***********************************************************************************************************************/

// constant:

	template<typename SizeType>
	struct T_env_model_constant : public T_env_model_entry<SizeType>
	{
		using base		= T_env_model_entry<SizeType>;
		using size_type		= typename base::size_type;
		using csize_type	= typename base::csize_type;
		using Type		= typename base::Type;
		using Constant		= typename base::Constant;

		nik_ce T_env_model_constant(csize_type p) : base{Type::constant}
			{ base::array[Constant::pos] = p; }

		nik_ce auto size() const { return Constant::dimension; }
		nik_ce auto cend() const { return base::array + size(); }
	};

/***********************************************************************************************************************/

// variadic:

	template<typename SizeType>
	struct T_env_model_variadic : public T_env_model_entry<SizeType>
	{
		using base		= T_env_model_entry<SizeType>;
		using size_type		= typename base::size_type;
		using csize_type	= typename base::csize_type;
		using Type		= typename base::Type;
		using Variadic		= typename base::Variadic;

		nik_ce T_env_model_variadic(csize_type p) : base{Type::variadic}
			{ base::array[Variadic::pos] = p; }

		nik_ce auto size() const { return Variadic::dimension; }
		nik_ce auto cend() const { return base::array + size(); }
	};

/***********************************************************************************************************************/

// compound:

	template<typename SizeType>
	struct T_env_model_compound : public T_env_model_entry<SizeType>
	{
		using base		= T_env_model_entry<SizeType>;
		using size_type		= typename base::size_type;
		using csize_type	= typename base::csize_type;
		using Type		= typename base::Type;
		using Compound		= typename base::Compound;

		nik_ce T_env_model_compound() : base{Type::compound} { }

		nik_ce auto size() const { return Compound::dimension; }
		nik_ce auto cend() const { return base::array + size(); }
	};

/***********************************************************************************************************************/

// interface:

	template<typename CharType, typename SizeType, SizeType Size>
	class T_env_model : public cctmp::T_list_model<SizeType, Size>
	{
		public:

			using base				= cctmp::T_list_model<SizeType, Size>;
			using size_type				= typename base::size_type;
			using size_type_ref			= size_type &;
			using csize_type			= typename base::csize_type;
			using list_type				= typename base::list_type;
			using clist_type			= typename base::clist_type;
			using record_type			= pair<bool, size_type>;
			using Pair				= typename base::Pair;

			using char_type				= CharType;
			using cselect				= cselector<char_type, size_type>;
			using ccselect				= cselect const;
			using ccselect_ref			= ccselect &;
			using strlit_type			= string_literal<CharType, size_type>;
			using cstrlit_type			= strlit_type const;
			using cstrlit_ref			= cstrlit_type &;

			using entry_type			= T_env_model_entry<SizeType>;
			using centry_type			= entry_type const;
			using centry_ptr			= centry_type *;
			using centry_ref			= centry_type &;
			using EntryType				= typename entry_type::Type;

			using constant_type			= T_env_model_constant<SizeType>;
			using constant				= typename constant_type::Constant;

			using variadic_type			= T_env_model_variadic<SizeType>;
			using Variadic				= typename variadic_type::Variadic;

			using compound_type			= T_env_model_compound<SizeType>;
			using Compound				= typename compound_type::Compound;

		protected:

			struct Variable { enum : size_type { start, finish, dimension }; };

			cstrlit_type src;

		public:

			nik_ce T_env_model(cstrlit_ref s) : base{}, src{s} { }

		protected:

			// src:

				nik_ce auto start  (ccselect_ref s) const { return s.cbegin() - src.cbegin(); }
				nik_ce auto finish (ccselect_ref s) const { return src.cend() - s.cend(); }

			// lookup:

				nik_ce bool lookup_frame(ccselect_ref var, clist_type frame, size_type_ref entry) const
				{
					bool no_match = true;

					for (auto k = frame; no_match && base::not_null(k); k = base::cdr(k))
						no_match = lookup_binding(var, base::car(k), entry);

					return no_match;
				}

				nik_ce bool lookup_binding(ccselect_ref var, csize_type binding, size_type_ref entry) const
				{
					auto variable = base::car(binding);
					auto start    = base::get_value(variable, Variable::start);
					auto finish   = base::get_value(variable, Variable::finish);

					auto src_cselect = src.cselect(start, finish);

					bool match = cctmp::apply<_subarray_same_<>>(var, src_cselect);

					if (match) entry = base::cdr(binding);

					return !match;
				}

			// binding:

				nik_ce void set_binding_variable(csize_type variable, ccselect_ref var)
				{
					base::set_value(variable, Variable::start , start(var));
					base::set_value(variable, Variable::finish , finish(var));
				}

				template<typename Entry>
				nik_ce void set_binding_value(csize_type value, const Entry & val)
				{
					size_type j = 0;

					for (auto k = val.cbegin(); k != val.cend(); ++j, ++k)
						base::set_value(value, j, *k);
				}

		public:

			// list:

				nik_ce auto null_env     () const { return base::null_list(); }
				nik_ce auto null_frame   () const { return base::null_list(); }
				nik_ce auto null_binding () const { return base::null_list(); }

			// env:

				nik_ce auto lookup_variable(ccselect_ref var, clist_type env) const
				{
					bool no_match = true;
					size_type entry = 0;

					for (auto k = env; no_match && base::not_null(k); k = base::cdr(k))
						no_match = lookup_frame(var, base::car(k), entry);

					return record_type{!no_match, entry};
				}

				template<typename Entry>
				nik_ce void define_variable(ccselect_ref var, const Entry & val, clist_type env)
				{
					auto frame    = base::car(env);
					auto variable = base::allocate(Variable::dimension);
					auto value    = base::allocate(Entry::length); // disjoint union.
					auto binding  = base::cons(variable, value);
					auto nframe   = base::cons(binding, frame);

					set_binding_variable(variable, var);
					set_binding_value(value, val);
					base::set_value(env, Pair::car, nframe);
				}

				template<typename Entry>
				nik_ce void set_variable(ccselect_ref var, const Entry & val, clist_type env)
				{
					auto rec = lookup_variable(var, env);

					set_binding_value(rec.v1, val);
				}

				nik_ce auto extend_environment(clist_type env)
					{ return base::cons(base::null_list(), env); }

			// binding:

				nik_ce auto variadic_pos(csize_type value) const
					{ return base::get_value(value, Variadic::pos); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// space:

/***********************************************************************************************************************/

// type:

	template<auto U>
	using read_only = T_store_U<eval<_read_only_, U>>;

	template<bool p, auto U0, auto U1>
	using retype = T_store_U<if_then_else_<p, U0, U1>>;

/***********************************************************************************************************************/

// interface:

	template<gindex_type StackSize, gindex_type Size>
	struct T_machine_contr : public sequence<instr_type, Size>
	{
		using base		= sequence<instr_type, Size>;
		using size_type		= typename base::size_type;
		using csize_type	= typename base::csize_type;
		using stack_type	= unit_stack<size_type, StackSize>;
		using cindex		= csize_type;

		struct Policy { enum : size_type { absolute = 0, relative, dimension }; };

		cindex rec_at; // required any more ?
		cindex src_at;
		cindex str_at;
		cindex env_at;

		stack_type stack; 

		nik_ce T_machine_contr(cindex rec, cindex src, cindex str, cindex env) :
			base{}, rec_at{rec}, src_at{src}, str_at{str}, env_at{env} { }

		// instr:

			nik_ce auto current () const { return base::max(); }
			nik_ce auto next    () const { return base::size(); }

			nik_ce void set_instr_value(cindex contr_pos, cindex instr_pos, cindex value)
				{ base::operator[](contr_pos)[instr_pos] = value; }

			nik_ce void push_instr(cindex name, cindex note, cindex pos = 0, cindex num = 0, cindex next = 1)
			{
				base::upsize();

				set_instr_value( current() , Instr::name , name );
				set_instr_value( current() , Instr::note , note );
				set_instr_value( current() , Instr::pos  , pos  );
				set_instr_value( current() , Instr::num  , num  );
				set_instr_value( current() , Instr::next , next );
			}

			nik_ce void delay_instr_value() { stack.push(current()); }

			nik_ce void force_instr_value(cindex instr_pos, csize_type relative)
			{
				cindex contr_pos = stack.pop();
				size_type value  = current();

				if (relative) value -= (contr_pos - 1);

				set_instr_value(contr_pos, instr_pos, value);
			}
	};

/***********************************************************************************************************************/

// dispatch:

	template<auto static_contr, typename MI, auto _index = 0>
	struct MachineDispatch
	{
		nik_ces auto & contr	= member_value_U<static_contr>;
		using cindex		= gcindex_type;

		// defaults:

			nik_ces gindex_type initial_index = _index;

		// accessors:

			nik_ces const auto & instr (cindex i) { return contr[i]; }
			nik_ces gindex_type value  (cindex i, cindex n) { return contr[i][n]; }

			nik_ces gindex_type pos (cindex i) { return value(i, MI::pos); }
			nik_ces gindex_type num (cindex i) { return value(i, MI::num); }

		// navigators:

			nik_ces gindex_type next_offset (cindex i) { return value(i, MI::next); }
			nik_ces gindex_type next_index  (cindex i) { return i + next_offset(i); }

			nik_ces gkey_type next_name (cindex i) { return value(next_index(i), MI::name); }
			nik_ces gkey_type next_note (cindex i) { return value(next_index(i), MI::note); }
	};

	template<auto static_contr, typename MI, auto _index = 0>
	using MD = MachineDispatch<static_contr, MI, _index>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// action:

	template<gkey_type, gkey_type, auto...> struct T_machine_action;

	// syntactic sugar:

		template<auto name, auto note, typename... Ts>
		nik_ce auto machine_action(Ts... vs) // requires template deduction <>:
			{ return T_machine_action<name, note>::template result<>(vs...); }

		template<auto name, auto note>
		nik_ce auto machine_offset = T_machine_action<name, note>::offset;

/***********************************************************************************************************************/

// names:

	struct MachineActionName
	{
		enum : gkey_type // convenience for default params.
			{ identity = 0, id = identity, push, delay, force, dimension };

	}; using MAN = MachineActionName;

/***********************************************************************************************************************/

// notes:

	struct MachineActionNote
	{
		enum : gkey_type // convenience for default params.
			{ identity = 0, id = identity, instr, jump, call, dimension };

	}; using MAT = MachineActionNote;

/***********************************************************************************************************************/

// push:

	// instr:

		template<auto... filler>
		struct T_machine_action<MAN::push, MAT::instr, filler...>
		{
			nik_ces gindex_type offset = 1;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr,
				cindex name, cindex note, cindex pos = 0, cindex num = 0, cindex next = 1)
					{ contr->push_instr(name, note, pos, num, next); }
		};

/***********************************************************************************************************************/

// delay:

	// jump:

		template<auto... filler>
		struct T_machine_action<MAN::delay, MAT::jump, filler...>
		{
			nik_ces gindex_type offset = 1;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex name, cindex note, cindex num = 0, cindex next = 1)
			{
				contr->push_instr(name, note, 0, num, next);
				contr->delay_instr_value();
			}
		};

	// call:

		template<auto... filler>
		struct T_machine_action<MAN::delay, MAT::call, filler...>
		{
			nik_ces gindex_type offset = 1;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex name, cindex note, cindex num = 0, cindex next = 1)
			{
				cindex pos = contr->next() + 1;
				contr->push_instr(name, note, pos, num, next);
				contr->delay_instr_value();
			}
		};

/***********************************************************************************************************************/

// force:

	// jump:

		template<auto... filler>
		struct T_machine_action<MAN::force, MAT::jump, filler...>
		{
			nik_ces gindex_type offset = 0;

			template<typename Contr>
			nik_ces void result(Contr *contr)
			{
				using Policy = typename Contr::Policy;
				contr->force_instr_value(Instr::pos, Policy::absolute);
			}
		};

	// call:

		template<auto... filler>
		struct T_machine_action<MAN::force, MAT::call, filler...>
		{
			nik_ces gindex_type offset = 0;

			template<typename Contr>
			nik_ces void result(Contr *contr)
			{
				using Policy = typename Contr::Policy;
				contr->force_instr_value(Instr::next, Policy::relative);
			}
		};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace machine

