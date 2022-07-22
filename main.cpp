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

#include<cstdio>

/***********************************************************************************************************************/

#include"define_macros.hpp"
#include"00_cctmp_grammar.hpp"
#include"01_cctmp_block.hpp"
#include"02_cctmp_machine.hpp"
#include"03_cctmp_functional.hpp"
//#include"04_cctmp_front.hpp"
#include"05_generic_assembly.hpp"
#include"06_one_cycle_generics.hpp"
//#include"07_one_cycle_specifics.hpp"
//#include"08_one_cycle_defaults.hpp"
//#include"09_domain_specifics.hpp"
//#include"10_big_numbers.hpp"
//#include"11_cryptography.hpp"
//#include"12_numerical.hpp"
//#include"13_signal_processing.hpp"
#include"undef_macros.hpp"

/***********************************************************************************************************************/

	using namespace cctmp;
//	using namespace cctmp_generics;
//	using namespace cctmp_one_cycle_specs;

//	template<auto... Vs> constexpr auto U_pack_Vs = cctmp::template U_pack_Vs<Vs...>;

/***********************************************************************************************************************/

	constexpr void print_array(int *b, const int *e)
	{
		while (b != e)
		{
			printf("%d, ", *b);
			++b;
		}

		printf("end\n");
	}

	constexpr void repeat_array(int *b, const int *e, int v)
	{
		while (b != e) *(b++) = v;
	}

/***********************************************************************************************************************/

	constexpr auto p = U_pack_Vs
	<
		16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
		16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
		16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
		16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
		16, 7, 12, 3, 1,  200, 99, 0, 5, 41,

		16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
		16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
		16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
		16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
		16, 7, 12, 3, 1,  200, 99, 0, 5, 41,

		16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
		16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
		16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
		16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
		16, 7, 12, 3, 1,  200, 99, 0, 5, 41,

		16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
		16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
		16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
		16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
		16, 7, 12, 3, 1,  200, 99, 0, 5, 41,

		99, 0, 5, 41
	>;

/***********************************************************************************************************************/

// functions:

/*
	constexpr int sq(int x)			{ return x*x; }
	constexpr auto _sq_			= cctmp::template _apply_<sq>;

	constexpr int mod_add(int x, int y)	{ return (x+y) % 10; }
	constexpr auto _mod_add_		= cctmp::template _apply_<mod_add>;

	constexpr int carry0_add_ddd(int *o, int *i1, int *i2) { return (*o < *i1); }
	constexpr int carry1_add_dii(int *o, int i, bool a) { return a || (i == 1 && *o == 0); }

	constexpr auto _carry0_add_ddd_		= cctmp::template _apply_<carry0_add_ddd>;
	constexpr auto _carry1_add_dii_		= cctmp::template _apply_<carry1_add_dii>;

	constexpr auto _id_			= cctmp::_id_;
	constexpr auto _add_			= cctmp::_add_;
	constexpr auto _is_25_			= cctmp::template _is_equal_<25>;
	constexpr auto _assign_			= cctmp::_assign_;
	constexpr auto _deref_			= cctmp::_dereference_;

	constexpr auto _add_dd_			= cctmp_generics::template _argcompose_<_add_, _deref_, _deref_>;
	constexpr auto _is_25_d_		= cctmp_generics::template _argcompose_<_is_25_, _deref_>;
	constexpr auto _mod_add_di_		= cctmp_generics::template _argcompose_<_mod_add_, _deref_, _id_>;
	constexpr auto _mod_add_dd_		= cctmp_generics::template _argcompose_<_mod_add_, _deref_, _deref_>;

	constexpr auto _d_assign_i_		= cctmp_generics::template _argcompose_<_assign_, _deref_, _id_>;
	constexpr auto _d_assign_sq_		= cctmp_generics::template _argcompose_<_assign_, _deref_, _sq_>;
	constexpr auto _d_assign_add_		= cctmp_generics::template _subcompose_
						<
							_assign_,

							U_pack_Vs < _deref_ , _add_           >,
							U_pack_Vs < 0       , U_pack_Vs<1, 2> >
						>;
	constexpr auto _d_assign_add_dd_	= cctmp_generics::template _argcompose_
						<
							_d_assign_add_, _id_, _deref_, _deref_
						>;
*/

/***********************************************************************************************************************/

// repeat:

//	constexpr auto closed			= cctmp_one_cycle_specs::_closed;
//	constexpr auto closed_type		= cctmp_one_cycle_specs::template _type_<closed>;
//	constexpr auto closed_ival		= cctmp_one_cycle_specs::template _out_ival_<closed_type>;

