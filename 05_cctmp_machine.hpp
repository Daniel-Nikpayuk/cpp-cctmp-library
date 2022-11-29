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
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.

			call        , recall      ,
			paste_r_all , paste_a_all ,
			stage       , jump        , memoize ,
			halt
		};
	};

	using MN = InstrName;

/***********************************************************************************************************************/

// notes:

	struct InstrNote
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.

			start      ,
			copy_r_pos , copy_j_pos , copy_c_pos , copy_a_pos , copy ,
			cut_r_pos  , cut_a_pos  , cut        ,
			action     , compel     , propel     ,
			go_to      , branch     , lookup     , insert     ,
			pause      , debug
		};
	};

	using MT = InstrNote;

/***********************************************************************************************************************/

// locations:

	struct InstrLocs
	{
		using type = gcindex_type* const;

		enum Position : gkey_type
		{
			size = 0,
			name , note      ,
			pos  , dec = pos , mov = pos ,
			ctn  , syn       , key       , act
		};

		// locations:

		enum Location : gkey_type
		{
			_register = 0,
			_junction , _constant , _argument
		};

		// actions:

		enum Action : gkey_type
		{
			h0 = 0,
			h0_write , h1 , h1_pair , value // h1_pair is C++17 specific.
		};

		// stages:

		enum Stage : gkey_type
		{
			first = 0,
			all
		};

		nik_ces gindex_type length     (type i)         { return i[size]; }
		nik_ces bool        is_optimal (gcindex_type n) { return (n < _eight); }

		nik_ces auto copy_note(gckey_type l)
		{
			if      (l == _register) return MT::copy_r_pos;
			else if (l == _junction) return MT::copy_j_pos;
			else if (l == _constant) return MT::copy_c_pos;
			else                     return MT::copy_a_pos;
		}

		nik_ces auto cut_note(gckey_type l)
		{
			if   (l == _register) return MT::cut_r_pos;
			else                  return MT::cut_a_pos;
		}

		nik_ces auto paste_name(gckey_type l)
		{
			if   (l == _register) return MN::paste_r_all;
			else                  return MN::paste_a_all;
		}
	};

	using MI			= InstrLocs;
	using instr_type		= typename MI::type;
	using cinstr_type		= instr_type const;

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

	template<auto... Vs>
	nik_ce instr_type instruction = array<gindex_type, sizeof...(Vs), (gindex_type) Vs...>;

/***********************************************************************************************************************/

// controllers:

	struct InstrContr
	{
		using type = cinstr_type* const;

		enum Position : gkey_type
		{
			size = 0
		};

		nik_ces gindex_type length (type l) { return l[size][MI::size]; }
	};

	using MC		= InstrContr;
	using contr_type	= typename MC::type;

	template<auto... Vs>
	nik_ce contr_type controller = array<instr_type, array<gindex_type, sizeof...(Vs)>, Vs...>;

/***********************************************************************************************************************/

// dispatch:

	struct InstrDisp
	{
		// defaults:

			nik_ces gdepth_type initial_depth = 500;
			nik_ces gindex_type initial_index = _zero;

		// accessors:

			nik_ces auto instr(contr_type c, gcindex_type i)
				{ return c[i]; }

		// navigators:

			nik_ces gkey_type next_name(gcdepth_type d, gckey_type m, contr_type c, gcindex_type i)
			{
				if (d == 0)           return MN::halt;
				else if (m != MT::id) return MN::recall;
				else                  return c[i+1][MI::name];
			}

			nik_ces gkey_type next_note(gcdepth_type d, gckey_type m, contr_type c, gcindex_type i)
			{
				if (d == 0)           return MT::pause;
				else if (m != MT::id) return m;
				else                  return c[i+1][MI::note];
			}

			nik_ces gdepth_type next_depth(gcdepth_type d)
				{ return d - bool{d != 0}; }

			nik_ces gindex_type next_index(gcdepth_type d, gckey_type m, contr_type, gcindex_type i)
				{ return i + bool{d != 0 && m == MT::id}; }
	};

	using MD = InstrDisp;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// machine:

	// Arbitrary list_id input for greater utility,
	// U_pack_Vs for internal output for greater generality.

	template<gkey_type, gkey_type, auto...> struct T_machine;

	template<auto Name, auto Note, auto... Vs>
	nik_ce auto U_machine = U_store_T<T_machine<Name, Note, Vs...>>;

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
	nik_ce auto U_machine_start	= U_machine<MN::call, MT::start>;

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
				nik_ce auto h0 = listload_<_unite_, v0, v1, X0>;

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
				nik_ce auto h0 = listload_<_unite_, v0, v1, X0>;

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
				nik_ce auto h0 = listload_<_unite_, v0, v1, X0>;

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
				nik_ce auto syn = ins[MI::syn];
				nik_ce auto key = ins[MI::key];
				nik_ce auto act = ins[MI::act];
				nik_ce auto val = eval<U_grammar<syn, key, act>, Ws...>;

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
				nik_ce auto syn = ins[MI::syn];
				nik_ce auto key	= ins[MI::key];
				nik_ce auto act	= ins[MI::act];
				nik_ce auto val = eval<U_grammar<syn, key, act>, Ws...>;

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
				nik_ce auto syn = ins[MI::syn];
				nik_ce auto key = ins[MI::key];
				nik_ce auto act = ins[MI::act];
				nik_ce auto nd	= d+1-n;
				nik_ce auto val = eval<U_grammar<syn, key, act>, nd, Ws...>;

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
				nik_ce auto syn = ins[MI::syn];
				nik_ce auto key = ins[MI::key];
				nik_ce auto act = ins[MI::act];
				nik_ce auto nd	= d+1-n;
				nik_ce auto val = eval<U_grammar<syn, key, act>, nd, Ws...>;

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

