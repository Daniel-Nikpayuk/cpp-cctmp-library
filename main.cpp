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
#include"0_cctmp_backend_0.hpp"
#include"0_cctmp_backend_1.hpp"
#include"1_cctmp_functional.hpp"
//#include"2_cctmp_frontend.hpp"
//#include"3_generic_assembly.hpp"
//#include"4_one_cycle_generics_0.hpp"
//#include"4_one_cycle_generics_1.hpp"
//#include"5_domain_specific_grammars.hpp"
//#include"6_big_numbers_0.hpp"
//#include"6_big_numbers_1.hpp"
//#include"7_numerical_analysis_0.hpp"
//#include"7_numerical_analysis_1.hpp"
#include"undef_macros.hpp"

/***********************************************************************************************************************/

	using namespace cctmp;

/***********************************************************************************************************************/

/*
	using Overload = cctmp::Overload;

	template<auto... Vs>
	constexpr auto call = Overload::template result<Vs...>;

	constexpr auto p = cctmp::U_pack_Vs
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

	constexpr auto U_int	= cctmp::U_store_T<int>;
	constexpr auto U_char	= cctmp::U_store_T<char>;
*/

/***********************************************************************************************************************/

/*
	template<key_type ctn = _h1, depth_type dec = _two>
	nik_ce instr_type compel = instruction<MN::call, MT::compel, dec, ctn>;

	struct Compel
	{
		nik_ces auto m		= MT::id;
		nik_ces auto i		= MachineDispatch::initial_index;
		nik_ces auto ctn	= MI::value;

		template<auto d, auto h0, auto dec = _three, auto c = controller<compel<ctn, dec>>>
		nik_ces auto result = NIK_BEGIN_MACHINE(d, m, c, i) NIK_END_MACHINE(h0, U_null_Vs, U_null_Vs);
	};

	struct T_Segment_v0
	{
		template<auto d, auto n, auto m>
		nik_ces auto result = NIK_BEGIN_BLOCK(9, segment, d, n), m NIK_END_BLOCK;
	};

	constexpr auto U_Segment_v0 = U_store_T<T_Segment_v0>;

	struct Segment_v0
	{
		template<auto d, auto n, auto m>
		nik_ces auto result = Compel::template result<d, U_pack_Vs<U_Segment_v0, n, m>>;
	};

	template<auto n, auto m = index_type{0}, auto d = MachineDispatch::initial_depth>
	constexpr auto segment_v0 = Segment_v0::template result<d, n, m>;
*/

/***********************************************************************************************************************/

	int main(int argc, char *argv[])
	{
	//	printf("%s\n", call<Overload::same, U_char, U_char> ? "true" : "false");
	//	printf("%llu\n", call<Overload::map, cctmp::template increment_op<>, p>);
	//	printf("%hu\n", call<Overload::find, cctmp::template is_zero_op<>, p>);

	//	printf("%d\n", cctmp_program::at_v0<0, p>);
	//	printf("%llu\n", cctmp_program::left_v0<2, p>);
	//	printf("%llu\n", cctmp_program::split_v0<2, p>);
	//	printf("%llu\n", cctmp_program::segment_v0<uint_type{10}>);

	//	printf("%llu\n", cctmp_program::erase_v0<0, p>);
	//	printf("%llu\n", cctmp_program::insert_v0<7, 4, p>);
	//	printf("%llu\n", cctmp_program::replace_v0<7, 1, p>);

	//	printf("%llu\n", cctmp_program::fold_v0<cctmp::template add_op<>, uint_type{0}, p>);

	//	printf("%llu\n", cctmp_program::insert_sort_v0<p, 3>);
	//	printf("%llu\n", cctmp_program::sort_v0<p>);
	//	printf("%llu\n", cctmp_program::sort_v1<p>);
	//	printf("%llu\n", cctmp_program::sort_v2<p>);	// gcc 1.717s / clang 4.199s
								// gcc 1.344s / clang 3.568s

	//	printf("%llu\n", cctmp_program::factorial_v0<uint_type{20}>);
	//	printf("%llu\n", cctmp_program::factorial_v1<uint_type{20}>);

	//	printf("%llu\n", cctmp_program::fibonacci_v0<uint_type{43}>);	// gcc 1.767s / clang 5.641s
	//	printf("%llu\n", cctmp_program::fibonacci_v1<uint_type{43}>);	// gcc 0.599s / clang 1.300s

	//	printf("%llu\n", cctmp_program::fibonacci_v0<uint_type{70}>);	// gcc > 10m / clang ~ who knows (4x 10m)
	//	printf("%llu\n", cctmp_program::fibonacci_v1<uint_type{92}>);	// gcc 1.462s / clang 3.492s

		return 0;
	}

