/************************************************************************************************************************
**
** Copyright 2022-2023 Daniel Nikpayuk, Inuit Nunangat, The Inuit Nation
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

// assembly:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// dependencies:

/***********************************************************************************************************************/

// params (syntactic sugar):

	nik_ce auto _dpar_at_		= U_custom_T<T_machine_params< MT::back   , _car_           >>;
	nik_ce auto _dpar_left_		= U_custom_T<T_machine_params< MT::front  , _list_<>        >>;
	nik_ce auto _dpar_replace_	= U_custom_T<T_machine_params< MT::mutate , _list_<> , _one >>;

	nik_ce auto _par_at_		= _alias_< _dpar_at_      , MD::initial_depth >;
	nik_ce auto _par_left_		= _alias_< _dpar_left_    , MD::initial_depth >;
	nik_ce auto _par_replace_	= _alias_< _dpar_replace_ , MD::initial_depth >;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// chain:

	template<gkey_type, auto...> struct T_chain;

/***********************************************************************************************************************/

// names:

	struct ChainName
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.
			first , select , front , at , apply , applywise ,
			dimension
		};
	};

	using CN = ChainName;

/***********************************************************************************************************************/

// instructions:

	struct ChainInstr
	{
		enum : gkey_type
		{
			size = 0,
			name , pos ,
			dimension
		};
	};

	using CI = ChainInstr;

/***********************************************************************************************************************/

// dispatch:

	struct ChainDispatch
	{
		// defaults:

			nik_ces gindex_type initial_index = _zero;

		// accessors:

			nik_ces auto instr(ccontr_type c, gcindex_type i)
				{ return c[i]; }

		// navigators:

			nik_ces gkey_type next_name(ccontr_type c, gcindex_type i)
				{ return c[i+1][CI::name]; }

			nik_ces gindex_type next_index(ccontr_type, gcindex_type i)
				{ return i+1; }
	};

	using CD = ChainDispatch;

/***********************************************************************************************************************/

// start:

	struct T_chain_start
	{
		nik_ces auto i = CD::initial_index;

		template<auto c, auto l, auto... Vs, typename... Ts>
		nik_ces auto result(Ts... vs)
			{ return NIK_CHAIN(c, i, l, Vs)(vs...); }
	};

/***********************************************************************************************************************/

// first:

	template<auto... filler>
	struct T_chain<CN::first, filler...>
	{
		template<NIK_CHAIN_PARAMS(c, i, l, Vs), typename T0, typename... Ts>
		nik_ces auto result(T0 v0, Ts... vs) { return v0; }
	};

/***********************************************************************************************************************/

// select:

	template<auto... filler>
	struct T_chain<CN::select, filler...>
	{
		template<NIK_CHAIN_PARAMS(c, i, l, Vs), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto ins = CD::instr(c, i);
			nik_ce auto n   = ins[CI::pos];
			nik_ce auto p   = unpack_<l, _par_at_, n>;

			return NIK_CHAIN_TEMPLATE(c, i),

				p

			NIK_CHAIN_RESULT(c, i, l, Vs)(vs...);
		}
	};

/***********************************************************************************************************************/

// front:

	template<auto... filler>
	struct T_chain<CN::front, filler...>
	{
		template<NIK_CHAIN_PARAMS(c, i, l, Vs), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto ins = CD::instr(c, i);
			nik_ce auto n   = ins[CI::pos];
			nik_ce auto p   = eval<_par_left_, n, U_store_T<Ts>...>;

			return NIK_CHAIN_TEMPLATE(c, i),

				p

			NIK_CHAIN_RESULT(c, i, l, Vs)(vs...);
		}
	};

/***********************************************************************************************************************/

// at:

	template<template<auto...> typename B, auto... LUs, nik_vp(p)(B<LUs...>*)>
	struct T_chain<CN::at, p>
	{
		template<NIK_CHAIN_PARAMS(c, i, l, Vs), typename TN, typename... Ts>
		nik_ces auto result(T_store_U<LUs>... lvs, TN vn, Ts... vs)
		{
			return NIK_CHAIN(c, i, l, Vs)(vn);
		}
	};

/***********************************************************************************************************************/

// apply:

	template<auto f>
	struct T_chain<CN::apply, f>
	{
		template<NIK_CHAIN_PARAMS(c, i, l, Vs), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			return NIK_CHAIN(c, i, l, Vs)(T_store_U<f>::template result<>(vs...));
		}
	};

/***********************************************************************************************************************/

