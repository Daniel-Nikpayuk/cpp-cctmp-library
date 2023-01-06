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
/***********************************************************************************************************************/

// binding:

/***********************************************************************************************************************/

	template<typename CharType, auto Size, typename ValueType>
	struct binding
	{
		using char_type			= CharType;
		using string_type		= char_type const *;
		using size_type			= decltype(Size);

		nik_ces size_type size		= Size;
		nik_ces auto value		= U_restore_T<ValueType>;
		using value_type		= decltype(value);

		string_type string;

		nik_ce binding(const CharType (&s)[Size], ValueType) : string{s} { }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// table:

/***********************************************************************************************************************/

	template<typename CharType, typename... Bindings>
	struct table
	{
		using char_type			= T_restore_T<CharType>;
		using cchar_type		= char_type const;
		using string_type		= char_type const*;
		using cstring_type		= string_type const;

		nik_ces auto size		= sizeof...(Bindings);
		using size_type			= decltype(size);

		nik_ces auto sizes		= array<size_type, Bindings::size...>;
		nik_ces auto values		= U_pack_Vs<Bindings::value...>;

		cstring_type string[size];

		nik_ce table(CharType, Bindings... bs) : string{bs.string...} { }
	};

/***********************************************************************************************************************/

// function:

//	template<auto Size>
//	nik_ce bool equals_charset(gstring_type b, gstring_type e, gcchar_type (&charset)[Size])
//	{
//		bool match = ((e-b) == Size);

//		for (gstring_type i = charset; match && i != charset + Size; ++b, ++i)
//			match = (*b == *i);

//		return match;
//	}

	template<typename SizeType, typename Type1, typename Type2>
	nik_ce auto ptr_diff_equal(const Type1 *b1, const Type1 *e1, const Type2 *b2, const Type2 *e2)
	{
		using size_type = SizeType;

		const size_type size1 = e1 - b1;
		const size_type size2 = e2 - b2;

		bool equal = (size1 == size2);

		while (equal && b1 != e1) equal = (*(b1++) == *(b2++));

		return equal;
	}

	template<auto f, typename StringType>
	nik_ce auto lookup_function(StringType str_begin, StringType str_end)
	{
		nik_ce auto table		= f();

		using table_type		= decltype(table);
		using size_type			= typename table_type::size_type;
		using string_type		= typename table_type::string_type;
		using cstring_type		= typename table_type::cstring_type;

		cstring_type *key		= table.string;
		cstring_type *key_end		= key + table.size;

		size_type *size			= table.sizes;

		while (key != key_end)
		{
			string_type b		= *key;
			string_type e		= b + *(size++);

			if (ptr_diff_equal<size_type>(b, e, str_begin, str_end)) break;

			++key;
		}

		return key - table.string;
	}

	template<auto f>
	nik_ce auto make_lookup_function()
	{
		using table_type	= T_out_type<f>;
		using string_type	= typename table_type::string_type;

		nik_ce auto values	= table_type::values;
		nik_ce auto lookup_f	= lookup_function<f, string_type>;

		return eval<_cons_, H_id, values, lookup_f>;
	}

	template<auto f>
	nik_ce auto make_environment = make_lookup_function<f>();

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

// machine:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// default:

	nik_ce auto default_machine_lookup()
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
			binding( "find"              , _praxis_< _find_              >),

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

	nik_ce auto default_machine_environment = make_environment<default_machine_lookup>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// assembly:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// default:

	nik_ce auto default_assembly_lookup()
	{
		return table
		(
		 	U_char,

			binding( "id"                    , _id_                       ),
			binding( "upshift"               , _upshift_                  ),
			binding( "downshift"             , _downshift_                ),

			binding( "assign"                , _assign_                   ),
			binding( "dereference"           , _dereference_              ),
			binding( "to_bool"               , _to_bool_                  ),

			binding( "not"                   , _not_                      ),
			binding( "and"                   , _and_                      ),
			binding( "or"                    , _or_                       ),
			binding( "implies"               , _implies_                  ),
			binding( "equivalent"            , _equivalent_               ),

			binding( "equal"                 , _equal_                    ),
			binding( "is_zero"               , _is_zero_                  ),
			binding( "not_equal"             , _not_equal_                ),
			binding( "less_than"             , _less_than_                ),
			binding( "less_than_or_equal"    , _less_than_or_equal_       ),
			binding( "greater_than"          , _greater_than_             ),
			binding( "greater_than_or_equal" , _greater_than_or_equal_    ),

			binding( "add"                   , _add_                      ),
			binding( "subtract"              , _subtract_                 ),
			binding( "multiply"              , _multiply_                 ),
			binding( "divide"                , _divide_                   ),
			binding( "modulo"                , _modulo_                   ),

			binding( "increment"             , _increment_<1>             ),
			binding( "decrement"             , _increment_<-1>            ),

			binding( "is_array"              , _is_array_                 ),
			binding( "array_type"            , _array_type_               ),
			binding( "array_size"            , _array_size_               ),
			binding( "array_begin"           , _array_begin_              ),
			binding( "array_last"            , _array_last_               ),
			binding( "array_end"             , _array_end_                ),
			binding( "log_floor"             , _log_floor_                ),

			binding( "is_sequence"           , _is_sequence_              ),
			binding( "sequence_type"         , _sequence_type_            ),
			binding( "sequence_size"         , _sequence_size_            ),
			binding( "to_sequence"           , _to_sequence_              ),
			binding( "sequence_begin"        , _sequence_begin_           ),
			binding( "sequence_last"         , _sequence_last_            ),
			binding( "sequence_end"          , _sequence_end_             ),

			binding( "is_tuple"              , _is_tuple_                 ),
			binding( "tuple_type"            , _tuple_type_               ),
			binding( "tuple_size"            , _tuple_size_               ),
			binding( "to_tuple"              , _to_tuple_                 )
		);
	};

	nik_ce auto default_assembly_environment = make_environment<default_assembly_lookup>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

