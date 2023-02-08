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

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// dependencies:

/***********************************************************************************************************************/

	// find:

		nik_ce auto _find_ = U_par_abstract<Abstract::find>;

		template<gcbool_type *arr, gindex_type size>
		nik_ce auto eval_find()
		{
			nik_ce auto U_find = _multifind_<_dereference_>;
			nik_ce auto cur    = T_store_U<U_find>::result(arr, arr + size);

			return cur - arr;
		}

		template<auto Op, auto... Vs>
		nik_ce auto eval<_find_, Op, Vs...> = eval_find
		<
			array<gcbool_type, eval<Op, Vs>...>, sizeof...(Vs)
		>();

	// match:

		nik_ce auto _match_ = U_par_abstract<Abstract::match>;

		template<auto Op, auto V, auto... Vs>
		nik_ce auto eval<_match_, Op, V, Vs...> = eval_find
		<
			array<gcbool_type, eval<Op, V, Vs>...>, sizeof...(Vs)
		>();

/***********************************************************************************************************************/

// syntactic sugar:

	template<auto Op, auto... Vs> nik_ce auto find_  = eval<_find_, Op, Vs...>;
	template<auto Op, auto... Vs> nik_ce auto match_ = eval<_match_, Op, Vs...>;

/***********************************************************************************************************************/

// params (syntactic sugar):

	nik_ce auto _dpar_erase_	= U_custom_T<T_machine_params< MT::cut    , _list_<>        >>;
	nik_ce auto _dpar_insert_	= U_custom_T<T_machine_params< MT::paste  , _list_<> , _one >>;

	nik_ce auto _par_erase_		= _alias_< _dpar_erase_   , MD::initial_depth >;
	nik_ce auto _par_insert_	= _alias_< _dpar_insert_  , MD::initial_depth >;

/***********************************************************************************************************************/

// fold:

	struct T_machine_fold
	{
		template<auto Op>
		struct T_last
		{
			template<auto V0, auto V1>
			nik_ces auto result = stem_
			<
				eval<PP::_is_na_, V1>, V0, Op, V0, V1
			>;

		}; template<auto Op>
			nik_ces auto _last_ = U_custom_T<T_last<Op>>;

		template<auto Op> nik_ces auto sH0 = U_pack_Vs<Op, _last_<Op>>;
		template<auto Op> nik_ces auto H0  = U_pack_Vs<_car_, sH0<Op>>;

		template<auto n>
		nik_ces auto contr = controller
		<
			instruction < MN::call , MT::praxis , PN::fold , n >,
			instruction < MN::halt , MT::eval                  >
		>;

		template<auto d, auto Op, auto V, auto... Vs>
		nik_ces auto result = T_machine_start::template result<d, contr<sizeof...(Vs)>, V, Vs...>(H0<Op>);
	};

	nik_ce auto _dpar_fold_ = U_custom_T<T_machine_fold>;
	nik_ce auto  _par_fold_ = MD::template with_initial_depth<_dpar_fold_>;

/***********************************************************************************************************************/

// segment:

	struct T_machine_segment
	{
		nik_ces auto sH0 = U_pack_Vs<H_id>;
		nik_ces auto  H0 = U_pack_Vs<_car_, sH0>;

		template<auto n>
		nik_ces auto contr = controller
		<
			instruction < MN::call , MT::praxis , PN::segment , n >,
			instruction < MN::halt , MT::eval                     >
		>;

		template<auto d, auto n>
		nik_ces auto result = T_machine_start::template result<d, contr<n>, _zero>(H0);
	};

	nik_ce auto _dpar_segment_ = U_custom_T<T_machine_segment>;
	nik_ce auto  _par_segment_ = MD::template with_initial_depth<_dpar_segment_>;

/***********************************************************************************************************************/

// sift:

	struct T_machine_sift
	{
		template<auto Ops>
		struct T_last
		{
			template<auto V, auto N>
			nik_ces auto result = stem_
			<
				eval<PP::_is_na_, V>, _pack_null_, Ops, V, N
			>;

		}; template<auto Ops>
			nik_ces auto _last_ = U_custom_T<T_last<Ops>>;

		template<auto Ops> nik_ces auto sH0 = U_pack_Vs<H_id, Ops, _last_<Ops>>;
		template<auto Ops> nik_ces auto H0  = U_pack_Vs<_car_, sH0<_pack_filter_<Ops>>>;

		template<auto n>
		nik_ces auto contr = controller
		<
			instruction < MN::call , MT::praxis , PN::sift , n >,
			instruction < MN::halt , MT::eval                  >
		>;

		template<auto d, auto Ops, auto... Vs>
		nik_ces auto result = T_machine_start::template result<d, contr<sizeof...(Vs)>, _zero, Vs...>(H0<Ops>);
	};

	nik_ce auto _dpar_sift_ = U_custom_T<T_machine_sift>;
	nik_ce auto  _par_sift_ = MD::template with_initial_depth<_dpar_sift_>;

/***********************************************************************************************************************/

