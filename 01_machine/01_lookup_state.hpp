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

// lookup state:

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

	template<auto U>
	nik_ce auto & member_value_U			= cctmp::member_value_U<U>;

	using gkey_type					= cctmp::gkey_type;
	using gindex_type				= cctmp::gindex_type;
	using gcindex_type				= cctmp::gcindex_type;

	template<typename T, auto S>
	using sequence					= cctmp::sequence<T, S>;

	using instr_type				= cctmp::instr_type;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// space:

	template<gkey_type, gkey_type, auto...> struct T_lookup;

/***********************************************************************************************************************/

// names:

	struct LookupName
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.
			halt, jump, contains,
			dimension
		};
	};

	using LN = LookupName;

/***********************************************************************************************************************/

// notes:

	struct LookupNote
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.
			empty, map, loop,
			dimension
		};
	};

	using LT = LookupNote;

/***********************************************************************************************************************/

// instructions:

	using LI = cctmp::Instr;

/***********************************************************************************************************************/

// dispatch:

	template<auto static_contr, auto _index = 0, auto _match = false, auto _key = 0>
	struct LookupDispatch
	{
		nik_ces auto & contr = member_value_U<static_contr>;
		using cindex         = gcindex_type;

		// defaults:

			nik_ces gindex_type initial_index = _index;
			nik_ces gindex_type initial_match = _match;
			nik_ces gindex_type initial_key   = _key;

		// accessors:

			nik_ces const auto & instr (cindex i) { return contr[i]; }
			nik_ces gindex_type value  (cindex i, cindex n) { return contr[i][n]; }

			nik_ces gindex_type pos (cindex i) { return value(i, LI::pos); }
			nik_ces gindex_type num (cindex i) { return value(i, LI::num); }

		// navigators:

			nik_ces gindex_type next_offset (cindex i) { return value(i, LI::next); }
			nik_ces gindex_type next_index  (cindex i) { return i + next_offset(i); }

			nik_ces gkey_type next_name (cindex i) { return value(next_index(i), LI::name); }
			nik_ces gkey_type next_note (cindex i) { return value(next_index(i), LI::note); }
	};

	template<auto static_contr, auto _index = 0, auto _match = false, auto _key = 0>
	using LD = LookupDispatch<static_contr, _index, _match, _key>;

/***********************************************************************************************************************/

// start:

	struct T_lookup_start
	{
		template<auto c, auto s, typename... Fs>
		nik_ces auto result(Fs... fs)
		{
			nik_ce auto i = LD<c>::initial_index;
			nik_ce auto m = LD<c>::initial_match;
			nik_ce auto k = LD<c>::initial_key;

			return NIK_LOOKUP_TS(c, i, s, m, k, Fs...)(fs...);
		}
	};

/***********************************************************************************************************************/

// istart:

	struct T_lookup_istart
	{
		template<auto c, auto i, auto s, typename... Fs>
		nik_ces auto result(Fs... fs)
		{
			nik_ce auto m = LD<c>::initial_match;
			nik_ce auto k = LD<c>::initial_key;

			return NIK_LOOKUP_TS(c, i, s, m, k, Fs...)(fs...);
		}
	};

/***********************************************************************************************************************/

// default:

	nik_ce void _not_found_() { }

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// halt:

/***********************************************************************************************************************/

// empty:

	template<auto... filler>
	struct T_lookup<LN::halt, LT::empty, filler...>
	{
		template<NIK_LOOKUP_PARAMS(c, i, s, m, k), typename... Fs>
		nik_ces auto result(Fs... fs) { return _not_found_; }
	};

/***********************************************************************************************************************/

// map:

	template<auto... filler>
	struct T_lookup<LN::halt, LT::map, filler...>
	{
		template<NIK_LOOKUP_PARAMS(c, i, s, m, k), typename F, typename... Fs>
		nik_ces auto result(F f, Fs... fs) { return member_value_U<U_restore_T<F>>.template map<k>(); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// jump:

/***********************************************************************************************************************/

// empty:

	template<auto... filler>
	struct T_lookup<LN::jump, LT::empty, filler...>
	{
		template<NIK_LOOKUP_PARAMS(c, i, s, m, k), typename... Fs>
		nik_ces auto result(Fs... fs)
		{
			nik_ce auto empty = (sizeof...(Fs) == 0);
			nik_ce auto ni    = empty ? LD<c>::pos(i) : i;

			return NIK_LOOKUP_TS(c, ni, s, m, k, Fs...)(fs...);
		}
	};

/***********************************************************************************************************************/

// loop:

	template<auto... filler>
	struct T_lookup<LN::jump, LT::loop, filler...>
	{
		template<NIK_LOOKUP_PARAMS(c, i, s, m, k), typename F, typename... Fs>
		nik_ces auto result(F f, Fs... fs)
		{
			nik_ce auto ni = LD<c>::pos(i);

			if nik_ce (m) return NIK_LOOKUP_2TS(c, i, s, m, k, F, Fs...)(f, fs...);
			else          return NIK_LOOKUP_TS(c, ni, s, m, k, Fs...)(fs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// contains:

/***********************************************************************************************************************/

// id:

	template<auto... filler>
	struct T_lookup<LN::contains, LT::id, filler...>
	{
		template<NIK_LOOKUP_PARAMS(c, i, s, m, k), typename F, typename... Fs>
		nik_ces auto result(F f, Fs... fs)
		{
			nik_ce auto pos   = LD<c>::pos(i);
			nik_ce auto num   = LD<c>::num(i);
			nik_ce auto j     = member_value_U<s>.cselect(pos, num);
			nik_ce auto iter  = member_value_U<U_restore_T<F>>.contains(j);
			nik_ce auto nm    = iter.not_end();
			nik_ce auto nk    = iter.left_size();

			return NIK_LOOKUP_2TS(c, i, s, nm, nk, F, Fs...)(f, fs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace machine

