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

// algorithm:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// action:

	template<gkey_type, gkey_type, auto...> struct T_praxis_action;

/***********************************************************************************************************************/

// names:

	struct PraxisActionName
	{
		enum : gkey_type // convenience for default params.
			{ identity = 0, id = identity, base, cond, move, left, rest, fold, sift, dimension };

	}; using PAN = PraxisActionName;

/***********************************************************************************************************************/

// notes:

	struct PraxisActionNote
	{
		enum : gkey_type // convenience for default params.
		{ identity = 0, id = identity, padding, rolling, winding, resting, tailing, halting, dimension };

	}; using PAT = PraxisActionNote;

/***********************************************************************************************************************/

// instructions:

	struct PraxisActionInstr
	{
		enum : gkey_type { name = 0, note, subname, subnote, dimension };

	}; using PAI = PraxisActionInstr;

/***********************************************************************************************************************/

// offset:

	struct ActionOffset { enum : gindex_type { multiply = 0, add }; };

	using PraxisActionOffset = ActionOffset;
	using PAO                = ActionOffset;

/***********************************************************************************************************************/

// size:

	template<template<auto...> typename T_action, typename _AI, typename _AO>
	struct T_contr_size
	{
		template<auto src, auto n>
		nik_ces auto action_offset = T_action<src[n][_AI::name], src[n][_AI::note]>::offset;

		nik_ces auto count(gindex_type & mult_size, gindex_type & add_size, gcindex_type *offset)
		{
			mult_size += offset[_AO::multiply];
			add_size  += offset[_AO::add];
		}

		template<auto roll, auto src, auto... Is>
		nik_ces auto result(nik_avp(T_pack_Vs<Is...>*))
		{
			gindex_type mult_size{}, add_size{};

			(count(mult_size, add_size, action_offset<src, Is>), ...);

			return mult_size * roll + add_size;
		}
	};

	using T_praxis_contr_size = T_contr_size<T_praxis_action, PAI, PAO>;

/***********************************************************************************************************************/

// base:

	// id:

		template<auto... filler>
		struct T_praxis_action<PAN::base, PAT::id, filler...>
		{
			nik_ces gindex_type offset[] = {0, 2};

			template<typename Contr, typename Src>
			nik_ces void result(Contr *contr, Src *ins)
			{
				contr->add_instr(PN::id, PT::id);
				contr->add_instr(PN::mach, PT::id);
			}
		};

	// padding:

		template<auto... filler>
		struct T_praxis_action<PAN::base, PAT::padding, filler...>
		{
			nik_ces gindex_type offset[] = {0, 2};

			template<typename Contr, typename Src>
			nik_ces void result(Contr *contr, Src *ins)
			{
				contr->add_instr(PN::pad, PT::select, contr->record.pad);
				contr->add_instr(PN::pad, PT::push);
			}
		};

	// rolling:

		template<auto... filler>
		struct T_praxis_action<PAN::base, PAT::rolling, filler...>
		{
			nik_ces gindex_type offset[] = {1, 0};

			template<typename Contr, typename Src>
			nik_ces void result(Contr *contr, Src *ins)
			{
				for (auto k = 0; k != contr->record.roll; ++k)
					contr->add_instr(ins[PAI::subname], ins[PAI::subnote]);
			}
		};

	// winding:

		template<auto... filler>
		struct T_praxis_action<PAN::base, PAT::winding, filler...>
		{
			nik_ces gindex_type offset[] = {0, 3};

			template<typename Contr, typename Src>
			nik_ces void result(Contr *contr, Src *ins)
			{
				contr->add_instr(PN::sift, PT::select, contr->record.wind, PI::front);
				contr->add_instr(PN::sift, PT::proj);
				contr->add_instr(ins[PAI::subname], ins[PAI::subnote]);
			}
		};

	// resting:

		template<auto... filler>
		struct T_praxis_action<PAN::base, PAT::resting, filler...>
		{
			nik_ces gindex_type offset[] = {0, 3};

			template<typename Contr, typename Src>
			nik_ces void result(Contr *contr, Src *ins)
			{
				contr->add_instr(PN::sift, PT::select, contr->record.wind, PI::back);
				contr->add_instr(PN::sift, PT::proj);
				contr->add_instr(ins[PAI::subname], ins[PAI::subnote]);
			}
		};

	// tailing:

		template<auto... filler>
		struct T_praxis_action<PAN::base, PAT::tailing, filler...>
		{
			nik_ces gindex_type offset[] = {0, 3};

			template<typename Contr, typename Src>
			nik_ces void result(Contr *contr, Src *ins)
			{
				contr->add_instr(PN::sift, PT::tail, contr->record.wind, contr->record.tail);
				contr->add_instr(PN::sift, PT::proj);
				contr->add_instr(ins[PAI::subname], ins[PAI::subnote]);
			}
		};

	// halting:

		template<auto... filler>
		struct T_praxis_action<PAN::base, PAT::halting, filler...>
		{
			nik_ces gindex_type offset[] = {0, 1};

			template<typename Contr, typename Src>
			nik_ces void result(Contr *contr, Src *ins)
				{ contr->add_instr(ins[PAI::subname], ins[PAI::subnote]); }
		};

