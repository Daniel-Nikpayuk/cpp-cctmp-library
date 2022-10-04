/************************************************************************************************************************
**
** Copyright 2021-2022 Daniel Nikpayuk, Inuit Nunangat, The Inuit Nation
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

// numerical:

namespace cctmp_numerical {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// constant:

	nik_ce auto U_void = U_store_T<void>;

/***********************************************************************************************************************/

// integer (variable template):

	template<key_type, auto... Vs>
	nik_ce auto integer = U_pack_Vs<Vs...>;

	// (find) helper:

		template<auto width, typename ArrType>
		nik_ce auto limits_width_match(ArrType limit) { return (limit[_zero] >= width); }

		template<auto width, typename ArrType>
		nik_ce auto U_match_width = _match_<_apply_<limits_width_match<width, ArrType>>>;

/***********************************************************************************************************************/

	struct Limit
	{
		// indices:

			nik_ces key_type _char				=  0;
			nik_ces key_type _short				=  1;
			nik_ces key_type _int				=  2;
			nik_ces key_type _long				=  3;
			nik_ces key_type _long_long			=  4;

			nik_ces key_type _length			=  5;

		// limits:

			nik_ces key_type _width				=  0;
			nik_ces key_type _min				=  1;
			nik_ces key_type _max				=  2;

		// unsigned:

			nik_ces key_type uint_index			=  0;
			nik_ces key_type uint_type			=  1;

			nik_ces key_type is_uint_type			=  2;
			nik_ces key_type not_uint_type			=  3;

			nik_ces key_type uint_width			=  4;
			nik_ces key_type uint_min			=  5;
			nik_ces key_type uint_max			=  6;

			nik_ces key_type uint_find			=  7;
			nik_ces key_type uint_increment			=  8;
			nik_ces key_type uint_decrement			=  9;

		// signed:

			nik_ces key_type sint_index			= 10;
			nik_ces key_type sint_type			= 11;

			nik_ces key_type is_sint_type			= 12;
			nik_ces key_type not_sint_type			= 13;

			nik_ces key_type sint_width			= 14;
			nik_ces key_type sint_min			= 15;
			nik_ces key_type sint_max			= 16;

			nik_ces key_type sint_find			= 17;
			nik_ces key_type sint_increment			= 18;
			nik_ces key_type sint_decrement			= 19;

		// generic:

			nik_ces key_type is_int_type			= 20;
			nik_ces key_type not_int_type			= 21;

			nik_ces key_type int_width			= 22;
			nik_ces key_type int_min			= 23;
			nik_ces key_type int_max			= 24;
			nik_ces key_type int_find			= 25;

			nik_ces key_type int_increment			= 26;
			nik_ces key_type int_decrement			= 27;
	};

/***********************************************************************************************************************/

