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

// machine:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// tuple:

	template<typename...> struct tuple;

/***********************************************************************************************************************/

// value:

	template<typename T, gindex_type>
	struct MITupleValue
	{
		T v;

		nik_ce MITupleValue() : v{} { }
		nik_ce MITupleValue(const T & _v) : v{_v} { }
	};

/***********************************************************************************************************************/

// multiple inheritance:

	template<typename...> struct MITuple;

	template<template<auto...> typename B, auto... Is, typename... Ts>
	class MITuple<void(*const)(B<Is...>*), Ts...> : public MITupleValue<Ts, Is>...
	{
		friend class tuple<Ts...>;

		public:

			nik_ce MITuple() { }
			nik_ce MITuple(Ts... vs) : MITupleValue<Ts, Is>{vs}... { }

		protected:

			template<auto n>
			nik_ce const auto & value() const
			{
				using T		= type_at<n, Ts...>;
				using BasePtr	= MITupleValue<T, n> const*;

				return static_cast<BasePtr>(this)->v;
			}

			template<typename... Types>
			nik_ce auto push(Types... vs) const
				{ return tuple<Ts..., Types...>{value<Is>()..., vs...}; }

			template<auto... Us, auto... Js>
			nik_ce auto left(nik_avp(T_pack_Vs<Us...>*), nik_avp(T_pack_Vs<Js...>*)) const
				{ return tuple<T_store_U<Us>...>{value<Js>()...}; }
	};

/***********************************************************************************************************************/

// interface:

	template<typename... Ts>
	class tuple
	{
		using mi_type = MITuple<decltype(segment_<sizeof...(Ts)>), Ts...>;

		protected:

			mi_type mi;

		public:

			nik_ces auto length() { return sizeof...(Ts); }

			nik_ce tuple() { }
			nik_ce tuple(Ts... vs) : mi{vs...} { }

			template<auto n>
			nik_ce const auto & cvalue() const { return mi.template value<n>(); }

			template<auto n>
			nik_ce auto & value()
			{
				auto & v = mi.template value<n>();
				using CT = typename remove_reference<decltype(v)>::result;
				using  T = typename remove_const<CT>::result;

				return const_cast<T&>(v);
			}

			template<typename... Types>
			nik_ce auto push(Types... vs) const
				{ return mi.template push<Types...>(vs...); }

			template<auto n>
			nik_ce auto left() const
				{ return mi.left(eval<_par_left_, n, U_store_T<Ts>...>, segment_<n>); }
	};

	// 0-tuple:

		template<>
		class tuple<>
		{
			public:

				nik_ces auto length() { return 0; }

				template<typename... Types>
				nik_ce auto push(Types... vs) const
					{ return tuple<Types...>{vs...}; }

				template<auto n>
				nik_ce auto left() const
					{ return *this; }
		};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// environment:

/***********************************************************************************************************************/

// binding:

	template<typename KeyType, typename ValueType>
	class binding
	{
		public:

			using strlit_type	= string_literal<KeyType>;
			using value_type	= ValueType;

		protected:

			strlit_type strlit;
			value_type value;

		public:

			template<auto N>
			nik_ce binding(const KeyType (&s)[N], const ValueType & v) : strlit{s}, value{v} { }

			nik_ce binding(const strlit_type & s, const value_type & v) : strlit{s}, value{v} { }

			nik_ce const auto & key() const { return strlit; }
			nik_ce const auto & map() const { return value; }
	};

/***********************************************************************************************************************/

// frame:

		// would be implemented as a sequence, but gcc won't constexpr compile.

	template<typename CharType, typename... Bindings>
	class frame
	{
		protected:

			nik_ces auto length	= sizeof...(Bindings);

		public:

			using char_type		= T_restore_T<CharType>;
			using strlit_type	= string_literal<char_type>;
			using base		= sequence<strlit_type, length>;
			using tuple_type	= tuple<typename Bindings::value_type...>;

		protected:

			strlit_type variables[length];
			tuple_type values;

		public:

			nik_ce frame(const CharType &, const Bindings &... bs) :
				variables{bs.key()...}, values{bs.map()...} { }

			nik_ce bool is_empty  () const { return (length == 0); }
			nik_ce bool not_empty () const { return (length != 0); }

			nik_ce const auto & keys() const { return variables; }
			nik_ce const auto & maps() const { return values; }
	};

/***********************************************************************************************************************/

