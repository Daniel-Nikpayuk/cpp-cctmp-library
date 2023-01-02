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

// default:

	template<auto Op, bool V>
	nik_ce auto eval_assert() { static_assert(V, "eval: undefined operator"); }

	template<auto Op, auto... Vs>
	nik_ce auto eval = eval_assert<Op, false>();

/***********************************************************************************************************************/

// argument:

	template<auto Key, auto Op, auto... Ws, nik_vp(op)(T_argument<Key, Op, Ws...>*), auto... Vs>
	nik_ce auto eval<op, Vs...> = T_argument<Key, Op, Ws...>::template result<decltype(Vs)...>(Vs...);

// alias (defined after eval):

	template<auto, auto...> struct T_alias;

	template<auto Op, auto... Ws, nik_vp(op)(T_alias<Op, Ws...>*), auto... Vs>
	nik_ce auto eval<op, Vs...> = eval<Op, Ws..., Vs...>;

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

// comparison:

	// same:

		nik_ce auto _same_ = U_par_abstract<Abstract::same>;

		template<auto V0, auto V1> nik_ce auto eval<_same_, V0, V1> = false;
		template<auto V>           nik_ce auto eval<_same_, V , V > = true;

/***********************************************************************************************************************/

// variadic:

	// is null:

		nik_ce auto _is_null_ = U_par_abstract<Abstract::is_null>;

		template<auto... Vs>
		nik_ce auto eval<_is_null_, Vs...> = (sizeof...(Vs) == 0);

	// length:

		nik_ce auto _length_ = U_par_abstract<Abstract::length>;

		template<auto... Vs>
		nik_ce auto eval<_length_, Vs...> = sizeof...(Vs);

	// car:

		nik_ce auto _car_ = U_par_abstract<Abstract::car>;
		nik_ce auto _nop_ = _car_; // syntactic sugar.

		template<auto V0, auto... Vs>
		nik_ce auto eval<_car_, V0, Vs...> = V0;

	// cadr:

		nik_ce auto _cadr_ = U_par_abstract<Abstract::cadr>;

		template<auto V0, auto V1, auto... Vs>
		nik_ce auto eval<_cadr_, V0, V1, Vs...> = V1;

	// at (2^3):

		nik_ce auto _at_ = U_par_abstract<Abstract::at>;

		NIK_DEFINE_EVAL_AT(0, 1)
		NIK_DEFINE_EVAL_AT(1, 2)
		NIK_DEFINE_EVAL_AT(2, 3)
		NIK_DEFINE_EVAL_AT(3, 4)
		NIK_DEFINE_EVAL_AT(4, 5)
		NIK_DEFINE_EVAL_AT(5, 6)
		NIK_DEFINE_EVAL_AT(6, 7)
		NIK_DEFINE_EVAL_AT(7, 8)

	// find:

		nik_ce auto _find_ = U_par_abstract<Abstract::find>;

		template<const bool *arr, gindex_type size>
		nik_ce auto eval_find()
		{
			nik_ce auto U_find = _multifind_<_dereference_>;
			nik_ce auto cur    = T_store_U<U_find>::result(arr, arr + size);

			return cur - arr;
		}

		template<auto Op, auto... Vs>
		nik_ce auto eval<_find_, Op, Vs...> = eval_find<array<bool const, eval<Op, Vs>...>, sizeof...(Vs)>();

/***********************************************************************************************************************/

