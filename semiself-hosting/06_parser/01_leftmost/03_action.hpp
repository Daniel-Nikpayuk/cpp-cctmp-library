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

// action:

namespace cctmp  {
namespace parser {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// leftmost:

	struct leftmost_parser_action
	{
		// nop:

			template<typename Script, typename Lexer>
			nik_ces void nop(Script & s, const Lexer & l) { }

		// push unique head:

			template<typename Script, typename Lexer>
			nik_ces void push_unique_head(Script & s, const Lexer & l)
				{ s.nonterminal().push(l.cbegin(), l.ccurrent()); }

		// push empty next body:

			template<typename Script, typename Lexer>
			nik_ces void push_empty_next_body(Script & s, const Lexer & l)
			{
			}

		// push next body:

			template<typename Script, typename Lexer>
			nik_ces void push_next_body(Script & s, const Lexer & l)
			{
			}

		// push identifier current body:

			template<typename Script, typename Lexer>
			nik_ces void push_identifier_current_body(Script & s, const Lexer & l)
			{
			}

		// push next action:

			template<typename Script, typename Lexer>
			nik_ces void push_next_action(Script & s, const Lexer & l)
			{
			}

		// push identifier next action:

			template<typename Script, typename Lexer>
			nik_ces void push_identifier_next_action(Script & s, const Lexer & l)
			{
			}

		// push literal next action:

			template<typename Script, typename Lexer>
			nik_ces void push_literal_next_action(Script & s, const Lexer & l)
			{
			}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

}} // namespace cctmp::parser

