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

// backend 1:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// machination:

/***********************************************************************************************************************/

// struct:

	template<typename T1, typename T2>
	struct machination
	{
		T1 s1;
		T2 s2;

		nik_ce machination(const T1 & _s1, const T2 & _s2) : s1{_s1}, s2{_s2} { }
	};

/***********************************************************************************************************************/

// is machination:

	template<typename T>
	nik_ce bool is_machination = false;

	template<typename T1, typename T2> nik_ce bool is_machination <       machination<T1, T2>   > = true;
	template<typename T1, typename T2> nik_ce bool is_machination < const machination<T1, T2>   > = true;
	template<typename T1, typename T2> nik_ce bool is_machination < const machination<T1, T2> & > = true;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// machine:

	template<key_type, key_type, key_type...> struct machine;

/***********************************************************************************************************************/

// controllers:

	struct MachineContr
	{
		using type					= instr_type const * const;

		nik_ces key_type size				= 0;

		nik_ces index_type length (type l)		{ return l[size][MI::size]; }
	};

	using MC		= MachineContr;
	using contr_type	= typename MC::type;

	template<instr_type... Vs>
	nik_ce contr_type controller = array<instr_type, array<index_type, sizeof...(Vs)>, Vs...>;

/***********************************************************************************************************************/

// dispatch:

	struct MachineDisp
	{
		// defaults:

			nik_ces depth_type initial_depth = 500;
			nik_ces index_type initial_index = _zero;

		// accessors:

			nik_ces auto instr(contr_type c, cindex_type i)
				{ return c[i]; }

		// navigators:

			nik_ces key_type next_name(cdepth_type d, ckey_type m, contr_type c, cindex_type i)
			{
				if (d == 0)		return MN::halt;
				else if (m != MT::id)	return MN::recall;
				else			return c[i+1][MI::name];
			}

			nik_ces key_type next_note(cdepth_type d, ckey_type m, contr_type c, cindex_type i)
			{
				if (d == 0)		return MT::pause;
				else if (m != MT::id)	return m;
				else			return c[i+1][MI::note];
			}

			nik_ces depth_type next_depth(cdepth_type d)
				{ return d - bool{d != 0}; }

			nik_ces index_type next_index(cdepth_type d, ckey_type m, contr_type, cindex_type i)
				{ return i + bool{d != 0 && m == MT::id}; }
	};

	using MD = MachineDisp;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// block:

	template<key_type...> struct block;

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

		nik_ces key_type sifter		=  9;
		nik_ces key_type right		= 10;
		nik_ces key_type lookup		= 11;

		nik_ces key_type filter		= 12;
		nik_ces key_type left		= 13;
		nik_ces key_type split		= 14;
	};

	using BN = BlockName;

/***********************************************************************************************************************/