/***********************************************************************************************************************/

// cond:

	// padding:

		template<auto... filler>
		struct T_praxis_action<PAN::cond, PAT::padding, filler...>
		{
			using Winding = T_praxis_action<PAN::base, PAT::padding, filler...>;
			nik_ces auto & offset = Winding::offset;

			template<typename Contr, typename Src>
			nik_ces void result(Contr *contr, Src *ins)
			{
				if (contr->record.not_empty() && contr->record.not_block() && contr->record.is_last())
					Winding::template result<>(contr, ins);
			}
		};

	// winding:

		template<auto... filler>
		struct T_praxis_action<PAN::cond, PAT::winding, filler...>
		{
			using Winding = T_praxis_action<PAN::base, PAT::winding, filler...>;
			nik_ces auto & offset = Winding::offset;

			template<typename Contr, typename Src>
			nik_ces void result(Contr *contr, Src *ins)
			{
				if (contr->record.not_empty() && contr->record.not_block() && contr->record.is_last())
					Winding::template result<>(contr, ins);
			}
		};

/***********************************************************************************************************************/

// move:

	// padding:

		template<auto... filler>
		struct T_praxis_action<PAN::move, PAT::padding, filler...>
		{
			nik_ces gindex_type offset[] = {0, 2};

			template<typename Contr, typename Src>
			nik_ces void result(Contr *contr, Src *ins)
			{
				contr->add_instr(PN::count, ins[PAI::subname]);
				contr->add_instr(PN::pad, PT::pull);
			}
		};

/***********************************************************************************************************************/

// left:

	// winding:

		template<auto... filler>
		struct T_praxis_action<PAN::left, PAT::winding, filler...>
		{
			using Winding = T_praxis_action<PAN::base, PAT::winding, filler...>;

			nik_ces gindex_type offset[] = {0, 3}; // max, max

			template<typename Contr, typename Src>
			nik_ces void result(Contr *contr, Src *ins)
			{
				if (contr->record.not_empty() && contr->record.not_block())
					Winding::template result<>(contr, ins);
			}
		};

/***********************************************************************************************************************/

// rest:

	// winding:

		template<auto... filler>
		struct T_praxis_action<PAN::rest, PAT::winding, filler...>
		{
			using Tailing = T_praxis_action<PAN::base, PAT::tailing, filler...>;
			using Resting = T_praxis_action<PAN::base, PAT::resting, filler...>;

			nik_ces gindex_type offset[] = {0, 3}; // max, max

			template<typename Contr, typename Src>
			nik_ces void result(Contr *contr, Src *ins)
			{
				if (contr->record.not_empty() && contr->record.not_block())
				{
					if (contr->record.is_last()) Tailing::template result<>(contr, ins);
					else                         Resting::template result<>(contr, ins);
				}
			}
		};

/***********************************************************************************************************************/

