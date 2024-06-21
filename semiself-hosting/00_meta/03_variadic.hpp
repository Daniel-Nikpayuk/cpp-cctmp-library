/************************************************************************************************************************
**
** Copyright 2022-2024 Daniel Nikpayuk, Inuit Nunangat, The Inuit Nation
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

// variadic:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// machination:

		// Definition: A liner (trampoliner) is a nest-resulted struct that either returns
		// its value of interest, or a machination with the same structure as its input.
		// It is expected that all other nest-resulted structs are defined from such liners.

		// Both T_variadic and T_interpreter are implementations of such liners.

	template<typename Mach, typename Param, typename Heap>
	struct machination
	{
		Mach mach;
		Param param;
		Heap heap;

		nik_ce machination(const Mach & m, const Param & p, const Heap & h) :
			mach{m}, param{p}, heap{h} { }
	};

/***********************************************************************************************************************/

// is machination:

	template<typename T>
	nik_ce bool is_machination = false;

	template<typename M, typename P, typename H>
	nik_ce bool is_machination<machination<M, P, H>> = true;

	template<typename M, typename P, typename H>
	nik_ce bool is_machination<machination<M, P, H> const> = true;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// space:

	template<gkey_type, gkey_type, auto...> struct T_variadic;

	template<auto Name, auto Note, auto... Vs>
	nik_ce auto U_variadic = U_store_T<T_variadic<Name, Note, Vs...>>;

/***********************************************************************************************************************/

// names:

	struct VariadicName
	{
		enum : gkey_type
		{
			identity = 0, id = identity, // convenience for default params.
			halt, mach, count, left, segment,
			dimension
		};
	};

	using VN = VariadicName;

/***********************************************************************************************************************/

// notes:

	struct VariadicNote
	{
		enum : gkey_type
		{
			identity = 0, id = identity, // convenience for default params.
			pause, debug, first, heap, front,
			iter, copy, push, pull, proj,
			roll, part, catenate,
			dimension
		};
	};

	using VT = VariadicNote;

/***********************************************************************************************************************/

// index:

	struct VariadicIndex { enum : gkey_type { name, note, pos, num, dimension }; };

	using VI = VariadicIndex;

/***********************************************************************************************************************/

// instr:

	template<typename Type, typename SizeType>
	struct variadic_instr
	{
		using type			= Type;
		using type_ref			= type &;
		using ctype			= type const;
		using ctype_ref			= ctype &;
		using size_type			= SizeType;
		using csize_type		= size_type const;

		using Index 			= VariadicIndex;

		type initial[Index::dimension];

		nik_ce variadic_instr() : initial{} { }

		nik_ce ctype_ref operator [] (csize_type n) const { return initial[n]; }
		nik_ce  type_ref operator [] (csize_type n)       { return initial[n]; }

		nik_ce void set(csize_type n, csize_type t, csize_type p, csize_type m)
		{
			initial[Index::name] = n;
			initial[Index::note] = t;
			initial[Index::pos ] = p;
			initial[Index::num ] = m;
		}
	};

/***********************************************************************************************************************/

// contr:

	template<typename Type, typename SizeType, SizeType Size>
	struct variadic_contr
	{
		using instr_type		= variadic_instr<Type, SizeType>;
		using instr_ref			= instr_type &;
		using cinstr_type		= instr_type const;
		using cinstr_ref		= cinstr_type &;
		using type			= typename instr_type::type;
		using type_ref			= typename instr_type::type_ref;
		using ctype			= typename instr_type::ctype;
		using ctype_ref			= typename instr_type::ctype_ref;
		using size_type			= typename instr_type::size_type;
		using csize_type		= typename instr_type::csize_type;
		using Index			= typename instr_type::Index;

		nik_ces size_type length	= Size;

		instr_type initial[length];
		size_type current;

		nik_ce variadic_contr() : initial{}, current{} { }

		nik_ce cinstr_ref operator [] (csize_type n) const { return initial[n]; }
		nik_ce  instr_ref operator [] (csize_type n)       { return initial[n]; }

		nik_ce void push(csize_type n, csize_type t, csize_type p = 0, csize_type m = 0)
			{ initial[current++].set(n, t, p, m); }
	};

