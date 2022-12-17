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
			select , pad     , drop  , at      ,
			mutate , rotate  , unpad , replace , erase , insert ,
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
			selector , mutator ,
			_2_0 , _2_1 , _2_2 , _2_3 , _2_4 , _2_5 , _2_6 , _2_7 , _2_8 , _2_9 ,
			dimension
		};

		nik_ces gindex_type _2_N_from_note(gkey_type n) { return array_2_N[n - _2_0]; }
	};

	using PT = PraxisNote;

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

// argument (select):

	// select and mutate differ by the ability to auto deduce the function type.

/***********************************************************************************************************************/

// 2^N:

	NIK_DEFINE_PRAXIS_ARGUMENT_SELECT(6)

	template<auto Note, auto... Vs>
	nik_ce auto _arg_select_ = U_praxis_arg<PN::select, Note, Vs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// pad:

/***********************************************************************************************************************/

// selector:

	template<auto... Cs, nik_vp(p)(T_pack_Vs<Cs...>*)>
	struct T_praxis<Shape::argument, PN::pad, PT::selector, p>
	{
		template<auto cont, auto... Vs, typename... Ts>
		nik_ces auto result(Ts... vs) { return T_store_U<cont>::template result<Vs...>(vs..., Cs...); }

	}; template<auto N>
		nik_ce auto _arg_pad_selector_ = U_praxis_arg<PN::pad, PT::selector, padding<N>>;

// 2^N:

	template<gkey_type Note>
	struct T_praxis<Shape::argument, PN::pad, Note>
	{
		nik_ces auto _2_N = PT::_2_N_from_note(Note);

		template<auto... Vs, typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto Size = sizeof...(Ts);
			nik_ce auto o    = (Size > _2_N) ? _2_N : Size;
			nik_ce auto p    = _2_N - o;
			using T_cont     = T_store_U<_arg_pad_selector_<p>>;

			return T_cont::template result<Vs...>(vs...);
		}

	}; template<auto Note = PT::_2_6>
		nik_ce auto _arg_pad_2_N_ = U_praxis_arg<PN::pad, Note>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// drop:

/***********************************************************************************************************************/

// 2^N:

	NIK_DEFINE_PRAXIS_ARGUMENT_DROP(6)

// id:

	template<auto Note>
	struct T_praxis<Shape::argument, PN::drop, PT::id, Note>
	{
		using T_this = T_praxis_arg<PN::drop, Note>;

		template<auto n, auto cont, auto... Vs, typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			using T_cont = T_store_U<cont>;

			if constexpr (n == 0) return T_cont::template result<Vs...>(vs...);
			else return T_this::template result<n-1, cont, Vs...>(vs...);
		}

	}; template<auto Note = PT::_2_6>
		nik_ce auto _arg_drop_ = U_praxis_arg<PN::drop, PT::id, Note>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// at:

	template<gindex_type k, auto Note = PT::_2_6>
	nik_ce auto _arg_select_at_ = _arg_select_<Note, H_praxis_unit, k, _pack_null_, _pack_first_>;

/***********************************************************************************************************************/

// 2^N:

	template<gkey_type Note>
	struct T_praxis<Shape::argument, PN::at, Note>
	{
		using T_cont = T_store_U<_arg_pad_2_N_<Note>>;

		template<auto k, auto... Vs, typename... Ts>
		nik_ces auto result(Ts... vs)
			{ return T_cont::template result<_arg_select_at_<k, Note>, Vs...>(vs...); }

	}; template<auto Note = PT::_2_6>
		nik_ce auto _arg_at_2_N_ = U_praxis_arg<PN::at, Note>;

	// syntactic sugar:

		template<auto Note, auto k, typename... Ts>
		nik_ce auto _2_N_at(Ts... vs) // needs to do its own bounds check now that it pads.
		{
			using T_cont = T_store_U<_arg_at_2_N_<Note>>;

			return T_cont::template result<k, _first_>(vs...);
		}

/***********************************************************************************************************************/