// unsigned:

	// (array) type:

		using uint_type				= unsigned long long;
		using cuint_type			= uint_type const;

		using ulim_type				= cuint_type *;
		using culim_type			= ulim_type const;

	// constant:

		nik_ce auto U_uint_char			= U_store_T < unsigned char      >;
		nik_ce auto U_uint_short		= U_store_T < unsigned short     >;
		nik_ce auto U_uint_int			= U_store_T < unsigned int       >;
		nik_ce auto U_uint_long			= U_store_T < unsigned long      >;
		nik_ce auto U_uint_long_long		= U_store_T < unsigned long long >;

	// width:

		template<typename UIntType>
		nik_ce auto uint_width(UIntType max) // 8 * sizeof(IntType)
		{
			uint_type width{8};

			while (((max >>= 4) >>= 4)) width+=8; // 4x4 (instead of 8 directly) prevents a warning.

			return width;
		}

	// limit:

		template<typename UIntType>
		nik_ce auto uint_limit(void(*)(UIntType*))
		{
			nik_ce UIntType min   = _zero;
			nik_ce UIntType max   = (UIntType) -1;
			nik_ce UIntType width = uint_width(max);

			return array<cuint_type, width, min, max>;
		}

		nik_ce auto uint_limits = array
		<
			culim_type,

			uint_limit ( U_uint_char        ),
			uint_limit ( U_uint_short       ),
			uint_limit ( U_uint_int         ),
			uint_limit ( U_uint_long        ),
			uint_limit ( U_uint_long_long   )
		>;

	// index:

		template<nik_vp(V)(unsigned char     *)> nik_ce auto integer<Limit::uint_index, V> = Limit::_char;
		template<nik_vp(V)(unsigned short    *)> nik_ce auto integer<Limit::uint_index, V> = Limit::_short;
		template<nik_vp(V)(unsigned int      *)> nik_ce auto integer<Limit::uint_index, V> = Limit::_int;
		template<nik_vp(V)(unsigned long     *)> nik_ce auto integer<Limit::uint_index, V> = Limit::_long;
		template<nik_vp(V)(unsigned long long*)> nik_ce auto integer<Limit::uint_index, V> = Limit::_long_long;

		template<auto V>                         nik_ce auto integer<Limit::uint_index, V> = Limit::_length;

	// type:

		template<auto... Vs> nik_ce auto integer<Limit::uint_type, Limit::_char      , Vs...> = U_uint_char;
		template<auto... Vs> nik_ce auto integer<Limit::uint_type, Limit::_short     , Vs...> = U_uint_short;
		template<auto... Vs> nik_ce auto integer<Limit::uint_type, Limit::_int       , Vs...> = U_uint_int;
		template<auto... Vs> nik_ce auto integer<Limit::uint_type, Limit::_long      , Vs...> = U_uint_long;
		template<auto... Vs> nik_ce auto integer<Limit::uint_type, Limit::_long_long , Vs...> = U_uint_long_long;

	// is type:

		template<auto V>
		nik_ce auto integer<Limit::is_uint_type, V> = (integer<Limit::uint_index, V> < Limit::_length);

		nik_ce auto _is_uint_type_ = Limit::is_uint_type;

	// not type:

		template<auto V>
		nik_ce auto integer<Limit::not_uint_type, V> = (integer<Limit::uint_index, V> == Limit::_length);

		nik_ce auto _not_uint_type_ = Limit::not_uint_type;

	// width:

		template<auto V>
		nik_ce auto integer<Limit::uint_width, V> = uint_limits[integer<Limit::uint_index, V>][Limit::_width];

		nik_ce auto _uint_width_ = Limit::uint_width;

	// min:

		template<auto V>
		nik_ce auto integer<Limit::uint_min, V> = uint_limits[integer<Limit::uint_index, V>][Limit::_min];

		nik_ce auto _uint_min_ = Limit::uint_min;

	// max:

		template<auto V>
		nik_ce auto integer<Limit::uint_max, V> = uint_limits[integer<Limit::uint_index, V>][Limit::_max];

		nik_ce auto _uint_max_ = Limit::uint_max;

	// find (width to type-index):

		template<auto width>
		nik_ce auto integer<Limit::uint_find, width> = integer
		<
			Limit::uint_type,
			overload
			<
				U_match_width<width, culim_type>,
				uint_limits,
				Limit::_length
			>
		>;

		nik_ce auto _uint_find_ = Limit::uint_find;

	// increment (casting):

		// currently unsafe---no bounds check:

		template<auto V>
		nik_ce auto integer<Limit::uint_increment, V> = integer
		<
			Limit::uint_find,
			(integer<Limit::uint_width, V> << 1)
		>;

		nik_ce auto _uint_increment_ = Limit::uint_increment;

	// decrement (casting):

		// currently unsafe---no bounds check:

		template<auto V>
		nik_ce auto integer<Limit::uint_decrement, V> = integer
		<
			Limit::uint_find,
			(integer<Limit::uint_width, V> >> 1)
		>;

		nik_ce auto _uint_decrement_ = Limit::uint_decrement;

/***********************************************************************************************************************/

