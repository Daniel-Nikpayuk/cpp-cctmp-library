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

		// T_variadic is an implementation of such liners.

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
			halt, mach, left, right, segment,
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
			pause, heap, join, bind, roll, part, block,
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
		using size_type			= typename instr_type::size_type;
		using csize_type		= typename instr_type::csize_type;

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

// remainder:

	template<typename SizeType>
	struct variadic_remainder
	{
		using size_type		= SizeType;
		using csize_type	= size_type const;

		csize_type roll;
		csize_type part;
		csize_type size;
		const bool block;

		nik_ce variadic_remainder(csize_type index, csize_type length, csize_type _2_N) :

			roll(index / _2_N),
			part(index % _2_N),
			size(1 + roll + 2), // left, right, segment only.
			block{has_block(length, _2_N)}

			{ }

		private:

			nik_ce bool has_block(csize_type length, csize_type _2_N) const
				{ return ((roll + 1) * _2_N <= length); }
	};

/***********************************************************************************************************************/

// unroller:

	template<typename Type, typename SizeType, SizeType Size>
	struct variadic_unroller
	{
		using contr_type	= variadic_contr<Type, SizeType, Size>;
		using size_type		= typename contr_type::size_type;
		using csize_type	= typename contr_type::csize_type;

		contr_type contr;

		template<typename Policy, typename Remain>
		nik_ce variadic_unroller(nik_avp(Policy*), Remain remain)
		{
			contr.push(VN::id, VT::id);

			for (size_type k = 0; k != remain.roll; ++k) contr.push(Policy::name, VT::roll, Policy::pos);

			Policy::rest(contr, remain);
		}
	};

/***********************************************************************************************************************/

// static:

	template<typename Policy, auto index, auto length>
	struct T_variadic_static_contr
	{
	//	static_assert(index <= length);

		using roll_type		= typename Policy::roll_type;
		using size_type		= typename Policy::size_type;

		using remain_type	= variadic_remainder<size_type>;
		nik_ces auto remain	= remain_type{index, length, Policy::_2_N};

		using unroll_type	= variadic_unroller<roll_type, size_type, remain.size>;
		nik_ces auto unroll	= unroll_type{U_store_T<Policy>, remain};

		nik_ces auto & value	= unroll.contr;

	}; template<typename P, auto i, auto l>
		nik_ce auto _variadic_contr_ = U_store_T<T_variadic_static_contr<P, i, l>>;

/***********************************************************************************************************************/

// dispatch:

	template<auto static_contr>
	struct VariadicDispatch
	{
		using size_type		= typename T_store_U<static_contr>::size_type;
		using csize_type	= size_type const;

		nik_ces auto & contr	= member_value_U<static_contr>;

		// accessors:

			nik_ces const auto & instr (csize_type i) { return contr[i]; }
			nik_ces csize_type value   (csize_type i, csize_type n) { return contr[i][n]; }

			nik_ces csize_type pos (csize_type i) { return value(i, VI::pos); }
			nik_ces csize_type num (csize_type i) { return value(i, VI::num); }

		// navigators:

			nik_ces gkey_type next_name(csize_type d, csize_type i)
			{
				if (d == 0) return VN::halt;
				else        return contr[i+1][VI::name];
			}

			nik_ces gkey_type next_note(csize_type d, csize_type i)
			{
				if (d == 0) return VT::pause;
				else        return contr[i+1][VI::note];
			}

			nik_ces csize_type next_depth(csize_type d)
				{ return d - bool{d != 0}; }

			nik_ces csize_type next_index(csize_type d, csize_type i)
				{ return i + bool{d != 0}; }
	};

	template<auto static_contr>
	using VD = VariadicDispatch<static_contr>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// praxis:

	template<gkey_type, typename SizeType = gindex_type>
	struct T_praxis
	{
		using size_type = SizeType;

		template<auto...> struct pack;

		template<size_type n, auto... Vs>
		using match = pack<n, Vs...>;
	};

/***********************************************************************************************************************/

