/************************************************************************************************************************
**
** Copyright 2021-2022 Daniel Nikpayuk, Inuit Nunangat, The Inuit Nation
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

// generic assembly:

namespace cctmp_generics {

// cctmp:

	using key_type						= typename cctmp::key_type;
	using index_type					= typename cctmp::index_type;

	nik_ce auto _zero					= cctmp::_zero;
	nik_ce auto _one					= cctmp::_one;

	template<auto U> using T_store_U			= typename cctmp::template T_store_U<U>;
	template<auto... Vs> using T_pack_Vs			= typename cctmp::template T_pack_Vs<Vs...>;

	template<typename T> nik_ce auto U_store_T		= cctmp::template U_store_T<T>;
	template<typename T> nik_ce auto U_restore_T		= cctmp::template U_restore_T<T>;
	template<typename... Ts> nik_ce auto U_pack_Ts		= cctmp::template U_pack_Ts<Ts...>;
	template<auto... Vs> nik_ce auto U_pack_Vs		= cctmp::template U_pack_Vs<Vs...>;

	nik_ce auto U_null_Vs					= cctmp::U_null_Vs;

	template<typename T, auto... Vs> nik_ce auto array	= cctmp::template array<T, Vs...>;

	template<auto V> using T_out_type			= typename cctmp::template T_out_type<V>;
	template<auto V> nik_ce auto in_types			= cctmp::template in_types<V>;

	nik_ce auto H_id					= cctmp::H_id;

	template<auto... Vs> nik_ce auto overload		= cctmp::template overload<Vs...>;
	template<auto... Vs> nik_ce auto U_alias		= cctmp::template U_alias<Vs...>;

	nik_ce auto _id_					= cctmp::_id_;

	template<auto V> nik_ce auto _constant_			= cctmp::template _constant_<V>;
	template<auto f> nik_ce auto _apply_			= cctmp::template _apply_<f>;
	template<auto... Vs> nik_ce auto _bind_			= cctmp::template _bind_<Vs...>;

	nik_ce auto _same_					= cctmp::_same_;
	nik_ce auto _is_int_type_				= cctmp::_is_int_type_;
	nik_ce auto _not_int_type_				= cctmp::_not_int_type_;
	nik_ce auto _length_					= cctmp::_length_;
	nik_ce auto _car_					= cctmp::_car_;
	nik_ce auto _map_					= cctmp::_map_;
	nik_ce auto _find_					= cctmp::_find_;
	nik_ce auto _zip_					= cctmp::_zip_;
	nik_ce auto _cons_					= cctmp::_cons_;
	nik_ce auto _push_					= cctmp::_push_;
	nik_ce auto _unite_					= cctmp::_unite_;

	template<auto... Vs> nik_ce auto unpack_		= cctmp::template unpack_<Vs...>;
	template<auto... Vs> nik_ce auto find_			= cctmp::template find_<Vs...>;

	using T_block_argument					= typename cctmp::T_block_argument;

// functional:

	template<auto... Vs> nik_ce auto list_at		= cctmp_functional::template list_at<Vs...>;
	template<auto... Vs> nik_ce auto list_split		= cctmp_functional::template list_split<Vs...>;

	template<auto... Vs> nik_ce auto segment		= cctmp_functional::template segment<Vs...>;

	template<auto... Vs> nik_ce auto pack_parse		= cctmp_functional::template pack_parse<Vs...>;

	template<auto... Vs> nik_ce auto list_replace		= cctmp_functional::template list_replace<Vs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// conveniences:

/***********************************************************************************************************************/

// type at:

	template<index_type n, typename... Ts>
	using type_at = T_store_U<cctmp_functional::pack_at<n, U_store_T<Ts>...>>;

// same:

	template<auto V0, auto V1>
	nik_ce auto same = overload<_same_, V0, V1>;

// has int type:

	template<auto V>
	nik_ce auto has_int_type = overload<_is_int_type_, U_store_T<decltype(V)>>;

// length:

	template<auto p>
	nik_ce auto length = unpack_<p, _length_>;

// car:

	template<auto p>
	nik_ce auto car = unpack_<p, _car_>;

// cons:

	template<auto p, auto... Vs>
	nik_ce auto cons = overload<_cons_, H_id, p, Vs...>;

// push:

	template<auto p, auto... Vs>
	nik_ce auto push = overload<_push_, H_id, p, Vs...>;

// unite:

	template<auto p0, auto p1, auto... Vs>
	nik_ce auto unite = overload<_unite_, H_id, p0, p1, Vs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// functions:

/***********************************************************************************************************************/

// compose:

/***********************************************************************************************************************/