// signed:

	// (array) type:

		using sint_type				= signed long long;
		using csint_type			= sint_type const;

		using slim_type				= csint_type *;
		using cslim_type			= slim_type const;

	// constant:

		nik_ce auto U_sint_char			= U_store_T < signed char      >;
		nik_ce auto U_sint_short		= U_store_T < signed short     >;
		nik_ce auto U_sint_int			= U_store_T < signed int       >;
		nik_ce auto U_sint_long			= U_store_T < signed long      >;
		nik_ce auto U_sint_long_long		= U_store_T < signed long long >;

	// index:

		template<nik_vp(V)(signed char     *)> nik_ce auto integer<Limit::sint_index, V> = Limit::_char;
		template<nik_vp(V)(signed short    *)> nik_ce auto integer<Limit::sint_index, V> = Limit::_short;
		template<nik_vp(V)(signed int      *)> nik_ce auto integer<Limit::sint_index, V> = Limit::_int;
		template<nik_vp(V)(signed long     *)> nik_ce auto integer<Limit::sint_index, V> = Limit::_long;
		template<nik_vp(V)(signed long long*)> nik_ce auto integer<Limit::sint_index, V> = Limit::_long_long;

		template<auto V>                       nik_ce auto integer<Limit::sint_index, V> = Limit::_length;

	// limit:

		// Assumes sint_index and uint_index align.

		template<typename SIntType>
		nik_ce auto sint_limit(void(*i)(SIntType*))
		{
			nik_ce auto UIntIndex = integer<Limit::sint_index, U_restore_T<decltype(i)>>;

			nik_ce SIntType max   = (uint_limits[UIntIndex][Limit::_max] >> 1);
			nik_ce SIntType min   = -max-1;
			nik_ce SIntType width = uint_limits[UIntIndex][Limit::_width];

			return array<csint_type, width, min, max>;
		}

		nik_ce auto sint_limits = array
		<
			cslim_type,

			sint_limit ( U_sint_char        ),
			sint_limit ( U_sint_short       ),
			sint_limit ( U_sint_int         ),
			sint_limit ( U_sint_long        ),
			sint_limit ( U_sint_long_long   )
		>;

	// type:

		template<auto... Vs> nik_ce auto integer<Limit::sint_type, Limit::_char      , Vs...> = U_sint_char;
		template<auto... Vs> nik_ce auto integer<Limit::sint_type, Limit::_short     , Vs...> = U_sint_short;
		template<auto... Vs> nik_ce auto integer<Limit::sint_type, Limit::_int       , Vs...> = U_sint_int;
		template<auto... Vs> nik_ce auto integer<Limit::sint_type, Limit::_long      , Vs...> = U_sint_long;
		template<auto... Vs> nik_ce auto integer<Limit::sint_type, Limit::_long_long , Vs...> = U_sint_long_long;

	// is type:

		template<auto V>
		nik_ce auto integer<Limit::is_sint_type, V> = (integer<Limit::sint_index, V> < Limit::_length);

		nik_ce auto _is_sint_type_ = Limit::is_sint_type;

	// not type:

		template<auto V>
		nik_ce auto integer<Limit::not_sint_type, V> = (integer<Limit::sint_index, V> == Limit::_length);

		nik_ce auto _not_sint_type_ = Limit::not_sint_type;

	// width:

		template<auto V>
		nik_ce auto integer<Limit::sint_width, V> = sint_limits[integer<Limit::sint_index, V>][Limit::_width];

		nik_ce auto _sint_width_ = Limit::sint_width;

	// min:

		template<auto V>
		nik_ce auto integer<Limit::sint_min, V> = sint_limits[integer<Limit::sint_index, V>][Limit::_min];

		nik_ce auto _sint_min_ = Limit::sint_min;

	// max:

		template<auto V>
		nik_ce auto integer<Limit::sint_max, V> = sint_limits[integer<Limit::sint_index, V>][Limit::_max];

		nik_ce auto _sint_max_ = Limit::sint_max;

	// find (width to type-index):

		template<auto width>
		nik_ce auto integer<Limit::sint_find, width> = integer
		<
			Limit::sint_type,
			overload
			<
				U_match_width<width, cslim_type>,
				sint_limits,
				Limit::_length
			>
		>;

		nik_ce auto _sint_find_ = Limit::sint_find;

	// increment (casting):

		// currently unsafe---no bounds check:

		template<auto V>
		nik_ce auto integer<Limit::sint_increment, V> = integer
		<
			Limit::sint_find,
			(integer<Limit::sint_width, V> << 1)
		>;

		nik_ce auto _sint_increment_ = Limit::sint_increment;

	// decrement (casting):

		// currently unsafe---no bounds check:

		template<auto V>
		nik_ce auto integer<Limit::sint_decrement, V> = integer
		<
			Limit::sint_find,
			(integer<Limit::sint_width, V> >> 1)
		>;

		nik_ce auto _sint_decrement_ = Limit::sint_decrement;

