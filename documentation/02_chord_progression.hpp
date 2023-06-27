/************************************************************************************************************************
**
** Copyright 2022-2023 Daniel Nikpayuk, Inuit Nunangat, The Inuit Nation
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

// chord progression.

namespace cctmp_chord {

	// This grammar is currently experimental.

	// What about quotes? (eg. 'inc 2')

	// 1. add "void" as a keyword alternate to { !var = ...; }
	// 2. [) default expands to [+|-), otherwise if *next* is given, *prev* is also required.
	// 3. If no such *prev* exists, it must be indicated with "#".

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// symbols:

	// available functional operators: { repeat, map, fold, find_first, find_all, zip, fasten, glide }
	// special characters            :    ~!@#$%^&*()_+`-={}|[]\:";'<>?,./
	// disallowed                    :    "
	// already used                  :    !_#=:;'.
	// chord reserved                :    <>{}[](),@*+-|~
	// remaining                     :    $%^&`\?/

/***********************************************************************************************************************/

// version 0:

	constexpr auto some_function_v0()
	{
		return source
		(
			"some_function out in end                   ;"

			"body:                                      ;"
			"  pos = find_first<is_zero*>[,) in end     ;"
			"  out = map<square*|equal>[)[,] out!in pos ;"
			"    . = fold<add@*>(-,) zero end pos       ;"
			"  return _                                 ;"
		);
	}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// repeat:

/***********************************************************************************************************************/

// version 0 (full options):

	constexpr auto repeat_v0()
	{
		return source
		(
			"f out end in                                          ;"

			"body:                                                 ;"
			" . = repeat<@|appoint @ @|equal @ @>[+,){} out end in ;"
			" return _                                             ;"
		);
	}

/***********************************************************************************************************************/

// version 1 (minimal options):

	constexpr auto repeat_v1()
	{
		return source
		(
			"f out end in                    ;"

			"body:                           ;"
			" . = repeat<||>[,){} out end in ;"
			" return _                       ;"
		);
	}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// map:

/***********************************************************************************************************************/

// version 0 (full options):

	constexpr auto map_v0()
	{
		return source
		(
			"f out in end                                                       ;"

			"body:                                                              ;"
			" . = map<square *|appoint @ @|equal @ @>[+|-)[+|-, +|-) out in end ;"
			" return _                                                          ;"
		);
	}

/***********************************************************************************************************************/

// version 1 (minimal options):

	constexpr auto map_v1()
	{
		return source
		(
			"f out in end                         ;"

			"body:                                ;"
			" . = map<square *||>[)[,) out in end ;"
			" return _                            ;"
		);
	}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// fold:

/***********************************************************************************************************************/

// version 0 (full options):

	constexpr auto fold_v0() // "assign" is a keyword.
	{
		return source
		(
			"f out in end                                             ;"

			"body:                                                    ;"
			" . = fold<add @ *|assign @ @|equal @ @>{}[+,) out in end ;"
			" return _                                                ;"
		);
	}

/***********************************************************************************************************************/

// version 1 (minimal options):

	constexpr auto fold_v1()
	{
		return source
		(
			"f out in end                         ;"

			"body:                                ;"
			" . = fold<add @ *||>{}[,) out in end ;"
			" return _                            ;"
		);
	}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// find first:

/***********************************************************************************************************************/

// version 0 (full options):

	constexpr auto find_first_v0()
	{
		return source
		(
			"f in end                                        ;"

			"body:                                           ;"
			" . = find_first<is_zero *|equal @ @>[+,) in end ;"
			" return _                                       ;"
		);
	}

/***********************************************************************************************************************/

// version 1 (minimal options):

	constexpr auto find_first_v1()
	{
		return source
		(
			"f in end                              ;"

			"body:                                 ;"
			" . = find_first<is_zero *|>[,) in end ;"
			" return _                             ;"
		);
	}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// find all:

/***********************************************************************************************************************/

// version 0 (full options):

	constexpr auto find_all_v0()
	{
		return source
		(
			"f out in end                                                     ;"

			"body:                                                            ;"
			" . = find_all<is_zero *|appoint @ @|equal @ @>[+)[+,) out in end ;" // because [) is a fixed option
			" return _                                                        ;" // [,) is a minimal dispatch.
		);
	}

/***********************************************************************************************************************/

// version 1 (minimal options):

	constexpr auto find_all_v1()
	{
		return source
		(
			"f out in end                               ;"

			"body:                                      ;"
			" . = find_all<is_zero *||>[)[,) out in end ;" // because [) is a fixed option
			" return _                                  ;" // [,) is a minimal dispatch.
		);
	}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// zip (bimap):

/***********************************************************************************************************************/

// version 0 (full options):

	constexpr auto zip_v0()
	{
		return source
		(
			"f out in1 in2 end2                                                           ;"

			"body:                                                                        ;"
			" . = zip<add * *|appoint @ @|equal @ @>[+|-)[+|-)[+|-, +|-) out in1 in2 end2 ;"
			" return _                                                                    ;"
		);
	}

/***********************************************************************************************************************/

// version 1 (minimal options):

	constexpr auto zip_v1()
	{
		return source
		(
			"f out in1 in2 end2                          ;"

			"body:                                       ;"
			" . = zip<add * *||>[)[)[,) out in1 in2 end2 ;"
			" return _                                   ;"
		);
	}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// fasten (zip with a carry):

/***********************************************************************************************************************/

// version 0 (full options):

	constexpr auto fasten_v0()
	{
		return source
		(
			"f out in in1 in2 end2                                                                         ;"

			"body:                                                                                         ;"
			" . = fasten<add * *|appoint @ @|carry @ @|equal @ @>[+|-){}[+|-)[+|-,+|-) out in in1 in2 end2 ;"
			" return _                                                                                     ;"
		);
	}

/***********************************************************************************************************************/

// version 1 (minimal options):

	constexpr auto fasten_v1()
	{
		return source
		(
			"f out in in1 in2 end2                                     ;"

			"body:                                                     ;"
			" . = fasten<add * *||carry|>[){}[)[,) out in in1 in2 end2 ;"
			" return _                                                 ;"
		);
	}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// glide (bifold):

/***********************************************************************************************************************/

// version 0 (full options):

	constexpr auto glide_v0() // "assign" is a keyword.
	{
		return source
		(
			"f out in1 in2 end2                                                                     ;"

			"body:                                                                                  ;"
			" . = glide<multiply * *|add @ @|assign @ @|equal @ @>{}[+|-)[+|-,+|-) out in1 in2 end2 ;"
			" return _                                                                              ;"
		);
	}

/***********************************************************************************************************************/

// version 1 (minimal options):

	constexpr auto glide_v1()
	{
		return source
		(
			"f out in1 in2 end2                                     ;"

			"body:                                                  ;"
			" . = glide<multiply * *|add||>{}[)[,) out in1 in2 end2 ;"
			" return _                                              ;"
		);
	}

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp_chord

