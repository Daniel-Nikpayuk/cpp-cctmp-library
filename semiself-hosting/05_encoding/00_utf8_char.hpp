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

// utf8_char:

namespace cctmp    {
namespace encoding {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// utf8 char1:

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class utf8_char1_cmethod_disjoint : public Base
	{
		public:

			using base				= Base;
			using facade				= typename base::facade;
			using model_type			= typename base::model_type;

			nik_using_size_type_scope		(base)

			using icon_type				= typename base::icon_type;
			using icon_ctype_ref			= typename base::icon_ctype_ref;

			using sign_type				= typename base::sign_type;
			using sign_ctype_ref			= typename base::sign_ctype_ref;

		protected:

			// do I define these within the type system?

				// if so, as lists? Or as functions?
				// do I introduce the identity type?

		//	nik_ces char_type whitespace[3] =
		//	{
		//		' ', '\t', '\n'
		//	};

		//	nik_ces char_type latin_digit[10] =
		//	{
		//		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
		//	};

		//	nik_ces char_type latin_lowercase[26] =
		//	{
		//		'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
		//		'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
		//		'u', 'v', 'w', 'x', 'y', 'z'
		//	};

		//	nik_ces char_type latin_uppercase[26] =
		//	{
		//		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
		//		'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
		//		'U', 'V', 'W', 'X', 'Y', 'Z'
		//	};

		protected:

			using Range				= typename base::Range;
			using Point				= typename base::Point;

			nik_ces bool are_bytes_valid(size_ctype v1, size_ctype n)
				{ return base::is_byte1_valid(v1, n); }

		public:

			nik_ce utf8_char1_cmethod_disjoint() : base{} { }
			nik_ce utf8_char1_cmethod_disjoint(const facade & f) : base{f} { }

			// byte range:

				nik_ces bool is_char_valid(size_ctype v)
					{ return are_bytes_valid(v, Range::x00_x7f); }

			// code point:

				nik_ces bool is_code_valid(size_ctype v)
					{ return base::on_point(v, Point::x000000_x00007f); }

			// ascii:

			//	nik_ce void validate()
			//	{
			//		if (0 <= character && character < 128) set_valid();
			//		else set_invalid();
			//	}

			// matches (atomic):

		//		// whitespace:

		//			nik_ce bool is_whitespace() const
		//				{ return whitespace.contains(character); }

		//		// digit (optimization):

		//			nik_ce bool is_digit() const
		//				{ return ('0' <= character) && (character <= '9'); }

		//		// underscore:

		//			nik_ce bool is_underscore() const { return (character == '_'); }

		//		// latin lowercase:

		//			nik_ce bool is_latin_lowercase() const
		//				{ return latin_lowercase.contains(character); }

		//		// latin uppercase:

		//			nik_ce bool is_latin_uppercase() const
		//				{ return latin_uppercase.contains(character); }

			// matches (composite):

		//		// latin alphabet:

		//			nik_ce bool is_latin_alphabet() const
		//				{ return is_latin_lowercase() || is_latin_uppercase(); }

		//		// latin alphanumeric:

		//			nik_ce bool is_latin_alphanumeric() const
		//				{ return is_digit() || is_latin_alphabet(); }

		//		// underscore latin alphabet:

		//			nik_ce bool is_underscore_latin_alphabet() const
		//				{ return is_underscore() || is_latin_alphabet(); }

		//		// underscore latin alphanumeric:

		//			nik_ce bool is_underscore_latin_alphanumeric() const
		//				{ return is_digit() || is_underscore_latin_alphabet(); }
	};

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class utf8_char1_method_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;
			using model_type		= typename base::model_type;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

			using sign_type			= typename base::sign_type;
			using sign_ctype_ref		= typename base::sign_ctype_ref;

		public:

			nik_ce utf8_char1_method_disjoint() : base{} { }
			nik_ce utf8_char1_method_disjoint(const facade & f) : base{f} { }

			// define:

