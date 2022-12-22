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

	// extend macros to explicate between PA and PP before copying over!
	// fix "adjusted" with a lookup alias.

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

} // cctmp

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// halt:

/***********************************************************************************************************************/

// pause:

/*
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
*/

/***********************************************************************************************************************/

// debug:

/*
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
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// algorithm:

/*
	template<auto...> struct T_algorithm;
	template<auto... Vs> nik_ce auto _algorithm_ = U_custom_T<T_algorithm<Vs...>>;
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// block:

/*
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

