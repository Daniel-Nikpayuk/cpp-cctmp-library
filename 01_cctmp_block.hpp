/************************************************************************************************************************
**
** Copyright 2022 Daniel Nikpayuk, Inuit Nunangat, The Inuit Nation
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

// block:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// machination:

	// Definition: A liner (trampoliner) is a nest-resulted struct that either returns
	// its value of interest, or a machination with the same structure as its input.
	// It is expected that all other nest-resulted structs are defined from such liners.

	// Both T_block and T_machine are implementations of such liners.

/***********************************************************************************************************************/

// struct:

	template<typename U, typename P>
	struct machination
	{
		U u;
		P p;

		nik_ce machination(const U & _u, const P & _p) : u{_u}, p{_p} { }
	};

/***********************************************************************************************************************/

// is machination:

	template<typename T>
	nik_ce bool is_machination = false;

	template<typename U, typename P> nik_ce bool is_machination <       machination<U, P>   > = true;
	template<typename U, typename P> nik_ce bool is_machination < const machination<U, P>   > = true;
	template<typename U, typename P> nik_ce bool is_machination < const machination<U, P> & > = true;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// block overload:

	template<key_type, auto...> struct T_block_overload;

	struct BlockOverload
	{
		nik_ces key_type id		=  0;

		nik_ces key_type part		=  1;
		nik_ces key_type left		=  2;
		nik_ces key_type alter		=  3;
		nik_ces key_type lookup		=  4;
	};

	using BL = BlockOverload;

	// syntactic sugar:

		// car:

			using T_block_car					= T_alias<Alias::car>;
			nik_ce auto U_block_car					= U_store_T<T_block_car>;

		// right:

			template<auto b = H_id> using T_block_right		= T_alias<Alias::to_list, b>;
			template<auto b = H_id> nik_ce auto U_block_right	= U_store_T<T_block_right<b>>;

/***********************************************************************************************************************/

// part:

	template<auto Op, auto bl, auto br>
	struct T_block_overload<BL::part, Op, bl, br>
	{
		template<auto... Vs, template<auto...> typename B, auto... Ws>
		nik_ces auto result(nik_avp(B<Ws...>*))
		{
			nik_ce auto l = to_list_<bl, Ws...>;
			nik_ce auto r = overload<Op, br, Vs...>;

			return tuple<decltype(l), decltype(r)>(l, r);
		}
	};

	template<auto bl = H_id, auto br = H_id>
		nik_ce auto U_block_split = U_store_T<T_block_overload<BL::part, Alias::to_list, bl, br>>;

	template<auto bl = H_id, auto br = H_id>
		nik_ce auto U_block_cut = U_store_T<T_block_overload<BL::part, Alias::cdr, bl, br>>;

/***********************************************************************************************************************/

// left:

	template<auto b>
	struct T_block_overload<BL::left, b>
	{
		template<auto... Vs, template<auto...> typename B, auto... Ws>
		nik_ces auto result(nik_avp(B<Ws...>*)) { return to_list_<b, Ws...>; }

	}; template<auto b = H_id>
		nik_ce auto U_block_left = U_store_T<T_block_overload<BL::left, b>>;

/***********************************************************************************************************************/

// alter:

	template<auto bl, auto br, auto bp>
	struct T_block_overload<BL::alter, bl, br, bp>
	{
		template<auto V0, auto... Vs, template<auto...> typename B, auto... Ws>
		nik_ces auto result(nik_avp(B<Ws...>*))
		{
			nik_ce auto l = to_list_<bl, Ws...>;
			nik_ce auto r = to_list_<br, Vs...>;
			nik_ce auto p = to_list_<bp, l, r>;

			return tuple<decltype(p), decltype(V0)>(p, V0);
		}

	}; template<auto bl = H_id, auto br = H_id, auto bp = H_id>
		nik_ce auto U_block_alter = U_store_T<T_block_overload<BL::alter, bl, br, bp>>;

/***********************************************************************************************************************/

/*
// lookup:

	template<auto... filler>
	struct T_block_overload<BL::lookup, filler...>
	{
		template<auto V0, auto... Vs>
		nik_ces auto result = unpack_<V0, U_cadr>;

	}; nik_ce auto U_block_lookup = U_store_T<T_block_overload<BL::lookup>>;
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// block:

	// Arbitrary list_id for user output for greater utility,
	// U_pack_Vs for internal output for greater generality.

	template<key_type, key_type, key_type, auto...> struct T_block;

/***********************************************************************************************************************/

