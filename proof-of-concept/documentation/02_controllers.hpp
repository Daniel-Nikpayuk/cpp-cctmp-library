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

// (documentation) controllers:

namespace machine {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// lookup:

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

// chain:

/***********************************************************************************************************************/

// cctmp:

	template<auto... Vs>
	nik_ce auto U_pack_Vs						= cctmp::U_pack_Vs<Vs...>;

	template<typename... Ts>
	nik_ce auto U_pack_Ts						= cctmp::U_pack_Ts<Ts...>;

	using gcbool_type						= cctmp::gcbool_type;

	template<typename T, auto... Vs>
	nik_ce auto array						= cctmp::array<T, Vs...>;

	nik_ce auto _same_						= cctmp::_same_;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// subpose:

/***********************************************************************************************************************/

// controller:

	template<gindex_type length>
	struct T_chain_subpose_contr : public sequence<instr_type, length>
	{
		using base		= sequence<instr_type, length>;
		using cindex		= gcindex_type;

		gcbool_type *is_id;
		gindex_type arg_size;

		nik_ce T_chain_subpose_contr(gcbool_type *ii, cindex s) : base{}, is_id{ii}, arg_size{s}
		{
			add_initial_instrs   ();
			add_composand_instrs ();
			add_composer_instrs  ();
			add_halting_instrs   ();
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

		nik_ce void add_initial_instrs()
			{ T_chain_action<CAN::base, CAT::id>::template result<>(this); }

		nik_ce void add_composand_instrs()
		{
			for (gindex_type k = 0; k != arg_size; ++k)
				if (is_id[k]) add_id_composand_instr(k);
				else add_not_id_composand_instr(k);
		}

		nik_ce void add_id_composand_instr(cindex k)
			{ T_chain_action<CAN::non, CAT::arg>::template result<>(this, k); }

		nik_ce void add_not_id_composand_instr(cindex k)
			{ T_chain_action<CAN::list, CAT::arg>::template result<>(this, k, k); }

		nik_ce void add_composer_instrs()
			{ T_chain_action<CAN::list, CAT::non>::template result<>(this, arg_size); }

		nik_ce void add_halting_instrs()
		{
			T_chain_action<CAN::drop, CAT::halting>::template result<>(this, arg_size);
			T_chain_action<CAN::base, CAT::halting>::template result<>(this, CT::apply);
		}
	};

/***********************************************************************************************************************/

// static:

	template<auto is_id, auto n>
	struct T_chain_static_subpose_contr
	{
		nik_ces auto length = 3*n + 7; // needs to be confirmed.
		using type          = T_chain_subpose_contr<length>;
		nik_ces auto value  = type{is_id, n};

	}; template<auto is_id, auto n>
		nik_ce auto _chain_subpose_contr_ = U_store_T<T_chain_static_subpose_contr<is_id, n>>;

/***********************************************************************************************************************/

// interface:

	template<auto f, auto... gs>
	struct T_chain_subpose
	{
		nik_ces auto is_id = array<bool, eval<_same_, gs, _id_>...>;

		nik_ces auto contr  = _chain_subpose_contr_<is_id, sizeof...(gs)>;
		nik_ces auto lookup = U_pack_Vs<gs..., f>;

		template<typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto types = U_pack_Ts<Ts...>;

			return T_chain_start::template result<contr, lookup, types, Ts...>(vs...);
		}
	};

	// syntactic sugar:

		template<auto f, auto... gs>
		nik_ce auto _subpose_ = U_store_T<T_chain_subpose<f, gs...>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// subpose env:

/***********************************************************************************************************************/

// controller:

	template<gindex_type length>
	struct T_chain_subpose_env_contr : public sequence<instr_type, length>
	{
		using base		= sequence<instr_type, length>;
		using cindex		= gcindex_type;

		template<auto name, auto note>
		nik_ces auto action = chain_action_f<name, note, T_chain_subpose_env_contr>;

		template<auto name, auto note>
		nik_ces auto lookup_action = lookup_action_f<name, note, T_chain_subpose_env_contr>;

		gcbool_type *is_id;
		gindex_type arg_size;
		gindex_type subindex;
		gindex_type begin;
		gindex_type end;

