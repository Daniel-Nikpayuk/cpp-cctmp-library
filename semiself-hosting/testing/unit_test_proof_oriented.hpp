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

// proof oriented:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// tuple:

	void proof_oriented_test(int argc, char *argv[])
	{
		using tuple_type = tuple<int, float, char>;

		tuple_type tuple{main_at(0, argc, argv), 2.718, 'e'};

		printf("%d\n", tuple.at<0>());
		printf("%f\n", tuple.at<1>());
		printf("%c\n", tuple.at<2>());

		printf("\n");

		printf("%d\n", tuple.at_squared<0>());
		printf("%f\n", tuple.at_squared<1>());
		printf("%c\n", tuple.at_squared<2>());
	}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

