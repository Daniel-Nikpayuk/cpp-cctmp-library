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

// lookup compose:

namespace machine {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// env(ironment):

/***********************************************************************************************************************/

// controller:

	template<gindex_type length = 7>
	struct T_lookup_env_contr : public sequence<instr_type, length>
	{
		using base		= sequence<instr_type, length>;
		using cindex		= gcindex_type;

		template<auto name, auto note>
		nik_ces auto action = lookup_action_f<name, note, T_lookup_env_contr>;

		cindex begin;
		cindex end;

		nik_ce T_lookup_env_contr(cindex b, cindex e) : begin{b}, end{e}
		{
			add_initial_instrs ();
			add_looping_instrs ();
			add_halting_instrs ();
		}

		nik_ce void add_instr(cindex name, cindex note, cindex next = 1, cindex pos = 0, cindex num = 0)
		{
			base::end()->push(name);
			base::end()->push(note);
			base::end()->push(next);
			base::end()->push(pos);
			base::end()->push(num);

			base::upsize();
		}

		nik_ce void add_initial_instrs() { action<LAN::base, LAN::id>(this); }

		nik_ce void add_looping_instrs()
		{
			cindex halt = 4;
			cindex loop = 0;

			action<LAN::loop, LAN::id>(this, begin, end, halt, loop);
		}

		nik_ce void add_halting_instrs() { action<LAN::halt, LAN::id>(this); }
	};

/***********************************************************************************************************************/

// static:

	template<auto begin, auto end>
	struct T_lookup_env_static_contr
	{
		using type          = T_lookup_env_contr<>;
		nik_ces auto value  = type{begin, end};

	}; template<auto begin, auto end>
		nik_ce auto _lookup_env_contr_ = U_store_T<T_lookup_env_static_contr<begin, end>>;

/***********************************************************************************************************************/

// interface:

	template<auto str>
	struct T_lookup_env
	{
		nik_ces auto contr = _lookup_env_contr_<0, 0>;

		template<typename... Fs>
		nik_ces auto result(Fs... fs)
			{ return T_lookup_start::template result<contr, str, Fs...>(fs...); }
	};

	// syntactic sugar:

		template<auto str>
		nik_ce auto _lookup_env_ = U_store_T<T_lookup_env<str>>;

		template<auto str, auto... fs>
		nik_ce auto lookup_env(nik_avp(T_pack_Vs<fs...>*))
			{ return T_lookup_env<str>::template result<>(fs...); }

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace machine

