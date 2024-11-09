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

// lexer:

namespace cctmp  {
namespace engine {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// deterministic finite automata:

/***********************************************************************************************************************/

// keyword:

	template<typename String>
	class lexer_keyword
	{
		public:

			using string_type		= typename alias<String>::type;
			using string_ctype		= typename alias<String>::ctype;
			using string_ctype_ref		= typename alias<String>::ctype_ref;

			using char_type			= typename string_type::char_type;
			using char_ctype		= typename string_type::char_ctype;

			using size_type			= typename string_type::size_type;
			using size_ctype		= typename string_type::size_ctype;

		protected:

			string_ctype keyword;

		public:

			size_ctype token;

			nik_ce lexer_keyword(string_ctype_ref k, size_ctype t) : keyword{k}, token{t} { }

			template<typename In, typename End>
			nik_ce bool match(In in, End end) const { return keyword.equal(in, end); }
	};

/***********************************************************************************************************************/

// automaton:

	template<typename Table, typename String, typename State>
	class lexer_automaton
	{
		public:

			using table_type		= typename alias<Table>::type;
			using table_ctype		= typename alias<Table>::ctype;
			using table_ctype_ref		= typename alias<Table>::ctype_ref;

			using string_type		= typename alias<String>::type;
			using string_ctype		= typename alias<String>::ctype;
			using string_ctype_ref		= typename alias<String>::ctype_ref;

			using iter_type			= typename string_type::char_ctype_ptr;
			using iter_ctype		= typename string_type::char_ctype_cptr;

			using size_type			= typename string_type::size_type;
			using size_ctype		= typename string_type::size_ctype;

		protected:

			table_ctype table;

			iter_type start;
			iter_type current;
			iter_type finish;

			size_type mode;

		public:

			nik_ce lexer_automaton(table_ctype_ref t, string_ctype_ref s) :
				table{t}, start{s.cbegin()}, current{s.cbegin()}, finish{s.cend()}, mode{}
					{ }

			nik_ce size_type left_size() const { return current - start; }

			nik_ce bool not_begin () const { return (current != start); }
			nik_ce bool not_end   () const { return (current != finish); }

			nik_ce auto cbegin    () const { return start; }
			nik_ce auto cprevious () const { return current - 1; }
			nik_ce auto ccurrent  () const { return current; }
			nik_ce auto cend      () const { return finish; }

			nik_ce size_type state() const { return mode; }

		protected:

			nik_ce auto skip_whitespace()
			{
				while (not_end() && current->matches_whitespace()) ++current;

				return current;
			}

			nik_ce size_type cat(size_ctype row, size_ctype col) const { return table[row][col]; }

			nik_ce bool find_empty(size_type & peek, size_ctype col)
			{
				peek = cat(mode, col);

				return (peek == State::empty);
			}

			nik_ce void increment(size_ctype next) { mode = next; }

		public:

			nik_ce void initialize()
			{
				start = skip_whitespace();
				mode  = State::initial;
			}

			template<typename Policy>
			nik_ce bool find()
			{
				size_type peek;

				while (not_end())
				{
					if (find_empty(peek, Policy::map(*current++))) break;

					increment(peek);
				}

				return not_begin();
			}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

}} // namespace cctmp::engine