// notes:

	struct BlockNote
	{
		nik_ces key_type id		= 0;

		nik_ces key_type pause		= 1;
		nik_ces key_type halt		= 2;
		nik_ces key_type pass		= 3;
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

// halters:

	// sifter:

		template<key_type... filler>
		struct block<BN::sifter, filler...>
		{
			template<auto V0, auto... Vs>
			nik_ces auto result = V0;
		};

	// right:

		template<key_type... filler>
		struct block<BN::right, filler...>
		{
			template<auto... Vs>
			nik_ces auto result = U_pack_Vs<Vs...>;
		};

	// lookup:

		template<key_type... filler>
		struct block<BN::lookup, filler...>
		{
			template<auto V0, auto... Vs>
			nik_ces auto result = unpack_alias<V0, Operator::cadr>;
		};

	// filter:

		template<key_type... filler>
		struct block<BN::filter, filler...>
		{
			template<auto V0, auto... Vs, typename Pack>
			nik_ces auto result(Pack p)
			{
				nik_ce auto r = U_pack_Vs<Vs...>;

				return tuple<Pack, decltype(r)>(p, r);
			}
		};

	// left:

		template<key_type... filler>
		struct block<BN::left, filler...>
		{
			template<auto... Vs, typename Pack>
			nik_ces auto result(Pack p) { return p; }
		};

	// split:

		template<key_type... filler>
		struct block<BN::split, filler...>
		{
			template<auto... Vs, typename Pack>
			nik_ces auto result(Pack p)
			{
				nik_ce auto r = U_pack_Vs<Vs...>;

				return tuple<Pack, decltype(r)>(p, r);
			}
		};

/***********************************************************************************************************************/

// variable:

	template<key_type... filler>
	struct block<BN::variable, BT::pause, _zero, filler...>
	{
		template<auto d, auto n, auto rtn, auto... Vs>
		nik_ces auto result = machination(U_pack_Vs<rtn>, U_pack_Vs<n, Vs...>);
	};

	template<key_type... filler>
	struct block<BN::variable, BT::halt, _zero, filler...>
	{
		template<auto d, auto n, auto rtn, auto... Vs>
		nik_ces auto result = block<rtn>::template result<Vs...>;
	};

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

/***********************************************************************************************************************/

// function:

	template<key_type... filler>
	struct block<BN::function, BT::pause, _zero, filler...>
	{
		template<auto d, auto n, auto rtn, auto... Vs, typename Pack>
		nik_ces auto result(Pack p)
		{
			return machination(U_pack_Vs<rtn>, U_pack_Vs<U_restore_T<Pack>, n, Vs...>);
		}
	};

	template<key_type... filler>
	struct block<BN::function, BT::halt, _zero, filler...>
	{
		template<auto d, auto n, auto rtn, auto... Vs, typename Pack>
		nik_ces auto result(Pack p) { return block<rtn>::template result<Vs...>(p); }
	};

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

/***********************************************************************************************************************/

// segment:

	template<key_type... filler>
	struct block<BN::segment, BT::pause, _zero, filler...>
	{
		nik_ces auto s1 = U_pack_Vs<BN::segment>;

		template<auto d, auto n, auto m, auto... Vs>
		nik_ces auto result = machination(s1, U_pack_Vs<n, m, Vs...>);
	};

	template<key_type... filler>
	struct block<BN::segment, BT::halt, _zero, filler...>
	{
		template<auto d, auto n, auto m, auto... Vs>
		nik_ces auto result = U_pack_Vs<decltype(m){m+Vs}...>;
	};

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

/***********************************************************************************************************************/

// (action) fold:

	template<key_type... filler>
	struct block<BN::fold, BT::pause, _zero, filler...>
	{
		template<auto d, auto n, auto op, auto V, auto... Vs>
		nik_ces auto result = machination(U_pack_Vs<op>, U_pack_Vs<n, V, Vs...>);
	};

	template<key_type... filler>
	struct block<BN::fold, BT::halt, _zero, filler...>
	{
		template<auto d, auto n, auto op, auto V, auto... Vs>
		nik_ces auto result = V;
	};

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

/***********************************************************************************************************************/

// parse (fold with one lookahead):

	template<key_type... filler>
	struct block<BN::parse, BT::pause, _zero, filler...>
	{
		template<auto d, auto n, auto op, auto V, auto... Vs>
		nik_ces auto result = machination(U_pack_Vs<op>, U_pack_Vs<n, V, Vs...>);
	};

	template<key_type... filler>
	struct block<BN::parse, BT::halt, _zero, filler...>
	{
		template<auto d, auto n, auto op, auto V, auto... Vs>
		nik_ces auto result = V;
	};

	template<key_type... filler>
	struct block<BN::parse, BT::pass, _zero, filler...>
	{
		template<auto d, auto n, auto op, auto V, auto V0, auto V1, auto... Vs>
		nik_ces auto result = NIK_BEGIN_BLOCK(0, parse, d, n),

			op, overload<op, V, V0, V1>, V1, Vs...

		NIK_END_BLOCK;
	};

/***********************************************************************************************************************/

// cascade (compel fold):

	template<key_type... filler>
	struct block<BN::cascade, BT::pause, _zero, filler...>
	{
		template<auto d, auto n, auto op, auto V, auto... Vs>
		nik_ces auto result()
		{
			return machination(U_pack_Vs<op>, U_pack_Vs<BT::pause, n, V, Vs...>);
		}
	};

	template<key_type... filler>
	struct block<BN::cascade, BT::halt, _zero, filler...>
	{
		template<auto d, auto n, auto op, auto V, auto... Vs>
		nik_ces auto result() { return V; }
	};

	template<key_type... filler> // function compel and alias compel, then only call compels?
	struct block<BN::cascade, BT::pass, _zero, filler...> // can dispatch the ::pause ::id here.
	{
		template<auto d, auto n, auto op, auto V, auto V0, auto... Vs>
		nik_ces auto result()
		{
			nik_ce auto val = T_store_U<op>::template result<d, V, V0>;

			if nik_ce (is_machination<decltype(val)>)

				return machination(U_pack_Vs<op>, U_pack_Vs<BT::id, n, val.s1, val.s2, Vs...>);
			else
				return NIK_CASCADE_BLOCK(d, n, op, val, Vs);
		}
	};

/***********************************************************************************************************************/

// argument:

	template<key_type... filler>
	struct block<BN::argument, BT::pause, _zero, filler...>
	{
		template<bool V>
		nik_ces auto result_assert() { return V; }

		template<auto d, auto n, typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			static_assert(result_assert<bool{d != 0}>(), "argument nesting depth exceeded!");
		}
	};

	template<key_type... filler>
	struct block<BN::argument, BT::halt, _zero, filler...>
	{
		template<auto d, auto n, typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) { return v; }
	};

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

/***********************************************************************************************************************/

// tuple:

	template<key_type... filler>
	struct block<BN::tuple, BT::pause, _zero, filler...>
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

	template<key_type... filler>
	struct block<BN::tuple, BT::halt, _zero, filler...>
	{
		template<auto d, auto n, typename... Ts>
		nik_ces auto & result(tuple<Ts...> & t) { return t.value; }

		template<auto d, auto n, typename... Ts>
		nik_ces const auto & result(const tuple<Ts...> & t) { return t.value; }
	};

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

	// value:

		template<index_type n, typename... Ts>
		constexpr auto & tuple_value(tuple<Ts...> & t) { return NIK_TUPLE_BLOCK(3, 500, n, Ts)(t); }

		template<index_type n, typename... Ts>
		constexpr const auto & tuple_value(const tuple<Ts...> & t) { return NIK_TUPLE_BLOCK(3, 500, n, Ts)(t); }

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// call/recall:

/***********************************************************************************************************************/

