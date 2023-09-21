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
			same ,				// comparison
			is_null , length , car , cadr ,	// variadic
			alias ,				// operational
			dimension
		};
	};

/***********************************************************************************************************************/

// comparison:

	// same:

		nik_ce auto _same_ = U_par_abstract<ParAbstract::same>;

		template<auto V0, auto V1> nik_ce auto eval<_same_, V0, V1> = false;
		template<auto V>           nik_ce auto eval<_same_, V , V > = true;

/***********************************************************************************************************************/

// variadic:

	// is null:

		nik_ce auto _is_null_ = U_par_abstract<ParAbstract::is_null>;

		template<auto... Vs>
		nik_ce auto eval<_is_null_, Vs...> = (sizeof...(Vs) == 0);

	// length:

		nik_ce auto _length_ = U_par_abstract<ParAbstract::length>;

		template<auto... Vs>
		nik_ce auto eval<_length_, Vs...> = sizeof...(Vs);

	// car:

		nik_ce auto _car_ = U_par_abstract<ParAbstract::car>;

		template<auto V0, auto... Vs>
		nik_ce auto eval<_car_, V0, Vs...> = V0;

	// cadr:

		nik_ce auto _cadr_ = U_par_abstract<ParAbstract::cadr>;

		template<auto V0, auto V1, auto... Vs>
		nik_ce auto eval<_cadr_, V0, V1, Vs...> = V1;

/***********************************************************************************************************************/

// operational:

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
			is_const , add_const , remove_const , to_const , from_const ,	// basis
			csame ,								// comparison
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

		nik_ce auto _to_const_ = U_par_access<ParAccess::to_const>;

		template<auto U>
		nik_ce auto eval<_to_const_, U> = modify<add_const, U>;

	// from const (optimization):

		nik_ce auto _from_const_ = U_par_access<ParAccess::from_const>;

		template<auto U>
		nik_ce auto eval<_from_const_, U> = modify<remove_const, U>;

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

// list:

/***********************************************************************************************************************/

// operators:

	struct ParList
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.
			name    ,					// basis
			similar ,					// comparison
			to_list , b0_unpack , rename ,			// variadic
			pad , cdr , map , zip , unite , cons , push ,	// functional
			dimension
		};
	};

/***********************************************************************************************************************/

// basis:

	// name:

		nik_ce auto _name_ = U_par_list<ParList::name>;

		template<template<auto...> typename B, auto... Vs, nik_vp(p)(B<Vs...>*)>
		nik_ce auto eval<_name_, p> = U_store_B<B>;

/***********************************************************************************************************************/

// comparison:

	// similar:

		nik_ce auto _similar_ = U_par_list<ParList::similar>;

		template<auto V0, auto V1>
		nik_ce auto eval<_similar_, V0, V1> = eval
		<
			_same_,
			eval<_name_, V0>,
			eval<_name_, V1>
		>;

/***********************************************************************************************************************/

// variadic:

	// to list:

		nik_ce auto _to_list_ = U_par_list<ParList::to_list>;

		template<template<auto...> typename B, nik_vp(b)(T_store_B<B>*), auto... Vs>
		nik_ce auto eval<_to_list_, b, Vs...> = U_store_T<B<Vs...>>;

	// back (zero) unpack:

		nik_ce auto _b0_unpack_ = U_par_list<ParList::b0_unpack>;

		template<template<auto...> typename B, auto... Ws, nik_vp(p)(B<Ws...>*), auto... Vs>
		nik_ce auto eval<_b0_unpack_, p, Vs...> = eval<Vs..., Ws...>;

	// rename:

		nik_ce auto _rename_ = U_par_list<ParList::rename>;

		template<auto b, auto p>
		nik_ce auto eval<_rename_, b, p> = eval<_b0_unpack_, p, _to_list_, b>;

/***********************************************************************************************************************/

