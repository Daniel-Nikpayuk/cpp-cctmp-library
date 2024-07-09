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

		// requires only one size type.

	template<typename SizeType>
	struct lexer_transition_table_hustle
	{
		using size_type		= SizeType;
		using size_ctype	= size_type const;

		struct State
		{
			enum : size_type
			{
				empty       ,
				initial     ,
				l_paren     ,
				r_paren     ,
				arrow       ,
				colon       ,

				identifier  ,
				hash        , // # (boolean)
				boolean     ,
				n_numeral   ,
				r_numeral   ,
				period      ,
				character   ,
				string      ,

				equal       ,
				compare_lt  ,
				compare_le  ,
				compare_gt  ,
				compare_ge  ,
				plus        ,
				star        ,
				dash        ,
				slash       ,
				l_quote     ,

				dimension
			};
		};

		struct Charset
		{
			enum : size_type
			{
				other       ,
				ula         , // underscore latin alphabet
				digit       ,
				quote       ,
				colon       ,
				period      ,
				l_paren     ,
				r_paren     ,
				question    ,
				octothorpe  ,
				punctuation ,

				equal       ,
				l_angle     ,
				r_angle     ,
				plus        ,
				star        ,
				dash        ,
				slash       ,

				backslash   ,
				dimension
			};
		};

		template<typename Seq>
		constexpr static void set(Seq & seq, size_ctype row, size_ctype col, size_ctype val)
			{ seq[row * Charset::dimension + col] = val; }

		constexpr static auto make()
		{
			constexpr size_type size = State::dimension * Charset::dimension;
			using seq_type           = cctmp::sequence<size_type, size_type, size>;

			seq_type seq;
			for (size_type k = seq.length(); k != 0; --k) seq.push(State::empty);

			set( seq , State::initial    , Charset::ula         , State::identifier );
			set( seq , State::initial    , Charset::l_paren     , State::l_paren    );
			set( seq , State::initial    , Charset::r_paren     , State::r_paren    );
			set( seq , State::initial    , Charset::colon       , State::colon      );
			set( seq , State::initial    , Charset::octothorpe  , State::hash       );
			set( seq , State::initial    , Charset::digit       , State::n_numeral  );
			set( seq , State::initial    , Charset::period      , State::period     );
			set( seq , State::initial    , Charset::quote       , State::l_quote    );
			set( seq , State::initial    , Charset::equal       , State::equal      );
			set( seq , State::initial    , Charset::l_angle     , State::compare_lt );
			set( seq , State::initial    , Charset::r_angle     , State::compare_gt );
			set( seq , State::initial    , Charset::plus        , State::plus       );
			set( seq , State::initial    , Charset::star        , State::star       );
			set( seq , State::initial    , Charset::dash        , State::dash       );
			set( seq , State::initial    , Charset::slash       , State::slash      );

			set( seq , State::identifier , Charset::ula         , State::identifier );
			set( seq , State::identifier , Charset::digit       , State::identifier );
			set( seq , State::identifier , Charset::dash        , State::identifier );
			set( seq , State::identifier , Charset::question    , State::identifier );
			set( seq , State::identifier , Charset::punctuation , State::identifier );

			set( seq , State::hash       , Charset::ula         , State::boolean    );

			set( seq , State::n_numeral  , Charset::digit       , State::n_numeral  );
			set( seq , State::n_numeral  , Charset::period      , State::period     );

			set( seq , State::r_numeral  , Charset::digit       , State::r_numeral  );

			set( seq , State::period     , Charset::digit       , State::r_numeral  );

			set( seq , State::l_quote    , Charset::ula         , State::character  );

			set( seq , State::character  , Charset::ula         , State::string     );

			set( seq , State::string     , Charset::ula         , State::string     );

			set( seq , State::compare_lt , Charset::equal       , State::compare_le );

			set( seq , State::compare_gt , Charset::equal       , State::compare_ge );

			set( seq , State::dash       , Charset::r_angle     , State::arrow      );

			return seq;
		}

		constexpr static auto seq   = make();
		constexpr static auto value = seq.origin();
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace inventory

