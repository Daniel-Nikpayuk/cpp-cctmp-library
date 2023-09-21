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

// lookup:

namespace chord {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

	template<template<auto...> typename B>
	nik_ce auto U_store_B					= cctmp::U_store_B<B>;

	template<auto... Vs>
	nik_ce auto to_list_					= cctmp::to_list_<Vs...>;

	template<auto... Vs>
	nik_ce auto car_					= cctmp::car_<Vs...>;

	template<auto... Vs>
	nik_ce auto cadr_					= cctmp::cadr_<Vs...>;

	template<auto... Vs>
	nik_ce auto insert_					= cctmp::insert_<Vs...>;

	template<auto... Vs>
	nik_ce auto replace_					= cctmp::replace_<Vs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// lookup:

/***********************************************************************************************************************/

// env:

	template<auto static_parsed, auto env>
	struct T_inductor_env
	{
		nik_ces auto & parsed = member_value_U<static_parsed>;
		using T_lookup_frame  = cctmp::T_lookup<env>;

		template<auto n, auto m, auto l, auto t>
		nik_ces auto result()
		{
			nik_ce auto & entry = parsed.link_entry(n, m);
			nik_ce auto record  = T_lookup_frame::find_frame(entry);

			return T_lookup_frame::template map<record.v0, record.v1>();
		}

	}; template<auto static_parsed, auto env>
		nik_ce auto U_inductor_env = U_store_T<T_inductor_env<static_parsed, env>>;

/***********************************************************************************************************************/

// cycle:

	template<auto static_parsed>
	struct T_inductor_cycle
	{
		nik_ces auto & parsed = member_value_U<static_parsed>;

		template<auto n, auto m, auto l, auto t>
		nik_ces auto result()
		{
			nik_ce auto & entry = parsed.link_entry(n, m);

			return cctmp::_id_;
		}

	}; template<auto static_parsed>
		nik_ce auto U_inductor_cycle = U_store_T<T_inductor_cycle<static_parsed>>;

		//	else if nik_ce (Sign::is_cycle(sign))
		//	{
		//		nik_ce auto index = parsed.link_entry_index(n, m);
		//		nik_ce auto token = parsed.cycle_level[index].token;
		//		nik_ce auto size  = parsed.cycle_level[index].interval.size();
		//		nik_ce auto notes = segment_<size>;
		//		nik_ce auto types = U_restore_T<decltype(U)>;
		//		using T_cycle     = T_cycle_dispatch<token, static_parsed, this_f, env>;

		//		return T_cycle::template result<index, types>(notes);
		//	}

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// controller:

/***********************************************************************************************************************/

// interface:

	template<auto static_parsed, gindex_type size>
	struct T_lookup_contr : public cctmp::sequence<chain_instr_type, size>
	{
		nik_ces gindex_type instr_size	= CAI::dimension;
		using subinstr_type		= cctmp::sequence<gindex_type, instr_size>;
		using base			= cctmp::sequence<chain_instr_type, size>;
		using cindex			= gcindex_type;

		nik_ces auto & parsed		= member_value_U<static_parsed>;

		cindex arg_size;
		cindex line_size;
		cindex _2_N;

		cindex line_pos;
		cindex env_pos;
		cindex mor_pos;
		cindex cyc_pos;
		cindex lup_pos;

		subinstr_type ins;

		nik_ce T_lookup_contr
		(
			cindex as, cindex ls, cindex bs, cindex lp, cindex ep, cindex mp, cindex cp, cindex rp

		) : base{}, arg_size{as}, line_size{ls}, _2_N{bs},
			line_pos{lp}, env_pos{ep}, mor_pos{mp}, cyc_pos{cp}, lup_pos{rp}
				{ ins.fullsize(); }

		nik_ce void add_instr(cindex name, cindex note, cindex pos = 0, cindex num = 0)
		{
			base::end()->push(name);
			base::end()->push(note);
			base::end()->push(pos);
			base::end()->push(num);

			base::upsize();
		}

		// initial:

			nik_ce void add_initial_instrs()
				{ T_chain_action<CAN::base, CAT::id>::template result<>(this, ins); }

		// padding:

