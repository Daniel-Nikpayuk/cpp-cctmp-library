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

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

/***********************************************************************************************************************/

// not int type:

/*
	struct NotIntType
	{
		template<auto V>
		nik_ces bool result = ! is_int_type<decltype(V)>;
	};
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// type sifter:

/*
	template<index_type n, typename... Ts>
	using type_sifter = T_store_U<_value_sifter<n, U_store_T<Ts>...>()>;
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// functions:

/***********************************************************************************************************************/

// arguments:

/*
	template<index_type n, typename T, typename... Ts>
	nik_ce auto arg(T v, Ts... vs)
	{
		if nik_ce (n == 0) return v;
		else               return arg<n-1, Ts...>(vs...);
	}

	template<auto f, auto n, typename... Ts>
	nik_ce auto f_arg = T_store_U<f>::template result<type_sifter<n, Ts...>>;

	template<auto f, auto n, typename... Ts>
	using f_arg_type = T_out_type<f_arg<f, n, Ts...>>;

	// value:

			// The trailing return type is necessary to preserve references and qualifiers.

		template<auto f, auto n>
		struct T_value
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) -> f_arg_type<f, n, Ts...>
			{
				return f_arg<f, n, Ts...>(arg<n, Ts...>(vs...));
			}
		};

		template<auto n>
		struct T_value<_id_, n>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return arg<n, Ts...>(vs...); }

		}; template<auto n, auto f = _id_>
			nik_ce auto _value_ = U_store_T<T_value<f, n>>;

		// return:

			nik_ce auto _return_ = _value_<_zero>;
*/

/***********************************************************************************************************************/

// call:

	// Normalizes the grammatical form for various kinds of function calls.
	// All function calls following are assumed to have the normal form
	// unless stated otherwise. With that said, labels are assumed
	// to be fully declared.

	// subcompose:

/*
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
					type_sifter<l_ns, Ts...>...,
					T,
					type_sifter<r_ns, Ts...>...
				>
				(
					T_value<_id_, l_ns>::template result<Ts...>(vs...)...,
					v,
					T_value<_id_, r_ns>::template result<Ts...>(vs...)...
				);
			}

		}; template<auto l, auto r, auto f>
			nik_ce auto _allot_ = U_store_T<T_allot<l, r, f>>;
*/

/***********************************************************************************************************************/

// mutation:

	// assign:

/*
		struct T_assign
		{
			template<typename T1, typename T2>
			nik_ces auto result(T1 v1, T2 v2) { return v1 = v2; }

		}; nik_ce auto _assign_ = U_store_T<T_assign>;

	// dereference:

		struct T_dereference
		{
			template<typename T>
			nik_ces auto & result(T v) { return *v; }

		}; nik_ce auto _dereference_ = U_store_T<T_dereference>;

		// deref assign:

			nik_ce auto _deref_assign_ = _subcompose_
			<
				_assign_,

				U_pack_Vs < _dereference_ , _id_ >,
				U_pack_Vs <  0            ,  1   >
			>;
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// instructions:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// go to:

/***********************************************************************************************************************/

/*
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
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// branch:

/***********************************************************************************************************************/

/*
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
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// label:

/***********************************************************************************************************************/

/*
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
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// lift:

	// Total (register) assignment in this context is equivalent to replacing the continuation's given argument.
	// Partial assignment is then achieved through the side effect of the given instruction.

/*
	template<auto...> struct T_lift { };

	// id:

		nik_ce auto _lifted_id_ = U_store_T<T_lift<>>;

	// is label:

		template<auto>
		nik_ce bool is_lift = false;

		template<auto... Vs, nik_vp(p)(T_lift<Vs...>*)>
		nik_ce bool is_lift<p> = true;
*/

/***********************************************************************************************************************/

/*
	nik_ce void _cp_ () { } // copy
	nik_ce void _ps_ () { } // paste

	struct Lift
	{
		nik_ces key_type deny			= 0;
		nik_ces key_type allow			= 1;

		nik_ces key_type insert			= 2;
		nik_ces key_type replace		= 3;

		template<auto V>
		nik_ces key_type direction	= !is_int_type<decltype(V)> && !same<V, _cp_> ? deny : allow;

		template<auto V>
		nik_ces key_type location	= same<V, _cp_> ? insert : replace;
	};
*/

/***********************************************************************************************************************/

// deny:

	// direct:

