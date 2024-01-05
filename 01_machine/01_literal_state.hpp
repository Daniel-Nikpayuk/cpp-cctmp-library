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

// literal state:

namespace machine {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// cctmp:

	template<typename T>
	nik_ce auto U_store_T				= cctmp::U_store_T<T>;

	template<typename T>
	nik_ce auto U_restore_T				= cctmp::U_restore_T<T>;

	template<auto... Vs>
	using T_pack_Vs					= cctmp::T_pack_Vs<Vs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// space:

	template<gkey_type, gkey_type, auto...> struct T_literal;

/***********************************************************************************************************************/

// names:

	struct LiteralName
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.
			halt, resolve,
			dimension
		};
	};

	using LN = LiteralName;

/***********************************************************************************************************************/

// notes:

	struct LiteralNote
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.
			first, boolean, number, character, string,
			dimension
		};
	};

	using LT = LiteralNote;

/***********************************************************************************************************************/

// instructions:

	using LI = cctmp::Instr;

/***********************************************************************************************************************/

// dispatch:

	template<auto static_contr, auto _index = 0>
	struct LiteralDispatch : public MachineDispatch<static_contr, LI, _index> { };

	template<auto static_contr, auto _index = 0>
	using LD = LiteralDispatch<static_contr, _index>;

/***********************************************************************************************************************/

// cons:

	template<auto s, auto c, auto i>
	struct T_literal_cons
	{
		template<typename... Ts>
		nik_ces auto result(Ts... vs) { return NIK_LITERAL_TS(s, c, i, Ts...)(vs...); }

	}; template<auto s, auto c, auto i>
		nik_ce auto U_literal_cons = U_store_T<T_literal_cons<s, c, i>>;

/***********************************************************************************************************************/

// start:

	struct T_literal_start
	{
		template<auto s, auto c, typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto i = LD<c>::initial_index;

			return NIK_LITERAL_TS(s, c, i, Ts...)(vs...);
		}
	};

/***********************************************************************************************************************/

// istart:

	struct T_literal_istart
	{
		template<auto s, auto c, auto i, typename... Ts>
		nik_ces auto result(Ts... vs) { return NIK_LITERAL_TS(s, c, i, Ts...)(vs...); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// halt:

/***********************************************************************************************************************/

// first:

	template<auto... filler>
	struct T_literal<LN::halt, LT::first, filler...>
	{
		template<NIK_LITERAL_PARAMS(s, c, i), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) { return v; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// literal:

/***********************************************************************************************************************/

// boolean:

	template<auto... filler>
	struct T_literal<LN::resolve, LT::boolean, filler...>
	{
		using cbool = gcbool_type;

		template<NIK_LITERAL_PARAMS(s, c, i), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			auto  k = member_value_U<s>.cbegin() + LD<c>::pos(i) + 1;
			cbool v = (*k == 'r') || (*k == 't');

			return NIK_LITERAL_2TS(s, c, i, cbool, Ts...)(v, vs...);
		}
	};

/***********************************************************************************************************************/

// number:

	template<auto... filler>
	struct T_literal<LN::resolve, LT::number, filler...>
	{
		using size_type  = gindex_type;
		using csize_type = size_type const;

		template<NIK_LITERAL_PARAMS(s, c, i), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			auto b = member_value_U<s>.cbegin() + LD<c>::pos(i);
			auto e = member_value_U<s>.cbegin() + LD<c>::num(i);

			size_type num = 0;

			for (size_type dig = 0, exp = 1; e != b; exp *= 10)
			{
				dig  = (*--e) - '0';
				num += dig * exp;
			}

			return NIK_LITERAL_2TS(s, c, i, csize_type, Ts...)(static_cast<csize_type>(num), vs...);
		}
	};

/***********************************************************************************************************************/

// character:

	template<auto... filler>
	struct T_literal<LN::resolve, LT::character, filler...>
	{
		using cchar = gcchar_type;

		template<NIK_LITERAL_PARAMS(s, c, i), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			auto  b = member_value_U<s>.cbegin() + LD<c>::pos(i) + 1;
			cchar v = *b;

			return NIK_LITERAL_2TS(s, c, i, cchar, Ts...)(v, vs...);
		}
	};

/***********************************************************************************************************************/

// string:

	template<auto... filler>
	struct T_literal<LN::resolve, LT::string, filler...>
	{
		using size_type = gindex_type;

		template<NIK_LITERAL_PARAMS(s, c, i), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto b = member_value_U<s>.cbegin() + LD<c>::pos(i);
			nik_ce auto e = member_value_U<s>.cbegin() + LD<c>::num(i);

			using seq_type  = sequence<char, (e - b)>;
			using cseq_type = seq_type const;

			seq_type v;
			for (auto k = b; k != e; ++k) v.push(*k);

			return NIK_LITERAL_2TS(s, c, i, cseq_type, Ts...)(static_cast<cseq_type>(v), vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace machine