// constant:

	// null:

		nik_ce auto null_frame_callable()
			{ return frame(U_gchar_type); }

		nik_ce auto null_frame = _static_callable_<null_frame_callable>;

	// number:

		nik_ce auto number_frame_callable()
		{
			return frame
			(
				U_gchar_type,

				binding( "zero"  , _zero  ),
				binding( "one"   , _one   ),
				binding( "two"   , _two   ),
				binding( "three" , _three ),
				binding( "four"  , _four  ),
				binding( "five"  , _five  ),
				binding( "six"   , _six   ),
				binding( "seven" , _seven ),
				binding( "eight" , _eight ),
				binding( "nine"  , _nine  ),
				binding( "ten"   , _ten   )
			);
		};

		nik_ce auto number_frame = _static_callable_<number_frame_callable>;

/***********************************************************************************************************************/

// lookup:

	template<typename LiteralType, gindex_type Size> // SizeType ?
	class T_lookup : public sequence<LiteralType, Size>
	{
		public:

			using base			= sequence<LiteralType, Size>;
			using literal_type		= typename base::type;
			using cliteral_type		= typename base::ctype;
			using cliteral_ref		= typename base::ctype_ref;
			using size_type			= typename base::size_type;

			using strlit_type		= typename literal_type::type;
			using cstrlit_type		= typename literal_type::ctype;
			using cstrlit_ref		= typename literal_type::ctype_ref;

			using char_type			= typename strlit_type::type;
			using literal_citerate		= citerator<literal_type, size_type>;
			using strlit_citerate		= citerator<strlit_type, size_type>;
			using str_cselect		= cselector<char_type, size_type>;
			using inhabit_type		= pair_stack<size_type, 1>;

			template<typename... Frames>
			nik_ce T_lookup(const Frames &... fs) : base{} { (base::push(fs.keys()), ...); }

			nik_ce auto match_variable(const str_cselect & s) const
			{
				inhabit_type inhabit{};

				for (auto k = base::citerate(); k.not_end(); ++k)
				{
					auto j = k->citerate().find(s);

					if (j.not_end())
					{
						inhabit.push(k.left_size(), j.left_size());
						break;
					}
				}

				return inhabit;
			}
	};

/***********************************************************************************************************************/

// env lookup:

	template<auto... static_frames>
	struct T_env_lookup
	{
		using char_type		= gchar_type;
		using size_type		= gindex_type;

		using strlit_type	= string_literal<char_type, size_type>;
		using literal_type	= literal<strlit_type, size_type>;
		using look_type		= T_lookup<literal_type, static_cast<size_type>(sizeof...(static_frames))>;

		nik_ces auto value	= look_type{member_value_U<static_frames>...};
		using type		= decltype(value);

	}; nik_ce auto H_env_lookup = U_store_B<T_env_lookup>;

/***********************************************************************************************************************/

// env tuple:

	template<auto... static_frames>
	struct T_env_tuple
	{
		using tuple_type	= tuple<typename member_type_U<static_frames>::tuple_type...>;
		nik_ces auto value	= tuple_type{member_value_U<static_frames>.maps()...};
		using type		= decltype(value);

	}; nik_ce auto H_env_tuple = U_store_B<T_env_tuple>;

/***********************************************************************************************************************/

// interface:

	template<auto... static_frames>
	nik_ce auto env = U_pack_Vs<static_frames...>;

	nik_ce auto null_env = env<>;

/***********************************************************************************************************************/

// source:

	template<typename CharType, auto N, typename... Bindings>
	nik_ce auto source(const CharType (&s)[N], const Bindings &... bs)
	{
		nik_ce auto U_char_type = U_store_T<CharType>;

		return pair{string_literal{s}, frame(U_char_type, bs...)};
	}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// env(ironment) model:

/***********************************************************************************************************************/