/*
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
*/

/***********************************************************************************************************************/

// (allow,) insert:

	// direct:

/*
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
*/

/***********************************************************************************************************************/

// (allow,) replace:

	// direct:

/*
		template<auto m, auto f>
		struct T_lift<Lift::replace, m, f, true>
		{
			nik_ces auto l = index_segment<m, _zero>;
			nik_ces auto n = m + _one;

			template<auto pass, typename... Ts>
			nik_ces auto result(Ts... vs)
			{
				nik_ce auto r = index_segment<sizeof...(Ts)-n, n>;

				auto val      = T_store_U<f>::template result<Ts...>(vs...);

				return T_allot<l, r, pass>::template result<decltype(val), Ts...>(val, vs...);
			}
		};

	// indirect:

		template<auto m, auto f>
		struct T_lift<Lift::replace, m, f, false>
		{
			nik_ces auto l = index_segment<m, _zero>;
			nik_ces auto n = m + _one;

			template<auto pass, typename T, typename... Ts>
			nik_ces auto result(T v, Ts... vs)
			{
				nik_ce auto r = index_segment<sizeof...(Ts)-n, n>;

				auto val      = T_store_U<f>::template result<T, Ts...>(v, vs...);

				return T_allot<l, r, pass>::template result<decltype(val), Ts...>(val, vs...);
			}
		};
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// lift:

	// helpers:

/*
		template<auto... ns>
		nik_ce auto find_non_int = ArrayPointer::template find<NotIntType, ns...>;

		template<auto p, auto... ns>
		nik_ce auto is_all_ints = (p == sizeof...(ns));

		template<auto V>
		nik_ce index_type map_indices()
		{
			if nik_ce (is_int_type<decltype(V)>) return V + _one;
			else return _zero;
		}

		template<bool all_ints, auto... ns>
		nik_ce auto lift_indices()
		{
			if nik_ce (all_ints) return U_pack_Vs<index_type{ns}...>;
			else                 return U_pack_Vs<map_indices<ns>()...>;
		}
*/

/***********************************************************************************************************************/

// specializations:

/*
	template<key_type, key_type, key_type...> struct LiftDispatch;

	using T_ToId = T_ToValue<_id_>;

// deny, id:

	template<key_type... filler>
	struct LiftDispatch<Lift::deny, Lift::replace, filler...>
	{
		template<auto f, auto... ns>
		nik_ces auto _result()
		{
			if nik_ce (same<f, _id_>) return _lifted_id_;
			else
			{
				nik_ce auto p		= find_non_int<ns...>;
				nik_ce auto all_ints	= is_all_ints<p, ns...>;

				nik_ce auto f_ns_p	= U_pack_Vs<T_ToId::template result<ns>...>;
				nik_ce auto ns_p	= lift_indices<all_ints, ns...>();
				nik_ce auto nf		= _subcompose_<f, f_ns_p, ns_p>;

				using T_internal_lift	= T_lift<Lift::deny, nf, all_ints>;

				return U_store_T<T_internal_lift>;
			}
		}

		template<auto f, auto... ns>
		nik_ces auto result = _result<f, ns...>();
	};

// allow, insert:

	template<key_type... filler>
	struct LiftDispatch<Lift::allow, Lift::insert, filler...>
	{
		template<auto f, auto... ns>
		nik_ces auto _result()
		{
			if nik_ce (same<f, _id_>) return _lifted_id_;
			else
			{
				nik_ce auto p		= find_non_int<ns...>;
				nik_ce auto all_ints	= is_all_ints<p, ns...>;

				nik_ce auto f_ns_p	= U_pack_Vs<T_ToId::template result<ns>...>;
				nik_ce auto ns_p	= lift_indices<all_ints, ns...>();
				nik_ce auto nf		= _subcompose_<f, f_ns_p, ns_p>;

				using T_indirect_lift	= T_lift<Lift::insert, nf, all_ints>;

				return U_store_T<T_indirect_lift>;
			}
		}

		template<auto m, auto f, auto... ns>
		nik_ces auto result = _result<f, ns...>();
	};

// allow, replace:

	template<key_type... filler>
	struct LiftDispatch<Lift::allow, Lift::replace, filler...>
	{
		template<auto m, auto f, auto... ns>
		nik_ces auto _result()
		{
			if nik_ce (same<f, _id_>) return _lifted_id_;
			else
			{
				nik_ce auto p		= find_non_int<ns...>;
				nik_ce auto all_ints	= is_all_ints<p, ns...>;

				nik_ce auto f_ns_p	= U_pack_Vs<T_ToId::template result<ns>...>;
				nik_ce auto ns_p	= lift_indices<all_ints, ns...>();
				nik_ce auto nf		= _subcompose_<f, f_ns_p, ns_p>;

				using T_direct_lift	= T_lift<Lift::replace, m, nf, all_ints>;

				return U_store_T<T_direct_lift>;
			}
		}

		template<auto m, auto f, auto... ns>
		nik_ces auto result = _result<m, f, ns...>();
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
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// endoposition:

/***********************************************************************************************************************/