// jump:

/***********************************************************************************************************************/

// go to:

	template<auto... filler>
	struct T_machine<MN::jump, MT::go_to, filler...>
	{
		template<NIK_CONTR_PARAMS, auto... Vs, typename... Heaps>
		nik_ces auto result(Heaps... Hs)
		{
			nik_ce auto ins	= MD::instr(c, i);
			nik_ce auto ni	= ins[MI::pos];

			return NIK_MACHINE(d, MT::id, c, ni, Vs)(Hs...);
		}
	};

// branch:

	template<auto... filler>
	struct T_machine<MN::jump, MT::branch, filler...>
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
			nik_ces auto result = eval<_same_, W, unpack_<Z, _car_>>;

		}; nik_ces auto _same_car_ = U_custom_T<T_same_car>;

		template
		<
			NIK_CONTR_PARAMS, auto... Vs, template<auto...> typename B0, auto W0,
			template<auto...> typename B1, auto... Xs, typename Heap2,
			template<auto...> typename B3, auto... Zs, typename... Args
		>
		nik_ces auto result(nik_vp(H0)(B0<W0>*), nik_vp(H1)(B1<Xs...>*), Heap2 H2, nik_vp(A0)(B3<Zs...>*), Args... As)
		{
			nik_ce auto size = sizeof...(Zs);
			nik_ce auto pos	 = find_<_alias_<_same_car_, W0>, Zs...>;

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

			return eval<_to_tuple_, a0, X0>;
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// halt:

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
			nik_ce auto cs = eval<_to_tuple_, d, m, c, i>;
			nik_ce auto rs = eval<_to_tuple_, Vs...>;
			nik_ce auto hs = eval<_to_tuple_, U_restore_T<Heaps>...>;

			return eval<_to_tuple_, cs, rs, hs>;
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// syntactic sugar:

/***********************************************************************************************************************/

// action:

		// reverse order for user friendliness:

	template<auto syn, auto key, auto act, gkey_type ctn = _h1, gdepth_type dec = _two>
	nik_ce instr_type action = instruction<MN::call, MT::action, dec, ctn, syn, key, act>;

		template<auto key, auto act, gkey_type ctn = _h1, gdepth_type dec = _two>
		nik_ce instr_type arg_action = action<Shape::argument, key, act, ctn, dec>;

		template<auto key, auto act, gkey_type ctn = _h1, gdepth_type dec = _two>
		nik_ce instr_type par_action = action<Shape::parameter, key, act, ctn, dec>;

	// overload:

		template<auto act, gkey_type ctn = _h1, gdepth_type dec = _two>
		nik_ce instr_type overload_arg_action = arg_action<Pattern::overload, act, ctn, dec>;

		// comparison:

			template<gkey_type ctn = _h1, gdepth_type dec = _two>
			nik_ce auto equal = overload_arg_action<Overload::equal, ctn, dec>;

			template<gkey_type ctn = _h1, gdepth_type dec = _two>
			nik_ce auto not_equal = overload_arg_action<Overload::not_equal, ctn, dec>;

			template<gkey_type ctn = _h1, gdepth_type dec = _two>
			nik_ce auto less_than = overload_arg_action<Overload::less_than, ctn, dec>;

			template<gkey_type ctn = _h1, gdepth_type dec = _two>
			nik_ce auto less_than_or_equal = overload_arg_action<Overload::less_than_or_equal, ctn, dec>;

			template<gkey_type ctn = _h1, gdepth_type dec = _two>
			nik_ce auto greater_than = overload_arg_action<Overload::greater_than, ctn, dec>;

			template<gkey_type ctn = _h1, gdepth_type dec = _two>
			nik_ce auto greater_than_or_equal = overload_arg_action<Overload::greater_than_or_equal, ctn, dec>;

		// logical:

			template<gkey_type ctn = _h1, gdepth_type dec = _two>
			nik_ce auto not_ = overload_arg_action<Overload::not_, ctn, dec>;

			template<gkey_type ctn = _h1, gdepth_type dec = _two>
			nik_ce auto and_ = overload_arg_action<Overload::and_, ctn, dec>;

			template<gkey_type ctn = _h1, gdepth_type dec = _two>
			nik_ce auto or_ = overload_arg_action<Overload::or_, ctn, dec>;

			template<gkey_type ctn = _h1, gdepth_type dec = _two>
			nik_ce auto implies = overload_arg_action<Overload::implies, ctn, dec>;

			template<gkey_type ctn = _h1, gdepth_type dec = _two>
			nik_ce auto equivalent = overload_arg_action<Overload::equivalent, ctn, dec>;

		// arithmetic:

			template<gkey_type ctn = _h1, gdepth_type dec = _two>
			nik_ce auto add = overload_arg_action<Overload::add, ctn, dec>;

			template<gkey_type ctn = _h1, gdepth_type dec = _two>
			nik_ce auto subtract = overload_arg_action<Overload::subtract, ctn, dec>;

			template<gkey_type ctn = _h1, gdepth_type dec = _two>
			nik_ce auto multiply = overload_arg_action<Overload::multiply, ctn, dec>;

			template<gkey_type ctn = _h1, gdepth_type dec = _two>
			nik_ce auto divide = overload_arg_action<Overload::divide, ctn, dec>;

			template<gkey_type ctn = _h1, gdepth_type dec = _two>
			nik_ce auto modulo = overload_arg_action<Overload::modulo, ctn, dec>;

		// bitwise:

			template<gkey_type ctn = _h1, gdepth_type dec = _two>
			nik_ce auto upshift = overload_arg_action<Overload::upshift, ctn, dec>;

			template<gkey_type ctn = _h1, gdepth_type dec = _two>
			nik_ce auto downshift = overload_arg_action<Overload::downshift, ctn, dec>;

	// abstract:

		template<auto act, gkey_type ctn = _h1, gdepth_type dec = _two>
		nik_ce instr_type abstract_par_action = par_action<Pattern::abstract, act, ctn, dec>;

		// comparison:

			template<gkey_type ctn = _h1, gdepth_type dec = _two>
			nik_ce auto same = abstract_par_action<Abstract::same, ctn, dec>;

		// variadic:

			template<gkey_type ctn = _h1, gdepth_type dec = _two>
			nik_ce auto is_null = abstract_par_action<Abstract::is_null, ctn, dec>;

			template<gkey_type ctn = _h1, gdepth_type dec = _two>
			nik_ce auto length = abstract_par_action<Abstract::length, ctn, dec>;

			template<gkey_type ctn = _h1, gdepth_type dec = _two>
			nik_ce auto car = abstract_par_action<Abstract::car, ctn, dec>;

			template<gkey_type ctn = _h1, gdepth_type dec = _two>
			nik_ce auto cadr = abstract_par_action<Abstract::cadr, ctn, dec>;

			template<gkey_type ctn = _h1, gdepth_type dec = _two>
			nik_ce auto find = abstract_par_action<Abstract::find, ctn, dec>;

	// access:

		template<auto act, gkey_type ctn = _h1, gdepth_type dec = _two>
		nik_ce instr_type access_par_action = par_action<Pattern::access, act, ctn, dec>;

		// basis:

			template<gkey_type ctn = _h1, gdepth_type dec = _two>
			nik_ce auto to_const = access_par_action<Access::to_const, ctn, dec>;

		// comparison:

			template<gkey_type ctn = _h1, gdepth_type dec = _two>
			nik_ce auto csame = access_par_action<Access::csame, ctn, dec>;

	// list:

		template<auto act, gkey_type ctn = _h1, gdepth_type dec = _two>
		nik_ce instr_type list_par_action = par_action<Pattern::list, act, ctn, dec>;

		// basis:

			template<gkey_type ctn = _h1, gdepth_type dec = _two>
			nik_ce auto name = list_par_action<List::name, ctn, dec>;

		// comparison:

			template<gkey_type ctn = _h1, gdepth_type dec = _two>
			nik_ce auto similar = list_par_action<List::similar, ctn, dec>;

		// variadic:

			template<gkey_type ctn = _h1, gdepth_type dec = _two>
			nik_ce auto to_list = list_par_action<List::to_list, ctn, dec>;

			template<gkey_type ctn = _h1, gdepth_type dec = _three>
			nik_ce auto f0_unpack = list_par_action<List::f0_unpack, ctn, dec>;

			template<gkey_type ctn = _h1, gdepth_type dec = _three>
			nik_ce auto f1_unpack = list_par_action<List::f1_unpack, ctn, dec>;

			template<gkey_type ctn = _h1, gdepth_type dec = _three>
			nik_ce auto f2_unpack = list_par_action<List::f2_unpack, ctn, dec>;

			template<gkey_type ctn = _h1, gdepth_type dec = _three>
			nik_ce auto b0_unpack = list_par_action<List::b0_unpack, ctn, dec>;

				template<gkey_type ctn = _h1, gdepth_type dec = _three>
				nik_ce auto unpack = b0_unpack<ctn, dec>;

			template<gkey_type ctn = _h1, gdepth_type dec = _three>
			nik_ce auto b1_unpack = list_par_action<List::b1_unpack, ctn, dec>;

			template<gkey_type ctn = _h1, gdepth_type dec = _three>
			nik_ce auto b2_unpack = list_par_action<List::b2_unpack, ctn, dec>;

			template<gkey_type ctn = _h1, gdepth_type dec = _two>
			nik_ce auto rename = list_par_action<List::rename, ctn, dec>;

		// functional:

			template<gkey_type ctn = _h1, gdepth_type dec = _two>
			nik_ce auto cdr = list_par_action<List::cdr, ctn, dec>;

			template<gkey_type ctn = _h1, gdepth_type dec = _two>
			nik_ce auto map = list_par_action<List::map, ctn, dec>;

			template<gkey_type ctn = _h1, gdepth_type dec = _two>
			nik_ce auto zip = list_par_action<List::zip, ctn, dec>;

			template<gkey_type ctn = _h1, gdepth_type dec = _two>
			nik_ce auto unite = list_par_action<List::unite, ctn, dec>;

			template<gkey_type ctn = _h1, gdepth_type dec = _two>
			nik_ce auto cons = list_par_action<List::cons, ctn, dec>;

			template<gkey_type ctn = _h1, gdepth_type dec = _two>
			nik_ce auto push = list_par_action<List::push, ctn, dec>;

	// boolean:

		template<auto act, gkey_type ctn = _h1, gdepth_type dec = _two>
		nik_ce instr_type boolean_par_action = par_action<Pattern::boolean, act, ctn, dec>;

		// basis:

			template<gkey_type ctn = _h1, gdepth_type dec = _two>
			nik_ce auto if_then_else = boolean_par_action<Boolean::if_then_else, ctn, dec>;

	// number:

		template<auto act, gkey_type ctn = _h1, gdepth_type dec = _two>
		nik_ce instr_type number_par_action = par_action<Pattern::number, act, ctn, dec>;

		// basis:

			template<gkey_type ctn = _h1, gdepth_type dec = _two>
			nik_ce auto is_unsigned = number_par_action<Number::is_unsigned, ctn, dec>;

			template<gkey_type ctn = _h1, gdepth_type dec = _two>
			nik_ce auto not_unsigned = number_par_action<Number::not_unsigned, ctn, dec>;

			template<gkey_type ctn = _h1, gdepth_type dec = _two>
			nik_ce auto is_signed = number_par_action<Number::is_signed, ctn, dec>;

			template<gkey_type ctn = _h1, gdepth_type dec = _two>
			nik_ce auto not_signed = number_par_action<Number::not_signed, ctn, dec>;

	// pointer:

		// basis:

	// reference:

		// basis:

	// array:

		template<auto act, gkey_type ctn = _h1, gdepth_type dec = _two>
		nik_ce instr_type array_par_action = par_action<Pattern::array, act, ctn, dec>;

		// meta:

		// basis:

			template<gkey_type ctn = _h1, gdepth_type dec = _two>
			nik_ce auto to_array = array_par_action<Array::to_array, ctn, dec>;

	// function:

		template<auto act, gkey_type ctn = _h1, gdepth_type dec = _two>
		nik_ce instr_type function_par_action = par_action<Pattern::function, act, ctn, dec>;

		// meta:

		// call:

			template<gkey_type ctn = _h1, gdepth_type dec = _two>
			nik_ce auto custom = function_par_action<Function::custom, ctn, dec>;

			template<gkey_type ctn = _h1, gdepth_type dec = _two>
			nik_ce auto nested = function_par_action<Function::nested, ctn, dec>;

			template<gkey_type ctn = _h1, gdepth_type dec = _two>
			nik_ce auto procedure = function_par_action<Function::procedure, ctn, dec>;

			template<gkey_type ctn = _h1, gdepth_type dec = _two>
			nik_ce auto method = function_par_action<Function::method, ctn, dec>;

			template<gkey_type ctn = _h1, gdepth_type dec = _two>
			nik_ce auto tailor = function_par_action<Function::tailor, ctn, dec>;

	// sequence:

		template<auto act, gkey_type ctn = _h1, gdepth_type dec = _two>
		nik_ce instr_type sequence_arg_action = arg_action<Pattern::sequence, act, ctn, dec>;

		// meta:

		// basis:

	// tuple:

		template<auto act, gkey_type ctn = _h1, gdepth_type dec = _two>
		nik_ce instr_type tuple_arg_action = arg_action<Pattern::tuple, act, ctn, dec>;

		// meta:

		// basis:

	// identity:

		template<auto act, gkey_type ctn = _h1, gdepth_type dec = _two>
		nik_ce instr_type identity_par_action = par_action<Pattern::identity, act, ctn, dec>;

		// list to:

			template<gkey_type ctn = _h1, gdepth_type dec = _two>
			nik_ce auto list_to_array = identity_par_action<Identity::list_to_array, ctn, dec>;

		// array to:

			template<gkey_type ctn = _h1, gdepth_type dec = _two>
			nik_ce auto array_to_list = identity_par_action<Identity::array_to_list, ctn, dec>;

/***********************************************************************************************************************/

// compel:

	template<auto act, gkey_type ctn = _h1, gdepth_type dec = _two>
	nik_ce instr_type compel = instruction<MN::call, MT::compel, dec, ctn, Shape::parameter, Pattern::function, act>;

		nik_ce auto _custom = Function::custom;
		nik_ce auto _nested = Function::nested;
		nik_ce auto _method = Function::method;

/***********************************************************************************************************************/

// machine:

	template<gindex_type pos, gkey_type loc, gkey_type ctn = _h0> // reverse order for user friendliness.
	nik_ce instr_type copy = instruction<MN::call, MI::copy_note(loc), pos, ctn>;

		template<gindex_type pos, gkey_type loc>
		nik_ce instr_type write = copy<pos, loc, _h0_write>;

		template<gindex_type pos, gkey_type loc>
		nik_ce instr_type value = copy<pos, loc, _value>;

	template<gindex_type pos, gkey_type loc> // reverse order for user friendliness.
	nik_ce instr_type cut = instruction<MN::call, MI::cut_note(loc), pos>;

	template<gkey_type loc>
	nik_ce instr_type paste = instruction<MI::paste_name(loc), MT::id>;

	template<gkey_type mov = _first>
	nik_ce instr_type stage = instruction<MN::stage, MT::id, mov>;

	template<gkey_type...>
	nik_ce instr_type cycle = instruction<MN::jump, MT::go_to, _zero>;

	template<gkey_type pos>
	nik_ce instr_type branch = instruction<MN::jump, MT::branch, pos>;

	template<gkey_type pos>
	nik_ce instr_type mem_lookup = instruction<MN::memoize, MT::lookup, pos>;

	template<gkey_type...>
	nik_ce instr_type mem_insert = instruction<MN::memoize, MT::insert>;

/***********************************************************************************************************************/

// debugging:

	template<gkey_type...>
	nik_ce instr_type debug = instruction<MN::halt, MT::debug>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

