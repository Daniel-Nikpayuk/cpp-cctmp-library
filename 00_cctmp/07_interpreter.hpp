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

// binding:

/***********************************************************************************************************************/

	template<typename KeyType, typename ValueType>
	class binding
	{
		template<typename, typename...> friend class frame;

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
/***********************************************************************************************************************/

// frame:

/***********************************************************************************************************************/

	template<typename CharType, typename... Bindings>
	class frame
	{
		public:

			using char_type		= T_restore_T<CharType>;
			using strlit_type	= string_literal<char_type>;
			using sequence_type	= ce_sequence<strlit_type, sizeof...(Bindings)>;
			using tuple_type	= tuple<typename Bindings::value_type...>;

		protected:

			sequence_type strlit;
			tuple_type value;

		public:

			nik_ce frame(const CharType &, const Bindings &... bs) :
				strlit{{bs.strlit...}}, value{bs.value...} { }

			template<typename T>
			nik_ce auto contains(const T & v) const { return strlit.citerate().find(v); }

			template<auto key>
			nik_ce auto map() const { return value.template cvalue<key>(); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// lookup:

/***********************************************************************************************************************/

	template<auto> struct T_lookup;

	template<template<auto...> typename B, auto... static_frames, nik_vp(env)(B<static_frames...>*)>
	struct T_lookup<env>
	{
		using pair_type  = pair<gindex_type, gindex_type>;
		using citer_type = citerator<strlit_type>;

		nik_ces void update_frame(pair_type & pos, bool & match, citer_type k)
		{
			if (!match)
			{
				match   = k.not_end();
				pos.v0 += not match;
				pos.v1  = k.left_size();
			}
		}

		template<typename EntryType>
		nik_ces auto find_frame(const EntryType & entry)
		{
			pair_type pos;
			bool match{false};

			(update_frame(pos, match, member_value_U<static_frames>.contains(entry)), ...);

			return pos;
		}

		template<auto pos, auto key>
		nik_ces auto map()
		{
			nik_ce auto static_frame = eval<_par_at_, pos, static_frames...>;
			nik_ce auto & frame      = member_value_U<static_frame>;

			return frame.template map<key>();
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// machine:

/***********************************************************************************************************************/

// default:

	nik_ce auto default_machine_frame_callable()
	{
		return frame
		(
		 	U_char,

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

	nik_ce auto default_machine_frame = _static_callable_<default_machine_frame_callable>;

/***********************************************************************************************************************/

// constant:

	nik_ce auto constant_machine_frame_callable()
	{
		return frame
		(
			U_char,

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

	nik_ce auto constant_machine_frame = _static_callable_<constant_machine_frame_callable>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// environment:

	template<auto... frames>
	nik_ce auto env = U_pack_Vs<frames...>;

	nik_ce auto null_env = env<>;

/***********************************************************************************************************************/

// source:

	template<typename CharType, auto N, typename... Bindings>
	nik_ce auto source(const CharType (&s)[N], const Bindings &... bs)
	{
		nik_ce auto U_char_type   = U_store_T<CharType>;
		nik_ce auto empty_binding = binding("", _na_);

		return pair{string_literal{s}, frame{U_char_type, bs..., empty_binding}};
	}

/***********************************************************************************************************************/

// subsource:

	struct T_default_subsource
	{
		nik_ces auto value			= string_literal{"id dereference appoint equal"};
		using type				= decltype(value);

		nik_ces gindex_type id_start		=  0;
		nik_ces gindex_type id_finish		= 26; // 28 - 2

		nik_ces gindex_type deref_start		=  3;
		nik_ces gindex_type deref_finish	= 14; // 28 - 14

		nik_ces gindex_type appoint_start	= 15;
		nik_ces gindex_type appoint_finish	=  6; // 28 - 22

		nik_ces gindex_type equal_start		= 23;
		nik_ces gindex_type equal_finish	=  0; // 28 - 28

	}; nik_ce auto _default_subsource_ = U_store_T<T_default_subsource>;

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