// arguments:

	// f_args:

		template<auto f, auto n, typename... Ts>
		nik_ce auto f_args = T_store_U<f>::template result<type_at<n, Ts...>>;

		template<auto f, auto... ns, nik_vp(p)(T_pack_Vs<ns...>*), typename... Ts>
		nik_ce auto f_args<f, p, Ts...> = T_store_U<f>::template result<type_at<ns, Ts...>...>;

	// out_type:

		template<auto f, auto on, typename... Ts>
		using f_args_out_type = T_out_type<f_args<f, on, Ts...>>;

	// block_arg:

		template<auto d, auto n, typename... Ts>
		nik_ce auto block_arg = T_block_argument::template result<d, n, Ts...>;

/***********************************************************************************************************************/

// subapply:

		// The trailing return type is necessary to preserve references and qualifiers.

	template<auto f, auto n, auto d = 500>
	struct T_subapply
	{
		template<typename... Ts>
		nik_ces auto result(Ts... vs) -> f_args_out_type<f, n, Ts...>
			{ return f_args<f, n, Ts...>(block_arg<d, n, Ts...>(vs...)); }
	};

	template<auto n, auto d>
	struct T_subapply<_id_, n, d>
	{
		template<typename... Ts>
		nik_ces auto result(Ts... vs) { return block_arg<d, n, Ts...>(vs...); }
	};

	template<auto f, auto... ns, nik_vp(p)(T_pack_Vs<ns...>*), auto d>
	struct T_subapply<f, p, d>
	{
		template<typename... Ts>
		nik_ces auto result(Ts... vs) -> f_args_out_type<f, p, Ts...>
			{ return f_args<f, p, Ts...>(block_arg<d, ns, Ts...>(vs...)...); }
	};

	// value:

		template<auto n, auto f = _id_, auto d = 500>
		nik_ce auto _value_ = U_store_T<T_subapply<f, n, d>>;

	// return:

		nik_ce auto _return_ = _value_<_zero>;

/***********************************************************************************************************************/

// allot:

	template<auto l, auto r, auto f> struct T_allot;

	template
	<
		auto... l_ns, nik_vp(l)(T_pack_Vs<l_ns...>*),
		auto... r_ns, nik_vp(r)(T_pack_Vs<r_ns...>*),
		auto f
	>
	struct T_allot<l, r, f>
	{
		template<typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs)
		{
			return T_store_U<f>::template result
			<
				type_at<l_ns, Ts...>...,
				T,
				type_at<r_ns, Ts...>...
			>
			(
				T_subapply<_id_, l_ns>::template result<Ts...>(vs...)...,
				v,
				T_subapply<_id_, r_ns>::template result<Ts...>(vs...)...
			);
		}

	}; template<auto l, auto r, auto f>
		nik_ce auto _allot_ = U_store_T<T_allot<l, r, f>>;

	// Normalizes the grammatical form for various kinds of function calls.
	// All function calls following are assumed to have the normal form
	// unless stated otherwise. With that said, labels are assumed
	// to be fully declared.

/***********************************************************************************************************************/

// subcompose:

	template<auto f, auto f_ns_p, auto ons_p> struct T_subcompose;

	template
	<
		auto f,
		auto... f_ns, nik_vp(f_ns_p)(T_pack_Vs<f_ns...>*),
		auto... ons, nik_vp(ons_p)(T_pack_Vs<ons...>*)
	>
	struct T_subcompose<f, f_ns_p, ons_p>
	{
		template<typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			return T_store_U<f>::template result
			<
				f_args_out_type<f_ns, ons, Ts...>...

			>(T_subapply<f_ns, ons>::template result<Ts...>(vs...)...);
		}

	}; template<auto f, auto f_ns_p, auto ons_p>
		nik_ce auto _subcompose_ = U_store_T<T_subcompose<f, f_ns_p, ons_p>>;

	// arg:

		template<auto op, auto... fs>
		nik_ce auto _argcompose_ = _subcompose_<op, U_pack_Vs<fs...>, segment<sizeof...(fs)>>;

/***********************************************************************************************************************/

// tuple apply:

//	template<auto f, typename T, typename... Ts, index_type... tuple_indices>
//	constexpr auto tuple_apply(const tuple<T, Ts...> & t, nik_vp(pack)(T_pack_Vs<tuple_indices...>*))
//	{
//		return f(tuple_value<tuple_indices>(t)...);
//	}

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// instructions:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// go to:

/***********************************************************************************************************************/

	template<auto lbl>
	nik_ce auto _go_to_ = _apply_<lbl>;

	template<auto lbl> struct _go_to { };

	template<auto lbl>
	nik_ce auto go_to = U_store_T<_go_to<lbl>>;

	// is go to:

		template<auto>
		nik_ce bool is_go_to = false;

		template<auto lbl, nik_vp(p)(_go_to<lbl>*)>
		nik_ce bool is_go_to<p> = true;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// branch:

/***********************************************************************************************************************/

	template<auto lbl>
	struct T_branch
	{
		template<auto pass, typename BoolType, typename... Ts>
		nik_ces auto result(BoolType cond, Ts... vs)
		{
			if (cond) return lbl(vs...);
			else      return T_store_U<pass>::template result<Ts...>(vs...);
		}

	}; template<auto lbl>
		nik_ce auto _branch_ = U_store_T<T_branch<lbl>>;

	template<auto lbl> struct _branch { };

	template<auto lbl>
	nik_ce auto branch = U_store_T<_branch<lbl>>;

	// is branch:

		template<auto>
		nik_ce bool is_branch = false;

		template<auto lbl, nik_vp(p)(_branch<lbl>*)>
		nik_ce bool is_branch<p> = true;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// label:

/***********************************************************************************************************************/

	template<auto lbl> struct _label { };

	template<auto lbl>
	nik_ce auto label = U_store_T<_label<lbl>>;

	// is label:

		template<auto>
		nik_ce bool is_label = false;

		template<auto lbl, nik_vp(p)(_label<lbl>*)>
		nik_ce bool is_label<p> = true;

	// label value:

		template<auto v>
		nik_ce auto label_value = v;

		template<auto lbl, nik_vp(p)(_go_to<lbl>*)>
		nik_ce auto label_value<p> = lbl;

		template<auto lbl, nik_vp(p)(_branch<lbl>*)>
		nik_ce auto label_value<p> = lbl;

		template<auto lbl, nik_vp(p)(_label<lbl>*)>
		nik_ce auto label_value<p> = lbl;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// side:

/***********************************************************************************************************************/

	template<auto f> struct _side { };

	template<auto f>
	nik_ce auto _side_ = U_store_T<_side<f>>;

	// is side:

		template<auto>
		nik_ce bool is_side = false;

		template<auto f, nik_vp(p)(_side<f>*)>
		nik_ce bool is_side<p> = true;

	// side value:

		template<auto v>
		nik_ce auto side_value = v;

		template<auto f, nik_vp(p)(_side<f>*)>
		nik_ce auto side_value<p> = f;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// lift:

	template<auto...> struct T_lift { };

/***********************************************************************************************************************/

// name:

	struct LiftName
	{
		nik_ces key_type effect		= 0;
		nik_ces key_type copy		= 1;
		nik_ces key_type mutate		= 2;
	};

	using FN		= LiftName;

	nik_ce auto U_effect	= U_pack_Vs<FN::effect>;
	nik_ce auto U_copy	= U_pack_Vs<FN::copy>;

	template<auto m>
	nik_ce auto U_mutate	= U_pack_Vs<FN::mutate, m>;

/***********************************************************************************************************************/

// is lift:

	template<auto>
	nik_ce bool is_lift = false;

	template<auto... Vs, nik_vp(p)(T_lift<Vs...>*)>
	nik_ce bool is_lift<p> = true;

/***********************************************************************************************************************/

// options:

	nik_ce void _cp_ () { } // copy
	nik_ce void _ps_ () { } // paste

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// specializations:

	// Total (register) assignment in this context is equivalent to replacing the continuation's given argument.
	// Partial assignment is then achieved through the side effect of the given instruction.

/***********************************************************************************************************************/

// id:

	nik_ce auto _lifted_id_ = U_store_T<T_lift<>>;

/***********************************************************************************************************************/

// (side) effect:

	// sign:

		template<auto f>
		struct T_lift<FN::effect, f, true>
		{
			template<auto pass, typename... Ts>
			nik_ces auto result(Ts... vs)
			{
				T_store_U<f>::template result<Ts...>(vs...);

				return T_store_U<pass>::template result<Ts...>(vs...);
			}
		};

	// paste:

		template<auto f>
		struct T_lift<FN::effect, f, false>
		{
			template<auto pass, typename T, typename... Ts>
			nik_ces auto result(T v, Ts... vs)
			{
				T_store_U<f>::template result<T, Ts...>(v, vs...);

				return T_store_U<pass>::template result<Ts...>(vs...);
			}
		};

/***********************************************************************************************************************/