// fold:

	// winding:

		template<auto... filler>
		struct T_praxis_action<PAN::fold, PAT::winding, filler...>
		{
			nik_ces gindex_type offset[] = {0, 2};

			template<typename Contr, typename Src>
			nik_ces void result(Contr *contr, Src *ins)
			{
				contr->add_instr(PN::sift, PT::iter);
				contr->add_instr(PN::fold, PT::id);
			}
		};

/***********************************************************************************************************************/

// sift:

	// rolling:

		template<auto... filler>
		struct T_praxis_action<PAN::sift, PAT::rolling, filler...>
		{
			nik_ces gindex_type offset[] = {2, 0};

			template<typename Contr, typename Src>
			nik_ces void result(Contr *contr, Src *ins)
			{
				for (auto k = 0; k != contr->record.roll; ++k)
				{
					contr->add_instr(PN::sift, PT::id);
					contr->add_instr(PN::sift, PT::push);
				}
			}
		};

	// winding:

		template<auto... filler>
		struct T_praxis_action<PAN::sift, PAT::winding, filler...>
		{
			nik_ces gindex_type offset[] = {0, 3};

			template<typename Contr, typename Src>
			nik_ces void result(Contr *contr, Src *ins)
			{
				contr->add_instr(PN::sift, PT::iter);
				contr->add_instr(PN::sift, PT::id);
				contr->add_instr(PN::sift, PT::push);
			}
		};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// controller:

/***********************************************************************************************************************/

// record:

	struct T_praxis_contr_record // assumes wind <= tail.
	{
		gindex_type _2_N;
		gindex_type roll;
		gindex_type wind;
		gindex_type cycle;
		gindex_type tail;
		gindex_type pad;

		nik_ce T_praxis_contr_record(gcindex_type n, gcindex_type s, gcindex_type b) :
			_2_N{b}, roll{}, wind{}, cycle{}, tail{}, pad{} { initialize(n, s); }

		nik_ce void initialize(gcindex_type n, gcindex_type s)
		{
			roll  = n / _2_N;
			wind  = n % _2_N;
			cycle = s / _2_N;

			gindex_type mod = s % _2_N;

			tail = mod ? mod : _2_N;
			pad  = _2_N - tail;
		}

		nik_ce bool has_rolling () const { return (roll != 0); }
		nik_ce bool not_block   () const { return (wind != 0); }
		nik_ce bool not_empty   () const { return has_rolling() || not_block(); }
		nik_ce bool is_last     () const { return (roll == cycle); }
	};

/***********************************************************************************************************************/

// source:

	template<auto... Vs> nik_ce auto praxis_lift   = array< gkey_type        , Vs... >;
	template<auto... Vs> nik_ce auto praxis_source = array< gckey_type*const , Vs... >;

/***********************************************************************************************************************/

// interface:

	using praxis_instr_type = sequence<gindex_type, static_cast<gindex_type>(PI::dimension)>;

	template<auto src, auto length>
	struct T_praxis_contr : public sequence<praxis_instr_type, length>
	{
		using base		= sequence<praxis_instr_type, length>;
		using record_type	= T_praxis_contr_record;

		template<auto n>
		using action = T_praxis_action<src[n][PAI::name], src[n][PAI::note]>;

		record_type record;

		template<auto... Is>
		nik_ce T_praxis_contr(gcindex_type n, gcindex_type s, gcindex_type b, nik_avp(T_pack_Vs<Is...>*)) :
			base{}, record{n, s, b} { (action<Is>::template result<>(this, src[Is]), ...); }

		nik_ce void add_instr(gcindex_type name, gcindex_type note, gcindex_type pos = 0, gcindex_type num = 0)
		{
			base::end()->push(name);
			base::end()->push(note);
			base::end()->push(pos);
			base::end()->push(num);

			base::upsize();
		}
	};

/***********************************************************************************************************************/