// endopose:

/*
	template<typename F, typename G>
	struct _endopose
	{
		nik_ces auto g = U_store_T<G>;

		template<auto pass, typename... Ts>
		nik_ces auto result(Ts... vs) { return F::template result<_bind_<g, pass>, Ts...>(vs...); }
	};

	template<auto f, auto g>
	nik_ce auto endopose = U_store_T<_endopose<T_store_U<f>, T_store_U<g>>>;

	template<auto g>
	nik_ce auto endopose<_lifted_id_, g> = g;

	template<auto f>
	nik_ce auto endopose<f, _lifted_id_> = f;

	template<>
	nik_ce auto endopose<_lifted_id_, _lifted_id_> = _lifted_id_;

// endofold:

	template<auto... fs>
	nik_ce auto endofold = _lifted_id_;

	template<auto f, auto... fs>
	nik_ce auto endofold<f, fs...> = f;

	template<auto f, auto f0, auto... fs>
	nik_ce auto endofold<f, f0, fs...> = endofold<endopose<f, f0>, fs...>;

// endodrop:

	template<typename... Ts>
	nik_ce auto signature = U_pack_Ts<Ts...>;

	// implemented this way as gcc complains about ambiguous matches.

	template<auto f, auto halt, typename... Ts>
	nik_ce auto _endodrop(nik_avp(typename_pack<Ts...>*))
	{
		if nik_ce (same<f, _lifted_id_>) return T_store_U<halt>::template result<Ts...>;
		else                             return T_store_U<f>::template result<halt, Ts...>;
	}

	template<auto s, auto...>
	nik_ce auto endodrop = _endodrop<_lifted_id_, _id_>(s);

	template<auto s, auto halt>
	nik_ce auto endodrop<s, halt> = _endodrop<_lifted_id_, halt>(s);

	template<auto s, auto f, auto halt>
	nik_ce auto endodrop<s, f, halt> = _endodrop<f, halt>(s);

	template<auto s, auto f, auto f0, auto f1, auto... fs>
	nik_ce auto endodrop<s, f, f0, f1, fs...> = endodrop<s, endopose<f, f0>, f1, fs...>;
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// parse:

/*
	using cdep_type  = cindex_type* const;
	using cdeps_type = cdep_type* const;
*/

/***********************************************************************************************************************/

