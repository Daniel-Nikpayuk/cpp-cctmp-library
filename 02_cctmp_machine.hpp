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

// machine:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// instructions:

/***********************************************************************************************************************/

// names:

	struct InstrName
	{
		nik_ces key_type id				=  0;
		nik_ces key_type identity			= id; // convenience for
								      // default params.

		nik_ces key_type recall				=  1;
		nik_ces key_type call				=  2;
		nik_ces key_type halt				=  3;

		nik_ces key_type move_j_all			=  4;

		nik_ces key_type paste_r_all			=  5;
		nik_ces key_type paste_a_all			=  6;

		nik_ces key_type go_to				=  7;

		nik_ces key_type memoize			=  8;
	};

	using MN = InstrName;

/***********************************************************************************************************************/

// notes:

	struct InstrNote
	{
		nik_ces key_type id				=  0;
		nik_ces key_type identity			= id;	// convenience for
									// default params.

		nik_ces key_type start				=  1;

		nik_ces key_type copy_r_pos			=  2;
		nik_ces key_type copy_j_pos			=  3;
		nik_ces key_type copy_c_pos			=  4;
		nik_ces key_type copy_a_pos			=  5;
		nik_ces key_type copy				=  6;

		nik_ces key_type cut_r_pos			=  7;
		nik_ces key_type cut_a_pos			=  8;
		nik_ces key_type cut				=  9;

		nik_ces key_type action				= 10;
		nik_ces key_type compel				= 11;
		nik_ces key_type propel				= 12;

		nik_ces key_type pause				= 13;

		nik_ces key_type conditional			= 14;

		nik_ces key_type lookup				= 15;
		nik_ces key_type insert				= 16;
	};

	using MT = InstrNote;

/***********************************************************************************************************************/

// locations:

	struct InstrLocs
	{
		using type						= index_type const * const;

		nik_ces key_type size					= 0;
		nik_ces key_type name					= 1;
		nik_ces key_type note					= 2;

		nik_ces key_type pos					= 3;
		nik_ces key_type dec					= 3;
		nik_ces key_type rtn					= 3;

		nik_ces key_type ctn					= 4;
		nik_ces key_type key					= 5;
		nik_ces key_type act					= 6;

		// locations:

		nik_ces key_type _register				= 0;
		nik_ces key_type _junction				= 1;
		nik_ces key_type _constant				= 2;
		nik_ces key_type _argument				= 3;

		// actions:

		nik_ces key_type h0					= 0;
		nik_ces key_type h0_write				= 1;
		nik_ces key_type h1					= 2;
		nik_ces key_type h1_pair				= 3; // C++17 specific.
		nik_ces key_type value					= 4;

		nik_ces index_type length     (type i)			{ return i[size]; }
		nik_ces bool       is_optimal (cindex_type n)		{ return (n < _eight); }

		nik_ces auto copy_note(ckey_type l)
		{
			if      (l == _register) return MT::copy_r_pos;
			else if (l == _junction) return MT::copy_j_pos;
			else if (l == _constant) return MT::copy_c_pos;
			else                     return MT::copy_a_pos;
		}

		nik_ces auto cut_note(ckey_type l)
		{
			if   (l == _register) return MT::cut_r_pos;
			else                  return MT::cut_a_pos;
		}

		nik_ces auto paste_name(ckey_type l)
		{
			if   (l == _register) return MN::paste_r_all;
			else                  return MN::paste_a_all;
		}
	};

	using MI			= InstrLocs;
	using instr_type		= typename MI::type;

	nik_ce auto _register		= MI::_register;
	nik_ce auto _junction		= MI::_junction;
	nik_ce auto _constant		= MI::_constant;
	nik_ce auto _argument		= MI::_argument;

	nik_ce auto _h0			= MI::h0;
	nik_ce auto _h0_write		= MI::h0_write;
	nik_ce auto _h1			= MI::h1;
	nik_ce auto _h1_pair		= MI::h1_pair;
	nik_ce auto _value		= MI::value;

	template<index_type... Vs>
	nik_ce instr_type instruction = array<index_type, sizeof...(Vs), Vs...>;

/***********************************************************************************************************************/

