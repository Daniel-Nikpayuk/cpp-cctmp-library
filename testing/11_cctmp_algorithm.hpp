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

// dependencies:

/***********************************************************************************************************************/

//	template<auto Size>
//	nik_ce bool equals_charset(gstring_type b, gstring_type e, gcchar_type (&charset)[Size])
//	{
//		bool match = ((e-b) == Size);

//		for (gstring_type i = charset; match && i != charset + Size; ++b, ++i)
//			match = (*b == *i);

//		return match;
//	}

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

	nik_ce auto _dpar_erase_	= U_custom_T<T_interpreter_params< IT::cut   , _list_<>        >>;
	nik_ce auto _dpar_insert_	= U_custom_T<T_interpreter_params< IT::paste , _list_<> , _one >>;

	nik_ce auto _par_erase_		= _alias_< _dpar_erase_   , ID::initial_depth >;
	nik_ce auto _par_insert_	= _alias_< _dpar_insert_  , ID::initial_depth >;

/***********************************************************************************************************************/

// fold:

	struct T_interpreter_fold
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
			instruction < IN::call , IT::praxis , PN::fold , n >,
			instruction < IN::halt , IT::eval                  >
		>;

		template<auto d, auto Op, auto V, auto... Vs>
		nik_ces auto result = T_interpreter_start::template result<d, contr<sizeof...(Vs)>, V, Vs...>(H0<Op>);
	};

	nik_ce auto _dpar_fold_ = U_custom_T<T_interpreter_fold>;
	nik_ce auto  _par_fold_ = ID::template with_initial_depth<_dpar_fold_>;

/***********************************************************************************************************************/

// sift:

	struct T_interpreter_sift
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
			instruction < IN::call , IT::praxis , PN::sift , n >,
			instruction < IN::halt , IT::eval                  >
		>;

		template<auto d, auto Ops, auto... Vs>
		nik_ces auto result = T_interpreter_start::template result<d, contr<sizeof...(Vs)>, _zero, Vs...>(H0<Ops>);
	};

	nik_ce auto _dpar_sift_ = U_custom_T<T_interpreter_sift>;
	nik_ce auto  _par_sift_ = ID::template with_initial_depth<_dpar_sift_>;

/***********************************************************************************************************************/

// insert sort:

	template<auto Op>
	struct T_interpreter_insert_sort
	{
		nik_ces auto match = _alias_<_match_, Op>;
		nik_ces auto H0    = U_pack_Vs<_car_, _praxis_<match, _one>, _dpar_insert_>;

		template<auto f = _one, auto n0 = _one, auto i = _two, auto n1 = _one>
		nik_ces auto contr = controller
		<
			instruction < IN::call , IT::propel , f  >,
			instruction < IN::call , IT::eval   , n0 >,
			instruction < IN::call , IT::propel , i  >,
			instruction < IN::call , IT::eval   , n1 >,
			instruction < IN::halt , IT::eval        >
		>;

		template<auto d, auto V, template<auto...> typename B, auto... Vs>
		nik_ces auto _result(nik_avp(B<Vs...>*))
			{ return T_interpreter_start::template result<ID::next_depth(d), contr<>, V, Vs...>(H0); }

		template<auto d, auto List, auto V>
		nik_ces auto result = _result<ID::next_depth(d), V>(List);
	};

	template<auto Op> nik_ce auto _dpar_insert_sort_ = U_custom_T<T_interpreter_insert_sort<Op>>;
	template<auto Op> nik_ce auto  _par_insert_sort_ = ID::template with_initial_depth<_dpar_insert_sort_<Op>>;

/***********************************************************************************************************************/

// sort:

	template<auto Op>
	struct T_interpreter_sort
	{
		nik_ces auto H0 = U_pack_Vs<_car_, _dpar_insert_sort_<Op>>;

		template<auto n = _one, auto Loop = _zero, auto Done = _three>
		nik_ces auto contr = controller
		<
			instruction < IN::jump , IT::cascade , Done >,
			instruction < IN::call , IT::cascade , n    >,
			instruction < IN::jump , IT::go_to   , Loop >,
			instruction < IN::halt , IT::eval           >
		>;

		template<auto d, auto... Vs>
		nik_ces auto result = T_interpreter_start::template result<d, contr<>, U_null_Vs, Vs...>(H0);
	};

	template<auto Op> nik_ce auto _dpar_sort_ = U_custom_T<T_interpreter_sort<Op>>;
	template<auto Op> nik_ce auto  _par_sort_ = ID::template with_initial_depth<_dpar_sort_<Op>>;

/***********************************************************************************************************************/

// trampoline:

	template<auto Op>
	struct T_interpreter_trampoline
	{
		nik_ces auto H0 = U_pack_Vs<_car_>;

		template<auto n = _one>
		nik_ces auto contr = controller
		<
			instruction < IN::call , IT::eval , n >,
			instruction < IN::halt , IT::eval     >
		>;

		template<auto d, auto... Vs>
		nik_ces auto result = T_interpreter_start::template result<ID::next_depth(d), contr<>, Op, Vs...>(H0);
	};

	template<auto Op> nik_ce auto _dpar_trampoline_ = U_custom_T<T_interpreter_trampoline<Op>>;
	template<auto Op> nik_ce auto  _par_trampoline_ = ID::template with_initial_depth<_dpar_trampoline_<Op>>;

	// syntactic sugar:

		template<auto Op> nik_ces auto _dpart_sort_ = _dpar_trampoline_<_dpar_sort_<Op>>;
		template<auto Op> nik_ces auto _part_sort_ = _par_trampoline_<_dpar_sort_<Op>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// memoize:

/***********************************************************************************************************************/

