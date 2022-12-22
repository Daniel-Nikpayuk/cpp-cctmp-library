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

// praxis:

	// select and mutate differ by the ability to auto deduce the function type.

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// pack:

	nik_ce auto _pack_null_			= U_pack_Vs <                    >;
	nik_ce auto _pack_first_		= U_pack_Vs < _first_            >;
	nik_ce auto _pack_second_		= U_pack_Vs < _second_           >;
	nik_ce auto _pack_second_first_		= U_pack_Vs < _second_ , _first_ >;

/***********************************************************************************************************************/

// padding:

	template<gindex_type n, auto V = U_null_Vs, auto b = H_id>
	nik_ce auto padding = eval<_pad_, b, V, n>;

	nik_ce gindex_type required_padding(gcindex_type size, gcindex_type _2_N)
	{
		gcindex_type remainder = size % _2_N;

		if (remainder == 0) return 0;
		else                return _2_N - remainder;
	}

	nik_ce gindex_type conditional_padding(gcindex_type pos, gcindex_type size, gcindex_type _2_N)
	{
		gcindex_type padding = required_padding(size, _2_N);

		if (padding == 0) return 0;
		else
		{
			gcindex_type p_block = pos  / _2_N;
			gcindex_type s_block = size / _2_N;

			if (p_block != s_block) return 0;
			else                    return padding;
		}
	}

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// grammar:

	template<gkey_type, gkey_type, gkey_type, auto...> struct T_praxis;

	template<auto Syn, auto Name, auto Note, auto... Vs>
	nik_ce auto U_praxis = U_store_T<T_praxis<Syn, Name, Note, Vs...>>;

	nik_ce auto H_praxis = U_store_B<T_praxis>;

	// argument:

		template<auto Name, auto Note, auto... Vs>
		using T_praxis_arg = T_praxis<Shape::argument, Name, Note, Vs...>;

		template<auto Name, auto Note, auto... Vs>
		nik_ce auto U_praxis_arg = U_praxis<Shape::argument, Name, Note, Vs...>;

	// parameter:

		template<auto Name, auto Note, auto... Vs>
		using T_praxis_par = T_praxis<Shape::parameter, Name, Note, Vs...>;

		template<auto Name, auto Note, auto... Vs>
		nik_ce auto U_praxis_par = U_praxis<Shape::parameter, Name, Note, Vs...>;

/***********************************************************************************************************************/

// names:

	struct PraxisName
	{
		enum : gkey_type
		{
			identity = 0, id = identity, // convenience for default params.
			call   , recall  , tail  , halt    ,
			select , pad     , drop  ,
			mutate , rotate  , unpad ,
			fold   ,
			dimension
		};
	};

	using PN = PraxisName;

/***********************************************************************************************************************/

// notes:

	struct PraxisNote
	{
		enum : gkey_type
		{
			identity = 0, id = identity, // convenience for default params.
			pause    , debug   , arg   , par     ,
			selector , mutator , block , recurse ,
			_2_0 , _2_1 , _2_2 , _2_3 , _2_4 , _2_5 , _2_6 , _2_7 , _2_8 , _2_9 ,
			dimension
		};

		nik_ces gindex_type _2_N_from_note(gkey_type n) { return array_2_N[n - _2_0]; }
	};

	using PT = PraxisNote;

/***********************************************************************************************************************/

// instructions:

	struct PraxisInstr
	{
		using type	= gcindex_type*;
		using ctype	= type const;

		enum Position : gkey_type
		{
			size = 0,
			name , note , pos , num , subpos , subnum ,
			dimension
		};

		nik_ces gindex_type length (ctype i) { return i[size]; }
	};

	using PI		= PraxisInstr;
	using instr_type	= typename PI::type;
	using cinstr_type	= typename PI::ctype;

	template<auto... Vs>
	nik_ce instr_type instruction = array<gcindex_type, sizeof...(Vs), Vs...>;

/***********************************************************************************************************************/