// functional:

	// pad:

		nik_ce auto _pad_ = U_par_list<ParList::pad>;

		NIK_DEFINE_EVAL_PADS(65)

	// cdr:

		nik_ce auto _cdr_ = U_par_list<ParList::cdr>;

		template<auto b, auto V0, auto... Vs>
		nik_ce auto eval<_cdr_, b, V0, Vs...> = eval<_to_list_, b, Vs...>;

	// map:

		nik_ce auto _map_ = U_par_list<ParList::map>;

		template<auto b, auto Op, auto... Vs>
		nik_ce auto eval<_map_, b, Op, Vs...> = eval<_to_list_, b, eval<Op, Vs>...>;

	// zip:

		nik_ce auto _zip_ = U_par_list<ParList::zip>;

		template<auto b, auto Op, template<auto...> typename B, auto... Ws, nik_vp(p)(B<Ws...>*), auto... Vs>
		nik_ce auto eval<_zip_, b, Op, p, Vs...> = eval<_to_list_, b, eval<Op, Ws, Vs>...>;

	// unite (optimization):

		// alt == eval<_b0_unpack_, p2, _f2_unpack_, p1, _to_list_, b, Vs...>;

		nik_ce auto _unite_ = U_par_list<ParList::unite>;

		template
		<
			auto b,
			template<auto...> typename B0, auto... Xs, nik_vp(p0)(B0<Xs...>*),
			template<auto...> typename B1, auto... Ws, nik_vp(p1)(B1<Ws...>*),
			auto... Vs
		>
		nik_ce auto eval<_unite_, b, p0, p1, Vs...> = eval<_to_list_, b, Xs..., Vs..., Ws...>;

	// cons:

		nik_ce auto _cons_ = U_par_list<ParList::cons>;

		template<auto b, auto p, auto... Vs>
		nik_ce auto eval<_cons_, b, p, Vs...> = eval<_unite_, b, U_null_Vs, p, Vs...>;

	// push:

		nik_ce auto _push_ = U_par_list<ParList::push>;

		template<auto b, auto p, auto... Vs>
		nik_ce auto eval<_push_, b, p, Vs...> = eval<_unite_, b, p, U_null_Vs, Vs...>;

/***********************************************************************************************************************/

// syntactic sugar:

	template<auto V, auto n, auto... Vs>   nik_ce auto pad_      = eval<_pad_, H_id, V, n, Vs...>;

	template<auto b, auto... Vs>           nik_ce auto to_list_  = eval<_to_list_, b, Vs...>;
	template<auto... Vs>                   nik_ce auto list_     = eval<_to_list_, H_id, Vs...>;

	template<auto p, auto Op, auto... Vs>  nik_ce auto unpack_   = eval<_b0_unpack_, p, Op, Vs...>;
	template<auto p, auto... Vs>           nik_ce auto car_      = eval<_b0_unpack_, p, _car_, Vs...>;
	template<auto p, auto... Vs>           nik_ce auto cadr_     = eval<_b0_unpack_, p, _cadr_, Vs...>;
	template<auto p, auto... Vs>           nik_ce auto cdr_      = eval<_b0_unpack_, p, _cdr_, H_id, Vs...>;

	template<auto Op, auto... Vs>          nik_ce auto map_      = eval<_map_, H_id, Op, Vs...>;
	template<auto Op, auto p, auto... Vs>  nik_ce auto zip_      = eval<_zip_, H_id, Op, p, Vs...>;

	template<auto p0, auto p1, auto... Vs> nik_ce auto unite_    = eval<_unite_, H_id, p0, p1, Vs...>;
	template<auto p, auto... Vs>           nik_ce auto cons_     = eval<_unite_, H_id, U_null_Vs, p, Vs...>;
	template<auto p, auto... Vs>           nik_ce auto push_     = eval<_unite_, H_id, p, U_null_Vs, Vs...>;

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
			if_then_else ,						// basis
			stem         , costem , distem ,			// lazy
			and_wise     ,						// propositional
			dimension
		};
	};

/***********************************************************************************************************************/

// basis:

	// if then else:

		nik_ce auto _if_then_else_ = U_par_boolean<ParBoolean::if_then_else>;

		template<auto ante, auto conse> nik_ce auto eval<_if_then_else_, true , ante, conse> = ante;
		template<auto ante, auto conse> nik_ce auto eval<_if_then_else_, false, ante, conse> = conse;

/***********************************************************************************************************************/

