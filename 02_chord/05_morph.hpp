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

// morph:

namespace chord {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

	template<typename T>
	nik_ce auto U_store_T					= cctmp::U_store_T<T>;

	template<auto... Vs>
	using T_pack_Vs						= cctmp::T_pack_Vs<Vs...>;

	template<auto... Vs>
	nik_ce auto U_pack_Vs					= cctmp::U_pack_Vs<Vs...>;

	template<typename... Ts>
	nik_ce auto U_pack_Ts					= cctmp::U_pack_Ts<Ts...>;

	nik_ce auto _2_6					= cctmp::_2_6;

	template<typename T, T... Vs>
	nik_ce auto array					= cctmp::array<T, Vs...>;

	nik_ce auto _id_					= cctmp::_id_;

	template<auto... Vs>
	nik_ce auto eval					= cctmp::eval<Vs...>;

	nik_ce auto _same_					= cctmp::_same_;

	template<auto... Vs>
	nik_ce auto push_					= cctmp::push_<Vs...>;

	template<auto... Vs>
	nik_ce auto at_						= cctmp::at_<Vs...>;

	template<auto... Vs>
	nik_ce auto segment_					= cctmp::segment_<Vs...>;

	using gcbool_type					= cctmp::gcbool_type;

	using CT						= cctmp::CT;
	using CI						= cctmp::CI;

	using CAN						= cctmp::CAN;
	using CAT						= cctmp::CAT;
	using CAI						= cctmp::CAI;

	using T_chain_start					= cctmp::T_chain_start;

	using chain_instr_type					= cctmp::chain_instr_type;

	template<auto... Vs>
	using T_chain_action					= cctmp::T_chain_action<Vs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// argpose:

/***********************************************************************************************************************/

// controller:

	template<auto conductor, auto static_morph, gindex_type length>
	struct T_morph_argpose_contr : public cctmp::sequence<chain_instr_type, length>
	{
		using T_lookup_frame	= typename T_store_U<at_<conductor, 1>>::T_lookup_frame; // magic number.
		using subinstr_type	= cctmp::sequence<gindex_type, static_cast<gindex_type>(CAI::dimension)>;
		using base		= cctmp::sequence<chain_instr_type, length>;
		using cindex		= gcindex_type;

		nik_ces auto & morph	= member_value_U<static_morph>;

		cindex size_of;
		cindex _2_N;
		subinstr_type ins;

		nik_ce T_morph_argpose_contr(cindex s, cindex b) : base{}, size_of{s}, _2_N{b}
		{
			ins.fullsize();

			add_initial_instrs   ();
			add_padding_instrs   ();
			add_composand_instrs (segment_<morph.size() - 1, 1>);
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
			cindex mod     = size_of % _2_N;
			cindex tail    = mod ? mod : _2_N;
			ins[CAI::pos0] = _2_N - tail;

			T_chain_action<CAN::base, CAT::padding>::template result<>(this, ins);
		}

		template<auto... Is>
		nik_ce void add_composand_instrs(nik_avp(T_pack_Vs<Is...>*))
			{ (add_id_composand_instr<Is>(), ...); }

		template<auto pos>
		nik_ce void add_id_composand_instr()
		{
			nik_ce auto record = T_lookup_frame::find_frame(morph[pos]);

			ins[CAI::pos0] = T_lookup_frame::template map<record.v0, record.v1>();

			T_chain_action<CAN::non, CAT::arg>::template result<>(this, ins);
		}

		nik_ce void add_composer_instrs()
		{
			ins[CAI::pos0] = 4; // inductor morph env (magic number)
			ins[CAI::pos1] = T_store_U<static_morph>::index;
			ins[CAI::pos2] = 0; // composer (magic number)

			T_chain_action<CAN::ext, CAT::non>::template result<>(this, ins);
		}

		nik_ce void add_halting_instrs()
		{
			cindex cycle = size_of / _2_N;

			ins[CAI::pos0] = _2_N * (cycle + 1);
			T_chain_action<CAN::pose, CAT::halting>::template result<>(this, ins);

			ins[CAI::pos0] = CT::apply;
			T_chain_action<CAN::base, CAT::halting>::template result<>(this, ins);
		}
	};

/***********************************************************************************************************************/

// static:

	template<auto conductor, auto static_morph, auto s, auto _2_N>
	struct T_morph_static_argpose_contr
	{
		nik_ces auto length	= 3*member_value_U<static_morph>.size() + 8; // needs to be confirmed.
		nik_ces auto value	= T_morph_argpose_contr<conductor, static_morph, length>{s, _2_N};
		using type		= decltype(value);
	};

	template<auto conductor, auto static_morph, auto s, auto _2_N = _2_6>
	nik_ce auto _morph_argpose_contr_ = U_store_T<T_morph_static_argpose_contr<conductor, static_morph, s, _2_N>>;

/***********************************************************************************************************************/

// interface:

	template<auto static_morph, auto conductor, auto stypes>
	struct T_morph_argpose
	{
		template<auto s>
		nik_ces auto contr = _morph_argpose_contr_<conductor, static_morph, s>;

		template<typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			return T_chain_start::template result<contr<sizeof...(Ts)>, conductor, stypes, Ts...>(vs...);
		}
	};

	// syntactic sugar:

		template<auto static_morph, auto conductor, auto stypes>
		nik_ce auto _morph_argpose_ = U_store_T<T_morph_argpose<static_morph, conductor, stypes>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// subpose:

/***********************************************************************************************************************/

// controller:

	template<auto conductor, auto static_morph, gindex_type length>
	struct T_morph_subpose_contr : public cctmp::sequence<chain_instr_type, length>
	{
		using T_lookup_frame	= typename T_store_U<at_<conductor, 1>>::T_lookup_frame; // magic number.
		using subinstr_type	= cctmp::sequence<gindex_type, static_cast<gindex_type>(CAI::dimension + 1)>; // confirm.
		using base		= cctmp::sequence<chain_instr_type, length>;
		using cindex		= gcindex_type;

		nik_ces auto & morph	= member_value_U<static_morph>;

		cindex size_of;
		cindex _2_N;
		subinstr_type ins;

		nik_ce T_morph_subpose_contr(cindex s, cindex b) : base{}, size_of{s}, _2_N{b}
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

		// initial:

			nik_ce void add_initial_instrs()
				{ T_chain_action<CAN::base, CAT::id>::template result<>(this, ins); }

		// padding:

			nik_ce void add_padding_instrs()
			{
				cindex mod     = size_of % _2_N;
				cindex tail    = mod ? mod : _2_N;
				ins[CAI::pos0] = _2_N - tail;

				T_chain_action<CAN::base, CAT::padding>::template result<>(this, ins);
			}

		// composand:

			nik_ce void add_composand_instrs()
			{
				for (auto k = morph.citerate(1, 0); k.not_end(); ++k)
					dispatch_composand_instr(k);
			}

			template<typename Iter>
			nik_ce void dispatch_composand_instr(const Iter & k)
			{
				if (Sign::is_static_arg(k->sign)) add_arg_composand_instr(k);
				else if (Sign::is_env(k->sign)) add_env_composand_instr(k);
				else { } // error.
			}

			template<typename Iter>
			nik_ce void add_arg_composand_instr(const Iter & k)
			{
				ins[CAI::pos0] = k->index;
				ins[CAI::pos1] = k.left_size();

				T_chain_action<CAN::typ, CAT::arg>::template result<>(this, ins);
			}

			template<typename Iter>
			nik_ce void add_env_composand_instr(const Iter & k)
			{
				auto is_id = cctmp::apply<cctmp::_subarray_same_<>>(k->cselect(), Morph::id);

				if (is_id) add_id_env_composand_instr(k.left_size());
				else add_not_id_env_composand_instr(k);
			}

			nik_ce void add_id_env_composand_instr(cindex k)
			{
				ins[CAI::pos0] = k;

				T_chain_action<CAN::non, CAT::arg>::template result<>(this, ins);
			}

			template<typename Iter>
			nik_ce void add_not_id_env_composand_instr(const Iter & k)
			{
				ins[CAI::pos0] = 4; // inductor morph env (magic number)
				ins[CAI::pos1] = T_store_U<static_morph>::index;
				ins[CAI::pos2] = k.left_size() + 1;
				ins[CAI::pos3] = k.left_size();

				T_chain_action<CAN::ext, CAT::arg>::template result<>(this, ins);
			}

		// composer:

			nik_ce void add_composer_instrs()
			{
				ins[CAI::pos0] = 4; // inductor morph env (magic number)
				ins[CAI::pos1] = T_store_U<static_morph>::index;
				ins[CAI::pos2] = 0; // composer (magic number)

				T_chain_action<CAN::ext, CAT::non>::template result<>(this, ins);
			}

		// halting:

			nik_ce void add_halting_instrs()
			{
				cindex cycle = size_of / _2_N;

				ins[CAI::pos0] = _2_N * (cycle + 1);
				T_chain_action<CAN::pose, CAT::halting>::template result<>(this, ins);

				ins[CAI::pos0] = CT::apply;
				T_chain_action<CAN::base, CAT::halting>::template result<>(this, ins);
			}
	};

/***********************************************************************************************************************/