/***********************************************************************************************************************/

// unroller:

	template<typename Type, typename SizeType, SizeType Size>
	struct variadic_unroller
	{
		using contr_type		= variadic_contr<Type, SizeType, Size>;
		using type			= typename contr_type::type;
		using type_ref			= typename contr_type::type_ref;
		using ctype			= typename contr_type::ctype;
		using ctype_ref			= typename contr_type::ctype_ref;
		using size_type			= typename contr_type::size_type;
		using csize_type		= typename contr_type::csize_type;
		using Index			= typename contr_type::Index;

		nik_ces size_type length	= Size;

		contr_type contr;

		nik_ce variadic_unroller(csize_type n, csize_type r, csize_type p) { unroll(n, r, p); }

		nik_ce void unroll(csize_type name, csize_type roll, csize_type part)
		{
			contr.push(VN::id, VT::id);

			for (size_type k = 0; k != roll; ++k) contr.push(name, VT::roll);

			contr.push(name, VT::part, part);
			contr.push(VN::halt, VT::catenate);
		}
	};

/***********************************************************************************************************************/

// static:

	template<auto name, auto index, auto length, auto _2_N>
	struct T_variadic_static_contr
	{
		static_assert(index <= length);

		nik_ces auto roll	= index / _2_N;
		nik_ces auto part	= index % _2_N;
		nik_ces auto size	= 1 + roll + 2;

						// generalize gindex_type:
		using unroll_type	= variadic_unroller<gindex_type, gindex_type, size>;
		nik_ces auto unroll	= unroll_type{name, roll, part};

		nik_ces auto & value	= unroll.contr;

	}; template<auto n, auto i, auto l, auto _2_N>
		nik_ce auto _variadic_contr_ = U_store_T<T_variadic_static_contr<n, i, l, _2_N>>;

/***********************************************************************************************************************/

// dispatch:

	// generalize gindex_type.

	template<auto static_contr, auto _count = 0, auto _index = 0, auto _depth = 500, auto _size = _2_6>
	struct VariadicDispatch
	{
		nik_ces auto & contr = member_value_U<static_contr>;

		// defaults:

			nik_ces gindex_type initial_count = _count;
			nik_ces gindex_type initial_index = _index;
			nik_ces gdepth_type initial_depth = _depth;
			nik_ces gindex_type block_size    = _size;

		// accessors:

			nik_ces const auto & instr (gcindex_type i) { return contr[i]; }
			nik_ces gindex_type value  (gcindex_type i, gcindex_type n) { return contr[i][n]; }

			nik_ces gindex_type pos  (gcindex_type i) { return value(i, VI::pos); }
			nik_ces gindex_type num  (gcindex_type i) { return value(i, VI::num); }

		// navigators:

			nik_ces gkey_type next_name(gcdepth_type d, gcindex_type i)
			{
				if (d == 0) return VN::halt;
				else        return contr[i+1][VI::name];
			}

			nik_ces gkey_type next_note(gcdepth_type d, gcindex_type i)
			{
				if (d == 0) return VT::pause;
				else        return contr[i+1][VI::note];
			}

			nik_ces gdepth_type next_depth(gcdepth_type d)
				{ return d - bool{d != 0}; }

			nik_ces gindex_type next_index(gcdepth_type d, gcindex_type i)
				{ return i + bool{d != 0}; }
	};

	template<auto static_contr, auto _count = 0, auto _index = 0, auto _depth = 500, auto _size = _2_6>
	using VD = VariadicDispatch<static_contr, _count, _index, _depth, _size>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// algorithm:

	template<gkey_type, typename SizeType = gindex_type>
	struct T_algorithm
	{
		using size_type = SizeType;

		template<auto...> struct pack;

		template<size_type n, auto... Vs>
		using match = pack<n, Vs...>;
	};

/***********************************************************************************************************************/

