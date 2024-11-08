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

namespace cctmp  {
namespace parser {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// あparser generator grammar:

/***********************************************************************************************************************/

	// tree := (head plot, body corpus, action corpus)

	// " Start      -> Line RecLine                                                    ;"
	// " RecLine    -> Line RecLine                                                    ;"
	// "            -> empty                                                           ;"
	// " Line       -> Head arrow Body Action semicolon                                ;"
	// " Head       -> identifier                       : push_unique_head             ;"
	// "            -> empty                                                           ;"
	// " Body       -> Symbol RecBody                                                  ;"
	// "            -> empty_body                       : push_empty_next_body         ;"
	// " RecBody    -> Symbol RecBody                                                  ;"
	// "            -> empty                            : push_next_body               ;"
	// " Symbol     -> identifier                       : push_identifier_current_body ;"
	// " Action     -> colon Expression                                                ;"
	// "            -> empty                            : push_next_action             ;"
	// " Expression -> identifier                       : push_identifier_next_action  ;"
	// "            -> literal                          : push_literal_next_action     ;"

  /*---------------------------------*/  /*---------------------------------*/  /*---------------------------------*/
  /* terminals (tokens):             */  /* nonterminals:                   */  /* context-free grammar (CFG):     */
  /*                                 */  /*                                 */  /*                                 */
  /* e - empty (generator)           */  /* S - Start                       */  /* S -> LM                         */
  /* a - arrow (right)               */  /* L - Line                        */  /* M -> LM    | e                  */
  /* s - semicolon                   */  /* M - Line (recursive)            */  /* L -> HaBAs                      */
  /* i - identifier                  */  /* H - Head                        */  /* H -> i     | e                  */
  /* m - empty_body (generated)      */  /* B - Body                        */  /* B -> YC    | m                  */
  /* c - colon                       */  /* C - Body (recursive)            */  /* C -> YC    | e                  */
  /* l - literal                     */  /* A - Action                      */  /* Y -> i                          */
  /*---------------------------------*/  /* Y - Symbol                      */  /* A -> cE    | e                  */
                                         /* E - Expression                  */  /* E -> i     | l                  */
                                         /*---------------------------------*/  /* --------------------------------*/

  /*--------------------------------------------------*/  /*----------------*/
  /* first:                                           */  /* follow:        */
  /*                                                  */  /*                */
  /* nonterminals   | suffixes       | bodies         */  /* nonterminals   */
  /*--------------------------------------------------*/  /*----------------*/
  /* S |   | ia     | M    | e | ia  | LM    |   | ia */  /* S | $ |        */
  /* M | e | ia     | aBAs |   | a   | e     | e |    */  /* M | $ |        */
  /* L |   | ia     | As   |   | cs  | HaBAs |   | ia */  /* L | $ | ia     */
  /* H | e | i      | s    |   | s   | i     |   | i  */  /* H |   | a      */
  /* B |   | mi     | C    | e | i   | YC    |   | i  */  /* B |   | cs     */
  /* C | e | i      |      |   |     | m     |   | m  */  /* C |   | cs     */
  /* Y |   | i      |      |   |     | cE    |   | c  */  /* Y |   | ics    */
  /* A | e | c      |      |   |     | l     |   | l  */  /* A |   | s      */
  /* E |   | il     |      |   |     |       |   |    */  /* E |   | s      */
  /*--------------------------------------------------*/  /*----------------*/

  /*------------------------------------------------------------------------------------------------*/
  /* parse table:                                                                                   */
  /*                                                                                                */
  /* n\t | i          | a          | s          | c          | m          | l          | $          */
  /*------------------------------------------------------------------------------------------------*/
  /*   S | S -> LM    | S -> LM    |            |            |            |            |            */
  /*   M | M -> LM    | M -> LM    |            |            |            |            | M -> e     */
  /*   L | L -> HaBAs | L -> HaBAs |            |            |            |            |            */
  /*   H | H -> i     | H -> e     |            |            |            |            |            */
  /*   B | B -> YC    |            |            |            | B -> m     |            |            */
  /*   C | C -> YC    |            | C -> e     | C -> e     |            |            |            */
  /*   Y | Y -> i     |            |            |            |            |            |            */
  /*   A |            |            | A -> e     | A -> cE    |            |            |            */
  /*   E | E -> i     |            |            |            |            | E -> l     |            */
  /*------------------------------------------------------------------------------------------------*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// parser table:

/***********************************************************************************************************************/

// action:

	template<typename SizeType>
	struct leftmost_action
	{
		using size_type		= typename alias<SizeType>::type;
		using size_ctype	= typename alias<SizeType>::ctype;

		enum : size_type
		{
			nop,

			push_unique_head             ,
			push_empty_next_body         ,
			push_next_body               ,
			push_identifier_current_body ,
			push_next_action             ,
			push_identifier_next_action  ,
			push_literal_next_action     ,

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

			using strlit_type		= string_literal<char_ctype, size_type>;

			using    row_array_type		= array < size_type   , size_type , Size >;
			using column_array_type		= array < size_type   , size_type , Size >;
			using strlit_array_type		= array < strlit_type , size_type , Size >;
			using action_array_type		= array < size_type   , size_type , Size >;

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