//	constexpr auto repeat_dspec		= cctmp_one_cycle_specs::template direct_repeat<>;
//	constexpr auto repeat_cspec		= cctmp_one_cycle_specs::template conceptual_repeat<closed_ival>;

//	using Td_repeat				= typename cctmp_one_cycle_generics::template T_repeat<repeat_dspec>;
//	using Tc_repeat				= typename cctmp_one_cycle_generics::template T_repeat<repeat_cspec>;

// map:

//	constexpr auto _map_function_sq_	= cctmp_one_cycle_specs::template _assign_function_<_d_assign_sq_>;

//	constexpr auto map_dspec_id_		= cctmp_one_cycle_specs::template direct_map<>;
//	constexpr auto map_dspec_sq_		= cctmp_one_cycle_specs::template direct_map<_map_function_sq_>;
//	constexpr auto map_cspec_id_		= cctmp_one_cycle_specs::template conceptual_map<>;
//	constexpr auto map_cspec_sq_		= cctmp_one_cycle_specs::template conceptual_map<_map_function_sq_>;

//	using Td_map_id				= typename cctmp_one_cycle_generics::template T_map<map_dspec_id_>;
//	using Td_map_sq				= typename cctmp_one_cycle_generics::template T_map<map_dspec_sq_>;
//	using Tc_map_id				= typename cctmp_one_cycle_generics::template T_map<map_cspec_id_>;
//	using Tc_map_sq				= typename cctmp_one_cycle_generics::template T_map<map_cspec_sq_>;

// fold:

//	constexpr auto _fold_function_add_	= cctmp_one_cycle_specs::template _combine_function_<_add_>;

//	constexpr auto fold_dspec_add_		= cctmp_one_cycle_specs::template direct_fold<_fold_function_add_>;
//	constexpr auto fold_cspec_add_		= cctmp_one_cycle_specs::template conceptual_fold<_fold_function_add_>;

//	using Td_fold_add			= typename cctmp_one_cycle_generics::template T_fold<fold_dspec_add_>;
//	using Tc_fold_add			= typename cctmp_one_cycle_generics::template T_fold<fold_cspec_add_>;

// find first:

//	constexpr auto _find_first_pred_is_25_	= cctmp_one_cycle_specs::template _act_predicate_<_is_25_d_>;

//	constexpr auto find_first_dspec_is_25_	= cctmp_one_cycle_specs::template direct_find_first<_find_first_pred_is_25_>;
//	constexpr auto find_first_cspec_is_25_	= cctmp_one_cycle_specs::template conceptual_find_first<_find_first_pred_is_25_>;

//	using Td_find_first_is_25		= typename cctmp_one_cycle_generics::template T_find_first<find_first_dspec_is_25_>;
//	using Tc_find_first_is_25		= typename cctmp_one_cycle_generics::template T_find_first<find_first_cspec_is_25_>;

// find all:

//	constexpr auto find_all_dspec_is_25_	= cctmp_one_cycle_specs::template direct_find_all<_find_first_pred_is_25_>;
//	constexpr auto find_all_cspec_is_25_	= cctmp_one_cycle_specs::template conceptual_find_all<_find_first_pred_is_25_>;

//	using Td_find_all_is_25			= typename cctmp_one_cycle_generics::template T_find_all<find_all_dspec_is_25_>;
//	using Tc_find_all_is_25			= typename cctmp_one_cycle_generics::template T_find_all<find_all_cspec_is_25_>;

// zip:

//	constexpr auto _zip_function_add_	= cctmp_one_cycle_specs::template _act_function_<_add_dd_>;
//	constexpr auto _zip_assign_		= cctmp_one_cycle_specs::template _assign_function_<_d_assign_i_>;

//	constexpr auto zip_dspec_add_		= cctmp_one_cycle_specs::template direct_zip
//						<
//							_zip_function_add_, _zip_assign_
//						>;
//	constexpr auto zip_cspec_add_		= cctmp_one_cycle_specs::template conceptual_zip
//						<
//							_zip_function_add_, _zip_assign_
//						>;

//	using Td_zip_add			= typename cctmp_one_cycle_generics::template T_zip<zip_dspec_add_>;
//	using Tc_zip_add			= typename cctmp_one_cycle_generics::template T_zip<zip_cspec_add_>;

// fasten:

//	constexpr auto _fasten_function_add_	= cctmp_one_cycle_specs::template _act_function_<_mod_add_dd_>;
//	constexpr auto _fasten_combine_add_	= cctmp_one_cycle_specs::template _combine_function_<_mod_add_di_>;
//	constexpr auto _fasten_aux_next_	= cctmp_one_cycle_specs::template _aux_next_<_carry0_add_ddd_>;
//	constexpr auto _fasten_in_next_		= cctmp_one_cycle_specs::template _in_next_<_carry1_add_dii_>;

