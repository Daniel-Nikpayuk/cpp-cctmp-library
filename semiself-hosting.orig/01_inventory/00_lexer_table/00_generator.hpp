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

// generator:

namespace inventory {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// lexer:

/***********************************************************************************************************************/

// transition table:

		// requires only one size type.

	template<typename SizeType>
	class lexer_transition_table_generator
	{
		using size_type		= SizeType;
		using size_ctype	= size_type const;

		struct State
		{
			enum : size_type
			{
				empty      ,
				initial    ,
				any        ,
				dash       ,
				rangle     ,
				equal      ,
				colon      ,
				semicolon  ,
				backslash  ,
				whitespace ,

				dimension
			};
		};

		struct Charset
		{
			enum : size_type
			{
				any        ,
				dash       ,
				rangle     ,
				equal      ,
				colon      ,
				semicolon  ,
				backslash  ,
				whitespace ,

				dimension
			};
		};

		template<typename Seq>
		constexpr static void set(Seq & seq, size_ctype row, size_ctype col, size_ctype val)
			{ seq[row * Charset::dimension + col] = val; }

		constexpr static auto make()
		{
			constexpr size_type size = State::dimension * Charset::dimension;
			using seq_type           = cctmp::array<size_type, size_type, size>;

			seq_type seq;
			for (size_type k = seq.length(); k != 0; --k) seq.push(State::empty);

			set( seq , State::initial   , Charset::any       , State::any       );
			set( seq , State::initial   , Charset::dash      , State::dash      );
			set( seq , State::initial   , Charset::equal     , State::equal     );
			set( seq , State::initial   , Charset::colon     , State::colon     );
			set( seq , State::initial   , Charset::semicolon , State::semicolon );
			set( seq , State::initial   , Charset::backslash , State::backslash );

			set( seq , State::any       , Charset::any       , State::any       );
			set( seq , State::any       , Charset::backslash , State::backslash );

			set( seq , State::backslash , Charset::dash      , State::any       );
			set( seq , State::backslash , Charset::rangle    , State::any       );
			set( seq , State::backslash , Charset::equal     , State::any       );
			set( seq , State::backslash , Charset::colon     , State::any       );
			set( seq , State::backslash , Charset::semicolon , State::any       );
			set( seq , State::backslash , Charset::backslash , State::any       );

			set( seq , State::dash      , Charset::rangle    , State::rangle    );

			return seq;
		}

		constexpr static auto seq   = make();
		constexpr static auto value = seq.origin();
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace inventory