/*
	template<bool EmptyInstrs, bool... filler>
	struct Parse
	{
		template<auto... lbls, auto... ds>
		nik_ces auto map(nik_avp(auto_pack<ds...>*))
		{
			return array
			<
				cindex_type, sizeof...(ds),
				ArrayPointer::template find<T_is_same<ds>, lbls...>...
			>;
		}

		template
		<
			auto... lbls, auto... Ls,
			typename Words, typename Word,
			auto... Ds, typename Verts
		>
		nik_ces auto result
		(
			nik_vp(labels)(auto_pack<lbls...>*), nik_vp(lines)(auto_pack<Ls...>*),
			Words, Word, nik_vp(graph)(auto_pack<Ds...>*), Verts
		)
		{
			nik_ce auto asize  = array<cindex_type, sizeof...(Ds)>;
			nik_ce auto deps   = array<cdep_type, asize, map<lbls...>(Ds)...>;
			nik_ce auto parsed = U_pack_Vs<deps, Ls...>;

			return parsed;
		}
	};

	template<bool... filler>
	struct Parse<false, filler...>
	{
		template<auto V>
		nik_ces auto parse_assert() { return false; }

		template
		<
			auto instr0, auto... instrs,

			auto... lbls, auto... Ls,
			auto... Ws, auto... ws,
			auto... Ds, auto... ds
		>
		nik_ces auto dispatch_label
		(
			nik_vp(labels)(auto_pack<lbls...>*), nik_vp(lines)(auto_pack<Ls...>*),
			nik_vp(words)(auto_pack<Ws...>*), nik_vp(chars)(auto_pack<ws...>*),
			nik_vp(graph)(auto_pack<Ds...>*), nik_vp(verts)(auto_pack<ds...>*)
		)
		{
			nik_ce auto lbl     = label_value<instr0>;
			nik_ce auto nlabels = U_pack_Vs<lbls..., lbl>; // error if already exists.

			return Parse<bool{sizeof...(instrs) == 0}>::template result<instrs...>
			(
				nlabels, lines, words, chars, graph, verts
			);
		}

		template
		<
			auto instr0, auto... instrs,

			auto... lbls, auto... Ls,
			auto... Ws, auto... ws,
			auto... Ds, auto... ds
		>
		nik_ces auto dispatch_branch
		(
			nik_vp(labels)(auto_pack<lbls...>*), nik_vp(lines)(auto_pack<Ls...>*),
			nik_vp(words)(auto_pack<Ws...>*), nik_vp(chars)(auto_pack<ws...>*),
			nik_vp(graph)(auto_pack<Ds...>*), nik_vp(verts)(auto_pack<ds...>*)
		)
		{
			nik_ce auto lbl    = label_value<instr0>;
			nik_ce auto nverts = U_pack_Vs<ds..., lbl>;

			nik_ce auto nword  = endofold<ws...>;
			nik_ce auto nwords = U_pack_Vs<Ws..., nword>;

			return Parse<bool{sizeof...(instrs) == 0}>::template result<instrs...>
			(
				labels, lines, nwords, U_null_Vs, graph, nverts
			);
		}

		template
		<
			auto instr0, auto... instrs,

			auto... lbls, auto... Ls,
			auto... Ws, auto... ws,
			auto... Ds, auto... ds
		>
		nik_ces auto dispatch_go_to
		(
			nik_vp(labels)(auto_pack<lbls...>*), nik_vp(lines)(auto_pack<Ls...>*),
			nik_vp(words)(auto_pack<Ws...>*), nik_vp(chars)(auto_pack<ws...>*),
			nik_vp(graph)(auto_pack<Ds...>*), nik_vp(verts)(auto_pack<ds...>*)
		)
		{
			nik_ce auto lbl    = label_value<instr0>;
			nik_ce auto nverts = U_pack_Vs<ds..., lbl>;
			nik_ce auto ngraph = U_pack_Vs<Ds..., nverts>;

			nik_ce auto nword  = endofold<ws...>;
			nik_ce auto nwords = U_pack_Vs<Ws..., nword>;
			nik_ce auto nlines = U_pack_Vs<Ls..., nwords>;

			return Parse<bool{sizeof...(instrs) == 0}>::template result<instrs...>
			(
				labels, nlines, U_null_Vs, U_null_Vs, ngraph, U_null_Vs
			);
		}

		template
		<
			auto instr0, auto... instrs,

			auto... lbls, auto... Ls,
			auto... Ws, auto... ws,
			auto... Ds, auto... ds
		>
		nik_ces auto dispatch_lift
		(
			nik_vp(labels)(auto_pack<lbls...>*), nik_vp(lines)(auto_pack<Ls...>*),
			nik_vp(words)(auto_pack<Ws...>*), nik_vp(chars)(auto_pack<ws...>*),
			nik_vp(graph)(auto_pack<Ds...>*), nik_vp(verts)(auto_pack<ds...>*)
		)
		{
			nik_ce auto nchars = U_pack_Vs<ws..., instr0>;

			return Parse<bool{sizeof...(instrs) == 0}>::template result<instrs...>
			(
				labels, lines, words, nchars, graph, verts
			);
		}

		template
		<
			auto instr0, auto... instrs,

			auto... lbls, auto... Ls,
			auto... Ws, auto... ws,
			auto... Ds, auto... ds
		>
		nik_ces auto dispatch_drop
		(
			nik_vp(labels)(auto_pack<lbls...>*), nik_vp(lines)(auto_pack<Ls...>*),
			nik_vp(words)(auto_pack<Ws...>*), nik_vp(chars)(auto_pack<ws...>*),
			nik_vp(graph)(auto_pack<Ds...>*), nik_vp(verts)(auto_pack<ds...>*)
		)
		{
			nik_ce auto nverts = U_restore_T<decltype(verts)>;
			nik_ce auto ngraph = U_pack_Vs<Ds..., nverts>;

			nik_ce auto nword  = endofold<ws...>;
			nik_ce auto nwords = U_pack_Vs<Ws..., nword, instr0>;
			nik_ce auto nlines = U_pack_Vs<Ls..., nwords>;

			return Parse<bool{sizeof...(instrs) == 0}>::template result<instrs...>
			(
				labels, nlines, U_null_Vs, U_null_Vs, ngraph, U_null_Vs
			);
		}

		template
		<
			auto instr0,

			auto... lbls, auto... Ls,
			auto... Ws, auto... ws,
			auto... Ds, auto... ds
		>
		nik_ces auto rest_is_empty
		(
			nik_vp(labels)(auto_pack<lbls...>*), nik_vp(lines)(auto_pack<Ls...>*),
			nik_vp(words)(auto_pack<Ws...>*), nik_vp(chars)(auto_pack<ws...>*),
			nik_vp(graph)(auto_pack<Ds...>*), nik_vp(verts)(auto_pack<ds...>*)
		)
		{
			if nik_ce (is_label<instr0>)

				static_assert(parse_assert<instr0>(), "A label as a final instruction is not allowed.");

			else if nik_ce (is_branch<instr0>)

				static_assert(parse_assert<instr0>(), "A branch as a final instruction is not allowed.");

			else if nik_ce (is_go_to<instr0>)

				return dispatch_go_to<instr0>(labels, lines, words, chars, graph, verts);

			else if nik_ce (is_lift<instr0>)

				static_assert(parse_assert<instr0>(), "A lift as a final instruction is not allowed.");
			else
				return dispatch_drop<instr0>(labels, lines, words, chars, graph, verts);
		}

		template
		<
			auto instr0, auto... instrs,

			auto... lbls, auto... Ls,
			auto... Ws, auto... ws,
			auto... Ds, auto... ds
		>
		nik_ces auto is_before_label
		(
			nik_vp(labels)(auto_pack<lbls...>*), nik_vp(lines)(auto_pack<Ls...>*),
			nik_vp(words)(auto_pack<Ws...>*), nik_vp(chars)(auto_pack<ws...>*),
			nik_vp(graph)(auto_pack<Ds...>*), nik_vp(verts)(auto_pack<ds...>*)
		)
		{
			if nik_ce (is_label<instr0>)

				static_assert(parse_assert<instr0>(), "A label before a label is not allowed.");

			else if nik_ce (is_branch<instr0>)

				static_assert(parse_assert<instr0>(), "A branch before a label is not allowed.");

			else if nik_ce (is_go_to<instr0>)

				return dispatch_go_to<instr0, instrs...>(labels, lines, words, chars, graph, verts);

			else if nik_ce (is_lift<instr0>)
			{
				nik_ce auto instr1 = go_to<label_value<car<instrs...>>>;
				nik_ce auto nchars = U_pack_Vs<ws..., instr0>;

				return dispatch_go_to<instr1, instrs...>(labels, lines, words, nchars, graph, verts);
			}
			else
				return dispatch_drop<instr0, instrs...>(labels, lines, words, chars, graph, verts);
		}

		template
		<
			auto instr0, auto... instrs,

			auto... lbls, auto... Ls,
			auto... Ws, auto... ws,
			auto... Ds, auto... ds
		>
		nik_ces auto not_before_label
		(
			nik_vp(labels)(auto_pack<lbls...>*), nik_vp(lines)(auto_pack<Ls...>*),
			nik_vp(words)(auto_pack<Ws...>*), nik_vp(chars)(auto_pack<ws...>*),
			nik_vp(graph)(auto_pack<Ds...>*), nik_vp(verts)(auto_pack<ds...>*)
		)
		{
			if nik_ce (is_label<instr0>)

				return dispatch_label<instr0, instrs...>(labels, lines, words, chars, graph, verts);

			else if nik_ce (is_branch<instr0>)

				return dispatch_branch<instr0, instrs...>(labels, lines, words, chars, graph, verts);

			else if nik_ce (is_go_to<instr0>)

				static_assert(parse_assert<instr0>(), "A go_to followed by a nonlabel is not allowed.");

			else if nik_ce (is_lift<instr0>)

				return dispatch_lift<instr0, instrs...>(labels, lines, words, chars, graph, verts);
			else 
				static_assert(parse_assert<instr0>(), "A drop followed by a nonlabel is not allowed.");
		}

		template
		<
			auto instr0, auto... instrs,

			auto... lbls, auto... Ls,
			auto... Ws, auto... ws,
			auto... Ds, auto... ds
		>
		nik_ces auto result
		(
			nik_vp(labels)(auto_pack<lbls...>*), nik_vp(lines)(auto_pack<Ls...>*),
			nik_vp(words)(auto_pack<Ws...>*), nik_vp(chars)(auto_pack<ws...>*),
			nik_vp(graph)(auto_pack<Ds...>*), nik_vp(verts)(auto_pack<ds...>*)
		)
		{
			if nik_ce (sizeof...(instrs) == 0)

				return rest_is_empty<instr0>(labels, lines, words, chars, graph, verts);

			else if nik_ce (is_label<car<instrs...>>)

				return is_before_label<instr0, instrs...>(labels, lines, words, chars, graph, verts);
			else
				return not_before_label<instr0, instrs...>(labels, lines, words, chars, graph, verts);
		}
	};

	template<auto... instrs>
	nik_ce auto parse = Parse<bool{sizeof...(instrs) == 0}>::template result<instrs...>
	(
		U_null_Vs, U_null_Vs, U_null_Vs, U_null_Vs, U_null_Vs, U_null_Vs
	);
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// make:

/*
	template<bool, bool...> struct Make;

	nik_ce auto dispatch_make(cindex_type k, cdep_type deps, cindex_type rest_size)
	{
		auto no_deps_left = (k == deps[0]);
		auto is_last_word = (rest_size == 1);

		return no_deps_left || is_last_word;
	}
*/