//	constexpr auto fasten_dspec_add_	= cctmp_one_cycle_specs::template direct_fasten
//						<
//							_fasten_function_add_, _fasten_combine_add_,
//							_fasten_aux_next_, _fasten_in_next_
//						>;
//	constexpr auto fasten_cspec_add_	= cctmp_one_cycle_specs::template conceptual_fasten
//						<
//							_fasten_function_add_, _fasten_combine_add_,
//							_fasten_aux_next_, _fasten_in_next_
//						>;

//	using Td_fasten_mod_add			= typename cctmp_one_cycle_generics::template T_fasten<fasten_dspec_add_>;
//	using Tc_fasten_mod_add			= typename cctmp_one_cycle_generics::template T_fasten<fasten_cspec_add_>;

// glide:

//	constexpr auto _glide_function_add_	= cctmp_one_cycle_specs::template _act_function_<_add_dd_>;
//	constexpr auto _glide_combine_add_	= cctmp_one_cycle_specs::template _combine_function_<_add_>;

//	constexpr auto glide_dspec_add_		= cctmp_one_cycle_specs::template direct_glide
//						<
//							_glide_function_add_, _glide_combine_add_
//						>;
//	constexpr auto glide_cspec_add_		= cctmp_one_cycle_specs::template conceptual_glide
//						<
//							_glide_function_add_, _glide_combine_add_
//						>;

//	using Td_glide_add			= typename cctmp_one_cycle_generics::template T_glide<glide_dspec_add_>;
//	using Tc_glide_add			= typename cctmp_one_cycle_generics::template T_glide<glide_cspec_add_>;

/***********************************************************************************************************************/

	int main(int argc, char *argv[])
	{
	//	int size = 10;//argc;

	//	int  arr[size];
	//	int  arr_id[size];
	//	int  arr_sq[size];
	//	int* arr_ptr[size];

// repeat:

	//	printf("%d\n", cctmp_functional::list_at<repeat_cspec, 0>);
	//	repeat_array(arr, arr+size, argc);

	//	Td_repeat::result(arr, arr+size, argc);
	//	print_array(arr, arr+size);

	//	Tc_repeat::result(arr, arr+size, argc);
	//	print_array(arr, arr+size);

// map:

	//	Td_map_id::template result(arr_id, 0, size);
	//	print_array(arr_id, arr_id+size);

	//	Td_map_sq::template result(arr_sq, 0, size);
	//	print_array(arr_sq, arr_sq+size);

// fold:

	//	auto val = T_fold_add::template result(0, 0, size);
	//	printf("%d\n", val);

// find first:

	//	T_map_sq::template result(arr_sq, 0, size);

	//	auto val = T_find_first_is_25::template result(arr_ptr, arr_sq, arr_sq+size);
	//	printf("%ld\n", val - arr_ptr);
	//	printf("%ld\n", *arr_ptr - arr_sq);

// find all:

	//	T_map_sq::template result(arr_sq, 0, size);
	//	arr_sq[3] = 25;
	//	arr_sq[8] = 25;

	//	auto val = T_find_all_is_25::template result(arr_ptr, arr_sq, arr_sq+size);
	//	printf("%ld\n", val - arr_ptr);
	//	printf("%ld\n", arr_ptr[0] - arr_sq);
	//	printf("%ld\n", arr_ptr[1] - arr_sq);
	//	printf("%ld\n", arr_ptr[2] - arr_sq);

// zip:

	//	T_map_id::template result(arr_id, 0, size);
	//	T_map_sq::template result(arr_sq, 0, size);

	//	T_zip_add::template result(arr, arr_id, arr_sq, arr_sq+size);
	//	print_array(arr, arr+size);

// fasten:

	//	int mod_size = 3;
	//	int arr_mod_add[mod_size];
	//	int arr_134[] = { 4, 3, 1 };
	//	int arr_379[] = { 9, 7, 3 };

	//	T_fasten_mod_add::template result(arr_mod_add, 0, 0, arr_134, arr_379, arr_379+mod_size);
	//	printf("%d%d%d\n", arr_mod_add[2], arr_mod_add[1], arr_mod_add[0]);

// glide:

	//	T_map_id::template result(arr_id, 0, size);
	//	T_map_sq::template result(arr_sq, 0, size);

	//	auto val = T_glide_add::template result(0, arr_id, arr_sq, arr_sq+size);
	//	printf("%d\n", val);

		return 0;
	}