			nik_ce void add_padding_instrs()
			{
				cindex mod     = arg_size % _2_N;
				cindex tail    = mod ? mod : _2_N;
				ins[CAI::pos0] = _2_N - tail;

				T_chain_action<CAN::base, CAT::padding>::template result<>(this, ins);
			}

		// composand:

			nik_ce void add_composand_instrs(cindex init_pos = 1)
			{
				for (gindex_type ent_pos = init_pos; ent_pos != line_size; ++ent_pos)
					dispatch_composand_instrs(ent_pos);
			}

			nik_ce void dispatch_composand_instrs(cindex ent_pos)
			{
				cindex sign = parsed.link_entry_sign(line_pos, ent_pos);

				if      (Sign::is_env(sign)  ) add_env_composand_instr   (ent_pos);
				else if (Sign::is_morph(sign)) add_morph_composand_instr (ent_pos);
				else if (Sign::is_cycle(sign)) add_cycle_composand_instr (ent_pos);
				else                           add_arg_composand_instr   (ent_pos);
			}

			nik_ce void add_ext_composand_instr(cindex look_pos, cindex row_pos, cindex col_pos)
			{
				ins[CAI::pos0] = look_pos;
				ins[CAI::pos1] = row_pos;
				ins[CAI::pos2] = col_pos;

				T_chain_action<CAN::non, CAT::ext>::template result<>(this, ins);
			}

			nik_ce void add_env_composand_instr(cindex ent_pos)
				{ add_ext_composand_instr(env_pos, line_pos, ent_pos); }

			nik_ce void add_morph_composand_instr(cindex ent_pos)
				{ add_ext_composand_instr(mor_pos, parsed.link_entry_index(line_pos, ent_pos), 0); }

			nik_ce void add_cycle_composand_instr(cindex ent_pos)
				{ add_ext_composand_instr(cyc_pos, parsed.link_entry_index(line_pos, ent_pos), 0); }

			nik_ce void add_arg_composand_instr(cindex ent_pos)
			{
				ins[CAI::pos0] = parsed.link_entry_index(line_pos, ent_pos);

				T_chain_action<CAN::non, CAT::arg>::template result<>(this, ins);
			}

		// composer:

			nik_ce void add_composer_instrs(cindex ent_pos = 0)
			{
				cindex sign = parsed.link_entry_sign(line_pos, ent_pos);

				if      (Sign::is_env(sign)    ) add_env_composer_instr   (ent_pos);
				else if (Sign::is_morph(sign)  ) add_morph_composer_instr (ent_pos);
				else if (Sign::is_cycle(sign)  ) add_cycle_composer_instr (ent_pos);
				else if (Sign::is_recurse(sign)) add_lup_composer_instr   (       );
				else                             add_arg_composer_instr   (ent_pos);
			}

			nik_ce void add_ext_composer_instr(cindex look_pos, cindex row_pos, cindex col_pos)
			{
				ins[CAI::pos0] = look_pos;
				ins[CAI::pos1] = row_pos;
				ins[CAI::pos2] = col_pos;

				T_chain_action<CAN::ext, CAT::non>::template result<>(this, ins);
			}

			nik_ce void add_env_composer_instr(cindex ent_pos)
				{ add_ext_composer_instr(env_pos, line_pos, ent_pos); }

			nik_ce void add_morph_composer_instr(cindex ent_pos)
				{ add_ext_composer_instr(mor_pos, parsed.link_entry_index(line_pos, ent_pos), 0); }

			nik_ce void add_cycle_composer_instr(cindex ent_pos)
				{ add_ext_composer_instr(cyc_pos, parsed.link_entry_index(line_pos, ent_pos), 0); }

			nik_ce void add_lup_composer_instr()
			{
				ins[CAI::pos0] = lup_pos;

				T_chain_action<CAN::lup, CAT::non>::template result<>(this, ins);
			}

			nik_ce void add_arg_composer_instr(cindex ent_pos)
			{
				ins[CAI::pos0] = parsed.link_entry_index(line_pos, ent_pos);

				T_chain_action<CAN::arg, CAT::non>::template result<>(this, ins);
			}

		// halting:

			nik_ce void add_halting_instrs(cindex note)
			{
				cindex cycle = arg_size / _2_N;

				ins[CAI::pos0] = _2_N * (cycle + 1);
				T_chain_action<CAN::pose, CAT::halting>::template result<>(this, ins);

				ins[CAI::pos0] = note;
				T_chain_action<CAN::base, CAT::halting>::template result<>(this, ins);
			}
	};

/***********************************************************************************************************************/

// static:

	template
	<
		template<auto...> typename Contr, auto static_parsed,
		auto line_pos, auto arg_size, auto line_size, auto size, auto _2_N = _2_6
	>
	struct T_slookup_contr
	{
		using type		= Contr<static_parsed, size>;

		nik_ces auto lup_pos	= 0;
		nik_ces auto env_pos	= 1;
		nik_ces auto mor_pos	= 2;
		nik_ces auto cyc_pos	= 3;
		nik_ces auto value	= type{arg_size, line_size, _2_N, line_pos, env_pos, mor_pos, cyc_pos, lup_pos};
	};

	// syntactic sugar:

		template
		<
			template<auto...> typename Contr, auto static_parsed,
			auto line_pos, auto arg_size, auto line_size, auto size, auto _2_N = _2_6
		>
		nik_ce auto U_slookup_contr = U_store_T
		<
			T_slookup_contr<Contr, static_parsed, line_pos, arg_size, line_size, size, _2_N>
		>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// swap:

/***********************************************************************************************************************/

// controller:

	template<auto static_parsed, gindex_type size>
	struct T_lookup_swap_contr : public T_lookup_contr<static_parsed, size>
	{
		using base   = T_lookup_contr<static_parsed, size>;
		using cindex = typename base::cindex;

		nik_ce T_lookup_swap_contr
		(
			cindex as, cindex ls, cindex bs, cindex lp, cindex ep, cindex mp, cindex cp, cindex rp

		) : base{as, ls, bs, lp, ep, mp, cp, rp}
		{
			base::add_initial_instrs   ( );
			base::add_padding_instrs   ( );
			base::add_composand_instrs ( );
			base::add_composer_instrs  (1);
			base::add_halting_instrs   (CT::apply);
		}

		nik_ce void add_composand_instrs()
		{
			base::dispatch_composand_instrs(0);
			base::add_composand_instrs     (2);
		}
	};

	// static:

		template
		<
			auto static_parsed,
			auto line_pos, auto arg_size, auto line_size,
			auto size = 3*line_size + 7, auto _2_N = _2_6 // clean up size determination.
		>
		nik_ce auto U_slookup_swap_contr = U_slookup_contr
		<
			T_lookup_swap_contr, static_parsed, line_pos, arg_size, line_size, size, _2_N
		>;

/***********************************************************************************************************************/

// interface:

	template<auto static_parsed, auto lookup>
	struct T_lookup_swap
	{
		nik_ces auto & parsed = member_value_U<static_parsed>;

		template<auto line_pos, auto stypes, typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto arg_size  = sizeof...(Ts);
			nik_ce auto line_size = parsed.link_level[line_pos].size();
			nik_ce auto contr     = U_slookup_swap_contr<static_parsed, line_pos, arg_size, line_size>;

			return T_chain_start::template result<contr, lookup, stypes, Ts...>(vs...);
		}

	}; nik_ce auto _lookup_swap_ = U_store_B<T_lookup_swap>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// appl(ication):

/***********************************************************************************************************************/

// controller:

	template<auto static_parsed, gindex_type size>
	struct T_lookup_appl_contr : public T_lookup_contr<static_parsed, size>
	{
		using base   = T_lookup_contr<static_parsed, size>;
		using cindex = typename base::cindex;

		nik_ce T_lookup_appl_contr
		(
			cindex as, cindex ls, cindex bs, cindex lp, cindex ep, cindex mp, cindex cp, cindex rp

		) : base{as, ls, bs, lp, ep, mp, cp, rp}
		{
			base::add_initial_instrs   ();
			base::add_padding_instrs   ();
			base::add_composand_instrs ();
			base::add_composer_instrs  ();
			base::add_halting_instrs   (CT::apply);
		}
	};

	// static:

		template
		<
			auto static_parsed,
			auto line_pos, auto arg_size, auto line_size,
			auto size = 3*line_size + 7, auto _2_N = _2_6 // clean up size determination.
		>
		nik_ce auto U_slookup_appl_contr = U_slookup_contr
		<
			T_lookup_appl_contr, static_parsed, line_pos, arg_size, line_size, size, _2_N
		>;