// controllers:

	struct PraxisContr
	{
		using type	= cinstr_type*;
		using ctype	= type const;

		enum Position : gkey_type
		{
			size = 0,
			dimension
		};

		nik_ces gindex_type length (ctype c) { return c[size][PI::size]; }
	};

	using PC         	= PraxisContr;
	using contr_type	= typename PC::type;
	using ccontr_type	= typename PC::ctype;

	template<auto... Vs>
	nik_ce contr_type controller = array<cinstr_type, array<gcindex_type, sizeof...(Vs)>, Vs...>;

	// select:

		// block:

			template<auto Note, auto q, auto k, auto f0 = _zero, auto f1 = _one, auto h = _two>
			nik_ce auto block_select_contr = controller
			<
				instruction < PN::pad    , PT::selector , q                  >,
				instruction < PN::select , PT::id       , k , f0 , f1 , Note >,
				instruction < PN::call   , PT::arg      , h                  >
			>;

		// recurse:

			template<auto Note, auto m, auto q, auto k, auto f0 = _zero, auto f1 = _one, auto h = _two>
			nik_ces auto recurse_select_contr = controller
			<
				instruction < PN::drop   , PT::selector , m ,           Note >,
				instruction < PN::pad    , PT::selector , q                  >,
				instruction < PN::select , PT::id       , k , f0 , f1 , Note >,
				instruction < PN::call   , PT::arg      , h                  >
			>;

	// mutate:

		// block:

			template
			<
				auto Note, auto q0, auto q1, auto k, auto j0, auto j1, auto m,
				auto f0 = _zero, auto f1 = _one, auto h = _two
			>
			nik_ce auto block_mutate_contr = controller
			<
				instruction < PN::pad    , PT::mutator , q0 , q1             >,
				instruction < PN::mutate , PT::id      , k  , f0 , f1 , Note >,
				instruction < PN::unpad  , PT::mutator , j0 , j1 ,      Note >,
				instruction < PN::drop   , PT::mutator , m  ,           Note >,
				instruction < PN::tail   , PT::arg     , h                   >
			>;

		// recurse:

			template
			<
				auto Note, auto q0, auto q1, auto m0, auto k, auto m1, auto j0, auto j1, auto m2,
				auto f0 = _zero, auto f1 = _one, auto h = _two
			>
			nik_ce auto recurse_mutate_contr = controller
			<
				instruction < PN::pad    , PT::mutator , q0 , q1             >,
				instruction < PN::rotate , PT::mutator , m0 ,           Note >,
				instruction < PN::mutate , PT::id      , k  , f0 , f1 , Note >,
				instruction < PN::rotate , PT::mutator , m1 ,           Note >,
				instruction < PN::unpad  , PT::mutator , j0 , j1 ,      Note >,
				instruction < PN::drop   , PT::mutator , m2 ,           Note >,
				instruction < PN::tail   , PT::arg     , h                   >
			>;

/***********************************************************************************************************************/

// basis:

	NIK_DEFINE_PRAXIS_BASIS(64)

	// base:

		template<gkey_type Syn, gkey_type Name, gkey_type Note>
		nik_ce auto U_praxis_base = _alias_<_unite_, H_using<T_praxis, Syn, Name, Note>>;

	// unit:

		template<auto Syn, auto Name, auto Note, auto n, auto L, auto R, auto _2_N = PT::_2_N_from_note(Note)>
		using T_praxis_unit = T_eval<U_praxis_base<Syn, Name, Note>, padding<n, L>, padding<_2_N-(n+1), L>, R>;

		nik_ce auto H_praxis_unit = U_store_B<T_praxis_unit>;

	// part:

		template<auto Syn, auto Name, auto Note, auto n, auto L, auto R, auto _2_N = PT::_2_N_from_note(Note)>
		using T_praxis_part = T_eval<U_praxis_base<Syn, Name, Note>, padding<n, L>, padding<_2_N-n, R>>;

		nik_ce auto H_praxis_part = U_store_B<T_praxis_part>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// argument:

/***********************************************************************************************************************/

