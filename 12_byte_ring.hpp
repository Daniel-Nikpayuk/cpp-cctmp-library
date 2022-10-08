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

	template<auto U> using T_store_U				= typename cctmp::template T_store_U<U>;
	template<auto... Vs> using T_pack_Vs				= typename cctmp::template T_pack_Vs<Vs...>;

//	template<typename T> nik_ce auto U_store_T			= cctmp::template U_store_T<T>;

	template<auto... Vs> nik_ce auto U_pack_Vs			= cctmp::template U_pack_Vs<Vs...>;

	template<typename T, auto... Vs> nik_ce auto array		= cctmp::template array<T, Vs...>;

	nik_ce auto U_unsigned_char					= cctmp::U_unsigned_char;
	nik_ce auto U_unsigned_short					= cctmp::U_unsigned_short;
	nik_ce auto U_unsigned_int					= cctmp::U_unsigned_int;
	nik_ce auto U_unsigned_long					= cctmp::U_unsigned_long;
	nik_ce auto U_unsigned_long_long				= cctmp::U_unsigned_long_long;

	nik_ce auto U_signed_char					= cctmp::U_signed_char;
	nik_ce auto U_signed_short					= cctmp::U_signed_short;
	nik_ce auto U_signed_int					= cctmp::U_signed_int;
	nik_ce auto U_signed_long					= cctmp::U_signed_long;
	nik_ce auto U_signed_long_long					= cctmp::U_signed_long_long;

	using key_type							= typename cctmp::key_type;

	nik_ce auto _zero						= cctmp::_zero;
	nik_ce auto _one						= cctmp::_one;
	nik_ce auto _eight						= cctmp::_eight;

	template<auto... Vs> nik_ce auto overload			= cctmp::template overload<Vs...>;

	template<auto V> nik_ce auto _match_				= cctmp::template _match_<V>;
	template<auto V> nik_ce auto _is_greater_than_or_equal_		= cctmp::template _is_greater_than_or_equal_<V>;

	nik_ce auto _length_						= cctmp::_length_;

	template<auto... Vs> nik_ce auto unpack_			= cctmp::template unpack_<Vs...>;

	template<auto... Vs> nik_ce auto list_at			= cctmp_functional::template list_at<Vs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// builtin:

	template<key_type, auto... Vs>
	nik_ce auto builtin = U_pack_Vs<Vs...>;

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

			nik_ces auto indices				= U_pack_Vs
									<
										_char,
										_short,
										_int,
										_long,
										_long_long
									>;

			nik_ces key_type length				=  unpack_<indices, _length_>;

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
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// ring:

/***********************************************************************************************************************/

// byte size:

	template<key_type ByteSize>
	class ring
	{
			template<key_type... indices>
			nik_ces auto to_byte_size_array(nik_avp(T_pack_Vs<indices...>*))
			{
				return array
				<
					key_type,
					sizeof(T_store_U<builtin<Builtin::_unsigned, indices>>)...
				>;
			}

			template<key_type byte_size>
			nik_ces auto index = overload
			<
				_match_<_is_greater_than_or_equal_<byte_size>>,
				to_byte_size_array(Builtin::indices),
				Builtin::length
			>;

			nik_ces auto type = list_at<Builtin::indices, index<ByteSize>>;

		public:

			nik_ces auto U_unsigned_type		= builtin<Builtin::_unsigned, type>;
			using builtin_type			= T_store_U<U_unsigned_type>;

			nik_ces builtin_type byte_size		= sizeof(builtin_type);
			nik_ces builtin_type bit_size		= _eight * byte_size;

			using prev_type				= ring<(byte_size >> 1)>;
			using next_type				= ring<(byte_size << 1)>;

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

// policy:

	struct Policy
	{
		nik_ces key_type byte_size		=  0;
		nik_ces key_type bit_size		=  1;
		nik_ces key_type builtin_type		=  2;
	};

/***********************************************************************************************************************/

// syntactic sugar:

	template<auto V, auto P>
	nik_ce auto ring_parameter()
	{
		if      constexpr (P == Policy::byte_size) return V;
		else if constexpr (P == Policy::bit_size ) return V / _eight;
		else                                       return sizeof(T_store_U<V>);
	}

	template<auto V, auto P = Policy::byte_size>
	using make_ring = ring<ring_parameter<V, P>()>;

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

