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

// utf8:

namespace cctmp    {
namespace encoding {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// spec(ification):

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// byte:

/***********************************************************************************************************************/

// interface:

	template<typename CharType, typename SizeType>
	struct utf8_byte
	{
		using char_type			= typename alias<CharType>::type;
		using char_ctype		= typename alias<CharType>::ctype;

		using size_type			= typename alias<SizeType>::type;
		using size_ctype		= typename alias<SizeType>::ctype;

		nik_ces size_type max_length	= 4;

		struct Range
		{
			enum : size_type
			{
				x00_x7f, xc2_xdf, xe0_xe0, xe1_xec, xed_xed,
				xee_xef, xf0_xf0, xf1_xf3, xf4_xf4,

				dimension
			};
		};

		struct Byte { enum : size_type { b1, e1, b2, e2, b3, e3, b4, e4, dimension }; };

		nik_ces char_type range[][Byte::dimension] =
		{
			{ 0x00,0x7f , 0x00,0x7f , 0x00,0x7f , 0x00,0x7f },
			{ 0xc2,0xdf , 0x80,0xbf , 0x00,0x7f , 0x00,0x7f },
			{ 0xe0,0xe0 , 0xa0,0xbf , 0x80,0xbf , 0x00,0x7f },
			{ 0xe1,0xec , 0x80,0xbf , 0x80,0xbf , 0x00,0x7f },
			{ 0xed,0xed , 0x80,0x9f , 0x80,0xbf , 0x00,0x7f },
			{ 0xee,0xef , 0x80,0xbf , 0x80,0xbf , 0x00,0x7f },
			{ 0xf0,0xf0 , 0x90,0xbf , 0x80,0xbf , 0x80,0xbf },
			{ 0xf1,0xf3 , 0x80,0xbf , 0x80,0xbf , 0x80,0xbf },
			{ 0xf4,0xf4 , 0x80,0x8f , 0x80,0xbf , 0x80,0xbf }
		};

		// valid range:

			nik_ces bool valid_range(size_ctype n) { return (n != Range::dimension); }

		// in byte range:

			nik_ces bool in_byte_range(char_ctype v, size_ctype n, size_ctype f, size_ctype l)
				{ return (range[n][f] <= v && v <= range[n][l]); }

			nik_ces bool in_byte1_range(char_ctype v, size_ctype n)
				{ return in_byte_range(v, n, Byte::b1, Byte::e1); }

			nik_ces bool in_byte2_range(char_ctype v, size_ctype n)
				{ return in_byte_range(v, n, Byte::b2, Byte::e2); }

			nik_ces bool in_byte3_range(char_ctype v, size_ctype n)
				{ return in_byte_range(v, n, Byte::b3, Byte::e3); }

			nik_ces bool in_byte4_range(char_ctype v, size_ctype n)
				{ return in_byte_range(v, n, Byte::b4, Byte::e4); }

		// byte range:

			nik_ces size_type byte_range(size_ctype b, char_ctype v, size_ctype f, size_ctype l)
			{
				for (size_type k = b; k != Range::dimension; ++k)
					if (in_byte_range(v, k, f, l)) return k;

				return Range::dimension;
			}

