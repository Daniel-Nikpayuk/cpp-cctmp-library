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

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

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
/***********************************************************************************************************************/

// abstract (machine):

/***********************************************************************************************************************/

// names:

	struct AbstractName
	{
		enum : gkey_type
		{
			identity = 0, id = identity, // convenience for default params.
			call , recall , jump , halt ,
			dimension
		};
	};

	using AN = AbstractName;

/***********************************************************************************************************************/

// notes:

	struct AbstractNote
	{
		enum : gkey_type
		{
			identity = 0, id = identity, // convenience for default params.
			go_to , branch , pause , debug ,
			dimension
		};
	};

	using AT = AbstractNote;

/***********************************************************************************************************************/

// instructions:

	struct AbstractInstr
	{
		using type = gcindex_type* const;

		enum Position : gkey_type
		{
			size = 0,
			name , note , subject , pos = subject , jmp ,
			dimension
		};

		nik_ces gindex_type length (type i) { return i[size]; }
	};

	using AI		= AbstractInstr;
	using instr_type	= typename AI::type;
	using cinstr_type	= instr_type const;

	template<auto... Vs>
	nik_ce instr_type instruction = array<gindex_type, sizeof...(Vs), Vs...>;

/***********************************************************************************************************************/

// controllers:

	struct AbstractContr
	{
		using type = cinstr_type* const;

		enum Position : gkey_type
		{
			size = 0,
			dimension
		};

		nik_ces gindex_type length (type l) { return l[size][AI::size]; }
	};

	using AC         = AbstractContr;
	using contr_type = typename AC::type;

	template<auto... Vs>
	nik_ce contr_type controller = array<instr_type, array<gindex_type, sizeof...(Vs)>, Vs...>;

/***********************************************************************************************************************/

// dispatch:

	struct AbstractDisp
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
				if (d == 0)           return AN::halt;
				else if (m != AT::id) return AN::recall;
				else                  return c[i+1][AI::name];
			}

			nik_ces gkey_type next_note(gcdepth_type d, gckey_type m, contr_type c, gcindex_type i)
			{
				if (d == 0)           return AT::pause;
				else if (m != AT::id) return m;
				else                  return c[i+1][AI::note];
			}

			nik_ces gdepth_type next_depth(gcdepth_type d)
				{ return d - bool{d != 0}; }

			nik_ces gindex_type next_index(gcdepth_type d, gckey_type m, contr_type, gcindex_type i)
				{ return i + bool{d != 0 && m == AT::id}; }
	};

	using AD = AbstractDisp;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// block:

	// Arbitrary list_id for user output for greater utility,
	// U_pack_Vs for internal output for greater generality.

	template<gkey_type, gkey_type, auto...> struct T_block;

	template<auto Name, auto Note, auto... Vs>
	nik_ce auto U_block = U_store_T<T_block<Name, Note, Vs...>>;

/***********************************************************************************************************************/

// names:

	struct BlockName : public AbstractName
	{
		enum : gkey_type
		{
			drop = AN::dimension, // = 5
			heap , pad , turn , sift , filter, fold , argument , tuple ,
			dimension
		};
	};

	using BN = BlockName;

/***********************************************************************************************************************/

// notes:

	struct BlockNote : public AbstractNote
	{
		enum : gkey_type
		{
			test = AT::dimension, // = 5
			_2_0 , _2_1 , _2_2 , _2_3 , _2_4 , _2_5 , _2_6 , _2_7 , _2_8 , _2_9 ,
			tail, front, back , eval ,
			dimension
		};
	};

	using BT = BlockNote;

/***********************************************************************************************************************/

// instructions, controllers:

	using BI = AbstractInstr;
	using BC = AbstractContr;

/***********************************************************************************************************************/

// dispatch:

	struct BlockDisp : public AbstractDisp
	{
		using ArrayEnd = T_store_U<_array_end_>;

		nik_ces gindex_type _2_N[] = { _2_0, _2_1, _2_2, _2_3, _2_4, _2_5, _2_6, _2_7, _2_8, _2_9 };

		nik_ces gkey_type log_floor(gcindex_type n)
		{
			gcindex_type *k = ArrayEnd::result(_2_N);

			while (--k != _2_N) if (*k <= n) break;

			return k - _2_N;
		}

		nik_ces gindex_type _2_N_from_note(gkey_type n)
			{ return _2_N[n - BT::_2_0]; }
	};

	using BD = BlockDisp;

/***********************************************************************************************************************/

// constant:

	struct T_block_constant
	{
		nik_ces auto bc_0	= U_pack_Vs<false>;
		nik_ces auto bc_1	= eval<_unite_, H_id, bc_0, bc_0>;
		nik_ces auto bc_2	= eval<_unite_, H_id, bc_1, bc_1>;
		nik_ces auto bc_3	= eval<_unite_, H_id, bc_2, bc_2>;
		nik_ces auto bc_4	= eval<_unite_, H_id, bc_3, bc_3>;
		nik_ces auto bc_5	= eval<_unite_, H_id, bc_4, bc_4>;
		nik_ces auto bc_6	= eval<_unite_, H_id, bc_5, bc_5>;
		nik_ces auto bc_7	= eval<_unite_, H_id, bc_6, bc_6>;
		nik_ces auto bc_8	= eval<_unite_, H_id, bc_7, bc_7>;
		nik_ces auto bc_9	= eval<_unite_, H_id, bc_8, bc_8>;

		nik_ces auto bc_0_to_4	= U_pack_Vs<bc_0, bc_1, bc_2, bc_3, bc_4>;
		nik_ces auto bc_5_to_9	= U_pack_Vs<bc_5, bc_6, bc_7, bc_8, bc_9>;

		template<auto Note>
		nik_ces auto result = unpack_
		<
			if_then_else_<(Note < BT::_2_5), bc_0_to_4, bc_5_to_9>,
			_at_, gindex_type{(Note - BT::_2_0) % _five}
		>;

	}; nik_ce auto _block_constant_ = U_custom_T<T_block_constant>;

	// syntactic sugar:

		template<auto Note> nik_ce auto block_constant_ = eval<_block_constant_, Note>;