// applywise:

	template<template<auto...> typename B, auto... fs, nik_vp(p)(B<fs...>*)>
	struct T_chain<CN::applywise, p>
	{
		template<NIK_CHAIN_PARAMS(c, i, l, Vs), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			return NIK_CHAIN(c, i, l, Vs)(T_store_U<fs>::template result<>(vs)...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// space:

	template<gkey_type, gkey_type, auto...> struct T_assembly;

/***********************************************************************************************************************/

// names:

	struct AssemblyName
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.
			first , jump    , select ,
			right , replace ,
			call  , recall  ,
			loop  ,
			dimension
		};
	};

	using AN = AssemblyName;

/***********************************************************************************************************************/

// notes:

	struct AssemblyNote
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.
			front , go_to , branch , pair , side ,
			dimension
		};
	};

	using AT = AssemblyNote;

/***********************************************************************************************************************/

// instructions:

	struct AssemblyInstr
	{
		enum : gkey_type
		{
			size = 0,
			name , note , pos ,
			dimension
		};
	};

	using AI = AssemblyInstr;

/***********************************************************************************************************************/

// dispatch:

	struct AssemblyDispatch
	{
		// defaults:

			nik_ces gindex_type initial_index = _zero;

		// accessors:

			nik_ces auto instr(ccontr_type c, gcindex_type i)
				{ return c[i]; }

		// navigators:

			nik_ces gkey_type next_name(ccontr_type c, gcindex_type i)
				{ return c[i+1][AI::name]; }

			nik_ces gkey_type next_note(ccontr_type c, gcindex_type i)
				{ return c[i+1][AI::note]; }

			nik_ces gindex_type next_index(ccontr_type, gcindex_type i)
				{ return i+1; }
	};

	using AD = AssemblyDispatch;

/***********************************************************************************************************************/

