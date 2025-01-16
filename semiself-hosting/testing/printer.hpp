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

// printer:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// print:

	// does not accept compile time objects.
	// maybe move this class code to fileput?

	// might be better to declare constexpr static
	// and take the base type as input.

/***********************************************************************************************************************/

// array:

	template<typename Array>
	constexpr void print_array(const Array & a, const char *s = "%d ")
	{
		for (auto k = a.cbegin(); k != a.cend(); ++k) printf(s, *k);

		printf("\n");
	}

/***********************************************************************************************************************/

// immutable:

	// assumptions:

	template<typename Facade>
	class print_cmethod : public cctmp::array_cmethod<Facade>
	{
		public:

			using base			= cctmp::array_cmethod<Facade>;

			using ctype			= typename base::ctype;
			using ctype_ptr			= typename base::ctype_ptr;
			using ctype_cptr		= typename base::ctype_cptr;
			using ctype_ref			= typename base::ctype_ref;

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

		public:

			constexpr print_cmethod() : base{} { }
			constexpr print_cmethod(const Facade & f) : base{f} { }

			// set:

				constexpr void as_set(const char* s = "%d") const
				{
					if (base::cbegin() != base::cend())
					{
						printf("{ ");

						for (auto k = base::cbegin(); k != base::clast(); ++k)
						{
							printf(s, *k);
							printf(", ");
						}

						printf(s, *base::clast());
						printf(" }\n");
					}
				}
	};

/***********************************************************************************************************************/

// set:

	template<typename Logo>
	constexpr void print_as_set(const Logo & l)
	{
		using text_type = typename Logo::base::text_type;
		using cmethod0  = cctmp::resolve_cmethod<text_type, print_cmethod>;
		auto print_logo = l.ctext()->template cequip<cmethod0>();

		print_logo.as_set(); // prints: { 0, 8, 0 }
	}