/***********************************************************************************************************************/

// start:

	struct T_block_start
	{
		nik_ces auto d = BD::initial_depth;
		nik_ces auto m = BT::id;
		nik_ces auto i = BD::initial_index;

		template<auto c, auto n, auto... Vs, typename... Heaps>
		nik_ces auto result(Heaps... Hs) { return NIK_BLOCK(d, m, c, i, n, Vs)(Hs...); }

	}; nik_ce auto U_block_start = U_custom_T<T_block_start>;

/***********************************************************************************************************************/

// restart:

	struct T_block_restart
	{
		template<NIK_BLOCK_PARAMS, auto... Vs, template<auto...> typename B, auto... Hs>
		nik_ces auto _result(nik_avp(B<Hs...>*)) { return NIK_BLOCK(d, m, c, i, n, Vs)(Hs...); }

		template<auto d, auto p, auto m, auto c, auto i, auto n, auto...Vs>
		nik_ces auto result = _result<d, m, c, i, n, Vs...>(p);

	}; nik_ce auto U_block_restart = U_custom_T<T_block_restart>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// call:

/***********************************************************************************************************************/

// test:

	template<auto... filler>
	struct T_block<BN::call, BT::test, filler...>
	{
		template
		<
			NIK_BLOCK_PARAMS, auto... Vs,
			template<auto...> typename B0, auto Lookup, auto... Ops,
			typename Heap1, typename Heap2,
			template<auto...> typename B3, auto... Ws, typename... Heaps
		>
		nik_ces auto result
		(
			nik_vp(H0)(B0<Lookup, Ops...>*), Heap1 H1, Heap2 H2,
			nik_vp(H3)(B3<Ws...>*), Heaps... Hs
		)
		{
			nik_ce auto ins	= BD::instr(c, i);
			nik_ce auto Op  = eval<Lookup, ins[BI::pos], Ops...>;
			nik_ce auto W0  = eval<Op, n>;
			nik_ce auto nH3 = U_store_T<B3<W0, Ws...>>;

			return NIK_BLOCK(d, BT::id, c, i, n, Vs)(H0, H1, H2, nH3, Hs...);
		}
	};

/***********************************************************************************************************************/