// start:

	struct T_assembly_start
	{
		nik_ces auto i = AD::initial_index;

		template<auto s, auto c, auto l, auto... Vs, typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
			{ return NIK_ASSEMBLY(s, c, i, l, Vs)(vs...); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// dependencies:

	// conceptually, modularizing out (division of labour) arg_at (focused on the registers)
	// from the arbitrary function application (separate out compose and apply) is a better
	// design, but given the nature of variadics the following might be more performant?

/***********************************************************************************************************************/

// at:

	template<auto f, auto n>
	struct T_arg_at
	{
		nik_ces auto is_optimizable   = eval<_same_, f, _id_>;
		nik_ces auto lookup           = stem_<is_optimizable, U_null_Vs, _list_<>, f>;

		nik_ces auto _i_first_        = U_pack_Vs<instruction<CN::first>>;
		nik_ces auto _i_select_apply_ = U_pack_Vs<instruction<CN::select, _zero>, instruction<CN::apply>>;
		nik_ces auto _i_rest_         = if_then_else_<is_optimizable, _i_first_, _i_select_apply_>;
		nik_ces auto contr            = unpack_
		<
			_i_rest_, _contr_,
			instruction< CN::front , n >,
			instruction< CN::at        >
		>;

		template<typename... Ts>
		nik_ces auto result(Ts... vs) { return T_chain_start::template result<contr, lookup>(vs...); }

	}; template<auto f, auto n>
		nik_ce auto _arg_at_ = U_store_T<T_arg_at<f, n>>;

	// syntactic sugar:

		template<auto f, auto n, typename... Ts>
		nik_ce auto arg_at(Ts... vs) { return T_arg_at<f, n>::template result<>(vs...); }

/***********************************************************************************************************************/

// compose:

	template<auto f, auto gs_p>
	struct T_arg_compose
	{
		nik_ces auto lookup = U_pack_Vs<f, gs_p>;

		template<auto m = _zero, auto n = _one>
		nik_ces auto contr = controller
		<
			instruction< CN::select    , n >,
			instruction< CN::applywise     >,
			instruction< CN::select    , m >,
			instruction< CN::apply         >,
			instruction< CN::first         >
		>;

		template<typename... Ts>
		nik_ces auto result(Ts... vs) { return T_chain_start::template result<contr<>, lookup>(vs...); }

	}; template<auto f, auto gs_p>
		nik_ce auto _arg_compose_ = U_store_T<T_arg_compose<f, gs_p>>;

	template<auto f, auto... gs>
	nik_ce auto arg_compose = _arg_compose_<f, U_pack_Vs<gs...>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// jump:

/***********************************************************************************************************************/

// go to:

	template<auto... filler>
	struct T_assembly<AN::jump, AT::go_to, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(s, c, i, l, Vs), typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
		{
			nik_ce auto ins = AD::instr(c, i);
			nik_ce auto ni  = ins[AI::pos];

			return NIK_ASSEMBLY(s, c, ni, l, Vs)(vs...);
		}
	};

/***********************************************************************************************************************/

// branch:

	template<auto... filler>
	struct T_assembly<AN::jump, AT::branch, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(s, c, i, l, Vs), typename BoolType, typename... Ts>
		nik_ces auto result(BoolType v, Ts... vs) -> T_store_U<s>
		{
			nik_ce auto ins = AD::instr(c, i);
			nik_ce auto ni  = ins[AI::pos];

			if (v) return NIK_ASSEMBLY(s, c, ni, l, Vs)(vs...);
			else   return NIK_ASSEMBLY(s, c,  i, l, Vs)(vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// first:

/***********************************************************************************************************************/

// id:

	template<auto... filler>
	struct T_assembly<AN::first, AT::id, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(s, c, i, l, Vs), typename T0, typename... Ts>
		nik_ces auto result(T0 v0, Ts... vs) -> T_store_U<s>
			{ return v0; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// select:

/***********************************************************************************************************************/

// front:

	template<auto... filler>
	struct T_assembly<AN::select, AT::front, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(s, c, i, l, Vs), typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
		{
			nik_ce auto ins	= AD::instr(c, i);
			nik_ce auto n   = ins[AI::pos];
			nik_ce auto p   = eval<_par_left_, n, U_store_T<Ts>...>;

			return NIK_ASSEMBLY_TEMPLATE(c, i),

			       p

			NIK_ASSEMBLY_RESULT(s, c, i, l, Vs)(vs...);
		}
	};

/***********************************************************************************************************************/

// pair:

	template<auto... filler>
	struct T_assembly<AN::select, AT::pair, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(s, c, i, l, Vs), typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
		{
			nik_ce auto ins	= AD::instr(c, i);
			nik_ce auto n   = ins[AI::pos];
			nik_ce auto p   = unpack_<l, _par_at_, n>;
			nik_ce auto p0  = unpack_<p, _car_>;
			nik_ce auto p1  = unpack_<p, _cadr_>;

			return NIK_ASSEMBLY_TEMPLATE(c, i),

			       p0, p1

			NIK_ASSEMBLY_RESULT(s, c, i, l, Vs)(vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// right:

/***********************************************************************************************************************/

// id:

	template<template<auto...> typename B, auto... LUs, nik_vp(p)(B<LUs...>*)>
	struct T_assembly<AN::right, AT::id, p>
	{
		template<NIK_ASSEMBLY_PARAMS(s, c, i, l, Vs), typename... Ts>
		nik_ces auto result(T_store_U<LUs>... lvs, Ts... vs) -> T_store_U<s>
			{ return NIK_ASSEMBLY(s, c, i, l, Vs)(vs...); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// replace:

/***********************************************************************************************************************/

// id:

	template<template<auto...> typename B, auto... LUs, nik_vp(p)(B<LUs...>*)>
	struct T_assembly<AN::replace, AT::id, p>
	{
		template<NIK_ASSEMBLY_PARAMS(s, c, i, l, Vs), typename T, typename TN, typename... Ts>
		nik_ces auto result(T v, T_store_U<LUs>... lvs, TN vn, Ts... vs) -> T_store_U<s>
			{ return NIK_ASSEMBLY(s, c, i, l, Vs)(lvs..., v, vs...); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// call:

/***********************************************************************************************************************/

// id:

	template
	<
		template<auto...> typename B0, auto f, auto... gs, nik_vp(p0)(B0<f, gs...>*),
		template<auto...> typename B1, auto... ns, nik_vp(p1)(B1<ns...>*)
	>
	struct T_assembly<AN::call, AT::id, p0, p1>
	{
		nik_ces auto F = arg_compose<f, _arg_at_<gs, ns>...>;

		template<NIK_ASSEMBLY_PARAMS(s, c, i, l, Vs), typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
		{
			auto val = T_store_U<F>::template result<>(vs...);

			return NIK_ASSEMBLY(s, c, i, l, Vs)(val, vs...);
		}
	};

/***********************************************************************************************************************/

// side:

	template
	<
		template<auto...> typename B0, auto f, auto... gs, nik_vp(p0)(B0<f, gs...>*),
		template<auto...> typename B1, auto... ns, nik_vp(p1)(B1<ns...>*)
	>
	struct T_assembly<AN::call, AT::side, p0, p1>
	{
		nik_ces auto F = arg_compose<f, _arg_at_<gs, ns>...>;

		template<NIK_ASSEMBLY_PARAMS(s, c, i, l, Vs), typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
		{
			T_store_U<F>::template result<>(vs...);

			return NIK_ASSEMBLY(s, c, i, l, Vs)(vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// recall:

/***********************************************************************************************************************/

// id:

	template
	<
		template<auto...> typename B0, auto f, auto... gs, nik_vp(p0)(B0<f, gs...>*),
		template<auto...> typename B1, auto... ns, nik_vp(p1)(B1<ns...>*)
	>
	struct T_assembly<AN::recall, AT::id, p0, p1>
	{
		nik_ces auto F = arg_compose<f, _arg_at_<gs, ns>...>;

		template<NIK_ASSEMBLY_PARAMS(s, c, i, l, Vs), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) -> T_store_U<s>
		{
			auto val = T_store_U<F>::template result<>(v, vs...);

			return NIK_ASSEMBLY(s, c, i, l, Vs)(val, vs...);
		}
	};
	
/***********************************************************************************************************************/

// side:

	template
	<
		template<auto...> typename B0, auto f, auto... gs, nik_vp(p0)(B0<f, gs...>*),
		template<auto...> typename B1, auto... ns, nik_vp(p1)(B1<ns...>*)
	>
	struct T_assembly<AN::recall, AT::side, p0, p1>
	{
		nik_ces auto F = arg_compose<f, _arg_at_<gs, ns>...>;

		template<NIK_ASSEMBLY_PARAMS(s, c, i, l, Vs), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) -> T_store_U<s>
		{
			T_store_U<F>::template result<>(v, vs...);

			return NIK_ASSEMBLY(s, c, i, l, Vs)(vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// loop:

/***********************************************************************************************************************/

// id:

	template
	<
		template<auto...> typename B0, auto Op0, auto... Is0, nik_vp(p0)(B0<Op0, Is0...>*),
		template<auto...> typename B1, auto Op1, auto... Is1, nik_vp(p1)(B1<Op1, Is1...>*)
	>
	struct T_assembly<AN::loop, AT::id, p0, p1>
	{
		template<NIK_ASSEMBLY_PARAMS(s, c, i, l, Vs), typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
		{
			while (T_store_U<Op0>::template result<>(arg_at<Is0>(vs...)...))
				T_store_U<Op1>::template result<>(arg_at<Is1>(vs...)...);

			return NIK_ASSEMBLY(s, c, i, l, Vs)(vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// one cycle:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// predicate:

/***********************************************************************************************************************/

	// peek:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// precycle:

/***********************************************************************************************************************/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// cycle:

/***********************************************************************************************************************/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// postcycle:

/***********************************************************************************************************************/

// multimap:

/*
	template<auto f>
	struct T_multimap
	{
		using F = T_store_U<f>;

		template<typename Out, typename In, typename End, typename... Ins>
		nik_ces auto result(Out out, In in, End end, Ins... ins)
		{
			while (in != end)
			{
				*out = F::template result<In, Ins...>(in, ins...);
				++out; ++in; (++ins, ...);
			}

			return out;
		}

	}; template<auto f>
		nik_ce auto _multimap_ = U_arg_iterator<Iterator::multimap, f>;

		template<auto f>
		struct T_grammar<Shape::argument, Pattern::iterator, Iterator::multimap, f>
		{
			using F = T_store_U<f>;

			template<typename Out, typename In, typename End, typename... Ins>
			nik_ces auto result(Out out, In in, End end, Ins... ins)
			{
				while (in != end)
				{
					*out = F::template result<In, Ins...>(in, ins...);
					++out; ++in; (++ins, ...);
				}

				return out;
			}

		}; template<auto f>
			nik_ce auto _multimap_ = U_arg_iterator<Iterator::multimap, f>;

	// multifold:

		template<auto f, auto init>
		struct T_grammar<Shape::argument, Pattern::iterator, Iterator::multifold, f, init>
		{
			using F = T_store_U<f>;

			template<typename Out, typename In, typename End, typename... Ins>
			nik_ces auto result(Out out, In in, End end, Ins... ins)
			{
				*out = init;

				while (in != end)
				{
					*out = F::template result<Out, In, Ins...>(out, in, ins...);
					++in; (++ins, ...);
				}

				return out;
			}

		}; template<auto f, auto init>
			nik_ce auto _multifold_ = U_arg_iterator<Iterator::multifold, f, init>;

	// multifind:

		template<auto p>
		struct T_grammar<Shape::argument, Pattern::iterator, Iterator::multifind, p>
		{
			using P = T_store_U<p>;

			template<typename In, typename End, typename... Ins>
			nik_ces auto result(In in, End end, Ins... ins)
			{
				while (in != end)
				{
					if (P::template result<In, Ins...>(in, ins...)) break;

					++in; (++ins, ...);
				}

				return in;
			}

		}; template<auto p>
			nik_ce auto _multifind_ = U_arg_iterator<Iterator::multifind, p>;

	// multisift:

		template<auto p>
		struct T_grammar<Shape::argument, Pattern::iterator, Iterator::multisift, p>
		{
			using P = T_store_U<p>;

			template<typename Out, typename In, typename End, typename... Ins>
			nik_ces auto result(Out out, In in, End end, Ins... ins)
			{
				while (in != end)
				{
					if (P::template result<In, Ins...>(in, ins...)) *(out++) = in;

					++in; (++ins, ...);
				}

				return out;
			}

		}; template<auto p>
			nik_ce auto _multisift_ = U_arg_iterator<Iterator::multisift, p>;
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// array:

/***********************************************************************************************************************/

/*
// map:

	template<auto f, auto a, auto l, auto Op, auto s, auto U, auto S>
	nik_ce auto array_map_ = eval<_array_apply_, Op, U, S, s, _multimap_<_arg_deref_<f>>, a, l>;

// fold:

	template<auto f, auto init, auto a, auto l, auto Op, auto U, auto S>
	nik_ce auto array_fold_ = eval<_array_apply_, Op, U, S, U_pack_Vs<0>, _multifold_<_arg_deref_<f>, init>, a, l>;

// find:

//	template<auto p, auto a, auto l, auto Op, auto U, auto S>
//	nik_ce auto array_find_ = eval<_array_apply_, Op, U, S, _multifind<_arg_deref_<p>>, a, l>;
*/

// sift:

/*
// -> V:

	template<typename Type, auto p, auto Arr, auto Leng, auto... Is>
	nik_ce auto V_sift(nik_vp(indices)(T_pack_Vs<Is...>*))
	{
		nik_ce auto Size	= Leng + 1;
		nik_ce auto arr		= ArrayModule::template apply<Type, Size, IteratorModule::Sift, Leng, p>(Arr);
		nik_ce auto leng	= arr.value[Leng];

		if nik_ce (leng != sizeof...(Is)) return arr;
		else return array<Type, arr.value[Is]...>;
	}

	template<typename Type, auto p, auto Arr, auto Leng, auto I0, auto... Is>
	nik_ce auto V_sift(nik_vp(indices)(T_pack_Vs<I0, Is...>*))
	{
		nik_ce auto Size	= sizeof...(Is) + 1;
		nik_ce auto arr		= apply<Type, Size, IteratorModule::Sift, Leng, p>(Arr);

		return array<Type, arr.value[Is]...>;
	}

// -> U:

	template<typename Type, auto p, auto Arr, auto Leng, auto I0, auto... Is>
	nik_ce auto U_sift(nik_vp(indices)(T_pack_Vs<I0, Is...>*))
	{
		nik_ce auto Size	= sizeof...(Is) + 1;
		nik_ce auto arr		= apply<Type, Size, IteratorModule::Sift, Leng, p>(Arr);

		return U_pack_Vs<arr.value[Is]...>;
	}
*/

	// subsequence:

/*
// -> V:

	template<typename Type, auto p, auto Arr, auto Leng, auto... Is>
	nik_ce auto V_subsequence(nik_vp(indices)(T_pack_Vs<Is...>*))
		{ return V_apply<Type, IteratorModule::Sift, Arr>(U_pack_Vs<Leng, sizeof...(Is), p>, indices); }

// -> U:

	template<typename Type, auto p, auto Arr, auto Leng, auto... Is>
	nik_ce auto U_subsequence(nik_vp(indices)(T_pack_Vs<Is...>*))
		{ return U_apply<Type, IteratorModule::Sift, Arr>(U_pack_Vs<Leng, sizeof...(Is), p>, indices); }
*/

// zip:

/*
// generic:

// -> V:

	template<typename Type, auto f, auto Arr1, auto Leng1, auto Arr2, typename Indices>
	nik_ce auto V_zip(Indices indices)
		{ return V_apply<Type, IteratorModule::Zip, Arr1, Arr2>(U_pack_Vs<Leng1, f>, indices); }

// -> U:

	template<typename Type, auto f, auto Arr1, auto Leng1, auto Arr2, typename Indices>
	nik_ce auto U_zip(Indices indices)
		{ return U_apply<Type, IteratorModule::Zip, Arr1, Arr2>(U_pack_Vs<Leng1, f>, indices); }
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