// action:

	// call:

		template<key_type... filler>
		struct machine<MN::call, MT::action, filler...>
		{
			template<NIK_CONTR_PARAMS, auto... Vs, auto... Ws, auto... Xs, typename... Heaps>
			nik_ces auto result(nik_vp(H0)(auto_pack<Ws...>*), nik_vp(H1)(auto_pack<Xs...>*), Heaps... Hs)
			{
				nik_ce auto ins	= MD::instr(c, i);
				nik_ce auto n	= ins[MI::dec];

				if nik_ce (n >= d) // analogous to returning a machination.

					return NIK_MACHINE(0, MT::action, c, i, Vs)(H0, H1, Hs...);
				else
				{
					nik_ce auto ctn = ins[MI::ctn];
					nik_ce auto key = ins[MI::key];
					nik_ce auto act = ins[MI::act];
					nik_ce auto val = overload<U_overload<key, act>, Ws...>;

					if nik_ce (ctn == MI::h1)

						return NIK_MACHINE(d, MT::id, c, i, Vs)
							(U_null_Vs, U_pack_Vs<val, Xs...>, Hs...);

					else if nik_ce (ctn == MI::h1_pair)

					//	return NIK_MACHINE(d, MT::id, c, i, Vs)
					//		(U_null_Vs, U_pack_Vs<val.v1, val.v2, Xs...>, Hs...);

						return NIK_MACHINE(d, MT::id, c, i, Vs)
						(
							U_null_Vs, U_pack_Vs
							<
								tuple_value<0>(val),
								tuple_value<1>(val), Xs...

							>, Hs...
						);
					else
						return val;
				}
			}
		};

	// recall:

		template<key_type... filler>
		struct machine<MN::recall, MT::action, filler...>
		{
			template<NIK_CONTR_PARAMS, auto... Vs, auto... Ws, auto... Xs, typename... Heaps>
			nik_ces auto result(nik_vp(H0)(auto_pack<Ws...>*), nik_vp(H1)(auto_pack<Xs...>*), Heaps... Hs)
			{
				nik_ce auto ins	= MD::instr(c, i);
				nik_ce auto n	= ins[MI::dec];

				if nik_ce (n >= d) // analogous to returning a machination.

					return NIK_MACHINE(0, MT::action, c, i, Vs)(H0, H1, Hs...);
				else
				{
					nik_ce auto ctn	= ins[MI::ctn];
					nik_ce auto key	= ins[MI::key];
					nik_ce auto act	= ins[MI::act];
					nik_ce auto val = overload<U_overload<key, act>, Ws...>;

					if nik_ce (ctn == MI::h1)

						return NIK_MACHINE(d, MT::id, c, i, Vs)
							(U_null_Vs, U_pack_Vs<val, Xs...>, Hs...);

					else if nik_ce (ctn == MI::h1_pair)

					//	return NIK_MACHINE(d, MT::id, c, i, Vs)
					//		(U_null_Vs, U_pack_Vs<val.v1, val.v2, Xs...>, Hs...);

						return NIK_MACHINE(d, MT::id, c, i, Vs)
						(
							U_null_Vs, U_pack_Vs
							<
								tuple_value<0>(val),
								tuple_value<1>(val), Xs...

							>, Hs...
						);
					else
						return val;
				}
			}
		};

/***********************************************************************************************************************/

// copy:

	// register:

		template<key_type... filler>
		struct machine<MN::call, MT::copy_r_pos, filler...>
		{
			template<NIK_CONTR_PARAMS, auto... Vs, auto... Ws, typename... Heaps>
			nik_ces auto result(nik_vp(H0)(auto_pack<Ws...>*), Heaps... Hs)
			{
				nik_ce auto ins	= MD::instr(c, i);
				nik_ce auto n	= ins[MI::pos];
				nik_ce auto ctn	= ins[MI::ctn];
				nik_ce auto val	= NIK_VARIABLE_BLOCK(3, d, n, BN::sifter, Vs);

				if nik_ce (is_machination<decltype(val)>)

					return NIK_MACHINE(d, MT::copy, c, i, Vs)(val.s1, val.s2, H0, Hs...);

				else if nik_ce (ctn == MI::h0)

					return NIK_MACHINE(d, MT::id, c, i, Vs)(U_pack_Vs<Ws..., val>, Hs...);

				else if nik_ce (ctn == MI::h0_write)

					return NIK_MACHINE(d, MT::id, c, i, Vs)(val, Hs...);
				else
					return val;
			}
		};

	// junction:

		template<key_type... filler>
		struct machine<MN::call, MT::copy_j_pos, filler...>
		{
			template<NIK_CONTR_PARAMS, auto... Vs, auto... Ws, auto... Xs, typename... Heaps>
			nik_ces auto result(nik_vp(H0)(auto_pack<Ws...>*), nik_vp(H1)(auto_pack<Xs...>*), Heaps... Hs)
			{
				nik_ce auto ins	= MD::instr(c, i);
				nik_ce auto n	= ins[MI::pos];
				nik_ce auto ctn	= ins[MI::ctn];
				nik_ce auto val	= NIK_VARIABLE_BLOCK(3, d, n, BN::sifter, Xs);

				if nik_ce (is_machination<decltype(val)>)

					return NIK_MACHINE(d, MT::copy, c, i, Vs)(val.s1, val.s2, H0, H1, Hs...);

				else if nik_ce (ctn == MI::h0)

					return NIK_MACHINE(d, MT::id, c, i, Vs)(U_pack_Vs<Ws..., val>, H1, Hs...);

				else if nik_ce (ctn == MI::h0_write)

					return NIK_MACHINE(d, MT::id, c, i, Vs)(val, H1, Hs...);
				else
					return val;
			}
		};

	// constant:

		template<key_type... filler>
		struct machine<MN::call, MT::copy_c_pos, filler...>
		{
			template
			<
				NIK_CONTR_PARAMS, auto... Vs,
				auto... Ws, typename Heap1, auto... Ys, typename... Args
			>
			nik_ces auto result
			(
				nik_vp(H0)(auto_pack<Ws...>*), Heap1 H1,
				nik_vp(H2)(auto_pack<Ys...>*), Args... As
			)
			{
				nik_ce auto ins	= MD::instr(c, i);
				nik_ce auto n	= ins[MI::pos];
				nik_ce auto ctn	= ins[MI::ctn];
				nik_ce auto val	= NIK_VARIABLE_BLOCK(3, d, n, BN::sifter, Ys);

				if nik_ce (is_machination<decltype(val)>)

					return NIK_MACHINE(d, MT::copy, c, i, Vs)(val.s1, val.s2, H0, H1, H2, As...);

				else if nik_ce (ctn == MI::h0)

					return NIK_MACHINE(d, MT::id, c, i, Vs)(U_pack_Vs<Ws..., val>, H1, H2, As...);

				else if nik_ce (ctn == MI::h0_write)

					return NIK_MACHINE(d, MT::id, c, i, Vs)(val, H1, H2, As...);
				else
					return val;
			}
		};

	// argument:

		template<key_type... filler>
		struct machine<MN::call, MT::copy_a_pos, filler...>
		{
			template
			<
				NIK_CONTR_PARAMS, auto... Vs,
				auto... Ws, typename Heap1, typename Heap2, typename... Args
			>
			nik_ces auto result(nik_vp(H0)(auto_pack<Ws...>*), Heap1 H1, Heap2 H2, Args... As)
			{
				nik_ce auto ins	= MD::instr(c, i);
				nik_ce auto n	= ins[MI::pos];
				nik_ce auto ctn	= ins[MI::ctn];
				nik_ce auto val	= NIK_VARIABLE_BLOCK(3, d, n, BN::sifter, U_restore_T<Args>);

				if nik_ce (is_machination<decltype(val)>)

					return NIK_MACHINE(d, MT::copy, c, i, Vs)(val.s1, val.s2, H0, H1, H2, As...);

				else if nik_ce (ctn == MI::h0)

					return NIK_MACHINE(d, MT::id, c, i, Vs)(U_pack_Vs<Ws..., val>, H1, H2, As...);

				else if nik_ce (ctn == MI::h0_write)

					return NIK_MACHINE(d, MT::id, c, i, Vs)(val, H1, H2, As...);
				else
					return val;
			}
		};

	// recall:

		template<key_type... filler>
		struct machine<MN::recall, MT::copy, filler...>
		{
			template
			<
				NIK_CONTR_PARAMS, auto... Vs,
				auto rtn, auto n, auto... _Vs,
				auto... Ws, typename... Heaps
			>
			nik_ces auto result
			(
				nik_avp(auto_pack<rtn>*), nik_avp(auto_pack<n, _Vs...>*),
				nik_vp(H0)(auto_pack<Ws...>*), Heaps... Hs
			)
			{
				nik_ce auto ins = MD::instr(c, i);
				nik_ce auto ctn = ins[MI::ctn];
				nik_ce auto val = NIK_VARIABLE_BLOCK(3, d, n, rtn, _Vs);

				if nik_ce (is_machination<decltype(val)>)

					return NIK_MACHINE(d, MT::copy, c, i, Vs)(val.s1, val.s2, H0, Hs...);

				else if nik_ce (ctn == MI::h0)

					return NIK_MACHINE(d, MT::id, c, i, Vs)(U_pack_Vs<Ws..., val>, Hs...);

				else if nik_ce (ctn == MI::h0_write)

					return NIK_MACHINE(d, MT::id, c, i, Vs)(val, Hs...);
				else
					return val;
			}
		};