// static:

	template<auto src, auto pack, auto n, auto s, auto _2_N>
	struct T_praxis_static_contr
	{
		nik_ces auto length = T_praxis_contr_size::template result<(n/_2_N), src>(pack);
		nik_ces auto value  = T_praxis_contr<src, length>{n, s, _2_N, pack};
		using type          = decltype(value);

	}; template<auto src, auto pack, auto n, auto s, auto _2_N>
		nik_ce auto _praxis_contr_ = U_store_T<T_praxis_static_contr<src, pack, n, s, _2_N>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// algorithms:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// left:

/***********************************************************************************************************************/

// controller:

	template<gindex_type _2_N = _2_6>
	struct T_praxis_left
	{
		nik_ces auto source = praxis_source
		<
			praxis_lift< PAN::base , PAT::id                             >,
			praxis_lift< PAN::cond , PAT::padding                        >,
			praxis_lift< PAN::base , PAT::rolling , PN::left , PT::heap  >,
			praxis_lift< PAN::left , PAT::winding , PN::sift , PT::heap  >,
			praxis_lift< PAN::base , PAT::halting , PN::halt , PT::front >
		>;

		nik_ces auto pack = U_pack_Vs<0, 1, 2, 3, 4>;

		template<auto n, auto s>
		nik_ces auto contr = _praxis_contr_<source, pack, n, s, _2_N>;

		template<auto d, auto n, auto... Vs>
		nik_ces auto result = T_praxis_start::template result<d, contr<n, sizeof...(Vs)>, Vs...>(U_null_Vs);
	};

	// syntactic sugar:

		nik_ce auto _dpar_left_ = U_custom_T<T_praxis_left<>>;
		nik_ce auto  _par_left_ = _alias_<_dpar_left_, 500>;

		template<auto p, auto n>
		nik_ce auto left_ = unpack_<p, _dpar_left_, 500, n>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// right:

/***********************************************************************************************************************/

// controller:

	template<gindex_type _2_N = _2_6>
	struct T_praxis_right
	{
		nik_ces auto source = praxis_source
		<
			praxis_lift< PAN::base , PAT::id                            >,
			praxis_lift< PAN::cond , PAT::padding                       >,
			praxis_lift< PAN::base , PAT::rolling , PN::left , PT::heap >,
			praxis_lift< PAN::left , PAT::winding , PN::sift , PT::heap >,
			praxis_lift< PAN::rest , PAT::winding , PN::sift , PT::pull >,
			praxis_lift< PAN::base , PAT::halting , PN::halt , PT::heap >
		>;

		nik_ces auto pack = U_pack_Vs<0, 1, 2, 3, 4, 5>;

		template<auto n, auto s>
		nik_ces auto contr = _praxis_contr_<source, pack, n, s, _2_N>;

		template<auto d, auto n, auto... Vs>
		nik_ces auto result = T_praxis_start::template result<d, contr<n, sizeof...(Vs)>, Vs...>(U_null_Vs);
	};

	// syntactic sugar:

		nik_ce auto _dpar_right_ = U_custom_T<T_praxis_right<>>;
		nik_ce auto  _par_right_ = _alias_<_dpar_right_, 500>;

		template<auto p, auto n>
		nik_ce auto right_ = unpack_<p, _dpar_right_, 500, n>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// at:

/***********************************************************************************************************************/

// controller:

	template<gindex_type _2_N = _2_6>
	struct T_praxis_at
	{
		nik_ces auto source = praxis_source
		<
			praxis_lift< PAN::base , PAT::id                             >,
			praxis_lift< PAN::cond , PAT::padding                        >,
			praxis_lift< PAN::base , PAT::rolling , PN::left , PT::heap  >,
			praxis_lift< PAN::rest , PAT::winding , PN::sift , PT::pull  >,
			praxis_lift< PAN::base , PAT::halting , PN::halt , PT::first >
		>;

		nik_ces auto pack = U_pack_Vs<0, 1, 2, 3, 4>;

		template<auto n, auto s>
		nik_ces auto contr = _praxis_contr_<source, pack, n, s, _2_N>;

		template<auto d, auto n, auto... Vs>
		nik_ces auto result = T_praxis_start::template result<d, contr<n, sizeof...(Vs)>, Vs...>(U_null_Vs);
	};

	// syntactic sugar:

		nik_ce auto _dpar_at_ = U_custom_T<T_praxis_at<>>;
		nik_ce auto  _par_at_ = _alias_<_dpar_at_, 500>;

		template<auto p, auto n>
		nik_ce auto at_ = unpack_<p, _dpar_at_, 500, n>;

		template<auto n, typename... Ts>
		using type_at = T_store_U<eval<_dpar_at_, 500, n, U_store_T<Ts>...>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// mutate:

/***********************************************************************************************************************/

// controller:

	template<gindex_type Note, gindex_type _2_N = _2_6>
	struct T_praxis_mutate
	{
		nik_ces auto source = praxis_source
		<
			praxis_lift< PAN::base , PAT::id                            >,
			praxis_lift< PAN::cond , PAT::padding                       >,
			praxis_lift< PAN::base , PAT::rolling , PN::left , PT::heap >,
			praxis_lift< PAN::left , PAT::winding , PN::sift , PT::heap >,
			praxis_lift< PAN::rest , PAT::winding , PN::sift , PT::pull >,
			praxis_lift< PAN::move , PAT::padding ,                Note >,
			praxis_lift< PAN::base , PAT::halting , PN::halt , PT::heap >
		>;

		nik_ces auto pack = U_pack_Vs<0, 1, 2, 3, 4, 5, 6>;

		template<auto n, auto s>
		nik_ces auto contr = _praxis_contr_<source, pack, n, s, _2_N>;

		template<auto d, auto n, auto j, auto... Vs>
		nik_ces auto result = T_praxis_jstart::template result<d, contr<n, sizeof...(Vs)>, j, Vs...>(U_null_Vs);
	};

/***********************************************************************************************************************/

// insert:

	// syntactic sugar:

		nik_ce auto _dpar_insert_ = U_custom_T<T_praxis_mutate<PT::copy>>;
		nik_ce auto  _par_insert_ = _alias_<_dpar_insert_, 500>;

		template<auto p, auto n, auto V>
		nik_ce auto insert_ = unpack_<p, _dpar_insert_, 500, n, V>;

/***********************************************************************************************************************/

// replace:

	// syntactic sugar:

		nik_ce auto _dpar_replace_ = U_custom_T<T_praxis_mutate<PT::proj>>;
		nik_ce auto  _par_replace_ = _alias_<_dpar_replace_, 500>;

		template<auto p, auto n, auto V>
		nik_ce auto replace_ = unpack_<p, _dpar_replace_, 500, n, V>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// segment:

/***********************************************************************************************************************/

// controller:

	template<gindex_type _2_N = _2_6>
	struct T_praxis_segment
	{
		nik_ces auto source = praxis_source
		<
			praxis_lift< PAN::base , PAT::id                               >,
			praxis_lift< PAN::base , PAT::rolling , PN::segment , PT::push >,
			praxis_lift< PAN::base , PAT::winding , PN::segment , PT::pull >,
			praxis_lift< PAN::base , PAT::halting , PN::halt    , PT::heap >
		>;

		nik_ces auto pack = U_pack_Vs<0, 1, 2, 3>;

		template<auto n>
		nik_ces auto contr = _praxis_contr_<source, pack, n, n, _2_N>;

		template<auto d, auto n, auto j>
		nik_ces auto result = T_praxis_jstart::template result<d, contr<n>, j>(U_null_Vs);
	};

	// syntactic sugar:

		nik_ce auto _dpar_segment_ = U_custom_T<T_praxis_segment<>>;
		nik_ce auto  _par_segment_ = _alias_<_dpar_segment_, 500>;

		template<auto n, auto j = 0>
		nik_ce auto segment_ = eval<_dpar_segment_, 500, n, j>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// fold:

/***********************************************************************************************************************/

// winders:

	template<auto Op>
	struct T_winder_fold
	{
		template<auto V, auto V0>
		nik_ces auto result = distem_<(not_na<V> && not_na<V0>), Op, _car_, V, V0>;

	}; template<auto Op>
		nik_ce auto _winder_fold_ = U_custom_T<T_winder_fold<Op>>;