// copy:

	// sign:

		template<auto f>
		struct T_lift<FN::copy, f, true>
		{
			template<auto pass, typename... Ts>
			nik_ces auto result(Ts... vs)
			{
				auto val = T_store_U<f>::template result<Ts...>(vs...);

				return T_store_U<pass>::template result<decltype(val), Ts...>(val, vs...);
			}
		};

	// paste:

		template<auto f>
		struct T_lift<FN::copy, f, false>
		{
			template<auto pass, typename T, typename... Ts>
			nik_ces auto result(T v, Ts... vs)
			{
				auto val = T_store_U<f>::template result<T, Ts...>(v, vs...);

				return T_store_U<pass>::template result<decltype(val), Ts...>(val, vs...);
			}
		};

/***********************************************************************************************************************/

// mutate:

	// sign:

		template<auto m, auto f>
		struct T_lift<FN::mutate, m, f, true>
		{
			nik_ces auto l = segment<m>;
			nik_ces auto n = m + _one;

			template<auto pass, typename... Ts>
			nik_ces auto result(Ts... vs)
			{
				nik_ce auto r = segment<sizeof...(Ts)-n, n>;

				auto val      = T_store_U<f>::template result<Ts...>(vs...);

				return T_allot<l, r, pass>::template result<decltype(val), Ts...>(val, vs...);
			}
		};

	// paste:

		template<auto m, auto f>
		struct T_lift<FN::mutate, m, f, false>
		{
			nik_ces auto l = segment<m>;
			nik_ces auto n = m + _one;

			template<auto pass, typename T, typename... Ts>
			nik_ces auto result(T v, Ts... vs)
			{
				nik_ce auto r = segment<sizeof...(Ts)-n, n>;

				auto val      = T_store_U<f>::template result<T, Ts...>(v, vs...);

				return T_allot<l, r, pass>::template result<decltype(val), Ts...>(val, vs...);
			}
		};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// dispatch:

/***********************************************************************************************************************/

	struct LiftDispatch
	{
		template<auto... ns>
		nik_ces auto find_non_int = find_<_not_int_type_, U_store_T<decltype(ns)>...>;

		template<auto p, auto... ns>
		nik_ces auto is_all_ints = (p == sizeof...(ns));

		template<auto V>
		nik_ces index_type map_index()
		{
			if nik_ce (has_int_type<V>) return V + _one;
			else return _zero;
		}

		template<bool all_ints, auto... ns>
		nik_ces auto index_list()
		{
			if nik_ce (all_ints) return U_pack_Vs<index_type{ns}...>;
			else                 return U_pack_Vs<map_index<ns>()...>;
		}

		template<auto f, auto... ns, auto name, auto... ms>
		nik_ces auto result(nik_avp(T_pack_Vs<name, ms...>*))
		{
			if nik_ce (same<f, _id_>) return _lifted_id_;
			else
			{
				nik_ce auto p		= find_non_int<ns...>;
				nik_ce auto all_ints	= is_all_ints<p, ns...>;

				nik_ce auto f_ns_p	= U_pack_Vs<overload<_constant_<_id_>, ns>...>;
				nik_ce auto ns_p	= index_list<all_ints, ns...>();
				nik_ce auto nf		= _subcompose_<f, f_ns_p, ns_p>;

				using T_dispatched_lift = T_lift<name, ms..., nf, all_ints>;

				return U_store_T<T_dispatched_lift>;
			}
		}
	};

	using FD = LiftDispatch;

	// lift:

		template<auto m, auto f, auto... ns>
		nik_ce auto _lift_maybe()
		{
			if nik_ce (is_side<f>) return FD::template result<side_value<f>, m, ns...>(U_effect);
			else                   return FD::template result<f, ns...>(U_mutate<m>);
		}

		template<auto V, auto... Vs>
		nik_ce auto _lift()
		{
			if      nik_ce (same<V, _cp_>)    return FD::template result<Vs...>(U_copy);
			else if nik_ce (!has_int_type<V>) return FD::template result<V, Vs...>(U_effect);
			else                              return _lift_maybe<V, Vs...>();
		}

		template<auto... Vs>
		nik_ce auto lift = _lift<Vs...>();

	// test:

		template<auto p, auto... ns>
		nik_ce auto test = FD::template result<p, ns...>(U_copy);

	// tacit:

		template<auto f>
		nik_ce auto tacit = FD::template result<f, _ps_>(U_copy);

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// endoposition:

/***********************************************************************************************************************/

