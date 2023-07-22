/************************************************************************************************************************
**
** Copyright 2022-2023 Daniel Nikpayuk, Inuit Nunangat, The Inuit Nation
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

// progression grammar tests:

namespace chord {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// printers:

	template<auto Size>
	void print_array(const int (&arr)[Size])
	{
		printf(" ");
		for (auto k = arr; k != arr + Size; ++k) printf("%d ", *k);
		printf("\n");
	}

	template<typename Begin, typename In, typename End>
	void print_sifted(Begin begin, In in, End end)
	{
		printf(" ");
		while (in != end)
		{
			int pos = *in - begin;
			int val = **in;
			printf("(pos: %d, val: %d) ", pos, val);
			++in;
		}
		printf("\n");
	}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// progressions:

/***********************************************************************************************************************/

// repeat:

	void repeat_tests()
	{
		int arr0[] = { 1, 2, 3, 4, 5, 0 };
		int arr1[] = { 5, 4, 3, 2, 1, 0 };

		repeat_v0(arr0, arr0 + 5, arr1 + 5);
		print_array(arr0);
	}

/***********************************************************************************************************************/

// fold:

	void fold_tests()
	{
		int arr0[] = { 1, 2, 3, 4, 5, 0 };

		printf("%d\n", (int) fold_v0(0, arr0, arr0 + 5)); // prints: 15
	}

/***********************************************************************************************************************/

// find:

	void find_tests()
	{
		int arr2[] = { 7, 4, 6, 2, 9, 0 };

		int* found[1];
		auto found_end = find_v0(found, arr2, arr2 + 5);
		print_sifted(arr2, found, found_end);
	}

/***********************************************************************************************************************/

// sift:

	void sift_tests()
	{
		int arr2[] = { 7, 4, 6, 2, 9, 0 };

		int* sifted[6];
		auto sifted_end = sift_v0(sifted, arr2, arr2 + 5);
		print_sifted(arr2, sifted, sifted_end);
	}

/***********************************************************************************************************************/

// map:

	void map_tests()
	{
		int arr0[] = { 1, 2, 3, 4, 5, 0 };
		int arr1[] = { 5, 4, 3, 2, 1, 0 };

		map_v0(arr1, arr0, arr0 + 5);
		print_array(arr1);
	}

/***********************************************************************************************************************/

// zip:

	void zip_tests()
	{
		int arr0[] = { 1, 2, 3, 4, 5, 0 };
		int arr1[] = { 5, 4, 3, 2, 1, 0 };

		vec_sum_v0(arr0, arr0, arr1, arr1 + 5);
		print_array(arr0);
	}

/***********************************************************************************************************************/

// glide:

	void glide_tests()
	{
		int arr0[] = { 1, 2, 3, 4, 5, 0 };
		int arr1[] = { 5, 4, 3, 2, 1, 0 };

		printf("%d\n", (int) dot_product_v0(0, arr0, arr1, arr1 + 5)); // prints: 35
		printf("%d\n", (int) convolution_v0(0, arr0, arr1, arr1 + 5)); // prints: 55
	}

/***********************************************************************************************************************/

// fasten:

	void fasten_tests()
	{
		int arr0[] = { 1, 2, 3, 4, 5, 0 };
		int arr1[] = { 5, 4, 3, 2, 1, 0 };
		int arr2[] = { 7, 4, 6, 2, 9, 0 };

		array_add_v0(arr0, 0, arr1, arr2, arr2 + 5);	//  12345
		print_array(arr0);				// +92647
								// ------
								// 104992
								// 299401
	}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// progressions:

/***********************************************************************************************************************/

// change of base:

	void change_of_base_tests()
	{
		int arr[100];

		change_of_base_printer_v0<2>("%d ", arr, 10); // prints: 1 0 1 0
	}

/***********************************************************************************************************************/

// array printer:

	void array_printer_tests()
	{
		int arr[100];

		array_printer_v0("%d ", arr, arr + 10); // prints: 0 0 0 0 0 0 0 0 0 0
	}

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace chord

