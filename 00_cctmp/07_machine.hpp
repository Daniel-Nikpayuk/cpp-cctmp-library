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

	// operator:

		nik_ce auto operator_frame_callable()
		{
			return frame
			(
			 	U_gchar_type,

				binding( "id"                    , _id_                    ),
				binding( "nop"                   , _nop_                   ),
				binding( "upshift"               , _upshift_               ),
				binding( "downshift"             , _downshift_             ),

				binding( "dereference"           , _dereference_           ),
				binding( "appoint"               , _appoint_               ),
				binding( "to_bool"               , _to_bool_               ),

				binding( "not"                   , _not_                   ),
				binding( "and"                   , _and_                   ),
				binding( "or"                    , _or_                    ),
				binding( "implies"               , _implies_               ),
				binding( "equivalent"            , _equivalent_            ),

				binding( "equal"                 , _equal_                 ),
				binding( "is_zero"               , _is_zero_               ),
				binding( "not_equal"             , _not_equal_             ),
				binding( "not_zero"              , _not_zero_              ),
				binding( "less_than"             , _less_than_             ),
				binding( "less_than_or_equal"    , _less_than_or_equal_    ),
				binding( "greater_than"          , _greater_than_          ),
				binding( "greater_than_or_equal" , _greater_than_or_equal_ ),

				binding( "add"                   , _add_                   ),
				binding( "subtract"              , _subtract_              ),
				binding( "multiply"              , _multiply_              ),
				binding( "divide"                , _divide_                ),
				binding( "modulo"                , _modulo_                ),

				binding( "increment"             , _increment_<1>          ),
				binding( "decrement"             , _increment_<-1>         ),

				binding( "is_array"              , _is_array_              ),
				binding( "array_type"            , _array_type_            ),
				binding( "array_size"            , _array_size_            ),
				binding( "array_begin"           , _array_begin_           ),
				binding( "array_last"            , _array_last_            ),
				binding( "array_end"             , _array_end_             ),
				binding( "log_floor"             , _log_floor_             ),

				binding( "is_sequence"           , _is_sequence_           ),
				binding( "sequence_type"         , _sequence_type_         ),
				binding( "sequence_length"       , _sequence_length_       )
			);
		};

		nik_ce auto operator_frame = _static_callable_<operator_frame_callable>;

/***********************************************************************************************************************/