// endopose:

	template<typename F, typename G>
	struct _endopose
	{
		nik_ces auto g = U_store_T<G>;

		template<auto pass, typename... Ts>
		nik_ces auto result(Ts... vs) { return F::template result<_bind_<g, pass>, Ts...>(vs...); }
	};

	struct T_endopose
	{
		template<auto f, auto g>
		nik_ces auto result = U_store_T<_endopose<T_store_U<f>, T_store_U<g>>>;

	}; nik_ce auto U_endopose = U_store_T<T_endopose>;

	template<auto g>
	nik_ce auto T_endopose::result<_lifted_id_, g> = g;

	template<auto f>
	nik_ce auto T_endopose::result<f, _lifted_id_> = f;

	template<>
	nik_ce auto T_endopose::result<_lifted_id_, _lifted_id_> = _lifted_id_;

// endofold:

	struct T_endofold
	{
		template<auto... Vs>
		nik_ces auto result = cctmp_functional::pack_fold<U_endopose, _lifted_id_, Vs...>;

	}; nik_ce auto U_endofold = U_store_T<T_endofold>;

// endodrop:

	template<typename... Ts>
	nik_ce auto signature = U_pack_Ts<Ts...>;

	// implemented this way as gcc complains about ambiguous matches.

	struct T_endodrop
	{
		template<auto p, auto... UTs>
		nik_ces auto _result(nik_avp(T_pack_Vs<UTs...>*))
		{
			nik_ce auto size = length<p>;

			if nik_ce (size == _zero) return T_store_U<_id_>::template result<T_store_U<UTs>...>;
			else
			{
				nik_ce auto s    = list_split<p, size-1>;
				nik_ce auto l    = cctmp::tuple_value<0>(s);
				nik_ce auto r    = cctmp::tuple_value<1>(s);
				nik_ce auto f    = unpack_<l, U_endofold>;
				nik_ce auto halt = car<r>;

				if nik_ce (same<f, _lifted_id_>) return T_store_U<halt>::template result<T_store_U<UTs>...>;
				else                             return T_store_U<f>::template result<halt, T_store_U<UTs>...>;
			}
		}

		template<auto s, auto p>
		nik_ces auto result = _result<p>(s);

	}; nik_ce auto U_endodrop = U_store_T<T_endodrop>;

	template<auto s, auto... fs>
	nik_ce auto endodrop = T_endodrop::template result<s, U_pack_Vs<fs...>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// parse:

/***********************************************************************************************************************/

// state:

	struct ParseState
	{
		nik_ces key_type labels				= 0;
		nik_ces key_type lines				= 1;
		nik_ces key_type words				= 2;
		nik_ces key_type chars				= 3;
		nik_ces key_type graph				= 4;
		nik_ces key_type verts				= 5;
	};

	using PS = ParseState;

/***********************************************************************************************************************/

// dispatch:

	struct ParseDispatch
	{
		nik_ces key_type name				= 0;
		nik_ces key_type note				= 1;

		nik_ces key_type rest_is_empty			= 0;
		nik_ces key_type is_before_label		= 1;
		nik_ces key_type not_before_label		= 2;

		nik_ces key_type label				= 0;
		nik_ces key_type branch				= 1;
		nik_ces key_type go_to				= 2;
		nik_ces key_type lift				= 3;
		nik_ces key_type drop				= 4;
	};

	using PD = ParseDispatch;

/***********************************************************************************************************************/

