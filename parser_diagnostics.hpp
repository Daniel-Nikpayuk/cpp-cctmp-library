/************************************************************************************************************************
**
** Copyright 2022-2023 Daniel Nikpayuk, Inuit Nunangat, The Inuit Nation
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

// parser diagnostics:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// derivation:

/***********************************************************************************************************************/

	template<typename T_pdtt, typename T_ast, typename T_syntax, auto StaticSource, auto Size>
	struct DerivationPDA : public GenericPDA<T_pdtt, T_ast, T_syntax, StaticSource>
	{
		using Base		= GenericPDA<T_pdtt, T_ast, T_syntax, StaticSource>;
		nik_ces auto length     = Size;

		using char_type		= typename Base::char_type;
		using string_type	= typename Base::string_type;
		using T_dfa		= typename Base::T_dfa;

		char_type record[length];
		char_type *current;

		nik_ce DerivationPDA() :

			Base    { false  },
			record  {        },
			current { record }

			{ parse(); }

		nik_ce void parse()
		{
			while (*Base::stack.current != '\0')
			{
				switch (T_pdtt::token_kind(Base::front))
				{
					case TokenKind::nonterminal: nonterminal(); break;
					case TokenKind::terminal:       terminal(); break;
					default:                           error(); break;
				}

				Base::front = Base::stack.front();
			}

			update_end();
		}

		nik_ce void nonterminal()
		{
			Base::update_production();

			update_stack();
			update_tokens();
			update_production();

			Base::update_stack();
			Base::update_action();
		}

		nik_ce void terminal()
		{
			update_stack();
			update_tokens();
			update_newline();

			Base::terminal();
		}

		nik_ce void error()
		{
			// nothing yet.
		}

		nik_ce void update_newline() { *(current++) = '\n'; }
		nik_ce void update_symline() { *(current++) =  '$'; } // A visual substitute for '\0'.
		nik_ce void update_endline() { *(current++) = '\0'; }
		nik_ce void update_space  () { *(current++) =  ' '; }
		nik_ce void update_dash   () { *(current++) =  '-'; }
		nik_ce void update_gt     () { *(current++) =  '>'; }
		nik_ce void update_arrow  () { update_space(); update_dash(); update_gt(); update_space(); }

		nik_ce void update_pad(int s)
		{
			for (int k = 0; k < s; ++k) *(current++) = ' ';
		}

		nik_ce void update_stack()
		{
			auto k = Base::stack.current;
			update_pad(14 - (k - Base::stack.token));
			while (k != Base::stack.token) *(current++) = *(k--);
			update_symline();
		}

		nik_ce void update_tokens()
		{
			update_pad(4);
			auto k = Base::word.finish;
			auto count = 32;
			while (k != Base::src.finish)
			{
				auto w = T_dfa::lex(k, Base::src.finish);
				--count;
				k = w.finish;
			}

			k = Base::word.finish;
			update_pad(count);

			if (Base::word.value != '\0') *(current++) = Base::word.value;
			else update_pad(1);
			while (k != Base::src.finish)
			{
				auto w = T_dfa::lex(k, Base::src.finish);
				*(current++) = w.value;
				k = w.finish;
			}
			update_symline();
		}

		nik_ce void update_production()
		{
			const Body & b = Base::production.body;
			update_pad(4);
			*(current++) = Base::front;
			update_space();
			*(current++) = (Base::word.value == '\0') ? '$' : Base::word.value;
			update_arrow();
			auto s = 6 - b.size;
			if (b.size == 0) *(current++) = 'e';
			else for (auto k = b.symbol; k != b.symbol + b.size; ++current, ++k) *current = *k;
			update_pad(s);
			update_newline();
		}

		nik_ce void update_end()
		{
			update_stack();
			update_tokens();
			update_endline();
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// generic assembly:

/***********************************************************************************************************************/

// derivation:

	struct T_generic_assembly_dpda
	{
		using T_pdtt = T_generic_assembly_pdtt;
		using T_ast  = T_generic_assembly_ast;

		template<auto static_src, auto Size>
		struct parser
		{
			using T_syntax		= TableOfContents<static_src>;
			nik_ces auto value      = GenericDPDA<T_pdtt, T_ast, T_syntax, static_src, Size>{};
		};

		template<auto SourceCallable, auto Size = 5'000>
		nik_ces auto parse = parser<_static_object_<SourceCallable>, Size>::value;
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

