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

// hustle:

namespace inventory {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// lexer:

/***********************************************************************************************************************/

// transition table:

	template<typename LexerTrait>
	struct lexer_transition_table_hustle
	{
		using trait		= LexerTrait;
		using state_name	= typename trait::State;
		using charset_name	= typename trait::Charset;

		using size_type		= typename trait::size_type;
		using size_ctype	= typename trait::size_ctype;

		template<typename Seq>
		constexpr static void set(Seq & seq, size_ctype row, size_ctype col, size_ctype val)
			{ seq[row * charset_name::dimension + col] = val; }

		constexpr static auto make()
		{
			constexpr size_type size = state_name::dimension * charset_name::dimension;
			using seq_type           = cctmp::array<size_type, size_type, size>;

			seq_type seq;
			for (size_type k = seq.length(); k != 0; --k) seq.push(state_name::empty);

			set( seq , state_name::initial    , charset_name::ula         , state_name::identifier );
			set( seq , state_name::initial    , charset_name::l_paren     , state_name::l_paren    );
			set( seq , state_name::initial    , charset_name::r_paren     , state_name::r_paren    );
			set( seq , state_name::initial    , charset_name::colon       , state_name::colon      );
			set( seq , state_name::initial    , charset_name::octothorpe  , state_name::hash       );
			set( seq , state_name::initial    , charset_name::digit       , state_name::n_numeral  );
			set( seq , state_name::initial    , charset_name::period      , state_name::period     );
			set( seq , state_name::initial    , charset_name::quote       , state_name::l_quote    );
			set( seq , state_name::initial    , charset_name::equal       , state_name::equal      );
			set( seq , state_name::initial    , charset_name::l_angle     , state_name::compare_lt );
			set( seq , state_name::initial    , charset_name::r_angle     , state_name::compare_gt );
			set( seq , state_name::initial    , charset_name::plus        , state_name::plus       );
			set( seq , state_name::initial    , charset_name::star        , state_name::star       );
			set( seq , state_name::initial    , charset_name::dash        , state_name::dash       );
			set( seq , state_name::initial    , charset_name::slash       , state_name::slash      );

			set( seq , state_name::identifier , charset_name::ula         , state_name::identifier );
			set( seq , state_name::identifier , charset_name::digit       , state_name::identifier );
			set( seq , state_name::identifier , charset_name::dash        , state_name::identifier );
			set( seq , state_name::identifier , charset_name::question    , state_name::identifier );
			set( seq , state_name::identifier , charset_name::punctuation , state_name::identifier );

			set( seq , state_name::hash       , charset_name::ula         , state_name::boolean    );

			set( seq , state_name::n_numeral  , charset_name::digit       , state_name::n_numeral  );
			set( seq , state_name::n_numeral  , charset_name::period      , state_name::period     );

			set( seq , state_name::r_numeral  , charset_name::digit       , state_name::r_numeral  );

			set( seq , state_name::period     , charset_name::digit       , state_name::r_numeral  );

			set( seq , state_name::l_quote    , charset_name::ula         , state_name::character  );

			set( seq , state_name::character  , charset_name::ula         , state_name::string     );

			set( seq , state_name::string     , charset_name::ula         , state_name::string     );

			set( seq , state_name::compare_lt , charset_name::equal       , state_name::compare_le );

			set( seq , state_name::compare_gt , charset_name::equal       , state_name::compare_ge );

			set( seq , state_name::dash       , charset_name::r_angle     , state_name::arrow      );

			return seq;
		}

		constexpr static auto seq   = make();
		constexpr static auto value = seq.origin();
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace inventory