// names:

	struct BlockName
	{
		nik_ces key_type id		=  0;

		nik_ces key_type variable	=  1;
		nik_ces key_type function	=  2;

		nik_ces key_type segment	=  3;

		nik_ces key_type fold		=  4;
		nik_ces key_type parse		=  5;
		nik_ces key_type cascade	=  6;

		nik_ces key_type argument	=  7;
		nik_ces key_type tuple		=  8;
	};

	using BN = BlockName;

/***********************************************************************************************************************/

// notes:

	struct BlockNote
	{
		nik_ces key_type id		= 0;

		nik_ces key_type start		= 1;
		nik_ces key_type pass		= 2;
		nik_ces key_type pause		= 3;
		nik_ces key_type halt		= 4;
	};

	using BT = BlockNote;

/***********************************************************************************************************************/

// dispatch:

	struct BlockDisp
	{
		// length:

		nik_ces key_type max_length_0(cindex_type n) { if (n >= _2_0) return 0; else return _zero; }
		nik_ces key_type max_length_1(cindex_type n) { if (n >= _2_1) return 1; else return max_length_0(n); }
		nik_ces key_type max_length_2(cindex_type n) { if (n >= _2_2) return 2; else return max_length_1(n); }
		nik_ces key_type max_length_3(cindex_type n) { if (n >= _2_3) return 3; else return max_length_2(n); }
		nik_ces key_type max_length_4(cindex_type n) { if (n >= _2_4) return 4; else return max_length_3(n); }
		nik_ces key_type max_length_5(cindex_type n) { if (n >= _2_5) return 5; else return max_length_4(n); }
		nik_ces key_type max_length_6(cindex_type n) { if (n >= _2_6) return 6; else return max_length_5(n); }
		nik_ces key_type max_length_7(cindex_type n) { if (n >= _2_7) return 7; else return max_length_6(n); }
		nik_ces key_type max_length_8(cindex_type n) { if (n >= _2_8) return 8; else return max_length_7(n); }
		nik_ces key_type max_length_9(cindex_type n) { if (n >= _2_9) return 9; else return max_length_8(n); }

		// index:

		nik_ces index_type max_index_0(cindex_type n) { if (n >= _2_0) return _2_0; else return _zero; }
		nik_ces index_type max_index_1(cindex_type n) { if (n >= _2_1) return _2_1; else return max_index_0(n); }
		nik_ces index_type max_index_2(cindex_type n) { if (n >= _2_2) return _2_2; else return max_index_1(n); }
		nik_ces index_type max_index_3(cindex_type n) { if (n >= _2_3) return _2_3; else return max_index_2(n); }
		nik_ces index_type max_index_4(cindex_type n) { if (n >= _2_4) return _2_4; else return max_index_3(n); }
		nik_ces index_type max_index_5(cindex_type n) { if (n >= _2_5) return _2_5; else return max_index_4(n); }
		nik_ces index_type max_index_6(cindex_type n) { if (n >= _2_6) return _2_6; else return max_index_5(n); }
		nik_ces index_type max_index_7(cindex_type n) { if (n >= _2_7) return _2_7; else return max_index_6(n); }
		nik_ces index_type max_index_8(cindex_type n) { if (n >= _2_8) return _2_8; else return max_index_7(n); }
		nik_ces index_type max_index_9(cindex_type n) { if (n >= _2_9) return _2_9; else return max_index_8(n); }

		// note:

			nik_ces key_type next_note(cdepth_type d, cindex_type n)
			{
				if      (d == 0) return BT::pause;
				else if (n == 0) return BT::halt;
				else             return BT::pass;
			}

		// length:

			NIK_BLOCK_DISPATCH_NEXT_LENGTH(0)
			NIK_BLOCK_DISPATCH_NEXT_LENGTH(1)
			NIK_BLOCK_DISPATCH_NEXT_LENGTH(2)
			NIK_BLOCK_DISPATCH_NEXT_LENGTH(3)
			NIK_BLOCK_DISPATCH_NEXT_LENGTH(4)
			NIK_BLOCK_DISPATCH_NEXT_LENGTH(5)
			NIK_BLOCK_DISPATCH_NEXT_LENGTH(6)
			NIK_BLOCK_DISPATCH_NEXT_LENGTH(7)
			NIK_BLOCK_DISPATCH_NEXT_LENGTH(8)
			NIK_BLOCK_DISPATCH_NEXT_LENGTH(9)

		// depth:

			nik_ces depth_type next_depth(cdepth_type d)
				{ return d - bool{d != 0}; }

		// index:

			NIK_BLOCK_DISPATCH_NEXT_INDEX(0)
			NIK_BLOCK_DISPATCH_NEXT_INDEX(1)
			NIK_BLOCK_DISPATCH_NEXT_INDEX(2)
			NIK_BLOCK_DISPATCH_NEXT_INDEX(3)
			NIK_BLOCK_DISPATCH_NEXT_INDEX(4)
			NIK_BLOCK_DISPATCH_NEXT_INDEX(5)
			NIK_BLOCK_DISPATCH_NEXT_INDEX(6)
			NIK_BLOCK_DISPATCH_NEXT_INDEX(7)
			NIK_BLOCK_DISPATCH_NEXT_INDEX(8)
			NIK_BLOCK_DISPATCH_NEXT_INDEX(9)
	};

	using BD = BlockDisp;