// syntactic sugar:

	template<auto Op, auto... Vs>
	nik_ce auto find_ = eval<_find_, Op, Vs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// access:

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

		nik_ce auto _is_const_ = U_par_access<Access::is_const>;

		template<auto U>
		nik_ce auto eval<_is_const_, U> = reflect<is_const, U>;

	// add const:

		nik_ce auto _add_const_ = U_par_access<Access::add_const>;

		template<auto U>
		nik_ce auto eval<_add_const_, U> = modify<add_const, U>;

	// remove const:

		nik_ce auto _remove_const_ = U_par_access<Access::remove_const>;

		template<auto U>
		nik_ce auto eval<_remove_const_, U> = modify<remove_const, U>;

	// to const (optimization):

		nik_ce auto _to_const_ = U_par_access<Access::to_const>;

		template<auto U>
		nik_ce auto eval<_to_const_, U> = modify<add_const, U>;

	// from const (optimization):

		nik_ce auto _from_const_ = U_par_access<Access::from_const>;

		template<auto U>
		nik_ce auto eval<_from_const_, U> = modify<remove_const, U>;

/***********************************************************************************************************************/

// comparison:

	// csame:

		nik_ce auto _csame_ = U_par_access<Access::csame>;

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

// basis:

	// name:

		nik_ce auto _name_ = U_par_list<List::name>;

		template<template<auto...> typename B, auto... Vs, nik_vp(p)(B<Vs...>*)>
		nik_ce auto eval<_name_, p> = U_store_B<B>;

/***********************************************************************************************************************/

// comparison:

	// similar:

		nik_ce auto _similar_ = U_par_list<List::similar>;

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

		nik_ce auto _to_list_ = U_par_list<List::to_list>;

		template<template<auto...> typename B, nik_vp(b)(T_store_B<B>*), auto... Vs>
		nik_ce auto eval<_to_list_, b, Vs...> = U_store_T<B<Vs...>>;

	// front (zero) unpack:

		nik_ce auto _f0_unpack_ = U_par_list<List::f0_unpack>;

		template<template<auto...> typename B, auto... Ws, nik_vp(p)(B<Ws...>*), auto... Vs>
		nik_ce auto eval<_f0_unpack_, p, Vs...> = eval<Ws..., Vs...>;

	// front (one) unpack:

		nik_ce auto _f1_unpack_ = U_par_list<List::f1_unpack>;

		template<template<auto...> typename B, auto... Ws, nik_vp(p)(B<Ws...>*), auto V0, auto... Vs>
		nik_ce auto eval<_f1_unpack_, p, V0, Vs...> = eval<V0, Ws..., Vs...>;

	// front (two) unpack:

		nik_ce auto _f2_unpack_ = U_par_list<List::f2_unpack>;

		template<template<auto...> typename B, auto... Ws, nik_vp(p)(B<Ws...>*), auto V0, auto V1, auto... Vs>
		nik_ce auto eval<_f2_unpack_, p, V0, V1, Vs...> = eval<V0, V1, Ws..., Vs...>;

	// back (zero) unpack:

		nik_ce auto _b0_unpack_ = U_par_list<List::b0_unpack>;

		template<template<auto...> typename B, auto... Ws, nik_vp(p)(B<Ws...>*), auto... Vs>
		nik_ce auto eval<_b0_unpack_, p, Vs...> = eval<Vs..., Ws...>;

	// back (one) unpack:

		nik_ce auto _b1_unpack_ = U_par_list<List::b1_unpack>;

		template<template<auto...> typename B, auto W0, auto... Ws, nik_vp(p)(B<W0, Ws...>*), auto... Vs>
		nik_ce auto eval<_b1_unpack_, p, Vs...> = eval<W0, Vs..., Ws...>;

	// back (two) unpack:

		nik_ce auto _b2_unpack_ = U_par_list<List::b2_unpack>;

		template<template<auto...> typename B, auto W0, auto W1, auto... Ws, nik_vp(p)(B<W0, W1, Ws...>*), auto... Vs>
		nik_ce auto eval<_b2_unpack_, p, Vs...> = eval<W0, W1, Vs..., Ws...>;

	// rename:

		nik_ce auto _rename_ = U_par_list<List::rename>;

		template<auto b, auto p>
		nik_ce auto eval<_rename_, b, p> = eval<_b0_unpack_, p, _to_list_, b>;

/***********************************************************************************************************************/