// static:

	template<auto conductor, auto static_morph, auto s, auto _2_N>
	struct T_morph_static_subpose_contr
	{
		nik_ces auto length	= 3*member_value_U<static_morph>.size() + 7; // needs to be confirmed.
		nik_ces auto value	= T_morph_subpose_contr<conductor, static_morph, length>{s, _2_N};
		using type		= decltype(value);
	};

	template<auto conductor, auto static_morph, auto s, auto _2_N = _2_6>
	nik_ce auto _morph_subpose_contr_ = U_store_T<T_morph_static_subpose_contr<conductor, static_morph, s, _2_N>>;

/***********************************************************************************************************************/

// interface:

	template<auto static_morph, auto conductor, auto stypes>
	struct T_morph_subpose
	{
		template<auto s>
		nik_ces auto contr = _morph_subpose_contr_<conductor, static_morph, s>;

		template<typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			return T_chain_start::template result<contr<sizeof...(Ts)>, conductor, stypes, Ts...>(vs...);
		}
	};

	// syntactic sugar:

		template<auto static_morph, auto conductor, auto stypes>
		nik_ce auto _morph_subpose_ = U_store_T<T_morph_subpose<static_morph, conductor, stypes>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// curry:

	// reimplement using interpreter machines, analogous to how
	// argpose and subpose are implemented with chain machines.

/***********************************************************************************************************************/

// interface:

	template<auto static_morph, auto conductor, auto stypes>
	struct T_morph_curry
	{
		using T_lookup_frame = typename T_store_U<at_<conductor, 1>>::T_lookup_frame; // magic number.

		nik_ces auto & morph = member_value_U<static_morph>;

	//	template<auto s>
	//	nik_ces auto contr = _morph_subpose_contr_<conductor, static_morph, s>;

		template<auto pos>
		nik_ces auto get()
		{
			nik_ce auto & entry = morph[pos];
			nik_ce auto record  = T_lookup_frame::find_frame(entry);

			return T_lookup_frame::template map<record.v0, record.v1>();
		}

		template<auto... Is>
		nik_ces auto curry(nik_avp(T_pack_Vs<Is...>*)) { return cctmp::_curry_<get<Is>()...>; }

		template<typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto segment = segment_<morph.size()>;
			nik_ce auto curried = curry(segment);
		//	nik_ce auto curried = T_praxis_start::template result<contr<sizeof...(Ts), conductor, stypes>();

			return T_store_U<curried>::template result<Ts...>(vs...);
		}
	};

	// syntactic sugar:

		template<auto static_morph, auto conductor, auto stypes>
		nik_ce auto _morph_curry_ = U_store_T<T_morph_curry<static_morph, conductor, stypes>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// interface:

/***********************************************************************************************************************/

// static:

	template<auto static_parsed, auto n, auto m>
	struct T_static_morph
	{
		nik_ces auto & parsed	= member_value_U<static_parsed>;
		nik_ces auto index	= parsed.link_entry_index(n, m);
		nik_ces auto token	= parsed.morph_level[index].token;
		nik_ces auto & value	= parsed.morph_level[index].parameter;
		using type		= modify_type<_from_reference_, decltype(value)>;

	}; template<auto static_parsed, auto n, auto m>
		nik_ce auto _static_morph_ = U_store_T<T_static_morph<static_parsed, n, m>>;

/***********************************************************************************************************************/

// env:

	template<auto static_parsed>
	struct T_inductor_morph_env
	{
		nik_ces auto & parsed = member_value_U<static_parsed>;

		template<auto n, auto m, auto l, auto t>
		nik_ces auto result()
		{
			using T_lookup_frame = typename T_store_U<at_<l, 1>>::T_lookup_frame; // magic number.

			nik_ce auto & entry = parsed.morph_level[n].parameter[m];
			nik_ce auto record  = T_lookup_frame::find_frame(entry);

			return T_lookup_frame::template map<record.v0, record.v1>();
		}

	}; template<auto static_parsed>
		nik_ce auto U_inductor_morph_env = U_store_T<T_inductor_morph_env<static_parsed>>;

/***********************************************************************************************************************/

// interface:

	template<auto static_parsed>
	struct T_inductor_morph
	{
		using Token = typename T_chord_assembly_lexer::Token;

		template<auto n, auto m, auto l, auto t>
		nik_ces auto result()
		{
			nik_ce auto static_morph = _static_morph_<static_parsed, n, m>;
			nik_ce auto line_token   = T_store_U<static_morph>::token;
			nik_ce auto nl           = push_<l, U_inductor_morph_env<static_parsed>>;

			if      nik_ce (line_token == Token::argpose) return _morph_argpose_ <static_morph, nl, t>;
			else if nik_ce (line_token == Token::subpose) return _morph_subpose_ <static_morph, nl, t>;
			else if nik_ce (line_token == Token::curry  ) return _morph_curry_   <static_morph, nl, t>;
			else                                          return cctmp::_na_; // error.
		}

	}; template<auto static_parsed>
		nik_ce auto U_inductor_morph = U_store_T<T_inductor_morph<static_parsed>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace chord