				nik_ce auto define_value(icon_ctype_ref icon, size_ctype v1)
					{ return base::define_value(icon, { v1 }); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// utf8 char2:

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class utf8_char2_cmethod_disjoint : public Base
	{
		public:

			using base				= Base;
			using facade				= typename base::facade;
			using model_type			= typename base::model_type;

			nik_using_size_type_scope		(base)

			using icon_type				= typename base::icon_type;
			using icon_ctype_ref			= typename base::icon_ctype_ref;

			using sign_type				= typename base::sign_type;
			using sign_ctype_ref			= typename base::sign_ctype_ref;

		protected:

			using Range				= typename base::Range;
			using Point				= typename base::Point;

			nik_ces bool are_bytes_valid(size_ctype v1, size_ctype v2, size_ctype n)
			{
				return	base::is_byte1_valid(v1, n) &&
					base::is_byte2_valid(v2, n) ;
			}

		public:

			nik_ce utf8_char2_cmethod_disjoint() : base{} { }
			nik_ce utf8_char2_cmethod_disjoint(const facade & f) : base{f} { }

			// byte range:

				nik_ces bool is_char_valid(size_ctype v1, size_ctype v2)
					{ return are_bytes_valid(v1, v2, Range::xc2_xdf); }

			// code point:

				nik_ces bool is_code_valid(size_ctype v)
					{ return base::on_point(v, Point::x000080_x0007ff); }
	};

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class utf8_char2_method_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;
			using model_type		= typename base::model_type;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

			using sign_type			= typename base::sign_type;
			using sign_ctype_ref		= typename base::sign_ctype_ref;

		public:

			nik_ce utf8_char2_method_disjoint() : base{} { }
			nik_ce utf8_char2_method_disjoint(const facade & f) : base{f} { }

			// define:

				nik_ce auto define_value(icon_ctype_ref icon, size_ctype v1, size_ctype v2)
					{ return base::define_value(icon, { v1, v2 }); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// utf8 char3:

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class utf8_char3_cmethod_disjoint : public Base
	{
		public:

			using base				= Base;
			using facade				= typename base::facade;
			using model_type			= typename base::model_type;

			nik_using_size_type_scope		(base)

			using icon_type				= typename base::icon_type;
			using icon_ctype_ref			= typename base::icon_ctype_ref;

			using sign_type				= typename base::sign_type;
			using sign_ctype_ref			= typename base::sign_ctype_ref;

		protected:

			using Range				= typename base::Range;
			using Point				= typename base::Point;

			nik_ces bool are_bytes_valid(size_ctype v1, size_ctype v2, size_ctype v3, size_ctype n)
			{
				return	base::is_byte1_valid(v1, n) &&
					base::is_byte2_valid(v2, n) &&
					base::is_byte3_valid(v3, n) ;
			}

		public:

			nik_ce utf8_char3_cmethod_disjoint() : base{} { }
			nik_ce utf8_char3_cmethod_disjoint(const facade & f) : base{f} { }

			// byte range:

				nik_ces bool is_char_valid(size_ctype v1, size_ctype v2, size_ctype v3)
				{
					return	are_bytes_valid_(v1, v2, v3, Range::xe0_xe0) ||
						are_bytes_valid_(v1, v2, v3, Range::xe1_xec) ||
						are_bytes_valid_(v1, v2, v3, Range::xed_xed) ||
						are_bytes_valid_(v2, v2, v3, Range::xee_xef) ;
				}

			// code point:

				nik_ces bool is_code_valid(size_ctype v)
				{
					return	base::on_point(v, Point::x000800_x000fff) ||
						base::on_point(v, Point::x001000_x00cfff) ||
						base::on_point(v, Point::x00d000_x00d7ff) ||
						base::on_point(v, Point::x00e000_x00ffff) ;
				}
	};

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class utf8_char3_method_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;
			using model_type		= typename base::model_type;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

			using sign_type			= typename base::sign_type;
			using sign_ctype_ref		= typename base::sign_ctype_ref;

		public:

			nik_ce utf8_char3_method_disjoint() : base{} { }
			nik_ce utf8_char3_method_disjoint(const facade & f) : base{f} { }

			// define:

				nik_ce auto define_value(icon_ctype_ref icon,
					size_ctype v1, size_ctype v2, size_ctype v3)
						{ return base::define_value(icon, { v1, v2, v3 }); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// utf8 char4:

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class utf8_char4_cmethod_disjoint : public Base
	{
		public:

			using base				= Base;
			using facade				= typename base::facade;
			using model_type			= typename base::model_type;

			nik_using_size_type_scope		(base)

			using icon_type				= typename base::icon_type;
			using icon_ctype_ref			= typename base::icon_ctype_ref;

			using sign_type				= typename base::sign_type;
			using sign_ctype_ref			= typename base::sign_ctype_ref;

		protected:

			using Range				= typename base::Range;
			using Point				= typename base::Point;

			nik_ces bool are_bytes_valid(size_ctype v1,
				size_ctype v2, size_ctype v3, size_ctype v4, size_ctype n)
			{
				return	base::is_byte1_valid(v1, n) &&
					base::is_byte2_valid(v2, n) &&
					base::is_byte3_valid(v3, n) &&
					base::is_byte4_valid(v4, n) ;
			}

		public:

			nik_ce utf8_char4_cmethod_disjoint() : base{} { }
			nik_ce utf8_char4_cmethod_disjoint(const facade & f) : base{f} { }

			// byte range:

				nik_ces bool is_char_valid(size_ctype v1, size_ctype v2, size_ctype v3, size_ctype v4)
				{
					return	are_bytes_valid_(v1, v2, v3, v4, Range::xf0_xf0) ||
						are_bytes_valid_(v1, v2, v3, v4, Range::xf1_xf3) ||
						are_bytes_valid_(v2, v2, v3, v4, Range::xf4_xf4) ;
				}

			// code point:

				nik_ces bool is_code_valid(size_ctype v)
				{
					return	base::on_point(v, Point::x010000_x03ffff) ||
						base::on_point(v, Point::x040000_x0fffff) ||
						base::on_point(v, Point::x100000_x10ffff) ;
				}
	};

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class utf8_char4_method_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;
			using model_type		= typename base::model_type;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

			using sign_type			= typename base::sign_type;
			using sign_ctype_ref		= typename base::sign_ctype_ref;

		public:

			nik_ce utf8_char4_method_disjoint() : base{} { }
			nik_ce utf8_char4_method_disjoint(const facade & f) : base{f} { }

			// define:

				nik_ce auto define_value(icon_ctype_ref icon,
					size_ctype v1, size_ctype v2, size_ctype v3, size_ctype v4)
						{ return base::define_value(icon, { v1, v2, v3, v4 }); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// utf8 char (utf8_char1 | utf8_char2 | utf8_char3 | utf8_char4):

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class utf8_char_cmethod_disjoint : public Base
	{
		public:

			using base				= Base;
			using facade				= typename base::facade;
			using model_type			= typename base::model_type;

			nik_using_size_type_scope		(base)

			using icon_type				= typename base::icon_type;
			using icon_ctype_ref			= typename base::icon_ctype_ref;

			using sign_type				= typename base::sign_type;
			using sign_ctype_ref			= typename base::sign_ctype_ref;

		public:

			nik_ce utf8_char_cmethod_disjoint() : base{} { }
			nik_ce utf8_char_cmethod_disjoint(const facade & f) : base{f} { }
	};

	// syntactic sugar:

		template<typename Facade>
		using utf8_char_cmethod =
			utf8_char_cmethod_disjoint        <
			cctmp::utf8_char_cmethod_disjoint < Facade >>;

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class utf8_char_method_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;
			using model_type		= typename base::model_type;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

			using sign_type			= typename base::sign_type;
			using sign_ctype_ref		= typename base::sign_ctype_ref;

		public:

			nik_ce utf8_char_method_disjoint() : base{} { }
			nik_ce utf8_char_method_disjoint(const facade & f) : base{f} { }

			// define:

			//	template<typename In, typename End>
			//	nik_ce auto push_value(icon_ctype_ref icon, In in, End end)
			//	{
			//		auto sign = base::declare_value(icon);

			//		size_ctype length = end - in;
			//		auto text_ival    = base::record_text(sign, ImageBuiltin::point, length);
			//		text_ival         . copy(0, in, end);

			//		return sign;
			//	}
	};

	// syntactic sugar:

		template<typename Facade>
		using utf8_char_method =
			utf8_char_method_disjoint         <
			utf8_char_cmethod_disjoint        <
			cctmp::utf8_char_method_disjoint  <
			cctmp::utf8_char_cmethod_disjoint < Facade >>>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

}} // namespace cctmp::encoding