// functional:

	// pad:

		nik_ce auto _pad_ = U_par_list<List::pad>;

		NIK_DEFINE_EVAL_PADS(65)

	// cdr:

		nik_ce auto _cdr_ = U_par_list<List::cdr>;

		template<auto b, auto V0, auto... Vs>
		nik_ce auto eval<_cdr_, b, V0, Vs...> = eval<_to_list_, b, Vs...>;

	// map:

		nik_ce auto _map_ = U_par_list<List::map>;

		template<auto b, auto Op, auto... Vs>
		nik_ce auto eval<_map_, b, Op, Vs...> = eval<_to_list_, b, eval<Op, Vs>...>;

	// zip:

		nik_ce auto _zip_ = U_par_list<List::zip>;

		template<auto b, auto Op, template<auto...> typename B, auto... Ws, nik_vp(p)(B<Ws...>*), auto... Vs>
		nik_ce auto eval<_zip_, b, Op, p, Vs...> = eval<_to_list_, b, eval<Op, Ws, Vs>...>;

	// unite (optimization):

		// alt == eval<_b0_unpack_, p2, _f2_unpack_, p1, _to_list_, b, Vs...>;

		nik_ce auto _unite_ = U_par_list<List::unite>;

		template
		<
			auto b,
			template<auto...> typename B0, auto... Xs, nik_vp(p0)(B0<Xs...>*),
			template<auto...> typename B1, auto... Ws, nik_vp(p1)(B1<Ws...>*),
			auto... Vs
		>
		nik_ce auto eval<_unite_, b, p0, p1, Vs...> = eval<_to_list_, b, Xs..., Vs..., Ws...>;

	// cons:

		nik_ce auto _cons_ = U_par_list<List::cons>;

		template<auto b, auto p, auto... Vs>
		nik_ce auto eval<_cons_, b, p, Vs...> = eval<_unite_, b, U_null_Vs, p, Vs...>;

	// push:

		nik_ce auto _push_ = U_par_list<List::push>;

		template<auto b, auto p, auto... Vs>
		nik_ce auto eval<_push_, b, p, Vs...> = eval<_unite_, b, p, U_null_Vs, Vs...>;

/***********************************************************************************************************************/

// syntactic sugar:

	template<auto Op, auto... Vs>
	nik_ce auto listload_ = eval<Op, H_id, Vs...>;

	template<auto b, auto... Vs>
	nik_ce auto to_list_ = eval<_to_list_, b, Vs...>;

	template<auto b, auto... Vs>
	nik_ce auto list_ = eval<_to_list_, H_id, Vs...>;

	template<auto p, auto Op, auto... Vs>
	nik_ce auto unpack_ = eval<_b0_unpack_, p, Op, Vs...>;

	template<auto b, auto Op, auto... Vs>
	nik_ce auto map_ = eval<_map_, b, Op, Vs...>;

	template<auto b, auto Op, auto p, auto... Vs>
	nik_ce auto zip_ = eval<_zip_, b, Op, p, Vs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// boolean:

/***********************************************************************************************************************/

// basis:

	// if then else:

		nik_ce auto _if_then_else_ = U_par_boolean<Boolean::if_then_else>;

		template<auto ante, auto conse> nik_ce auto eval<_if_then_else_, true , ante, conse> = ante;
		template<auto ante, auto conse> nik_ce auto eval<_if_then_else_, false, ante, conse> = conse;

/***********************************************************************************************************************/

// syntactic sugar:

	template<auto... Vs>
	nik_ce auto if_then_else_ = eval<_if_then_else_, Vs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// number:

/***********************************************************************************************************************/

