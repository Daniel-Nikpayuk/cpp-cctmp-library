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
//#include"06_generic_optimizers.hpp"
#include"07_one_cycle_assembly.hpp"
#include"08_one_cycle_specifics.hpp"
#include"09_one_cycle_accords.hpp"
#include"10_one_cycle_generics.hpp"
//#include"11_domain_specifics.hpp"
#include"12_byte_ring.hpp"
//#include"13_byte_array_ring.hpp"
//#include"14_cryptography.hpp"
//#include"15_linear_algebra.hpp"
//#include"16_signal_processing.hpp"
#include"undef_macros.hpp"

/***********************************************************************************************************************/

	template<auto V> using unsigned_limit	= cctmp_byte_ring::template unsigned_limit<V>;
	template<auto V> using   signed_limit	= cctmp_byte_ring::template   signed_limit<V>;

	using ring_policy	= typename cctmp_byte_ring::Policy;

	using ring_type		= cctmp_byte_ring::template make_ring<8, ring_policy::bit_size>;
//	using prev_type		= typename ring_type::prev_type;

/***********************************************************************************************************************/

//	using uchar_limit = unsigned_limit<cctmp::U_unsigned_char>;
//	using schar_limit = signed_limit<uchar_limit::U_signed_type>;

	int main(int argc, char *argv[])
	{
	//	printf("%d\n", ring_type::U_unsigned_type);

	//	printf("%llu\n", uchar_limit::minimum);
	//	printf("%llu\n", uchar_limit::maximum);

	//	printf("%lli\n", schar_limit::minimum);
	//	printf("%lli\n", schar_limit::maximum);

		ring_type x{1};
		ring_type y{2};
		ring_type z = x - y;

		printf("%hhu\n", z.to_builtin());

		return 0;
	}

