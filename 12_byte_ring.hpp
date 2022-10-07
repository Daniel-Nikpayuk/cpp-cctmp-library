/************************************************************************************************************************
**
** Copyright 2022 Daniel Nikpayuk, Inuit Nunangat, The Inuit Nation
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

// byte ring:

namespace cctmp_byte_ring {

	template<auto U> using T_store_U			= typename cctmp::template T_store_U<U>;
//	template<auto... Vs> using T_pack_Vs			= typename cctmp::template T_pack_Vs<Vs...>;

//	template<typename T> nik_ce auto U_store_T		= cctmp::template U_store_T<T>;

	template<auto... Vs> nik_ce auto U_pack_Vs		= cctmp::template U_pack_Vs<Vs...>;

	nik_ce auto U_unsigned_char				= cctmp::U_unsigned_char;
	nik_ce auto U_unsigned_short				= cctmp::U_unsigned_short;
	nik_ce auto U_unsigned_int				= cctmp::U_unsigned_int;
	nik_ce auto U_unsigned_long				= cctmp::U_unsigned_long;
	nik_ce auto U_unsigned_long_long			= cctmp::U_unsigned_long_long;

	nik_ce auto U_signed_char				= cctmp::U_signed_char;
	nik_ce auto U_signed_short				= cctmp::U_signed_short;
	nik_ce auto U_signed_int				= cctmp::U_signed_int;
	nik_ce auto U_signed_long				= cctmp::U_signed_long;
	nik_ce auto U_signed_long_long				= cctmp::U_signed_long_long;

	using key_type						= typename cctmp::key_type;

	nik_ce auto _zero					= cctmp::_zero;
	nik_ce auto _one					= cctmp::_one;
	nik_ce auto _eight					= cctmp::_eight;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// builtin:

	template<key_type, auto... Vs>
	nik_ce auto builtin = U_pack_Vs<Vs...>;

	// (find) helper:

	//	template<auto width, typename ArrType>
	//	nik_ce auto limits_width_match(ArrType limit) { return (limit[_zero] >= width); }

	//	template<auto width, typename ArrType>
	//	nik_ce auto U_match_width = _match_<_apply_<limits_width_match<width, ArrType>>>;

/***********************************************************************************************************************/

// names:

	struct Builtin
	{
		// indices:

			nik_ces key_type _char				=  0;
			nik_ces key_type _short				=  1;
			nik_ces key_type _int				=  2;
			nik_ces key_type _long				=  3;
			nik_ces key_type _long_long			=  4;

			nik_ces key_type length				=  5;

		// operators:

			nik_ces key_type index				=  0;

			nik_ces key_type _unsigned			=  1;
			nik_ces key_type _signed			=  2;
	};

/***********************************************************************************************************************/

// limits:

	using ulimit_type = unsigned long long;
	using slimit_type =   signed long long;

/***********************************************************************************************************************/