/***********************************************************************************************************************/

/*
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
				nik_ce auto ncont = endopose<cont, word>;
				nik_ce auto n     = deps[k+1];
				nik_ce auto nlbl  = value_sifter<n, lbls...>;
				nik_ce auto halt  = _apply_<nlbl>;

				return endodrop<sign, ncont, halt>;
			}
			else if nik_ce (sizeof...(words) != 0)
			{
				nik_ce auto ncont = endopose<cont, word>;
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
			nik_ce auto nlbl    = value_sifter<n, lbls...>;
			nik_ce auto nbranch = _branch_<nlbl>;
			nik_ce auto nword   = endopose<word, nbranch>;
			nik_ce auto ncont   = endopose<cont, nword>;
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
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// link:

/***********************************************************************************************************************/

/*
	template<auto lbl, auto... lbls, auto deps, auto... lines>
	nik_ce auto _link(nik_avp(auto_pack<deps, lines...>*))
	{
		nik_ce auto n = ArrayPointer::template find<T_is_same<lbl>, lbls...>;
		nik_ce auto l = value_sifter<n, lines...>;
		nik_ce auto s = in_types<lbl>;
		nik_ce auto c = U_pack_Vs<s, deps[n+1], lbls...>;

		return make<l, c>;
	}

	template<auto parsed, auto lbl, auto... lbls>
	nik_ce auto link = _link<lbl, lbls...>(parsed);
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// labels:

/*
	template<index_type, index_type...> struct Label { };
*/

/***********************************************************************************************************************/

// [0-7]:

/*
	NIK_DEFINE_LABEL_STRUCT(0, 1);
	NIK_DEFINE_LABEL_STRUCT(1, 2);
	NIK_DEFINE_LABEL_STRUCT(2, 3);
	NIK_DEFINE_LABEL_STRUCT(3, 4);
	NIK_DEFINE_LABEL_STRUCT(4, 5);
	NIK_DEFINE_LABEL_STRUCT(5, 6);
	NIK_DEFINE_LABEL_STRUCT(6, 7);
	NIK_DEFINE_LABEL_STRUCT(7, 8);
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// call:

/*
	template<auto deps, auto... lines>
	nik_ce auto label_size(nik_avp(auto_pack<deps, lines...>*)) { return sizeof...(lines); }
*/

/***********************************************************************************************************************/

/*
	template<auto object, typename T, typename... Ts>
	nik_ce auto call(Ts... vs)
	{
		return Label<label_size(object)>::template l0<object, T, Ts...>(vs...);
	}
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // cctmp_generics

