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

// assembly:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// dependencies:

/***********************************************************************************************************************/

// params (syntactic sugar):

	nik_ce auto _dpar_at_		= U_custom_T<T_machine_params< MT::copy   , _car_           >>;
	nik_ce auto _dpar_left_		= U_custom_T<T_machine_params< MT::front  , _list_<>        >>;
	nik_ce auto _dpar_erase_	= U_custom_T<T_machine_params< MT::cut    , _list_<>        >>;
	nik_ce auto _dpar_insert_	= U_custom_T<T_machine_params< MT::paste  , _list_<> , _one >>;
	nik_ce auto _dpar_replace_	= U_custom_T<T_machine_params< MT::mutate , _list_<> , _one >>;

	nik_ce auto _par_at_		= _alias_< _dpar_at_      , MD::initial_depth >;
	nik_ce auto _par_left_		= _alias_< _dpar_left_    , MD::initial_depth >;
	nik_ce auto _par_erase_		= _alias_< _dpar_erase_   , MD::initial_depth >;
	nik_ce auto _par_insert_	= _alias_< _dpar_insert_  , MD::initial_depth >;
	nik_ce auto _par_replace_	= _alias_< _dpar_replace_ , MD::initial_depth >;

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
/***********************************************************************************************************************/

// space:

	template<gkey_type, gkey_type, auto...> struct T_assembly;

/***********************************************************************************************************************/

// names:

	struct AssemblyName
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.
			jump , left , at , replace , select , apply ,
			dimension
		};
	};

	using AN = AssemblyName;

/***********************************************************************************************************************/

// notes:

	struct AssemblyNote
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.
			go_to , branch ,
			dimension
		};
	};

	using AT = AssemblyNote;

/***********************************************************************************************************************/

// instructions:

	struct AssemblyInstr
	{
		enum : gkey_type
		{
			size = 0,
			name , note , pos ,
			dimension
		};
	};

	using AI = AssemblyInstr;

/***********************************************************************************************************************/

// dispatch:

	struct AssemblyDispatch
	{
		// defaults:

			nik_ces gindex_type initial_index = _zero;

		// accessors:

			nik_ces auto instr(ccontr_type c, gcindex_type i)
				{ return c[i]; }

		// navigators:

			nik_ces gkey_type next_name(ccontr_type c, gcindex_type i)
				{ return c[i+1][AI::name]; }

			nik_ces gkey_type next_note(ccontr_type c, gcindex_type i)
				{ return c[i+1][AI::note]; }

			nik_ces gindex_type next_index(ccontr_type, gcindex_type i)
				{ return i + 1; }
	};

	using AD = AssemblyDispatch;

/***********************************************************************************************************************/

// start:

	struct T_assembly_start
	{
		nik_ces auto i = AD::initial_index;

		template<auto s, auto c, auto l, auto... Vs, typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
			{ return NIK_ASSEMBLY(s, c, i, l, Vs)(vs...); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// dependencies:

	template<gkey_type, auto...> struct T_arg;

/***********************************************************************************************************************/

// left:

	template<auto... filler>
	struct T_arg<AN::left, filler...>
	{
		template<auto Name, auto n, auto... Vs, typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto p = eval<_par_left_, n, U_store_T<Ts>...>;

			return T_arg<Name, p>::template result<Vs...>(vs...);
		}
	};

/***********************************************************************************************************************/

// at:

	template<template<auto...> typename B, auto... LUs, nik_vp(p)(B<LUs...>*)>
	struct T_arg<AN::at, p>
	{
		template<auto... Vs, typename TN, typename... Ts>
		nik_ces auto result(T_store_U<LUs>... lvs, TN vn, Ts... vs) { return vn; }
	};

	// syntactic sugar:

		template<auto n, auto... Vs, typename... Ts>
		nik_ce auto arg_at(Ts... vs) { return T_arg<AN::left>::template result<AN::at, n, Vs...>(vs...); }

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// jump:

/***********************************************************************************************************************/

// go to:

	template<auto... filler>
	struct T_assembly<AN::jump, AT::go_to, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(s, c, i, l, Vs), typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
		{
			nik_ce auto ins = instr(c, i);
			nik_ce auto ni  = ins[AI::pos];

			return NIK_ASSEMBLY(s, c, ni, l, Vs)(vs...);
		}
	};

/***********************************************************************************************************************/

// branch:

	template<auto... filler>
	struct T_assembly<AN::jump, AT::branch, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(s, c, i, l, Vs), typename BoolType, typename... Ts>
		nik_ces auto result(BoolType v, Ts... vs) -> T_store_U<s>
		{
			nik_ce auto ins = instr(c, i);
			nik_ce auto ni  = ins[AI::pos];

			if (v) return NIK_ASSEMBLY(s, c, ni, l, Vs)(vs...);
			else   return NIK_ASSEMBLY(s, c,  i, l, Vs)(vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// left:

/***********************************************************************************************************************/

// id:

	template<auto... filler>
	struct T_assembly<AN::left, AT::id, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(s, c, i, l, Vs), typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
		{
			nik_ce auto ins	= AD::instr(c, i);
			nik_ce auto n   = ins[AI::pos];
			nik_ce auto p   = eval<_par_left_, n, U_store_T<Ts>...>;

			return NIK_ASSEMBLY_TEMPLATE(c, i),

			       p

			NIK_ASSEMBLY_RESULT(s, c, i, l, Vs)(vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// at:

/***********************************************************************************************************************/

// id:

	template<template<auto...> typename B, auto... LUs, nik_vp(p)(B<LUs...>*)>
	struct T_assembly<AN::at, AT::id, p>
	{
		template<NIK_ASSEMBLY_PARAMS(s, c, i, l, Vs), typename TN, typename... Ts>
		nik_ces auto result(T_store_U<LUs>... lvs, TN vn, Ts... vs) -> T_store_U<s>
			{ return vn; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// replace:

/***********************************************************************************************************************/

// id:

	template<template<auto...> typename B, auto... LUs, nik_vp(p)(B<LUs...>*)>
	struct T_assembly<AN::replace, AT::id, p>
	{
		template<NIK_ASSEMBLY_PARAMS(s, c, i, l, Vs), typename T, typename TN, typename... Ts>
		nik_ces auto result(T v, T_store_U<LUs>... lvs, TN vn, Ts... vs) -> T_store_U<s>
			{ return NIK_ASSEMBLY(s, c, i, l, Vs)(lvs..., v, vs...); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// select:

/***********************************************************************************************************************/

// id:

	template<auto... filler>
	struct T_assembly<AN::select, AT::id, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(s, c, i, l, Vs), typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
		{
			nik_ce auto ins	= AD::instr(c, i);
			nik_ce auto n   = ins[AI::pos];
			nik_ce auto p   = unpack_<l, _par_at_, n>;

			return NIK_ASSEMBLY_TEMPLATE(c, i),

			       p

			NIK_ASSEMBLY_RESULT(s, c, i, l, Vs)(vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// apply:

/***********************************************************************************************************************/

// id:

	template<template<auto...> typename B, auto Op, auto... Is, nik_vp(p)(B<Op, Is...>*)>
	struct T_assembly<AN::apply, AT::id, p>
	{
		template<NIK_ASSEMBLY_PARAMS(s, c, i, l, Vs), typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
		{
			auto val = T_store_U<Op>::template result<>(arg_at<Is>(vs...)...);

			return NIK_ASSEMBLY(s, c, i, l, Vs)(val, vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

