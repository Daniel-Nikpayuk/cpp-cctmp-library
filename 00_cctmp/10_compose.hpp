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

// compose:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// instr:

	using chain_instr_type = sequence<gindex_type, static_cast<gindex_type>(CI::dimension)>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// subpose:

/***********************************************************************************************************************/

// controller:

	template<gindex_type length>
	struct T_chain_subpose_contr : public sequence<chain_instr_type, length>
	{
		using subinstr_type	= sequence<gindex_type, static_cast<gindex_type>(CAI::dimension)>;
		using base		= sequence<chain_instr_type, length>;
		using cindex		= gcindex_type;

		gcbool_type *is_id;
		gindex_type size_of;
		gindex_type _2_N;
		subinstr_type ins;

		nik_ce T_chain_subpose_contr(gcbool_type *ii, cindex s, cindex b) :
			base{}, is_id{ii}, size_of{s}, _2_N{b}
			{
				ins.fullsize();

				add_initial_instrs   ();
				add_padding_instrs   ();
				add_composand_instrs ();
				add_composer_instrs  ();
				add_halting_instrs   ();
			}

		nik_ce void add_instr(cindex name, cindex note, cindex pos = 0, cindex num = 0)
		{
			base::end()->push(name);
			base::end()->push(note);
			base::end()->push(pos);
			base::end()->push(num);

			base::upsize();
		}

		nik_ce void add_initial_instrs()
			{ T_chain_action<CAN::base, CAT::id>::template result<>(this, ins); }

		nik_ce void add_padding_instrs()
		{
			gcindex_type mod  = size_of % _2_N;
			gcindex_type tail = mod ? mod : _2_N;
			ins[CAI::pos0]    = _2_N - tail;

			T_chain_action<CAN::base, CAT::padding>::template result<>(this, ins);
		}

		nik_ce void add_composand_instrs()
		{
			for (gindex_type k = 0; k != size_of; ++k)
				if (is_id[k]) add_id_composand_instr(k);
				else add_not_id_composand_instr(k);
		}

		nik_ce void add_id_composand_instr(gcindex_type k)
		{
			ins[CAI::pos0] = k;

			T_chain_action<CAN::non, CAT::arg>::template result<>(this, ins);
		}

		nik_ce void add_not_id_composand_instr(gcindex_type k)
		{
			ins[CAI::pos0] = k;
			ins[CAI::pos1] = k;

			T_chain_action<CAN::lup, CAT::arg>::template result<>(this, ins);
		}

		nik_ce void add_composer_instrs()
		{
			ins[CAI::pos0] = size_of;

			T_chain_action<CAN::lup, CAT::non>::template result<>(this, ins);
		}

		nik_ce void add_halting_instrs()
		{
			gcindex_type cycle = size_of / _2_N;

			ins[CAI::pos0] = _2_N * (cycle + 1);
			T_chain_action<CAN::pose, CAT::halting>::template result<>(this, ins);

			ins[CAI::pos0] = CT::apply;
			T_chain_action<CAN::base, CAT::halting>::template result<>(this, ins);
		}
	};

/***********************************************************************************************************************/

// static:

	template<auto is_id, auto n, auto _2_N>
	struct T_chain_static_subpose_contr
	{
		nik_ces auto length = 3*n + 7; // needs to be confirmed.
		nik_ces auto value  = T_chain_subpose_contr<length>{is_id, n, _2_N};
		using type          = decltype(value);

	}; template<auto is_id, auto n, auto _2_N = _2_6>
		nik_ce auto _chain_subpose_contr_ = U_store_T<T_chain_static_subpose_contr<is_id, n, _2_N>>;

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

// argpose:

/***********************************************************************************************************************/

// controller:

	template<gindex_type length>
	struct T_chain_argpose_contr : public sequence<chain_instr_type, length>
	{
		using subinstr_type	= sequence<gindex_type, static_cast<gindex_type>(CAI::dimension)>;
		using base		= sequence<chain_instr_type, length>;
		using cindex		= gcindex_type;

		cindex *poses;
		gindex_type pos_size;
		gindex_type size_of;
		gindex_type _2_N;
		subinstr_type ins;

		nik_ce T_chain_argpose_contr(cindex *ps, cindex p, cindex s, cindex b) :
			base{}, poses{ps}, pos_size{p}, size_of{s}, _2_N{b}
			{
				ins.fullsize();

				add_initial_instrs   ();
				add_padding_instrs   ();
				add_composand_instrs ();
				add_composer_instrs  ();
				add_halting_instrs   ();
			}

		nik_ce void add_instr(cindex name, cindex note, cindex pos = 0, cindex num = 0)
		{
			base::end()->push(name);
			base::end()->push(note);
			base::end()->push(pos);
			base::end()->push(num);

			base::upsize();
		}

		nik_ce void add_initial_instrs()
			{ T_chain_action<CAN::base, CAT::id>::template result<>(this, ins); }

		nik_ce void add_padding_instrs()
		{
			gcindex_type mod  = size_of % _2_N;
			gcindex_type tail = mod ? mod : _2_N;
			ins[CAI::pos0]    = _2_N - tail;

			T_chain_action<CAN::base, CAT::padding>::template result<>(this, ins);
		}

		nik_ce void add_composand_instrs()
			{ for (gindex_type k = 0; k != pos_size; ++k) add_id_composand_instr(k); }

		nik_ce void add_id_composand_instr(gcindex_type k)
		{
			ins[CAI::pos0] = poses[k];

			T_chain_action<CAN::non, CAT::arg>::template result<>(this, ins);
		}

		nik_ce void add_composer_instrs()
		{
			ins[CAI::pos0] = 0;

			T_chain_action<CAN::lup, CAT::non>::template result<>(this, ins);
		}

		nik_ce void add_halting_instrs()
		{
			gcindex_type cycle = size_of / _2_N;

			ins[CAI::pos0] = _2_N * (cycle + 1);
			T_chain_action<CAN::pose, CAT::halting>::template result<>(this, ins);

			ins[CAI::pos0] = CT::apply;
			T_chain_action<CAN::base, CAT::halting>::template result<>(this, ins);
		}
	};

