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

	using cctmp::gchar_type;
	using cctmp::gindex_type;

	using cctmp::U_gindex_type;
	using cctmp::member_value_U;

	using cctmp::strlit_type;
	using cctmp::U_strlit_type;

	using cctmp::sequence;
	using cctmp::Instr;

	// syntactic sugar:

		using ixs_pair = cctmp::pair<gindex_type, strlit_type>;

// assembly:

	using assembly::AN;
	using assembly::AT;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// assembly:

/***********************************************************************************************************************/

// names:

	nik_ce auto assembly_names = cctmp::table
	(
		U_gindex_type, U_strlit_type,

		ixs_pair( AN::id         , "AN::id"         ),

		ixs_pair( AN::halt       , "AN::halt"       ),

		ixs_pair( AN::type       , "AN::type"       ),
		ixs_pair( AN::literal    , "AN::literal"    ),
		ixs_pair( AN::floating   , "AN::floating"   ),
		ixs_pair( AN::string     , "AN::string"     ),
		ixs_pair( AN::lookup     , "AN::lookup"     ),
		ixs_pair( AN::arg        , "AN::arg"        ),

		ixs_pair( AN::pad        , "AN::pad"        ),
		ixs_pair( AN::hash       , "AN::hash"       ),
		ixs_pair( AN::pound      , "AN::pound"      ),
		ixs_pair( AN::apply      , "AN::apply"      ),
		ixs_pair( AN::bind       , "AN::bind"       ),
		ixs_pair( AN::eval       , "AN::eval"       ),

		ixs_pair( AN::go_to      , "AN::go_to"      ),
		ixs_pair( AN::branch     , "AN::branch"     ),
		ixs_pair( AN::invert     , "AN::invert"     ),
		ixs_pair( AN::loop       , "AN::loop"       ),

		ixs_pair( AN::cycle      , "AN::cycle"      ),
		ixs_pair( AN::next       , "AN::next"       ),
		ixs_pair( AN::set        , "AN::set"        ),

		ixs_pair( AN::repeat     , "AN::repeat"     ),
		ixs_pair( AN::map        , "AN::map"        ),
		ixs_pair( AN::fold       , "AN::fold"       ),
		ixs_pair( AN::find       , "AN::find"       ),
		ixs_pair( AN::sift       , "AN::sift"       ),

		ixs_pair( AN::dimension  , "AN::dimension"  )
	);

/***********************************************************************************************************************/

// notes:

	nik_ce auto assembly_notes = cctmp::table
	(
		U_gindex_type, U_strlit_type,

		ixs_pair( AT::id        , "AT::id"        ),

		ixs_pair( AT::none      , "AT::none"      ),
		ixs_pair( AT::first     , "AT::first"     ),
		ixs_pair( AT::front     , "AT::front"     ),
		ixs_pair( AT::back      , "AT::back"      ),

		ixs_pair( AT::boolean   , "AT::boolean"   ),
		ixs_pair( AT::character , "AT::character" ),
		ixs_pair( AT::n_number  , "AT::n_number"  ),
		ixs_pair( AT::r_number  , "AT::r_number"  ),

		ixs_pair( AT::port      , "AT::port"      ),
		ixs_pair( AT::select    , "AT::select"    ),

		ixs_pair( AT::push      , "AT::push"      ),
		ixs_pair( AT::pull      , "AT::pull"      ),
		ixs_pair( AT::drop      , "AT::drop"      ),

		ixs_pair( AT::verse     , "AT::verse"     ),
		ixs_pair( AT::side      , "AT::side"      ),
		ixs_pair( AT::replace   , "AT::replace"   ),

		ixs_pair( AT::inc       , "AT::inc"       ),
		ixs_pair( AT::dec       , "AT::dec"       ),

		ixs_pair( AT::dimension , "AT::dimension" )
	);

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
		);
	}

/***********************************************************************************************************************/

// def(ine) assembly:

	constexpr auto string_def_assembly()
	{
		return	"\t\tusing AN = assembly::AN;\n"
			"\t\tusing AT = assembly::AT;\n"
			"\n"
			;
	}

/***********************************************************************************************************************/

