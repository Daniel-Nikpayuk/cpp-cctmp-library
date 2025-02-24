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
#include"include/01_automata.hpp"

#include"undef_macros.hpp"

#include"testing/printer.hpp"

/***********************************************************************************************************************/
/***********************************************************************************************************************/

	using namespace cctmp;

/***********************************************************************************************************************/

// square:

	template<typename MI, typename MP, typename SizeType>
	struct square_concord
	{
		using size_type         = SizeType;
		using glyph_pack        = cctmp::T_pack_Vs<100, 1, 0, 0, 1>;
		using space_pack        = cctmp::T_pack_Vs<  0, 0, 0, 0, 0>;
		using image_pack        = cctmp::T_pack_Vs< 10, 1, 0, 0, 1>;
		using concord_type      = concord<size_type, size_type, glyph_pack, space_pack, image_pack, 100>;
		using sign_type         = sign<size_type>;

		using ring_method_type  = resolve_method<concord_type, concord_ring_method>;
		using func_method_type  = resolve_method<concord_type, concord_function_method>;
		using eval_cmethod_type = resolve_eval_cmethod<concord_type, 10, 10, 10>;

		constexpr static size_type contr[32] =
		{
			MI::program         , 6 ,            0 , 2 ,	// line 0: action,  lines, atomic,   next
			MI::define_argument , 0 ,            0 , 1 ,	// line 1: action,  index,  start, finish
			MI::function        , 6 , MP::to_stack , 1 ,	// line 2: action, inline, policy,   next
			MI::argument        , 1 , MP::to_stack , 1 ,	// line 3: action, inline, policy,   next
			MI::argument        , 1 , MP::to_stack , 1 ,	// line 4: action, inline, policy,   next
			MI::apply           , 0 , MP::to_carry , 0 ,	// line 5: action, offset, policy,   next
		// multiply:
			MI::program         , 2 ,            1 , 1 ,	// line 6: action,  lines, atomic,   next
			MI::multiply        , 0 , MP::to_carry , 0	// line 7: action, offset, policy,   next
		};

		concord_type value;
		sign_type square;

		constexpr square_concord()
		{
			auto ring_method       = value.template equip<ring_method_type>();
			auto func_method       = value.template equip<func_method_type>();

			auto ring8_t           = ring_method.declare_type(8);
			auto ring8_to_ring8_f  = func_method.declare_type({ ring8_t, ring8_t });

			square                 = func_method.define_abstract(ring8_to_ring8_f, contr);
		}

		constexpr auto eval_cmethod() const { return value.template cequip<eval_cmethod_type>(); }
	};

	// test:

		template<typename size_type>
		constexpr auto square(size_type const v)
		{
			constexpr auto concord = square_concord<MachineInstr, MachinePolicy, size_type>{};
			auto eval_cmethod      = concord.eval_cmethod();
			eval_cmethod           . apply(concord.square, {v});

			return eval_cmethod.rtn_cat(0);
		}

/***********************************************************************************************************************/

	int main(int argc, char *argv[])
	{
	//	static_assert(square<unsigned long>(5) == 25);

	//	printf("%lu\n", square<unsigned long>(5));

		return 0;
	}

