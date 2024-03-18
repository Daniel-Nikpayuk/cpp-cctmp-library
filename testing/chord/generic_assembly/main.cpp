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
#include<cstdlib>

#define NIK_PARSER_GENERATOR_PARSER_OBJ "../object/00_parser_generator_parser.hpp"
#define NIK_CHORD_PARSER_OBJ            "../object/01_chord_parser.hpp"

#define NIK_PARSER_GENERATOR_PARSER // bug: currently all need to be on or all off.
#define NIK_CHORD_PARSER

/***********************************************************************************************************************/

#include"../../../define_macros.hpp"

#include"../../../include/00_cctmp.h"
#include"../../../include/01_assembly.h"
#include"../../../include/02_generator.h"
#include"../../../include/03_chord.h"

#include"../../../undef_macros.hpp"

/***********************************************************************************************************************/
/***********************************************************************************************************************/

	using namespace cctmp;

/***********************************************************************************************************************/

	constexpr char string_copyright[] =

		"/***********************************************************"
		"************************************************************\n"
		"**\n"
		"** Copyright 2022-2024 Daniel Nikpayuk, Inuit Nunangat, The Inuit Nation\n"
		"**\n"
		"** This file is part of cpp_cctmp_library.\n"
		"**\n"
		"** cpp_cctmp_library is free software: you can redistribute it and/or modify it under the terms\n"
		"** of the GNU General Public License as published by the Free Software Foundation, either version 3\n"
		"** of the License, or (at your option) any later version.\n"
		"**\n"
		"** cpp_cctmp_library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;\n"
		"** without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n"
		"** See the GNU General Public License for more details.\n"
		"**\n"
		"** You should have received a copy of the GNU General Public License along with cpp_cctmp_library.\n"
		"** If not, see <http://www.gnu.org/licenses/>.\n"
		"**\n"
		"************************************************************"
		"***********************************************************/\n\n"
	;

/***********************************************************************************************************************/

	constexpr char string_def_begin[] =

		"\ttemplate<typename SizeType>\n"
		"\tstruct T_chord_square_v0\n"
		"\t{\n"
		"\t\tusing size_type = SizeType;\n"
		"\n"
	;

/***********************************************************************************************************************/

	constexpr char string_def_value[] =

		"\t\tconstexpr static size_type value[][5] =\n"
		"\t\t{\n"
	;

/***********************************************************************************************************************/

	constexpr char string_def_end[] =

		"\t\t};\n"
		"\n"
		"\t}; template<typename SizeType>\n"
		"\t\tconstexpr auto _chord_square_v0 = cctmp::U_store_T<T_chord_square_v0<SizeType>>;\n\n"
	;

/***********************************************************************************************************************/

	template<auto callable_source, typename FilePtr>
	void src_to_file(FilePtr file_ptr)
	{
		constexpr auto static_pair	= _static_callable_<callable_source>;
		constexpr auto static_source	= _static_car_<static_pair>;
		constexpr auto & source		= member_value_U<static_source>;

		fputs("\t\tconstexpr static auto src()\n" , file_ptr);
		fputs("\t\t{\n"                           , file_ptr);
		fputs("\t\t\treturn cctmp::source\n"      , file_ptr);
		fputs("\t\t\t(\n"                         , file_ptr);
		fputs("\t\t\t\t\""                        , file_ptr);
		fputs(source.origin()                     , file_ptr);
		fputs("\"\n"                              , file_ptr);
		fputs("\t\t\t);\n"                        , file_ptr);
		fputs("\t\t}\n\n"                         , file_ptr);
	}

/***********************************************************************************************************************/

	template<auto static_contr, typename FilePtr, typename StrType>
	void lit_to_file(FilePtr file_ptr, int k, int j, StrType str)
	{
		constexpr auto & contr = member_value_U<static_contr>;

		auto v = contr[k][j];
		auto t = (v < 10) ? "  " : (v < 100) ? " " : "";

		fprintf(file_ptr, " %s%d%s", t, v, str);
	}

/***********************************************************************************************************************/

	template<auto static_contr, typename FilePtr, typename StrType>
	void row_to_file(FilePtr file_ptr, int k, StrType str)
	{
		fputs("\t\t\t{", file_ptr);

		auto e = Instr::dimension;

		for (auto j = 0; j != e - 1; ++j) lit_to_file<static_contr>(file_ptr, k, j, ",");

		lit_to_file<static_contr>(file_ptr, k, e - 1, "");

		fputs(" }"  , file_ptr);
		fputs(str   , file_ptr);
		fputs(" \n" , file_ptr);
	}

/***********************************************************************************************************************/

	template<auto callable_source, auto static_contr, typename FilePtr>
	void write_to_file(FilePtr file_ptr)
	{
		auto b = 0;
		auto e = member_value_U<static_contr>.size();

		fputs(string_copyright, file_ptr);
		fputs(string_def_begin, file_ptr);

		src_to_file<callable_source>(file_ptr);
		fputs(string_def_value, file_ptr);

		for (auto k = b; k != e - 1; ++k) row_to_file<static_contr>(file_ptr, k, ",");

		row_to_file<static_contr>(file_ptr, e - 1, "");

		fputs(string_def_end, file_ptr);
	}

/***********************************************************************************************************************/

	template<auto callable_source, auto initial_env>
	void write_controller()
	{
		constexpr auto static_contr = chord::metapile<callable_source, initial_env>;

		auto file_ptr = fopen("square_v0.hpp", "w");

		if (file_ptr) write_to_file<callable_source, static_contr>(file_ptr);

		fclose(file_ptr);
	}

/***********************************************************************************************************************/

	constexpr auto _chord_square_v0()
	{
		return source
		(
			"main x           ;"

			"body:            ;"
			". = multiply x x ;"
			"return _         ;"
		);
	}

/***********************************************************************************************************************/

	int main(int argc, char *argv[])
	{
		write_controller<_chord_square_v0, null_env>();

		return 0;
	}