/***********************************************************************************************************************/

// controller:

	template<gindex_type _2_N = _2_6>
	struct T_praxis_fold
	{
		nik_ces auto source = praxis_source
		<
			praxis_lift< PAN::base , PAT::id                             >,
			praxis_lift< PAN::base , PAT::padding                        >,
			praxis_lift< PAN::base , PAT::rolling , PN::fold , PT::id    >,
			praxis_lift< PAN::fold , PAT::winding                        >,
			praxis_lift< PAN::base , PAT::halting , PN::halt , PT::first >
		>;

		nik_ces auto pack = U_pack_Vs<0, 1, 2, 3, 4>;

		template<auto n>
		nik_ces auto contr = _praxis_contr_<source, pack, n, n, _2_N>;

		template<auto d, auto Op, auto V, auto... Vs>
		nik_ces auto result = T_praxis_start::template result
		<
			d, contr<sizeof...(Vs)>, V, Vs...

		>(U_null_Vs, Op, _winder_fold_<Op>);
	};

	// syntactic sugar:

		nik_ce auto _dpar_fold_ = U_custom_T<T_praxis_fold<>>;
		nik_ce auto  _par_fold_ = _alias_<_dpar_fold_, 500>;

		template<auto Op, auto... Vs>
		nik_ce auto fold_ = eval<_dpar_fold_, 500, Op, Vs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// sift:

/***********************************************************************************************************************/

// winders:

	// car:

		template<auto Op>
		struct T_winder_car
		{
			template<auto V>
			nik_ces auto result = distem_<not_na<V>, Op, _constant_<false>, V>;

		}; template<auto Op>
			nik_ce auto _winder_car_ = U_custom_T<T_winder_car<Op>>;

	// cdr:

		template<auto Op, auto M>
		struct T_winder_cdr
		{
			template<auto N>
			nik_ces auto result = (eval<Op, N> && (N < M));

		}; template<auto Op, auto M>
			nik_ce auto _winder_cdr_ = U_custom_T<T_winder_cdr<Op, M>>;

	// sift:

		template<auto static_contr>
		struct T_winder_sift
		{
			template<template<auto...> typename B, auto Op0, auto Op1>
			nik_ces auto result(nik_vp(H)(B<Op0, Op1>*))
			{
				nik_ce auto & contr = member_value_U<static_contr>;

				if nik_ce (!contr.record.not_block()) return H;
				else
				{
					nik_ce auto nOp0 = _winder_car_<Op0>;
					nik_ce auto nOp1 = _winder_cdr_<Op1, contr.record.wind>;

					return U_store_T<B<nOp0, nOp1>>;
				}
			}
		};

/***********************************************************************************************************************/

// controller:

	template<gindex_type _2_N = _2_6>
	struct T_praxis_sift
	{
		nik_ces auto source = praxis_source
		<
			praxis_lift< PAN::base , PAT::id                            >,
			praxis_lift< PAN::base , PAT::padding                       >,
			praxis_lift< PAN::sift , PAT::rolling                       >,
			praxis_lift< PAN::sift , PAT::winding                       >,
			praxis_lift< PAN::base , PAT::halting , PN::halt , PT::heap >
		>;

		nik_ces auto pack = U_pack_Vs<0, 1, 2, 3, 4>;

		template<auto n>
		nik_ces auto contr = _praxis_contr_<source, pack, n, n, _2_N>;

		template<auto n, auto Op>
		nik_ces auto winder = T_winder_sift<contr<n>>::template result<>(Op);

		template<auto d, auto Op, auto... Vs>
		nik_ces auto result = T_praxis_start::template result
		<
			d, contr<sizeof...(Vs)>, Vs...

		>(U_null_Vs, Op, winder<sizeof...(Vs), Op>);
	};

	nik_ce auto _dpar_sift_ = U_custom_T<T_praxis_sift<>>;
	nik_ce auto  _par_sift_ = _alias_<_dpar_sift_, 500>;

	template<auto Op, auto... Vs>
	nik_ce auto sift_ = eval<_dpar_sift_, 500, Op, Vs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