// dispatch:

	struct PraxisArgument
	{
		// defaults:

			nik_ces gindex_type initial_index = _zero;

		// accessors:

			nik_ces auto instr(ccontr_type c, gcindex_type i) { return c[i]; }

		// navigators:

			nik_ces   gkey_type next_name  (ccontr_type c, gcindex_type i) { return c[i+1][PI::name]; }
			nik_ces   gkey_type next_note  (ccontr_type c, gcindex_type i) { return c[i+1][PI::note]; }
			nik_ces gindex_type next_index (               gcindex_type i) { return i+1; }
	};

	using PA = PraxisArgument;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// argument (select):

/***********************************************************************************************************************/

// (start):

	struct T_praxis_arg_select
	{
		nik_ces auto i = PA::initial_index;

		template<auto c, auto l, auto... Vs, typename... Ts>
		nik_ces auto result(Ts... vs) { return NIK_PRAX_ARG(c, i, l, Vs)(vs...); }

	}; nik_ce auto U_praxis_arg_select = U_custom_T<T_praxis_arg_select>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// call:

/***********************************************************************************************************************/

// arg:

	template<auto... filler>
	struct T_praxis<Shape::argument, PN::call, PT::arg, filler...>
	{
		template<NIK_PRAX_ARG_PARAMS(c, i, l, Vs), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto ins	   = PA::instr(c, i);
			nik_ce auto lookup = unpack_<l, _car_>;
			nik_ce auto pos    = ins[PI::pos] + 1; // adjusted.
			nik_ce auto cont   = unpack_<l, lookup, gindex_type{pos}>;
			using T_cont       = T_store_U<cont>;

			return T_cont::template result<Vs...>(vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// pad:

/***********************************************************************************************************************/

// selector:

	template<auto... Cs, nik_vp(U)(T_pack_Vs<Cs...>*)>
	struct T_praxis<Shape::argument, PN::pad, PT::selector, U>
	{
		template<NIK_PRAX_ARG_PARAMS(c, i, l, Vs), typename... Ts>
		nik_ces auto result(Ts... vs) { return NIK_PRAX_ARG(c, i, l, Vs)(vs..., Cs...); }
	};

	template<auto... filler>
	struct T_praxis<Shape::argument, PN::pad, PT::selector, filler...>
	{
		template<NIK_PRAX_ARG_PARAMS(c, i, l, Vs), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto ins = PA::instr(c, i);
			nik_ce auto N   = ins[PI::pos];
			using T_cont    = T_praxis_arg<PN::pad, PT::selector, padding<N>>;

			return T_cont::template result<c, i, l, Vs...>(vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// drop:

/***********************************************************************************************************************/

// 2^N:

	NIK_DEFINE_PRAXIS_ARGUMENT_DROP_SELECTOR(6)

// selector:

	template<auto... filler>
	struct T_praxis<Shape::argument, PN::drop, PT::selector, filler...>
	{
		template<NIK_PRAX_ARG_PARAMS(c, i, l, Vs), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto ins	= PA::instr(c, i);
			nik_ce auto m   = ins[PI::pos];
			using T_cont    = T_praxis_arg<PN::drop, ins[PI::num], PT::selector>;

			if constexpr (m == 0)

				return NIK_PRAX_ARG(c, i, l, Vs)(vs...);
			else
				return T_cont::template result<m-1, c, i, l, Vs...>(vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// select:

/***********************************************************************************************************************/

// 2^N:

	NIK_DEFINE_PRAXIS_ARGUMENT_SELECT(6)

// id:

	template<auto... filler>
	struct T_praxis<Shape::argument, PN::select, PT::id, filler...>
	{
		template<NIK_PRAX_ARG_PARAMS(c, i, l, Vs), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto ins    = PA::instr(c, i);
			nik_ce auto k      = ins[PI::pos];
			nik_ce auto f0     = ins[PI::num] + 1; // adjusted.
			nik_ce auto f1     = ins[PI::subpos] + 1; // adjusted.
			nik_ce auto t      = ins[PI::subnum];

			nik_ce auto lookup = unpack_<l, _car_>;
			nik_ce auto p0     = unpack_<l, lookup, gindex_type{f0}>;
			nik_ce auto p1     = unpack_<l, lookup, gindex_type{f1}>;
			using T_cont       = T_praxis_arg<PN::select, t, H_praxis_unit, k, p0, p1>;

			return T_cont::template result<c, i, l, Vs...>(vs...);
		}
	};

/***********************************************************************************************************************/

// block:

	template<auto p0, auto p1, auto cont, auto Note>
	struct T_arg_block_select
	{
		nik_ces auto _2_N = PT::_2_N_from_note(Note);
		nik_ces auto l    = U_pack_Vs<_at_, p0, p1, cont>;

		template<auto k, typename... Ts>
		nik_ces auto result(Ts... vs) // needs to do its own bounds check now that it pads.
		{
			nik_ce auto q = conditional_padding(k, sizeof...(Ts), _2_N);
			nik_ce auto c = block_select_contr<Note, q, k>;

			return T_praxis_arg_select::template result<c, l>(vs...);
		}

	}; template<auto p0, auto p1, auto cont, auto Note>
		nik_ce auto _arg_block_select_ = U_custom_T<T_arg_block_select<p0, p1, cont, Note>>;

	// syntactic sugar:

		// at:

			template<auto k, typename... Ts>
			nik_ce auto arg_block_at(Ts... vs)
			{
				nik_ce auto p0   = _pack_null_;
				nik_ce auto p1   = _pack_first_;
				nik_ce auto cont = _first_;
				nik_ce auto Note = PT::_2_6;

				return T_arg_block_select<p0, p1, cont, Note>::template result<k>(vs...);
			}

/***********************************************************************************************************************/

// recurse:

	template<auto p0, auto p1, auto cont, auto Note>
	struct T_arg_recurse_select
	{
		nik_ces auto _2_N = PT::_2_N_from_note(Note);
		nik_ces auto l    = U_pack_Vs<_at_, p0, p1, cont>;

		template<auto n, typename... Ts>
		nik_ces auto result(Ts... vs) // needs to do its own bounds check now that it pads.
		{
			nik_ce auto m = n / _2_N;
			nik_ce auto k = n % _2_N;
			nik_ce auto q = conditional_padding(n, sizeof...(Ts), _2_N);
			nik_ce auto c = recurse_select_contr<Note, m, q, k>;

			return T_praxis_arg_select::template result<c, l>(vs...);
		}

	}; template<auto p0, auto p1, auto cont, auto Note>
		nik_ce auto _arg_recurse_select_ = U_custom_T<T_arg_recurse_select<p0, p1, cont, Note>>;

	// syntactic sugar:

		// at:

			template<auto n, typename... Ts>
			nik_ce auto arg_at(Ts... vs)
			{
				nik_ce auto p0   = _pack_null_;
				nik_ce auto p1   = _pack_first_;
				nik_ce auto cont = _first_;
				nik_ce auto Note = PT::_2_6;

				return T_arg_recurse_select<p0, p1, cont, Note>::template result<n>(vs...);
			}

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// argument (mutate):

/***********************************************************************************************************************/

// (start):

	struct T_praxis_arg_mutate
	{
		nik_ces auto i = PA::initial_index;

		template<auto s, auto c, auto l, auto... Vs, typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) -> T_store_U<s>
			{ return NIK_PRAX_XARG(s, c, i, l, Vs)(v, vs...); }

	}; nik_ce auto U_praxis_arg_mutate = U_custom_T<T_praxis_arg_mutate>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// tail:

/***********************************************************************************************************************/

// arg:

	template<auto... filler>
	struct T_praxis<Shape::argument, PN::tail, PT::arg, filler...>
	{
		template<NIK_PRAX_ARG_XPARAMS(s, c, i, l, Vs), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) -> T_store_U<s>
		{
			nik_ce auto ins	   = PA::instr(c, i);
			nik_ce auto lookup = unpack_<l, _car_>;
			nik_ce auto pos    = ins[PI::pos] + 1; // adjusted.
			nik_ce auto cont   = unpack_<l, lookup, gindex_type{pos}>;
			using T_cont       = T_store_U<cont>;

			return T_cont::template result<Vs...>(vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// rotate:

/***********************************************************************************************************************/

// 2^N:

	NIK_DEFINE_PRAXIS_ARGUMENT_ROTATE_MUTATOR(6)

// mutator:

	template<auto... filler>
	struct T_praxis<Shape::argument, PN::rotate, PT::mutator, filler...>
	{
		template<NIK_PRAX_ARG_XPARAMS(s, c, i, l, Vs), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) -> T_store_U<s>
		{
			nik_ce auto ins	= PA::instr(c, i);
			nik_ce auto m   = ins[PI::pos];
			using T_cont    = T_praxis_arg<PN::rotate, ins[PI::num], PT::mutator>;

			if constexpr (m == 0)

				return NIK_PRAX_XARG(s, c, i, l, Vs)(v, vs...);
			else
				return T_cont::template result<m-1, s, c, i, l, Vs...>(v, vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// pad:

/***********************************************************************************************************************/

// mutator:

		// matches two packs due to padding limits.

	template<auto... C0s, nik_vp(U0)(T_pack_Vs<C0s...>*), auto... C1s, nik_vp(U1)(T_pack_Vs<C1s...>*)>
	struct T_praxis<Shape::argument, PN::pad, PT::mutator, U0, U1>
	{
		template<NIK_PRAX_ARG_XPARAMS(s, c, i, l, Vs), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) -> T_store_U<s>
			{ return NIK_PRAX_XARG(s, c, i, l, Vs)(v, vs..., C0s..., C1s...); }
	};

	template<auto... filler>
	struct T_praxis<Shape::argument, PN::pad, PT::mutator, filler...>
	{
		template<NIK_PRAX_ARG_XPARAMS(s, c, i, l, Vs), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) -> T_store_U<s>
		{
			nik_ce auto ins  = PA::instr(c, i);
			nik_ce auto q0   = ins[PI::pos];
			nik_ce auto q1   = ins[PI::num];
			using T_cont     = T_praxis_arg<PN::pad, PT::mutator, padding<q0>, padding<q1>>;

			return T_cont::template result<s, c, i, l, Vs...>(v, vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// unpad:

/***********************************************************************************************************************/

// 2^N:

	NIK_DEFINE_PRAXIS_ARGUMENT_UNPAD(6)

// id:

	template<auto... filler>
	struct T_praxis<Shape::argument, PN::unpad, PT::mutator, filler...>
	{
		template<NIK_PRAX_ARG_XPARAMS(s, c, i, l, Vs), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) -> T_store_U<s>
		{
			nik_ce auto ins	  = PA::instr(c, i);
			nik_ce auto j0    = ins[PI::pos];
			nik_ce auto j1    = ins[PI::num];
			nik_ce auto t     = ins[PI::subpos];
			nik_ce auto j     = (gindex_type) (j0 + j1);
			using T_cont      = T_praxis_arg<PN::unpad, t, H_praxis_part, j, _pack_first_, _pack_null_>;

			if constexpr (j == 0)

				return NIK_PRAX_XARG(s, c, i, l, Vs)(v, vs...);
			else
				return T_cont::template result<s, c, i, l, Vs...>(v, vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// drop:

/***********************************************************************************************************************/

// 2^N:

	NIK_DEFINE_PRAXIS_ARGUMENT_DROP_MUTATOR(6)

// mutator:

	template<auto... filler>
	struct T_praxis<Shape::argument, PN::drop, PT::mutator, filler...>
	{
		template<NIK_PRAX_ARG_XPARAMS(s, c, i, l, Vs), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) -> T_store_U<s>
		{
			nik_ce auto ins	= PA::instr(c, i);
			nik_ce auto m   = ins[PI::pos];
			using T_cont    = T_praxis_arg<PN::drop, ins[PI::num], PT::mutator>;

			if constexpr (m == 0)

				return NIK_PRAX_XARG(s, c, i, l, Vs)(v, vs...);
			else
				return T_cont::template result<m-1, s, c, i, l, Vs...>(v, vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// mutate:

/***********************************************************************************************************************/

// 2^N:

	NIK_DEFINE_PRAXIS_ARGUMENT_MUTATE(6)

// id:

	template<auto... filler>
	struct T_praxis<Shape::argument, PN::mutate, PT::id, filler...>
	{
		template<NIK_PRAX_ARG_XPARAMS(s, c, i, l, Vs), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) -> T_store_U<s>
		{
			nik_ce auto ins    = PA::instr(c, i);
			nik_ce auto k      = ins[PI::pos];
			nik_ce auto f0     = ins[PI::num] + 1; // adjusted.
			nik_ce auto f1     = ins[PI::subpos] + 1; // adjusted.
			nik_ce auto t      = ins[PI::subnum];

			nik_ce auto lookup = unpack_<l, _car_>;
			nik_ce auto p0     = unpack_<l, lookup, gindex_type{f0}>;
			nik_ce auto p1     = unpack_<l, lookup, gindex_type{f1}>;
			using T_cont       = T_praxis_arg<PN::mutate, t, H_praxis_unit, k, p0, p1>;

			return T_cont::template result<s, c, i, l, Vs...>(v, vs...);
		}
	};

/***********************************************************************************************************************/

// block:

	template<auto p0, auto p1, auto cont, auto Note>
	struct T_arg_block_mutate
	{
		nik_ces auto _2_N = PT::_2_N_from_note(Note);
		nik_ces auto l    = U_pack_Vs<_at_, p0, p1, cont>;

		template<auto s, auto k, auto q1, auto j1, auto m, auto... Vs, typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) -> T_store_U<s> // needs to do its own bounds check now that it pads.
		{
			nik_ce auto q0 = required_padding(sizeof...(Ts), _2_N);
			nik_ce auto j0 = (sizeof...(Ts) % _2_N);
			nik_ce auto c  = block_mutate_contr<Note, q0, q1, k, j0, j1, m>;

			return T_praxis_arg_mutate::template result<s, c, l, Vs...>(v, vs...);
		}

	}; template<auto p0, auto p1, auto cont, auto Note>
		nik_ce auto _arg_block_mutate_ = U_custom_T<T_arg_block_mutate<p0, p1, cont, Note>>;

	// syntactic sugar:

		// replace:

			template<auto s, auto k, auto cont, auto... Vs, typename T, typename... Ts>
			nik_ce auto arg_block_replace(T v, Ts... vs) -> T_store_U<s>
			{
				nik_ce auto p0   = _pack_first_;
				nik_ce auto p1   = _pack_second_;
				nik_ce auto Note = PT::_2_6;
				nik_ce auto q1   = gindex_type{0};
				nik_ce auto j1   = gindex_type{0};
				nik_ce auto m    = gindex_type{0};

				return T_arg_block_mutate<p0, p1, cont, Note>::template
					result<s, k, q1, j1, m, Vs...>(v, vs...);
			}

		// insert:

			template<auto s, auto k, auto cont, auto... Vs, typename T, typename... Ts>
			nik_ce auto arg_block_insert(T v, Ts... vs) -> T_store_U<s>
			{
				nik_ce auto p0   = _pack_first_;
				nik_ce auto p1   = _pack_second_first_;
				nik_ce auto Note = PT::_2_6;
				nik_ce auto _2_N = PT::_2_N_from_note(Note);
				nik_ce auto q1   = gindex_type{_2_N-1};
				nik_ce auto j1   = gindex_type{1};
				nik_ce auto m    = gindex_type{1};

				return T_arg_block_mutate<p0, p1, cont, Note>::template
					result<s, k, q1, j1, m, Vs...>(v, vs...);
			}

		// erase:

			template<auto s, auto k, auto cont, auto... Vs, typename T, typename... Ts>
			nik_ce auto arg_block_erase(T v, Ts... vs) -> T_store_U<s>
			{
				nik_ce auto p0   = _pack_first_;
				nik_ce auto p1   = _pack_null_;
				nik_ce auto Note = PT::_2_6;
				nik_ce auto q1   = gindex_type{1};
				nik_ce auto j1   = (gindex_type) -1;
				nik_ce auto m    = gindex_type{0};

				return T_arg_block_mutate<p0, p1, cont, Note>::template
					result<s, k, q1, j1, m, Vs...>(v, vs...);
			}

/***********************************************************************************************************************/

// recurse:

	template<auto p0, auto p1, auto cont, auto Note>
	struct T_arg_recurse_mutate
	{
		nik_ces auto _2_N = PT::_2_N_from_note(Note);
		nik_ces auto l    = U_pack_Vs<_at_, p0, p1, cont>;

		template<auto s, auto n, auto q1, auto j1, auto m2, auto... Vs, typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) -> T_store_U<s> // needs to do its own bounds check now that it pads.
		{
			nik_ce auto m0 = n / _2_N;
			nik_ce auto k  = n % _2_N;

			nik_ce auto e  = sizeof...(Ts) / _2_N;
			nik_ce auto j0 = sizeof...(Ts) % _2_N;
			nik_ce auto m1 = (e + (j0 != 0)) - (m0 + 1);

			nik_ce auto q0 = required_padding(sizeof...(Ts), _2_N);
			nik_ce auto c  = recurse_mutate_contr<Note, q0, q1, m0, k, m1, j0, j1, m2>;

			return T_praxis_arg_mutate::template result<s, c, l, Vs...>(v, vs...);
		}

	}; template<auto p0, auto p1, auto cont, auto Note>
		nik_ce auto _arg_recurse_mutate_ = U_custom_T<T_arg_recurse_mutate<p0, p1, cont, Note>>;

	// syntactic sugar:

		// replace:

			template<auto s, auto n, auto cont, auto... Vs, typename T, typename... Ts>
			nik_ce auto arg_replace(T v, Ts... vs) -> T_store_U<s>
			{
				nik_ce auto p0   = _pack_first_;
				nik_ce auto p1   = _pack_second_;
				nik_ce auto Note = PT::_2_6;
				nik_ce auto q1   = gindex_type{0};
				nik_ce auto j1   = gindex_type{0};
				nik_ce auto m2   = gindex_type{0};

				return T_arg_recurse_mutate<p0, p1, cont, Note>::template
					result<s, n, q1, j1, m2, Vs...>(v, vs...);
			}

		// insert:

			template<auto s, auto n, auto cont, auto... Vs, typename T, typename... Ts>
			nik_ce auto arg_insert(T v, Ts... vs) -> T_store_U<s>
			{
				nik_ce auto p0   = _pack_first_;
				nik_ce auto p1   = _pack_second_first_;
				nik_ce auto Note = PT::_2_6;
				nik_ce auto _2_N = PT::_2_N_from_note(Note);
				nik_ce auto q1   = gindex_type{_2_N-1};
				nik_ce auto j1   = gindex_type{1};
				nik_ce auto m2   = gindex_type{1};

				return T_arg_recurse_mutate<p0, p1, cont, Note>::template
					result<s, n, q1, j1, m2, Vs...>(v, vs...);
			}

		// erase:

			template<auto s, auto n, auto cont, auto... Vs, typename T, typename... Ts>
			nik_ce auto arg_erase(T v, Ts... vs) -> T_store_U<s>
			{
				nik_ce auto p0   = _pack_first_;
				nik_ce auto p1   = _pack_null_;
				nik_ce auto Note = PT::_2_6;
				nik_ce auto q1   = gindex_type{1};
				nik_ce auto j1   = (gindex_type) -1;
				nik_ce auto m2   = gindex_type{0};

				return T_arg_recurse_mutate<p0, p1, cont, Note>::template
					result<s, n, q1, j1, m2, Vs...>(v, vs...);
			}

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