// fold:

	// left:

		template<typename T0, typename TN, typename... Ts>
		using foldl_decltype = decltype((*(T0*) 0 + ... + *(Ts*) 0) + *(TN*) 0);

		template<typename T, auto n, auto... Vs>
		using foldl_type = foldl_decltype
		<
			typename T::template match < n  >,
			typename T::template pack  <    >,
			typename T::template pack  < Vs >...
		>;

	// right:

		template<typename T0, typename TN, typename... Ts>
		using foldr_decltype = decltype(*(TN*) 0 + (*(Ts*) 0 + ... + *(T0*) 0));

		template<typename T, auto n, auto... Vs>
		using foldr_type = foldr_decltype
		<
			typename T::template match < n  >,
			typename T::template pack  <    >,
			typename T::template pack  < Vs >...
		>;

/***********************************************************************************************************************/

// left:

	using T_left = T_praxis<VN::left>;

	template<auto... Vs>
	auto operator + (T_left::match<0, Vs...> &, T_left::pack< > &) -> T_pack_Vs<Vs...>;

	template<auto... Vs, auto V>
	auto operator + (T_left::match<0, Vs...> &, T_left::pack<V> &) -> T_left::match<0, Vs...> &;

	template<auto n, auto... Vs, auto V>
	auto operator + (T_left::match<n, Vs...> &, T_left::pack<V> &) -> T_left::match<n-1, Vs..., V> &;

/***********************************************************************************************************************/

// right:

	using T_right = T_praxis<VN::right>;

	template<auto... Vs>
	auto operator + (T_right::pack< > &, T_right::match<0, Vs...> &) -> T_pack_Vs<Vs...>;

	template<auto V, auto... Vs>
	auto operator + (T_right::pack<V> &, T_right::match<0, Vs...> &) -> T_right::match<0, Vs...> &;

	template<auto V, auto n, auto... Vs>
	auto operator + (T_right::pack<V> &, T_right::match<n, Vs...> &) -> T_right::match<n-1, V, Vs...> &;

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
		nik_ces auto i = 0;
		nik_ces auto j = 0;

		template<auto d, auto c, auto... Vs, typename... Heaps>
		nik_ces auto result(Heaps... Hs) { return NIK_VARIADIC(d, c, i, j, Vs)(Hs...); }
	};

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

// heap:

	template<auto... filler>
	struct T_variadic<VN::halt, VT::heap, filler...>
	{
		template<NIK_VARIADIC_CONTROLS(d, c, i, j), auto... Vs, typename Heap0, typename... Heaps>
		nik_ces auto result(Heap0 H0, Heaps... Hs)
			{ return H0; }
	};

/***********************************************************************************************************************/

// join:

	template<auto... filler>
	struct T_variadic<VN::halt, VT::join, filler...>
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

// bind:

	template<auto... filler>
	struct T_variadic<VN::halt, VT::bind, filler...>
	{
		template
		<
			NIK_VARIADIC_CONTROLS(d, c, i, j), auto... Vs,
			template<auto...> typename B0, auto... Ws, typename... Heaps
		>
		nik_ces auto result(nik_vp(H0)(B0<Ws...>*), Heaps... Hs)
			{ return U_store_T<B0<Ws..., Vs...>>; }
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

// left:

/***********************************************************************************************************************/

// 2^6:

	// roll:

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

	// part:

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
				nik_ce auto nH1 = U_store_T<foldl_type<T_left, n, Vs...>>;

				return NIK_VARIADIC_BEGIN(d, c, i, j)
					NIK_VARIADIC_END(H0, nH1, Hs...);
			}
		};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// right:

/***********************************************************************************************************************/