// id:

	template<auto Note>
	struct T_praxis<Shape::argument, PN::at, PT::id, Note>
	{
		nik_ces auto _2_N = PT::_2_N_from_note(Note);
		using T_cont      = T_store_U<_arg_drop_<Note>>;

		template<auto n, auto... Vs, typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto m = n / _2_N;
			nik_ce auto k = n % _2_N;

			return T_cont::template result<m, _arg_at_2_N_<Note>, k, Vs...>(vs...);
		}

	}; template<auto Note = PT::_2_6>
		nik_ce auto _arg_at_ = U_praxis_arg<PN::at, PT::id, Note>;

	// syntactic sugar:

		template<auto Note, auto n, typename... Ts>
		nik_ce auto at(Ts... vs) // needs to do its own bounds check now that it pads.
		{
			using T_cont = T_store_U<_arg_at_<Note>>;

			return T_cont::template result<n, _first_>(vs...);
		}

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// argument (mutate):

	// [...] b [...] e

/***********************************************************************************************************************/

// 2^N:

	NIK_DEFINE_PRAXIS_ARGUMENT_MUTATE(6)

	template<auto Note, auto... Vs>
	nik_ce auto _arg_mutate_ = U_praxis_arg<PN::mutate, Note, Vs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// rotate:

/***********************************************************************************************************************/

// 2^N:

	NIK_DEFINE_PRAXIS_ARGUMENT_ROTATE(6)

// id:

	template<auto Note>
	struct T_praxis<Shape::argument, PN::rotate, PT::id, Note>
	{
		using T_this = T_praxis_arg<PN::rotate, Note>;

		template<auto s, auto n, auto cont, auto... Vs, typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) -> T_store_U<s>
		{
			using T_cont = T_store_U<cont>;

			if constexpr (n == 0) return T_cont::template result<s, Vs...>(v, vs...);
			else return T_this::template result<s, n-1, cont, Vs...>(v, vs...);
		}

	}; template<auto Note = PT::_2_6>
		nik_ce auto _arg_rotate_ = U_praxis_arg<PN::rotate, PT::id, Note>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// pad:

/***********************************************************************************************************************/

// mutator:

	template<auto... Cs, nik_vp(p)(T_pack_Vs<Cs...>*)>
	struct T_praxis<Shape::argument, PN::pad, PT::mutator, p>
	{
		template<auto s, auto cont, auto... Vs, typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) -> T_store_U<s>
			{ return T_store_U<cont>::template result<s, Vs...>(v, vs..., Cs...); }

	}; template<auto N>
		nik_ce auto _arg_pad_mutator_ = U_praxis_arg<PN::pad, PT::mutator, padding<N, 0>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// unpad:

/***********************************************************************************************************************/

// 2^N:

	NIK_DEFINE_PRAXIS_ARGUMENT_UNPAD(6)

	template<gindex_type j, auto Note = PT::_2_6>
	nik_ce auto _arg_unpad_2_N_ = U_praxis_arg<PN::unpad, Note, H_praxis_part, j, _pack_first_, _pack_null_>;

// id:

	template<auto Note>
	struct T_praxis<Shape::argument, PN::unpad, PT::id, Note>
	{
		template<auto s, auto j, auto cont, auto... Vs, typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) -> T_store_U<s>
		{
			using T_this = T_store_U<_arg_unpad_2_N_<j, Note>>;
			using T_cont = T_store_U<cont>;

			if constexpr (j == 0) return T_cont::template result<s, Vs...>(v, vs...);
			else return T_this::template result<s, cont, Vs...>(v, vs...);
		}

	}; template<auto Note = PT::_2_6>
		nik_ce auto _arg_unpad_ = U_praxis_arg<PN::unpad, PT::id, Note>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// replace:

	template<gindex_type k, auto Note = PT::_2_6>
	nik_ce auto _arg_mutate_replace_ = _arg_mutate_<Note, H_praxis_unit, k, _pack_first_, _pack_second_>;

/***********************************************************************************************************************/

// 2^N:

	template<gkey_type Note>
	struct T_praxis<Shape::argument, PN::replace, Note>
	{
		nik_ces auto rotate  = _arg_rotate_<Note>;
		nik_ces auto unpad   = _arg_unpad_<Note>;

		template<auto s, auto k, auto m1, auto j, auto... Vs, typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) -> T_store_U<s>
		{
			using T_cont = T_store_U<_arg_mutate_replace_<k, Note>>;

			return T_cont::template result<s, rotate, m1, unpad, j, Vs...>(v, vs...);
		}

	}; template<auto Note = PT::_2_6>
		nik_ce auto _arg_replace_2_N_ = U_praxis_arg<PN::replace, Note>;

	// syntactic sugar:

		template<typename S, auto Note, auto k, auto m1, auto j, auto cont, auto... Vs, typename... Ts>
		nik_ce auto _2_N_replace(Ts... vs) -> S // needs to do its own bounds check now that it pads.
		{
			nik_ce auto s = U_store_T<S>;
			using T_cont  = T_store_U<_arg_replace_2_N_<Note>>;

			return T_cont::template result<s, k, m1, j, cont, Vs...>(vs...);
		}