/***********************************************************************************************************************/

// cut:

	// register:

		template<key_type... filler>
		struct machine<MN::call, MT::cut_r_pos, filler...>
		{
			template<NIK_CONTR_PARAMS, auto... Vs, typename Heap0, auto X0, auto... Xs, typename... Heaps>
			nik_ces auto result(Heap0 H0, nik_vp(H1)(auto_pack<X0, Xs...>*), Heaps... Hs)
			{
				nik_ce auto ins	= MD::instr(c, i);
				nik_ce auto n	= ins[MI::pos];
				nik_ce auto val	= NIK_FUNCTION_BLOCK(3, d, n, BN::filter, Vs)(U_null_Vs);

				if nik_ce (is_machination<decltype(val)>)

					return NIK_MACHINE(d, MT::cut, c, i, Vs)(val.s1, val.s2, H1, Hs...);
				else
				{
					nik_ce auto h0 = alias<Operator::unite, val.v1, val.v2, X0>;

					return NIK_MACHINE(d, MT::id, c, i, Vs)(h0, U_pack_Vs<Xs...>, Hs...);
				}
			}
		};

	// argument:

		template<key_type... filler>
		struct machine<MN::call, MT::cut_a_pos, filler...>
		{
			template
			<
				NIK_CONTR_PARAMS, auto... Vs,
				typename Heap0, auto X0, auto... Xs, typename Heap2, typename... Args
			>
			nik_ces auto result(Heap0 H0, nik_vp(H1)(auto_pack<X0, Xs...>*), Heap2 H2, Args... As)
			{
				nik_ce auto ins	= MD::instr(c, i);
				nik_ce auto n	= ins[MI::pos];
				nik_ce auto val	= NIK_FUNCTION_BLOCK(3, d, n, BN::filter, U_restore_T<Args>)(U_null_Vs);

				if nik_ce (is_machination<decltype(val)>)

					return NIK_MACHINE(d, MT::cut, c, i, Vs)(val.s1, val.s2, H1, H2, As...);
				else
				{
					nik_ce auto h0 = alias<Operator::unite, val.v1, val.v2, X0>;

					return NIK_MACHINE(d, MT::id, c, i, Vs)(h0, U_pack_Vs<Xs...>, H2, As...);
				}
			}
		};

	// recall:

		template<key_type... filler>
		struct machine<MN::recall, MT::cut, filler...>
		{
			template
			<
				NIK_CONTR_PARAMS, auto... Vs,
				auto rtn, auto pack, auto n, auto... _Vs,
				auto X0, auto... Xs, typename... Heaps
			>
			nik_ces auto result
			(
				nik_avp(auto_pack<rtn>*), nik_avp(auto_pack<pack, n, _Vs...>*),
				nik_vp(H1)(auto_pack<X0, Xs...>*), Heaps... Hs
			)
			{
				nik_ce auto val = NIK_FUNCTION_BLOCK(3, d, n, rtn, _Vs)(pack);

				if nik_ce (is_machination<decltype(val)>)

					return NIK_MACHINE(d, MT::cut, c, i, Vs)(val.s1, val.s2, H1, Hs...);
				else
				{
					nik_ce auto h0 = alias<Operator::unite, val.v1, val.v2, X0>;

					return NIK_MACHINE(d, MT::id, c, i, Vs)(h0, U_pack_Vs<Xs...>, Hs...);
				}
			}
		};

/***********************************************************************************************************************/

