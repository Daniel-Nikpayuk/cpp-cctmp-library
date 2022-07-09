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
#include"07_one_cycle_specifics.hpp"
//#include"08_domain_specifics.hpp"
//#include"09_big_numbers.hpp"
//#include"10_cryptography.hpp"
//#include"11_numerical.hpp"
//#include"12_signal_processing.hpp"
#include"undef_macros.hpp"

/***********************************************************************************************************************/

//	using namespace cctmp;
//	using namespace cctmp_generics;
//	using namespace cctmp_one_cycle_specs;

	template<auto... Vs> constexpr auto U_pack_Vs = cctmp::template U_pack_Vs<Vs...>;

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

/*
	constexpr auto p = U_pack_Vs
	<
	//	16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
	//	16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
	//	16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
	//	16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
	//	16, 7, 12, 3, 1,  200, 99, 0, 5, 41,

	//	16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
	//	16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
	//	16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
	//	16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
	//	16, 7, 12, 3, 1,  200, 99, 0, 5, 41,

	//	16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
	//	16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
	//	16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
	//	16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
	//	16, 7, 12, 3, 1,  200, 99, 0, 5, 41,

	//	16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
	//	16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
	//	16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
	//	16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
	//	16, 7, 12, 3, 1,  200, 99, 0, 5, 41,

		99, 0, 5, 41
	>;
*/

/***********************************************************************************************************************/

// repeat:

//	constexpr auto repeat_d_spec		= cctmp_one_cycle_specs::template direct_repeat<>;
//	using T_repeat				= typename cctmp_one_cycle_generics::template T_repeat<repeat_d_spec>;

// map:

	constexpr int sq(int x)			{ return x*x; }
	constexpr auto _sq_			= cctmp::template _apply_<sq>;

	constexpr auto _id_			= cctmp::_id_;
	constexpr auto _add_			= cctmp::_add_;
	constexpr auto _assign_			= cctmp::_assign_;
	constexpr auto _deref_			= cctmp::_dereference_;

	constexpr auto _side_assign_d_i_	= cctmp_generics::template _side_assign_<_deref_, _id_>;
	constexpr auto _map_function_id_	= cctmp_one_cycle_specs::template _act_function_<_side_assign_d_i_>;
	constexpr auto map_d_spec_id_		= cctmp_one_cycle_specs::template direct_map<_map_function_id_>;
	using T_map_id				= typename cctmp_one_cycle_generics::template T_map<map_d_spec_id_>;

	constexpr auto _side_assign_d_sq_	= cctmp_generics::template _side_assign_<_deref_, _sq_>;
	constexpr auto _map_function_sq_	= cctmp_one_cycle_specs::template _act_function_<_side_assign_d_sq_>;
	constexpr auto map_d_spec_sq_		= cctmp_one_cycle_specs::template direct_map<_map_function_sq_>;
	using T_map_sq				= typename cctmp_one_cycle_generics::template T_map<map_d_spec_sq_>;

// fold:

	constexpr auto _fold_function_add_	= cctmp_one_cycle_specs::template _combine_function_<_add_>;

	constexpr auto fold_d_spec_add_		= cctmp_one_cycle_specs::template direct_fold<_fold_function_add_>;
	using T_fold_add			= typename cctmp_one_cycle_generics::template T_fold<fold_d_spec_add_>;

// zip:

	constexpr auto _add_dd_			= cctmp_generics::template _subcompose_
						<
							_add_,

							U_pack_Vs < _deref_ , _deref_ >,
							U_pack_Vs < 0       , 1       >
						>;
	constexpr auto _assign_d_add_dd_	= cctmp_generics::template _subcompose_
						<
							_assign_,

							U_pack_Vs < _deref_ , _add_dd_         >,
							U_pack_Vs < 0       , U_pack_Vs<1, 2>  >
						>;
	constexpr auto _side_assign_d_add_dd_	= cctmp_generics::template _side_<_assign_d_add_dd_>;
	constexpr auto _zip_function_add_	= cctmp_one_cycle_specs::template _act_function_<_side_assign_d_add_dd_>;
	constexpr auto zip_d_spec_add_		= cctmp_one_cycle_specs::template direct_zip<_zip_function_add_>;
	using T_zip_add				= typename cctmp_one_cycle_generics::template T_zip<zip_d_spec_add_>;

// glide:

	constexpr auto _glide_function_add_	= cctmp_one_cycle_specs::template _act_function_<_add_dd_>;
	constexpr auto glide_d_spec_add_	= cctmp_one_cycle_specs::template direct_glide
						<
							_glide_function_add_, _fold_function_add_
						>;
	using T_glide_add			= typename cctmp_one_cycle_generics::template T_glide<glide_d_spec_add_>;