// lazy:

	// stem:

		nik_ce auto _stem_ = U_par_boolean<ParBoolean::stem>;

		template<auto ante, auto conse, auto... Vs>
		nik_ce auto eval<_stem_, true , ante, conse, Vs...> = ante;

		template<auto ante, auto conse, auto... Vs>
		nik_ce auto eval<_stem_, false, ante, conse, Vs...> = eval<conse, Vs...>;

	// costem:

		nik_ce auto _costem_ = U_par_boolean<ParBoolean::costem>;

		template<auto ante, auto conse, auto... Vs>
		nik_ce auto eval<_costem_, true, ante, conse, Vs...> = eval<ante, Vs...>;

		template<auto ante, auto conse, auto... Vs>
		nik_ce auto eval<_costem_, false , ante, conse, Vs...> = conse;

	// distem:

		nik_ce auto _distem_ = U_par_boolean<ParBoolean::distem>;

		template<auto ante, auto conse, auto... Vs>
		nik_ce auto eval<_distem_, true, ante, conse, Vs...> = eval<ante, Vs...>;

		template<auto ante, auto conse, auto... Vs>
		nik_ce auto eval<_distem_, false, ante, conse, Vs...> = eval<conse, Vs...>;

/***********************************************************************************************************************/

// propositional:

	// and wise:

		nik_ce auto _and_wise_ = U_par_boolean<ParBoolean::and_wise>;

		template<template<auto...> typename B, auto... Preds, nik_vp(p)(B<Preds...>*), auto... Vs>
		nik_ce auto eval<_and_wise_, p, Vs...> = eval<_and_, eval<Preds, Vs>...>;

/***********************************************************************************************************************/

// syntactic sugar:

	template<bool Pred, auto... Vs> nik_ce auto if_then_else_ = eval<_if_then_else_, Pred, Vs...>;
	template<bool Pred, auto... Vs> nik_ce auto stem_         = eval<_stem_, Pred, Vs...>;
	template<bool Pred, auto... Vs> nik_ce auto costem_       = eval<_costem_, Pred, Vs...>;
	template<bool Pred, auto... Vs> nik_ce auto distem_       = eval<_distem_, Pred, Vs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// number:

/***********************************************************************************************************************/

// operators:

	struct ParNumber
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.
			is_unsigned , not_unsigned ,	// basis
			is_signed   , not_signed   ,
			is_integer  , not_integer  ,
			dimension
		};
	};

/***********************************************************************************************************************/

// basis:

	// is unsigned:

		nik_ce auto _is_unsigned_ = U_par_number<ParNumber::is_unsigned>;

		template<auto V>                         nik_ce auto eval<_is_unsigned_, V> = false;
		template<nik_vp(V)(unsigned char     *)> nik_ce auto eval<_is_unsigned_, V> = true;
		template<nik_vp(V)(unsigned short    *)> nik_ce auto eval<_is_unsigned_, V> = true;
		template<nik_vp(V)(unsigned int      *)> nik_ce auto eval<_is_unsigned_, V> = true;
		template<nik_vp(V)(unsigned long     *)> nik_ce auto eval<_is_unsigned_, V> = true;
		template<nik_vp(V)(unsigned long long*)> nik_ce auto eval<_is_unsigned_, V> = true;

	// not unsigned:

		nik_ce auto _not_unsigned_ = U_par_number<ParNumber::not_unsigned>;

		template<auto V>
		nik_ce auto eval<_not_unsigned_, V> = not eval<_is_unsigned_, V>;

	// is signed:

		nik_ce auto _is_signed_ = U_par_number<ParNumber::is_signed>;

		template<auto V>                       nik_ce auto eval<_is_signed_, V> = false;
		template<nik_vp(V)(signed char     *)> nik_ce auto eval<_is_signed_, V> = true;
		template<nik_vp(V)(signed short    *)> nik_ce auto eval<_is_signed_, V> = true;
		template<nik_vp(V)(signed int      *)> nik_ce auto eval<_is_signed_, V> = true;
		template<nik_vp(V)(signed long     *)> nik_ce auto eval<_is_signed_, V> = true;
		template<nik_vp(V)(signed long long*)> nik_ce auto eval<_is_signed_, V> = true;

	// not signed:

		nik_ce auto _not_signed_ = U_par_number<ParNumber::not_signed>;

		template<auto V>
		nik_ce auto eval<_not_signed_, V> = not eval<_is_signed_, V>;

	// is integer:

		nik_ce auto _is_integer_ = U_par_number<ParNumber::is_integer>;

		template<auto V>
		nik_ce auto eval<_is_integer_, V> = eval<_is_unsigned_, V> || eval<_is_signed_, V>;

	// not integer:

		nik_ce auto _not_integer_ = U_par_number<ParNumber::not_integer>;

		template<auto V>
		nik_ce auto eval<_not_integer_, V> = not eval<_is_integer_, V>;

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
			is , add , remove , to , from , // basis
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

		nik_ce auto _from_pointer_ = U_par_pointer<ParPointer::from>;

		template<auto U>
		nik_ce auto eval<_from_pointer_, U> = modify<remove_pointer, U>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// reference:

/***********************************************************************************************************************/

// operators:

	struct ParReference
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.
			is , add , remove , to , from , // basis
			dimension
		};
	};

/***********************************************************************************************************************/

// matchers:

	// is reference:

		template<typename T> struct is_reference		{ nik_ces auto result = false; };
		template<typename T> struct is_reference<T&>		{ nik_ces auto result = true;  };

	// add reference:

		template<typename T> struct add_reference		{ using result = T&; };
		template<typename T> struct add_reference<T&>		{ using result = T&; };

	// remove reference:

		template<typename T> struct remove_reference		{ using result = T; };
		template<typename T> struct remove_reference<T&>	{ using result = T; };

/***********************************************************************************************************************/

// basis:

	// is:

		nik_ce auto _is_reference_ = U_par_reference<ParReference::is>;

		template<auto U>
		nik_ce auto eval<_is_reference_, U> = reflect<is_reference, U>;

	// add:

		nik_ce auto _add_reference_ = U_par_reference<ParReference::add>;

		template<auto U>
		nik_ce auto eval<_add_reference_, U> = modify<add_reference, U>;

	// remove:

		nik_ce auto _remove_reference_ = U_par_reference<ParReference::remove>;

		template<auto U>
		nik_ce auto eval<_remove_reference_, U> = modify<remove_reference, U>;

	// to:

		nik_ce auto _to_reference_ = U_par_reference<ParReference::to>;

		template<auto U>
		nik_ce auto eval<_to_reference_, U> = stem_
		<
			eval<_is_reference_, U>, U, _add_reference_, U
		>;

	// from (optimization):

		nik_ce auto _from_reference_ = U_par_reference<ParReference::from>;

		template<auto U>
		nik_ce auto eval<_from_reference_, U> = modify<remove_reference, U>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// array:

/***********************************************************************************************************************/

// operators:

	struct ParArray
	{
		enum : gkey_type
		{
			id = 0, identity = id,	// convenience for default params.
			to_array  ,		// basis
			dimension
		};
	};

/***********************************************************************************************************************/

// basis:

	// cons:

		nik_ce auto _to_array_ = U_par_array<ParArray::to_array>;

		template<auto U, auto... Vs>
		nik_ce auto eval<_to_array_, U, Vs...> = array<T_store_U<U>, Vs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// function:

/***********************************************************************************************************************/

// operators:

	struct ParFunction
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.
			type , arity , out_type , in_types ,		// meta
			eval , procedure , method , tailor , custom ,	// call
			dimension
		};
	};

/***********************************************************************************************************************/

// meta:

	// type:

		nik_ce auto _function_type_ = U_par_function<ParFunction::type>;

		template<typename OutType, typename... InTypes, OutType(*f)(InTypes...)>
		nik_ce auto eval<_function_type_, f> = U_store_T<OutType(*)(InTypes...)>;

	// arity:

		nik_ce auto _function_arity_ = U_par_function<ParFunction::arity>;

		template<typename OutType, typename... InTypes, OutType(*f)(InTypes...)>
		nik_ce auto eval<_function_arity_, f> = sizeof...(InTypes);

	// out type:

		nik_ce auto _function_out_type_ = U_par_function<ParFunction::out_type>;

		template<typename OutType, typename... InTypes, OutType(*f)(InTypes...)>
		nik_ce auto eval<_function_out_type_, f> = U_store_T<OutType>;

	// in types:

		nik_ce auto _function_in_types_ = U_par_function<ParFunction::in_types>;

		template
		<
			template<typename...> typename A, nik_vp(a)(T_store_A<A>*),
			typename OutType, typename... InTypes, OutType(*f)(InTypes...)
		>
		nik_ce auto eval<_function_in_types_, a, f> = U_store_T<A<InTypes...>>;