			nik_ces bool byte1_range(char_ctype v) { return byte_range(0, v, Byte::b1, Byte::e1); }
			nik_ces bool byte2_range(char_ctype v) { return byte_range(1, v, Byte::b2, Byte::e2); }
			nik_ces bool byte3_range(char_ctype v) { return byte_range(2, v, Byte::b3, Byte::e3); }
			nik_ces bool byte4_range(char_ctype v) { return byte_range(6, v, Byte::b4, Byte::e4); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// code point:

/***********************************************************************************************************************/

// interface:

	template<typename CharType, typename PointType, typename SizeType>
	struct utf8_point
	{
		using char_type		= typename alias<CharType>::type;
		using char_ctype	= typename alias<CharType>::ctype;

		using point_type	= typename alias<PointType>::type;
		using point_ctype	= typename alias<PointType>::ctype;

		using size_type		= typename alias<SizeType>::type;
		using size_ctype	= typename alias<SizeType>::ctype;

		struct Range
		{
			enum : size_type
			{
				x000000_x00007f,
				x000080_x0007ff,
				x000800_x000fff,
				x001000_x00cfff,
				x00d000_x00d7ff,
				x00e000_x00ffff,
				x010000_x03ffff,
				x040000_x0fffff,
				x100000_x10ffff,

				dimension
			};
		};

		struct Point { enum : size_type { b, e, dimension }; };

		nik_ces point_type range[][Point::dimension] =
		{
			{ 0x000000 , 0x00007f },
			{ 0x000080 , 0x0007ff },
			{ 0x000800 , 0x000fff },
			{ 0x001000 , 0x00cfff },
			{ 0x00d000 , 0x00d7ff },
			{ 0x00e000 , 0x00ffff },
			{ 0x010000 , 0x03ffff },
			{ 0x040000 , 0x0fffff },
			{ 0x100000 , 0x10ffff }
		};

		nik_ces bool in_range(point_ctype v, size_ctype n)
			{ return (range[n][Point::b] <= v && v <= range[n][Point::e]); }

		nik_ces size_type point_range(char_ctype v)
		{
			for (size_type k = 0; k != Range::dimension; ++k)
				if (in_range(v, k)) return k;

			return Range::dimension;
		}
	};

/***********************************************************************************************************************/

// apply:

/*
	template<gkey_type, auto...> struct utf8_apply;

	// x000000 - x00007f:

		template<auto... filler>
		struct utf8_apply<Utf8Spec::x000000_x00007f, filler...>
		{
			using uint8_type		= typename Utf8Spec::uint8_type;
			using uint8_ctype		= typename Utf8Spec::uint8_ctype;

			using uint32_type		= typename Utf8Spec::uint32_type;
			using uint32_ctype		= typename Utf8Spec::uint32_ctype;

			using size_type			= typename Utf8Spec::size_type;
			using size_ctype		= typename Utf8Spec::size_ctype;

			nik_ces size_type byte_size	= 1;

			nik_ces uint32_type to_scalar(uint8_ctype (&u)[Utf8Spec::max_byte_size])
			{
				return 0;
			}
		};

	// x000080 - x0007ff:

		template<auto... filler>
		struct utf8_apply<Utf8Spec::x000080_x0007ff, filler...>
		{
			using uint8_type		= typename Utf8Spec::uint8_type;
			using uint8_ctype		= typename Utf8Spec::uint8_ctype;

			using uint32_type		= typename Utf8Spec::uint32_type;
			using uint32_ctype		= typename Utf8Spec::uint32_ctype;

			using size_type			= typename Utf8Spec::size_type;
			using size_ctype		= typename Utf8Spec::size_ctype;

			nik_ces size_type byte_size	= 2;
		};

	// x000800 - x000fff:

		template<auto... filler>
		struct utf8_apply<Utf8Spec::x000800_x000fff, filler...>
		{
			using uint8_type		= typename Utf8Spec::uint8_type;
			using uint8_ctype		= typename Utf8Spec::uint8_ctype;

			using uint32_type		= typename Utf8Spec::uint32_type;
			using uint32_ctype		= typename Utf8Spec::uint32_ctype;

			using size_type			= typename Utf8Spec::size_type;
			using size_ctype		= typename Utf8Spec::size_ctype;

			nik_ces size_type byte_size	= 3;
		};

	// x001000 - x00cfff:

		template<auto... filler>
		struct utf8_apply<Utf8Spec::x001000_x00cfff, filler...>
		{
			using uint8_type		= typename Utf8Spec::uint8_type;
			using uint8_ctype		= typename Utf8Spec::uint8_ctype;

			using uint32_type		= typename Utf8Spec::uint32_type;
			using uint32_ctype		= typename Utf8Spec::uint32_ctype;

			using size_type			= typename Utf8Spec::size_type;
			using size_ctype		= typename Utf8Spec::size_ctype;

			nik_ces size_type byte_size	= 3;
		};

	// x00d000 - x00d7ff:

		template<auto... filler>
		struct utf8_apply<Utf8Spec::x00d000_x00d7ff, filler...>
		{
			using uint8_type		= typename Utf8Spec::uint8_type;
			using uint8_ctype		= typename Utf8Spec::uint8_ctype;

			using uint32_type		= typename Utf8Spec::uint32_type;
			using uint32_ctype		= typename Utf8Spec::uint32_ctype;

			using size_type			= typename Utf8Spec::size_type;
			using size_ctype		= typename Utf8Spec::size_ctype;

			nik_ces size_type byte_size	= 3;
		};

	// x00e000 - x00ffff:

		template<auto... filler>
		struct utf8_apply<Utf8Spec::x00e000_x00ffff, filler...>
		{
			using uint8_type		= typename Utf8Spec::uint8_type;
			using uint8_ctype		= typename Utf8Spec::uint8_ctype;

			using uint32_type		= typename Utf8Spec::uint32_type;
			using uint32_ctype		= typename Utf8Spec::uint32_ctype;

			using size_type			= typename Utf8Spec::size_type;
			using size_ctype		= typename Utf8Spec::size_ctype;

			nik_ces size_type byte_size	= 3;
		};

	// x010000 - x03ffff:

		template<auto... filler>
		struct utf8_apply<Utf8Spec::x010000_x03ffff, filler...>
		{
			using uint8_type		= typename Utf8Spec::uint8_type;
			using uint8_ctype		= typename Utf8Spec::uint8_ctype;

			using uint32_type		= typename Utf8Spec::uint32_type;
			using uint32_ctype		= typename Utf8Spec::uint32_ctype;

			using size_type			= typename Utf8Spec::size_type;
			using size_ctype		= typename Utf8Spec::size_ctype;

			nik_ces size_type byte_size	= 4;
		};

	// x040000 - x0fffff:

		template<auto... filler>
		struct utf8_apply<Utf8Spec::x040000_x0fffff, filler...>
		{
			using uint8_type		= typename Utf8Spec::uint8_type;
			using uint8_ctype		= typename Utf8Spec::uint8_ctype;

			using uint32_type		= typename Utf8Spec::uint32_type;
			using uint32_ctype		= typename Utf8Spec::uint32_ctype;

			using size_type			= typename Utf8Spec::size_type;
			using size_ctype		= typename Utf8Spec::size_ctype;

			nik_ces size_type byte_size	= 4;
		};

	// x100000 - x10ffff:

		template<auto... filler>
		struct utf8_apply<Utf8Spec::x100000_x10ffff, filler...>
		{
			using uint8_type		= typename Utf8Spec::uint8_type;
			using uint8_ctype		= typename Utf8Spec::uint8_ctype;

			using uint32_type		= typename Utf8Spec::uint32_type;
			using uint32_ctype		= typename Utf8Spec::uint32_ctype;

			using size_type			= typename Utf8Spec::size_type;
			using size_ctype		= typename Utf8Spec::size_ctype;

			nik_ces size_type byte_size	= 4;
		};
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// char(acter):

/***********************************************************************************************************************/

// valid:

	template<typename Unicode>
	struct utf8_valid
	{
		using unicode_type		= typename alias<Unicode>::type;
		using unicode_ctype		= typename alias<Unicode>::ctype;

		using char_type			= typename unicode_type::char_type;
		using char_ctype		= typename unicode_type::char_ctype;

		using size_type			= typename unicode_type::size_type;
		using size_ctype		= typename unicode_type::size_ctype;

		using byte_type			= utf8_byte<char_type, size_type>;
		using byte_range		= typename byte_type::Range;

		template<typename In, typename End>
		nik_ces void push(unicode_type & ch, In in, End end)
			{ if (in != end) { push_byte1(ch, byte_type::byte1_range(*in), in, end); } }

		template<typename In, typename End>
		nik_ces void push_byte1(unicode_type & ch, size_ctype row, In in, End end)
		{
			if (byte_type::valid_range(row))
			{
				ch += static_cast<char_type>(*in);

				if (row != byte_range::x00_x7f) push_byte2(ch, row, in + 1, end);
			}
		}

		template<typename In, typename End>
		nik_ces void push_byte2(unicode_type & ch, size_ctype row, In in, End end)
		{
			if (in != end && byte_type::in_byte2_range(*in, row))
			{
				ch += static_cast<char_type>(*in);

				if (row != byte_range::xc2_xdf) push_byte3(ch, row, in + 1, end);
			}
		}

		template<typename In, typename End>
		nik_ces void push_byte3(unicode_type & ch, size_ctype row, In in, End end)
		{
			if (in != end && byte_type::in_byte3_range(*in, row))
			{
				ch += static_cast<char_type>(*in);

				const bool is_byte4 =	(row == byte_range::xf0_xf0) ||
							(row == byte_range::xf1_xf3) ||
							(row == byte_range::xf4_xf4) ;

				if (is_byte4) push_byte4(ch, row, in + 1, end);
			}
		}

		template<typename In, typename End>
		nik_ces void push_byte4(unicode_type & ch, size_ctype row, In in, End end)
		{
			if (in != end && byte_type::in_byte4_range(*in, row))
				{ ch += static_cast<char_type>(*in); }
		}
	};

/***********************************************************************************************************************/

// interface:

	template<typename CharType, typename SizeType>
	class utf8_char
	{
		public:

			using char_type			= typename alias<CharType>::type;
			using char_ctype		= typename alias<CharType>::ctype;

			using size_type			= typename alias<SizeType>::type;
			using size_ctype		= typename alias<SizeType>::ctype;

			nik_ces size_type length	= 4;

			using array_type		= array<char_type, size_type, length>;
			using valid_type		= utf8_valid<utf8_char>;

		protected:

			using ascii_char_type		= ascii_char<char_type, size_type>;
			using ascii_char_type_ptr	= typename alias<ascii_char_type>::type_ptr;
			using ascii_char_type_cptr	= typename alias<ascii_char_type>::type_cptr;
			using ascii_char_type_ref	= typename alias<ascii_char_type>::type_ref;

			using ascii_char_ctype		= typename alias<ascii_char_type>::ctype;
			using ascii_char_ctype_ptr	= typename alias<ascii_char_type>::ctype_ptr;
			using ascii_char_ctype_cptr	= typename alias<ascii_char_type>::ctype_cptr;
			using ascii_char_ctype_ref	= typename alias<ascii_char_type>::ctype_ref;

			array_type character;

		public:

			nik_ce utf8_char() { }

			nik_ce utf8_char(ascii_char_ctype_ref c) { character.push(c.value()); }

			nik_ce size_type size() const { return character.size(); }

			nik_ce bool is_empty  () const { return character.is_empty(); }
			nik_ce bool not_empty () const { return character.not_empty(); }

			nik_ce utf8_char & operator += (ascii_char_ctype_ref c)
				{ character.push(c.value()); return *this; }

			template<typename In, typename End>
			nik_ce void push_valid(In in, End end) { valid_type::push(*this, in, end); }

			// c str(ing) array:

				nik_ce auto cstr_array() const
				{
					array<char, size_type, length + 1> cstr_arr;

					cstr_arr.push(character.cbegin(), character.cend());
					cstr_arr.push('\0');

					return cstr_arr;
				}

			// ascii:

				nik_ce ascii_char_type to_ascii() const { return ascii_char_type{character[0]}; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// string:

/***********************************************************************************************************************/

// interface:

	template<typename CharType, typename SizeType, SizeType Size>
	class utf8_string : public array<utf8_char<CharType, SizeType>, SizeType, Size>
	{
		public:

			using unicode_type		= utf8_char<CharType, SizeType>;
			using base			= array<unicode_type, SizeType, Size>;

			using char_type			= typename unicode_type::char_type;
			using char_ctype		= typename unicode_type::char_ctype;

			using size_type			= typename unicode_type::size_type;
			using size_ctype		= typename unicode_type::size_ctype;

		protected:

			nik_ce void set_invalid() { valid = false; }

			bool valid;

		public:

			nik_ce utf8_string() : valid{} { }

			nik_ce utf8_string(const string_literal<const char, size_type> & s) :
				utf8_string(s.cbegin(), s.cend()) { }

			template<typename In, typename End>
			nik_ce utf8_string(In in, End end) : valid{true}
			{
				while (in != end)
				{
					unicode_type ch;

					ch.push_valid(in, end);

					if (ch.not_empty())
					{
						base::push(ch);

						in += ch.size();
					}
					else
					{
						set_invalid();
						break;
					}
				}
			}

			nik_ce bool is_valid() const { return valid; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

}} // namespace cctmp::encoding