// basis:

	// is unsigned:

		nik_ce auto _is_unsigned_ = U_par_number<Number::is_unsigned>;

		template<auto V>                         nik_ce auto eval<_is_unsigned_, V> = false;
		template<nik_vp(V)(unsigned char     *)> nik_ce auto eval<_is_unsigned_, V> = true;
		template<nik_vp(V)(unsigned short    *)> nik_ce auto eval<_is_unsigned_, V> = true;
		template<nik_vp(V)(unsigned int      *)> nik_ce auto eval<_is_unsigned_, V> = true;
		template<nik_vp(V)(unsigned long     *)> nik_ce auto eval<_is_unsigned_, V> = true;
		template<nik_vp(V)(unsigned long long*)> nik_ce auto eval<_is_unsigned_, V> = true;

	// not unsigned:

		nik_ce auto _not_unsigned_ = U_par_number<Number::not_unsigned>;

		template<auto V>
		nik_ce auto eval<_not_unsigned_, V> = not(eval<_is_unsigned_, V>);

	// is signed:

		nik_ce auto _is_signed_ = U_par_number<Number::is_signed>;

		template<auto V>                       nik_ce auto eval<_is_signed_, V> = false;
		template<nik_vp(V)(signed char     *)> nik_ce auto eval<_is_signed_, V> = true;
		template<nik_vp(V)(signed short    *)> nik_ce auto eval<_is_signed_, V> = true;
		template<nik_vp(V)(signed int      *)> nik_ce auto eval<_is_signed_, V> = true;
		template<nik_vp(V)(signed long     *)> nik_ce auto eval<_is_signed_, V> = true;
		template<nik_vp(V)(signed long long*)> nik_ce auto eval<_is_signed_, V> = true;

	// not signed:

		nik_ce auto _not_signed_ = U_par_number<Number::not_signed>;

		template<auto V>
		nik_ce auto eval<_not_signed_, V> = not(eval<_is_signed_, V>);

	// is integer:

		nik_ce auto _is_integer_ = U_par_number<Number::is_integer>;

		template<auto V>
		nik_ce auto eval<_is_integer_, V> = eval<_is_unsigned_, V> || eval<_is_signed_, V>;

	// not integer:

		nik_ce auto _not_integer_ = U_par_number<Number::not_integer>;

		template<auto V>
		nik_ce auto eval<_not_integer_, V> = not(eval<_is_integer_, V>);

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// pointer:

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

		nik_ce auto _is_pointer_ = U_par_pointer<Pointer::is>;

		template<auto U>
		nik_ce auto eval<_is_pointer_, U> = reflect<is_pointer, U>;

	// add:

		nik_ce auto _add_pointer_ = U_par_pointer<Pointer::add>;

		template<auto U>
		nik_ce auto eval<_add_pointer_, U> = modify<add_pointer, U>;

	// remove:

		nik_ce auto _remove_pointer_ = U_par_pointer<Pointer::remove>;

		template<auto U>
		nik_ce auto eval<_remove_pointer_, U> = modify<remove_pointer, U>;

	// to:

		nik_ce auto _to_pointer_ = U_par_pointer<Pointer::to>;

		template<auto U>
		nik_ce auto eval<_to_pointer_, U> = eval
		<
			if_then_else_
			<
				eval<_is_pointer_, U>,
				_nop_,
				_add_pointer_
			>,

			U
		>;

	// from (optimization):

		nik_ce auto _from_pointer_ = U_par_pointer<Pointer::from>;

		template<auto U>
		nik_ce auto eval<_from_pointer_, U> = modify<remove_pointer, U>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// reference:

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

		nik_ce auto _is_reference_ = U_par_reference<Reference::is>;

		template<auto U>
		nik_ce auto eval<_is_reference_, U> = reflect<is_reference, U>;

	// add:

		nik_ce auto _add_reference_ = U_par_reference<Reference::add>;

		template<auto U>
		nik_ce auto eval<_add_reference_, U> = modify<add_reference, U>;

	// remove:

		nik_ce auto _remove_reference_ = U_par_reference<Reference::remove>;

		template<auto U>
		nik_ce auto eval<_remove_reference_, U> = modify<remove_reference, U>;

	// to:

		nik_ce auto _to_reference_ = U_par_reference<Reference::to>;

		template<auto U>
		nik_ce auto eval<_to_reference_, U> = eval
		<
			if_then_else_
			<
				eval<_is_reference_, U>,
				_nop_,
				_add_reference_
			>,

			U
		>;

	// from (optimization):

		nik_ce auto _from_reference_ = U_par_reference<Reference::from>;

		template<auto U>
		nik_ce auto eval<_from_reference_, U> = modify<remove_reference, U>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// array:

/***********************************************************************************************************************/

// basis:

	// cons:

		nik_ce auto _to_array_ = U_par_array<Array::to_array>;

		template<auto U, auto... Vs>
		nik_ce auto eval<_to_array_, U, Vs...> = array<T_store_U<U>, Vs...>;

/***********************************************************************************************************************/

// near linear:

	// The size parameter (S) might seem redundant as one can potentially deduce it from sizeof...(Is),
	// but there are many contexts in which we know an initial size but not a final one.

	// apply:

		nik_ce auto _array_apply_ = U_par_array<Array::apply>;

		template
		<
			auto Op, auto U, auto S,
			template<auto...> typename B, auto... Is, nik_vp(p)(B<Is...>*),
			auto f, auto a, auto l, auto... as
		>
		nik_ce auto eval<_array_apply_, Op, U, S, p, f, a, l, as...> = eval
		<
			Op,
			T_store_U
			<
				_sequence_apply_<U, S, f>

			>::template result(a, a + l, as...).value[Is]...
		>;

/***********************************************************************************************************************/

// syntactic sugar:

	// map:

		template<auto f, auto a, auto l, auto Op, auto s, auto U, auto S>
		nik_ce auto array_map_ = eval<_array_apply_, Op, U, S, s, _multimap_<_arg_deref_<f>>, a, l>;

	// fold:

		template<auto f, auto init, auto a, auto l, auto Op, auto U, auto S>
		nik_ce auto array_fold_ = eval<_array_apply_, Op, U, S, U_pack_Vs<0>, _multifold_<_arg_deref_<f>, init>, a, l>;

	// find:

	//	template<auto p, auto a, auto l, auto Op, auto U, auto S>
	//	nik_ce auto array_find_ = eval<_array_apply_, Op, U, S, _multifind<_arg_deref_<p>>, a, l>;

	// sift:

/*
	// -> V:

		template<typename Type, auto p, auto Arr, auto Leng, auto... Is>
		nik_ce auto V_sift(nik_vp(indices)(T_pack_Vs<Is...>*))
		{
			nik_ce auto Size	= Leng + 1;
			nik_ce auto arr		= ArrayModule::template apply<Type, Size, IteratorModule::Sift, Leng, p>(Arr);
			nik_ce auto leng	= arr.value[Leng];

			if nik_ce (leng != sizeof...(Is)) return arr;
			else return array<Type, arr.value[Is]...>;
		}

		template<typename Type, auto p, auto Arr, auto Leng, auto I0, auto... Is>
		nik_ce auto V_sift(nik_vp(indices)(T_pack_Vs<I0, Is...>*))
		{
			nik_ce auto Size	= sizeof...(Is) + 1;
			nik_ce auto arr		= apply<Type, Size, IteratorModule::Sift, Leng, p>(Arr);

			return array<Type, arr.value[Is]...>;
		}

	// -> U:

		template<typename Type, auto p, auto Arr, auto Leng, auto I0, auto... Is>
		nik_ce auto U_sift(nik_vp(indices)(T_pack_Vs<I0, Is...>*))
		{
			nik_ce auto Size	= sizeof...(Is) + 1;
			nik_ce auto arr		= apply<Type, Size, IteratorModule::Sift, Leng, p>(Arr);

			return U_pack_Vs<arr.value[Is]...>;
		}
*/

	// subsequence:

/*
	// -> V:

		template<typename Type, auto p, auto Arr, auto Leng, auto... Is>
		nik_ce auto V_subsequence(nik_vp(indices)(T_pack_Vs<Is...>*))
			{ return V_apply<Type, IteratorModule::Sift, Arr>(U_pack_Vs<Leng, sizeof...(Is), p>, indices); }

	// -> U:

		template<typename Type, auto p, auto Arr, auto Leng, auto... Is>
		nik_ce auto U_subsequence(nik_vp(indices)(T_pack_Vs<Is...>*))
			{ return U_apply<Type, IteratorModule::Sift, Arr>(U_pack_Vs<Leng, sizeof...(Is), p>, indices); }
*/

	// zip:

/*
	// generic:

	// -> V:

		template<typename Type, auto f, auto Arr1, auto Leng1, auto Arr2, typename Indices>
		nik_ce auto V_zip(Indices indices)
			{ return V_apply<Type, IteratorModule::Zip, Arr1, Arr2>(U_pack_Vs<Leng1, f>, indices); }

	// -> U:

		template<typename Type, auto f, auto Arr1, auto Leng1, auto Arr2, typename Indices>
		nik_ce auto U_zip(Indices indices)
			{ return U_apply<Type, IteratorModule::Zip, Arr1, Arr2>(U_pack_Vs<Leng1, f>, indices); }
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// function:

/***********************************************************************************************************************/

// meta:

	// type:

		nik_ce auto _function_type_ = U_par_function<Function::type>;

		template<typename OutType, typename... InTypes, OutType(*f)(InTypes...)>
		nik_ce auto eval<_function_type_, f> = U_store_T<OutType(*)(InTypes...)>;

	// arity:

		nik_ce auto _function_arity_ = U_par_function<Function::arity>;

		template<typename OutType, typename... InTypes, OutType(*f)(InTypes...)>
		nik_ce auto eval<_function_arity_, f> = sizeof...(InTypes);

	// out type:

		nik_ce auto _function_out_type_ = U_par_function<Function::out_type>;

		template<typename OutType, typename... InTypes, OutType(*f)(InTypes...)>
		nik_ce auto eval<_function_out_type_, f> = U_store_T<OutType>;

	// in types:

		nik_ce auto _function_in_types_ = U_par_function<Function::in_types>;

		template
		<
			template<typename...> typename A, nik_vp(a)(T_store_A<A>*),
			typename OutType, typename... InTypes, OutType(*f)(InTypes...)
		>
		nik_ce auto eval<_function_in_types_, a, f> = U_store_T<A<InTypes...>>;

/***********************************************************************************************************************/

// call:

	// custom:

		template<auto U>           using T_custom_U = T_par_function<Function::custom, U>;
		template<auto U>     nik_ce auto U_custom_U = U_store_T<T_custom_U<U>>;
		template<typename T> nik_ce auto U_custom_T = U_custom_U<U_store_T<T>>;

		nik_ce auto _custom_ = U_par_function<Function::custom>;

		template<auto Op, auto... Vs>
		nik_ce auto eval<_custom_, Op, Vs...> = T_store_U<Op>::template result<Vs...>;

		template<auto Op, nik_vp(op)(T_custom_U<Op>*), auto... Vs>
		nik_ce auto eval<op, Vs...> = T_store_U<Op>::template result<Vs...>;

		// Required for compile time register machines.

		template<auto Op, nik_vp(op)(T_custom_U<Op>*), auto... Vs>
		nik_ce auto eval<_custom_, op, Vs...> = T_store_U<Op>::template result<Vs...>;

	// nested:

		nik_ce auto _nested_ = U_par_function<Function::nested>;

		template<auto d, auto Op, auto... Vs>
		nik_ce auto eval<_nested_, d, Op, Vs...> = T_store_U<Op>::template result<d, Vs...>;

		// Required for compile time register machines.

		template<auto d, auto Op, nik_vp(op)(T_custom_U<Op>*), auto... Vs>
		nik_ce auto eval<_nested_, d, op, Vs...> = T_store_U<Op>::template result<d, Vs...>;

	// procedure:

		nik_ce auto _procedure_ = U_par_function<Function::procedure>;

		template<auto Op, auto... Vs>
		nik_ce auto eval<_procedure_, Op, Vs...> = T_store_U<Op>::result(Vs...);

	// method:

		nik_ce auto _method_ = U_par_function<Function::method>;

		template<auto Op, template<auto...> typename B, auto... Ws, nik_vp(p)(B<Ws...>*), auto... Vs>
		nik_ce auto eval<_method_, Op, p, Vs...> = T_store_U<Op>::template result<Ws...>(Vs...);

		// Required for compile time register machines.

		template
		<
			auto Op, nik_vp(op)(T_custom_U<Op>*),
			template<auto...> typename B, auto... Ws, nik_vp(p)(B<Ws...>*), auto... Vs
		>
		nik_ce auto eval<_method_, op, p, Vs...> = T_store_U<Op>::template result<Ws...>(Vs...);

	// tailor:

		nik_ce auto _tailor_ = U_par_function<Function::tailor>;

		template<auto Op, template<auto...> typename B, auto... Ws, nik_vp(p)(B<Ws...>*), auto... Vs>
		nik_ce auto eval<_tailor_, Op, p, Vs...> = T_store_U<Op>::template result<Vs...>(Ws...);