// interface:

	template<typename CharType, typename SizeType, SizeType Size>
	class T_env_model : public T_list_model<SizeType, Size>
	{
		public:

			nik_ces SizeType length		= Size;

			using base			= T_list_model<SizeType, length>;
			using size_type			= typename base::size_type;
			using csize_type		= typename base::csize_type;
			using list_type			= typename base::list_type;
			using clist_type		= typename base::clist_type;
			using inhabit_type		= unit_stack<size_type, 1>;
			using Pair			= typename base::Pair;

			using char_type			= CharType;
			using cselect			= cselector<char_type, size_type>;
			using ccselect			= cselect const;
			using ccselect_ref		= ccselect &;
			using strlit_type		= string_literal<CharType, size_type>;
			using cstrlit_type		= strlit_type const;
			using cstrlit_ref		= cstrlit_type &;

		protected:

			cstrlit_type src;

		public:

			inhabit_type inhabit;

			nik_ce T_env_model(cstrlit_ref s) : base{}, src{s} { }

			nik_ce auto get_value(csize_type n) const { return base::get_value(inhabit.cvalue(), n); }
			nik_ce void set_value(csize_type n, csize_type v) { base::set_value(inhabit.cvalue(), n, v); }

		protected:

			// src:

				nik_ce auto start  (ccselect_ref s) const { return s.cbegin() - src.cbegin(); }
				nik_ce auto finish (ccselect_ref s) const { return src.cend() - s.cend(); }

			// env:

				nik_ce auto get_frame   (clist_type env) const { return base::car(env); }
				nik_ce auto get_binding (clist_type env) const { return base::car(get_frame(env)); }
				nik_ce auto get_entry   (clist_type env) const { return base::cdr(get_binding(env)); }

		public:

			// name:

				nik_ce auto get_name(csize_type binding) const
				{
					auto variable = base::car(binding);
					auto start    = base::get_value(variable, Pair::car);
					auto finish   = base::get_value(variable, Pair::cdr);

					return src.cselect(start, finish);
				}

		protected:

			// lookup:

				nik_ce void lookup_frame(ccselect_ref var, clist_type frame)
				{
					for (auto k = frame; inhabit.is_empty() && base::not_null(k); k = base::cdr(k))
						lookup_binding(var, base::car(k));
				}

				nik_ce void lookup_binding(ccselect_ref var, csize_type binding)
				{
					if (apply<_subarray_same_<>>(var, get_name(binding)))
						inhabit.push(base::cdr(binding));
				}

			// binding:

				nik_ce auto set_binding_variable(ccselect_ref var)
				{
					csize_type p = base::allocate(Pair::dimension);

					base::set_value(p, Pair::car, start(var));
					base::set_value(p, Pair::cdr, finish(var));

					return p;
				}

				template<typename In, typename End>
				nik_ce auto set_binding_value(In in, End end)
				{
					csize_type p = base::allocate(end - in);
					size_type  k = 0;

					while (in != end) base::set_value(p, k++, *in++);

					return p;
				}

				nik_ce void set_binding_entry(csize_type variable, csize_type value, clist_type env)
				{
					auto frame   = base::car(env);
					auto binding = base::cons(variable, value);
					auto nframe  = base::cons(binding, frame);

					base::set_value(env, Pair::car, nframe);
				}

		public:

			// list:

				nik_ce auto null_env     () const { return base::null_list(); }
				nik_ce auto null_frame   () const { return base::null_list(); }
				nik_ce auto null_binding () const { return base::null_list(); }

			// env:

				nik_ce bool lookup_variable(ccselect_ref var, clist_type env)
				{
					inhabit.clear();

					for (auto k = env; inhabit.is_empty() && base::not_null(k); k = base::cdr(k))
						lookup_frame(var, base::car(k));

					return inhabit.not_empty();
				}

				template<typename In, typename End>
				nik_ce void define_variable(ccselect_ref var, In in, End end, clist_type env)
				{
					auto variable = set_binding_variable(var);
					auto value    = set_binding_value(in, end);

					set_binding_entry(variable, value, env);
				}

				template<size_type N>
				nik_ce void define_variable(ccselect_ref var, csize_type (&ent)[N], clist_type env)
					{ define_variable(var, ent, ent + N, env); }

				template<typename In, typename End>
				nik_ce void set_variable(ccselect_ref var, In in, End end, clist_type env)
				{
					lookup_variable(var, env);

					if (inhabit.not_empty())

						for (size_type k = 0; in != end; ++in, ++k) set_value(k, *in);

					else { } // error.
				}

				nik_ce auto extend_env(clist_type env) { return base::cons(null_frame(), env); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// controller:

/***********************************************************************************************************************/

// instructions:

	struct Instr { enum : gkey_type { name = 0, note, pos, num, aux0, aux1, aux2, next, dimension }; };

	// type:

		using instr_type = sequence<gindex_type, static_cast<gindex_type>(Instr::dimension)>;

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

		cindex src_at;
		cindex str_at;

		stack_type stack; 

		nik_ce T_machine_contr(cindex src, cindex str) :
			base{}, src_at{src}, str_at{str} { }

		// instr:

			nik_ce auto current(csize_type offset = 0) const { return base::max() + offset; }

			nik_ce void set_instr_value(cindex contr_pos, cindex instr_pos, cindex value)
				{ base::operator[](contr_pos)[instr_pos] = value; }

			nik_ce void push_instr(cindex name, cindex note, cindex pos = 0, cindex num = 0,
				cindex aux0 = 0, cindex aux1 = 0, cindex aux2 = 0, cindex next = 1)
			{
				base::upsize();
				base::end()->fullsize();

				set_instr_value( current() , Instr::name , name );
				set_instr_value( current() , Instr::note , note );
				set_instr_value( current() , Instr::pos  , pos  );
				set_instr_value( current() , Instr::num  , num  );
				set_instr_value( current() , Instr::aux0 , aux0 );
				set_instr_value( current() , Instr::aux1 , aux1 );
				set_instr_value( current() , Instr::aux2 , aux2 );
				set_instr_value( current() , Instr::next , next );
			}

			nik_ce void delay_instr_value(csize_type offset = 0) { stack.push(current(offset)); }

			nik_ce void force_instr_value(cindex instr_pos, csize_type relative, csize_type offset = 0)
			{
				cindex contr_pos = stack.pop();
				size_type value  = current(offset);

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
			nik_ces gindex_type peek   (cindex i, cindex m, cindex n) { return contr[i + m][n]; }

			nik_ces gindex_type pos  (cindex i) { return value(i, MI::pos); }
			nik_ces gindex_type num  (cindex i) { return value(i, MI::num); }
			nik_ces gindex_type aux0 (cindex i) { return value(i, MI::aux0); }
			nik_ces gindex_type aux1 (cindex i) { return value(i, MI::aux1); }
			nik_ces gindex_type aux2 (cindex i) { return value(i, MI::aux2); }

		// navigators:

			nik_ces gindex_type next_offset (cindex i) { return value(i, MI::next); }
			nik_ces gindex_type next_index  (cindex i) { return i + next_offset(i); }

			nik_ces gkey_type next_name (cindex i) { return value(next_index(i), MI::name); }
			nik_ces gkey_type next_note (cindex i) { return value(next_index(i), MI::note); }
	};

	template<auto static_contr, typename MI, auto _index = 0>
	using MD = MachineDispatch<static_contr, MI, _index>;

/***********************************************************************************************************************/

// action:

	template<gkey_type, gkey_type, auto...> struct T_machine_action;

	// syntactic sugar:

		template<auto name, auto note, typename... Ts>
		nik_ce auto machine_action(Ts... vs) // requires template deduction <>:
			{ return T_machine_action<name, note>::template result<>(vs...); }

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
			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result
			(
				Contr *contr, cindex name, cindex note, cindex pos = 0, cindex num = 0,
				cindex aux0 = 0, cindex aux1 = 0, cindex aux2 = 0, cindex next = 1
			)
			{ contr->push_instr(name, note, pos, num, aux0, aux1, aux2, next); }
		};

/***********************************************************************************************************************/

// delay:

	// jump:

		template<auto... filler>
		struct T_machine_action<MAN::delay, MAT::jump, filler...>
		{
			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result
			(
				Contr *contr, cindex name, cindex note, cindex num = 0,
				cindex aux0 = 0, cindex aux1 = 0, cindex aux2 = 0, cindex next = 1
			)
			{
				contr->push_instr(name, note, 0, num, aux0, aux1, aux2, next);
				contr->delay_instr_value();
			}
		};

	// call:

		template<auto... filler>
		struct T_machine_action<MAN::delay, MAT::call, filler...>
		{
			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result
			(
				Contr *contr, cindex name, cindex note, cindex num = 0,
				cindex aux0 = 0, cindex aux1 = 0, cindex aux2 = 0
			)
			{
				cindex pos = contr->current(2);
				contr->push_instr(name, note, pos, num, aux0, aux1, aux2, 0);
				contr->delay_instr_value();
			}
		};

/***********************************************************************************************************************/

// force:

	// jump:

		template<auto... filler>
		struct T_machine_action<MAN::force, MAT::jump, filler...>
		{
			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex offset = 0)
			{
				using Policy = typename Contr::Policy;
				contr->force_instr_value(Instr::pos, Policy::absolute, offset);
			}
		};

	// call:

		template<auto... filler>
		struct T_machine_action<MAN::force, MAT::call, filler...>
		{
			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex offset = 0)
			{
				using Policy = typename Contr::Policy;
				contr->force_instr_value(Instr::next, Policy::relative, offset);
			}
		};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

