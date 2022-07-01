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

	using key_type						= typename cctmp::key_type;
	using index_type					= typename cctmp::index_type;
	using cindex_type					= typename cctmp::cindex_type;
	using BN						= typename cctmp::BN;
	using BD						= typename cctmp::BD;
	using MD						= typename cctmp::MD;
	using Operator						= typename cctmp::Operator;

	template<auto... Vs> using auto_pack			= typename cctmp::template auto_pack<Vs...>;
	template<auto... Vs> using block			= typename cctmp::template block<Vs...>;

	template<auto U> using T_store_U			= typename cctmp::template T_store_U<U>;

	template<auto V> using T_out_type			= typename cctmp::template T_out_type<V>;

	nik_ce auto _zero					= cctmp::_zero;
	nik_ce auto _one					= cctmp::_one;

	nik_ce auto U_null_Vs					= cctmp::U_null_Vs;

	nik_ce auto _id_					= cctmp::_id_;
	nik_ce auto _assign_					= cctmp::_assign_;
	nik_ce auto _dereference_				= cctmp::_dereference_;

	template<typename T> nik_ce auto U_store_T		= cctmp::template U_store_T<T>;
	template<typename T> nik_ce auto U_restore_T		= cctmp::template U_restore_T<T>;
	template<auto... Vs> nik_ce auto U_pack_Vs		= cctmp::template U_pack_Vs<Vs...>;
	template<typename... Ts> nik_ce auto U_pack_Ts		= cctmp::template U_pack_Ts<Ts...>;

	template<typename T, auto... Vs> nik_ce auto array	= cctmp::template array<T, Vs...>;

	template<auto V> nik_ce auto in_types			= cctmp::template in_types<V>;

	template<auto... Vs> nik_ce auto overload		= cctmp::template overload<Vs...>;

	template<auto V> nik_ce auto _constant_			= cctmp::template _constant_<V>;
	template<auto f> nik_ce auto _apply_			= cctmp::template _apply_<f>;
	template<auto... Vs> nik_ce auto _bind_			= cctmp::template _bind_<Vs...>;

	template<auto... Vs> nik_ce auto alias			= cctmp::template alias<Vs...>;
	template<auto... Vs> nik_ce auto unpack_alias		= cctmp::template unpack_alias<Vs...>;

	template<auto... Vs> nik_ce auto U_same			= cctmp::template U_same<Vs...>;
	template<auto...> nik_ce auto U_not_int_type		= cctmp::template U_not_int_type<>;

	template<auto...Vs> nik_ce auto U_custom		= cctmp::template U_custom<Vs...>;

	template<auto... Vs> nik_ce auto segment		= cctmp_functional::template segment<Vs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// conveniences:

/***********************************************************************************************************************/

// type at:

	template<index_type n, typename... Ts>
	using type_at = T_store_U<NIK_VARIABLE_BLOCK(3, 500, n, BN::sifter, U_store_T<Ts>)>;

// same:

	template<auto V0, auto V1>
	nik_ce auto same = alias<Operator::same, V0, V1>;

// has int type:

	template<auto V>
	nik_ce auto has_int_type = alias<Operator::is_int_type, U_store_T<decltype(V)>>;

// car:

	template<auto... Vs>
	nik_ce auto car = alias<Operator::car, Vs...>;

// find:

	template<auto Op, auto... Vs>
	nik_ce auto find = alias<Operator::find, Op, Vs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// functions:

/***********************************************************************************************************************/

// arguments:

	template<auto f, auto n, typename... Ts>
	nik_ce auto f_arg = T_store_U<f>::template result<type_at<n, Ts...>>;

	template<auto f, auto n, typename... Ts>
	using f_arg_type = T_out_type<f_arg<f, n, Ts...>>;

	// value:

			// The trailing return type is necessary to preserve references and qualifiers.

		template<auto f, auto n, auto d = 500>
		struct T_value
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) -> f_arg_type<f, n, Ts...>
				{ return f_arg<f, n, Ts...>(NIK_ARGUMENT_BLOCK(3, d, n, Ts)(vs...)); }
		};

		template<auto n, auto d>
		struct T_value<_id_, n, d>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return NIK_ARGUMENT_BLOCK(3, d, n, Ts)(vs...); }

		}; template<auto n, auto f = _id_, auto d = 500>
			nik_ce auto _value_ = U_store_T<T_value<f, n, d>>;

		// return:

			nik_ce auto _return_ = _value_<_zero>;