// tail:

	template<auto... filler>
	struct T_block<BN::call, BT::tail, filler...>
	{
		nik_ces auto ni = BD::initial_index;

		template
		<
			NIK_BLOCK_PARAMS, auto... Vs,
			template<auto...> typename B, auto Lookup, auto... Ops,
			typename... Heaps
		>
		nik_ces auto result(nik_vp(H0)(B<Lookup, Ops...>*), Heaps... Hs)
		{
			nik_ce auto ins	= BD::instr(c, i);
			nik_ce auto p   = eval<Lookup, ins[BI::pos], Ops...>;
			nik_ce auto nc  = unpack_<p, _car_>;
			nik_ce auto nn  = unpack_<p, _cadr_>;

			return NIK_BLOCK(d, BT::id, nc, ni, nn, Vs)(H0, Hs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// heap:

/***********************************************************************************************************************/

// front:

	template<auto... filler>
	struct T_block<BN::heap, BT::front, filler...>
	{
		template
		<
			NIK_BLOCK_PARAMS, auto... Vs,
			typename Heap0, typename Heap1, typename Heap2,
			template<auto...> typename B3, auto... Ws, typename... Heaps
		>
		nik_ces auto result(Heap0 H0, Heap1 H1, Heap2 H2, nik_vp(H3)(B3<Ws...>*), Heaps... Hs)
		{
			nik_ce auto nH3 = U_store_T<B3<>>;

			return NIK_BEGIN_BLOCK(d, BT::id, c, i, n),

				Ws..., Vs...

			NIK_END_BLOCK(H0, H1, H2, nH3, Hs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// pad:

/***********************************************************************************************************************/

// back:

	template<auto... filler>
	struct T_block<BN::pad, BT::back, filler...>
	{
		template
		<
			NIK_BLOCK_PARAMS, auto... Vs,
			typename Heap0, typename Heap1,
			template<auto...> typename B2, auto... Cs, typename... Heaps
		>
		nik_ces auto result(Heap0 H0, Heap1 H1, nik_vp(H2)(B2<Cs...>*), Heaps... Hs)
		{
			nik_ce auto nH2 = U_store_T<B2<>>;

			return NIK_BEGIN_BLOCK(d, BT::id, c, i, n),

				Vs..., Cs...

			NIK_END_BLOCK(H0, H1, nH2, Hs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// powers:

/***********************************************************************************************************************/

// 2^0 - 2^6:

	NIK_DEFINE_BLOCK_DROP   (0)	NIK_DEFINE_BLOCK_DROP   (1)	NIK_DEFINE_BLOCK_DROP   (2)
	NIK_DEFINE_BLOCK_HEAP   (0)	NIK_DEFINE_BLOCK_HEAP   (1)	NIK_DEFINE_BLOCK_HEAP   (2)
	NIK_DEFINE_BLOCK_TURN   (0)	NIK_DEFINE_BLOCK_TURN   (1)	NIK_DEFINE_BLOCK_TURN   (2)
	NIK_DEFINE_BLOCK_SIFT   (0)	NIK_DEFINE_BLOCK_SIFT   (1)	NIK_DEFINE_BLOCK_SIFT   (2)
	NIK_DEFINE_BLOCK_FILTER (0)	NIK_DEFINE_BLOCK_FILTER (1)	NIK_DEFINE_BLOCK_FILTER (2)
	NIK_DEFINE_BLOCK_FOLD   (0)	NIK_DEFINE_BLOCK_FOLD   (1)	NIK_DEFINE_BLOCK_FOLD   (2)

	NIK_DEFINE_BLOCK_DROP   (3)	NIK_DEFINE_BLOCK_DROP   (4)	NIK_DEFINE_BLOCK_DROP   (5)
	NIK_DEFINE_BLOCK_HEAP   (3)	NIK_DEFINE_BLOCK_HEAP   (4)	NIK_DEFINE_BLOCK_HEAP   (5)
	NIK_DEFINE_BLOCK_TURN   (3)	NIK_DEFINE_BLOCK_TURN   (4)	NIK_DEFINE_BLOCK_TURN   (5)
	NIK_DEFINE_BLOCK_SIFT   (3)	NIK_DEFINE_BLOCK_SIFT   (4)	NIK_DEFINE_BLOCK_SIFT   (5)
	NIK_DEFINE_BLOCK_FILTER (3)	NIK_DEFINE_BLOCK_FILTER (4)	NIK_DEFINE_BLOCK_FILTER (5)
	NIK_DEFINE_BLOCK_FOLD   (3)	NIK_DEFINE_BLOCK_FOLD   (4)	NIK_DEFINE_BLOCK_FOLD   (5)

	NIK_DEFINE_BLOCK_DROP   (6)
	NIK_DEFINE_BLOCK_HEAP   (6)
	NIK_DEFINE_BLOCK_TURN   (6)
	NIK_DEFINE_BLOCK_SIFT   (6)
	NIK_DEFINE_BLOCK_FILTER (6)
	NIK_DEFINE_BLOCK_FOLD   (6)

/***********************************************************************************************************************/

// 2^7:

#if defined NIK_DEFINE_2_7_BLOCKS || \
    defined NIK_DEFINE_2_8_BLOCKS || \
    defined NIK_DEFINE_2_9_BLOCKS

	NIK_DEFINE_BLOCK_DROP   (7)
	NIK_DEFINE_BLOCK_HEAP   (7)
	NIK_DEFINE_BLOCK_TURN   (7)
	NIK_DEFINE_BLOCK_SIFT   (7)
	NIK_DEFINE_BLOCK_FILTER (7)
	NIK_DEFINE_BLOCK_FOLD   (7)

#endif

/***********************************************************************************************************************/

// 2^8:

#if defined NIK_DEFINE_2_8_BLOCKS || \
    defined NIK_DEFINE_2_9_BLOCKS

	NIK_DEFINE_BLOCK_DROP   (8)
	NIK_DEFINE_BLOCK_HEAP   (8)
	NIK_DEFINE_BLOCK_TURN   (8)
	NIK_DEFINE_BLOCK_SIFT   (8)
	NIK_DEFINE_BLOCK_FILTER (8)
	NIK_DEFINE_BLOCK_FOLD   (8)

#endif

/***********************************************************************************************************************/

// 2^9:

#if defined NIK_DEFINE_2_9_BLOCKS

	NIK_DEFINE_BLOCK_DROP   (9)
	NIK_DEFINE_BLOCK_HEAP   (9)
	NIK_DEFINE_BLOCK_TURN   (9)
	NIK_DEFINE_BLOCK_SIFT   (9)
	NIK_DEFINE_BLOCK_FILTER (9)
	NIK_DEFINE_BLOCK_FOLD   (9)

#endif

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// jump:

/***********************************************************************************************************************/

// go to:

	template<auto... filler>
	struct T_block<BN::jump, BT::go_to, filler...>
	{
		template
		<
			NIK_BLOCK_PARAMS, auto... Vs,
			template<auto...> typename B0, auto Lookup, auto... Ops, typename... Heaps
		>
		nik_ces auto result(nik_vp(H0)(B0<Lookup, Ops...>*), Heaps... Hs)
		{
			nik_ce auto ins	= BD::instr(c, i);
			nik_ce auto Op  = eval<Lookup, ins[BI::pos], Ops...>;
			nik_ce auto ni	= ins[BI::jmp];
			nik_ce auto nn  = eval<Op, n>;

			return NIK_BLOCK(d, BT::id, c, ni, nn, Vs)(H0, Hs...);
		}
	};

/***********************************************************************************************************************/

// branch:

	template<auto... filler>
	struct T_block<BN::jump, BT::branch, filler...>
	{
		template
		<
			NIK_BLOCK_PARAMS, auto... Vs,
			template<auto...> typename B0, auto Lookup, auto... Ops,
			typename Heap1, typename Heap2,
			template<auto...> typename B3, bool W0, auto... Ws, typename... Heaps
		>
		nik_ces auto result
		(
			nik_vp(H0)(B0<Lookup, Ops...>*), Heap1 H1, Heap2 H2,
			nik_vp(H3)(B3<W0, Ws...>*), Heaps... Hs
		)
		{
			nik_ce auto ins	= BD::instr(c, i);
			nik_ce auto Op  = eval<Lookup, ins[BI::pos], Ops...>;
			nik_ce auto ni	= W0 ? ins[BI::jmp] : i;
			nik_ce auto nn  = eval<Op, n>;
			nik_ce auto nH3 = U_store_T<B3<Ws...>>;

			return NIK_BLOCK(d, BT::id, c, ni, nn, Vs)(H0, H1, H2, nH3, Hs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// halt:

/***********************************************************************************************************************/

// pause:

	template<auto... filler>
	struct T_block<BN::halt, BT::pause, filler...>
	{
		template<NIK_BLOCK_PARAMS, auto... Vs, typename... Heaps>
		nik_ces auto result(Heaps...)
		{
			nik_ce auto p = U_pack_Vs<U_restore_T<Heaps>...>;

			return machination(U_block_restart, U_pack_Vs<p, m, c, i, n, Vs...>);
		}
	};

/***********************************************************************************************************************/

// debug:

	template<auto... filler>
	struct T_block<BN::halt, BT::debug, filler...>
	{
		template<NIK_BLOCK_PARAMS, auto... Vs, typename... Heaps>
		nik_ces auto result(Heaps... Hs)
		{
			nik_ce auto cs = eval<_to_tuple_, d, m, c, i, n>;
			nik_ce auto rs = eval<_to_tuple_, Vs...>;
			nik_ce auto hs = eval<_to_tuple_, U_restore_T<Heaps>...>;

			return eval<_to_tuple_, cs, rs, hs>;
		}
	};

/***********************************************************************************************************************/

// eval:

	template<auto... filler>
	struct T_block<BN::halt, BT::eval, filler...>
	{
		template
		<
			NIK_BLOCK_PARAMS, auto... Vs,
			template<auto...> typename B, auto Lookup, auto... Ops,
			typename... Heaps
		>
		nik_ces auto result(nik_vp(H0)(B<Lookup, Ops...>*), Heaps...)
		{
			nik_ce auto ins	= BD::instr(c, i);
			nik_ce auto Op  = eval<Lookup, ins[BI::pos], Ops...>;

			return eval<Op, Vs...>;
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// algorithm:

	template<auto...> struct T_algorithm;
	template<auto... Vs> nik_ce auto _algorithm_ = U_custom_T<T_algorithm<Vs...>>;

/***********************************************************************************************************************/

// names:

	struct Algorithm
	{
		enum : gkey_type
		{
			padding = 0,
			index, value
		};
	};

/***********************************************************************************************************************/

// notes:

	struct Paradigm
	{
		enum : gkey_type
		{
			block = 0,
			recurse
		};
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// filters:

/***********************************************************************************************************************/

// basis:

	nik_ce auto grammatical_index					= U_pack_Vs < _car_                  >;
	nik_ce auto grammatical_value					= U_pack_Vs < _cadr_                 >;
	nik_ce auto grammatical_erase					= U_pack_Vs <                        >;

	template<auto V> nik_ce auto grammatical_replace		= U_pack_Vs < _constant_<V>          >;
	template<auto V> nik_ce auto grammatical_insert			= U_pack_Vs < _constant_<V> , _cadr_ >;

	// syntactic sugar:

		nik_ce auto gr_index					= grammatical_index;
		nik_ce auto gr_value					= grammatical_value;
		nik_ce auto gr_erase					= grammatical_erase;

		template<auto V> nik_ce auto gr_replace			= grammatical_replace<V>;
		template<auto V> nik_ce auto gr_insert			= grammatical_insert<V>;

/***********************************************************************************************************************/

// by index:

	template<auto op, auto ante, auto conse>
	struct T_filter_by_index
	{
		template<auto k, auto v>
		nik_ces auto result = if_then_else_<eval<op, k>, ante, conse>;
	};

	// at:

		template<auto n>
		using T_filter_at		= T_filter_by_index<_is_equal_<n>, gr_value, gr_erase>;
		nik_ce auto H_filter_at		= U_store_B<T_filter_at>;

	// erase:

		template<auto n>
		using T_filter_erase		= T_filter_by_index<_is_equal_<n>, gr_erase, gr_value>;
		nik_ce auto H_filter_erase	= U_store_B<T_filter_erase>;

	// replace:

		template<auto n, auto V>
		using T_filter_replace		= T_filter_by_index<_is_equal_<n>, gr_replace<V>, gr_value>;
		nik_ce auto H_filter_replace	= U_store_B<T_filter_replace>;

	// insert:

		template<auto n, auto V>
		using T_filter_insert		= T_filter_by_index<_is_equal_<n>, gr_insert<V>, gr_value>;
		nik_ce auto H_filter_insert	= U_store_B<T_filter_insert>;

	// before:

		template<auto n>
		using T_filter_before		= T_filter_by_index<_is_lt_<n>, gr_value, gr_erase>;
		nik_ce auto H_filter_before	= U_store_B<T_filter_before>;

	// left:

		template<auto n>
		using T_filter_left		= T_filter_by_index<_is_lt_or_eq_<n>, gr_value, gr_erase>;
		nik_ce auto H_filter_left	= U_store_B<T_filter_left>;

	// after:

		template<auto n>
		using T_filter_after		= T_filter_by_index<_is_gt_<n>, gr_value, gr_erase>;
		nik_ce auto H_filter_after	= U_store_B<T_filter_after>;

	// right:

		template<auto n>
		using T_filter_right		= T_filter_by_index<_is_gt_or_eq_<n>, gr_value, gr_erase>;
		nik_ce auto H_filter_right	= U_store_B<T_filter_right>;

/***********************************************************************************************************************/

// padder:

	template<auto filter, auto rs, auto padding_filter = gr_erase>
	struct T_filter_with_padder
	{
		nik_ces auto padder = _alias_<_car_, padding_filter>;

		template<auto k, auto v>
		nik_ces auto result = eval
		<
			if_then_else_<(k < rs), filter, padder>, k, v
		>;

	}; template<auto filter, auto rs, auto padding_filter = gr_erase>
		nik_ce auto U_filter_with_padder = U_custom_T<T_filter_with_padder<filter, rs, padding_filter>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// block:

	template<auto Name, auto... Vs> using T_block_algorithm		= T_algorithm<Name, Paradigm::block, Vs...>;
	template<auto Name, auto... Vs> nik_ce auto _block_algorithm_	= _algorithm_<Name, Paradigm::block, Vs...>;

	// controller:

		template<auto...>
		nik_ce auto generic_block_contr = controller<>;

		template
		<
			auto Note, auto op0,
			auto... Ps, nik_vp(p)(T_pack_Vs<Ps...>*),
			auto... Hs, nik_vp(h)(T_pack_Vs<Hs...>*)
		>
		nik_ce auto generic_block_contr<Note, op0, p, h> = controller
		<
			eval<Ps, instruction < BN::pad  , BT::back          >>... ,
			         instruction < BN::turn , Note      , _zero >     ,
			         instruction < BN::sift , Note              >     ,
			eval<Hs, instruction < BN::heap , BT::front         >>... ,
			         instruction < BN::halt , BT::eval  , op0   >
		>;

		// unpadded:

			template<auto Note, auto op0 = _zero>
			nik_ce auto block_contr = generic_block_contr<Note, op0, gr_erase, gr_erase>;

			template<auto Note, auto op0 = _zero>
			nik_ce auto h_block_contr = generic_block_contr<Note, op0, gr_erase, gr_index>;

		// padded:

			template<auto Note, auto op0 = _zero>
			nik_ce auto p_block_contr = generic_block_contr<Note, op0, gr_index, gr_erase>;

			template<auto Note, auto op0 = _zero>
			nik_ce auto ph_block_contr = generic_block_contr<Note, op0, gr_index, gr_index>;

/***********************************************************************************************************************/

// padding:

	template<auto Note, auto... Cs, nik_vp(Constant)(T_pack_Vs<Cs...>*)>
	struct T_algorithm<Algorithm::padding, Paradigm::block, Note, Constant>
	{
		nik_ces auto Contr			= block_contr<Note>;
		nik_ces auto Lookup0			= _cadr_;
		nik_ces auto Eval			= _list_<>;
		nik_ces auto Lookup1			= _cadr_;
		template<auto n> nik_ces auto Filter	= U_custom_T<T_filter_right<n>>;

		nik_ces auto h0				= U_pack_Vs<Lookup0, Eval>;
		template<auto n> nik_ces auto h1	= U_pack_Vs<Lookup1, Filter<n>>;
		nik_ces auto h2				= U_null_Vs;
		nik_ces auto h3				= U_null_Vs;

		template<gindex_type n>
		nik_ces auto result = T_block_start::template result<Contr, _zero, Cs...>(h0, h1<n>, h2, h3);
	};

	// 2^N:

		template<auto Note>
		nik_ce auto _2_N_padding_ = _block_algorithm_<Algorithm::padding, Note, block_constant_<Note>>;

	// padder (optimized):

		template<gindex_type n, gindex_type log_ceil = BD::log_floor(n) + 1>
		nik_ce auto padder = eval
		<
			_2_N_padding_<BT::_2_0 + log_ceil>,
			BD::_2_N[log_ceil] - n
		>;

/***********************************************************************************************************************/

// index:

	template<auto Note, template<auto...> typename B, nik_vp(Filter)(T_store_B<B>*), auto Eval>
	struct T_algorithm<Algorithm::index, Paradigm::block, Note, Filter, Eval>
	{
		nik_ces auto Contr					= p_block_contr<Note>;
		nik_ces auto Lookup0					= _cadr_;
		nik_ces auto Lookup1					= _cadr_;

		nik_ces auto h0						= U_pack_Vs<Lookup0, Eval>;

		template<auto F> nik_ces auto H1			= U_pack_Vs<Lookup1, F>;
		template<typename F, auto s> nik_ces auto FiltPad	= U_filter_with_padder<U_custom_T<F>, s>;
		template<auto n, auto s, auto... Vs> nik_ces auto h1	= H1<FiltPad<B<n, Vs...>, s>>;

		template<auto s> nik_ces auto h2			= padder<BD::_2_N_from_note(Note) - s>;
		nik_ces auto h3						= U_null_Vs;

		template<gindex_type n, auto... Vs>
		nik_ces auto result = T_block_start::template result
		<
			Contr, _zero, Vs...

		>(h0, h1<n, sizeof...(Vs)>, h2<sizeof...(Vs)>, h3);
	};

	// at (2^N):

		template<auto Note>
		nik_ce auto _2_N_block_at_ = _block_algorithm_<Algorithm::index, Note, H_filter_at, _car_>;

	// erase (2^N):

		template<auto Note>
		nik_ce auto _2_N_block_erase_ = _block_algorithm_<Algorithm::index, Note, H_filter_erase, _list_<>>;

/***********************************************************************************************************************/

// value:

	template<auto Note, template<auto...> typename B, nik_vp(Filt)(T_store_B<B>*), auto Eval>
	struct T_algorithm<Algorithm::value, Paradigm::block, Note, Filt, Eval> :
		public T_block_algorithm<Algorithm::index, Note, Filt, Eval>
	{
		using Base = T_algorithm;

		template<gindex_type n, auto V, auto... Vs>
		nik_ces auto result = T_block_start::template result
		<
			Base::Contr, _zero, Vs...

		>(Base::h0, Base::template h1<n, sizeof...(Vs), V>, Base::template h2<sizeof...(Vs)>, Base::h3);
	};

	// replace (2^N):

		template<auto Note>
		nik_ce auto _2_N_block_replace_ = _block_algorithm_<Algorithm::value, Note, H_filter_replace, _list_<>>;

	// insert (2^N):

		template<auto Note>
		nik_ce auto _2_N_block_insert_ = _block_algorithm_<Algorithm::value, Note, H_filter_insert, _list_<>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// recurse:

	template<auto Name, auto... Vs> using T_recurse_algorithm	= T_algorithm<Name, Paradigm::recurse, Vs...>;
	template<auto Name, auto... Vs> nik_ce auto _recurse_algorithm_	= _algorithm_<Name, Paradigm::recurse, Vs...>;

	// controller:

		template
		<
			auto Name, auto Note,
			auto  op0 = _zero , auto  op1 = _one  , auto op2 = _two , auto op3 = _three ,
			auto lbl0 = _zero , auto lbl4 = _four
		>
		nik_ce auto recurse_contr = controller
		<
		// loop:
			instruction < BN::call , BT::test   , op0          >,
			instruction < BN::jump , BT::branch , op1   , lbl4 >,
			instruction < Name     , Note                      >,
			instruction < BN::jump , BT::go_to  , op2   , lbl0 >,
		// done:
			instruction < BN::call , BT::tail   , op3          >
		>;

/***********************************************************************************************************************/

// dispatch:

	// tail call:

	template<auto qn, auto qs>
	nik_ces auto dispatch_gr_pad = if_then_else_<(qn == qs), gr_index, gr_erase>;

	template<auto Note, auto pos, auto qn, auto qs, auto gr_heap>
	nik_ces auto dispatch_tail_call = U_pack_Vs
	<
		generic_block_contr<Note, pos, dispatch_gr_pad<qn, qs>, gr_heap>, _zero
	>;

	// filter:

	template<auto Filter, auto last, auto rs>
	nik_ce auto dispatch_filter()
	{
		if constexpr (last) return U_filter_with_padder<Filter, rs>;
		else                return Filter;
	}

	// padding:

	template<auto qn, auto qs, auto rs, auto _2_N>
	nik_ces auto dispatch_padding()
	{
		if constexpr (qn == qs) return padder<_2_N - rs>;
		else                    return U_null_Vs;
	}
	
/***********************************************************************************************************************/

// index:

	template
	<
		auto Note, auto Action, auto Heap,
		template<auto...> typename B, nik_vp(Filter)(T_store_B<B>*),
		auto Eval
	>
	struct T_algorithm<Algorithm::index, Paradigm::recurse, Note, Action, Heap, Filter, Eval>
	{
		nik_ces auto Contr						= recurse_contr<Action, Note>;
		nik_ces auto Lookup0						= _at_;
		nik_ces auto Test						= _is_equal_<0>;
		nik_ces auto Branch						= _id_;
		nik_ces auto Goto						= _increment_<-1>;
		nik_ces auto Lookup1						= _cadr_;
		nik_ces auto _2_N						= BD::_2_N_from_note(Note);

		template<auto T> nik_ces auto H0				= U_pack_Vs<Lookup0, Test, Branch, Goto, T, Eval>;
		template<auto qn, auto qs> nik_ces auto TailCall		= dispatch_tail_call<Note, _four, qn, qs, Heap>;
		template<auto qn, auto qs> nik_ces auto h0			= H0<TailCall<qn, qs>>;

		template<auto F> nik_ces auto H1				= U_pack_Vs<Lookup1, F>;
		template<auto F, auto last, auto rs> nik_ces auto FiltPad	= H1<dispatch_filter<F, last, rs>()>;
		template<auto rn, auto... Vs> nik_ces auto Filt			= U_custom_T<B<rn, Vs...>>;
		template<auto qn, auto rn, auto qs, auto rs, auto... Vs>
			nik_ces auto h1						= FiltPad<Filt<rn, Vs...>, (qn == qs), rs>;

		template<auto qn, auto qs, auto rs> nik_ces auto h2		= dispatch_padding<qn, qs, rs, _2_N>();
		nik_ces auto h3							= U_null_Vs;

		template<auto qn, auto rn, auto qs, auto rs, auto... Vs>
		nik_ces auto let_result = T_block_start::template result
		<
			Contr, qn, Vs...

		>(h0<qn, qs>, h1<qn, rn, qs, rs>, h2<qn, qs, rs>, h3);

		template<gindex_type n, auto... Vs>
		nik_ces auto result = let_result<n/_2_N, n%_2_N, sizeof...(Vs)/_2_N, sizeof...(Vs)%_2_N, Vs...>;
	};

	// at (2^N):

		template<auto Note>
		nik_ce auto _2_N_at_ = _recurse_algorithm_
		<
			Algorithm::index, Note, BN::drop, gr_erase, H_filter_at, _car_
		>;

	// erase (2^N):

		template<auto Note>
		nik_ce auto _2_N_erase_ = _recurse_algorithm_
		<
			Algorithm::index, Note, BN::heap, gr_index, H_filter_erase, _list_<>
		>;

/***********************************************************************************************************************/

// value:

	template
	<
		auto Note, auto Action, auto Heap,
		template<auto...> typename B, nik_vp(Filter)(T_store_B<B>*),
		auto Eval
	>
	struct T_algorithm<Algorithm::value, Paradigm::recurse, Note, Action, Heap, Filter, Eval> :
		public T_recurse_algorithm<Algorithm::index, Note, Action, Heap, Filter, Eval>
	{
		using Base		= T_algorithm;
		nik_ces auto _2_N	= BD::_2_N_from_note(Note);

		template<auto qn, auto rn, auto qs, auto rs, auto V, auto... Vs>
		nik_ces auto let_result = T_block_start::template result
		<
			Base::Contr, qn, Vs...

		>(Base::template h0<qn, qs>, Base::template h1<qn, rn, qs, rs, V>, Base::template h2<qn, qs, rs>, Base::h3);

		template<gindex_type n, auto V, auto... Vs>
		nik_ces auto result = let_result<n/_2_N, n%_2_N, sizeof...(Vs)/_2_N, sizeof...(Vs)%_2_N, V, Vs...>;
	};

	// replace (2^N):

		template<auto Note>
		nik_ce auto _2_N_replace_ = _recurse_algorithm_
		<
			Algorithm::value, Note, BN::heap, gr_index, H_filter_replace, _list_<>
		>;

	// insert (2^N):

		template<auto Note>
		nik_ce auto _2_N_insert_ = _recurse_algorithm_
		<
			Algorithm::value, Note, BN::heap, gr_index, H_filter_insert, _list_<>
		>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// sort:

/***********************************************************************************************************************/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// tuple:

/***********************************************************************************************************************/

// value:

/*
	template<gindex_type n, typename... Ts>
	nik_ce auto & tuple_value(tuple<Ts...> & t) { return NIK_TUPLE_BLOCK(3, 500, n, Ts)(t); }

	template<gindex_type n, typename... Ts>
	nik_ce const auto & tuple_value(const tuple<Ts...> & t) { return NIK_TUPLE_BLOCK(3, 500, n, Ts)(t); }
*/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// ordered:

/***********************************************************************************************************************/

// mutate (generic):

/*
	template<auto Part>
	struct TP_ordered_mutate
	{
		nik_ces auto c = controller
		<
			find   <                     >,
			copy   < _zero   , _constant >,
			stage  <           _all      >,
			compel < _nested , _h1_pair  >,
			copy   < _one    , _constant >,
			stage  <           _all      >,
			copy   < _zero   , _register >,
			unite  <           _value    >
		>;

		template<auto d, auto b, auto Pred, auto V, auto... Vs>
		nik_ces auto result = T_start::template result<d, c, V>
		(
			U_pack_Vs<_alias_<Pred, V>, Vs...>,
			U_pack_Vs<H_id, H_id, Vs...>,
			U_pack_Vs<Part, b>
		);

	}; template<auto Part>
		nik_ce auto UP_ordered_mutate = U_custom_T<TP_ordered_mutate<Part>>;
*/

/***********************************************************************************************************************/

// insert:

/*
	using TP_ordered_insert		= TP_ordered_mutate<UP_split>;
	nik_ce auto UP_ordered_insert	= U_custom_T<TP_ordered_insert>;

	using TL_ordered_insert		= TP_unpack<UP_ordered_insert>;
	nik_ce auto UL_ordered_insert	= UP_unpack<UP_ordered_insert>;

	template<auto Pred, auto V, auto... Vs>
	nik_ce auto pack_ordered_insert = TP_ordered_insert::template result<MD::initial_depth, H_id, Pred, V, Vs...>;

	template<auto p, auto V, auto Pred = _less_than_, auto b = H_id, auto d = MD::initial_depth>
	nik_ce auto list_ordered_insert = TL_ordered_insert::template result<d, p, b, Pred, V>;
*/

/***********************************************************************************************************************/

// replace:

/*
	using TP_ordered_replace	= TP_ordered_mutate<UP_cut>;
	nik_ce auto UP_ordered_replace	= U_custom_T<TP_ordered_replace>;

	using TL_ordered_replace	= TP_unpack<UP_ordered_replace>;
	nik_ce auto UL_ordered_replace	= UP_unpack<UP_ordered_replace>;

	template<auto Pred, auto V, auto... Vs>
	nik_ce auto pack_ordered_replace = TP_ordered_replace::template result<MD::initial_depth, H_id, Pred, V, Vs...>;

	template<auto p, auto V, auto Pred = _less_than_, auto b = H_id, auto d = MD::initial_depth>
	nik_ce auto list_ordered_replace = TL_ordered_replace::template result<d, p, b, Pred, V>;
*/

/***********************************************************************************************************************/

// monoid:

/*
	template<auto Part, auto Pred = _less_than_, auto b = H_id>
	struct TP_ordered_monoid
	{
		template<auto d, auto p, auto V>
		nik_ces auto result = unpack_<p, UP_ordered_mutate<Part>, d, b, Pred, V>;

	}; template<auto Part, auto Pred = _less_than_, auto b = H_id>
		nik_ce auto UP_ordered_monoid = U_custom_T<TP_ordered_monoid<Part, Pred, b>>;
*/

/***********************************************************************************************************************/

// fold:

/*
	template<auto Part>
	struct TP_ordered_fold
	{
		template<auto d, auto b, auto Pred, auto V, auto... Vs>
		nik_ces auto result = TP_cascade::template result<d, UP_ordered_monoid<Part, Pred, b>, V, Vs...>;

	}; template<auto Part>
		nik_ce auto UP_ordered_fold = U_custom_T<TP_ordered_fold<Part>>;
*/

/***********************************************************************************************************************/

// sort:

/*
	using TP_sort		= TP_ordered_fold<UP_split>;
	nik_ce auto UP_sort	= U_custom_T<TP_sort>;

	using TL_sort		= TP_unpack<UP_sort>;
	nik_ce auto UL_sort	= UP_unpack<UP_sort>;

	template<auto Pred, auto V, auto... Vs>
	nik_ce auto pack_sort = TP_sort::template result<MD::initial_depth, H_id, Pred, V, Vs...>;

	template<auto p, auto Pred = _less_than_, auto V = U_null_Vs, auto b = H_id, auto d = MD::initial_depth>
	nik_ce auto list_sort = TL_sort::template result<d, p, b, Pred, V>;
*/

/***********************************************************************************************************************/

// write:

/*
	using TP_write		= TP_ordered_fold<UP_cut>;
	nik_ce auto UP_write	= U_custom_T<TP_write>;

	using TL_write		= TP_unpack<UP_write>;
	nik_ce auto UL_write	= UP_unpack<UP_write>;

	template<auto Pred, auto V, auto... Vs>
	nik_ce auto pack_write = TP_write::template result<MD::initial_depth, H_id, Pred, V, Vs...>;

	template<auto p, auto Pred = _less_than_, auto V = U_null_Vs, auto b = H_id, auto d = MD::initial_depth>
	nik_ce auto list_write = TL_write::template result<d, p, b, Pred, V>;
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// modify:

/***********************************************************************************************************************/

/*
	struct TP_modify
	{
		nik_ces auto c = controller
		<
			find      <                     >,
			copy      < _zero   , _constant >,
			stage     <           _all      >,
			compel    < _nested , _h1_pair  >,
			stage     <                     >,
			paste     <           _register >,
			write     < _zero   , _argument >,
			stage     <                     >,
			compel    < _nested             >,
			copy      < _zero   , _register >,
			copy      < _one    , _constant >,
			copy      < _two    , _constant >,
			stage     <                     >,
			f2_unpack <           _value    >
		>;

		template<auto d, auto b, auto Pred, auto Op, auto V, auto... Vs>
		nik_ces auto result = T_start::template result<d, c>
		(
		 	U_pack_Vs<_alias_<Pred, V>, Vs...>,
			U_pack_Vs<H_id, H_id, H_id, Vs...>,
			U_pack_Vs<UP_alter, _unite_, b>,
			U_pack_Vs<Op, V>
		);

	}; nik_ce auto UP_modify = U_custom_T<TP_modify>;
*/

/***********************************************************************************************************************/

// monoid:

/*
	template<auto Op, auto Pred = _same_, auto b = H_id>
	struct TP_modify_monoid
	{
		template<auto d, auto p, auto V>
		nik_ces auto result = unpack_<p, UP_modify, d, b, Pred, Op, V>;

	}; template<auto Op, auto Pred = _same_, auto b = H_id>
		nik_ce auto UP_modify_monoid = U_custom_T<TP_modify_monoid<Op, Pred, b>>;
*/

/***********************************************************************************************************************/

// fold:

/*
	struct TP_modify_fold
	{
		template<auto d, auto b, auto Pred, auto Op, auto V, auto... Vs>
		nik_ces auto result = TP_cascade::template result<d, UP_modify_monoid<Op, Pred, b>, V, Vs...>;

	}; nik_ce auto UP_modify_fold = U_custom_T<TP_modify_fold>;
*/

/***********************************************************************************************************************/

// merge:

/*
	using TP_merge		= TP_modify_fold;
	nik_ce auto UP_merge	= U_custom_T<TP_merge>;

	using TL_merge		= TP_unpack<UP_merge>;
	nik_ce auto UL_merge	= UP_unpack<UP_merge>;

	template<auto Pred, auto Op, auto V, auto... Vs>
	nik_ce auto pack_merge = TP_merge::template result<MD::initial_depth, H_id, Pred, Op, V, Vs...>;

	template<auto p, auto Op, auto Pred = _same_, auto V = U_null_Vs, auto b = H_id, auto d = MD::initial_depth>
	nik_ce auto list_merge = TL_merge::template result<d, p, b, Pred, Op, V>;
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// match:

	// This operator is intended for use within machine tests, with the _h1_pair option.

/***********************************************************************************************************************/

/*
	struct TP_match
	{
		template<auto Pred, auto V, auto... Vs>
		nik_ces auto _result()
		{
			nik_ce auto pos  = find_<_alias_<Pred, V>, Vs...>;
			nik_ce auto size = sizeof...(Vs);

			return eval<_to_tuple_, bool{pos < size}, pos>;
		}

		template<auto Pred, auto V, auto... Vs>
		nik_ces auto result = _result<Pred, V, Vs...>();

	}; nik_ce auto UP_match = U_custom_T<TP_match>;

	struct TL_match
	{
		template<auto p, auto Pred, auto V>
		nik_ces auto result = unpack_<p, UP_match, Pred, V>;

	}; nik_ce auto UL_match = U_custom_T<TL_match>;

	template<auto Pred, auto V, auto... Vs>
	nik_ce auto pack_match = TP_match::template result<Pred, V, Vs...>;

	template<auto p, auto V, auto Pred = _same_>
	nik_ce auto list_match = TL_match::template result<p, Pred, V>;
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// lookup:

/***********************************************************************************************************************/

/*
	struct TP_lookup
	{

	}; nik_ce auto UP_lookup = U_custom_T<TP_lookup>;
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// tuple:

/***********************************************************************************************************************/

// to list:

/*
	template<auto b, auto c>
	nik_ce auto return_tuple_to_list()
	{
		nik_ce auto t = c();

		return to_list_<b, tuple_value<Is>(t)...>;
	}

	template<auto b, auto c>
	nik_ce auto constexpr_tuple_to_list()
	{
		nik_ce auto types = c();

		return return_tuple_to_list<c>();
	}

	template<auto b, auto c>
	nik_ce auto callable_tuple_to_list = constexpr_tuple_to_list<b, c>()
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // cctmp