// variable:

	// call:

		template<key_type... filler>
		struct machine<MN::call, MT::variable, filler...>
		{
			template<NIK_CONTR_PARAMS, auto... Vs, auto... Ws, auto n, auto... Xs, typename... Heaps> 
			nik_ces auto result(nik_vp(H0)(auto_pack<Ws...>*), nik_vp(H1)(auto_pack<n, Xs...>*), Heaps... Hs)
			{
				nik_ce auto ins	= MD::instr(c, i);
				nik_ce auto rtn	= ins[MI::rtn];
				nik_ce auto ctn	= ins[MI::ctn];
				nik_ce auto val	= NIK_VARIABLE_BLOCK(9, d, n, rtn, Ws);

				if nik_ce (is_machination<decltype(val)>)

					return NIK_MACHINE(d, MT::variable, c, i, Vs)(val.s1, val.s2, H1, Hs...);

				else if nik_ce (ctn == MI::h1)

					return NIK_MACHINE(d, MT::id, c, i, Vs)
						(U_null_Vs, U_pack_Vs<val, Xs...>, Hs...);

				else if nik_ce (ctn == MI::h1_pair)

				//	return NIK_MACHINE(d, MT::id, c, i, Vs)
				//		(U_null_Vs, U_pack_Vs<val.v1, val.v2, Xs...>, Hs...);

					return NIK_MACHINE(d, MT::id, c, i, Vs)
					(
						U_null_Vs, U_pack_Vs
						<
							tuple_value<0>(val),
							tuple_value<1>(val), Xs...

						>, Hs...
					);
				else
					return val;
			}
		};

	// recall:

		template<key_type... filler>
		struct machine<MN::recall, MT::variable, filler...>
		{
			template
			<
				NIK_CONTR_PARAMS, auto... Vs,
				auto rtn, auto n, auto... _Vs,
				auto... Xs, typename... Heaps
			>
			nik_ces auto result
			(
				nik_avp(auto_pack<rtn>*), nik_avp(auto_pack<n, _Vs...>*),
				nik_vp(H1)(auto_pack<Xs...>*), Heaps... Hs
			)
			{
				nik_ce auto ins = MD::instr(c, i);
				nik_ce auto ctn = ins[MI::ctn];
				nik_ce auto val = NIK_VARIABLE_BLOCK(9, d, n, rtn, _Vs);

				if nik_ce (is_machination<decltype(val)>)

					return NIK_MACHINE(d, MT::variable, c, i, Vs)(val.s1, val.s2, H1, Hs...);

				else if nik_ce (ctn == MI::h1)

					return NIK_MACHINE(d, MT::id, c, i, Vs)(U_null_Vs, U_pack_Vs<val, Xs...>, Hs...);

				else if nik_ce (ctn == MI::h1_pair)

				//	return NIK_MACHINE(d, MT::id, c, i, Vs)
				//		(U_null_Vs, U_pack_Vs<val.v1, val.v2, Xs...>, Hs...);

					return NIK_MACHINE(d, MT::id, c, i, Vs)
					(
						U_null_Vs, U_pack_Vs
						<
							tuple_value<0>(val),
							tuple_value<1>(val), Xs...

						>, Hs...
					);
				else
					return val;
			}
		};

/***********************************************************************************************************************/

// function:

	// call:

		template<key_type... filler>
		struct machine<MN::call, MT::function, filler...>
		{
			template<NIK_CONTR_PARAMS, auto... Vs, auto... Ws, auto n, auto... Xs, typename... Heaps>
			nik_ces auto result(nik_vp(H0)(auto_pack<Ws...>*), nik_vp(H1)(auto_pack<n, Xs...>*), Heaps... Hs)
			{
				nik_ce auto ins	= MD::instr(c, i);
				nik_ce auto rtn	= ins[MI::rtn];
				nik_ce auto ctn	= ins[MI::ctn];
				nik_ce auto val	= NIK_FUNCTION_BLOCK(9, d, n, rtn, Ws)(U_null_Vs);

				if nik_ce (is_machination<decltype(val)>)

					return NIK_MACHINE(d, MT::function, c, i, Vs)(val.s1, val.s2, H1, Hs...);

				else if nik_ce (ctn == MI::h1 || ctn == MI::h1_pair)

				//	return NIK_MACHINE(d, MT::id, c, i, Vs)
				//		(U_null_Vs, U_pack_Vs<val.v1, val.v2, Xs...>, Hs...);

					return NIK_MACHINE(d, MT::id, c, i, Vs)
					(
						U_null_Vs, U_pack_Vs
						<
							tuple_value<0>(val),
							tuple_value<1>(val), Xs...

						>, Hs...
					);
				else
					return val;
			}
		};

	// recall:

		template<key_type... filler>
		struct machine<MN::recall, MT::function, filler...>
		{
			template
			<
				NIK_CONTR_PARAMS, auto... Vs,
				auto rtn, auto pack, auto n, auto... _Vs,
				auto... Xs, typename... Heaps
			>
			nik_ces auto result
			(
				nik_avp(auto_pack<rtn>*), nik_avp(auto_pack<pack, n, _Vs...>*),
				nik_vp(H1)(auto_pack<Xs...>*), Heaps... Hs
			)
			{
				nik_ce auto val = NIK_FUNCTION_BLOCK(9, d, n, rtn, _Vs)(pack);

				if nik_ce (is_machination<decltype(val)>)

					return NIK_MACHINE(d, MT::function, c, i, Vs)(val.s1, val.s2, H1, Hs...);
				else
					return NIK_MACHINE(d, MT::id, c, i, Vs)
						(U_null_Vs, U_pack_Vs<val.v1, val.v2, Xs...>, Hs...);
			}
		};

/***********************************************************************************************************************/