// insert sort:

	template<auto Op>
	struct T_machine_insert_sort
	{
		nik_ces auto match = _alias_<_match_, Op>;
		nik_ces auto H0    = U_pack_Vs<_car_, _praxis_<match, _one>, _dpar_insert_>;

		template<auto f = _one, auto n0 = _one, auto i = _two, auto n1 = _one>
		nik_ces auto contr = controller
		<
			instruction < MN::call , MT::propel , f  >,
			instruction < MN::call , MT::eval   , n0 >,
			instruction < MN::call , MT::propel , i  >,
			instruction < MN::call , MT::eval   , n1 >,
			instruction < MN::halt , MT::eval        >
		>;

		template<auto d, auto V, template<auto...> typename B, auto... Vs>
		nik_ces auto _result(nik_avp(B<Vs...>*))
			{ return T_machine_start::template result<MD::next_depth(d), contr<>, V, Vs...>(H0); }

		template<auto d, auto List, auto V>
		nik_ces auto result = _result<MD::next_depth(d), V>(List);
	};

	template<auto Op> nik_ce auto _dpar_insert_sort_ = U_custom_T<T_machine_insert_sort<Op>>;
	template<auto Op> nik_ce auto  _par_insert_sort_ = MD::template with_initial_depth<_dpar_insert_sort_<Op>>;

/***********************************************************************************************************************/

// sort:

	template<auto Op>
	struct T_machine_sort
	{
		nik_ces auto H0 = U_pack_Vs<_car_, _dpar_insert_sort_<Op>>;

		template<auto n = _one, auto Loop = _zero, auto Done = _three>
		nik_ces auto contr = controller
		<
			instruction < MN::jump , MT::cascade , Done >,
			instruction < MN::call , MT::cascade , n    >,
			instruction < MN::jump , MT::go_to   , Loop >,
			instruction < MN::halt , MT::eval           >
		>;

		template<auto d, auto... Vs>
		nik_ces auto result = T_machine_start::template result<d, contr<>, U_null_Vs, Vs...>(H0);
	};

	template<auto Op> nik_ce auto _dpar_sort_ = U_custom_T<T_machine_sort<Op>>;
	template<auto Op> nik_ce auto  _par_sort_ = MD::template with_initial_depth<_dpar_sort_<Op>>;

/***********************************************************************************************************************/

// trampoline:

	template<auto Op>
	struct T_machine_trampoline
	{
		nik_ces auto H0 = U_pack_Vs<_car_>;

		template<auto n = _one>
		nik_ces auto contr = controller
		<
			instruction < MN::call , MT::eval , n >,
			instruction < MN::halt , MT::eval     >
		>;

		template<auto d, auto... Vs>
		nik_ces auto result = T_machine_start::template result<MD::next_depth(d), contr<>, Op, Vs...>(H0);
	};

	template<auto Op> nik_ce auto _dpar_trampoline_ = U_custom_T<T_machine_trampoline<Op>>;
	template<auto Op> nik_ce auto  _par_trampoline_ = MD::template with_initial_depth<_dpar_trampoline_<Op>>;

	// syntactic sugar:

		template<auto Op> nik_ces auto _dpart_sort_ = _dpar_trampoline_<_dpar_sort_<Op>>;
		template<auto Op> nik_ces auto _part_sort_ = _par_trampoline_<_dpar_sort_<Op>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// memoize:

/***********************************************************************************************************************/

// lookup:

	template<gindex_type _2_N>
	struct T_machine<MN::memoize, MT::lookup, _2_N>
	{
		struct T_same_car
		{
			template<auto W, auto Z>
			nik_ces auto result = eval<_same_, W, unpack_<Z, _car_>>;

		}; nik_ces auto _same_car_ = U_custom_T<T_same_car>;

		template
		<
			NIK_MACHINE_PARAMS(d, m, c, i, Vs),
			template<auto...> typename B0, auto W0,
			template<auto...> typename B1, auto... Xs, typename Heap2,
			template<auto...> typename B3, auto... Zs, typename... Args
		>
		nik_ces auto result(nik_vp(H0)(B0<W0>*), nik_vp(H1)(B1<Xs...>*), Heap2 H2, nik_vp(A0)(B3<Zs...>*), Args... As)
		{
			nik_ce auto size = sizeof...(Zs);
			nik_ce auto pos	 = find_<_alias_<_same_car_, W0>, Zs...>;

			if nik_ce (pos == size)

				return NIK_MACHINE(_2_N, d, MT::id, c, i, Vs)(U_null_Vs, H1, H2, A0, As...);
			else
			{
				nik_ce auto ins = MD::instr(c, i);
				nik_ce auto ni  = ins[MI::pos];

				return NIK_MACHINE(_2_N, d, MT::id, c, ni, Vs)(A0, U_pack_Vs<pos, Xs...>, H2, A0, As...);
			}
		}
	};

/***********************************************************************************************************************/

// insert:

	template<gindex_type _2_N>
	struct T_machine<MN::memoize, MT::insert, _2_N>
	{
		template
		<
			NIK_MACHINE_PARAMS(d, m, c, i, Vs), template<auto...> typename B0, auto W0,
			template<auto...> typename B1, auto X0, auto... Xs, typename Heap2,
			template<auto...> typename B3, auto... Zs, typename... Args
		>
		nik_ces auto result
		(
			nik_vp(H0)(B0<W0>*), nik_vp(H1)(B1<X0, Xs...>*), Heap2 H2, nik_vp(A0)(B3<Zs...>*), Args... As
		)
		{
			nik_ce auto Z0 = U_pack_Vs<W0, X0>;
			nik_ce auto a0 = U_pack_Vs<Z0, Zs...>;

			return eval<_to_tuple_, a0, X0>;
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

