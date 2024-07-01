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

// parameter (eval):

	// Privileges template parameters through variable templates and variadic input.

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// eval:

	template<auto Op, bool V>
	nik_ce auto eval_assert() { static_assert(V, "eval: undefined operator"); }

	template<auto Op, auto... Vs>
	nik_ce auto eval = eval_assert<Op, false>();

/***********************************************************************************************************************/

// argument:

	template<auto Key, auto Op, auto... Ws, nik_vp(op)(T_argument<Key, Op, Ws...>*), auto... Vs>
	nik_ce auto eval<op, Vs...> = T_argument<Key, Op, Ws...>::template result<decltype(Vs)...>(Vs...);

// modify type:

	template<auto Op, typename T>
	using modify_type = T_store_U<eval<Op, U_store_T<T>>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// matchers:

	template<template<typename> class matcher, auto U>
	nik_ce auto reflect = matcher<T_store_U<U>>::result;

	template<template<typename> class matcher, auto U>
	nik_ce auto modify = U_store_T<typename matcher<T_store_U<U>>::result>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// abstract:

/***********************************************************************************************************************/

// operators:

	struct ParAbstract
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.
			same , alias ,
			dimension
		};
	};

/***********************************************************************************************************************/

// same:

	nik_ce auto _same_ = U_par_abstract<ParAbstract::same>;

	template<auto V0, auto V1> nik_ce auto eval<_same_, V0, V1> = false;
	template<auto V>           nik_ce auto eval<_same_, V , V > = true;

/***********************************************************************************************************************/

// alias:

	template<auto Op, auto... Ws>
	nik_ce auto  _alias_ = U_store_T<T_par_abstract<ParAbstract::alias, Op, Ws...>>;

	template<auto Op, auto... Ws, nik_vp(op)(T_par_abstract<ParAbstract::alias, Op, Ws...>*), auto... Vs>
	nik_ce auto eval<op, Vs...> = eval<Op, Ws..., Vs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// access:

/***********************************************************************************************************************/

// operators:

	struct ParAccess
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.
			is_const , add_const , remove_const ,	// basis
			csame ,					// comparison
			dimension
		};
	};

/***********************************************************************************************************************/

// matchers:

	// is const:

		template<typename T> struct is_const			{ nik_ces auto result = false; };
		template<typename T> struct is_const<T const>		{ nik_ces auto result = true;  };

	// add const:

		template<typename T> struct add_const			{ using result = T const; };
		template<typename T> struct add_const<T const>		{ using result = T const; };

	// remove const:

		template<typename T> struct remove_const		{ using result = T; };
		template<typename T> struct remove_const<T const>	{ using result = T; };

/***********************************************************************************************************************/

// basis:

	// is const:

		nik_ce auto _is_const_ = U_par_access<ParAccess::is_const>;

		template<auto U>
		nik_ce auto eval<_is_const_, U> = reflect<is_const, U>;

	// add const:

		nik_ce auto _add_const_ = U_par_access<ParAccess::add_const>;

		template<auto U>
		nik_ce auto eval<_add_const_, U> = modify<add_const, U>;

	// remove const:

		nik_ce auto _remove_const_ = U_par_access<ParAccess::remove_const>;

		template<auto U>
		nik_ce auto eval<_remove_const_, U> = modify<remove_const, U>;

	// to const (optimization):

		nik_ce auto _to_const_ = _add_const_;

	// from const (optimization):

		nik_ce auto _from_const_ = _remove_const_;

/***********************************************************************************************************************/

// comparison:

	// csame:

		nik_ce auto _csame_ = U_par_access<ParAccess::csame>;

		template<auto V0, auto V1>
		nik_ce auto eval<_csame_, V0, V1> = eval
		<
			_same_,
			eval<_to_const_, V0>,
			eval<_to_const_, V1>
		>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// boolean:

/***********************************************************************************************************************/

// operators:

	struct ParBoolean
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.
			if_then_else , stem , costem , distem ,
			dimension
		};
	};

/***********************************************************************************************************************/