// 2^6:

	// roll:

		template<auto... filler>
		struct T_variadic<VN::right, VT::roll, filler...>
		{
			template
			<
				NIK_VARIADIC_CONTROLS(d, c, i, j),
				NIK_2_N_AUTO_VARS(6, NIK_V_1), auto... Vs, typename... Heaps
			>
			nik_ces auto result(Heaps... Hs)
			{
				return NIK_VARIADIC_BEGIN(d, c, i, j),

					Vs...

				NIK_VARIADIC_END(Hs...);
			}
		};

	// part:

		template<auto... filler>
		struct T_variadic<VN::right, VT::part, filler...>
		{
			template<NIK_VARIADIC_CONTROLS(d, c, i, j), auto... Vs, typename Heap0, typename... Heaps>
			nik_ces auto result(Heap0 H0, Heaps... Hs)
			{
				nik_ce auto n   = sizeof...(Vs) - VD<c>::pos(i);
				nik_ce auto nH0 = U_store_T<foldr_type<T_right, n, Vs...>>;

				return NIK_VARIADIC_BEGIN(d, c, i, j)
					NIK_VARIADIC_END(nH0, Hs...);
			}
		};

	// block:

		template<auto... filler>
		struct T_variadic<VN::right, VT::block, filler...>
		{
			template
			<
				NIK_VARIADIC_CONTROLS(d, c, i, j),
				NIK_2_N_AUTO_VARS(6, NIK_V_1), auto... Vs,
				typename Heap0, typename... Heaps
			>
			nik_ces auto result(Heap0 H0, Heaps... Hs)
			{
				nik_ce auto n   = VD<c>::num(i) - VD<c>::pos(i);
				nik_ce auto nH0 = U_store_T<foldr_type<T_right, n, NIK_2_N_VARS(6, NIK_V_1)>>;

				return NIK_VARIADIC_BEGIN(d, c, i, j),

					Vs...

				NIK_VARIADIC_END(nH0, Hs...);
			}
		};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// segment:

/***********************************************************************************************************************/

// 2^6:

	// roll:

		template<auto... filler>
		struct T_variadic<VN::segment, VT::roll, filler...>
		{
			template
			<
				NIK_VARIADIC_CONTROLS(d, c, i, j), auto... Vs,
				template<auto...> typename B0, auto... Ws0,
				template<auto...> typename B1, auto... Ws1,
				typename... Heaps
			>
			nik_ces auto result(nik_vp(H0)(B0<Ws0...>*), nik_vp(H1)(B1<Ws1...>*), Heaps... Hs)
			{
				nik_ce auto n   = VD<c>::pos(i);
				nik_ce auto nH0 = U_store_T<B0<Ws0..., j + Ws1...>>;

				return NIK_VARIADIC(d, c, i, j + n, Vs)(nH0, H1, Hs...);
			}
		};

	// part:

		template<auto... filler>
		struct T_variadic<VN::segment, VT::part, filler...>
		{
			template
			<
				NIK_VARIADIC_CONTROLS(d, c, i, j), auto... Vs,
				typename Heap0, template<auto...> typename B1, auto... Ws, typename... Heaps
			>
			nik_ces auto result(Heap0 H0, nik_vp(H1)(B1<Ws...>*), Heaps... Hs)
			{
				nik_ce auto n   = VD<c>::pos(i);
				nik_ce auto nH1 = U_store_T<foldl_type<T_left, n, j + Ws...>>;

				return NIK_VARIADIC(d, c, i, j, Vs)(H0, nH1, Hs...);
			}
		};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// algorithm:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// left:

/***********************************************************************************************************************/

// policy:

	template<typename RollType, typename SizeType, SizeType BlockSize>
	struct variadic_left_policy
	{
		using roll_type		= RollType;
		using size_type		= SizeType;
		using csize_type	= size_type const;

		nik_ces size_type name	= VN::left;
		nik_ces size_type pos	= 0;
		nik_ces size_type _2_N	= BlockSize;

		template<typename Contr, typename Remain>
		nik_ces void rest(Contr & contr, const Remain & remain)
		{
			contr.push(VN::left, VT::part, remain.part);
			contr.push(VN::halt, VT::join);
		}
	};

/***********************************************************************************************************************/