// mutators:

	template<key_type, key_type...> struct Parse;

	template<key_type... filler>
	struct Parse<PD::label, filler...>
	{
		template<auto instr0, typename State>
		nik_ces auto result(State)
		{
			nik_ce auto state   = U_restore_T<State>;
			nik_ce auto labels  = list_at<state, PS::labels>;

			nik_ce auto lbl     = label_value<instr0>;
			nik_ce auto nlabels = push<labels, lbl>; // error if already exists.
			nik_ce auto nstate  = list_replace<state, PS::labels, nlabels>;

			return nstate;
		}
	};

	template<key_type... filler>
	struct Parse<PD::branch, filler...>
	{
		template<auto instr0, auto labels, auto lines, auto words, auto chars, auto graph, auto verts>
		nik_ces auto result(nik_vp(state)(T_pack_Vs<labels, lines, words, chars, graph, verts>*))
		{
			nik_ce auto lbl    = label_value<instr0>;
			nik_ce auto nverts = push<verts, lbl>;

			nik_ce auto nword  = unpack_<chars, U_endofold>;
			nik_ce auto nwords = push<words, nword>;

			nik_ce auto nstate = U_pack_Vs<labels, lines, nwords, U_null_Vs, graph, nverts>;

			return nstate;
		}
	};

	template<key_type... filler>
	struct Parse<PD::go_to, filler...>
	{
		template<auto instr0, auto labels, auto lines, auto words, auto chars, auto graph, auto verts>
		nik_ces auto result(nik_vp(state)(T_pack_Vs<labels, lines, words, chars, graph, verts>*))
		{
			nik_ce auto lbl    = label_value<instr0>;
			nik_ce auto nverts = push<verts, lbl>;
			nik_ce auto ngraph = push<graph, nverts>;

			nik_ce auto nword  = unpack_<chars, U_endofold>;
			nik_ce auto nwords = push<words, nword>;
			nik_ce auto nlines = push<lines, nwords>;

			nik_ce auto nstate = U_pack_Vs<labels, nlines, U_null_Vs, U_null_Vs, ngraph, U_null_Vs>;

			return nstate;
		}
	};

	template<key_type... filler>
	struct Parse<PD::lift, filler...>
	{
		template<auto instr0, typename State>
		nik_ces auto result(State)
		{
			nik_ce auto state  = U_restore_T<State>;
			nik_ce auto chars  = list_at<state, PS::chars>;

			nik_ce auto nchars = push<chars, instr0>;
			nik_ce auto nstate = list_replace<state, PS::chars, nchars>;

			return nstate;
		}
	};

	template<key_type... filler>
	struct Parse<PD::drop, filler...>
	{
		template<auto instr0, auto labels, auto lines, auto words, auto chars, auto graph, auto verts>
		nik_ces auto result(nik_vp(state)(T_pack_Vs<labels, lines, words, chars, graph, verts>*))
		{
			nik_ce auto ngraph = push<graph, verts>;

			nik_ce auto nword  = unpack_<chars, U_endofold>;
			nik_ce auto nwords = push<words, nword, instr0>;
			nik_ce auto nlines = push<lines, nwords>;

			nik_ce auto nstate = U_pack_Vs<labels, nlines, U_null_Vs, U_null_Vs, ngraph, U_null_Vs>;

			return nstate;
		}
	};

/***********************************************************************************************************************/

// go_to state:

	template<key_type, key_type...> struct GoToState;

	template<key_type... filler>
	struct GoToState<PD::branch, filler...>
	{
		template<auto instr0, auto labels, auto lines, auto words, auto chars, auto graph, auto verts>
		nik_ces auto result(nik_vp(state)(T_pack_Vs<labels, lines, words, chars, graph, verts>*))
		{
			nik_ce auto lbl     = label_value<instr0>;
			nik_ce auto nverts  = push<verts, lbl>;

			nik_ce auto nword   = unpack_<chars, U_endofold>;
			nik_ce auto nwords  = push<words, nword>;
			nik_ce auto nstate  = U_pack_Vs<labels, lines, nwords, U_null_Vs, graph, nverts>;

			return nstate;
		}
	};

	template<key_type... filler>
	struct GoToState<PD::lift, filler...>
	{
		template<auto instr0, typename State>
		nik_ces auto result(State)
		{
			nik_ce auto state  = U_restore_T<State>;
			nik_ce auto chars  = list_at<state, PS::chars>;

			nik_ce auto nchars = push<chars, instr0>;
			nik_ce auto nstate = list_replace<state, PS::chars, nchars>;

			return nstate;
		}
	};

/***********************************************************************************************************************/