// if then else:

	nik_ce auto _if_then_else_ = U_par_boolean<ParBoolean::if_then_else>;

	template<auto ante, auto conse> nik_ce auto eval<_if_then_else_, true , ante, conse> = ante;
	template<auto ante, auto conse> nik_ce auto eval<_if_then_else_, false, ante, conse> = conse;

/***********************************************************************************************************************/

// stem:

	nik_ce auto _stem_ = U_par_boolean<ParBoolean::stem>;

	template<auto ante, auto conse, auto... Vs>
	nik_ce auto eval<_stem_, true , ante, conse, Vs...> = ante;

	template<auto ante, auto conse, auto... Vs>
	nik_ce auto eval<_stem_, false, ante, conse, Vs...> = eval<conse, Vs...>;

/***********************************************************************************************************************/

// costem:

	nik_ce auto _costem_ = U_par_boolean<ParBoolean::costem>;

	template<auto ante, auto conse, auto... Vs>
	nik_ce auto eval<_costem_, true, ante, conse, Vs...> = eval<ante, Vs...>;

	template<auto ante, auto conse, auto... Vs>
	nik_ce auto eval<_costem_, false , ante, conse, Vs...> = conse;

/***********************************************************************************************************************/

// distem:

	nik_ce auto _distem_ = U_par_boolean<ParBoolean::distem>;

	template<auto ante, auto conse, auto... Vs>
	nik_ce auto eval<_distem_, true, ante, conse, Vs...> = eval<ante, Vs...>;

	template<auto ante, auto conse, auto... Vs>
	nik_ce auto eval<_distem_, false, ante, conse, Vs...> = eval<conse, Vs...>;

/***********************************************************************************************************************/

// syntactic sugar:

	template<bool Pred, auto... Vs> nik_ce auto if_then_else_ = eval<_if_then_else_, Pred, Vs...>;
	template<bool Pred, auto... Vs> nik_ce auto stem_         = eval<_stem_, Pred, Vs...>;
	template<bool Pred, auto... Vs> nik_ce auto costem_       = eval<_costem_, Pred, Vs...>;
	template<bool Pred, auto... Vs> nik_ce auto distem_       = eval<_distem_, Pred, Vs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// pointer:

/***********************************************************************************************************************/

// operators:

	struct ParPointer
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.
			is , add , remove , to , // basis
			dimension
		};
	};

/***********************************************************************************************************************/

// matchers:

	// is pointer:

		template<typename T> struct is_pointer			{ nik_ces auto result = false; };
		template<typename T> struct is_pointer<T*>		{ nik_ces auto result = true;  };

	// add pointer:

		template<typename T> struct add_pointer			{ using result = T*; };
		template<typename T> struct add_pointer<T*>		{ using result = T*; };

	// remove pointer:

		template<typename T> struct remove_pointer		{ using result = T; };
		template<typename T> struct remove_pointer<T*>		{ using result = T; };

/***********************************************************************************************************************/

// basis:

	// is:

		nik_ce auto _is_pointer_ = U_par_pointer<ParPointer::is>;

		template<auto U>
		nik_ce auto eval<_is_pointer_, U> = reflect<is_pointer, U>;

	// add:

		nik_ce auto _add_pointer_ = U_par_pointer<ParPointer::add>;

		template<auto U>
		nik_ce auto eval<_add_pointer_, U> = modify<add_pointer, U>;

	// remove:

		nik_ce auto _remove_pointer_ = U_par_pointer<ParPointer::remove>;

		template<auto U>
		nik_ce auto eval<_remove_pointer_, U> = modify<remove_pointer, U>;

	// to:

		nik_ce auto _to_pointer_ = U_par_pointer<ParPointer::to>;

		template<auto U>
		nik_ce auto eval<_to_pointer_, U> = stem_
		<
			eval<_is_pointer_, U>, U, _add_pointer_, U
		>;

	// from (optimization):

		nik_ce auto _from_pointer_ = _remove_pointer_;

/***********************************************************************************************************************/

// syntactic sugar:

	template<auto U>
	using from_const = T_store_U<eval<_from_const_, U>>;

	template<auto U>
	using from_cptr = T_store_U<eval<_from_const_, eval<_from_pointer_, U>>>;

	template<auto U> // assumes U is a pointer type.
	using to_mptr = from_cptr<U> *;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