/***********************************************************************************************************************/

// id:

	template<auto Note>
	struct T_praxis<Shape::argument, PN::replace, PT::id, Note>
	{
		nik_ces auto _2_N    = PT::_2_N_from_note(Note);
		nik_ces auto rotate  = _arg_rotate_<Note>;
		nik_ces auto replace = _arg_replace_2_N_<Note>;

		template<auto s, auto n, auto... Vs, typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) -> T_store_U<s>
		{
			nik_ce auto m0 = n / _2_N;
			nik_ce auto k  = n % _2_N;

			nik_ce auto e  = sizeof...(Ts) / _2_N;
			nik_ce auto j0 = sizeof...(Ts) % _2_N;
			nik_ce auto m1 = (e + (j0 != 0)) - (m0 + 1);

			nik_ce auto j  = (j0 == 0) ? _2_N : j0;
			nik_ce auto p  = _2_N - j;
			using T_cont   = T_store_U<_arg_pad_mutator_<p>>;

			return T_cont::template result<s, rotate, m0, replace, k, m1, j0, Vs...>(v, vs...);
		}

	}; template<auto Note = PT::_2_6>
		nik_ce auto _arg_replace_ = U_praxis_arg<PN::replace, PT::id, Note>;

	// syntactic sugar:

		template<typename S, auto Note, auto n, auto cont, auto... Vs, typename... Ts>
		nik_ce auto replace(Ts... vs) -> S // needs to do its own bounds check now that it pads.
		{
			nik_ce auto s = U_store_T<S>;
			using T_cont  = T_store_U<_arg_replace_<Note>>;

			return T_cont::template result<s, n, cont, Vs...>(vs...);
		}

/***********************************************************************************************************************/

	template<auto cont>
	struct Manual
	{
		template<auto s, auto... Vs, typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) -> T_store_U<s>
		{
			using T_cont = T_store_U<cont>;

			return T_cont::template result<Vs...>(vs...);
		}

	}; template<auto cont>
		nik_ce auto _manual_ = U_store_T<Manual<cont>>;

		template<auto n, typename T, typename... Ts>
		nik_ce auto repl(T v, Ts... vs)
		{
		//	return replace<int, PT::_2_6, n, _manual_<_first_>>(v, vs...);
			return replace<tuple<Ts...>, PT::_2_6, n, _manual_<_to_tuple_>>(v, vs...);
		}

/***********************************************************************************************************************/

// tuple:

	template<typename... Ts>
	nik_ce auto print_tuple(const tuple<Ts...> & t)
	{
		if constexpr (sizeof...(Ts) == 0) printf("\n");
		else
		{
			printf("%d, ", t.value);

			print_tuple(t.rest);
		}
	}

// segment:

	template<auto n, auto... Vs>
	nik_ce auto _segment()
	{
		if constexpr (n == 0) return U_pack_Vs<n, Vs...>;
		else                  return _segment<n-1, n, Vs...>();
	}

	template<auto n>
	nik_ce auto segment = _segment<n>();

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// parameter:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// dispatch:

	struct PraxisDisp
	{
		// defaults:

			nik_ces gindex_type initial_index = _zero;

		// accessors:

		//	nik_ces auto instr(ccontr_type c, gcindex_type i) { return c[i]; }

		// navigators:

			// argument:

		//	nik_ces   gkey_type next_name  (ccontr_type c, gcindex_type i) { return c[i+1][PI::name]; }
		//	nik_ces   gkey_type next_note  (ccontr_type c, gcindex_type i) { return c[i+1][PI::note]; }
		//	nik_ces gindex_type next_index (ccontr_type  , gcindex_type i) { return i + 1; }

			// parameter:
	};

	using PD = PraxisDisp;

/***********************************************************************************************************************/

// :

/***********************************************************************************************************************/

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