/***********************************************************************************************************************/

// static:

	template<auto poses, auto pos_size, auto s, auto _2_N>
	struct T_chain_static_argpose_contr
	{
		nik_ces auto length = 3*pos_size + 8; // needs to be confirmed.
		nik_ces auto value  = T_chain_argpose_contr<length>{poses, pos_size, s, _2_N};
		using type          = decltype(value);

	}; template<auto poses, auto pos_size, auto s, auto _2_N = _2_6>
		nik_ce auto _chain_argpose_contr_ = U_store_T<T_chain_static_argpose_contr<poses, pos_size, s, _2_N>>;

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
	struct T_chain_arg_at_contr : public sequence<chain_instr_type, length>
	{
		using subinstr_type	= sequence<gindex_type, static_cast<gindex_type>(CAI::dimension)>;
		using base		= sequence<chain_instr_type, length>;
		using cindex		= gcindex_type;

		gcbool_type is_id;
		gindex_type pos_at;
		gindex_type size_of;
		gindex_type _2_N;
		subinstr_type ins;

		nik_ce T_chain_arg_at_contr(gcbool_type ii, cindex p, cindex s, cindex b) :
			base{}, is_id{ii}, pos_at{p}, size_of{s}, _2_N{b}
			{
				ins.fullsize();

				add_initial_instrs  ();
				add_padding_instrs  ();
				add_composer_instrs ();
				add_halting_instrs  ();
			}

		nik_ce void add_instr(cindex name, cindex note, cindex pos = 0, cindex num = 0)
		{
			base::end()->push(name);
			base::end()->push(note);
			base::end()->push(pos);
			base::end()->push(num);

			base::upsize();
		}

		nik_ce void add_initial_instrs()
			{ T_chain_action<CAN::base, CAT::id>::template result<>(this, ins); }

		nik_ce void add_padding_instrs()
		{
			gcindex_type mod  = size_of % _2_N;
			gcindex_type tail = mod ? mod : _2_N;
			ins[CAI::pos0]    = _2_N - tail;

			T_chain_action<CAN::base, CAT::padding>::template result<>(this, ins);
		}

		nik_ce void add_composer_instrs()
		{
			if (is_id) add_id_composer_instr(pos_at);
			else add_not_id_composer_instr(pos_at);
		}

		nik_ce void add_id_composer_instr(gcindex_type k)
		{
			ins[CAI::pos0] = k;

			T_chain_action<CAN::non, CAT::arg>::template result<>(this, ins);
		}

		nik_ce void add_not_id_composer_instr(gcindex_type k)
		{
			ins[CAI::pos0] = 0;
			ins[CAI::pos1] = k;

			T_chain_action<CAN::lup, CAT::arg>::template result<>(this, ins);
		}

		nik_ce void add_halting_instrs()
		{
			gcindex_type cycle = size_of / _2_N;

			ins[CAI::pos0] = _2_N * (cycle + 1);
			T_chain_action<CAN::pose, CAT::halting>::template result<>(this, ins);

			ins[CAI::pos0] = CT::first;
			T_chain_action<CAN::base, CAT::halting>::template result<>(this, ins);
		}
	};

/***********************************************************************************************************************/

// static:

	template<auto is_id, auto n, auto s, auto _2_N>
	struct T_chain_static_arg_at_contr
	{
		nik_ces auto length = 3*s + 7; // needs to be confirmed.
		nik_ces auto value  = T_chain_arg_at_contr<length>{is_id, n, s, _2_N};
		using type          = decltype(value);

	}; template<auto is_id, auto n, auto s, auto _2_N = _2_6>
		nik_ce auto _chain_arg_at_contr_ = U_store_T<T_chain_static_arg_at_contr<is_id, n, s, _2_N>>;

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

} // namespace cctmp