// lookup:

	template<typename LiteralType, gindex_type Size> // SizeType ?
	struct T_lookup : public sequence<LiteralType, Size>
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
			using path_type			= pair<size_type, size_type>;
			using record_type		= pair<bool, path_type>;

			template<typename... Frames>
			nik_ce T_lookup(const Frames &... fs) : base{} { (base::push(fs.keys()), ...); }

		public:

			nik_ce auto match_variable(const str_cselect & s) const
			{
				bool match{false};
				path_type path{0, 0};

				for (auto k = base::citerate(); k.not_end(); ++k)
				{
					auto j = k->citerate().find(s);
					match = j.not_end();

					if (match)
					{
						path.v0 = k.left_size();
						path.v1 = j.left_size();
						break;
					}
				}

				return record_type{match, path};
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

// controller:

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

			nik_ce void push_instr(cindex name, cindex note, cindex pos = 0, cindex num = 0, cindex next = 1)
			{
				base::upsize();
				base::end()->fullsize();

				set_instr_value( current() , Instr::name , name );
				set_instr_value( current() , Instr::note , note );
				set_instr_value( current() , Instr::pos  , pos  );
				set_instr_value( current() , Instr::num  , num  );
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
			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex name, cindex note, cindex num = 0)
			{
				cindex pos = contr->current(2);
				contr->push_instr(name, note, pos, num, 0);
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

// env(ironment) model:

/***********************************************************************************************************************/

// msg:

	nik_ce void _not_found_() { }

/***********************************************************************************************************************/

// entry:

	template<typename SizeType, SizeType Size = 7>
	struct T_env_model_entry : public T_list_model_entry<SizeType, Size>
	{
		using base		= T_list_model_entry<SizeType, Size>;
		using size_type		= typename base::size_type;
		using csize_type	= typename base::csize_type;
		using Entry		= typename base::Entry;

		struct Type     { enum : size_type { constant, variadic, compound, dimension }; };
		struct Constant { enum : size_type { type = Entry::type, pos, dimension }; };
		struct Variadic { enum : size_type { type = Entry::type, pos, dimension }; };
		struct Compound
		{
			enum : size_type { type = Entry::type, kind, port, left, ins, env, aux, dimension };
		};

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

		nik_ce T_env_model_compound(csize_type p0, csize_type p1, csize_type p2) : base{Type::compound}
		{
			base::array[Compound::left] = p0;
			base::array[Compound::ins ] = p1;
			base::array[Compound::env ] = p2;
		}

		nik_ce auto size() const { return Compound::dimension; }
		nik_ce auto cend() const { return base::array + size(); }
	};

/***********************************************************************************************************************/

// interface:

	template<typename CharType, typename SizeType, SizeType Size>
	class T_env_model : public T_list_model<SizeType, Size>
	{
		public:

			using base				= T_list_model<SizeType, Size>;
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
			using cconstant_type			= constant_type const;
			using cconstant_ref			= cconstant_type &;
			using Constant				= typename constant_type::Constant;

			using variadic_type			= T_env_model_variadic<SizeType>;
			using cvariadic_type			= variadic_type const;
			using cvariadic_ref			= cvariadic_type &;
			using Variadic				= typename variadic_type::Variadic;

			using compound_type			= T_env_model_compound<SizeType>;
			using ccompound_type			= compound_type const;
			using ccompound_ref			= ccompound_type &;
			using Compound				= typename compound_type::Compound;

		protected:

			cstrlit_type src;

		public:

			nik_ce T_env_model(cstrlit_ref s) : base{}, src{s} { }

			nik_ce auto get_value(csize_type p, csize_type n) const { return base::get_value(p, n); }
			nik_ce void set_value(csize_type p, csize_type n, csize_type v) { base::set_value(p, n, v); }

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
					auto start    = base::get_value(variable, Pair::car);
					auto finish   = base::get_value(variable, Pair::cdr);

					auto src_cselect = src.cselect(start, finish);

					bool match = apply<_subarray_same_<>>(var, src_cselect);

					if (match) entry = base::cdr(binding);

					return !match;
				}

			// binding:

				nik_ce auto set_binding_variable(ccselect_ref var)
				{
					csize_type variable = base::allocate(Pair::dimension);
					
					base::set_value(variable, Pair::car , start(var));
					base::set_value(variable, Pair::cdr , finish(var));

					return variable;
				}

				nik_ce auto allocate_binding_value()
					{ return base::allocate(entry_type::length); }

				nik_ce auto set_variadic_value(cvariadic_ref val)
				{
					csize_type value = allocate_binding_value();

					base::set_value(value, Variadic::type , val[Variadic::type]);
					base::set_value(value, Variadic::pos  , val[Variadic::pos]);

					return value;
				}

				nik_ce auto set_compound_value(ccompound_ref val)
				{
					csize_type value = allocate_binding_value();

					base::set_value(value, Compound::type , val[Compound::type]);
					base::set_value(value, Compound::left , val[Compound::left]);
					base::set_value(value, Compound::ins  , val[Compound::ins ]);
					base::set_value(value, Compound::env  , val[Compound::env ]);

					return value;
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

				nik_ce auto lookup_variable(ccselect_ref var, clist_type env) const
				{
					bool no_match = true;
					size_type entry = 0;

					for (auto k = env; no_match && base::not_null(k); k = base::cdr(k))
						no_match = lookup_frame(var, base::car(k), entry);

					return record_type{!no_match, entry};
				}

				nik_ce void define_variable(ccselect_ref var, cvariadic_ref val, clist_type env)
				{
					auto variable = set_binding_variable(var);
					auto value    = set_variadic_value(val);

					set_binding_entry(variable, value, env);
				}

				nik_ce auto define_compound(ccselect_ref var, ccompound_ref val, clist_type env)
				{
					auto variable = set_binding_variable(var);
					auto value    = set_compound_value(val);

					set_binding_entry(variable, value, env);

					return value;
				}

				template<typename Entry>
				nik_ce void set_variable(ccselect_ref var, const Entry & val, clist_type env)
				{
					auto rec = lookup_variable(var, env);

					set_binding_value(rec.v1, val);
				}

				nik_ce auto extend_environment(clist_type env)
					{ return base::cons(null_frame(), env); }

			// binding:

				nik_ce bool is_compound(csize_type entry) const
					{ return (base::get_value(entry, Compound::type) == EntryType::compound); }

				nik_ce auto compound_kind(csize_type entry) const
					{ return base::get_value(entry, Compound::kind); }

				nik_ce auto compound_port(csize_type entry) const
					{ return base::get_value(entry, Compound::port); }

				nik_ce auto compound_left(csize_type entry) const
					{ return base::get_value(entry, Compound::left); }

				nik_ce auto compound_origin(csize_type entry) const
					{ return base::get_value(entry, Compound::ins); }

				nik_ce auto compound_aux(csize_type entry) const
					{ return base::get_value(entry, Compound::aux); }

				nik_ce auto variadic_pos(csize_type entry) const
					{ return base::get_value(entry, Variadic::pos); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

