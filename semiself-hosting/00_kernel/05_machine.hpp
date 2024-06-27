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
	using AN = MN; // temporary until semiself hosting is complete.

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
	using AT = MT; // temporary until semiself hosting is complete.

/***********************************************************************************************************************/

// index:

	struct MachineIndex { enum : gkey_type { name, note, pos, num, aux0, aux1, aux2, next, dimension }; };

	using MI = MachineIndex;
	using AI = MI; // temporary until semiself hosting is complete.

/***********************************************************************************************************************/

// dispatch:

	template<auto static_contr>
	struct MachineDispatch
	{
		using size_type		= typename T_store_U<static_contr>::size_type;
		using csize_type	= size_type const;

		nik_ces auto & contr	= member_value_U<static_contr>;

		// accessors:

			nik_ces const auto & instr (csize_type i) { return contr[i]; }
			nik_ces csize_type value   (csize_type i, csize_type n) { return contr[i][n]; }
			nik_ces csize_type peek    (csize_type i, csize_type m, csize_type n) { return contr[i + m][n]; }

			nik_ces csize_type pos  (csize_type i) { return value(i, MI::pos); }
			nik_ces csize_type num  (csize_type i) { return value(i, MI::num); }
			nik_ces csize_type aux0 (csize_type i) { return value(i, MI::aux0); }
			nik_ces csize_type aux1 (csize_type i) { return value(i, MI::aux1); }
			nik_ces csize_type aux2 (csize_type i) { return value(i, MI::aux2); }

		// navigators:

			nik_ces csize_type next_offset (csize_type i) { return value(i, MI::next); }
			nik_ces csize_type next_index  (csize_type i) { return i + next_offset(i); }

			nik_ces gkey_type next_name (csize_type i) { return value(next_index(i), MI::name); }
			nik_ces gkey_type next_note (csize_type i) { return value(next_index(i), MI::note); }
	};

	template<auto static_contr>
	using MD = MachineDispatch<static_contr>;

	template<auto static_contr>
	using AD = MD<static_contr>; // temporary until semiself hosting is complete.

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

