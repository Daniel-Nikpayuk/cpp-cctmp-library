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

		nik_ces key_type call				=  1;
		nik_ces key_type recall				=  2;

		nik_ces key_type paste_r_all			=  3;
		nik_ces key_type paste_a_all			=  4;

		nik_ces key_type stage				=  5;
		nik_ces key_type go_to				=  6;
		nik_ces key_type memoize			=  7;

		nik_ces key_type halt				=  8;
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

		nik_ces key_type conditional			= 13;
		nik_ces key_type lookup				= 14;
		nik_ces key_type insert				= 15;

		nik_ces key_type pause				= 16;
		nik_ces key_type debug				= 17;
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
		nik_ces key_type mov					= 3;

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

		// stages:

		nik_ces key_type first					= 0;
		nik_ces key_type all					= 1;

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

	nik_ce auto _first		= MI::first;
	nik_ce auto _all		= MI::all;

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

	// Arbitrary list_id input for greater utility,
	// U_pack_Vs for internal output for greater generality.

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
	nik_ce auto start = U_pack_Vs<Vs...>;

	template
	<
		auto d,
		template<auto...> typename B, auto... Hs, nik_vp(p)(B<Hs...>*),
		auto m, auto c, auto i, auto...Vs
	>
	nik_ce auto start<d, p, m, c, i, Vs...> = NIK_MACHINE(d, m, c, i, Vs)(Hs...);

	struct T_start
	{
		nik_ces auto m = MT::id;
		nik_ces auto i = MD::initial_index;

		template<auto d, auto c, auto... Vs, typename... Heaps>
		nik_ces auto result(Heaps... Hs) { return NIK_MACHINE(d, m, c, i, Vs)(Hs...); }

	}; nik_ce auto U_start = U_store_T<T_start>;

/***********************************************************************************************************************/

	template<auto... filler>
	struct T_machine<MN::call, MT::start, filler...>
	{
		template<auto d, auto p, auto m, auto c, auto i, auto...Vs>
		nik_ces auto result = start<d, p, m, c, i, Vs...>;
	};

	using T_machine_start		= T_machine<MN::call, MT::start>;
	nik_ce auto U_machine_start	= U_store_T<T_machine_start>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// copy:

/***********************************************************************************************************************/