// parse instruction (monoid):

	nik_ce void _parse_end_ () { }

	struct T_parse_instr
	{
		template<auto instr1>
		nik_ces auto _name()
		{
			if nik_ce (same<instr1, _parse_end_>) return PD::rest_is_empty;
			else if nik_ce (is_label<instr1>)     return PD::is_before_label;
			else                                  return PD::not_before_label;
		}

		template<auto instr0>
		nik_ces auto _note()
		{
			if      nik_ce (is_label<instr0> ) return PD::label;
			else if nik_ce (is_branch<instr0>) return PD::branch;
			else if nik_ce (is_go_to<instr0> ) return PD::go_to;
			else if nik_ce (is_lift<instr0>  ) return PD::lift;
			else                               return PD::drop;
		}

		template<auto name, auto note>
		nik_ces auto _dispatch()
		{
			nik_ce auto names = array
			<
				bool const,

				(name == PD::rest_is_empty),
				(name == PD::is_before_label),
				(name == PD::not_before_label)
			>;

			nik_ce auto notes = array
			<
				bool const,

				(note == PD::label),
				(note == PD::branch),
				(note == PD::go_to),
				(note == PD::lift),
				(note == PD::drop)
			>;

			return array<bool const*, names, notes>;
		}

		template<auto d>
		nik_ces auto _static_assert()
		{
			nik_ce bool rest_is_empty_label    = !(d[PD::name][PD::rest_is_empty] && d[PD::note][PD::label]);
			nik_ce bool rest_is_empty_branch   = !(d[PD::name][PD::rest_is_empty] && d[PD::note][PD::branch]);
			nik_ce bool rest_is_empty_lift     = !(d[PD::name][PD::rest_is_empty] && d[PD::note][PD::lift]);

			nik_ce bool is_before_label_label  = !(d[PD::name][PD::is_before_label] && d[PD::note][PD::label]);

			nik_ce bool not_before_label_go_to = !(d[PD::name][PD::not_before_label] && d[PD::note][PD::go_to]);
			nik_ce bool not_before_label_drop  = !(d[PD::name][PD::not_before_label] && d[PD::note][PD::drop]);

			static_assert(rest_is_empty_label    , "A label as a final instruction is not allowed.");
			static_assert(rest_is_empty_branch   , "A branch as a final instruction is not allowed.");
			static_assert(rest_is_empty_lift     , "A lift as a final instruction is not allowed.");

			static_assert(is_before_label_label  , "A label before a label is not allowed.");

			static_assert(not_before_label_go_to , "A go_to followed by a nonlabel is not allowed.");
			static_assert(not_before_label_drop  , "A drop followed by a nonlabel is not allowed.");
		}

		template<auto state, auto instr0, auto instr1>
		nik_ces auto _result()
		{
			if nik_ce (same<instr0, _parse_end_>) return state;
			else
			{
				nik_ce auto name = _name<instr1>();
				nik_ce auto note = _note<instr0>();
				nik_ce auto disp = _dispatch<name, note>();

				_static_assert<disp>();

				nik_ce bool is_before_label	= disp[PD::name][PD::is_before_label];
				nik_ce bool is_branch		= disp[PD::note][PD::branch];
				nik_ce bool is_lift		= disp[PD::note][PD::lift];
				nik_ce bool is_go_to_deducible	= is_before_label && (is_branch || is_lift);

				if nik_ce (!is_go_to_deducible) return Parse<note>::template result<instr0>(state);
				else
				{
					nik_ce auto disp    = is_branch ? PD::branch : PD::lift;
					nik_ce auto nstate  = GoToState<disp>::template result<instr0>(state);
					nik_ce auto ninstr0 = go_to<label_value<instr1>>;

					return Parse<PD::go_to>::template result<ninstr0>(nstate);
				}
			}
		}

		template<auto state, auto instr0, auto instr1>
		nik_ces auto result = _result<state, instr0, instr1>();

	}; nik_ce auto U_parse_instr = U_store_T<T_parse_instr>;

/***********************************************************************************************************************/

// (parser) helpers:

	struct T_vertices_to_indices
	{
		template<auto labels, auto... vertexes>
		nik_ces auto result = U_pack_Vs
		<
			unpack_<labels, _find_, U_alias<_same_, vertexes>>...
		>;

	}; nik_ce auto U_vertices_to_indices = U_store_T<T_vertices_to_indices>;

	struct T_graph_to_requirements
	{
		template<auto labels, auto... vertices>
		nik_ces auto result = U_pack_Vs
		<
			unpack_<vertices, U_vertices_to_indices, labels>...
		>;

	}; nik_ce auto U_graph_to_requirements = U_store_T<T_graph_to_requirements>;

/***********************************************************************************************************************/

// parser:

	struct T_parse
	{
		nik_ces auto initial_state = unpack_<segment<6>, _map_, H_id, _constant_<U_null_Vs>>;

		template<auto labels, auto lines, auto words, auto chars, auto graph, auto verts>
		nik_ces auto _result(nik_vp(state)(T_pack_Vs<labels, lines, words, chars, graph, verts>*))
		{
			nik_ce auto reqs   = unpack_<graph, U_graph_to_requirements, labels>;
			nik_ce auto parsed = cons<lines, reqs>;

			return parsed;
		}

		template<auto... instrs>
		nik_ces auto result = _result
		(
			pack_parse
			<
				U_parse_instr, initial_state,
				instrs..., _parse_end_, _parse_end_
			>
		);
	};

	template<auto... instrs>
	nik_ce auto parse = T_parse::template result<instrs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// make:

/***********************************************************************************************************************/

	struct T_make
	{
		template<auto cont, auto lbl>
		nik_ces auto result = T_endopose::template result<cont, _branch_<lbl>>;

	}; nik_ce auto U_make = U_store_T<T_make>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// link:

	// line { f0, f1, ... , f.n-1, fn, maybe f.n+1 }
	// deps { dep[0], dep[1], ... , dep[n-1] } with { dep[n] or f.n+1 = drop }

	// link { f0, dep[0], f1, dep[1], ... , f.n-1, dep[n-1], fn, dep[n] or f.n+1 = drop }

	template<key_type...> struct Link;