// fold:

	// decltype:

		template<typename T0, typename TN, typename... Ts>
		using fold_decltype = decltype((*(T0*) 0 + ... + *(Ts*) 0) + *(TN*) 0);

	// type:

		template<typename T, auto n, auto... Vs>
		using fold_type = fold_decltype
		<
			typename T::template match < n  >,
			typename T::template pack  <    >,
			typename T::template pack  < Vs >...
		>;

/***********************************************************************************************************************/

// left:

	using T_left = T_algorithm<VN::left>;

	template<auto... Vs>
	auto operator + (T_left::match<0, Vs...> &, T_left::pack< > &) -> T_pack_Vs<Vs...>;

	template<auto... Vs, auto V>
	auto operator + (T_left::match<0, Vs...> &, T_left::pack<V> &) -> T_left::match<0, Vs...> &;

	template<auto n, auto... Vs, auto V>
	auto operator + (T_left::match<n, Vs...> &, T_left::pack<V> &) -> T_left::match<n-1, Vs..., V> &;

/***********************************************************************************************************************/

// segment:

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// machine:

/***********************************************************************************************************************/

// start:

	struct T_variadic_start
	{
		template<auto d, auto c, auto... Vs, typename... Heaps>
		nik_ces auto result(Heaps... Hs)
		{
			nik_ce auto i = VD<c>::initial_index;
			nik_ce auto j = VD<c>::initial_count;

			return NIK_VARIADIC(d, c, i, j, Vs)(Hs...);
		}

	}; // nik_ce auto U_variadic_start = U_custom_T<T_variadic_start>;

/***********************************************************************************************************************/

// jstart:

	struct T_variadic_jstart
	{
		template<auto d, auto c, auto j, auto... Vs, typename... Heaps>
		nik_ces auto result(Heaps... Hs)
		{
			nik_ce auto i = VD<c>::initial_index;

			return NIK_VARIADIC(d, c, i, j, Vs)(Hs...);
		}

	}; // nik_ce auto U_variadic_jstart = U_custom_T<T_variadic_jstart>;

/***********************************************************************************************************************/

// restart:

	struct T_variadic_restart
	{
		template<NIK_VARIADIC_CONTROLS(d, c, i, j), auto... Vs, typename... Heaps>
		nik_ces auto result(Heaps... Hs) { return NIK_VARIADIC(d, c, i, j, Vs)(Hs...); }

	}; nik_ce auto U_variadic_restart = U_store_T<T_variadic_restart>; // expected to be a store.

/***********************************************************************************************************************/