	template<typename Text, typename Table>
	struct T_leftmost_char_to_parse_symbol
	{
		using    Terminal = typename Table::Terminal;
		using Nonterminal = typename Table::Nonterminal;

		template<typename CharType>
		nik_ces auto result(CharType c) -> Text
		{
			bool s = false;
			auto t = Table::terminal.lfind(c, Terminal::invalid);

			if (t == Terminal::invalid)
			{
				s = true;
				t = Table::nonterminal.lfind(c, Nonterminal::invalid);
			}

			return Text{s, t};
		}

	}; template<typename Text, typename Table>
		nik_ce auto _leftmost_char_to_parse_symbol_ = U_store_T<T_leftmost_char_to_parse_symbol<Text, Table>>;

/***********************************************************************************************************************/

// leftmost:

	template<typename Token, typename Action, typename CharType, typename SizeType>
	struct leftmost_parser_table
	{
		using char_type			= typename alias<CharType>::type;
		using char_ctype		= typename alias<CharType>::ctype;

		using size_type			= typename alias<SizeType>::type;
		using size_ctype		= typename alias<SizeType>::ctype;

		nik_ces auto U_char_type	= U_store_T<char_type>;
		nik_ces auto U_size_type	= U_store_T<size_type>;

		// grammar:

			using Terminal = Token;

			struct Nonterminal
			{
				enum : size_type
				{
					invalid,

					start          ,
					line           ,
					line_recursive ,
					head           ,
					body           ,
					body_recursive ,
					action         ,
					symbol         ,
					expression     ,

					dimension
				};
			};

			nik_ces auto terminal = engine::lookup
			(
				U_size_type,
				U_char_type, U_size_type,

				engine::pair( 'a' , Terminal::arrow      ),
				engine::pair( ';' , Terminal::semicolon  ),
				engine::pair( 'i' , Terminal::identifier ),
				engine::pair( 'm' , Terminal::empty_body ),
				engine::pair( ':' , Terminal::colon      ),
				engine::pair( 'l' , Terminal::literal    ),
				engine::pair( '$' , Terminal::prompt     )
			);

			nik_ces auto nonterminal = engine::lookup
			(
				U_size_type,
				U_char_type, U_size_type,

				engine::pair( 'S' , Nonterminal::start          ),
				engine::pair( 'L' , Nonterminal::line           ),
				engine::pair( 'M' , Nonterminal::line_recursive ),
				engine::pair( 'H' , Nonterminal::head           ),
				engine::pair( 'B' , Nonterminal::body           ),
				engine::pair( 'C' , Nonterminal::body_recursive ),
				engine::pair( 'A' , Nonterminal::action         ),
				engine::pair( 'Y' , Nonterminal::symbol         ),
				engine::pair( 'E' , Nonterminal::expression     )
			);

		// table:

			using strlit_type		= string_literal<char_ctype, size_type>;
			using strlit_ctype_ref		= typename alias<strlit_type>::ctype_ref;

			nik_ces size_type row_size	= Nonterminal::dimension;
			nik_ces size_type col_size	=    Terminal::dimension;

			using table_type		= engine::parse_table<size_type, row_size, col_size>;
			nik_ces auto char_to_symbol	= _leftmost_char_to_parse_symbol_
							<
								typename table_type::text_type,
								leftmost_parser_table
							>;

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

					trans_table.at(row, col).set_action(action);
					trans_table.setmap(row, col, char_to_symbol, cin, cend);
				}

				return trans_table;
			}

			nik_ces auto entry
			(
				char_ctype row_c, char_ctype col_c, strlit_ctype_ref str, size_ctype act = Action::nop
			)
			{
				size_ctype row = nonterminal.lfind(row_c, Nonterminal::invalid);
				size_ctype col =    terminal.lfind(col_c,    Terminal::invalid);

				return LambdaTuple::template make(row, col, str, act);
			}

			nik_ces auto value = make_table
			(
				entry( 'S' , 'i' , "LM"                                           ),
				entry( 'S' , 'a' , "LM"                                           ),
				entry( 'M' , 'i' , "LM"                                           ),
				entry( 'M' , 'a' , "LM"                                           ),
				entry( 'M' , '$' , ""                                             ),
				entry( 'L' , 'i' , "HaBAs"                                        ),
				entry( 'L' , 'a' , "HaBAs"                                        ),
				entry( 'H' , 'i' , "i"     , Action::push_unique_head             ),
				entry( 'H' , 'a' , ""                                             ),
				entry( 'B' , 'i' , "YC"                                           ),
				entry( 'B' , 'm' , "m"     , Action::push_empty_next_body         ),
				entry( 'C' , 'i' , "YC"                                           ),
				entry( 'C' , 's' , ""      , Action::push_next_body               ),
				entry( 'C' , 'c' , ""      , Action::push_next_body               ),
				entry( 'Y' , 'i' , "i"     , Action::push_identifier_current_body ),
				entry( 'A' , 's' , ""      , Action::push_next_action             ),
				entry( 'A' , 'c' , "cE"                                           ),
				entry( 'E' , 'i' , "i"     , Action::push_identifier_next_action  ),
				entry( 'E' , 'l' , "l"     , Action::push_literal_next_action     )
			);
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

}} // namespace cctmp::parser

