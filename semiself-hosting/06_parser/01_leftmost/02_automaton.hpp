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

// parser generator grammar:

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
/***********************************************************************************************************************/

// parser generator:

/***********************************************************************************************************************/

// trait:

	template<typename LexerTrait>
	struct leftmost_parser_trait
	{
		using string_type	= typename LexerTrait::string_type;
		using string_ctype	= typename LexerTrait::string_ctype;

		using char_type		= typename LexerTrait::char_type;
		using char_ctype_ref	= typename LexerTrait::char_ctype_ref;

		using size_type		= typename LexerTrait::size_type;
		using size_ctype	= typename LexerTrait::size_ctype;

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

		using Terminal = typename LexerTrait::Token;

		enum Action : size_type
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

		using table_type	= engine::parser_table<size_type, Nonterminal::dimension, Terminal::dimension>;
		using table_ctype	= typename alias<table_type>::ctype;
	};

/***********************************************************************************************************************/

// policy:

	template<typename Trait>
	struct leftmost_parser_policy
	{
		using Nonterminal		= typename Trait::Nonterminal;
		using Terminal			= typename Trait::Terminal;
		using Action			= typename Trait::Action;

		using char_type			= typename Trait::char_type;
		using char_ctype_ref		= typename Trait::char_ctype_ref;

		using size_type			= typename Trait::size_type;
		using size_ctype		= typename Trait::size_ctype;

		using text_type			= typename Trait::table_type::text_type;

		using strlit_type		= string_literal<const char, size_type>;
		using strlit_ctype_ref		= typename alias<strlit_type>::ctype_ref;

		nik_ces auto U_char_type	= U_store_T<char_type>;
		nik_ces auto U_size_type	= U_store_T<size_type>;

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

		nik_ces auto terminal = engine::lookup
		(
			U_size_type,
			U_char_type, U_size_type,

			engine::pair( 'a' , Terminal::arrow      ),
			engine::pair( 's' , Terminal::semicolon  ),
			engine::pair( 'i' , Terminal::identifier ),
			engine::pair( 'm' , Terminal::empty_body ),
			engine::pair( 'c' , Terminal::colon      ),
			engine::pair( 'l' , Terminal::literal    ),
			engine::pair( '$' , Terminal::prompt     )
		);

		nik_ces auto entry(char_ctype_ref rc, char_ctype_ref cc, strlit_ctype_ref s, size_ctype a = Action::nop)
		{
			size_ctype row = nonterminal.lfind(rc, Nonterminal::invalid);
			size_ctype col =    terminal.lfind(cc,    Terminal::invalid);

			return LambdaTuple::template make(row, col, s, a);
		}

		// char to symbol:

			struct T_char_to_symbol
			{
				nik_ces auto result(char_ctype_ref c) -> text_type
				{
					bool s = false;
					auto t = terminal.lfind(c, Terminal::invalid);
			
					if (t == Terminal::invalid)
					{
						s = true;
						t = nonterminal.lfind(c, Nonterminal::invalid);
					}
			
					return text_type{s, t};
				}
			
			};

			nik_ces auto _char_to_symbol_ = U_store_T<T_char_to_symbol>;
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// parser table:

/***********************************************************************************************************************/

// repack (helper):

	template<typename CharType, typename SizeType, SizeType Size>
	class leftmost_repack_table
	{
		public:

			using size_type			= typename alias<SizeType>::type;
			using size_ctype		= typename alias<SizeType>::ctype;

			using strlit_type		= string_literal<const char, size_type>;

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
			nik_ce      auto cbegin (size_ctype n) const { return strlit_array[n].cbegin(); }
			nik_ce      auto cend   (size_ctype n) const { return strlit_array[n].cend(); }
			nik_ce size_type action (size_ctype n) const { return action_array[n]; }
	};

/***********************************************************************************************************************/

// (transition) table:

	template<typename Trait>
	struct leftmost_parser_table
	{
		using Action			= typename Trait::Action;

		using table_type		= typename Trait::table_type;
		using table_ctype		= typename Trait::table_ctype;

		using char_type			= typename Trait::char_type;
		using char_ctype_ref		= typename Trait::char_ctype_ref;

		using size_type			= typename Trait::size_type;
		using size_ctype		= typename Trait::size_ctype;

		using policy			= leftmost_parser_policy<Trait>;

		nik_ces auto char_to_symbol	= policy::_char_to_symbol_;

		template<typename... Entries>
		nik_ces auto make(Entries... ents)
		{
			nik_ce size_type pack_size	= sizeof...(Entries);
			using repack_type		= leftmost_repack_table<char_type, size_type, pack_size>;

			repack_type rtab{ents...};
			table_type tab;

			for (auto k = 0; k != pack_size; ++k)
			{
				size_ctype row    = rtab.row    (k);
				size_ctype col    = rtab.column (k);
				      auto cin    = rtab.cbegin (k);
				      auto cend   = rtab.cend   (k);
				size_ctype action = rtab.action (k);

				tab.push_entry(row, col, char_to_symbol, cin, cend, action);
			}

			return tab;
		}

		nik_ces auto value = make
		(
			policy::entry( 'S' , 'i' , "LM"                                           ),
			policy::entry( 'S' , 'a' , "LM"                                           ),
			policy::entry( 'M' , 'i' , "LM"                                           ),
			policy::entry( 'M' , 'a' , "LM"                                           ),
			policy::entry( 'M' , '$' , ""                                             ),
			policy::entry( 'L' , 'i' , "HaBAs"                                        ),
			policy::entry( 'L' , 'a' , "HaBAs"                                        ),
			policy::entry( 'H' , 'i' , "i"     , Action::push_unique_head             ),
			policy::entry( 'H' , 'a' , ""                                             ),
			policy::entry( 'B' , 'i' , "YC"                                           ),
			policy::entry( 'B' , 'm' , "m"     , Action::push_empty_next_body         ),
			policy::entry( 'C' , 'i' , "YC"                                           ),
			policy::entry( 'C' , 's' , ""      , Action::push_next_body               ),
			policy::entry( 'C' , 'c' , ""      , Action::push_next_body               ),
			policy::entry( 'Y' , 'i' , "i"     , Action::push_identifier_current_body ),
			policy::entry( 'A' , 's' , ""      , Action::push_next_action             ),
			policy::entry( 'A' , 'c' , "cE"                                           ),
			policy::entry( 'E' , 'i' , "i"     , Action::push_identifier_next_action  ),
			policy::entry( 'E' , 'l' , "l"     , Action::push_literal_next_action     )
		);
	};

/***********************************************************************************************************************/

// tree size trait (default):

	template<typename String>
	struct leftmost_tree_size_trait
	{
		using size_type					= typename String::size_type;
		using size_ctype				= typename String::size_ctype;

		nik_ces size_type size				= String::length();

		nik_ces size_type nonterminal_page_size		= String::length();
		nik_ces size_type nonterminal_text_size		= String::length();

		nik_ces size_type terminal_page_size		= String::length();
		nik_ces size_type terminal_text_size		= String::length();

		nik_ces size_type action_page_size		= String::length();
		nik_ces size_type action_text_size		= String::length();

		nik_ces size_type grammar_body_size		= String::length();
		nik_ces size_type grammar_page_size		= String::length();
		nik_ces size_type grammar_text_size		= String::length();
	};

/***********************************************************************************************************************/

// syntactic sugar:

	template<typename String, typename TreeSizeTrait, typename String::size_type StackSize>
	nik_ce auto make_leftmost_parser(const string_literal<const char, typename String::size_type> & s)
	{
		using script_trait_type		= leftmost_tree_trait<String, TreeSizeTrait>;
		using script_type		= leftmost_parser_tree<script_trait_type>;
		using action			= leftmost_parser_action;

		using lexer_trait_type		= lexer_trait<String>;
		using lexer_type		= lexer<lexer_trait_type>;

		using parser_trait_type		= leftmost_parser_trait<lexer_trait_type>;
		using table_type		= typename parser_trait_type::table_type;
		using table_instance		= leftmost_parser_table<parser_trait_type>;

		using tree_type			= engine::parser_tree<script_type, lexer_type, TreeSizeTrait::size>;
		using parser_type		= engine::parser<table_type, tree_type, lexer_type, StackSize>;

		auto tree	= tree_type
				{{
					action::nop                          <script_type, lexer_type>,
					action::push_unique_head             <script_type, lexer_type>,
					action::push_empty_next_body         <script_type, lexer_type>,
					action::push_next_body               <script_type, lexer_type>,
					action::push_identifier_current_body <script_type, lexer_type>,
					action::push_next_action             <script_type, lexer_type>,
					action::push_identifier_next_action  <script_type, lexer_type>,
					action::push_literal_next_action     <script_type, lexer_type>
				}};
		auto lexer	= make_lexer<String>(s);
		auto start	= parser_trait_type::Nonterminal::start;

		return parser_type{table_instance::value, tree, lexer, start};
	}

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

}} // namespace cctmp::parser