// machinate:

	struct T_variadic_machinate
	{
		template
		<
			auto d, typename U_mach,
			template<auto...> typename BP, auto c, auto... ps,
			template<auto...> typename BH, auto... hs
		>
		nik_ces auto result(U_mach m, nik_vp(p)(BP<c, ps...>*), nik_vp(h)(BH<hs...>*))
		{
			if nik_ce (d == 0) return machination(m, p, h);

			nik_ce auto nd = VD<c>::next_depth(d);
			nik_ce auto v  = T_restore_T<U_mach>::template result<nd, c, ps...>(hs...);

			if nik_ce (not is_machination<decltype(v)>) return v;
			else return T_variadic_machinate::template result<nd>(v.mach, v.param, v.heap);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// halt:

/***********************************************************************************************************************/

// pause:

	template<auto... filler>
	struct T_variadic<VN::halt, VT::pause, filler...>
	{
		template<NIK_VARIADIC_CONTROLS(d, c, i, j), auto... Vs, typename... Heaps>
		nik_ces auto result(Heaps... Hs)
		{
			nik_ce auto param = U_pack_Vs<c, i, j, Vs...>;
			nik_ce auto heap  = U_pack_Vs<U_restore_T<Heaps>...>;

			return machination(U_variadic_restart, param, heap);
		}
	};

/***********************************************************************************************************************/

// debug:

/*
	template<auto... filler>
	struct T_variadic<VN::halt, VT::debug, filler...>
	{
		template<NIK_VARIADIC_CONTROLS(d, c, i, j), auto... Vs, typename... Heaps>
		nik_ces auto result(Heaps... Hs)
		{
			nik_ce auto cs = list_<d, c, i, j>;
			nik_ce auto rs = list_<Vs...>;
			nik_ce auto hs = list_<U_restore_T<Heaps>...>;

			return list_<cs, rs, hs>;
		}
	};
*/

/***********************************************************************************************************************/

// first:

	template<auto... filler>
	struct T_variadic<VN::halt, VT::first, filler...>
	{
		template<NIK_VARIADIC_CONTROLS(d, c, i, j), auto V, auto... Vs, typename... Heaps>
		nik_ces auto result(Heaps... Hs) { return V; }
	};

/***********************************************************************************************************************/

// heap:

	template<auto... filler>
	struct T_variadic<VN::halt, VT::heap, filler...>
	{
		template
		<
			NIK_VARIADIC_CONTROLS(d, c, i, j), auto... Vs,
			template<auto...> typename B0, auto... Ws, typename... Heaps
		>
		nik_ces auto result(nik_vp(H0)(B0<Ws...>*), Heaps... Hs) { return U_store_T<B0<Vs...>>; }
	};

/***********************************************************************************************************************/

// front:

	template<auto... filler>
	struct T_variadic<VN::halt, VT::front, filler...>
	{
		template<NIK_VARIADIC_PARAMS(d, c, i, j, Vs), typename Heap0, typename... Heaps>
		nik_ces auto result(Heap0 H0, Heaps... Hs) { return H0; }
	};

/***********************************************************************************************************************/

// catenate:

	template<auto... filler>
	struct T_variadic<VN::halt, VT::catenate, filler...>
	{
		template
		<
			NIK_VARIADIC_CONTROLS(d, c, i, j), auto... Vs,
			template<auto...> typename B0, auto... Ws0,
			template<auto...> typename B1, auto... Ws1,
			typename... Heaps
		>
		nik_ces auto result(nik_vp(H0)(B0<Ws0...>*), nik_vp(H1)(B1<Ws1...>*), Heaps... Hs)
			{ return U_store_T<B0<Ws0..., Ws1...>>; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// mach:

/***********************************************************************************************************************/

// id:

	template<auto... filler>
	struct T_variadic<VN::mach, VT::id, filler...>
	{
		template<NIK_VARIADIC_PARAMS(d, c, i, j, Vs), typename... Heaps>
		nik_ces auto result(Heaps... Hs)
		{
			nik_ce auto v = NIK_VARIADIC(d, c, i, j, Vs)(U_restore_T<Heaps>...);

			if nik_ce (not is_machination<decltype(v)>) return v;
			else
			{
				nik_ce auto nd = VD<c>::next_depth(d);

				return T_variadic_machinate::template result<nd>(v.mach, v.param, v.heap);
			}
		}
	};

/***********************************************************************************************************************/

// iter(ate):

/*
	template<auto... filler>
	struct T_variadic<VN::mach, VT::iter, filler...>
	{
		template<NIK_VARIADIC_CONTROLS(d, c, i, j), auto... Vs, typename Heap0, typename Heap1, typename... Heaps>
		nik_ces auto result(Heap0, Heap1, Heaps... Hs)
		{
			nik_ce auto & ins = VD<c>::instr(i);
			nik_ce auto n     = ins[VI::pos];
			nik_ce auto Op    = U_restore_T<Heap1>;

			if nik_ce (d < n)
			{
				nik_ce auto param = U_pack_Vs<c, i, j, Vs...>;
				nik_ce auto H0    = U_restore_T<Heap0>;
				nik_ce auto heap  = U_pack_Vs<H0, Op, U_restore_T<Heaps>...>;

				return machination(U_variadic_restart, param, heap);
			}
			else
			{
				nik_ce auto v = eval<Op, Vs...>;

				if nik_ce (not is_machination<decltype(v)>) return v;
				else
				{
					nik_ce auto nd = VD<c>::next_depth(d);

					return T_variadic_machinate::template result<nd>(v.mach, v.param, v.heap);
				}
			}
		}
	};
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// count:

/***********************************************************************************************************************/

// copy:

	template<auto... filler>
	struct T_variadic<VN::count, VT::copy, filler...>
	{
		template<NIK_VARIADIC_CONTROLS(d, c, i, j), auto... Vs, typename... Heaps>
		nik_ces auto result(Heaps... Hs)
		{
			return NIK_VARIADIC_BEGIN(d, c, i, j),

				j, Vs...

			NIK_VARIADIC_END(Hs...);
		}
	};

/***********************************************************************************************************************/

// proj:

	template<auto... filler>
	struct T_variadic<VN::count, VT::proj, filler...>
	{
		template<NIK_VARIADIC_CONTROLS(d, c, i, j), auto V0, auto... Vs, typename... Heaps>
		nik_ces auto result(Heaps... Hs)
		{
			return NIK_VARIADIC_BEGIN(d, c, i, j),

				j, Vs...

			NIK_VARIADIC_END(Hs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// left:

/***********************************************************************************************************************/

// 2^6:

	// next:

		template<auto... filler>
		struct T_variadic<VN::left, VT::roll, filler...>
		{
			template
			<
				NIK_VARIADIC_CONTROLS(d, c, i, j),
				NIK_2_N_AUTO_VARS(6, NIK_V_1), auto... Vs,
				template<auto...> typename B0, auto... Ws, typename... Heaps
			>
			nik_ces auto result(nik_vp(H0)(B0<Ws...>*), Heaps... Hs)
			{
				nik_ce auto nH0 = U_store_T<B0<Ws..., NIK_2_N_VARS(6, NIK_V_1)>>;

				return NIK_VARIADIC_BEGIN(d, c, i, j),

					Vs...

				NIK_VARIADIC_END(nH0, Hs...);
			}
		};

	// last:

		template<auto... filler>
		struct T_variadic<VN::left, VT::part, filler...>
		{
			template
			<
				NIK_VARIADIC_CONTROLS(d, c, i, j), auto... Vs,
				typename Heap0, typename Heap1, typename... Heaps
			>
			nik_ces auto result(Heap0 H0, Heap1 H1, Heaps... Hs)
			{
				nik_ce auto n   = VD<c>::pos(i);
				nik_ce auto nH1 = U_store_T<fold_type<T_left, n, Vs...>>;

				return NIK_VARIADIC_BEGIN(d, c, i, j)
					NIK_VARIADIC_END(H0, nH1, Hs...);
			}
		};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// segment:

/***********************************************************************************************************************/

// 2^6:

	// push:

		template<auto... filler>
		struct T_variadic<VN::segment, VT::roll, filler...>
		{
			template<NIK_VARIADIC_CONTROLS(d, c, i, j), auto... Vs, typename... Heaps>
			nik_ces auto result(Heaps... Hs)
			{
				return NIK_VARIADIC_BEGIN(d, c, i, j + _2_6),

					Vs..., NIK_2_N_SEGMENT_VARS(6, NIK_LJ) // NIK_LJ, or j directly ?

				NIK_VARIADIC_END(Hs...);
			}
		};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// left:

	template<gindex_type _2_N = _2_6>
	struct T_variadic_left
	{
		template<auto n, auto l>
		nik_ces auto contr = _variadic_contr_<VN::left, n, l, _2_N>;

		template<auto d, auto n, auto... Vs>
		nik_ces auto result = T_variadic_start::template
					result<d, contr<n, sizeof...(Vs)>, Vs...>(U_null_Vs, U_null_Vs);
	};

	// syntactic sugar:

	//	nik_ce auto _dpar_left_ = U_custom_T<T_variadic_left<>>;
	//	nik_ce auto  _par_left_ = _alias_<_dpar_left_, 500>;

	//	template<auto p, auto n>
	//	nik_ce auto left_ = unpack_<p, _dpar_left_, 500, n>;

		template<auto n, auto... Vs>
		nik_ce auto left_ = T_variadic_left<>::template result<500, n, Vs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

