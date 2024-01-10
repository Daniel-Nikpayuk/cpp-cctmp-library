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

// interpreter:

	// These machines are intended to be used for moderately complicated variadic manipulations.

	// Anything simpler can be implemented with chord machines, or praxis machines.
	// Anything complex will likely be more performant using constexpr and tuple designs.
	// For example variadic sort is more performant to first cast to a tuple, then using
	// the tuple for comparisons, sort the corresponding indices rather than the tuple itself.
	// Finally, once sorted the constexpr tuple can be unpacked using segments.

	// The possible exception is in implementing chord -> morph -> curry. It can be implemented
	// in simpler ways, but implementing here allows for fine grain control over error messaging
	// as part of a larger more complex system.

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
	};

	// 0-tuple:

		template<> class tuple<> { };

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

// environment:

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
/***********************************************************************************************************************/

// space:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// halt:

/***********************************************************************************************************************/

// apply:

//	template<auto... filler>
//	struct T_interpreter<IN::halt, IT::apply, filler...>
//	{
//		template<NIK_INTERPRETER_CONTROLS(d, c, i, j), auto... Vs, typename... Heaps>
//		nik_ces auto result(Heaps... Hs) { return eval<_to_list_, j, Vs...>; }
//	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// read:

	// Reimplement as compile time register machines.
	// Does only/write need to be expanded to handle additional types such as function pointers?

/***********************************************************************************************************************/

// only:

	struct T_read_only
	{
		// default:

			template<typename T>
			nik_ces auto _result(nik_avp(T*)) { return U_store_T<T const>; }

		// pointer (recursive):

			template<typename T>
			using T_add_pointer_const = T*const;

			template<auto U>
			nik_ces auto add_pointer_const = U_store_T<T_add_pointer_const<T_store_U<U>>>;

			template<typename T>
			nik_ces auto _result(nik_avp(T**)) { return add_pointer_const<_result(U_store_T<T>)>; }

			template<typename T>
			nik_ces auto _result(nik_avp(T*const*)) { return add_pointer_const<_result(U_store_T<T>)>; }

		// reference (recursive):

			template<typename T>
			using T_add_reference_const = T&;

			template<auto U>
			nik_ces auto add_reference_const = U_store_T<T_add_reference_const<T_store_U<U>>>;

			template<typename T>
			nik_ces auto _result(nik_avp(T&)) { return add_reference_const<_result(U_store_T<T>)>; }

		template<auto U>
		nik_ces auto result = _result(U);

	}; nik_ce auto _read_only_ = U_custom_T<T_read_only>;

/***********************************************************************************************************************/

// write:

	struct T_read_write
	{
		// default (recursive):

			template<typename T>
			nik_ces auto _result(nik_avp(T*)) { return U_store_T<T>; }

			template<typename T>
			nik_ces auto _result(nik_avp(T const*)) { return U_store_T<T>; }

		// pointer (recursive):

			template<typename T>
			using T_add_pointer = T*;

			template<auto U>
			nik_ces auto add_pointer = U_store_T<T_add_pointer<T_store_U<U>>>;

			template<typename T>
			nik_ces auto _result(nik_avp(T**)) { return add_pointer<_result(U_store_T<T>)>; }

			template<typename T>
			nik_ces auto _result(nik_avp(T*const*)) { return add_pointer<_result(U_store_T<T>)>; }

		// reference:

			template<typename T>
			using T_add_reference = T&;

			template<auto U>
			nik_ces auto add_reference = U_store_T<T_add_reference<T_store_U<U>>>;

			template<typename T>
			nik_ces auto _result(nik_avp(T&)) { return add_reference<_result(U_store_T<T>)>; }

		template<auto U>
		nik_ces auto result = _result(U);

	}; nik_ce auto _read_write_ = U_custom_T<T_read_write>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