/***********************************************************************************************************************/

// variable:

	template<auto... filler>
	struct T_block<BN::variable, BT::start, _zero, filler...>
	{
		template<auto d, auto n, auto rtn, auto... Vs>
		nik_ces auto result = NIK_VARIABLE_BLOCK(9, d, n, rtn, Vs);
	};

	using T_block_variable		= T_block<BN::variable, BT::start, _zero>;
	nik_ce auto U_block_variable	= U_store_T<T_block_variable>;

	NIK_DEFINE_BLOCK_VARIABLE_PASS(0)
	NIK_DEFINE_BLOCK_VARIABLE_PASS(1)
	NIK_DEFINE_BLOCK_VARIABLE_PASS(2)
	NIK_DEFINE_BLOCK_VARIABLE_PASS(3)
	NIK_DEFINE_BLOCK_VARIABLE_PASS(4)
	NIK_DEFINE_BLOCK_VARIABLE_PASS(5)
	NIK_DEFINE_BLOCK_VARIABLE_PASS(6)
	NIK_DEFINE_BLOCK_VARIABLE_PASS(7)
	NIK_DEFINE_BLOCK_VARIABLE_PASS(8)
	NIK_DEFINE_BLOCK_VARIABLE_PASS(9)

	template<auto... filler>
	struct T_block<BN::variable, BT::pause, _zero, filler...>
	{
		template<auto d, auto n, auto rtn, auto... Vs>
		nik_ces auto result = machination(U_block_variable, U_pack_Vs<n, rtn, Vs...>);
	};

	template<auto... filler>
	struct T_block<BN::variable, BT::halt, _zero, filler...>
	{
		template<auto d, auto n, auto rtn, auto... Vs>
		nik_ces auto result = T_store_U<rtn>::template result<Vs...>;
	};

/***********************************************************************************************************************/

// function:

	template<auto... filler>
	struct T_block<BN::function, BT::start, _zero, filler...>
	{
		template<auto d, auto p, auto n, auto rtn, auto... Vs>
		nik_ces auto result = NIK_FUNCTION_BLOCK(9, d, n, rtn, Vs)(p);
	};

	using T_block_function		= T_block<BN::function, BT::start, _zero>;
	nik_ce auto U_block_function	= U_store_T<T_block_function>;

	NIK_DEFINE_BLOCK_FUNCTION_PASS(0)
	NIK_DEFINE_BLOCK_FUNCTION_PASS(1)
	NIK_DEFINE_BLOCK_FUNCTION_PASS(2)
	NIK_DEFINE_BLOCK_FUNCTION_PASS(3)
	NIK_DEFINE_BLOCK_FUNCTION_PASS(4)
	NIK_DEFINE_BLOCK_FUNCTION_PASS(5)
	NIK_DEFINE_BLOCK_FUNCTION_PASS(6)
	NIK_DEFINE_BLOCK_FUNCTION_PASS(7)
	NIK_DEFINE_BLOCK_FUNCTION_PASS(8)
	NIK_DEFINE_BLOCK_FUNCTION_PASS(9)

	template<auto... filler>
	struct T_block<BN::function, BT::pause, _zero, filler...>
	{
		template<auto d, auto n, auto rtn, auto... Vs, typename Pack>
		nik_ces auto result(Pack)
		{
			nik_ce auto p = U_pack_Vs<U_restore_T<Pack>>;

			return machination(U_block_function, U_pack_Vs<p, n, rtn, Vs...>);
		}
	};

	template<auto... filler>
	struct T_block<BN::function, BT::halt, _zero, filler...>
	{
		template<auto d, auto n, auto rtn, auto... Vs, typename Pack>
		nik_ces auto result(Pack p) { return T_store_U<rtn>::template result<Vs...>(p); }
	};