/***********************************************************************************************************************/

// dispatch:

	struct LinkDispatch
	{
		nik_ces key_type go_to		= 0;
		nik_ces key_type drop		= 1;
	};

	using LD = LinkDispatch;

	template<key_type... filler>
	struct Link<LD::go_to, filler...>
	{
		template<auto sign, auto line, auto deps>
		nik_ces auto result() // the line pack and deps pack have the same size.
		{
			nik_ce auto size	= length<deps> - 1;

			nik_ce auto split_line	= list_split<line, size>;
			nik_ce auto line_front	= cctmp::tuple_value<0>(split_line);
			nik_ce auto line_back	= cctmp::tuple_value<1>(split_line);

			nik_ce auto split_deps	= list_split<deps, size>;
			nik_ce auto deps_front	= cctmp::tuple_value<0>(split_deps);
			nik_ce auto deps_back	= cctmp::tuple_value<1>(split_deps);

			nik_ce auto conts_p0	= unpack_<deps_front, _zip_, H_id, U_make, line_front>;
			nik_ce auto conts_p	= unite<conts_p0, line_back>;

			nik_ce auto halt_lbl	= car<deps_back>;
			nik_ce auto halt	= _go_to_<halt_lbl>;
			nik_ce auto fs_p	= push<conts_p, halt>;

			return overload<U_endodrop, sign, fs_p>;
		}
	};

	template<key_type... filler>
	struct Link<LD::drop, filler...>
	{
		template<auto sign, auto line, auto deps>
		nik_ces auto result() // if the last dep is not a go_to, it implies it's a branch.
		{
			nik_ce auto size	= length<deps>;

			nik_ce auto split_line	= list_split<line, size>;
			nik_ce auto line_front	= cctmp::tuple_value<0>(split_line);
			nik_ce auto line_back	= cctmp::tuple_value<1>(split_line);

			nik_ce auto conts_p	= unpack_<deps, _zip_, H_id, U_make, line_front>;
			nik_ce auto fs_p	= unite<conts_p, line_back>;

			return overload<U_endodrop, sign, fs_p>;
		}
	};

/***********************************************************************************************************************/

// (linker) helpers:

	struct T_indices_to_dependencies
	{
		template<auto labels, auto... indices>
		nik_ces auto result = U_pack_Vs
		<
			list_at<labels, indices>...
		>;

	}; nik_ce auto U_indices_to_dependencies = U_store_T<T_indices_to_dependencies>;

/***********************************************************************************************************************/

	template<auto lbl, auto... lbls, auto reqs, auto... lines>
	nik_ce auto _link(nik_vp(parsed)(T_pack_Vs<reqs, lines...>*))
	{
		nik_ce auto sign	= in_types<lbl>;
		nik_ce auto labels	= U_pack_Vs<lbls...>;
		nik_ce auto lbl_pos	= find_<U_alias<_same_, lbl>, lbls...>;

		nik_ce auto line	= list_at<U_restore_T<decltype(parsed)>, lbl_pos + 1>;
		nik_ce auto line_size	= length<line>;

		nik_ce auto inds	= list_at<reqs, lbl_pos>;
		nik_ce auto deps	= unpack_<inds, U_indices_to_dependencies, labels>;
		nik_ce auto deps_size	= length<deps>;

		nik_ce auto disp	= (line_size == deps_size) ? LD::go_to : LD::drop;

		return Link<disp>::template result<sign, line, deps>();
	}

	template<auto parsed, auto lbl, auto... lbls>
	nik_ce auto link = _link<lbl, lbls...>(parsed);

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// labels:

	template<index_type, index_type...> struct Label { };

/***********************************************************************************************************************/

// [0-7]:

	NIK_DEFINE_LABEL_STRUCT(0, 1);
	NIK_DEFINE_LABEL_STRUCT(1, 2);
	NIK_DEFINE_LABEL_STRUCT(2, 3);
	NIK_DEFINE_LABEL_STRUCT(3, 4);
	NIK_DEFINE_LABEL_STRUCT(4, 5);
	NIK_DEFINE_LABEL_STRUCT(5, 6);
	NIK_DEFINE_LABEL_STRUCT(6, 7);
	NIK_DEFINE_LABEL_STRUCT(7, 8);

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// call:

/***********************************************************************************************************************/

	template<auto object, typename T, typename... Ts>
	nik_ce auto call(Ts... vs) { return Label<length<object> - 1>::template l0<object, T, Ts...>(vs...); }

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // cctmp_generics

