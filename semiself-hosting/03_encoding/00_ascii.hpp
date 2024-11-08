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

// ascii:

namespace cctmp    {
namespace encoding {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// char(acter):

/***********************************************************************************************************************/

// set:

	template<typename CharType>
	struct ascii_set
	{
		using char_type		= typename alias<CharType>::type;
		using char_ctype	= typename alias<CharType>::ctype;

		nik_ces char_type whitespace[] =
		{
			' ', '\t', '\n'
		};

		nik_ces char_type latin_digit[] =
		{
			'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
		};

		nik_ces char_type latin_lowercase[] =
		{
			'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
			'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
			'u', 'v', 'w', 'x', 'y', 'z'
		};

		nik_ces char_type latin_uppercase[] =
		{
			'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
			'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
			'U', 'V', 'W', 'X', 'Y', 'Z'
		};
	};

/***********************************************************************************************************************/

// interface:

	template<typename CharType, typename SizeType>
	class ascii_char
	{
		public:

			using char_type			= typename alias<CharType>::type;
			using char_ctype		= typename alias<CharType>::ctype;

			using size_type			= typename alias<SizeType>::type;
			using size_ctype		= typename alias<SizeType>::ctype;

		protected:

			using lit_type			= array_literal<char_type, size_type>;
			using ascii_set_type		= ascii_set<char_type>;

			nik_ces auto whitespace		= lit_type{ ascii_set_type::whitespace      };
			nik_ces auto latin_digit	= lit_type{ ascii_set_type::latin_digit     };
			nik_ces auto latin_lowercase	= lit_type{ ascii_set_type::latin_lowercase };
			nik_ces auto latin_uppercase	= lit_type{ ascii_set_type::latin_uppercase };

			char_type character;

		public:

			nik_ce ascii_char() : character{} { }

			nik_ce ascii_char(const char c) : character{c} { }

			nik_ce bool operator == (const ascii_char & c) const
				{ return (character == c.character); }

			nik_ce bool operator != (const ascii_char & c) const
				{ return (character != c.character); }

			// matches (atomic):

				// whitespace:

					nik_ce bool is_whitespace() const
						{ return whitespace.contains(character); }

				// digit (optimization):

					nik_ce bool is_digit() const
						{ return ('0' <= character) && (character <= '9'); }

				// underscore:

					nik_ce bool is_underscore() const { return (character == '_'); }

				// latin lowercase:

					nik_ce bool is_latin_lowercase() const
						{ return latin_lowercase.contains(character); }

				// latin uppercase:

					nik_ce bool is_latin_uppercase() const
						{ return latin_uppercase.contains(character); }

			// matches (composite):

				// latin alphabet:

					nik_ce bool is_latin_alphabet() const
						{ return is_latin_lowercase() || is_latin_uppercase(); }

				// latin alphanumeric:

					nik_ce bool is_latin_alphanumeric() const
						{ return is_digit() || is_latin_alphabet(); }

				// underscore latin alphabet:

					nik_ce bool is_underscore_latin_alphabet() const
						{ return is_underscore() || is_latin_alphabet(); }

				// underscore latin alphanumeric:

					nik_ce bool is_underscore_latin_alphanumeric() const
						{ return is_digit() || is_underscore_latin_alphabet(); }

		public:

			nik_ce char_type value() const { return character; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

}} // namespace cctmp::encoding