/***********************************************************************************************************************/

// segment:

	template<auto... filler>
	struct T_block<BN::segment, BT::start, _zero, filler...>
	{
		template<auto d, auto n, auto b, auto s, auto... Vs>
		nik_ces auto result = NIK_SEGMENT_BLOCK(9, d, n, b, s, Vs);
	};

	using T_block_segment		= T_block<BN::segment, BT::start, _zero>;
	nik_ce auto U_block_segment	= U_store_T<T_block_segment>;

	NIK_DEFINE_BLOCK_SEGMENT_PASS(0)
	NIK_DEFINE_BLOCK_SEGMENT_PASS(1)
	NIK_DEFINE_BLOCK_SEGMENT_PASS(2)
	NIK_DEFINE_BLOCK_SEGMENT_PASS(3)
	NIK_DEFINE_BLOCK_SEGMENT_PASS(4)
	NIK_DEFINE_BLOCK_SEGMENT_PASS(5)
	NIK_DEFINE_BLOCK_SEGMENT_PASS(6)
	NIK_DEFINE_BLOCK_SEGMENT_PASS(7)
	NIK_DEFINE_BLOCK_SEGMENT_PASS(8)
	NIK_DEFINE_BLOCK_SEGMENT_PASS(9)

	template<auto... filler>
	struct T_block<BN::segment, BT::pause, _zero, filler...>
	{
		template<auto d, auto n, auto b, auto s, auto... Vs>
		nik_ces auto result = machination(U_block_segment, U_pack_Vs<n, b, s, Vs...>);
	};

	template<auto... filler>
	struct T_block<BN::segment, BT::halt, _zero, filler...>
	{
		template<auto d, auto n, auto b, auto s, auto... Vs>
		nik_ces auto result = to_list_<b, decltype(s){s+Vs}...>;
	};

/***********************************************************************************************************************/

// (action) fold:

	template<auto... filler>
	struct T_block<BN::fold, BT::start, _zero, filler...>
	{
		template<auto d, auto n, auto op, auto V, auto... Vs>
		nik_ces auto result = NIK_FOLD_BLOCK(9, d, n, op, V, Vs);
	};

	using T_block_fold		= T_block<BN::fold, BT::start, _zero>;
	nik_ce auto U_block_fold	= U_store_T<T_block_fold>;

	NIK_DEFINE_BLOCK_FOLD_PASS(0)
	NIK_DEFINE_BLOCK_FOLD_PASS(1)
	NIK_DEFINE_BLOCK_FOLD_PASS(2)
	NIK_DEFINE_BLOCK_FOLD_PASS(3)
	NIK_DEFINE_BLOCK_FOLD_PASS(4)
	NIK_DEFINE_BLOCK_FOLD_PASS(5)
	NIK_DEFINE_BLOCK_FOLD_PASS(6)
	NIK_DEFINE_BLOCK_FOLD_PASS(7)
	NIK_DEFINE_BLOCK_FOLD_PASS(8)
	NIK_DEFINE_BLOCK_FOLD_PASS(9)

	template<auto... filler>
	struct T_block<BN::fold, BT::pause, _zero, filler...>
	{
		template<auto d, auto n, auto op, auto V, auto... Vs>
		nik_ces auto result = machination(U_block_fold, U_pack_Vs<n, op, V, Vs...>);
	};

	template<auto... filler>
	struct T_block<BN::fold, BT::halt, _zero, filler...>
	{
		template<auto d, auto n, auto op, auto V, auto... Vs>
		nik_ces auto result = V;
	};

/***********************************************************************************************************************/

