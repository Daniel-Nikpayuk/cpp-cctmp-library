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

	template<typename CharType, typename SizeType>
	class lexer_keyword
	{
		public:

			using char_type			= CharType;
			using char_ctype		= char_type const;

			using size_type			= SizeType;
			using size_ctype		= size_type const;

			using strlit_type		= string_literal<char_type, size_type>;
			using strlit_ctype		= strlit_type const;
			using strlit_ctype_ref		= strlit_ctype &;

		protected:

			strlit_ctype keyword;

		public:

			size_ctype token;

			nik_ce lexer_keyword(strlit_ctype_ref k, size_ctype t) : keyword{k}, token{t} { }

			template<typename In, typename End>
			nik_ce bool match(In in, End end) const
			{
				for (auto k = keyword.cbegin(); k != keyword.cend(); ++k, ++in)
					if (*k != *in) break;

				return (in == end);
			}
	};

/***********************************************************************************************************************/

// automaton:

	template<typename State, typename Charset, typename IterType, typename SizeType>
	class lexer_automaton
	{
		public:

			using iter_type		= IterType;
			using iter_ctype	= iter_type const;

			using size_type		= SizeType;
			using size_ctype	= size_type const;

			using lit_type		= array_literal<size_type, size_type>;
			using lit_ctype		= lit_type const;
			using lit_ctype_ref	= lit_ctype &;

		protected:

			lit_ctype table;

			iter_type start;
			iter_type current;
			iter_type finish;

			size_type mode;

		public:

			nik_ce lexer_automaton(lit_ctype_ref t, iter_ctype s, iter_ctype f) :
				table{t}, start{s}, current{s}, finish{f}, mode{}
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
				while (not_end() && matches_whitespace(*current)) ++current;

				return current;
			}

			nik_ce size_type table_at(size_ctype row, size_ctype col) const
				{ return table[row * Charset::dimension + col]; }

			nik_ce bool find_empty(size_type & peek, size_ctype col)
			{
				peek = table_at(mode, col);

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

