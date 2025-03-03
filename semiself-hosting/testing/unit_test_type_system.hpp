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

// type system (concord):

		//	print_array(*_test_0.value.csymbol()->cglyph()->ctext());
		//	print_array(*_test_0.value.csymbol()->cimage()->ctext());

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// test:

/***********************************************************************************************************************/

// empty (unique):

	void concord_empty_test()
	{
		constexpr auto empty_test_0 = concord_test_empty<unsigned long>{};

		// glyph:

			print_array(empty_test_0.empty_cglyph(empty_test_0.empty_icon));

			printf("\n");

		// image:

			print_array(empty_test_0.empty_cimage(empty_test_0.empty_sign_1));
			print_array(empty_test_0.empty_cimage(empty_test_0.empty_sign_2));

			printf("\n");

		// value:

			auto crecord = empty_test_0.empty_cmethod().crecord();

			if (crecord.not_empty()) { print_array(crecord); }
			else                     { printf("empty");      }

			printf("\n");
	}

/***********************************************************************************************************************/

// ring (unique):

	void concord_ring_test()
	{
		constexpr auto ring_test_0 = concord_test_ring<unsigned long>{};

		// glyph:

			print_array(ring_test_0.ring_cglyph(ring_test_0.ring4_icon));
			print_array(ring_test_0.ring_cglyph(ring_test_0.ring8_icon));

			printf("\n");

		// image:

			print_array(ring_test_0.ring_cimage(ring_test_0.ring4_sign_1));
			print_array(ring_test_0.ring_cimage(ring_test_0.ring8_sign_1));
			print_array(ring_test_0.ring_cimage(ring_test_0.ring8_sign_2));
			print_array(ring_test_0.ring_cimage(ring_test_0.ring8_sign_3));

			printf("\n");

		// value:

			printf("%lu ", ring_test_0.ring_cmethod().cvalue(ring_test_0.ring4_sign_1));
			printf("%lu ", ring_test_0.ring_cmethod().cvalue(ring_test_0.ring8_sign_1));
			printf("%lu ", ring_test_0.ring_cmethod().cvalue(ring_test_0.ring8_sign_2));
			printf("%lu ", ring_test_0.ring_cmethod().cvalue(ring_test_0.ring8_sign_3));

			printf("\n");
	}

/***********************************************************************************************************************/

// utf8 char (unique):

	void concord_utf8_char_test()
	{
		constexpr auto char_test_0 = concord_test_utf8_char<unsigned long>{};

		// glyph:

			print_array(char_test_0.char_cglyph(char_test_0.char1_icon));
			print_array(char_test_0.char_cglyph(char_test_0.char2_icon));
			print_array(char_test_0.char_cglyph(char_test_0.char3_icon));
			print_array(char_test_0.char_cglyph(char_test_0.char4_icon));

			printf("\n");

		// image:

			print_array(char_test_0.char_cimage(char_test_0.char1_sign_1));
			print_array(char_test_0.char_cimage(char_test_0.char2_sign_1));
			print_array(char_test_0.char_cimage(char_test_0.char3_sign_1));
			print_array(char_test_0.char_cimage(char_test_0.char4_sign_1));

			printf("\n");

		// value:

			printf("%lu ", char_test_0.char_cmethod().cvalue(char_test_0.char1_sign_1));
			printf("%lu ", char_test_0.char_cmethod().cvalue(char_test_0.char2_sign_1));
			printf("%lu ", char_test_0.char_cmethod().cvalue(char_test_0.char3_sign_1));
			printf("%lu ", char_test_0.char_cmethod().cvalue(char_test_0.char4_sign_1));

			printf("\n");
	}

/***********************************************************************************************************************/

// tuple:

	void concord_tuple_test()
	{
		constexpr auto tuple_test_0 = concord_test_tuple<unsigned long>{};

		// glyph:

			print_array(tuple_test_0.ring_cglyph(tuple_test_0.ring1_icon));
			print_array(tuple_test_0.ring_cglyph(tuple_test_0.ring4_icon));
			print_array(tuple_test_0.ring_cglyph(tuple_test_0.ring8_icon));
			print_array(tuple_test_0.ring_cglyph(tuple_test_0.tuple_icon));

			printf("\n");

		// image:

			print_array(tuple_test_0.ring_cimage(tuple_test_0.ring1_sign_1));
			print_array(tuple_test_0.ring_cimage(tuple_test_0.ring4_sign_1));
			print_array(tuple_test_0.ring_cimage(tuple_test_0.ring8_sign_1));
			print_array(tuple_test_0.ring_cimage(tuple_test_0.tuple_sign_1));

			printf("\n");

		// sign:

			auto s0 = tuple_test_0.tuple_cmethod().sub_sign(tuple_test_0.tuple_sign_1, 0);
			auto s1 = tuple_test_0.tuple_cmethod().sub_sign(tuple_test_0.tuple_sign_1, 1);
			auto s2 = tuple_test_0.tuple_cmethod().sub_sign(tuple_test_0.tuple_sign_1, 2);

		// value:

			printf("%lu ", tuple_test_0.ring_cmethod().cvalue(s0));
			printf("%lu ", tuple_test_0.ring_cmethod().cvalue(s1));
			printf("%lu ", tuple_test_0.ring_cmethod().cvalue(s2));

			printf("\n");
	}