// cascade:

	// call:

		template<key_type... filler>
		struct machine<MN::call, MT::cascade, filler...>
		{
			template<NIK_CONTR_PARAMS, auto... Vs, auto Op, auto W0, auto... Ws, auto n, auto... Xs, typename... Heaps>
			nik_ces auto result(nik_vp(H0)(auto_pack<Op, W0, Ws...>*), nik_vp(H1)(auto_pack<n, Xs...>*), Heaps... Hs)
			{
				nik_ce auto ins	= MD::instr(c, i);
				nik_ce auto rtn	= ins[MI::rtn];
				nik_ce auto ctn	= ins[MI::ctn];
				nik_ce auto val	= NIK_CASCADE_BLOCK(d, n, Op, W0, Ws);

				if nik_ce (is_machination<decltype(val)>)

					return NIK_MACHINE(d, MT::cascade, c, i, Vs)(val.s1, val.s2, H1, Hs...);

				else if nik_ce (ctn == MI::h1)

					return NIK_MACHINE(d, MT::id, c, i, Vs)(U_null_Vs, U_pack_Vs<val, Xs...>, Hs...);
				else
					return val;
			}
		};

	// recall:

		template<key_type... filler>
		struct machine<MN::recall, MT::cascade, filler...>
		{
			// BT::id:

			template
			<
				NIK_CONTR_PARAMS, auto... Vs,
				typename OpType, auto n, auto _s1, auto _s2, auto... _Vs,
				auto... Xs, typename... Heaps
			>
			nik_ces auto result
			(
				OpType op, nik_avp(auto_pack<BT::id, n, _s1, _s2, _Vs...>*),
				nik_vp(H1)(auto_pack<Xs...>*), Heaps... Hs
			)
			{
				nik_ce auto _c	= controller<instruction<MN::call, MT::internal>>;
				nik_ce auto _i	= MD::initial_index;
				nik_ce auto val	= NIK_BEGIN_MACHINE(d, MT::internal, _c, _i)
								NIK_END_MACHINE(_s1, _s2);

				if nik_ce (is_machination<decltype(val)>)
				{
					nik_ce auto s2 = U_pack_Vs<BT::id, n, val.s1, val.s2, _Vs...>;

					return NIK_MACHINE(d, MT::cascade, c, i, Vs)(op, s2, H1, Hs...);
				}
				else
					return NIK_MACHINE(d, MT::cascade, c, i, Vs)
						(op, U_pack_Vs<BT::pause, n, val, _Vs...>, H1, Hs...);
			}

			// BT::pause:

			template
			<
				NIK_CONTR_PARAMS, auto... Vs,
				auto Op, auto n, auto _V, auto... _Vs,
				auto... Xs, typename... Heaps
			>
			nik_ces auto result
			(
				nik_avp(auto_pack<Op>*), nik_avp(auto_pack<BT::pause, n, _V, _Vs...>*),
				nik_vp(H1)(auto_pack<Xs...>*), Heaps... Hs
			)
			{
				nik_ce auto val = NIK_CASCADE_BLOCK(d, n, Op, _V, _Vs);

				if nik_ce (is_machination<decltype(val)>)

					return NIK_MACHINE(d, MT::cascade, c, i, Vs)(val.s1, val.s2, H1, Hs...);
				else
					return NIK_MACHINE(d, MT::id, c, i, Vs)(U_null_Vs, U_pack_Vs<val, Xs...>, Hs...);
			}
		};

/***********************************************************************************************************************/

// compel:

	// call:

		template<key_type... filler>
		struct machine<MN::call, MT::compel, filler...>
		{
			template
			<
				NIK_CONTR_PARAMS, auto... Vs,
				auto Op, auto... Ws, auto... Xs, typename... Heaps
			>
			nik_ces auto result
			(
				nik_vp(H0)(auto_pack<Op, Ws...>*),
				nik_vp(H1)(auto_pack<Xs...>*), Heaps... Hs
			)
			{
				nik_ce auto ins	= MD::instr(c, i);
				nik_ce auto n	= ins[MI::dec];

				if nik_ce (n >= d) // analogous to returning a machination.

					return NIK_MACHINE(0, MT::compel, c, i, Vs)(H0, H1, Hs...);
				else
				{
					nik_ce auto ctn	= ins[MI::ctn];
					nik_ce auto nd	= d+1-n;
					nik_ce auto val	= T_store_U<Op>::template result<nd, Ws...>;

					if nik_ce (is_machination<decltype(val)>)

						return NIK_MACHINE(d, MT::propel, c, i, Vs)(val.s1, val.s2, H1, Hs...);

					else if nik_ce (ctn == MI::h1)

						return NIK_MACHINE(d, MT::id, c, i, Vs)
							(U_null_Vs, U_pack_Vs<val, Xs...>, Hs...);

					else if nik_ce (ctn == MI::h1_pair)

					//	return NIK_MACHINE(d, MT::id, c, i, Vs)
					//		(U_null_Vs, U_pack_Vs<val.v1, val.v2, Xs...>, Hs...);

						return NIK_MACHINE(d, MT::id, c, i, Vs)
						(
							U_null_Vs, U_pack_Vs
							<
								tuple_value<0>(val),
								tuple_value<1>(val), Xs...

							>, Hs...
						);
					else
						return val;
				}
			}
		};

	// recall:

		template<key_type... filler>
		struct machine<MN::recall, MT::compel, filler...>
		{
			template
			<
				NIK_CONTR_PARAMS, auto... Vs,
				auto Op, auto... Ws, auto... Xs, typename... Heaps
			>
			nik_ces auto result
			(
				nik_vp(H0)(auto_pack<Op, Ws...>*),
				nik_vp(H1)(auto_pack<Xs...>*), Heaps... Hs
			)
			{
				nik_ce auto ins	= MD::instr(c, i);
				nik_ce auto n	= ins[MI::dec];

				if nik_ce (n >= d) // analogous to returning a machination.

					return NIK_MACHINE(0, MT::compel, c, i, Vs)(H0, H1, Hs...);
				else
				{
					nik_ce auto ctn	= ins[MI::ctn];
					nik_ce auto nd	= d+1-n;
					nik_ce auto val	= T_store_U<Op>::template result<nd, Ws...>;

					if nik_ce (is_machination<decltype(val)>)

						return NIK_MACHINE(d, MT::propel, c, i, Vs)(val.s1, val.s2, H1, Hs...);

					else if nik_ce (ctn == MI::h1)

						return NIK_MACHINE(d, MT::id, c, i, Vs)
							(U_null_Vs, U_pack_Vs<val, Xs...>, Hs...);

					else if nik_ce (ctn == MI::h1_pair)

					//	return NIK_MACHINE(d, MT::id, c, i, Vs)
					//		(U_null_Vs, U_pack_Vs<val.v1, val.v2, Xs...>, Hs...);

						return NIK_MACHINE(d, MT::id, c, i, Vs)
						(
							U_null_Vs, U_pack_Vs
							<
								tuple_value<0>(val),
								tuple_value<1>(val), Xs...

							>, Hs...
						);
					else
						return val;
				}
			}
		};

