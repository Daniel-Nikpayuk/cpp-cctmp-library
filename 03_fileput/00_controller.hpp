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

// controller:

namespace fileput {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// cctmp:

	using gindex_type					= cctmp::gindex_type;

	template<auto U>
	nik_ce auto & member_value_U				= cctmp::member_value_U<U>;

	template<typename T, auto S>
	using sequence						= cctmp::sequence<T, S>;

	using Instr						= cctmp::Instr;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// string (literal):

/***********************************************************************************************************************/

// catenate:

	template<typename SizeType, typename T, auto... Ns>
	constexpr auto string_catenate(const T(&... strs)[Ns])
	{
		static_assert(sizeof...(Ns), "string_catenate requires at least one argument.");

		constexpr SizeType Size = (sizeof...(Ns) + ... + Ns) - bool(sizeof...(Ns));
		using seq_type          = sequence<T, Size>;
		constexpr auto push_str = [](seq_type & seq, const T* str, const SizeType N)
						{ for (auto k = str; k != str + N - 1; ++k) seq.push(*k); };

		seq_type seq;
		(push_str(seq, strs, Ns), ...);
		seq.push('\0');

		return seq;
	}

	// syntactic sugar:

		template<typename T, auto... Ns>
		constexpr auto string16_catenate(const T(&... strs)[Ns])
			{ return string_catenate<gindex_type, T, Ns...>(strs...); }

/***********************************************************************************************************************/

// copyright:

	template<typename T>
	constexpr auto string_copyright(const T(&s)[3])
	{
		return string16_catenate
		(
			"/************************************************************"
			"************************************************************\n"
			"**\n"
			"** Copyright 2022-20",

			s,

			" Daniel Nikpayuk, Inuit Nunangat, The Inuit Nation\n"
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
			"*************************************************************"
			"***********************************************************/\n\n"
		);
	}

/***********************************************************************************************************************/

// def(ine) begin:

	template<typename T, auto N0, auto N1>
	constexpr auto string_def_begin(const T(&s0)[N0], const T(&s1)[N1])
	{
		return string16_catenate
		(
			"// object:\n\n"
			"\ttemplate<typename SizeType>\n"
			"\tstruct T_contr_object_",

			s0, "_", s1,

			"\n"
			"\t{\n"
			"\t\tusing size_type = SizeType;\n"
			"\n"
			"\t\tconstexpr static size_type value[][5] =\n"
			"\t\t{\n"
		);
	}

/***********************************************************************************************************************/

// def(ine) end:

	template<typename T, auto N0, auto N1>
	constexpr auto string_def_end(const T(&s0)[N0], const T(&s1)[N1])
	{
		return string16_catenate
		(
			"\t\t};\n"
			"\n"
			"\t}; template<typename SizeType>\n"
			"\t\tconstexpr auto contr_object_",

			s0, "_", s1,

			" = cctmp::U_store_T\n\t\t<\n\t\t\tT_contr_object_",

			s0, "_", s1,

			"<SizeType>\n\t\t>;\n\n"
		);
	}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// write:

/***********************************************************************************************************************/

// lit(eral) to file:

	template<auto static_contr, typename FilePtr, typename StrType>
	void lit_to_file(FilePtr file_ptr, int k, int j, StrType str)
	{
		constexpr auto & contr = member_value_U<static_contr>;

		auto v = contr[k][j];
		auto t = (v < 10) ? "  " : (v < 100) ? " " : "";

		fprintf(file_ptr, " %s%d%s", t, v, str);
	}

/***********************************************************************************************************************/

// row to file:

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

// write to file:

	template<auto static_contr, typename FilePtr, typename T, auto N0, auto N1>
	void write_to_file(FilePtr file_ptr, const T(&s0)[N0], const T(&s1)[N1])
	{
		auto b = 0;
		auto e = member_value_U<static_contr>.size();

		fputs(string_copyright("24").origin(), file_ptr);
		fputs(string_def_begin(s0, s1).origin(), file_ptr);

		for (auto k = b; k != e - 1; ++k) row_to_file<static_contr>(file_ptr, k, ",");

		row_to_file<static_contr>(file_ptr, e - 1, "");

		fputs(string_def_end(s0, s1).origin(), file_ptr);
	}

/***********************************************************************************************************************/

// write controller:

	template<auto static_contr, typename T, auto N0, auto N1>
	void write_controller(const T(&s0)[N0], const T(&s1)[N1])
	{
		auto file_ptr = fopen(string16_catenate(s1, ".hpp").origin(), "w");

		if (file_ptr) write_to_file<static_contr>(file_ptr, s0, s1);

		fclose(file_ptr);
	}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// print:

/***********************************************************************************************************************/

// print controller:

	template<auto static_contr>
	void print_controller(int b = 0, int e = member_value_U<static_contr>.size())
	{
		constexpr auto & contr = member_value_U<static_contr>;

		for (auto k = b; k != e; ++k)
		{
			auto s = (k < 10) ? "  " : (k < 100) ? " " : "";
			printf("line %s%d -", s, k);

			for (auto j = 0; j != Instr::dimension; ++j)
			{
				auto v = contr[k][j];
				auto t = (v < 10) ? "  " : (v < 100) ? " " : "";

				printf(" %s%d", t, v);
			}

			printf("\n");
		}
	}

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace fileput

