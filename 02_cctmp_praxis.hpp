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

	nik_ce gcindex_type required_padding(gcindex_type size, gcindex_type _2_N)
	{
		gcindex_type remainder = size % _2_N;

		if (remainder == 0) return 0;
		else                return _2_N - remainder;
	}

	nik_ce gcindex_type conditional_padding(gcindex_type pos, gcindex_type size, gcindex_type _2_N)
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
			select , pad     , drop  , at      ,
			mutate , rotate  , unpad , replace , erase , insert ,
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
		using type = gcindex_type* const;

		enum Position : gkey_type
		{
			size = 0,
			name , note , pos , subname = pos , subnote , subpos , num ,
			dimension
		};

		nik_ces gindex_type length (type i) { return i[size]; }
	};

	using PI		= PraxisInstr;
	using instr_type	= typename PI::type;
	using cinstr_type	= instr_type const;

	template<auto... Vs>
	nik_ce instr_type instruction = array<gindex_type, sizeof...(Vs), Vs...>;

/***********************************************************************************************************************/

// controllers:

	struct PraxisContr
	{
		using type = cinstr_type* const;

		enum Position : gkey_type
		{
			size = 0,
			dimension
		};

		nik_ces gindex_type length (type c) { return c[size][PI::size]; }
	};

	using PC         = PraxisContr;
	using contr_type = typename PC::type;

	template<auto... Vs>
	nik_ce contr_type controller = array<instr_type, array<gindex_type, sizeof...(Vs)>, Vs...>;

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

			nik_ces auto instr(contr_type c, gcindex_type i) { return c[i]; }

		// navigators:

			nik_ces   gkey_type next_name  (contr_type c, gcindex_type i) { return c[i+1][PI::name]; }
			nik_ces   gkey_type next_note  (contr_type c, gcindex_type i) { return c[i+1][PI::note]; }
			nik_ces gindex_type next_index (              gcindex_type i) { return i+1; }
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

// select:

/***********************************************************************************************************************/

// 2^N:

	NIK_DEFINE_PRAXIS_ARGUMENT_SELECT(6)

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

	NIK_DEFINE_PRAXIS_ARGUMENT_DROP(6)

// id:

	template<auto... filler>
	struct T_praxis<Shape::argument, PN::drop, PT::id, filler...>
	{
		template<NIK_PRAX_ARG_PARAMS(c, i, l, Vs), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto ins	= PA::instr(c, i);
			nik_ce auto n   = ins[PI::pos];
			using T_cont    = T_praxis_arg<PN::drop, ins[PI::subnote]>;

			if constexpr (n == 0)

				return NIK_PRAX_ARG(c, i, l, Vs)(vs...);
			else
				return T_cont::template result<c, i, l, n-1, Vs...>(vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// at:

	// block:

		template<auto q, auto k, auto h, auto Note>
		nik_ce auto block_at_contr = controller
		<
			instruction < PN::pad  , PT::selector , q        >,
			instruction < PN::at   , PT::id       , k , Note >,
			instruction < PN::call , PT::arg      , h        >
		>;

	// recurse:

		template<auto m, auto q, auto k, auto h, auto Note>
		nik_ces auto recurse_at_contr = controller
		<
			instruction < PN::drop , PT::id       , m , Note >,
			instruction < PN::pad  , PT::selector , q        >,
			instruction < PN::at   , PT::id       , k , Note >,
			instruction < PN::call , PT::arg      , h        >
		>;

/***********************************************************************************************************************/

// id:

	template<auto... filler>
	struct T_praxis<Shape::argument, PN::at, PT::id, filler...>
	{
		template<NIK_PRAX_ARG_PARAMS(c, i, l, Vs), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto ins	= PA::instr(c, i);
			nik_ce auto k   = ins[PI::pos];
			nik_ce auto t   = ins[PI::subnote];
			using T_cont    = T_praxis_arg<PN::select, t, H_praxis_unit, k, _pack_null_, _pack_first_>;

			return T_cont::template result<c, i, l, Vs...>(vs...);
		}
	};

/***********************************************************************************************************************/

// block:

	template<auto cont = _first_, auto Note = PT::_2_6>
	struct T_arg_block_at
	{
		nik_ces auto _2_N = PT::_2_N_from_note(Note);
		nik_ces auto l    = U_pack_Vs<_at_, cont>;
		nik_ces auto h    = _zero;

		template<auto k, typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto q = conditional_padding(k, sizeof...(Ts), _2_N);
			nik_ce auto c = block_at_contr<q, k, h, Note>;

			return T_praxis_arg_select::template result<c, l>(vs...);
		}

	}; template<auto cont = _first_, auto Note = PT::_2_6>
		nik_ce auto _arg_block_at_ = U_custom_T<T_arg_block_at<cont, Note>>;

	// syntactic sugar:

		template<auto Note, auto k, auto cont, typename... Ts>
		nik_ce auto arg_block_at(Ts... vs) // needs to do its own bounds check now that it pads.
		{
			using T_cont = T_arg_block_at<cont, Note>;

			return T_cont::template result<k>(vs...);
		}