		nik_ce T_chain_subpose_env_contr(gcbool_type *ii, cindex s, cindex b = 0, cindex e = 0) :
			base{}, is_id{ii}, arg_size{s}, subindex{}, begin{b}, end{e}
			{
				add_initial_instrs   ();
				add_composand_instrs ();
				add_composer_instrs  ();
				add_halting_instrs   ();

				add_lookup_contr     ();
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

		nik_ce void add_initial_instrs() { action<CAN::base, CAT::id>(this); }

		nik_ce void add_composand_instrs()
		{
			for (gindex_type k = 0; k != arg_size; ++k)
				if (is_id[k]) add_id_composand_instr(k);
				else add_not_id_composand_instr(k);
		}

		nik_ce void add_id_composand_instr    (cindex k) { action<CAN::non, CAT::arg>(this, k); }
		nik_ce void add_not_id_composand_instr(cindex k) { action<CAN::list, CAT::arg>(this, k, k); }

		nik_ce void add_composer_instrs()
		{
			subindex = 1 + 3*arg_size + 2 + 2 + 1;
			action<CAN::lookup, CAT::non>(this, arg_size + 1, subindex, arg_size);
		}

		nik_ce void add_halting_instrs()
		{
			action<CAN::drop, CAT::halting>(this, arg_size);
			action<CAN::base, CAT::halting>(this, CT::apply);
		}

		// lookup:

		nik_ce void add_lookup_contr()
		{
			lookup_action<LAN::base, LAN::id>(this);

			cindex halt = subindex + 4;
			cindex loop = subindex + 0;

			lookup_action<LAN::loop, LAN::id>(this, begin, end, halt, loop);

			lookup_action<LAN::halt, LAN::id>(this);
		}
	};

/***********************************************************************************************************************/

// static:

	template<auto str, auto is_id, auto n>
	struct T_chain_static_subpose_env_contr
	{
		nik_ces auto length = 3*n + 13; // needs to be confirmed.
		using type          = T_chain_subpose_env_contr<length>;
		nik_ces auto value  = type{is_id, n};

	}; template<auto str, auto is_id, auto n>
		nik_ce auto _chain_subpose_env_contr_ = U_store_T<T_chain_static_subpose_env_contr<str, is_id, n>>;

/***********************************************************************************************************************/

// interface:

	template<auto str, auto env, auto... gs>
	struct T_chain_subpose_env
	{
		nik_ces auto is_id = array<bool, eval<_same_, gs, _id_>...>;

		nik_ces auto contr  = _chain_subpose_env_contr_<str, is_id, sizeof...(gs)>;
		nik_ces auto lookup = U_pack_Vs<gs..., str, env>;

		template<typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto types = U_pack_Ts<Ts...>;

			return T_chain_start::template result<contr, lookup, types, Ts...>(vs...);
		}
	};

	// syntactic sugar:

		template<auto str, auto env, auto... gs>
		nik_ce auto _subpose_env_ = U_store_T<T_chain_subpose_env<str, env, gs...>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// argpose:

/***********************************************************************************************************************/

// controller:

	template<gindex_type length>
	struct T_chain_argpose_contr : public sequence<instr_type, length>
	{
		using base		= sequence<instr_type, length>;
		using cindex		= gcindex_type;

		cindex *poses;
		gindex_type pos_size;
		gindex_type arg_size;

		nik_ce T_chain_argpose_contr(cindex *ps, cindex p, cindex s) :
			base{}, poses{ps}, pos_size{p}, arg_size{s}
			{
				add_initial_instrs   ();
				add_composand_instrs ();
				add_composer_instrs  ();
				add_halting_instrs   ();
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

		nik_ce void add_initial_instrs()
			{ T_chain_action<CAN::base, CAT::id>::template result<>(this); }

		nik_ce void add_composand_instrs()
			{ for (gindex_type k = 0; k != pos_size; ++k) add_id_composand_instr(k); }

		nik_ce void add_id_composand_instr(cindex k)
			{ T_chain_action<CAN::non, CAT::arg>::template result<>(this, poses[k]); }

		nik_ce void add_composer_instrs()
			{ T_chain_action<CAN::list, CAT::non>::template result<>(this, 0); }

		nik_ce void add_halting_instrs()
		{
			T_chain_action<CAN::drop, CAT::halting>::template result<>(this, arg_size);
			T_chain_action<CAN::base, CAT::halting>::template result<>(this, CT::apply);
		}
	};

/***********************************************************************************************************************/

// static:

	template<auto poses, auto pos_size, auto s>
	struct T_chain_static_argpose_contr
	{
		nik_ces auto length = 3*pos_size + 8; // needs to be confirmed.
		using type          = T_chain_argpose_contr<length>;
		nik_ces auto value  = type{poses, pos_size, s};

	}; template<auto poses, auto pos_size, auto s>
		nik_ce auto _chain_argpose_contr_ = U_store_T<T_chain_static_argpose_contr<poses, pos_size, s>>;

/***********************************************************************************************************************/

// interface:

	template<auto f, auto poses, auto pos_size>
	struct T_chain_argpose
	{
		template<auto s>
		nik_ces auto contr  = _chain_argpose_contr_<poses, pos_size, s>;
		nik_ces auto lookup = U_pack_Vs<f>;

		template<typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto types = U_pack_Ts<Ts...>;

			return T_chain_start::template result<contr<sizeof...(Ts)>, lookup, types, Ts...>(vs...);
		}
	};

	// syntactic sugar:

		template<auto f, auto... poses>
		nik_ce auto _argpose_ = U_store_T<T_chain_argpose<f, array<gindex_type, poses...>, sizeof...(poses)>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// arg at:

/***********************************************************************************************************************/

// controller:

	template<gindex_type length>
	struct T_chain_arg_at_contr : public sequence<instr_type, length>
	{
		using base		= sequence<instr_type, length>;
		using cindex		= gcindex_type;

		gcbool_type is_id;
		gindex_type pos_at;
		gindex_type arg_size;

		nik_ce T_chain_arg_at_contr(gcbool_type ii, cindex p, cindex s) :
			base{}, is_id{ii}, pos_at{p}, arg_size{s}
			{
				add_initial_instrs  ();
				add_composer_instrs ();
				add_halting_instrs  ();
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

		nik_ce void add_initial_instrs()
			{ T_chain_action<CAN::base, CAT::id>::template result<>(this); }

		nik_ce void add_composer_instrs()
		{
			if (is_id) add_id_composer_instr(pos_at);
			else add_not_id_composer_instr(pos_at);
		}

		nik_ce void add_id_composer_instr(cindex k)
			{ T_chain_action<CAN::non, CAT::arg>::template result<>(this, k); }

		nik_ce void add_not_id_composer_instr(cindex k)
			{ T_chain_action<CAN::list, CAT::arg>::template result<>(this, 0, k); }

		nik_ce void add_halting_instrs()
		{
			T_chain_action<CAN::drop, CAT::halting>::template result<>(this, arg_size);
			T_chain_action<CAN::base, CAT::halting>::template result<>(this, CT::first);
		}
	};

/***********************************************************************************************************************/

// static:

	template<auto is_id, auto n, auto s>
	struct T_chain_static_arg_at_contr
	{
		nik_ces auto length = 3*s + 7; // needs to be confirmed.
		nik_ces auto value  = T_chain_arg_at_contr<length>{is_id, n, s};
		using type          = decltype(value);

	}; template<auto is_id, auto n, auto s>
		nik_ce auto _chain_arg_at_contr_ = U_store_T<T_chain_static_arg_at_contr<is_id, n, s>>;

/***********************************************************************************************************************/

// interface:

	template<auto n, auto f = _id_>
	struct T_chain_arg_at
	{
		nik_ces auto is_id = eval<_same_, f, _id_>;

		template<auto s>
		nik_ces auto contr  = _chain_arg_at_contr_<is_id, n, s>;
		nik_ces auto lookup = U_pack_Vs<f>;

		template<typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto types = U_pack_Ts<Ts...>;

			return T_chain_start::template result<contr<sizeof...(Ts)>, lookup, types, Ts...>(vs...);
		}
	};

	// syntactic sugar:

		template<auto n, auto f = _id_>
		nik_ce auto _arg_at_ = U_store_T<T_chain_arg_at<n, f>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace machine

