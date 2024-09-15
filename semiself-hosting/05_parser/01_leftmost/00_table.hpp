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

// (generate) table:

namespace cctmp  {
namespace parser {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// engine:

	using engine::LambdaTuple;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// transition table:

/***********************************************************************************************************************/

// token:

	template<typename SizeType>
	struct LeftmostToken
	{
		using size_type		= typename alias<SizeType>::type;
		using size_ctype	= typename alias<SizeType>::ctype;

		enum : size_type
		{
			invalid    ,
			empty      ,
			prompt     ,
			identifier ,
			none       ,
			arrow      ,
			equal      ,
			colon      ,
			semicolon  ,

			dimension
		};
	};

/***********************************************************************************************************************/

// action:

	template<typename SizeType>
	struct LeftmostAction
	{
		using size_type		= typename alias<SizeType>::type;
		using size_ctype	= typename alias<SizeType>::ctype;

		enum : size_type
		{
			nop,

			l_value , r_value , m_value , a_value ,
			front   , head    , body    , accept  ,

			dimension
		};
	};

/***********************************************************************************************************************/

// repack (helper):

	template<typename CharType, typename SizeType, SizeType Size>
	class leftmost_repack_table
	{
		public:

			using char_type			= typename alias<CharType>::type;
			using char_ctype		= typename alias<CharType>::ctype;

			using size_type			= typename alias<SizeType>::type;
			using size_ctype		= typename alias<SizeType>::ctype;

			using strlit_type		= cctmp::string_literal<char_ctype, size_type>;

			using    row_array_type		= cctmp::array < size_type   , size_type , Size >;
			using column_array_type		= cctmp::array < size_type   , size_type , Size >;
			using strlit_array_type		= cctmp::array < strlit_type , size_type , Size >;
			using action_array_type		= cctmp::array < size_type   , size_type , Size >;

		protected:

			   row_array_type    row_array;
			column_array_type column_array;
			strlit_array_type strlit_array;
			action_array_type action_array;

		public:

			template<typename... Entries>
			nik_ce leftmost_repack_table(Entries... ents) :

				   row_array {{LambdaTuple::value<0>(ents)...}},
				column_array {{LambdaTuple::value<1>(ents)...}},
				strlit_array {{LambdaTuple::value<2>(ents)...}},
				action_array {{LambdaTuple::value<3>(ents)...}}

				{ }

			nik_ce size_type row    (size_ctype n) const { return    row_array[n]; }
			nik_ce size_type column (size_ctype n) const { return column_array[n]; }
			nik_ce auto      cbegin (size_ctype n) const { return strlit_array[n].cbegin(); }
			nik_ce auto      cend   (size_ctype n) const { return strlit_array[n].cend(); }
			nik_ce size_type action (size_ctype n) const { return action_array[n]; }
	};

/***********************************************************************************************************************/

// char to parse symbol:

	template<typename Stance, typename Table>
	struct T_leftmost_char_to_parse_symbol
	{
		using    Terminal = typename Table::Terminal;
		using Nonterminal = typename Table::Nonterminal;

		template<typename CharType>
		nik_ces auto result(CharType c) -> Stance
		{
			bool s = false;
			auto t = Table::terminal.lfind(c, Terminal::invalid);

			if (t == Terminal::invalid)
			{
				s = true;
				t = Table::nonterminal.lfind(c, Nonterminal::invalid);
			}

			return Stance{s, t};
		}

	}; template<typename Stance, typename Table>
		nik_ce auto _leftmost_char_to_parse_symbol_ = U_store_T<T_leftmost_char_to_parse_symbol<Stance, Table>>;

/***********************************************************************************************************************/

// leftmost:

	template<typename Token, typename Action, typename CharType, typename SizeType>
	struct leftmost_transition_table
	{
		using char_type			= typename alias<CharType>::type;
		using char_ctype		= typename alias<CharType>::ctype;

		using size_type			= typename alias<SizeType>::type;
		using size_ctype		= typename alias<SizeType>::ctype;

		nik_ces auto U_char_type	= U_store_T<char_type>;
		nik_ces auto U_size_type	= U_store_T<size_type>;

		// grammar:

			using Terminal		= Token;

			struct Nonterminal
			{
				enum : size_type
				{
					start         ,
					rec_declare   ,
					front_declare ,
					head_declare  ,
					body_declare  ,
					disp_name     ,
					rec_name      ,
					tok_name      ,
					action        ,
					call          ,
					rec_alias     ,
					tok_alias     ,
					end_alias     ,
					invalid       ,

					dimension
				};
			};

