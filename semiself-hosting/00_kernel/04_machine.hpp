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

// space:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// operators:

/***********************************************************************************************************************/

// at:

	template<auto n, auto... filler>
	struct T_grammar<Shape::argument, Pattern::overload, ArgOverload::at, n, filler...>
	{
		template<typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto p0 = left_    <n, U_store_T<Ts>...>;
			nik_ce auto p1 = right_   <n, U_store_T<Ts>...>;
			nik_ce auto U  = _select_ <p0, p1>;

			return T_store_U<U>::result(vs...);
		}

	}; template<auto n>
		nik_ce auto _at_ = U_arg_overload<ArgOverload::at, n>;

	// syntactic sugar:

		template<auto n, auto... Vs>
		nik_ce auto at_ = T_store_U<_at_<n>>::template result<decltype(Vs)...>(Vs...);

		template<auto n, typename... Ts>
		using type_at = T_store_U<at_<n, U_store_T<Ts>...>>;

		template<auto... Vs, nik_vp(p)(T_pack_Vs<Vs...>*), auto n>
		nik_ce auto at_<p, n> = T_store_U<_at_<n>>::template result<decltype(Vs)...>(Vs...);

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// ctuple:

	template<typename, auto, typename...> struct ctuple;

/***********************************************************************************************************************/

// indexed value:

	template<typename T, typename SizeType, SizeType>
	struct indexed_value
	{
		T value;

		nik_ce indexed_value(const T & v) : value{v} { }
	};

/***********************************************************************************************************************/

// interface:

	template<typename SizeType, auto... Is, nik_vp(p)(T_pack_Vs<Is...>*), typename... Ts>
	struct ctuple<SizeType, p, Ts...> : public indexed_value<Ts, SizeType, Is>...
	{
		using size_type		= SizeType;
		using size_ctype	= size_type const;

		nik_ce ctuple(Ts... vs) : indexed_value<Ts, size_type, Is>{vs}... { }

		template<size_type n>
		nik_ce const auto & cvalue() const
		{
			using T		= type_at<n, Ts...>;
			using BasePtr	= indexed_value<T, size_type, n> const*;

			return static_cast<BasePtr>(this)->value;
		}
	};

	// syntactic sugar:

		template<typename SizeType, typename... Ts>
		nik_ces auto env_tuple(Ts... vs)
		{
			using frame_type = ctuple<SizeType, segment_<sizeof...(Ts)>, Ts...      >;
			using env_type   = ctuple<SizeType, segment_<1            >, frame_type >;

			return env_type{frame_type{vs...}};
		}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// machine:

	template<gkey_type, gkey_type, auto...> struct T_machine;

/***********************************************************************************************************************/

// names:

	struct MachineName
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.
			halt    ,							//  1
			type    , literal    , floating , string , lookup , arg  ,	//  2
			pad     , hash       , pound    , apply  , bind   , eval ,	//  8
			go_to   , branch     , invert   , loop   ,			// 14
			cycle   , next       , set      ,				// 18
			repeat  , map        , fold     , find   , sift   ,		// 21

		// symbolic:

			variable , value ,						// 26

			dimension
		};
	};

	using MN = MachineName;

/***********************************************************************************************************************/

// notes:

	struct MachineNote
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.
			none    , first     , front    , back     ,	//  1
			boolean , character , n_number , r_number ,	//  5
			port    , select    ,				//  9
			push    , pull      , drop     ,		// 11
			verse   , side      , replace  ,		// 14
			inc     , dec       ,				// 17

		// symbolic:

			t_number , universe , lookup   ,		// 19

			dimension
		};
	};

	using MT = MachineNote;

/***********************************************************************************************************************/

// index:

	struct MachineIndex { enum : gkey_type { name, note, pos, num, aux0, aux1, aux2, next, dimension }; };

	using MI = MachineIndex;

/***********************************************************************************************************************/