/***********************************************************************************************************************/

// cotuple:

	void concord_cotuple_test()
	{
		constexpr auto cotuple_test_0 = concord_test_cotuple<unsigned long>{};

		// glyph:

			print_array(cotuple_test_0.ring_cglyph(cotuple_test_0.ring1_icon));
			print_array(cotuple_test_0.ring_cglyph(cotuple_test_0.ring4_icon));
			print_array(cotuple_test_0.ring_cglyph(cotuple_test_0.ring8_icon));
			print_array(cotuple_test_0.ring_cglyph(cotuple_test_0.cotuple_icon));

			printf("\n");

		// image:

			print_array(cotuple_test_0.ring_cimage(cotuple_test_0.ring1_sign_1));
			print_array(cotuple_test_0.ring_cimage(cotuple_test_0.ring4_sign_1));
			print_array(cotuple_test_0.ring_cimage(cotuple_test_0.ring8_sign_1));
			print_array(cotuple_test_0.ring_cimage(cotuple_test_0.cotuple_sign_1));

			printf("\n");

		// sign:

			auto s1 = cotuple_test_0.cotuple_cmethod().sub_sign(cotuple_test_0.cotuple_sign_1);
			auto s2 = cotuple_test_0.cotuple_cmethod().sub_sign(cotuple_test_0.cotuple_sign_2);
			auto s3 = cotuple_test_0.cotuple_cmethod().sub_sign(cotuple_test_0.cotuple_sign_3);

		// value:

			printf("%lu ", cotuple_test_0.ring_cmethod().cvalue(s1));
			printf("%lu ", cotuple_test_0.ring_cmethod().cvalue(s2));
			printf("%lu ", cotuple_test_0.ring_cmethod().cvalue(s3));

			printf("\n");
	}

/***********************************************************************************************************************/

// function:

	void concord_function_test()
	{
		constexpr auto function_test_0 = concord_test_vm_function<unsigned long>{};

		// glyph:

			print_array(function_test_0.function_cglyph(function_test_0.unary_icon));
			print_array(function_test_0.function_cglyph(function_test_0.binary_icon));

			printf("\n");

		// image:

			print_array(function_test_0.function_cimage(function_test_0.square_sign));
			print_array(function_test_0.function_cimage(function_test_0.sum_of_sq_sign));
			print_array(function_test_0.function_cimage(function_test_0.factorial_sign));
			print_array(function_test_0.function_cimage(function_test_0.fibonacci_sign));

			printf("\n");
	}

/***********************************************************************************************************************/

// list:

	void concord_list_test()
	{
		constexpr auto list_test_0 = concord_test_list<unsigned long>{};

		// glyph:

			print_array(list_test_0.ring_cglyph(list_test_0.list_icon));

			printf("\n");

		// image:

			print_array(list_test_0.ring_cimage(list_test_0.list_sign));

			printf("\n");

		// value:

			auto ring_cmethod = list_test_0.ring_cmethod();
			auto list_cmethod = list_test_0.list_cmethod();
			auto l_sign       = list_test_0.list_sign;

			for (auto k = 0; k != 5; ++k)
			{
				auto r_sign = list_cmethod.car_sign(l_sign);
				     l_sign = list_cmethod.cdr_sign(l_sign);

				printf("%lu ", ring_cmethod.cvalue(r_sign));
			}

			printf("\n");
	}

/***********************************************************************************************************************/

// space:

	void concord_space_test()
	{
		constexpr auto space_test_0 = concord_test_space<unsigned long>{};

		// glyph:

			print_array(space_test_0.ring_cglyph(space_test_0.to_icon(space_test_0.char_mode)));
		//	print_array(space_test_0.ring_cglyph(space_test_0.string_mode));

			printf("\n");

		// image:

		//	print_array(space_test_0.ring_cimage(space_test_0.string_sign));

		//	printf("\n");

		// value:

		//	auto ring_cmethod  = space_test_0.ring_cmethod();
		//	auto space_cmethod = space_test_0.space_cmethod();
		//	auto l_sign        = space_test_0.space_sign;

		//	for (auto k = 0; k != 5; ++k)
		//	{
		//		auto r_sign = space_cmethod.car_sign(l_sign);
		//		     l_sign = space_cmethod.cdr_sign(l_sign);

		//		printf("%lu ", ring_cmethod.cvalue(r_sign));
		//	}

		//	printf("\n");
	}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