// unsigned:

	// limit:

		template<auto U_unsigned_type>
		struct unsigned_limit
		{
			using type				= T_store_U<U_unsigned_type>;
			nik_ces auto U_signed_type		= builtin<Builtin::_signed, Builtin::index>;

			nik_ces ulimit_type byte_size		= sizeof(type);
			nik_ces ulimit_type bit_size		= _eight * byte_size;
			nik_ces ulimit_type minimum		= _zero;
			nik_ces ulimit_type maximum		= (type) -1;

			private:

			nik_ces auto index			= builtin<Builtin::index, U_unsigned_type>;
		};

	// index:

		template<nik_vp(V)(unsigned char     *)> nik_ce auto builtin<Builtin::index, V> = Builtin::_char;
		template<nik_vp(V)(unsigned short    *)> nik_ce auto builtin<Builtin::index, V> = Builtin::_short;
		template<nik_vp(V)(unsigned int      *)> nik_ce auto builtin<Builtin::index, V> = Builtin::_int;
		template<nik_vp(V)(unsigned long     *)> nik_ce auto builtin<Builtin::index, V> = Builtin::_long;
		template<nik_vp(V)(unsigned long long*)> nik_ce auto builtin<Builtin::index, V> = Builtin::_long_long;

		template<auto V>                         nik_ce auto builtin<Builtin::index, V> = Builtin::length;

	// _unsigned:

		template<auto... Vs> nik_ce auto builtin<Builtin::_unsigned, Builtin::_char      , Vs...> = U_unsigned_char;
		template<auto... Vs> nik_ce auto builtin<Builtin::_unsigned, Builtin::_short     , Vs...> = U_unsigned_short;
		template<auto... Vs> nik_ce auto builtin<Builtin::_unsigned, Builtin::_int       , Vs...> = U_unsigned_int;
		template<auto... Vs> nik_ce auto builtin<Builtin::_unsigned, Builtin::_long      , Vs...> = U_unsigned_long;
		template<auto... Vs> nik_ce auto builtin<Builtin::_unsigned, Builtin::_long_long , Vs...> = U_unsigned_long_long;

/***********************************************************************************************************************/

// signed:

	// limit:

		// Assumes signed and unsigned indices align.

		template<auto U_signed_type>
		struct signed_limit
		{
			using type				= T_store_U<U_signed_type>;
			nik_ces auto U_unsigned_type		= builtin<Builtin::_unsigned, Builtin::index>;

			nik_ces slimit_type byte_size		= sizeof(type);
			nik_ces slimit_type bit_size		= _eight * byte_size;
			nik_ces slimit_type maximum		= (unsigned_limit<U_unsigned_type>::maximum >> 1);
			nik_ces slimit_type minimum		= -maximum-1;

			private:

			nik_ces auto index			= builtin<Builtin::index, U_signed_type>;
		};

	// index:

		template<nik_vp(V)(signed char     *)> nik_ce auto builtin<Builtin::index, V> = Builtin::_char;
		template<nik_vp(V)(signed short    *)> nik_ce auto builtin<Builtin::index, V> = Builtin::_short;
		template<nik_vp(V)(signed int      *)> nik_ce auto builtin<Builtin::index, V> = Builtin::_int;
		template<nik_vp(V)(signed long     *)> nik_ce auto builtin<Builtin::index, V> = Builtin::_long;
		template<nik_vp(V)(signed long long*)> nik_ce auto builtin<Builtin::index, V> = Builtin::_long_long;

		// The default is already defined with unsigned.

	// _signed:

		template<auto... Vs> nik_ce auto builtin<Builtin::_signed, Builtin::_char      , Vs...> = U_signed_char;
		template<auto... Vs> nik_ce auto builtin<Builtin::_signed, Builtin::_short     , Vs...> = U_signed_short;
		template<auto... Vs> nik_ce auto builtin<Builtin::_signed, Builtin::_int       , Vs...> = U_signed_int;
		template<auto... Vs> nik_ce auto builtin<Builtin::_signed, Builtin::_long      , Vs...> = U_signed_long;
		template<auto... Vs> nik_ce auto builtin<Builtin::_signed, Builtin::_long_long , Vs...> = U_signed_long_long;

/***********************************************************************************************************************/

// generic:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// bits:

	enum struct Bits
	{
		_8,
		_16,
		_32,
		_64
	};

/***********************************************************************************************************************/

// bytes:

	enum struct Bytes
	{
		_1,
		_2,
		_4,
		_8
	};

/***********************************************************************************************************************/

// protoring:

//	template<Bytes... byte_size> struct protoring;

/***********************************************************************************************************************/

// cast:

/*
	template<Bytes... filler>
	class protoring<Bytes::_1, filler...>
	{
		public:

			using prev_type				= void;
			using next_type				= ring<Bytes::_2, filler...>;

			using builtin_type			= unsigned char;

			nik_ces builtin_type bit_size		= 8;
			nik_ces builtin_type byte_size		= 1;

			nik_ces builtin_type zero		= 0;
			nik_ces builtin_type one		= 1;

		private:

			builtin_type value;

		public:

		[[nodiscard]] explicit nik_ce ring() : value(0) { };
		[[nodiscard]] explicit nik_ce ring(builtin_type v) : value(v) { };

		[[nodiscard]] const ring & operator = (builtin_type v) { value = v; return *this; }
		[[nodiscard]] const ring & operator = (const ring & v) { value = v.value; return *this; }

		[[nodiscard]] const ring operator + (const ring & v) const { return ring{(builtin_type)(value + v.value)}; }
		[[nodiscard]] const ring operator - (const ring & v) const { return ring{(builtin_type)(value - v.value)}; }
		[[nodiscard]] const ring operator * (const ring & v) const { return ring{(builtin_type)(value * v.value)}; }
		[[nodiscard]] const ring operator / (const ring & v) const { return ring{(builtin_type)(value / v.value)}; }

		[[nodiscard]] builtin_type to_builtin() const { return value; }
	};
*/

	// find (width to type-index):

	//	template<auto width>
	//	nik_ce auto integer<Limit::uint_find, width> = integer
	//	<
	//		Limit::uint_type,
	//		overload
	//		<
	//			U_match_width<width, culim_type>,
	//			uint_limits,
	//			Limit::_length
	//		>
	//	>;

	//	nik_ce auto _uint_find_ = Limit::uint_find;

	// increment (casting):

		// currently unsafe---no bounds check:

	//	template<auto V>
	//	nik_ce auto integer<Limit::uint_increment, V> = integer
	//	<
	//		Limit::uint_find,
	//		(integer<Limit::uint_width, V> << 1)
	//	>;

	//	nik_ce auto _uint_increment_ = Limit::uint_increment;

	// decrement (casting):

		// currently unsafe---no bounds check:

	//	template<auto V>
	//	nik_ce auto integer<Limit::uint_decrement, V> = integer
	//	<
	//		Limit::uint_find,
	//		(integer<Limit::uint_width, V> >> 1)
	//	>;

	//	nik_ce auto _uint_decrement_ = Limit::uint_decrement;

	// find (width to type-index):

	//	template<auto width>
	//	nik_ce auto integer<Limit::sint_find, width> = integer
	//	<
	//		Limit::sint_type,
	//		overload
	//		<
	//			U_match_width<width, cslim_type>,
	//			sint_limits,
	//			Limit::_length
	//		>
	//	>;

	//	nik_ce auto _sint_find_ = Limit::sint_find;

	// increment (casting):

		// currently unsafe---no bounds check:

	//	template<auto V>
	//	nik_ce auto integer<Limit::sint_increment, V> = integer
	//	<
	//		Limit::sint_find,
	//		(integer<Limit::sint_width, V> << 1)
	//	>;

	//	nik_ce auto _sint_increment_ = Limit::sint_increment;

	// decrement (casting):

		// currently unsafe---no bounds check:

	//	template<auto V>
	//	nik_ce auto integer<Limit::sint_decrement, V> = integer
	//	<
	//		Limit::sint_find,
	//		(integer<Limit::sint_width, V> >> 1)
	//	>;

	//	nik_ce auto _sint_decrement_ = Limit::sint_decrement;

/***********************************************************************************************************************/

	template<Bytes... byte_size> struct ring;

/***********************************************************************************************************************/