/***********************************************************************************************************************/

// syntactic sugar:

	// meta:

		template<auto f>
		nik_ce auto f_type = eval<_function_type_, f>;

		template<auto f>
		nik_ce auto arity = eval<_function_arity_, f>;

		template<auto f>
		nik_ce auto out_type = eval<_function_out_type_, f>;

		template<auto f>
		using T_out_type = T_store_U<out_type<f>>;

		template<auto f>
		nik_ce auto in_types = eval<_function_in_types_, f>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// identity:

/***********************************************************************************************************************/

// list to:

	// array:

		nik_ce auto _list_to_array_ = U_par_identity<Identity::list_to_array>;

		template<auto U, auto p>
		nik_ce auto eval<_list_to_array_, U, p> = eval<_b0_unpack_, p, _to_array_, U>;

/***********************************************************************************************************************/

// array to:

	// list:

		nik_ce auto _array_to_list_ = U_par_identity<Identity::array_to_list>;

		template<auto b, auto a, auto... Vs>
		nik_ce auto eval<_array_to_list_, b, a, Vs...> = eval<_to_list_, b, a[Vs]...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// using:

/***********************************************************************************************************************/

	template<template<auto...> typename B, auto... Ws>
	struct T_using
	{
		template<auto... Vs>
		using result = B<Ws..., Vs...>;
	};

	// syntactic sugar:

		template<auto... Vs>
		using T_eval = T_store_U<eval<Vs...>>;

		template<template<auto...> typename B, auto... Ws>
		nik_ce auto H_using = U_store_B<T_using<B, Ws...>::template result>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// alias:

/***********************************************************************************************************************/

	template<auto Op, auto... Ws>
	struct T_alias
	{
		template<auto... Vs>
		nik_ces auto result = eval<Op, Ws..., Vs...>;

	}; template<auto Op, auto... Ws>
		nik_ce auto _alias_ = U_store_T<T_alias<Op, Ws...>>;

	// syntactic sugar:

		template<auto H = H_id> nik_ce auto _list_	= _alias_<_to_list_, H>;
		template<auto H = H_id> nik_ce auto _cdr_list_	= _alias_<_cdr_, H>;
		template<auto U> nik_ce auto _array_		= _alias_<_to_array_, U>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// (recursive eval):

	// In general defer to the compile time register machine,
	// but there are occassions where this might be preferred.

/***********************************************************************************************************************/

	template<auto... Vs>
	nik_ce auto reval = eval<reval<Vs>...>;

	template<auto V>
	nik_ce auto reval<V> = V;

	template<auto... Vs, nik_vp(alias)(T_alias<Vs...>*)>
	nik_ce auto reval<alias> = eval<reval<Vs>...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