/***********************************************************************************************************************/

	int main(int argc, char *argv[])
	{
	//	printf("%s\n", call<Overload::same, U_char, U_char> ? "true" : "false");
	//	printf("%llu\n", call<Overload::map, cctmp::template increment_op<>, p>);
	//	printf("%hu\n", call<Overload::find, cctmp::template is_zero_op<>, p>);

	//	printf("%d\n",   cctmp_functional::pack_at<0, 3, 4, 5, 9>);
	//	printf("%d\n",   cctmp_functional::list_at<p, 0>);
	//	printf("%llu\n", cctmp_functional::pack_left<0, 3, 4, 5, 9>);
	//	printf("%llu\n", cctmp_functional::list_left<p, 0>);
	//	printf("%llu\n", cctmp_functional::pack_right<0, 3, 4, 5, 9>);
	//	printf("%llu\n", cctmp_functional::list_right<p, 0>);

	//	constexpr auto p_cut = cctmp_functional::pack_cut<0, 3, 4, 5, 9>;
	//	printf("%llu, %llu\n", tuple_value<0>(p_cut), tuple_value<1>(p_cut));
	//	constexpr auto l_cut = cctmp_functional::list_cut<p, 3>;
	//	printf("%llu, %llu\n", tuple_value<0>(l_cut), tuple_value<1>(l_cut));

	//	constexpr auto p_split = cctmp_functional::pack_split<0, 3, 4, 5, 9>;
	//	printf("%llu, %llu\n", tuple_value<0>(p_split), tuple_value<1>(p_split));
	//	constexpr auto l_split = cctmp_functional::list_split<p, 4>;
	//	printf("%llu, %llu\n", tuple_value<0>(l_split), tuple_value<1>(l_split));

	//	printf("%llu\n", cctmp_functional::segment<unsigned{10}>);

	//	printf("%d\n", cctmp_functional::pack_fold<_add_, 0, 3, 4, 5, 9>);
	//	printf("%d\n", cctmp_functional::list_fold<p, _add_, 0>);

	//	printf("%llu\n", cctmp_functional::pack_erase<0, 3, 4, 5, 9>);
	//	printf("%llu\n", cctmp_functional::list_erase<p, 0>);
	//	printf("%llu\n", cctmp_functional::pack_insert<0, 7,    3, 4, 5, 9>);
	//	printf("%llu\n", cctmp_functional::list_insert<p, 0, 7>);
	//	printf("%llu\n", cctmp_functional::pack_replace<1, 7,    3, 4, 5, 9>);
	//	printf("%llu\n", cctmp_functional::list_replace<p, 1, 7>);

	//	constexpr auto H_curry_equal		= H_curry<_equal_>;
	//	constexpr auto H_curry_less_than	= H_curry<_less_than_>;

	//	printf("%llu\n", cctmp_functional::pack_insert_sort<H_curry_less_than, 0,    3, 4, 5, 9>);
	//	printf("%llu\n", cctmp_functional::list_insert_sort<p, 0>);

	//	printf("%llu\n", cctmp_functional::pack_sort<H_curry_less_than, U_null_Vs, 3, 4, 5, 9>);
	//	printf("%llu\n", cctmp_functional::list_sort<p>);		// gcc 2.489s / clang 7.010s

	//	printf("%llu\n", cctmp_functional::pack_union<H_curry_equal, H_curry_less_than, U_null_Vs, 9,    3, 4, 5, 9>);

	//	constexpr auto def_specs	= U_pack_Vs<0, 1, 2, 3, 4, 5>;
	//	constexpr auto specs0		= U_pack_Vs<3, 5, 0>;
	//	printf("%llu\n", cctmp_functional::list_fill<def_specs, specs0>);

	//	constexpr auto p0  = cctmp_one_cycle_specs::direct_repeat_defaults;
	//	constexpr auto cmp = H_partial<U_custom, cctmp_one_cycle_specs::U_tag_compare, MD::initial_depth, _less_than_>;
	//	constexpr auto p  = cctmp_functional::list_sort<p0, cmp>;
	//	printf("%llu\n", p);

	//	constexpr auto tag0 = _pre_out_next_<_id_>;
	//	constexpr auto tag1 = _post_out_next_<_id_>;
	//	printf("%s\n", tag_compare<cctmp::_less_than_, tag1, tag0> ? "true" : "false");

		int size = argc;

		int arr[size];
		int arr_id[size];
		int arr_sq[size];

// repeat:

	//	repeat_array(arr, arr+size, argc);
	//	T_repeat::result(arr, arr+size, argc);
	//	print_array(arr, arr+size);

// map:

	//	T_map_id::template result(arr_id, 0, size);
	//	print_array(arr_id, arr_id+size);

	//	T_map_sq::template result(arr_sq, 0, size);
	//	print_array(arr_sq, arr_sq+size);

// fold:

	//	auto val = T_fold_add::template result(0, 0, size);
	//	printf("%d\n", val);

// zip:

	//	T_map_id::template result(arr_id, 0, size);
	//	T_map_sq::template result(arr_sq, 0, size);

	//	T_zip_add::template result(arr, arr_id, arr_sq, arr_sq+size);
	//	print_array(arr, arr+size);

// glide:

		T_map_id::template result(arr_id, 0, size);
		T_map_sq::template result(arr_sq, 0, size);

		auto val = T_glide_add::template result(0, arr_id, arr_sq, arr_sq+size);
		printf("%d\n", val);

		return 0;
	}