			nik_ces auto terminal = engine::lookup
			(
				U_size_type,
				U_char_type, U_size_type,

				engine::pair( 'i' , Terminal::identifier ),
				engine::pair( 'a' , Terminal::arrow      ),
				engine::pair( ';' , Terminal::semicolon  ),
				engine::pair( ':' , Terminal::colon      ),
				engine::pair( 'm' , Terminal::empty      ), // empty, not none.
				engine::pair( '=' , Terminal::equal      ),
				engine::pair( '$' , Terminal::prompt     )
			);

			nik_ces auto nonterminal = engine::lookup
			(
				U_size_type,
				U_char_type, U_size_type,

				engine::pair( 'S' , Nonterminal::start         ),
				engine::pair( 'D' , Nonterminal::rec_declare   ),
				engine::pair( 'F' , Nonterminal::front_declare ),
				engine::pair( 'H' , Nonterminal::head_declare  ),
				engine::pair( 'B' , Nonterminal::body_declare  ),
				engine::pair( 'M' , Nonterminal::disp_name     ),
				engine::pair( 'N' , Nonterminal::rec_name      ),
				engine::pair( 'T' , Nonterminal::tok_name      ),
				engine::pair( 'A' , Nonterminal::action        ),
				engine::pair( 'C' , Nonterminal::call          ),
				engine::pair( 'J' , Nonterminal::rec_alias     ),
				engine::pair( 'I' , Nonterminal::tok_alias     ),
				engine::pair( 'K' , Nonterminal::end_alias     )
			);

		// table:

			using strlit_type		= cctmp::string_literal<char_ctype, size_type>;
			using strlit_ctype_ref		= typename alias<strlit_type>::ctype_ref;

			nik_ces size_type row_size	= Nonterminal::dimension;
			nik_ces size_type col_size	=    Terminal::dimension;

			using page_type			= engine::parse_table_page < size_type >;
			using text_type			= engine::parse_table_text < size_type >;
			using table_type		= engine::plottable
							<
								page_type, text_type, size_type, row_size, col_size
							>;
			nik_ces auto char_to_symbol	= _leftmost_char_to_parse_symbol_
							<
								text_type, leftmost_transition_table
							>;

			nik_ces auto entry
			(
				char_ctype row_c, char_ctype col_c, strlit_ctype_ref str, size_ctype act = Action::nop
			)
			{
				size_ctype row = nonterminal.lfind(row_c, Nonterminal::invalid);
				size_ctype col =    terminal.lfind(col_c,    Terminal::invalid);

				return LambdaTuple::template make(row, col, str, act);
			}

			template<typename... Entries>
			nik_ces auto make_table(Entries... ents)
			{
				nik_ce size_type pack_size	= sizeof...(Entries);
				using repack_type		= leftmost_repack_table<char_type, size_type, pack_size>;

				repack_type repack_table{ents...};
				table_type trans_table;

				for (auto k = 0; k != pack_size; ++k)
				{
					size_ctype row    = repack_table.row    (k);
					size_ctype col    = repack_table.column (k);
					auto       cin    = repack_table.cbegin (k);
					auto       cend   = repack_table.cend   (k);
					size_ctype action = repack_table.action (k);

					trans_table[row][col].set_valid();
					trans_table[row][col].set_action(action);
					trans_table.setmap(row, col, char_to_symbol, cin, cend);
				}

				return trans_table;
			}

			nik_ces auto value = make_table
			(
				entry( 'S' , 'i' , "iFD"   , Action::l_value ),
				entry( 'D' , 'i' , "iHD"   , Action::l_value ),
				entry( 'D' , '$' , ""      , Action::accept  ),
				entry( 'F' , 'a' , "aMA;B" , Action::front   ),
				entry( 'F' , '=' , "=IJK"                    ),
				entry( 'H' , 'a' , "aMA;B" , Action::head    ),
				entry( 'H' , '=' , "=IJK"                    ),
				entry( 'B' , 'i' , ""                        ),
				entry( 'B' , 'a' , "aMA;B" , Action::body    ),
				entry( 'B' , '$' , ""                        ),
				entry( 'M' , 'i' , "TN"                      ),
				entry( 'M' , 'm' , "m"     , Action::m_value ),
				entry( 'N' , 'i' , "TN"                      ),
				entry( 'N' , ';' , ""                        ),
				entry( 'N' , ':' , ""                        ),
				entry( 'T' , 'i' , "i"     , Action::r_value ),
				entry( 'A' , ';' , ""                        ),
				entry( 'A' , ':' , ":C"                      ),
				entry( 'C' , 'i' , "i"     , Action::a_value ),
				entry( 'J' , 'i' , "IJ"                      ),
				entry( 'J' , ';' , ""                        ),
				entry( 'I' , 'i' , "i"                       ),
				entry( 'K' , ';' , ";"                       )
			);
	};

	using lltr_table = leftmost_transition_table
	<
		LeftmostToken<gindex_type>  ,
		LeftmostAction<gindex_type> ,
		gchar_type                  ,
		gindex_type
	>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

}} // namespace cctmp::parser

