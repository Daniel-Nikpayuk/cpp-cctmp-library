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

#include<cstdio>
//#include<cstdlib>

/***********************************************************************************************************************/

#include"define_macros.hpp"

#include"include/00_kernel.hpp"

#include"undef_macros.hpp"

#include"testing/printer.hpp"

/***********************************************************************************************************************/
/***********************************************************************************************************************/

	using namespace cctmp;

/***********************************************************************************************************************/

	constexpr auto corpus_add_test()
	{
		using size_type    = unsigned long;
		using sym_pack     = cctmp::T_pack_Vs<6, 3>;
		using img_pack     = cctmp::T_pack_Vs<6, 3>;
		using corpus_type  = corpus<unsigned, size_type, sym_pack, img_pack, 3>;
		using method_type  = resolve_method<corpus_type, cring_method>;

		auto corpus_value  = corpus_type{};
		auto corpus_method = corpus_value.template equip<method_type>();
		auto out_sign      = corpus_method.declare (64);
		auto in1_sign      = corpus_method.define  (64, 2);
		auto in2_sign      = corpus_method.define  (64, 3);

		corpus_method.add_to(out_sign, in1_sign, in2_sign);

		return corpus_value;
	}

	constexpr auto corpus0 = corpus_add_test();

/***********************************************************************************************************************/

	int main(int argc, char *argv[])
	{
		print_array(*corpus0.crecord()->csignifier()->ctext());
		print_array(*corpus0.crecord()->csignified()->ctext());
		print_array(*corpus0.cmemory());

		return 0;
	}