/***********************************************************************************************************************/

// recurse:

	template<auto cont = _first_, auto Note = PT::_2_6>
	struct T_arg_recurse_at
	{
		nik_ces auto _2_N = PT::_2_N_from_note(Note);
		nik_ces auto l    = U_pack_Vs<_at_, cont>;
		nik_ces auto h    = _zero;

		template<auto n, typename... Ts>
		nik_ces auto result(Ts... vs) // needs to do its own bounds check now that it pads.
		{
			nik_ce auto m = n / _2_N;
			nik_ce auto k = n % _2_N;
			nik_ce auto q = conditional_padding(n, sizeof...(Ts), _2_N);
			nik_ce auto c = recurse_at_contr<m, q, k, h, Note>;

			return T_praxis_arg_select::template result<c, l>(vs...);
		}

	}; template<auto cont = _first_, auto Note = PT::_2_6>
		nik_ce auto _arg_recurse_at_ = U_custom_T<T_arg_recurse_at<cont, Note>>;

	// syntactic sugar:

		template<auto Note, auto n, auto cont, typename... Ts>
		nik_ce auto arg_at(Ts... vs)
		{
			using T_cont = T_arg_recurse_at<cont, Note>;

			return T_cont::template result<n>(vs...);
		}

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// argument (mutate):

	// [...] b [...] e

/***********************************************************************************************************************/

// (start):

	struct T_praxis_arg_mutate
	{
		nik_ces auto i = PA::initial_index;

		template<auto s, auto c, auto l, auto... Vs, typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) -> T_store_U<s>
		{
			return NIK_PRAX_SARG(s, c, i, l, Vs)(v, vs...);
		}

	}; nik_ce auto U_praxis_arg_mutate = U_custom_T<T_praxis_arg_mutate>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// tail:

/***********************************************************************************************************************/