// controllers:

	struct InstrContr
	{
		using type					= instr_type const * const;

		nik_ces key_type size				= 0;

		nik_ces index_type length (type l)		{ return l[size][MI::size]; }
	};

	using MC		= InstrContr;
	using contr_type	= typename MC::type;

	template<instr_type... Vs>
	nik_ce contr_type controller = array<instr_type, array<index_type, sizeof...(Vs)>, Vs...>;

/***********************************************************************************************************************/

// dispatch:

	struct InstrDisp
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

	using MD = InstrDisp;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// machine:

	template<key_type, key_type, auto...> struct T_machine;

	// H0: Holds operators.
	// H1: Holds stack parameters.
	// H2: Holds stack arguments.
	// H3: Holds return values.
	// H4: Holds constants.
	// H5: Holds memoization tables (if applicable).

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// start:

/***********************************************************************************************************************/

	template<auto... Vs>
	nik_ce auto machine = U_pack_Vs<Vs...>;

	template<auto d, auto... Hs, nik_vp(p)(auto_pack<Hs...>*), auto m, auto c, auto i, auto...Vs>
	nik_ce auto machine<d, p, m, c, i, Vs...> = NIK_MACHINE(d, m, c, i, Vs)(Hs...);

	template<auto... filler>
	struct T_machine<MN::call, MT::start, filler...>
	{
		template<auto d, auto p, auto m, auto c, auto i, auto...Vs>
		nik_ces auto result = machine<d, p, m, c, i, Vs...>;

	}; nik_ce auto U_machine = U_store_T<T_machine<MN::call, MT::start>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// copy:

/***********************************************************************************************************************/

// register:

	template<auto... filler>
	struct T_machine<MN::call, MT::copy_r_pos, filler...>
	{
		template<NIK_CONTR_PARAMS, auto... Vs, auto... Ws, auto... Xs, typename... Heaps>
		nik_ces auto result(nik_vp(H0)(auto_pack<Ws...>*), Heaps... Hs)
		{
			nik_ce auto ins	= MD::instr(c, i);
			nik_ce auto n	= ins[MI::pos];
			nik_ce auto ctn	= ins[MI::ctn];
			nik_ce auto val	= NIK_VARIABLE_BLOCK(3, d, n, U_car, Vs);

			if nik_ce (is_machination<decltype(val)>)

				return NIK_MACHINE(d, MT::copy, c, i, Vs)(val.p, H0, Hs...);

			else if nik_ce (ctn == MI::h0)

				return NIK_MACHINE(d, MT::id, c, i, Vs)(U_pack_Vs<Ws..., val>, Hs...);

			else if nik_ce (ctn == MI::h0_write)

				return NIK_MACHINE(d, MT::id, c, i, Vs)(val, Hs...);
			else
				return val;
		}
	};

/***********************************************************************************************************************/

// junction:

	template<auto... filler>
	struct T_machine<MN::call, MT::copy_j_pos, filler...>
	{
		template<NIK_CONTR_PARAMS, auto... Vs, auto... Ws, auto... Xs, typename... Heaps>
		nik_ces auto result(nik_vp(H0)(auto_pack<Ws...>*), nik_vp(H1)(auto_pack<Xs...>*), Heaps... Hs)
		{
			nik_ce auto ins	= MD::instr(c, i);
			nik_ce auto n	= ins[MI::pos];
			nik_ce auto ctn	= ins[MI::ctn];
			nik_ce auto val	= NIK_VARIABLE_BLOCK(3, d, n, U_car, Xs);

			if nik_ce (is_machination<decltype(val)>)

				return NIK_MACHINE(d, MT::copy, c, i, Vs)(val.p, H0, H1, Hs...);

			else if nik_ce (ctn == MI::h0)

				return NIK_MACHINE(d, MT::id, c, i, Vs)(U_pack_Vs<Ws..., val>, H1, Hs...);

			else if nik_ce (ctn == MI::h0_write)

				return NIK_MACHINE(d, MT::id, c, i, Vs)(val, H1, Hs...);
			else
				return val;
		}
	};

/***********************************************************************************************************************/