// dispatch:

	template<auto static_contr>
	struct MachineDispatch
	{
		using size_type		= typename T_store_U<static_contr>::size_type;
		using size_ctype	= size_type const;

		nik_ces auto & contr	= member_value_U<static_contr>;

		// accessors:

			nik_ces const auto & instr (size_ctype i) { return contr[i]; }
			nik_ces size_type value    (size_ctype i, size_ctype n) { return contr[i][n]; }
			nik_ces size_type peek     (size_ctype i, size_ctype m, size_ctype n) { return contr[i + m][n]; }

			nik_ces size_type pos  (size_ctype i) { return value(i, MI::pos); }
			nik_ces size_type num  (size_ctype i) { return value(i, MI::num); }
			nik_ces size_type aux0 (size_ctype i) { return value(i, MI::aux0); }
			nik_ces size_type aux1 (size_ctype i) { return value(i, MI::aux1); }
			nik_ces size_type aux2 (size_ctype i) { return value(i, MI::aux2); }

		// navigators:

			nik_ces size_type next_offset (size_ctype i) { return value(i, MI::next); }
			nik_ces size_type next_index  (size_ctype i) { return i + next_offset(i); }

			nik_ces gkey_type next_name (size_ctype i) { return value(next_index(i), MI::name); }
			nik_ces gkey_type next_note (size_ctype i) { return value(next_index(i), MI::note); }
	};

	template<auto static_contr>
	using MD = MachineDispatch<static_contr>;

/***********************************************************************************************************************/

// compound:

	template<auto...> struct T_machine_compound;

	// untyped:

		template<auto c, auto i>
		struct T_machine_compound<c, i>
		{
			template<auto l, auto t, auto r, typename... Ts>
			nik_ces auto result(Ts... vs)
			{
				return NIK_MACHINE_TEMPLATE(c, i)
					::NIK_MACHINE_RESULT_TS(c, i, l, t, r, Ts...)
						(vs...);
			}
		};

	// typed:

		template<auto s, auto c, auto i>
		struct T_machine_compound<s, c, i>
		{
			using S = T_store_U<s>;

			template<auto l, auto t, auto r, typename... Ts>
			nik_ces auto result(Ts... vs) -> S
			{
				return NIK_MACHINE_TEMPLATE(c, i)
					::NIK_MACHINE_RESULT_TS(c, i, l, t, r, Ts...)
						(vs...);
			}
		};

	// syntactic sugar:

		template<auto... Vs>
		nik_ce auto U_machine_compound = U_store_T<T_machine_compound<Vs...>>;

		nik_ce auto H_machine_compound = U_store_B<T_machine_compound>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// read:

/***********************************************************************************************************************/

// only:

	template<auto...>
	struct T_read
	{
		// default:

			template<typename T>
			nik_ces auto only(nik_avp(T*)) { return U_store_T<T const>; }

		// pointer (recursive):

			template<typename T>
			using T_add_pointer_const = T*const;

			template<auto U>
			nik_ces auto add_pointer_const = U_store_T<T_add_pointer_const<T_store_U<U>>>;

			template<typename T>
			nik_ces auto only(nik_avp(T**))
				{ return add_pointer_const<only(U_store_T<T>)>; }

			template<typename T>
			nik_ces auto only(nik_avp(T*const*))
				{ return add_pointer_const<only(U_store_T<T>)>; }

		// reference (recursive):

			template<typename T>
			using T_add_reference_const = T&;

			template<auto U>
			nik_ces auto add_reference_const = U_store_T<T_add_reference_const<T_store_U<U>>>;

			template<typename T>
			nik_ces auto only(nik_avp(T&))
				{ return add_reference_const<only(U_store_T<T>)>; }
	};

	// syntactic sugar:

		template<bool V, typename T>
		using read_type = typename T_read<V, U_store_T<T>>::mtype;

/***********************************************************************************************************************/

// immutable:

	template<auto U, auto... filler>
	struct T_read<false, U, filler...>
	{
		protected:

			nik_ces auto U_mtype	= T_read<filler...>::only(U);

		public:

			using mtype		= T_store_U<U_mtype>;
	};

/***********************************************************************************************************************/

// mutable:

	template<auto U, auto... filler>
	struct T_read<true, U, filler...>
	{
		public:

			using mtype		= T_store_U<U>;
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// metapile:

/***********************************************************************************************************************/

// apply:

	template
	<
		typename SizeType,
		auto static_contr,
		auto static_values,
		auto out_types
	>
	struct T_metapile_apply
	{
		nik_ces SizeType zero = 0;

		template<typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			return T_machine_compound<static_contr, zero>::template
				result<static_values, out_types, zero, Ts...>(vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