// arg:

	template<auto... filler>
	struct T_praxis<Shape::argument, PN::tail, PT::arg, filler...>
	{
		template<NIK_PRAX_ARG_SPARAMS(s, c, i, l, Vs), typename T, typename... Ts>
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

// mutate:

/***********************************************************************************************************************/

// 2^N:

	NIK_DEFINE_PRAXIS_ARGUMENT_MUTATE(6)

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// rotate:

/***********************************************************************************************************************/

// 2^N:

	NIK_DEFINE_PRAXIS_ARGUMENT_ROTATE(6)

// id:

	template<auto... filler>
	struct T_praxis<Shape::argument, PN::rotate, PT::id, filler...>
	{
		template<NIK_PRAX_ARG_SPARAMS(s, c, i, l, Vs), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) -> T_store_U<s>
		{
			nik_ce auto ins	= PA::instr(c, i);
			nik_ce auto n   = ins[PI::pos];
			using T_cont    = T_praxis_arg<PN::rotate, ins[PI::subnote]>;

			if constexpr (n == 0)

				return NIK_PRAX_SARG(s, c, i, l, Vs)(v, vs...);
			else
				return T_cont::template result<s, c, i, l, n-1, Vs...>(v, vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// pad:

/***********************************************************************************************************************/

// mutator:

	template<auto... Cs, nik_vp(U)(T_pack_Vs<Cs...>*)>
	struct T_praxis<Shape::argument, PN::pad, PT::mutator, U>
	{
		template<NIK_PRAX_ARG_SPARAMS(s, c, i, l, Vs), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) -> T_store_U<s>
			{ return NIK_PRAX_SARG(s, c, i, l, Vs)(v, vs..., Cs...); }
	};

	template<auto... filler>
	struct T_praxis<Shape::argument, PN::pad, PT::mutator, filler...>
	{
		template<NIK_PRAX_ARG_SPARAMS(s, c, i, l, Vs), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) -> T_store_U<s>
		{
			nik_ce auto ins  = PA::instr(c, i);
			nik_ce auto N    = ins[PI::pos];
			using T_cont     = T_praxis_arg<PN::pad, PT::mutator, padding<N>>;

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
		template<NIK_PRAX_ARG_SPARAMS(s, c, i, l, Vs), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) -> T_store_U<s>
		{
			nik_ce auto ins	= PA::instr(c, i);
			nik_ce auto j   = ins[PI::pos];
			nik_ce auto t   = ins[PI::subnote];
			using T_cont    = T_praxis_arg<PN::unpad, t, H_praxis_part, j, _pack_first_, _pack_null_>;

			if constexpr (j == 0)

				return NIK_PRAX_SARG(s, c, i, l, Vs)(v, vs...);
			else
				return T_cont::template result<s, c, i, l, Vs...>(v, vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// replace:

	// block:

		template<auto q, auto k, auto j, auto h, auto Note>
		nik_ce auto block_replace_contr = controller
		<
			instruction < PN::pad     , PT::mutator , q        >,
			instruction < PN::replace , PT::id      , k , Note >,
			instruction < PN::unpad   , PT::mutator , j , Note >,
			instruction < PN::tail    , PT::arg     , h        >
		>;

	// recurse:

		template<auto q, auto m0, auto k, auto m1, auto j, auto h, auto Note>
		nik_ce auto recurse_replace_contr = controller
		<
			instruction < PN::pad     , PT::mutator , q         >,
			instruction < PN::rotate  , PT::id      , m0 , Note >,
			instruction < PN::replace , PT::id      , k  , Note >,
			instruction < PN::rotate  , PT::id      , m1 , Note >,
			instruction < PN::unpad   , PT::mutator , j  , Note >,
			instruction < PN::tail    , PT::arg     , h         >
		>;

/***********************************************************************************************************************/

// id:

	template<auto... filler>
	struct T_praxis<Shape::argument, PN::replace, PT::id, filler...>
	{
		template<NIK_PRAX_ARG_SPARAMS(s, c, i, l, Vs), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) -> T_store_U<s>
		{
			nik_ce auto ins	= PA::instr(c, i);
			nik_ce auto k   = ins[PI::pos];
			nik_ce auto t   = ins[PI::subnote];
			using T_cont    = T_praxis_arg<PN::mutate, t, H_praxis_unit, k, _pack_first_, _pack_second_>;

			return T_cont::template result<s, c, i, l, Vs...>(v, vs...);
		}
	};

/***********************************************************************************************************************/

// block:

	template<auto cont, auto Note = PT::_2_6>
	struct T_arg_block_replace
	{
		nik_ces auto _2_N = PT::_2_N_from_note(Note);
		nik_ces auto l    = U_pack_Vs<_at_, cont>;
		nik_ces auto h    = _zero;

		template<auto s, auto k, auto... Vs, typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) -> T_store_U<s>
		{
			nik_ce auto q = required_padding(sizeof...(Ts), _2_N);
			nik_ce auto j = sizeof...(Ts) % _2_N;
			nik_ce auto c = block_replace_contr<q, k, j, h, Note>;

			return T_praxis_arg_mutate::template result<s, c, l, Vs...>(v, vs...);
		}

	}; template<auto cont, auto Note = PT::_2_6>
		nik_ce auto _arg_block_replace_ = U_custom_T<T_arg_block_replace<cont, Note>>;

	// syntactic sugar:

		template<auto s, auto Note, auto k, auto cont, auto... Vs, typename T, typename... Ts>
		nik_ce auto arg_block_replace(T v, Ts... vs) -> T_store_U<s> // needs to do its own bounds check now that it pads.
		{
			using T_cont = T_arg_block_replace<cont, Note>;

			return T_cont::template result<s, k, Vs...>(v, vs...);
		}

/***********************************************************************************************************************/

// recurse:

	template<auto cont, auto Note = PT::_2_6>
	struct T_arg_recurse_replace
	{
		nik_ces auto _2_N = PT::_2_N_from_note(Note);
		nik_ces auto l    = U_pack_Vs<_at_, cont>;
		nik_ces auto h    = _zero;

		template<auto s, auto n, auto... Vs, typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) -> T_store_U<s> // needs to do its own bounds check now that it pads.
		{
			nik_ce auto m0 = n / _2_N;
			nik_ce auto k  = n % _2_N;

			nik_ce auto e  = sizeof...(Ts) / _2_N;
			nik_ce auto j  = sizeof...(Ts) % _2_N;
			nik_ce auto m1 = (e + (j != 0)) - (m0 + 1);

			nik_ce auto q = required_padding(sizeof...(Ts), _2_N);
			nik_ce auto c = recurse_replace_contr<q, m0, k, m1, j, h, Note>;

			return T_praxis_arg_mutate::template result<s, c, l, Vs...>(v, vs...);
		}

	}; template<auto cont, auto Note = PT::_2_6>
		nik_ce auto _arg_recurse_replace_ = U_custom_T<T_arg_recurse_replace<cont, Note>>;

	// syntactic sugar:

		template<auto s, auto Note, auto n, auto cont, auto... Vs, typename T, typename... Ts>
		nik_ce auto arg_replace(T v, Ts... vs) -> T_store_U<s>
		{
			using T_cont = T_arg_recurse_replace<cont, Note>;

			return T_cont::template result<s, n, Vs...>(v, vs...);
		}

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

// parameter:

/***********************************************************************************************************************/

// dispatch:

	struct PraxisParameter
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
				if (d == 0)           return PN::halt;
				else if (m != PT::id) return PN::recall;
				else                  return c[i+1][PI::name];
			}

			nik_ces gkey_type next_note(gcdepth_type d, gckey_type m, contr_type c, gcindex_type i)
			{
				if (d == 0)           return PT::pause;
				else if (m != PT::id) return m;
				else                  return c[i+1][PI::note];
			}

			nik_ces gdepth_type next_depth(gcdepth_type d)
				{ return d - bool{d != 0}; }

			nik_ces gindex_type next_index(gcdepth_type d, gckey_type m, gcindex_type i)
				{ return i + bool{d != 0 && m == PT::id}; }
	};

	using PP = PraxisParameter;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