// one byte:

	template<Bytes... filler>
	class ring<Bytes::_1, filler...>
	{
		public:

			using prev_type				= void;
			using next_type				= ring<Bytes::_2, filler...>;

			using builtin_type			= unsigned char;

			nik_ces builtin_type bit_size		= 8;
			nik_ces builtin_type byte_size		= 1;

			nik_ces builtin_type zero		= 0;
			nik_ces builtin_type one		= 1;

		private:

			builtin_type value;

		public:

		[[nodiscard]] explicit nik_ce ring() : value(0) { };
		[[nodiscard]] explicit nik_ce ring(builtin_type v) : value(v) { };

		[[nodiscard]] const ring & operator = (builtin_type v) { value = v; return *this; }
		[[nodiscard]] const ring & operator = (const ring & v) { value = v.value; return *this; }

		[[nodiscard]] const ring operator + (const ring & v) const { return ring{(builtin_type)(value + v.value)}; }
		[[nodiscard]] const ring operator - (const ring & v) const { return ring{(builtin_type)(value - v.value)}; }
		[[nodiscard]] const ring operator * (const ring & v) const { return ring{(builtin_type)(value * v.value)}; }
		[[nodiscard]] const ring operator / (const ring & v) const { return ring{(builtin_type)(value / v.value)}; }

		[[nodiscard]] builtin_type to_builtin() const { return value; }
	};

/***********************************************************************************************************************/

// two bytes:

	template<Bytes... filler>
	class ring<Bytes::_2, filler...>
	{
		public:

			using prev_type				= ring<Bytes::_1, filler...>;
			using next_type				= ring<Bytes::_4, filler...>;

			using builtin_type			= unsigned short;

			nik_ces builtin_type bit_size		= 16;
			nik_ces builtin_type byte_size		= 2;

			nik_ces builtin_type zero		= 0;
			nik_ces builtin_type one		= 1;

		private:

			builtin_type value;

		public:

		[[nodiscard]] explicit nik_ce ring() : value(0) { };
		[[nodiscard]] explicit nik_ce ring(builtin_type v) : value(v) { };

		[[nodiscard]] const ring & operator = (builtin_type v) { value = v; return *this; }
		[[nodiscard]] const ring & operator = (const ring & v) { value = v.value; return *this; }

		[[nodiscard]] const ring operator + (const ring & v) const { return ring{(builtin_type)(value + v.value)}; }
		[[nodiscard]] const ring operator - (const ring & v) const { return ring{(builtin_type)(value - v.value)}; }
		[[nodiscard]] const ring operator * (const ring & v) const { return ring{(builtin_type)(value * v.value)}; }
		[[nodiscard]] const ring operator / (const ring & v) const { return ring{(builtin_type)(value / v.value)}; }

		[[nodiscard]] builtin_type to_builtin() const { return value; }
	};

/***********************************************************************************************************************/

// four bytes:

	template<Bytes... filler>
	class ring<Bytes::_4, filler...>
	{
		public:

			using prev_type				= ring<Bytes::_2, filler...>;
			using next_type				= ring<Bytes::_8, filler...>;

			using builtin_type			= unsigned int;

			nik_ces builtin_type bit_size		= 32;
			nik_ces builtin_type byte_size		= 4;

			nik_ces builtin_type zero		= 0;
			nik_ces builtin_type one		= 1;

		private:

			builtin_type value;

		public:

		[[nodiscard]] explicit nik_ce ring() : value(0) { };
		[[nodiscard]] explicit nik_ce ring(builtin_type v) : value(v) { };

		[[nodiscard]] const ring & operator = (builtin_type v) { value = v; return *this; }
		[[nodiscard]] const ring & operator = (const ring & v) { value = v.value; return *this; }

		[[nodiscard]] const ring operator + (const ring & v) const { return ring{value + v.value}; }
		[[nodiscard]] const ring operator - (const ring & v) const { return ring{value - v.value}; }
		[[nodiscard]] const ring operator * (const ring & v) const { return ring{value * v.value}; }
		[[nodiscard]] const ring operator / (const ring & v) const { return ring{value / v.value}; }

		[[nodiscard]] builtin_type to_builtin() const { return value; }
	};

/***********************************************************************************************************************/
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

} // namespace cctmp_byte_ring