// constant:

	template<auto... filler>
	struct T_machine<MN::call, MT::copy_c_pos, filler...>
	{
		template<NIK_CONTR_PARAMS, auto... Vs, auto... Ws, typename Heap1, auto... Ys, typename... Args>
		nik_ces auto result(nik_vp(H0)(auto_pack<Ws...>*), Heap1 H1, nik_vp(H2)(auto_pack<Ys...>*), Args... As)
		{
			nik_ce auto ins	= MD::instr(c, i);
			nik_ce auto n	= ins[MI::pos];
			nik_ce auto ctn	= ins[MI::ctn];
			nik_ce auto val	= NIK_VARIABLE_BLOCK(3, d, n, U_car, Ys);

			if nik_ce (is_machination<decltype(val)>)

				return NIK_MACHINE(d, MT::copy, c, i, Vs)(val.p, H0, H1, H2, As...);

			else if nik_ce (ctn == MI::h0)

				return NIK_MACHINE(d, MT::id, c, i, Vs)(U_pack_Vs<Ws..., val>, H1, H2, As...);

			else if nik_ce (ctn == MI::h0_write)

				return NIK_MACHINE(d, MT::id, c, i, Vs)(val, H1, H2, As...);
			else
				return val;
		}
	};

/***********************************************************************************************************************/

// argument:

	template<auto... filler>
	struct T_machine<MN::call, MT::copy_a_pos, filler...>
	{
		template<NIK_CONTR_PARAMS, auto... Vs, auto... Ws, typename Heap1, typename Heap2, typename... Args>
		nik_ces auto result(nik_vp(H0)(auto_pack<Ws...>*), Heap1 H1, Heap2 H2, Args... As)
		{
			nik_ce auto ins	= MD::instr(c, i);
			nik_ce auto n	= ins[MI::pos];
			nik_ce auto ctn	= ins[MI::ctn];
			nik_ce auto val	= NIK_VARIABLE_BLOCK(3, d, n, U_car, U_restore_T<Args>);

			if nik_ce (is_machination<decltype(val)>)

				return NIK_MACHINE(d, MT::copy, c, i, Vs)(val.p, H0, H1, H2, As...);

			else if nik_ce (ctn == MI::h0)

				return NIK_MACHINE(d, MT::id, c, i, Vs)(U_pack_Vs<Ws..., val>, H1, H2, As...);

			else if nik_ce (ctn == MI::h0_write)

				return NIK_MACHINE(d, MT::id, c, i, Vs)(val, H1, H2, As...);
			else
				return val;
		}
	};

/***********************************************************************************************************************/