/***********************************************************************************************************************/

// call:

	// Normalizes the grammatical form for various kinds of function calls.
	// All function calls following are assumed to have the normal form
	// unless stated otherwise. With that said, labels are assumed
	// to be fully declared.

	// subcompose:

		template<auto f, auto f_ns_p, auto ns_p> struct T_subcompose;

		template
		<
			auto f,
			auto... f_ns, nik_vp(f_ns_p)(auto_pack<f_ns...>*),
			auto... ns, nik_vp(ns_p)(auto_pack<ns...>*)
		>
		struct T_subcompose<f, f_ns_p, ns_p>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs)
			{
				return T_store_U<f>::template result
				<
					f_arg_type<f_ns, ns, Ts...>...

				>(T_value<f_ns, ns>::template result<Ts...>(vs...)...);
			}

		}; template<auto f, auto f_ns_p, auto ns_p>
			nik_ce auto _subcompose_ = U_store_T<T_subcompose<f, f_ns_p, ns_p>>;

	// allot:

		template<auto l, auto r, auto f> struct T_allot;

		template
		<
			auto... l_ns, nik_vp(l)(auto_pack<l_ns...>*),
			auto... r_ns, nik_vp(r)(auto_pack<r_ns...>*),
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
					T_value<_id_, l_ns>::template result<Ts...>(vs...)...,
					v,
					T_value<_id_, r_ns>::template result<Ts...>(vs...)...
				);
			}

		}; template<auto l, auto r, auto f>
			nik_ce auto _allot_ = U_store_T<T_allot<l, r, f>>;

	// tuple apply:

	//	template<auto f, typename T, typename... Ts, index_type... tuple_indices>
	//	constexpr auto tuple_apply(const tuple<T, Ts...> & t, nik_vp(pack)(auto_pack<tuple_indices...>*))
	//	{
	//		return f(tuple_value<tuple_indices>(t)...);
	//	}

/***********************************************************************************************************************/

// mutation:

	// deref assign:

		nik_ce auto _deref_assign_ = _subcompose_
		<
			_assign_,

			U_pack_Vs < _dereference_ , _id_ >,
			U_pack_Vs <  0            ,  1   >
		>;

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
/***********************************************************************************************************************/

// lift:

	// Total (register) assignment in this context is equivalent to replacing the continuation's given argument.
	// Partial assignment is then achieved through the side effect of the given instruction.

	template<auto...> struct T_lift { };

	// id:

		nik_ce auto _lifted_id_ = U_store_T<T_lift<>>;

	// is label:

		template<auto>
		nik_ce bool is_lift = false;

		template<auto... Vs, nik_vp(p)(T_lift<Vs...>*)>
		nik_ce bool is_lift<p> = true;

/***********************************************************************************************************************/

	nik_ce void _cp_ () { } // copy
	nik_ce void _ps_ () { } // paste

	struct Lift
	{
		nik_ces key_type deny			= 0;
		nik_ces key_type allow			= 1;

		nik_ces key_type insert			= 2;
		nik_ces key_type replace		= 3;

		template<auto V>
		nik_ces key_type direction	=  !has_int_type<V> && !same<V, _cp_> ? deny : allow;

		template<auto V>
		nik_ces key_type location	= same<V, _cp_> ? insert : replace;
	};

/***********************************************************************************************************************/

