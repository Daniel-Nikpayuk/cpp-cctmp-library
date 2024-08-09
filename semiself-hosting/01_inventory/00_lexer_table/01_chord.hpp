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

// chord:

namespace inventory {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// lexer:

/***********************************************************************************************************************/

// transition table:

		// requires only one size type.

	template<typename SizeType>
	struct lexer_transition_table_chord
	{
		using size_type		= SizeType;
		using size_ctype	= size_type const;

		struct State
		{
			enum : size_type
			{
				empty         ,
				initial       ,
				arrow         ,
				colon         ,

				ulan          , // underscore latin alphanumeric
				n_numeral     ,
				r_numeral     ,
				semicolon     ,
				octothorpe    ,
				equal         ,
				punctuation   ,
				period        ,
				label         ,

				l_angle       ,
				r_angle       ,
				bar           ,
				at            ,
				star          ,
				caret         ,
				plus          ,
				dash          ,
				tilde         ,
				l_bracket     ,
				r_bracket     ,
				l_parenthesis ,
				r_parenthesis ,
				l_brace       ,
				r_brace       ,
				comma         ,

				backslash     ,
				no_quote      ,
				l_quote       ,
				r_quote       ,

				dimension
		};

		struct Charset
		{
			enum : size_type
			{
				other         ,
				ula           , // underscore latin alphabet
				colon         ,
				digit         ,
				semicolon     ,
				octothorpe    ,
				equal         ,
				punctuation   ,
				period        ,

				l_angle       ,
				r_angle       ,
				bar           ,
				at            ,
				star          ,
				caret         ,
				plus          ,
				dash          ,
				tilde         ,
				l_bracket     ,
				r_bracket     ,
				l_parenthesis ,
				r_parenthesis ,
				l_brace       ,
				r_brace       ,
				comma         ,

				quote         ,
				backslash     ,

				dimension
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

			set( seq , State::initial    , Charset::ula           , State::ulan          );
			set( seq , State::initial    , Charset::digit         , State::n_numeral     );
			set( seq , State::initial    , Charset::colon         , State::colon         );
			set( seq , State::initial    , Charset::semicolon     , State::semicolon     );
			set( seq , State::initial    , Charset::octothorpe    , State::octothorpe    );
			set( seq , State::initial    , Charset::equal         , State::equal         );
			set( seq , State::initial    , Charset::punctuation   , State::punctuation   );
			set( seq , State::initial    , Charset::period        , State::period        );

			set( seq , State::initial    , Charset::l_angle       , State::l_angle       );
			set( seq , State::initial    , Charset::r_angle       , State::r_angle       );
			set( seq , State::initial    , Charset::bar           , State::bar           );
			set( seq , State::initial    , Charset::at            , State::at            );
			set( seq , State::initial    , Charset::star          , State::star          );
			set( seq , State::initial    , Charset::caret         , State::caret         );
			set( seq , State::initial    , Charset::plus          , State::plus          );
			set( seq , State::initial    , Charset::dash          , State::dash          );
			set( seq , State::initial    , Charset::tilde         , State::tilde         );
			set( seq , State::initial    , Charset::l_bracket     , State::l_bracket     );
			set( seq , State::initial    , Charset::r_bracket     , State::r_bracket     );
			set( seq , State::initial    , Charset::l_parenthesis , State::l_parenthesis );
			set( seq , State::initial    , Charset::r_parenthesis , State::r_parenthesis );
			set( seq , State::initial    , Charset::l_brace       , State::l_brace       );
			set( seq , State::initial    , Charset::r_brace       , State::r_brace       );
			set( seq , State::initial    , Charset::comma         , State::comma         );

			set( seq , State::initial    , Charset::quote         , State::l_quote       );

			set( seq , State::ulan       , Charset::ula           , State::ulan          );
			set( seq , State::ulan       , Charset::digit         , State::ulan          );
			set( seq , State::ulan       , Charset::colon         , State::label         );

			set( seq , State::n_numeral  , Charset::digit         , State::n_numeral     );
			set( seq , State::n_numeral  , Charset::period        , State::period        );

			set( seq , State::r_numeral  , Charset::digit         , State::r_numeral     );

			set( seq , State::period     , Charset::digit         , State::r_numeral     );

			set( seq , State::dash       , Charset::r_angle       , State::arrow         );

			return seq;
		}

		constexpr static auto seq   = make();
		constexpr static auto value = seq.origin();
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace inventory