/***********************************************************************************************************************/

// generic:

	// is type:

		template<auto V>
		nik_ce auto integer<Limit::is_int_type, V> = (integer<Limit::is_uint_type, V> || integer<Limit::is_sint_type, V>);

		nik_ce auto _is_int_type_ = Limit::is_int_type;

	// not type:

		template<auto V>
		nik_ce auto integer<Limit::not_int_type, V> = (integer<Limit::not_uint_type, V> && integer<Limit::not_sint_type, V>);

		nik_ce auto _not_int_type_ = Limit::not_int_type;

	// width:

		template<auto V>
		nik_ce auto integer<Limit::int_width, V> = integer<Limit::is_uint_type, V> ? integer<Limit::uint_width, V> :
											     integer<Limit::sint_width, V> ;

		nik_ce auto _int_width_ = Limit::int_width;

	// min:

		template<auto V>
		nik_ce auto integer<Limit::int_min, V> = integer<Limit::is_uint_type, V> ? integer<Limit::uint_min, V> :
											   integer<Limit::sint_min, V> ;

		nik_ce auto _int_min_ = Limit::int_min;

	// max:

		template<auto V>
		nik_ce auto integer<Limit::int_max, V> = integer<Limit::is_uint_type, V> ? integer<Limit::uint_max, V> :
											   integer<Limit::sint_min, V> ;

		nik_ce auto _int_max_ = Limit::int_max;

	// find:

		template<auto V>
		nik_ce auto integer<Limit::int_find, V> = integer<Limit::is_uint_type, V> ? integer<Limit::uint_find, V> :
											    integer<Limit::sint_find, V> ;

		nik_ce auto _int_find_ = Limit::int_find;

	// increment:

		// currently unsafe---no bounds check:

		template<auto V>
		nik_ce auto integer<Limit::int_increment, V> = integer<Limit::is_uint_type, V> ? integer<Limit::uint_increment, V> :
											         integer<Limit::sint_increment, V> ;

		nik_ce auto _int_increment_ = Limit::int_increment;

	// decrement:

		// currently unsafe---no bounds check:

		template<auto V>
		nik_ce auto integer<Limit::int_decrement, V> = integer<Limit::is_uint_type, V> ? integer<Limit::uint_decrement, V> :
											         integer<Limit::sint_decrement, V> ;

		nik_ce auto _int_decrement_ = Limit::int_decrement;

/***********************************************************************************************************************/

// integer reshaping:

	//	unsigned long x = (unsigned long) 1 << 32;

	//	unsigned *y = (unsigned*) &x;

	//	printf("%lu, ", x);
	//	printf("%u, ", y[0]);
	//	printf("%u, ", y[1]);

	//	for (auto i : x) printf("%lu, ", i);
	//	printf("\n");

	//	for (unsigned *i = y; i < y + 16; ++i) printf("%u, ", *i);
	//	printf("\n");

/***********************************************************************************************************************/

// array reshaping:

	//	unsigned long x[] = { 0, 1, 2, 3, 4, 5, 6, ((unsigned long) 1 << 32) };

	//	unsigned *y = (unsigned*) x;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp_numerical