// parse (fold with one lookahead):

	template<auto... filler>
	struct T_block<BN::parse, BT::start, _zero, filler...>
	{
		template<auto d, auto n, auto op, auto V, auto... Vs>
		nik_ces auto result = NIK_PARSE_BLOCK(0, d, n, op, V, Vs);
	};

	using T_block_parse		= T_block<BN::parse, BT::start, _zero>;
	nik_ce auto U_block_parse	= U_store_T<T_block_parse>;

	template<auto... filler>
	struct T_block<BN::parse, BT::pass, _zero, filler...>
	{
		template<auto d, auto n, auto op, auto V, auto V0, auto V1, auto... Vs>
		nik_ces auto result = NIK_BEGIN_BLOCK(0, parse, d, n), op,

			overload<op, V, V0, V1>, V1, Vs...

		NIK_END_BLOCK;
	};

	template<auto... filler>
	struct T_block<BN::parse, BT::pause, _zero, filler...>
	{
		template<auto d, auto n, auto op, auto V, auto... Vs>
		nik_ces auto result = machination(U_block_parse, U_pack_Vs<n, op, V, Vs...>);
	};

	template<auto... filler>
	struct T_block<BN::parse, BT::halt, _zero, filler...>
	{
		template<auto d, auto n, auto op, auto V, auto... Vs>
		nik_ces auto result = V;
	};

/***********************************************************************************************************************/

// cascade (compel fold):

	template<auto... filler>
	struct T_block<BN::cascade, BT::start, _zero, filler...>
	{
		template<auto d, auto n, auto op, auto V, auto... Vs>
		nik_ces auto result = NIK_CASCADE_BLOCK(0, d, n, op, V, Vs)();
	};

	using T_block_cascade			= T_block<BN::cascade, BT::start, _zero>;
	nik_ce auto U_block_cascade		= U_store_T<T_block_cascade>;

	using T_block_cascade_internal		= T_block<BN::cascade, BT::start, _one>;
	nik_ce auto U_block_cascade_internal	= U_store_T<T_block_cascade_internal>;

	template<auto... filler> // recall
	struct T_block<BN::cascade, BT::start, _one, filler...>
	{
		template<auto d, auto u, auto n, auto op, auto... Vs, auto... _Vs>
		nik_ces auto _result(nik_avp(T_pack_Vs<_Vs...>*))
		{
			nik_ce auto val = T_store_U<u>::template result<d, _Vs...>;

			if nik_ce (is_machination<decltype(val)>)

				return machination(U_block_cascade_internal, U_pack_Vs<val.u, val.p, n, op, Vs...>);
			else
				return NIK_CASCADE_BLOCK(0, d, n, op, val, Vs)();
		}

		template<auto d, auto u, auto p, auto n, auto op, auto... Vs>
		nik_ces auto result = _result<d, u, n, op, Vs...>(p);
	};

	template<auto... filler>
	struct T_block<BN::cascade, BT::pass, _zero, filler...>
	{
		template<auto d, auto n, auto op, auto V, auto V0, auto... Vs>
		nik_ces auto result()
		{
			nik_ce auto val = T_store_U<op>::template result<d, V, V0>;

			if nik_ce (is_machination<decltype(val)>)

				return machination(U_block_cascade_internal, U_pack_Vs<val.u, val.p, n, op, Vs...>);
			else
				return NIK_CASCADE_BLOCK(0, d, n, op, val, Vs)();
		}
	};

	template<auto... filler>
	struct T_block<BN::cascade, BT::pause, _zero, filler...>
	{
		template<auto d, auto n, auto op, auto V, auto... Vs>
		nik_ces auto result() { return machination(U_block_cascade, U_pack_Vs<n, op, V, Vs...>); }
	};

	template<auto... filler>
	struct T_block<BN::cascade, BT::halt, _zero, filler...>
	{
		template<auto d, auto n, auto op, auto V, auto... Vs>
		nik_ces auto result() { return V; }
	};

/***********************************************************************************************************************/