// interface:

	template<typename Type = gindex_type, typename SizeType = gindex_type, SizeType _2_N = _2_6>
	struct T_variadic_left
	{
		using policy = variadic_left_policy<Type, SizeType, _2_N>;

		template<auto n, auto l>
		nik_ces auto contr = _variadic_contr_<policy, n, l>;

		template<auto d, auto n, auto... Vs>
		nik_ces auto result = T_variadic_start::template
					result<d, contr<n, sizeof...(Vs)>, Vs...>(U_null_Vs, U_null_Vs);
	};

	// syntactic sugar:

		template<auto n, auto... Vs>
		nik_ce auto left_ = T_variadic_left<>::template result<500, n, Vs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// right:

/***********************************************************************************************************************/

// policy:

	template<typename RollType, typename SizeType, SizeType BlockSize>
	struct variadic_right_policy
	{
		using roll_type		= RollType;
		using size_type		= SizeType;
		using csize_type	= size_type const;

		nik_ces size_type name	= VN::right;
		nik_ces size_type pos	= 0;
		nik_ces size_type _2_N	= BlockSize;

		template<typename Contr, typename Remain>
		nik_ces void rest_has_block(Contr & contr, const Remain & remain)
		{
			contr.push(VN::right, VT::block, remain.part, _2_N);
			contr.push(VN::halt, VT::bind);
		}

		template<typename Contr, typename Remain>
		nik_ces void rest_lacks_block(Contr & contr, const Remain & remain)
		{
			contr.push(VN::right, VT::part, remain.part);
			contr.push(VN::halt, VT::heap);
		}

		template<typename Contr, typename Remain>
		nik_ces void rest(Contr & contr, const Remain & remain)
		{
			if (remain.block) rest_has_block   (contr, remain);
			else              rest_lacks_block (contr, remain);
		}
	};

/***********************************************************************************************************************/

// interface:

	template<typename Type = gindex_type, typename SizeType = gindex_type, SizeType _2_N = _2_6>
	struct T_variadic_right
	{
		using policy = variadic_right_policy<Type, SizeType, _2_N>;

		template<auto n, auto l>
		nik_ces auto contr = _variadic_contr_<policy, n, l>;

		template<auto d, auto n, auto... Vs>
		nik_ces auto result = T_variadic_start::template
					result<d, contr<n, sizeof...(Vs)>, Vs...>(U_null_Vs, U_null_Vs);
	};

	// syntactic sugar:

		template<auto n, auto... Vs>
		nik_ce auto right_ = T_variadic_right<>::template result<500, n, Vs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// segment:

/***********************************************************************************************************************/

// policy:

	template<typename RollType, typename SizeType, SizeType BlockSize>
	struct variadic_segment_policy
	{
		using roll_type		= RollType;
		using size_type		= SizeType;
		using csize_type	= size_type const;

		nik_ces size_type name	= VN::segment;
		nik_ces size_type pos	= BlockSize;
		nik_ces size_type _2_N	= BlockSize;

		template<typename Contr, typename Remain>
		nik_ces void rest(Contr & contr, const Remain & remain)
		{
			contr.push(VN::segment, VT::part, remain.part);
			contr.push(VN::halt, VT::join);
		}
	};

/***********************************************************************************************************************/

// interface:

	template<typename Type = gindex_type, typename SizeType = gindex_type, SizeType _2_N = _2_6>
	struct T_variadic_segment
	{
		using policy = variadic_segment_policy<Type, SizeType, _2_N>;

		nik_ces auto pack = U_pack_Vs<NIK_2_N_SEGMENT_VARS(6, NIK_EMPTY)>;

		template<auto n, auto l>
		nik_ces auto contr = _variadic_contr_<policy, n, l>;

		template<auto d, auto n, auto... Vs>
		nik_ces auto result = T_variadic_start::template
					result<d, contr<n, sizeof...(Vs)>, Vs...>(U_null_Vs, pack);
	};

	// syntactic sugar:

		template<auto n, auto... Vs>
		nik_ce auto segment_ = T_variadic_segment<>::template result<500, n, Vs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