// lookup:

	template<gindex_type _2_N>
	struct T_interpreter<IN::memoize, IT::lookup, _2_N>
	{
		struct T_same_car
		{
			template<auto W, auto Z>
			nik_ces auto result = eval<_same_, W, unpack_<Z, _car_>>;

		}; nik_ces auto _same_car_ = U_custom_T<T_same_car>;

		template
		<
			NIK_INTERPRETER_PARAMS(d, m, c, i, Vs),
			template<auto...> typename B0, auto W0,
			template<auto...> typename B1, auto... Xs, typename Heap2,
			template<auto...> typename B3, auto... Zs, typename... Args
		>
		nik_ces auto result(nik_vp(H0)(B0<W0>*), nik_vp(H1)(B1<Xs...>*), Heap2 H2, nik_vp(A0)(B3<Zs...>*), Args... As)
		{
			nik_ce auto size = sizeof...(Zs);
			nik_ce auto pos	 = find_<_alias_<_same_car_, W0>, Zs...>;

			if nik_ce (pos == size)

				return NIK_INTERPRETER(_2_N, d, IT::id, c, i, Vs)(U_null_Vs, H1, H2, A0, As...);
			else
			{
				nik_ce auto ins = ID::instr(c, i);
				nik_ce auto ni  = ins[II::pos];

				return NIK_INTERPRETER(_2_N, d, IT::id, c, ni, Vs)(A0, U_pack_Vs<pos, Xs...>, H2, A0, As...);
			}
		}
	};

/***********************************************************************************************************************/

// insert:

	template<gindex_type _2_N>
	struct T_interpreter<IN::memoize, IT::insert, _2_N>
	{
		template
		<
			NIK_INTERPRETER_PARAMS(d, m, c, i, Vs), template<auto...> typename B0, auto W0,
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

// interpreter:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// default:

	nik_ce auto default_interpreter_frame()
	{
		return table
		(
		 	U_char,

			binding( "same"              , _praxis_< _same_              >),
			binding( "is_null"           , _praxis_< _is_null_           >),
			binding( "length"            , _praxis_< _length_            >),
			binding( "car"               , _praxis_< _car_               >),
			binding( "nop"               , _praxis_< _nop_               >),
			binding( "cadr"              , _praxis_< _cadr_              >),

			binding( "is_const"          , _praxis_< _is_const_          >),
			binding( "add_const"         , _praxis_< _add_const_         >),
			binding( "remove_const"      , _praxis_< _remove_const_      >),
			binding( "to_const"          , _praxis_< _to_const_          >),
			binding( "from_const"        , _praxis_< _from_const_        >),

			binding( "csame"             , _praxis_< _csame_             >),
			binding( "name"              , _praxis_< _name_              >),
			binding( "similar"           , _praxis_< _similar_           >),
			binding( "to_list"           , _praxis_< _to_list_           >),
			binding( "b0_unpack"         , _praxis_< _b0_unpack_         >),
			binding( "rename"            , _praxis_< _rename_            >),
			binding( "pad"               , _praxis_< _pad_               >),
			binding( "cdr"               , _praxis_< _cdr_               >),
			binding( "map"               , _praxis_< _map_               >),
			binding( "zip"               , _praxis_< _zip_               >),
			binding( "unite"             , _praxis_< _unite_             >),
			binding( "cons"              , _praxis_< _cons_              >),
			binding( "push"              , _praxis_< _push_              >),

			binding( "if_then_else"      , _praxis_< _if_then_else_      >),
			binding( "stem"              , _praxis_< _stem_              >),
			binding( "costem"            , _praxis_< _costem_            >),
			binding( "distem"            , _praxis_< _distem_            >),

			binding( "is_unsigned"       , _praxis_< _is_unsigned_       >),
			binding( "not_unsigned"      , _praxis_< _not_unsigned_      >),
			binding( "is_signed"         , _praxis_< _is_signed_         >),
			binding( "not_signed"        , _praxis_< _not_signed_        >),
			binding( "is_integer"        , _praxis_< _is_integer_        >),
			binding( "not_integer"       , _praxis_< _not_integer_       >),

			binding( "is_pointer"        , _praxis_< _is_pointer_        >),
			binding( "add_pointer"       , _praxis_< _add_pointer_       >),
			binding( "remove_pointer"    , _praxis_< _remove_pointer_    >),
			binding( "to_pointer"        , _praxis_< _to_pointer_        >),
			binding( "from_pointer"      , _praxis_< _from_pointer_      >),

			binding( "is_reference"      , _praxis_< _is_reference_      >),
			binding( "add_reference"     , _praxis_< _add_reference_     >),
			binding( "remove_reference"  , _praxis_< _remove_reference_  >),
			binding( "to_reference"      , _praxis_< _to_reference_      >),
			binding( "from_reference"    , _praxis_< _from_reference_    >),

			binding( "to_array"          , _praxis_< _to_array_          >),
			binding( "array_apply"       , _praxis_< _array_apply_       >),

			binding( "function_type"     , _praxis_< _function_type_     >),
			binding( "function_arity"    , _praxis_< _function_arity_    >),
			binding( "function_out_type" , _praxis_< _function_out_type_ >),
			binding( "function_in_types" , _praxis_< _function_in_types_ >),

			binding( "eval"              , _praxis_< _eval_              >),
			binding( "procedure"         , _praxis_< _procedure_         >),
			binding( "method"            , _praxis_< _method_            >),
			binding( "tailor"            , _praxis_< _tailor_            >),

			binding( "list_to_array"     , _praxis_< _list_to_array_     >),
			binding( "array_to_list"     , _praxis_< _array_to_list_     >)
		);
	};

//	nik_ce auto default_interpreter_lookup = make_frame<default_interpreter_frame>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