// argument:

	template<auto... filler>
	struct T_block<BN::argument, BT::start, _zero, filler...>
	{
		template<auto d, auto n, typename... Ts>
		nik_ces auto result(Ts... vs) { return NIK_ARGUMENT_BLOCK(9, d, n, Ts)(vs...); }
	};

	using T_block_argument		= T_block<BN::argument, BT::start, _zero>;
	nik_ce auto U_block_argument	= U_store_T<T_block_argument>;

	NIK_DEFINE_BLOCK_ARGUMENT_PASS(0)
	NIK_DEFINE_BLOCK_ARGUMENT_PASS(1)
	NIK_DEFINE_BLOCK_ARGUMENT_PASS(2)
	NIK_DEFINE_BLOCK_ARGUMENT_PASS(3)
	NIK_DEFINE_BLOCK_ARGUMENT_PASS(4)
	NIK_DEFINE_BLOCK_ARGUMENT_PASS(5)
	NIK_DEFINE_BLOCK_ARGUMENT_PASS(6)
	NIK_DEFINE_BLOCK_ARGUMENT_PASS(7)
	NIK_DEFINE_BLOCK_ARGUMENT_PASS(8)
	NIK_DEFINE_BLOCK_ARGUMENT_PASS(9)

	template<auto... filler>
	struct T_block<BN::argument, BT::pause, _zero, filler...>
	{
		template<bool V>
		nik_ces auto result_assert() { return V; }

		template<auto d, auto n, typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			static_assert(result_assert<bool{d != 0}>(), "argument nesting depth exceeded!");
		}
	};

	template<auto... filler>
	struct T_block<BN::argument, BT::halt, _zero, filler...>
	{
		template<auto d, auto n, typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) { return v; }
	};

/***********************************************************************************************************************/

// tuple:

	template<auto... filler>
	struct T_block<BN::tuple, BT::start, _zero, filler...>
	{
		template<auto d, auto n, typename... Ts>
		nik_ces auto & result(tuple<Ts...> & t) { return NIK_TUPLE_BLOCK(9, d, n, Ts)(t); }

		template<auto d, auto n, typename... Ts>
		nik_ces const auto & result(const tuple<Ts...> & t) { return NIK_TUPLE_BLOCK(9, d, n, Ts)(t); }
	};

	using T_block_tuple		= T_block<BN::tuple, BT::start, _zero>;
	nik_ce auto U_block_tuple	= U_store_T<T_block_tuple>;

	// value:

		template<index_type n, typename... Ts>
		constexpr auto & tuple_value(tuple<Ts...> & t) { return NIK_TUPLE_BLOCK(3, 500, n, Ts)(t); }

		template<index_type n, typename... Ts>
		constexpr const auto & tuple_value(const tuple<Ts...> & t) { return NIK_TUPLE_BLOCK(3, 500, n, Ts)(t); }

	NIK_DEFINE_BLOCK_TUPLE_PASS(0)
	NIK_DEFINE_BLOCK_TUPLE_PASS(1)
	NIK_DEFINE_BLOCK_TUPLE_PASS(2)
	NIK_DEFINE_BLOCK_TUPLE_PASS(3)
	NIK_DEFINE_BLOCK_TUPLE_PASS(4)
	NIK_DEFINE_BLOCK_TUPLE_PASS(5)
	NIK_DEFINE_BLOCK_TUPLE_PASS(6)
	NIK_DEFINE_BLOCK_TUPLE_PASS(7)
	NIK_DEFINE_BLOCK_TUPLE_PASS(8)
	NIK_DEFINE_BLOCK_TUPLE_PASS(9)

	template<auto... filler>
	struct T_block<BN::tuple, BT::pause, _zero, filler...>
	{
		template<bool V>
		nik_ces auto result_assert() { return V; }

		template<auto d, auto n, typename... Ts>
		nik_ces auto & result(tuple<Ts...> & t)
			{ static_assert(result_assert<bool{d != 0}>(), "tuple nesting depth exceeded!"); }

		template<auto d, auto n, typename... Ts>
		nik_ces const auto & result(const tuple<Ts...> & t)
			{ static_assert(result_assert<bool{d != 0}>(), "tuple nesting depth exceeded!"); }
	};

	template<auto... filler>
	struct T_block<BN::tuple, BT::halt, _zero, filler...>
	{
		template<auto d, auto n, typename... Ts>
		nik_ces auto & result(tuple<Ts...> & t) { return t.value; }

		template<auto d, auto n, typename... Ts>
		nik_ces const auto & result(const tuple<Ts...> & t) { return t.value; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