// deny:

	// direct:

		template<auto f>
		struct T_lift<Lift::deny, f, true>
		{
			template<auto pass, typename... Ts>
			nik_ces auto result(Ts... vs)
			{
				T_store_U<f>::template result<Ts...>(vs...);

				return T_store_U<pass>::template result<Ts...>(vs...);
			}
		};

	// indirect:

		template<auto f>
		struct T_lift<Lift::deny, f, false>
		{
			template<auto pass, typename T, typename... Ts>
			nik_ces auto result(T v, Ts... vs)
			{
				T_store_U<f>::template result<T, Ts...>(v, vs...);

				return T_store_U<pass>::template result<Ts...>(vs...);
			}
		};

/***********************************************************************************************************************/

// (allow,) insert:

	// direct:

		template<auto f>
		struct T_lift<Lift::insert, f, true>
		{
			template<auto pass, typename... Ts>
			nik_ces auto result(Ts... vs)
			{
				auto val = T_store_U<f>::template result<Ts...>(vs...);

				return T_store_U<pass>::template result<decltype(val), Ts...>(val, vs...);
			}
		};

	// indirect:

		template<auto f>
		struct T_lift<Lift::insert, f, false>
		{
			template<auto pass, typename T, typename... Ts>
			nik_ces auto result(T v, Ts... vs)
			{
				auto val = T_store_U<f>::template result<T, Ts...>(v, vs...);

				return T_store_U<pass>::template result<decltype(val), Ts...>(val, vs...);
			}
		};

/***********************************************************************************************************************/

// (allow,) replace:

	// direct:

		template<auto m, auto f>
		struct T_lift<Lift::replace, m, f, true>
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

	// indirect:

		template<auto m, auto f>
		struct T_lift<Lift::replace, m, f, false>
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

// lift:

	// helpers:

		nik_ce auto _constant_id_ = _constant_<_id_>;

		template<auto... ns>
		nik_ce auto find_non_int = find<U_not_int_type<>, U_store_T<decltype(ns)>...>;

		template<auto p, auto... ns>
		nik_ce auto is_all_ints = (p == sizeof...(ns));

		template<auto V>
		nik_ce index_type map_indices()
		{
			if nik_ce (has_int_type<V>) return V + _one;
			else return _zero;
		}

		template<bool all_ints, auto... ns>
		nik_ce auto lift_indices()
		{
			if nik_ce (all_ints) return U_pack_Vs<index_type{ns}...>;
			else                 return U_pack_Vs<map_indices<ns>()...>;
		}

		template<auto f, auto... ns, auto policy, auto... ms>
		nik_ce auto lift_dispatch(nik_avp(auto_pack<policy, ms...>*))
		{
			if nik_ce (same<f, _id_>) return _lifted_id_;
			else
			{
				nik_ce auto p		= find_non_int<ns...>;
				nik_ce auto all_ints	= is_all_ints<p, ns...>;

				nik_ce auto f_ns_p	= U_pack_Vs<overload<_constant_id_, ns>...>;
				nik_ce auto ns_p	= lift_indices<all_ints, ns...>();
				nik_ce auto nf		= _subcompose_<f, f_ns_p, ns_p>;

				using T_internal_lift = T_lift<policy, ms..., nf, all_ints>;

				return U_store_T<T_internal_lift>;
			}
		}

/***********************************************************************************************************************/

// specializations:

	template<key_type, key_type, key_type...> struct LiftDispatch;

// deny, id (internal):

	template<key_type... filler>
	struct LiftDispatch<Lift::deny, Lift::replace, filler...>
	{
		template<auto f, auto... ns>
		nik_ces auto result = lift_dispatch<f, ns...>(U_pack_Vs<Lift::deny>);
	};

// allow, insert (indirect):

	template<key_type... filler>
	struct LiftDispatch<Lift::allow, Lift::insert, filler...>
	{
		template<auto m, auto f, auto... ns>
		nik_ces auto result = lift_dispatch<f, ns...>(U_pack_Vs<Lift::insert>);
	};

