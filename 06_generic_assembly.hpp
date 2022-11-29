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

// generic assembly:

namespace cctmp_generics {

// cctmp:

	template<auto f> using T_out_type		= typename cctmp::template T_out_type<f>;

	nik_ce auto _is_zero_				= cctmp::_is_zero_;
	nik_ce auto _multiply_				= cctmp::_multiply_;

	nik_ce auto _cons_				= cctmp::_cons_;

	template<auto V> nik_ce auto _decrement_	= cctmp::template _decrement_<V>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// lookup:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// binding:

	template<typename CharType, auto Size, typename ValueType>
	struct binding
	{
		using char_type			= CharType;
		using string_type		= char_type const *;
		using size_type			= decltype(Size);

		nik_ces size_type size		= Size;
		nik_ces auto value		= U_restore_T<ValueType>;
		using value_type		= decltype(value);

		string_type string;

		nik_ce binding(const CharType (&s)[Size], ValueType) : string{s} { }
	};

/***********************************************************************************************************************/

// table:

	template<typename CharType, typename... Bindings>
	struct table
	{
		using char_type			= T_restore_T<CharType>;
		using cchar_type		= char_type const;
		using string_type		= char_type const*;
		using cstring_type		= string_type const;

		nik_ces auto size		= sizeof...(Bindings);
		using size_type			= decltype(size);

		nik_ces auto sizes		= array<size_type, Bindings::size...>;
		nik_ces auto values		= U_pack_Vs<Bindings::value...>;

		cstring_type string[size];

		nik_ce table(CharType, Bindings... bs) : string{bs.string...} { }
	};

/***********************************************************************************************************************/

// function:

//	template<auto Size>
//	nik_ce bool equals_charset(gstring_type b, gstring_type e, gcchar_type (&charset)[Size])
//	{
//		bool match = ((e-b) == Size);

//		for (gstring_type i = charset; match && i != charset + Size; ++b, ++i)
//			match = (*b == *i);

//		return match;
//	}

	template<typename SizeType, typename Type1, typename Type2>
	nik_ce auto ptr_diff_equal(const Type1 *b1, const Type1 *e1, const Type2 *b2, const Type2 *e2)
	{
		using size_type = SizeType;

		const size_type size1 = e1 - b1;
		const size_type size2 = e2 - b2;

		bool equal = (size1 == size2);

		while (equal && b1 != e1) equal = (*(b1++) == *(b2++));

		return equal;
	}

	template<auto f, typename StringType>
	nik_ce auto lookup_function(StringType str_begin, StringType str_end)
	{
		nik_ce auto table		= f();

		using table_type		= decltype(table);
		using size_type			= typename table_type::size_type;
		using string_type		= typename table_type::string_type;
		using cstring_type		= typename table_type::cstring_type;

		cstring_type *key		= table.string;
		cstring_type *key_end		= key + table.size;

		size_type *size			= table.sizes;

		while (key != key_end)
		{
			string_type b		= *key;
			string_type e		= b + *(size++);

			if (ptr_diff_equal<size_type>(b, e, str_begin, str_end)) break;

			++key;
		}

		return key - table.string;
	}

	template<auto f>
	nik_ce auto make_lookup_function()
	{
		using table_type	= T_out_type<f>;
		using string_type	= typename table_type::string_type;

		nik_ce auto values	= table_type::values;
		nik_ce auto lookup_f	= lookup_function<f, string_type>;

		return eval<_cons_, H_id, values, lookup_f>;
	}

	template<auto f>
	nik_ce auto make_environment = make_lookup_function<f>();

/***********************************************************************************************************************/

// default:

	nik_ce auto default_lookup()
	{
		return table
		(
		 	U_char,

			binding ( "is_zero"   , _is_zero_      ) ,
			binding ( "multiply"  , _multiply_     ) ,
			binding ( "decrement" , _decrement_<1> )
		);
	};

	nik_ce auto default_environment = make_environment<default_lookup>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // cctmp_generics