/***********************************************************************************************************************/

// propel:

	// call: No direct call.

	// recall:

		template<key_type... filler>
		struct machine<MN::recall, MT::propel, filler...>
		{
			template
			<
				NIK_CONTR_PARAMS, auto... Vs,
				auto _m, auto _c, auto _i, auto... _Vs,
				auto... _Hs, auto... Xs, typename... Heaps
			>
			nik_ces auto result
			(
				nik_avp(auto_pack<_m, _c, _i, _Vs...>*), nik_avp(auto_pack<_Hs...>*),
				nik_vp(H1)(auto_pack<Xs...>*), Heaps... Hs
			)
			{
				nik_ce auto ins = MD::instr(c, i);
				nik_ce auto ctn = ins[MI::ctn];
				nik_ce auto val = NIK_MACHINE(d, _m, _c, _i, _Vs)(_Hs...);

				if nik_ce (is_machination<decltype(val)>)

					return NIK_MACHINE(d, MT::propel, c, i, Vs)(val.s1, val.s2, H1, Hs...);

				else if nik_ce (ctn == MI::h1)

					return NIK_MACHINE(d, MT::id, c, i, Vs)(U_null_Vs, U_pack_Vs<val, Xs...>, Hs...);

				else if nik_ce (ctn == MI::h1_pair)

				//	return NIK_MACHINE(d, MT::id, c, i, Vs)
				//		(U_null_Vs, U_pack_Vs<val.v1, val.v2, Xs...>, Hs...);

					return NIK_MACHINE(d, MT::id, c, i, Vs)
					(
						U_null_Vs, U_pack_Vs
						<
							tuple_value<0>(val),
							tuple_value<1>(val), Xs...

						>, Hs...
					);
				else
					return val;
			}
		};

/***********************************************************************************************************************/

// internal:

	// call:

		template<key_type... filler>
		struct machine<MN::call, MT::internal, filler...>
		{
			template<NIK_CONTR_PARAMS, auto _m, auto _c, auto _i, auto... Vs, typename... Heaps>
			nik_ces auto result(Heaps...)
			{
				nik_ce auto val = NIK_MACHINE(d, _m, _c, _i, Vs)(U_restore_T<Heaps>...);

				if nik_ce (is_machination<decltype(val)>)

					return NIK_BEGIN_MACHINE(d, MT::internal, c, i) NIK_END_MACHINE(val.s1, val.s2);
				else
					return val;
			}
		};

	// recall:

		template<key_type... filler>
		struct machine<MN::recall, MT::internal, filler...>
		{
			template<NIK_CONTR_PARAMS, auto _m, auto _c, auto _i, auto... _Vs, auto... _Hs>
			nik_ces auto result(nik_avp(auto_pack<_m, _c, _i, _Vs...>*), nik_avp(auto_pack<_Hs...>*))
			{
				nik_ce auto val = NIK_MACHINE(d, _m, _c, _i, _Vs)(_Hs...);

				if nik_ce (is_machination<decltype(val)>)

					return NIK_BEGIN_MACHINE(d, MT::internal, c, i) NIK_END_MACHINE(val.s1, val.s2);
				else
					return val;
			}
		};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// halters:

/***********************************************************************************************************************/

