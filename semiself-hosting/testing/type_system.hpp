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

// type system:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// experimental:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// table:

		auto a10 = arr_type{a};

		using submethod1 = resolve_submethod<arr_type, table_submethod>;

		auto m11 = a10.template subequip<submethod1>();

		m11.mid_set(1, 5);
	//	m11.left_set(4);
	//	m11.right_shift(1);
		m11.set_sizes(2, 2);

		printf("%d " , m11[0][0]);
		printf("%d\n", m11[0][1]);
		printf("%d " , m11[1][0]);
		printf("%d\n", m11[1][1]);

/***********************************************************************************************************************/

// plot:

	constexpr auto make_plot()
	{
		using size_type = unsigned long;
		using plot_type = plot<size_type, size_type, 5, 7, 3, 5>;
		using method0   = resolve_method<plot_type, array_method>;

		auto rtn_plot   = plot_type{};
		auto subarr0    = rtn_plot.template equip<method0>(0);

		subarr0.fullsize();
		subarr0[0] = 5;
		subarr0[1] = 7;
		subarr0[2] = 2;
		subarr0[3] = 3;
		subarr0[4] = 4;

		return rtn_plot;
	}

	constexpr auto plot0 = make_plot();

	// main:

		using cmethod0 = resolve_cmethod<decltype(plot0), print_cmethod>;

		auto print0 = plot0.template cequip<cmethod0>(0);

		print0.as_set(); // prints: { 0, 5, 12, 15, 20 }

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// logo cstart:

	// main:

		using cmethod0 = resolve_cmethod<decltype(start0), print_cmethod>;

		auto print0 = start0.template cequip<cmethod0>();

		print0.as_set(); // prints: { 0, 5, 12, 15, 20 }