/***********************************************************************************************************************/

// interface:

	template<auto static_parsed, auto lookup>
	struct T_lookup_appl
	{
		nik_ces auto & parsed = member_value_U<static_parsed>;

		template<auto line_pos, auto stypes, typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto arg_size  = sizeof...(Ts);
			nik_ce auto line_size = parsed.link_level[line_pos].size();
			nik_ce auto contr     = U_slookup_appl_contr<static_parsed, line_pos, arg_size, line_size>;

			return T_chain_start::template result<contr, lookup, stypes, Ts...>(vs...);
		}

	}; nik_ce auto _lookup_appl_ = U_store_B<T_lookup_appl>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// unit:

/***********************************************************************************************************************/

// controller:

	template<auto static_parsed, gindex_type size>
	struct T_lookup_unit_contr : public T_lookup_contr<static_parsed, size>
	{
		using base   = T_lookup_contr<static_parsed, size>;
		using cindex = typename base::cindex;

		nik_ce T_lookup_unit_contr
		(
			cindex as, cindex ls, cindex bs, cindex lp, cindex ep, cindex mp, cindex cp, cindex rp

		) : base{as, ls, bs, lp, ep, mp, cp, rp}
		{
			base::add_initial_instrs ();
			base::add_padding_instrs ();

			base::dispatch_composand_instrs (    _zero);
			base::add_halting_instrs        (CT::first);
		}
	};

	// static:

		template
		<
			auto static_parsed,
			auto line_pos, auto arg_size, auto line_size,
			auto size = 2*line_size + 8, auto _2_N = _2_6 // clean up size determination.
		>
		nik_ce auto U_slookup_unit_contr = U_slookup_contr
		<
			T_lookup_unit_contr, static_parsed, line_pos, arg_size, line_size, size, _2_N
		>;

/***********************************************************************************************************************/

// interface:

	template<auto static_parsed, auto lookup>
	struct T_lookup_unit
	{
		nik_ces auto & parsed = member_value_U<static_parsed>;

		template<auto line_pos, auto stypes, typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto arg_size  = sizeof...(Ts);
			nik_ce auto line_size = parsed.link_level[line_pos].size();
			nik_ce auto contr     = U_slookup_unit_contr<static_parsed, line_pos, arg_size, line_size>;

			return T_chain_start::template result<contr, lookup, stypes, Ts...>(vs...);
		}

	}; nik_ce auto _lookup_unit_ = U_store_B<T_lookup_unit>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// line:

/***********************************************************************************************************************/

// interface:

	template<auto static_targeted, auto this_f_env>
	struct T_lookup_line
	{
		nik_ces auto static_parsed		= member_type_U<static_targeted>::static_parsed;
		nik_ces auto & parsed			= member_value_U<static_parsed>;

		nik_ces auto this_f			= car_ <this_f_env>;
		nik_ces auto env			= cadr_<this_f_env>;
		nik_ces auto conductor			= U_pack_Vs
							<
								this_f,
								U_inductor_env   < static_parsed , env >,
								U_inductor_morph < static_parsed       >,
								U_inductor_cycle < static_parsed       >
							>;

		template<auto b> using dispatch		= T_store_U<to_list_<b, static_parsed, conductor>>;

		template<auto n, auto t, typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto & line  = parsed.link_level[n];
			nik_ce auto arg0_mu = Sign::is_mutable_arg(parsed.link_entry_sign(n, _zero));

			nik_ce auto is_unit = (line.is_assign() || line.is_return());
			nik_ce auto is_void = (line.is_void() && arg0_mu);
			nik_ce auto is_swap = (line.is_void() && not arg0_mu);
			nik_ce auto is_appl = (line.is_apply() || line.is_test() || is_void); // matches void.

			if      nik_ce (is_unit) return dispatch<_lookup_unit_>::template result<n, t, Ts...>(vs...);
			else if nik_ce (is_appl) return dispatch<_lookup_appl_>::template result<n, t, Ts...>(vs...);
			else if nik_ce (is_swap) return dispatch<_lookup_swap_>::template result<n, t, Ts...>(vs...);
			else                     return cctmp::_na_; // error.
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace chord

