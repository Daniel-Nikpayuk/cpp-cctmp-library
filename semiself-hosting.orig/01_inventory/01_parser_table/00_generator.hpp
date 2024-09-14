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

// parser:

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// pushdown automaton:

/***********************************************************************************************************************/

// interface:

	template<typename SizeType>
	struct parser_transition_table_generator
	{
		using size_type		= SizeType;
		using size_ctype	= size_type const;

		template<typename Seq>
		constexpr static void set(Seq & seq, size_ctype row, size_ctype col, size_ctype val)
			{ seq[row * Charset::dimension + col] = val; }

		constexpr static auto make()
		{
			constexpr size_type size = State::dimension * Charset::dimension;
			using seq_type           = cctmp::array<size_type, size_type, size>;

			return seq;
		}

			// we temporarily need additional data structures
			// here until we can generate the table.
			// make it like a frame, where we go across bindings
			// to collect the relevant info.
			// a function which can collect relevant constexpr info.
			// problem is it is more than one variety of data: size_type, char_type.
			// we might need separate arrays.

			// maybe we can't define it here after all, maybe it needs to be in
			// the parser generator directory.

			set_entry( 'S' , 'i' , "iFD"   , ActName::l_value );
			set_entry( 'D' , 'i' , "iHD"   , ActName::l_value );
			set_entry( 'D' , '$' , ""      , ActName::accept  );
			set_entry( 'F' , 'a' , "aMA;B" , ActName::front   );
			set_entry( 'F' , '=' , "=IJK"                     );
			set_entry( 'H' , 'a' , "aMA;B" , ActName::head    );
			set_entry( 'H' , '=' , "=IJK"                     );
			set_entry( 'B' , 'i' , ""                         );
			set_entry( 'B' , 'a' , "aMA;B" , ActName::body    );
			set_entry( 'B' , '$' , ""                         );
			set_entry( 'M' , 'i' , "TN"                       );
			set_entry( 'M' , 'm' , "m"     , ActName::m_value );
			set_entry( 'N' , 'i' , "TN"                       );
			set_entry( 'N' , ';' , ""                         );
			set_entry( 'N' , ':' , ""                         );
			set_entry( 'T' , 'i' , "i"     , ActName::r_value );
			set_entry( 'A' , ';' , ""                         );
			set_entry( 'A' , ':' , ":C"                       );
			set_entry( 'C' , 'i' , "i"     , ActName::a_value );
			set_entry( 'J' , 'i' , "IJ"                       );
			set_entry( 'J' , ';' , ""                         );
			set_entry( 'I' , 'i' , "i"                        );
			set_entry( 'K' , ';' , ";"                        );

		constexpr static auto seq   = make();
		constexpr static auto value = seq.origin();
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