// def(ine) value:

	template<typename T>
	constexpr auto string_def_value()
	{
		nik_ce T size[] = "8";

		return string16_catenate
		(
			"\t\tconstexpr static size_type value[][",

			size,

			"] =\n"
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

// spacing:

	template<typename FilePtr>
	void fprint_spacing(FilePtr file_ptr, int n) { for (auto k = 0; k != n; ++k) fprintf(file_ptr, " "); }

/***********************************************************************************************************************/

// numeric to file:

	template<auto static_contr, typename FilePtr, typename StrType>
	void numeric_to_file(FilePtr file_ptr, int k, int j, StrType str)
	{
		constexpr auto & contr = member_value_U<static_contr>;

		auto v = contr[k][j];
		auto t = (v < 10) ? "  " : (v < 100) ? " " : "";

		fprintf(file_ptr, " %s%d%s", t, v, str);
	}

/***********************************************************************************************************************/

// name to file:

	template<auto static_contr, typename FilePtr, typename StrType>
	void name_to_file(FilePtr file_ptr, int k, StrType str)
	{
		constexpr auto & contr  = member_value_U<static_contr>;
		constexpr auto name_max = 14; // AN::out_in_ins

		auto name = assembly_names.lookup(contr[k][Instr::name], "unknown");
		fprintf(file_ptr, " %s", name.origin());
		fprint_spacing(file_ptr, name_max - name.size());
		fprintf(file_ptr, " ,");
	}

/***********************************************************************************************************************/

// note to file:

	template<auto static_contr, typename FilePtr, typename StrType>
	void note_to_file(FilePtr file_ptr, int k, StrType str)
	{
		constexpr auto & contr  = member_value_U<static_contr>;
		constexpr auto note_max = 13; // AT::character

		auto note = assembly_notes.lookup(contr[k][Instr::note], "unknown");
		fprintf(file_ptr, " %s", note.origin());
		fprint_spacing(file_ptr, note_max - note.size());
		fprintf(file_ptr, " ,");
	}

/***********************************************************************************************************************/

// literal to file:

	template<auto static_contr, bool is_numeric, typename FilePtr, typename StrType>
	void literal_to_file(FilePtr file_ptr, int k, int j, StrType str)
	{
		const bool is_name = !is_numeric && (j == Instr::name);
		const bool is_note = !is_numeric && (j == Instr::note);

		if      (is_name)    name_to_file<static_contr>(file_ptr, k, str);
		else if (is_note)    note_to_file<static_contr>(file_ptr, k, str);
		else              numeric_to_file<static_contr>(file_ptr, k, j, str);
	}

/***********************************************************************************************************************/

// row to file:

	template<auto static_contr, bool is_numeric, typename FilePtr, typename StrType>
	void row_to_file(FilePtr file_ptr, int k, StrType str)
	{
		fputs("\t\t\t{", file_ptr);

		auto e = Instr::dimension;

		for (auto j = 0; j != e - 1; ++j) literal_to_file<static_contr, is_numeric>(file_ptr, k, j, ",");

		literal_to_file<static_contr, is_numeric>(file_ptr, k, e - 1, "");

		fputs(" }" , file_ptr);
		fputs(str  , file_ptr);
		fputs("\n" , file_ptr);
	}

/***********************************************************************************************************************/

// write to file:

	template<auto static_contr, bool is_numeric, typename FilePtr, typename T, auto N0, auto N1>
	void write_to_file(FilePtr file_ptr, const T(&s0)[N0], const T(&s1)[N1])
	{
		auto b = 0;
		auto e = member_value_U<static_contr>.size();

		fputs(string_copyright("24").origin(), file_ptr);
		fputs(string_def_begin(s0, s1).origin(), file_ptr);

		if (!is_numeric) fputs(string_def_assembly(), file_ptr);

		fputs(string_def_value<T>().origin(), file_ptr);

		for (auto k = b; k != e - 1; ++k) row_to_file<static_contr, is_numeric>(file_ptr, k, ",");

		row_to_file<static_contr, is_numeric>(file_ptr, e - 1, "");

		fputs(string_def_end(s0, s1).origin(), file_ptr);
	}

/***********************************************************************************************************************/

// write controller:

	// numeric:

		template<auto static_contr, typename T, auto N0, auto N1>
		void write_numeric_controller(const T(&s0)[N0], const T(&s1)[N1])
		{
			auto file_ptr = fopen(string16_catenate("contr/", s1, ".hpp").origin(), "w");

			constexpr bool is_numeric = true;
			if (file_ptr) write_to_file<static_contr, is_numeric>(file_ptr, s0, s1);

			fclose(file_ptr);
		}

	// assembly:

		template<auto static_contr, typename T, auto N0, auto N1>
		void write_assembly_controller(const T(&s0)[N0], const T(&s1)[N1])
		{
			auto file_ptr = fopen(string16_catenate("contr/", s1, ".hpp").origin(), "w");

			constexpr bool is_numeric = false;
			if (file_ptr) write_to_file<static_contr, is_numeric>(file_ptr, s0, s1);

			fclose(file_ptr);
		}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// print:

/***********************************************************************************************************************/

// spacing:

	void print_spacing(int n) { for (auto k = 0; k != n; ++k) printf(" "); }

/***********************************************************************************************************************/

// numeric:

	template<auto static_contr>
	void print_numeric_controller(int b = 0, int e = member_value_U<static_contr>.size())
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

// assembly:

	template<auto static_contr>
	void print_assembly_controller(int b = 0, int e = member_value_U<static_contr>.size())
	{
		constexpr auto & contr  = member_value_U<static_contr>;
		constexpr auto name_max = 14; // AN::out_in_ins
		constexpr auto note_max = 13; // AT::character

		for (auto k = b; k != e; ++k)
		{
			auto s = (k < 10) ? "  " : (k < 100) ? " " : "";
			printf("line %s%d -", s, k);

			auto name = assembly_names.lookup(contr[k][Instr::name], "unknown");
			printf(" %s", name.origin());
			print_spacing(name_max - name.size());

			auto note = assembly_notes.lookup(contr[k][Instr::note], "unknown");
			printf(" %s", note.origin());
			print_spacing(note_max - note.size());

			for (auto j = 2; j != Instr::dimension; ++j)
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