// register:

	template<auto... filler>
	struct T_machine<MN::call, MT::copy_r_pos, filler...>
	{
		template<NIK_CONTR_PARAMS, auto... Vs, template<auto...> typename B0, auto... Ws, typename... Heaps>
		nik_ces auto result(nik_vp(H0)(B0<Ws...>*), Heaps... Hs)
		{
			nik_ce auto ins	= MD::instr(c, i);
			nik_ce auto n	= ins[MI::pos];
			nik_ce auto ctn	= ins[MI::ctn];
			nik_ce auto val	= NIK_VARIABLE_BLOCK(3, d, n, U_block_car, Vs);

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
		template
		<
			NIK_CONTR_PARAMS, auto... Vs, template<auto...> typename B0, auto... Ws,
			template<auto...> typename B1, auto... Xs, typename... Heaps
		>
		nik_ces auto result(nik_vp(H0)(B0<Ws...>*), nik_vp(H1)(B1<Xs...>*), Heaps... Hs)
		{
			nik_ce auto ins	= MD::instr(c, i);
			nik_ce auto n	= ins[MI::pos];
			nik_ce auto ctn	= ins[MI::ctn];
			nik_ce auto val	= NIK_VARIABLE_BLOCK(3, d, n, U_block_car, Xs);

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
		template
		<
			NIK_CONTR_PARAMS, auto... Vs, template<auto...> typename B0, auto... Ws,
			typename Heap1, template<auto...> typename B2, auto... Ys, typename... Args
		>
		nik_ces auto result(nik_vp(H0)(B0<Ws...>*), Heap1 H1, nik_vp(H2)(B2<Ys...>*), Args... As)
		{
			nik_ce auto ins	= MD::instr(c, i);
			nik_ce auto n	= ins[MI::pos];
			nik_ce auto ctn	= ins[MI::ctn];
			nik_ce auto val	= NIK_VARIABLE_BLOCK(3, d, n, U_block_car, Ys);

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
		template
		<
			NIK_CONTR_PARAMS, auto... Vs, template<auto...> typename B0, auto... Ws,
			typename Heap1, typename Heap2, typename... Args
		>
		nik_ces auto result(nik_vp(H0)(B0<Ws...>*), Heap1 H1, Heap2 H2, Args... As)
		{
			nik_ce auto ins	= MD::instr(c, i);
			nik_ce auto n	= ins[MI::pos];
			nik_ce auto ctn	= ins[MI::ctn];
			nik_ce auto val	= NIK_VARIABLE_BLOCK(3, d, n, U_block_car, U_restore_T<Args>);

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
			NIK_CONTR_PARAMS, auto... Vs, template<auto...> typename B, auto n, auto rtn, auto... _Vs,
			template<auto...> typename B0, auto... Ws, typename... Heaps
		>
		nik_ces auto result(nik_avp(B<n, rtn, _Vs...>*), nik_vp(H0)(B0<Ws...>*), Heaps... Hs)
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
		template
		<
			NIK_CONTR_PARAMS, auto... Vs, typename Heap0,
			template<auto...> typename B1, auto X0, auto... Xs, typename... Heaps
		>
		nik_ces auto result(Heap0 H0, nik_vp(H1)(B1<X0, Xs...>*), Heaps... Hs)
		{
			nik_ce auto ins	= MD::instr(c, i);
			nik_ce auto n	= ins[MI::pos];
			nik_ce auto val	= NIK_FUNCTION_BLOCK(3, d, n, U_block_cut<>, Vs)(U_null_Vs);

			if nik_ce (is_machination<decltype(val)>)

				return NIK_MACHINE(d, MT::cut, c, i, Vs)(val.p, H0, H1, Hs...);
			else
			{
				nik_ce auto v0 = tuple_value<0>(val);
				nik_ce auto v1 = tuple_value<1>(val);
				nik_ce auto h0 = listload_<Alias::unite, v0, v1, X0>;

				return NIK_MACHINE(d, MT::id, c, i, Vs)(h0, U_pack_Vs<Xs...>, Hs...);
			}
		}
	};

/***********************************************************************************************************************/

// argument:

	template<auto... filler>
	struct T_machine<MN::call, MT::cut_a_pos, filler...>
	{
		template
		<
			NIK_CONTR_PARAMS, auto... Vs, typename Heap0,
			template<auto...> typename B1, auto X0, auto... Xs, typename Heap2, typename... Args
		>
		nik_ces auto result(Heap0 H0, nik_vp(H1)(B1<X0, Xs...>*), Heap2 H2, Args... As)
		{
			nik_ce auto ins	= MD::instr(c, i);
			nik_ce auto n	= ins[MI::pos];
			nik_ce auto val	= NIK_FUNCTION_BLOCK(3, d, n, U_block_cut<>, U_restore_T<Args>)(U_null_Vs);

			if nik_ce (is_machination<decltype(val)>)

				return NIK_MACHINE(d, MT::cut, c, i, Vs)(val.p, H0, H1, H2, As...);
			else
			{
				nik_ce auto v0 = tuple_value<0>(val);
				nik_ce auto v1 = tuple_value<1>(val);
				nik_ce auto h0 = listload_<Alias::unite, v0, v1, X0>;

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
			template<auto...> typename B, auto p, auto n, auto rtn, auto... _Vs,
			typename Heap0, template<auto...> typename B1, auto X0, auto... Xs, typename... Heaps
		>
		nik_ces auto result(nik_avp(B<p, n, rtn, _Vs...>*), Heap0 H0, nik_vp(H1)(B1<X0, Xs...>*), Heaps... Hs)
		{
			nik_ce auto val = T_block_function::template result<d, p, n, rtn, _Vs...>;

			if nik_ce (is_machination<decltype(val)>)

				return NIK_MACHINE(d, MT::cut, c, i, Vs)(val.p, H0, H1, Hs...);
			else
			{
				nik_ce auto v0 = tuple_value<0>(val);
				nik_ce auto v1 = tuple_value<1>(val);
				nik_ce auto h0 = listload_<Alias::unite, v0, v1, X0>;

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
		template
		<
			NIK_CONTR_PARAMS, auto... Vs, template<auto...> typename B0, auto... Ws,
			template<auto...> typename B1, auto... Xs, typename... Heaps
		>
		nik_ces auto result(nik_vp(H0)(B0<Ws...>*), nik_vp(H1)(B1<Xs...>*), Heaps... Hs)
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
				nik_ce auto val = overload<U_grammar<key, act>, Ws...>;

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
		template
		<
			NIK_CONTR_PARAMS, auto... Vs, template<auto...> typename B0, auto... Ws,
			template<auto...> typename B1, auto... Xs, typename... Heaps
		>
		nik_ces auto result(nik_vp(H0)(B0<Ws...>*), nik_vp(H1)(B1<Xs...>*), Heaps... Hs)
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
				nik_ce auto val = overload<U_grammar<key, act>, Ws...>;

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
		template
		<
			NIK_CONTR_PARAMS, auto... Vs, template<auto...> typename B0, auto... Ws,
			template<auto...> typename B1, auto... Xs, typename... Heaps
		>
		nik_ces auto result(nik_vp(H0)(B0<Ws...>*), nik_vp(H1)(B1<Xs...>*), Heaps... Hs)
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
				nik_ce auto val = overload<U_grammar<key, act>, nd, Ws...>;

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
		template
		<
			NIK_CONTR_PARAMS, auto... Vs, template<auto...> typename B0, auto... Ws,
			template<auto...> typename B1, auto... Xs, typename... Heaps
		>
		nik_ces auto result(nik_vp(H0)(B0<Ws...>*), nik_vp(H1)(B1<Xs...>*), Heaps... Hs)
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
				nik_ce auto val = overload<U_grammar<key, act>, nd, Ws...>;

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
		template
		<
			NIK_CONTR_PARAMS, auto... Vs, typename _U, template<auto...> typename B, auto... _Ws,
			template<auto...> typename B1, auto... Xs, typename... Heaps
		>
		nik_ces auto result(_U, nik_avp(B<_Ws...>*), nik_vp(H1)(B1<Xs...>*), Heaps... Hs)
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

// paste:

/***********************************************************************************************************************/

// register:

	template<auto... filler>
	struct T_machine<MN::paste_r_all, MT::id, filler...>
	{
		template<NIK_CONTR_PARAMS, auto... Vs, template<auto...> typename B0, auto... Ws, typename... Heaps>
		nik_ces auto result(nik_vp(H0)(B0<Ws...>*), Heaps... Hs)
		{
			return NIK_MACHINE(d, MT::id, c, i, Ws)(U_null_Vs, Hs...);
		}
	};

// argument:

	template<auto... filler>
	struct T_machine<MN::paste_a_all, MT::id, filler...>
	{
		template
		<
			NIK_CONTR_PARAMS, auto... Vs, template<auto...> typename B0, auto... Ws,
			typename Heap1, typename Heap2, typename... Args
		>
		nik_ces auto result(nik_vp(H0)(B0<Ws...>*), Heap1 H1, Heap2 H2, Args... As)
		{
			return NIK_MACHINE(d, MT::id, c, i, Vs)(U_null_Vs, H1, H2, Ws...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// stage:

/***********************************************************************************************************************/

// id:

	template<auto... filler>
	struct T_machine<MN::stage, MT::id, filler...>
	{
		template
		<
			NIK_CONTR_PARAMS, auto... Vs, template<auto...> typename B0, auto... Ws,
			template<auto...> typename B1, auto X0, auto... Xs, typename... Heaps
		>
		nik_ces auto result(nik_vp(H0)(B0<Ws...>*), nik_vp(H1)(B1<X0, Xs...>*), Heaps... Hs)
		{
			nik_ce auto ins	= MD::instr(c, i);
			nik_ce auto mov = ins[MI::mov];

			if nik_ce (mov == MI::first)

				return NIK_MACHINE(d, MT::id, c, i, Vs)(U_pack_Vs<Ws..., X0>, U_pack_Vs<Xs...>, Hs...);
			else
				return NIK_MACHINE(d, MT::id, c, i, Vs)(U_pack_Vs<Ws..., X0, Xs...>, U_null_Vs, Hs...);
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
		template
		<
			NIK_CONTR_PARAMS, auto... Vs, typename Heap0,
			template<auto...> typename B1, bool X0, auto... Xs, typename... Heaps
		>
		nik_ces auto result(Heap0 H0, nik_vp(H1)(B1<X0, Xs...>*), Heaps... Hs)
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
			nik_ces auto result = overload<Alias::same, W, unpack_<Z, Alias::car>>;

		}; nik_ces auto U_same_car = U_store_T<T_same_car>;

		template
		<
			NIK_CONTR_PARAMS, auto... Vs, template<auto...> typename B0, auto W0,
			template<auto...> typename B1, auto... Xs, typename Heap2,
			template<auto...> typename B3, auto... Zs, typename... Args
		>
		nik_ces auto result(nik_vp(H0)(B0<W0>*), nik_vp(H1)(B1<Xs...>*), Heap2 H2, nik_vp(A0)(B3<Zs...>*), Args... As)
		{
			nik_ce auto size = sizeof...(Zs);
			nik_ce auto pos	 = find_<U_alias<U_same_car, W0>, Zs...>;

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
			NIK_CONTR_PARAMS, auto... Vs, template<auto...> typename B0, auto W0,
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

			return overload<Alias::to_tuple, a0, X0>;
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

			return machination(U_machine_start, U_pack_Vs<p, m, c, i, Vs...>);
		}
	};

/***********************************************************************************************************************/

// debug:

	template<auto... filler>
	struct T_machine<MN::halt, MT::debug, filler...>
	{
		template<NIK_CONTR_PARAMS, auto... Vs, typename... Heaps>
		nik_ces auto result(Heaps... Hs)
		{
			nik_ce auto cs = overload<Alias::to_tuple, d, m, c, i>;
			nik_ce auto rs = overload<Alias::to_tuple, Vs...>;
			nik_ce auto hs = overload<Alias::to_tuple, U_restore_T<Heaps>...>;

			return overload<Alias::to_tuple, cs, rs, hs>;
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// syntactic sugar:

/***********************************************************************************************************************/

// action:

		// reverse order for user friendliness:

	template<key_type key, key_type act, key_type ctn = _h1, depth_type dec = _two>
	nik_ce instr_type action = instruction<MN::call, MT::action, dec, ctn, key, act>;

		template<key_type act, key_type ctn = _h1, depth_type dec = _two>
		nik_ce instr_type f_action = action<Grammar::function, act, ctn, dec>;

		template<key_type act, key_type ctn = _h1, depth_type dec = _two>
		nik_ce instr_type h_action = action<Grammar::higher_order, act, ctn, dec>;

		template<key_type act, key_type ctn = _h1, depth_type dec = _two>
		nik_ce instr_type a_action = action<Grammar::alias, act, ctn, dec>;

	// function:

		// comparison:

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto equal = f_action<Function::equal, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto not_equal = f_action<Function::not_equal, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto less_than = f_action<Function::less_than, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto less_than_or_equal = f_action<Function::less_than_or_equal, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto greater_than = f_action<Function::greater_than, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto greater_than_or_equal = f_action<Function::greater_than_or_equal, ctn, dec>;

		// logical:

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto not_ = f_action<Function::not_, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto and_ = f_action<Function::and_, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto or_ = f_action<Function::or_, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto implies = f_action<Function::implies, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto equivalent = f_action<Function::equivalent, ctn, dec>;

		// arithmetic:

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto add = f_action<Function::add, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto subtract = f_action<Function::subtract, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto multiply = f_action<Function::multiply, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto divide = f_action<Function::divide, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto modulo = f_action<Function::modulo, ctn, dec>;

		// bitwise:

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto upshift = f_action<Function::upshift, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto downshift = f_action<Function::downshift, ctn, dec>;

		// algebraic:

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto product = f_action<Function::tuple, ctn, dec>;

	// higher order:

		// computational:

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto apply = h_action<HigherOrder::apply, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _three>
		nik_ce auto bind = h_action<HigherOrder::bind, ctn, dec>;

			// comparison:

			template<key_type ctn = _h1, depth_type dec = _two>
			nik_ce auto is_equal = h_action<HigherOrder::is_equal, ctn, dec>;

			template<key_type ctn = _h1, depth_type dec = _two>
			nik_ce auto is_zero = h_action<HigherOrder::is_zero, ctn, dec>;

			// arithmetic:

			template<key_type ctn = _h1, depth_type dec = _two>
			nik_ce auto increment = h_action<HigherOrder::increment, ctn, dec>;

			template<key_type ctn = _h1, depth_type dec = _two>
			nik_ce auto decrement = h_action<HigherOrder::decrement, ctn, dec>;

	// alias:

		// grammatical:

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto custom = a_action<Alias::custom, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto nested = a_action<Alias::nested, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto procedure = a_action<Alias::procedure, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto method = a_action<Alias::method, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto tailor = a_action<Alias::tailor, ctn, dec>;

		// basis:

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto type_to_const = a_action<Alias::type_to_const, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto if_then_else = a_action<Alias::if_then_else, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto list_id = a_action<Alias::list_id, ctn, dec>;

		// comparison:

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto same = a_action<Alias::same, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto csame = a_action<Alias::csame, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto similar = a_action<Alias::similar, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto is_int_type = a_action<Alias::is_int_type, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto not_int_type = a_action<Alias::not_int_type, ctn, dec>;

		// functional:

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto to_list = a_action<Alias::to_list, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto array_to_list = a_action<Alias::array_to_list, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto to_array = a_action<Alias::to_array, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto is_null = a_action<Alias::is_null, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto length = a_action<Alias::length, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto car = a_action<Alias::car, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto cdr = a_action<Alias::cdr, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto cadr = a_action<Alias::cadr, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto map = a_action<Alias::map, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto find = a_action<Alias::find, ctn, dec>;

		// variadic:

		template<key_type ctn = _h1, depth_type dec = _three>
		nik_ce auto f0_unpack = a_action<Alias::f0_unpack, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _three>
		nik_ce auto f1_unpack = a_action<Alias::f1_unpack, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _three>
		nik_ce auto f2_unpack = a_action<Alias::f2_unpack, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _three>
		nik_ce auto b0_unpack = a_action<Alias::b0_unpack, ctn, dec>;

			template<key_type ctn = _h1, depth_type dec = _three>
			nik_ce auto unpack = b0_unpack<ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _three>
		nik_ce auto b1_unpack = a_action<Alias::b1_unpack, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _three>
		nik_ce auto b2_unpack = a_action<Alias::b2_unpack, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto list_to_list = a_action<Alias::list_to_list, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto list_to_array = a_action<Alias::list_to_array, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto zip = a_action<Alias::zip, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto unite = a_action<Alias::unite, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto cons = a_action<Alias::cons, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto push = a_action<Alias::push, ctn, dec>;

/***********************************************************************************************************************/

// compel:

	template<key_type act, key_type ctn = _h1, depth_type dec = _two>
	nik_ce instr_type compel = instruction<MN::call, MT::compel, dec, ctn, Grammar::alias, act>;

		nik_ce auto _custom = Alias::custom;
		nik_ce auto _nested = Alias::nested;
		nik_ce auto _method = Alias::method;

/***********************************************************************************************************************/

// machine:

	template<index_type pos, key_type loc, key_type ctn = _h0> // reverse order for user friendliness.
	nik_ce instr_type copy = instruction<MN::call, MI::copy_note(loc), pos, ctn>;

		template<index_type pos, key_type loc>
		nik_ce instr_type write = copy<pos, loc, _h0_write>;

		template<index_type pos, key_type loc>
		nik_ce instr_type value = copy<pos, loc, _value>;

	template<index_type pos, key_type loc> // reverse order for user friendliness.
	nik_ce instr_type cut = instruction<MN::call, MI::cut_note(loc), pos>;

	template<key_type loc>
	nik_ce instr_type paste = instruction<MI::paste_name(loc), MT::id>;

	template<key_type mov = _first>
	nik_ce instr_type stage = instruction<MN::stage, MT::id, mov>;

	template<key_type...>
	nik_ce instr_type cycle = instruction<MN::go_to, MT::id, _zero>;

	template<key_type pos>
	nik_ce instr_type branch = instruction<MN::go_to, MT::conditional, pos>;

	template<key_type pos>
	nik_ce instr_type mem_lookup = instruction<MN::memoize, MT::lookup, pos>;

	template<key_type...>
	nik_ce instr_type mem_insert = instruction<MN::memoize, MT::insert>;

/***********************************************************************************************************************/

// debugging:

	template<key_type...>
	nik_ce instr_type debug = instruction<MN::halt, MT::debug>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