// recall:

	template<auto... filler>
	struct T_machine<MN::recall, MT::copy, filler...>
	{
		template
		<
			NIK_CONTR_PARAMS, auto... Vs,
			auto n, auto rtn, auto... _Vs,
			auto... Ws, auto... Xs, typename... Heaps
		>
		nik_ces auto result(nik_avp(auto_pack<n, rtn, _Vs...>*), nik_vp(H0)(auto_pack<Ws...>*), Heaps... Hs)
		{
			nik_ce auto ins = MD::instr(c, i);
			nik_ce auto ctn = ins[MI::ctn];
			nik_ce auto val = T_block_variable::template result<d, n, rtn, _Vs...>;

			if nik_ce (is_machination<decltype(val)>)

				return NIK_MACHINE(d, MT::copy, c, i, Vs)(val.p, H0, Hs...);

			else if nik_ce (ctn == MI::h0)

				return NIK_MACHINE(d, MT::id, c, i, Vs)(U_pack_Vs<Ws..., val>, Hs...);

			else if nik_ce (ctn == MI::h0_write)

				return NIK_MACHINE(d, MT::id, c, i, Vs)(val, Hs...);
			else
				return val;
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// cut:

/***********************************************************************************************************************/

// register:

	template<auto... filler>
	struct T_machine<MN::call, MT::cut_r_pos, filler...>
	{
		template<NIK_CONTR_PARAMS, auto... Vs, typename Heap0, auto X0, auto... Xs, typename... Heaps>
		nik_ces auto result(Heap0 H0, nik_vp(H1)(auto_pack<X0, Xs...>*), Heaps... Hs)
		{
			nik_ce auto ins	= MD::instr(c, i);
			nik_ce auto n	= ins[MI::pos];
			nik_ce auto val	= NIK_FUNCTION_BLOCK(3, d, n, U_block_filter, Vs)(U_null_Vs);

			if nik_ce (is_machination<decltype(val)>)

				return NIK_MACHINE(d, MT::cut, c, i, Vs)(val.p, H0, H1, Hs...);
			else
			{
				nik_ce auto v0 = tuple_value<0>(val);
				nik_ce auto v1 = tuple_value<1>(val);
				nik_ce auto h0 = alias<Operator::unite, v0, v1, X0>;

				return NIK_MACHINE(d, MT::id, c, i, Vs)(h0, U_pack_Vs<Xs...>, Hs...);
			}
		}
	};

/***********************************************************************************************************************/

// argument:

	template<auto... filler>
	struct T_machine<MN::call, MT::cut_a_pos, filler...>
	{
		template<NIK_CONTR_PARAMS, auto... Vs, typename Heap0, auto X0, auto... Xs, typename Heap2, typename... Args>
		nik_ces auto result(Heap0 H0, nik_vp(H1)(auto_pack<X0, Xs...>*), Heap2 H2, Args... As)
		{
			nik_ce auto ins	= MD::instr(c, i);
			nik_ce auto n	= ins[MI::pos];
			nik_ce auto val	= NIK_FUNCTION_BLOCK(3, d, n, U_block_filter, U_restore_T<Args>)(U_null_Vs);

			if nik_ce (is_machination<decltype(val)>)

				return NIK_MACHINE(d, MT::cut, c, i, Vs)(val.p, H0, H1, H2, As...);
			else
			{
				nik_ce auto v0 = tuple_value<0>(val);
				nik_ce auto v1 = tuple_value<1>(val);
				nik_ce auto h0 = alias<Operator::unite, v0, v1, X0>;

				return NIK_MACHINE(d, MT::id, c, i, Vs)(h0, U_pack_Vs<Xs...>, As...);
			}
		}
	};

/***********************************************************************************************************************/

// recall:

	template<auto... filler>
	struct T_machine<MN::recall, MT::cut, filler...>
	{
		template
		<
			NIK_CONTR_PARAMS, auto... Vs,
			auto p, auto n, auto rtn, auto... _Vs,
			typename Heap0, auto X0, auto... Xs, typename... Heaps
		>
		nik_ces auto result
		(
			nik_avp(auto_pack<p, n, rtn, _Vs...>*),
			Heap0 H0, nik_vp(H1)(auto_pack<X0, Xs...>*), Heaps... Hs
		)
		{
			nik_ce auto val = T_block_function::template result<d, p, n, rtn, _Vs...>;

			if nik_ce (is_machination<decltype(val)>)

				return NIK_MACHINE(d, MT::cut, c, i, Vs)(val.p, H0, H1, Hs...);
			else
			{
				nik_ce auto v0 = tuple_value<0>(val);
				nik_ce auto v1 = tuple_value<1>(val);
				nik_ce auto h0 = alias<Operator::unite, v0, v1, X0>;

				return NIK_MACHINE(d, MT::id, c, i, Vs)(h0, U_pack_Vs<Xs...>, Hs...);
			}
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// action:

/***********************************************************************************************************************/

// call:

	template<auto... filler>
	struct T_machine<MN::call, MT::action, filler...>
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

					return NIK_MACHINE(d, MT::id, c, i, Vs)(U_null_Vs, U_pack_Vs<val, Xs...>, Hs...);

				else if nik_ce (ctn == MI::h1_pair)

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

// recall:

	template<auto... filler>
	struct T_machine<MN::recall, MT::action, filler...>
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

					return NIK_MACHINE(d, MT::id, c, i, Vs)(U_null_Vs, U_pack_Vs<val, Xs...>, Hs...);

				else if nik_ce (ctn == MI::h1_pair)

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
/***********************************************************************************************************************/

// compel:

/***********************************************************************************************************************/

// call:

	template<auto... filler>
	struct T_machine<MN::call, MT::compel, filler...>
	{
		template<NIK_CONTR_PARAMS, auto... Vs, auto Op, auto... Ws, auto... Xs, typename... Heaps>
		nik_ces auto result(nik_vp(H0)(auto_pack<Op, Ws...>*), nik_vp(H1)(auto_pack<Xs...>*), Heaps... Hs)
		{
			nik_ce auto ins	= MD::instr(c, i);
			nik_ce auto n	= ins[MI::dec];

			if nik_ce (n >= d) // analogous to returning a machination.

				return NIK_MACHINE(0, MT::compel, c, i, Vs)(H0, H1, Hs...);
			else
			{
				nik_ce auto ctn	= ins[MI::ctn];
				nik_ce auto key = ins[MI::key];
				nik_ce auto act = ins[MI::act];
				nik_ce auto nd	= d+1-n;
				nik_ce auto val = overload<U_overload<key, act>, Op, nd, Ws...>;

				if nik_ce (is_machination<decltype(val)>)

					return NIK_MACHINE(d, MT::propel, c, i, Vs)(val.u, val.p, H1, Hs...);

				else if nik_ce (ctn == MI::h1)

					return NIK_MACHINE(d, MT::id, c, i, Vs)(U_null_Vs, U_pack_Vs<val, Xs...>, Hs...);

				else if nik_ce (ctn == MI::h1_pair)

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

// recall:

	template<auto... filler>
	struct T_machine<MN::recall, MT::compel, filler...>
	{
		template<NIK_CONTR_PARAMS, auto... Vs, auto Op, auto... Ws, auto... Xs, typename... Heaps>
		nik_ces auto result(nik_vp(H0)(auto_pack<Op, Ws...>*), nik_vp(H1)(auto_pack<Xs...>*), Heaps... Hs)
		{
			nik_ce auto ins	= MD::instr(c, i);
			nik_ce auto n	= ins[MI::dec];

			if nik_ce (n >= d) // analogous to returning a machination.

				return NIK_MACHINE(0, MT::compel, c, i, Vs)(H0, H1, Hs...);
			else
			{
				nik_ce auto ctn	= ins[MI::ctn];
				nik_ce auto key = ins[MI::key];
				nik_ce auto act = ins[MI::act];
				nik_ce auto nd	= d+1-n;
				nik_ce auto val = overload<U_overload<key, act>, Op, nd, Ws...>;

				if nik_ce (is_machination<decltype(val)>)

					return NIK_MACHINE(d, MT::propel, c, i, Vs)(val.u, val.p, H1, Hs...);

				else if nik_ce (ctn == MI::h1)

					return NIK_MACHINE(d, MT::id, c, i, Vs)(U_null_Vs, U_pack_Vs<val, Xs...>, Hs...);

				else if nik_ce (ctn == MI::h1_pair)

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
/***********************************************************************************************************************/

// propel:

	// No direct call.

/***********************************************************************************************************************/

// recall:

	template<auto... filler>
	struct T_machine<MN::recall, MT::propel, filler...>
	{
		template<NIK_CONTR_PARAMS, auto... Vs, typename _U, auto... _Ws, auto... Xs, typename... Heaps>
		nik_ces auto result(_U, nik_avp(auto_pack<_Ws...>*), nik_vp(H1)(auto_pack<Xs...>*), Heaps... Hs)
		{
			nik_ce auto ins = MD::instr(c, i);
			nik_ce auto ctn = ins[MI::ctn];
			nik_ce auto val = T_restore_T<_U>::template result<d, _Ws...>;

			if nik_ce (is_machination<decltype(val)>)

				return NIK_MACHINE(d, MT::propel, c, i, Vs)(val.u, val.p, H1, Hs...);

			else if nik_ce (ctn == MI::h1)

				return NIK_MACHINE(d, MT::id, c, i, Vs)(U_null_Vs, U_pack_Vs<val, Xs...>, Hs...);

			else if nik_ce (ctn == MI::h1_pair)

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
/***********************************************************************************************************************/

// halters:

/***********************************************************************************************************************/

// pause:

	template<auto... filler>
	struct T_machine<MN::halt, MT::pause, filler...>
	{
		template<NIK_CONTR_PARAMS, auto... Vs, typename... Heaps>
		nik_ces auto result(Heaps...)
		{
			nik_ce auto p = U_pack_Vs<U_restore_T<Heaps>...>;

			return machination(U_machine, U_pack_Vs<p, m, c, i, Vs...>);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// move:

/***********************************************************************************************************************/

// junction:

	template<auto... filler>
	struct T_machine<MN::move_j_all, MT::id, filler...>
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

	template<auto... filler>
	struct T_machine<MN::paste_r_all, MT::id, filler...>
	{
		template<NIK_CONTR_PARAMS, auto... Vs, auto... Ws, typename... Heaps>
		nik_ces auto result(nik_vp(H0)(auto_pack<Ws...>*), Heaps... Hs)
		{
			return NIK_MACHINE(d, MT::id, c, i, Ws)(U_null_Vs, Hs...);
		}
	};

// argument:

	template<auto... filler>
	struct T_machine<MN::paste_a_all, MT::id, filler...>
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

	template<auto... filler>
	struct T_machine<MN::go_to, MT::id, filler...>
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

	template<auto... filler>
	struct T_machine<MN::go_to, MT::conditional, filler...>
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

	template<auto... filler>
	struct T_machine<MN::memoize, MT::lookup, filler...>
	{
		struct T_same_car
		{
			template<auto W, auto Z>
			nik_ces auto result = overload<U_same, W, unpack_<Z, U_car>>;

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
			nik_ce auto pos	 = find_<U_partial<U_custom, U_same_car, W0>, Zs...>;

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

	template<auto... filler>
	struct T_machine<MN::memoize, MT::insert, filler...>
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

/***********************************************************************************************************************/

/***********************************************************************************************************************/

// syntactic sugar:

	// Nesting depth limits are mitigated here implicitly
	// as the machines being called trampoline internally.

// variable:

/*
	template<auto d, auto n, auto rtn, typename Heap0>
	nik_ce auto variable_start(Heap0 H0)
	{
		nik_ce auto ctn = MI::value;
		nik_ce auto m   = MT::id;
		nik_ce auto c   = controller<variable<rtn, ctn>>;
		nik_ce auto i   = MD::initial_index;
		nik_ce auto H1  = U_pack_Vs<n>;

		return NIK_BEGIN_MACHINE(d, m, c, i, u) NIK_END_MACHINE(H0, H1, U_null_Vs);
	}
*/

// function:

/*
	template<auto d, auto n, auto rtn, typename Heap0>
	nik_ce auto function_start(Heap0 H0)
	{
		nik_ce auto ctn = MI::value;
		nik_ce auto m   = MT::id;
		nik_ce auto c   = controller<function<rtn, ctn>>;
		nik_ce auto i   = MD::initial_index;
		nik_ce auto H1  = U_pack_Vs<n>;

		return NIK_BEGIN_MACHINE(d, m, c, i, u) NIK_END_MACHINE(H0, H1, U_null_Vs);
	}
*/

// compel:

		// default dec = 3

/*
	template<auto d, auto dec, typename Heap0>
	nik_ce auto compel_start(Heap0 H0)
	{
		nik_ce auto ctn = MI::value;
		nik_ce auto m   = MT::id;
		nik_ce auto c   = controller<compel<ctn, dec>>;
		nik_ce auto i   = MD::initial_index;

		return NIK_BEGIN_MACHINE(d, m, c, i, u) NIK_END_MACHINE(H0, U_null_Vs, U_null_Vs);
	}
*/

// general:

/*
	template<auto d, auto prog, auto... Vs, typename Heap0, typename Heap1, typename CHeap, typename... Args>
	nik_ce auto general_start(Heap0 H0, Heap1 H1, CHeap ch, Args... As)
	{
		nik_ce auto m = MT::id;
		nik_ce auto c = controller<internal<>>;
		nik_ce auto i = MD::initial_index;

		return NIK_BEGIN_MACHINE(d, m, c, i, u), m, prog, i, Vs... NIK_END_MACHINE(H0, H1, ch, As...);
	}
*/

// start:

/*
	template<auto d, auto prog, auto... Vs, typename CHeap, typename... Args>
	nik_ce auto start(CHeap ch, Args... As) { return general_start<d, prog, Vs...>(U_null_Vs, U_null_Vs, ch, As...); }
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// instructions:

/***********************************************************************************************************************/

// overload:

		// reverse order for user friendliness:

	template<key_type key, key_type act, key_type ctn = _h1, depth_type dec = _two>
	nik_ce instr_type action = instruction<MN::call, MT::action, dec, ctn, key, act>;

		template<key_type act, key_type ctn = _h1, depth_type dec = _two>
		nik_ce instr_type f_action = action<Overload::function, act, ctn, dec>;

		template<key_type act, key_type ctn = _h1, depth_type dec = _two>
		nik_ce instr_type h_action = action<Overload::higher_order, act, ctn, dec>;

		template<key_type act, key_type ctn = _h1, depth_type dec = _two>
		nik_ce instr_type a_action = action<Overload::alias, act, ctn, dec>;

	// function:

		// comparison:

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto equal = f_action<Operator::equal, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto not_equal = f_action<Operator::not_equal, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto less_than = f_action<Operator::less_than, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto less_than_or_equal = f_action<Operator::less_than_or_equal, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto greater_than = f_action<Operator::greater_than, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto greater_than_or_equal = f_action<Operator::greater_than_or_equal, ctn, dec>;

		// logical:

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto not_ = f_action<Operator::not_, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto and_ = f_action<Operator::and_, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto or_ = f_action<Operator::or_, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto implies = f_action<Operator::implies, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto equivalent = f_action<Operator::equivalent, ctn, dec>;

		// arithmetic:

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto add = f_action<Operator::add, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto subtract = f_action<Operator::subtract, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto multiply = f_action<Operator::multiply, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto divide = f_action<Operator::divide, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto modulo = f_action<Operator::modulo, ctn, dec>;

		// bitwise:

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto upshift = f_action<Operator::upshift, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto downshift = f_action<Operator::downshift, ctn, dec>;

		// algebraic:

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto product = f_action<Operator::tuple, ctn, dec>;

	// higher order:

		// computational:

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto apply = h_action<Operator::apply, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _three>
		nik_ce auto bind = h_action<Operator::bind, ctn, dec>;

			// comparison:

			template<key_type ctn = _h1, depth_type dec = _two>
			nik_ce auto is_equal = h_action<Operator::is_equal, ctn, dec>;

			template<key_type ctn = _h1, depth_type dec = _two>
			nik_ce auto is_zero = h_action<Operator::is_zero, ctn, dec>;

			// arithmetic:

			template<key_type ctn = _h1, depth_type dec = _two>
			nik_ce auto increment = h_action<Operator::increment, ctn, dec>;

			template<key_type ctn = _h1, depth_type dec = _two>
			nik_ce auto decrement = h_action<Operator::decrement, ctn, dec>;

	// alias:

		// basis:

		// comparison:

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto same = a_action<Operator::same, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto csame = a_action<Operator::csame, ctn, dec>;

		// functional:

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto length = a_action<Operator::length, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto map = a_action<Operator::map, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto zip = a_action<Operator::zip, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto is_null = a_action<Operator::is_null, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto car = a_action<Operator::car, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto cdr = a_action<Operator::cdr, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto cadr = a_action<Operator::cadr, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto unite = a_action<Operator::unite, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto find = a_action<Operator::find, ctn, dec>;

		// grammatical:

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto custom = a_action<Operator::custom, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto procedure = a_action<Operator::procedure, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto method = a_action<Operator::method, ctn, dec>;

		// unpack:

		template<key_type ctn = _h1, depth_type dec = _three>
		nik_ce auto unpack = a_action<Operator::unpack, ctn, dec>;

/***********************************************************************************************************************/

// machine:

	template<key_type ctn = _h1, depth_type dec = _two>
	nik_ce instr_type compel = instruction<MN::call, MT::compel, dec, ctn>;

	template<index_type pos, key_type loc, key_type ctn = _h0> // reverse order for user friendliness.
	nik_ce instr_type copy = instruction<MN::call, MI::copy_note(loc), pos, ctn>;

		template<index_type pos, key_type loc>
		nik_ce instr_type write = copy<pos, loc, _h0_write>;

		template<index_type pos, key_type loc>
		nik_ce instr_type value = copy<pos, loc, _value>;

	template<index_type pos, key_type loc> // reverse order for user friendliness.
	nik_ce instr_type cut = instruction<MN::call, MI::cut_note(loc), pos>;

	template<key_type...>
	nik_ce instr_type stage = instruction<MN::move_j_all, MT::id>;

	template<key_type loc>
	nik_ce instr_type paste = instruction<MI::paste_name(loc), MT::id>;

	template<key_type...>
	nik_ce instr_type cycle = instruction<MN::go_to, MT::id, _zero>;

	template<key_type pos>
	nik_ce instr_type branch = instruction<MN::go_to, MT::conditional, pos>;

	template<key_type pos>
	nik_ce instr_type mem_lookup = instruction<MN::memoize, MT::lookup, pos>;

	template<key_type...>
	nik_ce instr_type mem_insert = instruction<MN::memoize, MT::insert>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