/***********************************************************************************************************************/

// call:

	// eval:

		nik_ce auto _eval_ = U_par_function<ParFunction::eval>;

		template<auto Op1, auto Op0, auto... Vs>
		nik_ce auto eval<_eval_, Op1, Op0, Vs...> = eval<Op1, eval<Op0, Vs...>>;

	// procedure:

		nik_ce auto _procedure_ = U_par_function<ParFunction::procedure>;

		template<auto Op, auto... Vs>
		nik_ce auto eval<_procedure_, Op, Vs...> = T_store_U<Op>::result(Vs...);

	// method:

		nik_ce auto _method_ = U_par_function<ParFunction::method>;

		template<auto Op, template<auto...> typename B, auto... Ws, nik_vp(p)(B<Ws...>*), auto... Vs>
		nik_ce auto eval<_method_, Op, p, Vs...> = T_store_U<Op>::template result<Ws...>(Vs...);

	// tailor:

		nik_ce auto _tailor_ = U_par_function<ParFunction::tailor>;

		template<auto Op, template<auto...> typename B, auto... Ws, nik_vp(p)(B<Ws...>*), auto... Vs>
		nik_ce auto eval<_tailor_, Op, p, Vs...> = T_store_U<Op>::template result<Vs...>(Ws...);

		// syntactic sugar:

		//	template<auto H = H_id> nik_ce auto _list_	= _alias_<_to_list_, H>;
		//	template<auto H = H_id> nik_ce auto _cdr_list_	= _alias_<_cdr_, H>;
		//	template<auto U> nik_ce auto _array_		= _alias_<_to_array_, U>;
		//	template<auto F, auto G> nik_ce auto _pose_	= _alias_<_eval_, F, G>;
		//	template<auto U> nik_ce auto _id_to_cref_	= _pose_<_to_reference_, _to_const_>;
		//	template<auto U> nik_ce auto _cref_to_id_	= _pose_<_from_const_, _from_reference_>;

	// custom:

		template<auto Op>          using T_custom   = T_par_function<ParFunction::custom, Op>;
		template<auto Op>    nik_ce auto  _custom_  = U_store_T<T_custom<Op>>;
		template<typename T> nik_ce auto U_custom_T = _custom_<U_store_T<T>>;

		template<auto Op, nik_vp(op)(T_custom<Op>*), auto... Vs>
		nik_ce auto eval<op, Vs...> = T_store_U<Op>::template result<Vs...>;

/***********************************************************************************************************************/

// syntactic sugar:

	// meta:

		template<auto f> nik_ce auto f_type	= eval<_function_type_, f>;
		template<auto f> nik_ce auto arity	= eval<_function_arity_, f>;
		template<auto f> nik_ce auto out_type	= eval<_function_out_type_, f>;
		template<auto f> using T_out_type	= T_store_U<out_type<f>>;
		template<auto f> nik_ce auto in_types	= eval<_function_in_types_, f>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// identity:

/***********************************************************************************************************************/

// operators:

	struct ParIdentity
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.
			list_to_array , // list to
			array_to_list , // array to
			dimension
		};
	};

/***********************************************************************************************************************/

// list to:

	// array:

		nik_ce auto _list_to_array_ = U_par_identity<ParIdentity::list_to_array>;

		template<auto U, auto p>
		nik_ce auto eval<_list_to_array_, U, p> = eval<_b0_unpack_, p, _to_array_, U>;

/***********************************************************************************************************************/

// array to:

	// list:

		nik_ce auto _array_to_list_ = U_par_identity<ParIdentity::array_to_list>;

		template<auto b, auto a, auto... Vs>
		nik_ce auto eval<_array_to_list_, b, a, Vs...> = eval<_to_list_, b, a[Vs]...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