// allow, replace (direct):

	template<key_type... filler>
	struct LiftDispatch<Lift::allow, Lift::replace, filler...>
	{
		template<auto m, auto f, auto... ns>
		nik_ces auto result = lift_dispatch<f, ns...>(U_pack_Vs<Lift::replace, m>);
	};

	// lift:

		template<auto V, auto... Vs>
		nik_ce auto lift = LiftDispatch<Lift::direction<V>, Lift::location<V>>::template result<V, Vs...>;

	// test:

		template<auto p, auto... ns>
		nik_ce auto test = LiftDispatch<Lift::allow, Lift::insert>::template result<_cp_, p, ns...>;

	// tacit:

		template<auto f>
		nik_ce auto tacit = LiftDispatch<Lift::allow, Lift::insert>::template result<_cp_, f, _ps_>;

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
		nik_ces auto result = NIK_FOLD_BLOCK(500, sizeof...(Vs), U_custom<U_endopose>, _lifted_id_, Vs);

	}; nik_ce auto U_endofold = U_store_T<T_endofold>;

// endodrop:

	template<typename... Ts>
	nik_ce auto signature = U_pack_Ts<Ts...>;

	// implemented this way as gcc complains about ambiguous matches.

	template<auto... UTs, auto... fs>
	nik_ce auto _endodrop(nik_avp(auto_pack<UTs...>*), nik_vp(p)(auto_pack<fs...>*))
	{
		nik_ce auto size = sizeof...(fs);

		if nik_ce (size == _zero) return T_store_U<_id_>::template result<T_store_U<UTs>...>;
		else
		{
			nik_ce auto s    = cctmp_functional::split<size - _one, U_restore_T<decltype(p)>>;
			nik_ce auto l    = cctmp::tuple_value<0>(s);
			nik_ce auto r    = cctmp::tuple_value<1>(s);
			nik_ce auto f    = cctmp_functional::fold<U_custom<U_endopose>, _lifted_id_, l>;
			nik_ce auto halt = cctmp_functional::at<_zero, r>;

			if nik_ce (same<f, _lifted_id_>) return T_store_U<halt>::template result<T_store_U<UTs>...>;
			else                             return T_store_U<f>::template result<halt, T_store_U<UTs>...>;
		}
	}

	template<auto s, auto... fs>
	nik_ce auto endodrop = _endodrop(s, U_pack_Vs<fs...>);

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// parse:

	using cdep_type  = cindex_type* const;
	using cdeps_type = cdep_type* const;

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
			nik_ce auto labels  = cctmp_functional::at<PS::labels, state>;

			nik_ce auto lbl     = label_value<instr0>;
			nik_ce auto nlabels = unpack_alias<labels, Operator::push, lbl>; // error if already exists.
			nik_ce auto nstate  = cctmp_functional::replace<nlabels, PS::labels, state>;

			return nstate;
		}
	};

	template<key_type... filler>
	struct Parse<PD::branch, filler...>
	{
		template<auto instr0, auto labels, auto lines, auto words, auto chars, auto graph, auto verts>
		nik_ces auto result(nik_vp(state)(auto_pack<labels, lines, words, chars, graph, verts>*))
		{
			nik_ce auto lbl    = label_value<instr0>;
			nik_ce auto nverts = unpack_alias<verts, Operator::push, lbl>;

			nik_ce auto nword  = unpack_alias<chars, Operator::custom, U_endofold>;
			nik_ce auto nwords = unpack_alias<words, Operator::push, nword>;

			nik_ce auto nstate = U_pack_Vs<labels, lines, nwords, U_null_Vs, graph, nverts>;

			return nstate;
		}
	};

	template<key_type... filler>
	struct Parse<PD::go_to, filler...>
	{
		template<auto instr0, auto labels, auto lines, auto words, auto chars, auto graph, auto verts>
		nik_ces auto result(nik_vp(state)(auto_pack<labels, lines, words, chars, graph, verts>*))
		{
			nik_ce auto lbl    = label_value<instr0>;
			nik_ce auto nverts = unpack_alias<verts, Operator::push, lbl>;
			nik_ce auto ngraph = unpack_alias<graph, Operator::push, nverts>;

			nik_ce auto nword  = unpack_alias<chars, Operator::custom, U_endofold>;
			nik_ce auto nwords = unpack_alias<words, Operator::push, nword>;
			nik_ce auto nlines = unpack_alias<lines, Operator::push, nwords>;

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
			nik_ce auto chars  = cctmp_functional::at<PS::chars, state>;

			nik_ce auto nchars = unpack_alias<chars, Operator::push, instr0>;
			nik_ce auto nstate = cctmp_functional::replace<nchars, PS::chars, state>;

			return nstate;
		}
	};

	template<key_type... filler>
	struct Parse<PD::drop, filler...>
	{
		template<auto instr0, auto labels, auto lines, auto words, auto chars, auto graph, auto verts>
		nik_ces auto result(nik_vp(state)(auto_pack<labels, lines, words, chars, graph, verts>*))
		{
			nik_ce auto ngraph = unpack_alias<graph, Operator::push, verts>;

			nik_ce auto nword  = unpack_alias<chars, Operator::custom, U_endofold>;
			nik_ce auto nwords = unpack_alias<words, Operator::push, nword, instr0>;
			nik_ce auto nlines = unpack_alias<lines, Operator::push, nwords>;

			nik_ce auto nstate = U_pack_Vs<labels, nlines, U_null_Vs, U_null_Vs, ngraph, U_null_Vs>;

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
			nik_ce bool is_before_label_branch = !(d[PD::name][PD::is_before_label] && d[PD::note][PD::branch]);

			nik_ce bool not_before_label_go_to = !(d[PD::name][PD::not_before_label] && d[PD::note][PD::go_to]);
			nik_ce bool not_before_label_drop  = !(d[PD::name][PD::not_before_label] && d[PD::note][PD::drop]);

			static_assert(rest_is_empty_label    , "A label as a final instruction is not allowed.");
			static_assert(rest_is_empty_branch   , "A branch as a final instruction is not allowed.");
			static_assert(rest_is_empty_lift     , "A lift as a final instruction is not allowed.");

			static_assert(is_before_label_label  , "A label before a label is not allowed.");
			static_assert(is_before_label_branch , "A branch before a label is not allowed.");

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

				nik_ce bool is_before_label_lift = disp[PD::name][PD::is_before_label]
								&& disp[PD::note][PD::lift];

				if nik_ce (is_before_label_lift)
				{
					nik_ce auto chars   = cctmp_functional::at<PS::chars, state>;

					nik_ce auto ninstr0 = go_to<label_value<instr1>>;
					nik_ce auto nchars  = unpack_alias<chars, Operator::push, instr0>;
					nik_ce auto nstate  = cctmp_functional::replace<nchars, PS::chars, state>;

					return Parse<PD::go_to>::template result<ninstr0>(nstate);
				}
				else return Parse<note>::template result<instr0>(state);
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
		nik_ces auto result = array
		<
			cindex_type, sizeof...(vertexes),
			unpack_alias<labels, Operator::find, U_same<vertexes>>...
		>;

	}; nik_ce auto U_vertices_to_indices = U_store_T<T_vertices_to_indices>;

	struct T_graph_to_indices
	{
		template<auto labels, auto dep_size, auto... vertices>
		nik_ces auto result = array
		<
			cdep_type, dep_size,
			unpack_alias<vertices, Operator::custom, U_vertices_to_indices, labels>...
		>;

	}; nik_ce auto U_graph_to_indices = U_store_T<T_graph_to_indices>;

/***********************************************************************************************************************/

// parser:

	struct T_parse
	{
		nik_ces auto initial_state = unpack_alias<segment<6>, Operator::map, _constant_<U_null_Vs>>;

		template<auto labels, auto lines, auto words, auto chars, auto graph, auto verts>
		nik_ces auto _result(nik_vp(state)(auto_pack<labels, lines, words, chars, graph, verts>*))
		{
			nik_ce auto asize  = array<cindex_type, unpack_alias<graph, Operator::length>>;
			nik_ce auto deps   = unpack_alias<graph, Operator::custom, U_graph_to_indices, labels, asize>;
			nik_ce auto parsed = unpack_alias<lines, Operator::cons, deps>;

			return parsed;
		}

		template<auto... instrs>
		nik_ces auto result = _result
		(
			cctmp_functional::parse
			<
				U_custom<U_parse_instr>, initial_state,
				U_pack_Vs<instrs..., _parse_end_>
			>
		);
	};

	template<auto... instrs>
	nik_ce auto parse = T_parse::template result<instrs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// make:

	template<bool, bool...> struct Make;

	nik_ce auto dispatch_make(cindex_type k, cdep_type deps, cindex_type rest_size)
	{
		auto no_deps_left = (k == deps[0]);
		auto is_last_word = (rest_size == 1);

		return no_deps_left || is_last_word;
	}

/***********************************************************************************************************************/

	template<bool... filler>
	struct Make<true, filler...>
	{
			// Assumes sizeof...(words) < 2:

		template<auto k, auto cont, auto word, auto... words, auto sign, auto deps, auto... lbls>
		nik_ces auto result(nik_vp(c)(auto_pack<sign, deps, lbls...>*))
		{
			nik_ce auto is_go_to = (k != deps[0]);

			if nik_ce (is_go_to)
			{
				nik_ce auto ncont = T_endopose::template result<cont, word>;
				nik_ce auto n     = deps[k+1];
				nik_ce auto nlbl  = cctmp_functional::at<n+2, U_restore_T<decltype(c)>>;
				nik_ce auto halt  = _apply_<nlbl>;

				return endodrop<sign, ncont, halt>;
			}
			else if nik_ce (sizeof...(words) != 0)
			{
				nik_ce auto ncont = T_endopose::template result<cont, word>;
				nik_ce auto halt  = car<words...>;

				return endodrop<sign, ncont, halt>;
			}
			else return endodrop<sign, cont, word>;
		}
	};

	template<bool... filler>
	struct Make<false, filler...>
	{
		template<auto k, auto cont, auto word, auto... words, auto sign, auto deps, auto... lbls>
		nik_ces auto result(nik_vp(c)(auto_pack<sign, deps, lbls...>*))
		{
			nik_ce auto nk      = k+1;
			nik_ce auto n       = deps[nk];
			nik_ce auto nlbl    = cctmp_functional::at<n+2, U_restore_T<decltype(c)>>;
			nik_ce auto nbranch = _branch_<nlbl>;
			nik_ce auto nword   = T_endopose::template result<word, nbranch>;
			nik_ce auto ncont   = T_endopose::template result<cont, nword>;
			nik_ce auto size    = sizeof...(words);

			return Make<dispatch_make(nk, deps, size)>::template result<nk, ncont, words...>(c);
		}
	};

	template<auto...>
	nik_ce auto make = _id_;

		// It is expected the parser will create a _lifted_id_ so that words... is never empty.
		// It is an error otherwise.

	template
	<
		auto... words, nik_vp(l)(auto_pack<words...>*),
		auto sign, auto deps, auto... lbls, nik_vp(c)(auto_pack<sign, deps, lbls...>*)
	>
	nik_ce auto make<l, c> = Make
	<
		dispatch_make(0, deps, sizeof...(words))

	>::template result<0, _lifted_id_, words...>(c);

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// link:

/***********************************************************************************************************************/

	template<auto lbl, auto... lbls, auto deps, auto... lines>
	nik_ce auto _link(nik_vp(parsed)(auto_pack<deps, lines...>*))
	{
		nik_ce auto n = find<U_same<lbl>, lbls...>;
		nik_ce auto l = cctmp_functional::at<n+1, U_restore_T<decltype(parsed)>>;
		nik_ce auto s = in_types<lbl>;
		nik_ce auto c = U_pack_Vs<s, deps[n+1], lbls...>;

		return make<l, c>;
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

	template<auto deps, auto... lines>
	nik_ce auto label_size(nik_avp(auto_pack<deps, lines...>*)) { return sizeof...(lines); }

/***********************************************************************************************************************/

	template<auto object, typename T, typename... Ts>
	nik_ce auto call(Ts... vs)
	{
		return Label<label_size(object)>::template l0<object, T, Ts...>(vs...);
	}

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // cctmp_generics

