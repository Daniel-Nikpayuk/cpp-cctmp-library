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
				nik_ce auto ins	= MachineDispatch::instr(c, i);
				nik_ce auto n	= ins[MI::dec];

				if nik_ce (n >= d) // analogous to returning a machination.

					return NIK_MACHINE(0, MT::action, c, i, Vs)(H0, H1, Hs...);
				else
				{
					nik_ce auto ctn = ins[MI::ctn];
					nik_ce auto key = ins[MI::key];
					nik_ce auto act = ins[MI::act];
					nik_ce auto val = Overload::template result<key, act, Ws...>;

					if nik_ce (ctn == MI::h1)

						return NIK_MACHINE(d, MT::id, c, i, Vs)
							(U_null_Vs, U_pack_Vs<val, Xs...>, Hs...);

					else if nik_ce (ctn == MI::h1_pair)

						return NIK_MACHINE(d, MT::id, c, i, Vs)
							(U_null_Vs, U_pack_Vs<val.v1, val.v2, Xs...>, Hs...);
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
				nik_ce auto ins	= MachineDispatch::instr(c, i);
				nik_ce auto n	= ins[MI::dec];

				if nik_ce (n >= d) // analogous to returning a machination.

					return NIK_MACHINE(0, MT::action, c, i, Vs)(H0, H1, Hs...);
				else
				{
					nik_ce auto ctn	= ins[MI::ctn];
					nik_ce auto key	= ins[MI::key];
					nik_ce auto act	= ins[MI::act];
					nik_ce auto val	= Overload::template result<key, act, Ws...>;

					if nik_ce (ctn == MI::h1)

						return NIK_MACHINE(d, MT::id, c, i, Vs)
							(U_null_Vs, U_pack_Vs<val, Xs...>, Hs...);

					else if nik_ce (ctn == MI::h1_pair)

						return NIK_MACHINE(d, MT::id, c, i, Vs)
							(U_null_Vs, U_pack_Vs<val.v1, val.v2, Xs...>, Hs...);
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
				nik_ce auto ins	= MachineDispatch::instr(c, i);
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
				nik_ce auto ins	= MachineDispatch::instr(c, i);
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
				nik_ce auto ins	= MachineDispatch::instr(c, i);
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
				nik_ce auto ins	= MachineDispatch::instr(c, i);
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
				nik_ce auto ins = MachineDispatch::instr(c, i);
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
				nik_ce auto ins	= MachineDispatch::instr(c, i);
				nik_ce auto n	= ins[MI::pos];
				nik_ce auto val	= NIK_FUNCTION_BLOCK(3, d, n, BN::filter, Vs)(U_null_Vs);

				if nik_ce (is_machination<decltype(val)>)

					return NIK_MACHINE(d, MT::cut, c, i, Vs)(val.s1, val.s2, H1, Hs...);
				else
				{
					nik_ce auto h0 = Overload::template result
					<
						Overload::alias, Operator::unite, val.v1, val.v2, X0
					>;

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
				nik_ce auto ins	= MachineDispatch::instr(c, i);
				nik_ce auto n	= ins[MI::pos];
				nik_ce auto val	= NIK_FUNCTION_BLOCK(3, d, n, BN::filter, U_restore_T<Args>)(U_null_Vs);

				if nik_ce (is_machination<decltype(val)>)

					return NIK_MACHINE(d, MT::cut, c, i, Vs)(val.s1, val.s2, H1, H2, As...);
				else
				{
					nik_ce auto h0 = Overload::template result
					<
						Overload::alias, Operator::unite, val.v1, val.v2, X0
					>;

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
					nik_ce auto h0 = Overload::template result
					<
						Overload::alias, Operator::unite, val.v1, val.v2, X0
					>;

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
				nik_ce auto ins	= MachineDispatch::instr(c, i);
				nik_ce auto rtn	= ins[MI::rtn];
				nik_ce auto ctn	= ins[MI::ctn];
				nik_ce auto val	= NIK_VARIABLE_BLOCK(9, d, n, rtn, Ws);

				if nik_ce (is_machination<decltype(val)>)

					return NIK_MACHINE(d, MT::variable, c, i, Vs)(val.s1, val.s2, H1, Hs...);

				else if nik_ce (ctn == MI::h1)

					return NIK_MACHINE(d, MT::id, c, i, Vs)
						(U_null_Vs, U_pack_Vs<val, Xs...>, Hs...);

				else if nik_ce (ctn == MI::h1_pair)

					return NIK_MACHINE(d, MT::id, c, i, Vs)
						(U_null_Vs, U_pack_Vs<val.v1, val.v2, Xs...>, Hs...);
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
				nik_ce auto ins = MachineDispatch::instr(c, i);
				nik_ce auto ctn = ins[MI::ctn];
				nik_ce auto val = NIK_VARIABLE_BLOCK(9, d, n, rtn, _Vs);

				if nik_ce (is_machination<decltype(val)>)

					return NIK_MACHINE(d, MT::variable, c, i, Vs)(val.s1, val.s2, H1, Hs...);

				else if nik_ce (ctn == MI::h1)

					return NIK_MACHINE(d, MT::id, c, i, Vs)(U_null_Vs, U_pack_Vs<val, Xs...>, Hs...);

				else if nik_ce (ctn == MI::h1_pair)

					return NIK_MACHINE(d, MT::id, c, i, Vs)
						(U_null_Vs, U_pack_Vs<val.v1, val.v2, Xs...>, Hs...);
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
				nik_ce auto ins	= MachineDispatch::instr(c, i);
				nik_ce auto rtn	= ins[MI::rtn];
				nik_ce auto ctn	= ins[MI::ctn];
				nik_ce auto val	= NIK_FUNCTION_BLOCK(9, d, n, rtn, Ws)(U_null_Vs);

				if nik_ce (is_machination<decltype(val)>)

					return NIK_MACHINE(d, MT::function, c, i, Vs)(val.s1, val.s2, H1, Hs...);

				else if nik_ce (ctn == MI::h1 || ctn == MI::h1_pair)

					return NIK_MACHINE(d, MT::id, c, i, Vs)
						(U_null_Vs, U_pack_Vs<val.v1, val.v2, Xs...>, Hs...);
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
				nik_ce auto ins	= MachineDispatch::instr(c, i);
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
				nik_ce auto _i	= MachineDispatch::initial_index;
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
				nik_ce auto ins	= MachineDispatch::instr(c, i);
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

						return NIK_MACHINE(d, MT::id, c, i, Vs)
							(U_null_Vs, U_pack_Vs<val.v1, val.v2, Xs...>, Hs...);
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
				nik_ce auto ins	= MachineDispatch::instr(c, i);
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

						return NIK_MACHINE(d, MT::id, c, i, Vs)
							(U_null_Vs, U_pack_Vs<val.v1, val.v2, Xs...>, Hs...);
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
				nik_ce auto ins = MachineDispatch::instr(c, i);
				nik_ce auto ctn = ins[MI::ctn];
				nik_ce auto val = NIK_MACHINE(d, _m, _c, _i, _Vs)(_Hs...);

				if nik_ce (is_machination<decltype(val)>)

					return NIK_MACHINE(d, MT::propel, c, i, Vs)(val.s1, val.s2, H1, Hs...);

				else if nik_ce (ctn == MI::h1)

					return NIK_MACHINE(d, MT::id, c, i, Vs)(U_null_Vs, U_pack_Vs<val, Xs...>, Hs...);

				else if nik_ce (ctn == MI::h1_pair)

					return NIK_MACHINE(d, MT::id, c, i, Vs)
						(U_null_Vs, U_pack_Vs<val.v1, val.v2, Xs...>, Hs...);
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
			nik_ce auto ins	= MachineDispatch::instr(c, i);
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
			nik_ce auto ins	= MachineDispatch::instr(c, i);
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
		using T_find = T_overload<Overload::alias, Operator::find>;

		template<auto W, auto Z>
		nik_ces bool match = Overload::template result
		<
			Overload::alias, Operator::same, W,
			Overload::template result<Overload::alias, Operator::car, Z>
		>;

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
			nik_ce auto arr	 = array<bool, match<W0, Zs>...>;
			nik_ce auto pos	 = T_find::match(arr, size);

			if nik_ce (pos == size)

				return NIK_MACHINE(d, MT::id, c, i, Vs)(U_null_Vs, H1, H2, A0, As...);
			else
			{
				nik_ce auto ins = MachineDispatch::instr(c, i);
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

			return pair(a0, X0);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// instructions:

/***********************************************************************************************************************/

// overload:
		// reverse order for user friendliness:

	template<key_type key, key_type act, key_type ctn = _h1, depth_type dec = _two>
	nik_ce instr_type action = instruction<MN::call, MT::action, dec, ctn, key, act>;

	// function:

		// comparison:

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto equal = action<Overload::function, Operator::equal, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto not_equal = action<Overload::function, Operator::not_equal, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto less_than = action<Overload::function, Operator::less_than, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto less_than_or_equal = action<Overload::function, Operator::less_than_or_equal, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto greater_than = action<Overload::function, Operator::greater_than, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto greater_than_or_equal = action<Overload::function, Operator::greater_than_or_equal, ctn, dec>;

		// logical:

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto not_ = action<Overload::function, Operator::not_, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto and_ = action<Overload::function, Operator::and_, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto or_ = action<Overload::function, Operator::or_, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto implies = action<Overload::function, Operator::implies, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto equivalent = action<Overload::function, Operator::equivalent, ctn, dec>;

		// arithmetic:

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto add = action<Overload::function, Operator::add, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto subtract = action<Overload::function, Operator::subtract, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto multiply = action<Overload::function, Operator::multiply, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto divide = action<Overload::function, Operator::divide, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto modulo = action<Overload::function, Operator::modulo, ctn, dec>;

		// algebraic:

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto product = action<Overload::function, Operator::product, ctn, dec>;

		// computational:

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto apply = action<Overload::function, Operator::apply, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _three>
		nik_ce auto bind = action<Overload::function, Operator::bind, ctn, dec>;

	// curried:

		// comparison:

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto is_equal = action<Overload::curried, Operator::is_equal, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto is_zero = action<Overload::curried, Operator::is_zero, ctn, dec>;

		// bitwise:

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto upshift = action<Overload::curried, Operator::upshift, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto downshift = action<Overload::curried, Operator::downshift, ctn, dec>;

		// arithmetic:

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto increment = action<Overload::curried, Operator::increment, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto decrement = action<Overload::curried, Operator::decrement, ctn, dec>;

	// alias:

		// comparison:

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto same = action<Overload::alias, Operator::same, ctn, dec>;

		// functional:

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto length = action<Overload::alias, Operator::length, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto map = action<Overload::alias, Operator::map, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto zip = action<Overload::alias, Operator::zip, ctn, dec>;

		//

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto is_null = action<Overload::alias, Operator::is_null, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto cons = action<Overload::alias, Operator::cons, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto push = action<Overload::alias, Operator::push, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto car = action<Overload::alias, Operator::car, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto cdr = action<Overload::alias, Operator::cdr, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto unite = action<Overload::alias, Operator::unite, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto find = action<Overload::alias, Operator::find, ctn, dec>;

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

	template<key_type rtn, key_type ctn = _h1>
	nik_ce instr_type variable = instruction<MN::call, MT::variable, rtn, ctn>;

	template<key_type rtn, key_type ctn = _h1>
	nik_ce instr_type function = instruction<MN::call, MT::function, rtn, ctn>;

	template<key_type rtn, key_type ctn = _h1>
	nik_ce instr_type cascade = instruction<MN::call, MT::cascade, rtn, ctn>;

	template<key_type ctn = _h1, depth_type dec = _two>
	nik_ce instr_type compel = instruction<MN::call, MT::compel, dec, ctn>;

	template<key_type...>
	nik_ce instr_type internal = instruction<MN::call, MT::internal>;

//	template<key_type...>
//	nik_ce instr_type lift  = instruction<MN::move_j_all, MT::id>;

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

// start:

	template<auto d, auto prog, auto... Vs, typename CHeap, typename... Args>
	nik_ce auto start(CHeap ch, Args... As)
	{
		nik_ce auto m	= MT::id;
		nik_ce auto c	= controller<internal<>>;
		nik_ce auto i	= MachineDispatch::initial_index;

		return NIK_BEGIN_MACHINE(d, m, c, i),

				m, prog, i, Vs...

		NIK_END_MACHINE(U_null_Vs, U_null_Vs, ch, As...);
	}

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