// pause:

	template<key_type... filler>
	struct machine<MN::halt, MT::pause, filler...>
	{
		template<NIK_CONTR_PARAMS, auto... Vs, typename... Heaps>
		nik_ces auto result(Heaps...)
		{
			nik_ce auto s1 = U_pack_Vs<m, c, i, Vs...>;
			nik_ce auto s2 = U_pack_Vs<U_restore_T<Heaps>...>;

			return machination(s1, s2);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// move:

/***********************************************************************************************************************/

// junction:

	template<key_type... filler>
	struct machine<MN::move_j_all, MT::id, filler...>
	{
		template<NIK_CONTR_PARAMS, auto... Vs, auto... Ws, auto... Xs, typename... Heaps>
		nik_ces auto result(nik_vp(H0)(auto_pack<Ws...>*), nik_vp(H1)(auto_pack<Xs...>*), Heaps... Hs)
		{
			return NIK_MACHINE(d, MT::id, c, i, Vs)(U_pack_Vs<Ws..., Xs...>, U_null_Vs, Hs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// paste:

/***********************************************************************************************************************/

// register:

	template<key_type... filler>
	struct machine<MN::paste_r_all, MT::id, filler...>
	{
		template<NIK_CONTR_PARAMS, auto... Vs, auto... Ws, typename... Heaps>
		nik_ces auto result(nik_vp(H0)(auto_pack<Ws...>*), Heaps... Hs)
		{
			return NIK_MACHINE(d, MT::id, c, i, Ws)(U_null_Vs, Hs...);
		}
	};

// argument:

	template<key_type... filler>
	struct machine<MN::paste_a_all, MT::id, filler...>
	{
		template<NIK_CONTR_PARAMS, auto... Vs, auto... Ws, typename Heap1, typename Heap2, typename... Args>
		nik_ces auto result(nik_vp(H0)(auto_pack<Ws...>*), Heap1 H1, Heap2 H2, Args... As)
		{
			return NIK_MACHINE(d, MT::id, c, i, Vs)(U_null_Vs, H1, H2, Ws...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// go to:

/***********************************************************************************************************************/

// id:

	template<key_type... filler>
	struct machine<MN::go_to, MT::id, filler...>
	{
		template<NIK_CONTR_PARAMS, auto... Vs, typename... Heaps>
		nik_ces auto result(Heaps... Hs)
		{
			nik_ce auto ins	= MD::instr(c, i);
			nik_ce auto ni	= ins[MI::pos];

			return NIK_MACHINE(d, MT::id, c, ni, Vs)(Hs...);
		}
	};

// conditional:

	template<key_type... filler>
	struct machine<MN::go_to, MT::conditional, filler...>
	{
		template<NIK_CONTR_PARAMS, auto... Vs, typename Heap0, bool X0, auto... Xs, typename... Heaps>
		nik_ces auto result(Heap0 H0, nik_vp(H1)(auto_pack<X0, Xs...>*), Heaps... Hs)
		{
			nik_ce auto ins	= MD::instr(c, i);
			nik_ce auto ni	= X0 ? ins[MI::pos] : i;

			return NIK_MACHINE(d, MT::id, c, ni, Vs)(H0, U_pack_Vs<Xs...>, Hs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// memoize:

/***********************************************************************************************************************/

// lookup:

	template<key_type... filler>
	struct machine<MN::memoize, MT::lookup, filler...>
	{
		struct T_same_car
		{
			template<auto W, auto Z>
			nik_ces auto result = alias
			<
				Operator::same, W,
				unpack_alias<Z, Operator::car>
			>;

		}; nik_ces auto U_same_car = U_store_T<T_same_car>;

		template
		<
			NIK_CONTR_PARAMS, auto... Vs,
			auto W0, auto... Xs, typename Heap2, auto... Zs, typename... Args
		>
		nik_ces auto result
		(
			nik_vp(H0)(auto_pack<W0>*),
			nik_vp(H1)(auto_pack<Xs...>*), Heap2 H2,
			nik_vp(A0)(auto_pack<Zs...>*), Args... As
		)
		{
			nik_ce auto size = sizeof...(Zs);
			nik_ce auto pos	 = alias<Operator::find, U_custom<U_same_car, W0>, Zs...>;

			if nik_ce (pos == size)

				return NIK_MACHINE(d, MT::id, c, i, Vs)(U_null_Vs, H1, H2, A0, As...);
			else
			{
				nik_ce auto ins = MD::instr(c, i);
				nik_ce auto ni  = ins[MI::pos];

				return NIK_MACHINE(d, MT::id, c, ni, Vs)(A0, U_pack_Vs<pos, Xs...>, H2, A0, As...);
			}
		}
	};

/***********************************************************************************************************************/

// insert:

	template<key_type... filler>
	struct machine<MN::memoize, MT::insert, filler...>
	{
		template
		<
			NIK_CONTR_PARAMS, auto... Vs,
			auto W0, auto X0, auto... Xs, typename Heap2, auto... Zs, typename... Args
		>
		nik_ces auto result
		(
			nik_vp(H0)(auto_pack<W0>*),
			nik_vp(H1)(auto_pack<X0, Xs...>*), Heap2 H2,
			nik_vp(A0)(auto_pack<Zs...>*), Args... As
		)
		{
			nik_ce auto Z0 = U_pack_Vs<W0, X0>;
			nik_ce auto a0 = U_pack_Vs<Z0, Zs...>;

			return tuple<decltype(a0), decltype(X0)>(a0, X0);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// start:

	// Nesting depth limits are mitigated here implicitly
	// as the machines being called trampoline internally.

/***********************************************************************************************************************/

// variable:

	template<auto d, auto n, auto rtn, typename Heap0>
	nik_ce auto variable_start(Heap0 H0)
	{
		nik_ce auto ctn = MI::value;
		nik_ce auto m   = MT::id;
		nik_ce auto c   = controller<variable<rtn, ctn>>;
		nik_ce auto i   = MD::initial_index;
		nik_ce auto H1  = U_pack_Vs<n>;

		return NIK_BEGIN_MACHINE(d, m, c, i) NIK_END_MACHINE(H0, H1, U_null_Vs);
	}

// function:

	template<auto d, auto n, auto rtn, typename Heap0>
	nik_ce auto function_start(Heap0 H0)
	{
		nik_ce auto ctn = MI::value;
		nik_ce auto m   = MT::id;
		nik_ce auto c   = controller<function<rtn, ctn>>;
		nik_ce auto i   = MD::initial_index;
		nik_ce auto H1  = U_pack_Vs<n>;

		return NIK_BEGIN_MACHINE(d, m, c, i) NIK_END_MACHINE(H0, H1, U_null_Vs);
	}

// compel:

		// default dec = 3

	template<auto d, auto dec, typename Heap0>
	nik_ce auto compel_start(Heap0 H0)
	{
		nik_ce auto ctn = MI::value;
		nik_ce auto m   = MT::id;
		nik_ce auto c   = controller<compel<ctn, dec>>;
		nik_ce auto i   = MD::initial_index;

		return NIK_BEGIN_MACHINE(d, m, c, i) NIK_END_MACHINE(H0, U_null_Vs, U_null_Vs);
	}

// general:

	template<auto d, auto prog, auto... Vs, typename Heap0, typename Heap1, typename CHeap, typename... Args>
	nik_ce auto general_start(Heap0 H0, Heap1 H1, CHeap ch, Args... As)
	{
		nik_ce auto m = MT::id;
		nik_ce auto c = controller<internal<>>;
		nik_ce auto i = MD::initial_index;

		return NIK_BEGIN_MACHINE(d, m, c, i), m, prog, i, Vs... NIK_END_MACHINE(H0, H1, ch, As...);
	}

// start:

	template<auto d, auto prog, auto... Vs, typename CHeap, typename... Args>
	nik_ce auto start(CHeap ch, Args... As) { return general_start<d, prog, Vs...>(U_null_Vs, U_null_Vs, ch, As...); }

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

