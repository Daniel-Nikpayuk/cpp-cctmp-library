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

// lookup:

namespace chord {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

	template<typename T>
	nik_ce auto U_restore_T					= cctmp::U_restore_T<T>;

	template<auto... Vs>
	using T_pack_Vs						= cctmp::T_pack_Vs<Vs...>;

	template<typename... Ts>
	nik_ce auto U_pack_Ts					= cctmp::U_pack_Ts<Ts...>;

	nik_ce auto _nop_					= cctmp::_nop_;

	nik_ce auto _car_					= cctmp::_car_;
	nik_ce auto _cadr_					= cctmp::_cadr_;

	template<typename T>
	nik_ce auto U_custom_T					= cctmp::U_custom_T<T>;

	nik_ce auto _read_write_				= cctmp::_read_write_;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// space:

	template<gkey_type, gkey_type, auto...> struct T_lookup;

/***********************************************************************************************************************/

// dispatch:

	template<token_type, auto...> struct T_morph_dispatch;
	template<token_type, auto...> struct T_cycle_dispatch;

/***********************************************************************************************************************/

// names:

	struct LookupName
	{
		enum : gkey_type
		{
			line, link, env,
			dimension
		};
	};

	using LN = LookupName;

/***********************************************************************************************************************/

// notes:

	struct LookupNote
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.
			unit, vo_id, swap, apply,		// line
			mu_table, constant, tree, morph, cycle,	// link
			frame,					// env
			dimension
		};
	};

	using LT = LookupNote;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// env:

	template<auto... Vs> using T_lookup_frame		= T_lookup < LN::env , LT::frame , Vs... >;

	template<auto... Vs> nik_ce auto U_lookup_frame		= U_store_T < T_lookup_frame < Vs... > >;

/***********************************************************************************************************************/

// frame:

	template<auto... static_frames, nik_vp(env)(T_pack_Vs<static_frames...>*)>
	struct T_lookup<LN::env, LT::frame, env>
	{
		using pair_type  = cctmp::pair<gindex_type, gindex_type>;
		using citer_type = cctmp::citerator<strlit_type>;

		nik_ces void update_frame(pair_type & pos, bool & match, citer_type k)
		{
			if (!match)
			{
				match   = k.not_end();
				pos.v0 += not match;
				pos.v1  = k.left_size();
			}
		}

		template<typename EntryType>
		nik_ces auto find_frame(const EntryType & entry)
		{
			pair_type pos;
			bool match{false};

			(update_frame(pos, match, member_value_U<static_frames>.contains(entry)), ...);

			return pos;
		}

		template<auto pos, auto key>
		nik_ces auto map()
		{
			nik_ce auto static_frame = eval<_par_at_, pos, static_frames...>;
			nik_ce auto & frame      = member_value_U<static_frame>;

			return frame.template map<key>();
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// link:

	template<auto... Vs> using T_lookup_id_link		= T_lookup < LN::link , LT::id       , Vs... >;

	template<auto... Vs> using T_lookup_morph_link		= T_lookup < LN::link , LT::morph    , Vs... >;
	template<auto... Vs> using T_lookup_cycle_link		= T_lookup < LN::link , LT::cycle    , Vs... >;
	template<auto... Vs> using T_lookup_tree_link		= T_lookup < LN::link , LT::tree     , Vs... >;
	template<auto... Vs> using T_lookup_constant_link	= T_lookup < LN::link , LT::constant , Vs... >;
	template<auto... Vs> using T_lookup_mutable_link	= T_lookup < LN::link , LT::mu_table , Vs... >;

	template<auto... Vs> nik_ce auto U_lookup_morph_link	= U_store_T < T_lookup_morph_link    < Vs... > >;
	template<auto... Vs> nik_ce auto U_lookup_cycle_link	= U_store_T < T_lookup_cycle_link    < Vs... > >;
	template<auto... Vs> nik_ce auto U_lookup_tree_link	= U_store_T < T_lookup_tree_link     < Vs... > >;
	template<auto... Vs> nik_ce auto U_lookup_constant_link	= U_store_T < T_lookup_constant_link < Vs... > >;
	template<auto... Vs> nik_ce auto U_lookup_mutable_link	= U_store_T < T_lookup_mutable_link  < Vs... > >;

/***********************************************************************************************************************/

// id (helper):

	template<auto env>
	struct T_lookup<LN::link, LT::id, env>
	{
		template<auto entry_disp, auto l, auto n, auto m, auto... Us>
		nik_ces auto result(nik_avp(T_pack_Vs<Us...>*))
		{
			nik_ce auto & entry = entry_disp(l, n, m);
			nik_ce auto sign    = entry.sign;

			if nik_ce (Sign::is_static_arg(sign))
			{
				nik_ce auto U = eval<_par_at_, entry.index, Us...>;

				return U_restore_T<T_store_U<U>>; // constexpr cast
			}
			else if nik_ce (Sign::is_env(sign))
			{
				using T_frame_lookup = T_lookup_frame<env>;
				nik_ce auto record   = T_frame_lookup::find_frame(entry);

				return T_frame_lookup::template map<record.v0, record.v1>();
			}
			else return _id_; // error
		}
	};

/***********************************************************************************************************************/

// morph:

	template<auto static_parsed, auto this_f, auto env>
	struct T_lookup<LN::link, LT::morph, static_parsed, this_f, env>
	{
		nik_ces auto & parsed = member_value_U<static_parsed>;
		using dispatch        = T_lookup_id_link<env>;

		nik_ces auto & parameter_entry(gindex_type l, gindex_type n, gindex_type m)
			{ return parsed.morph_level[l].parameter[m]; }

		template<auto l, auto m, typename Pack>
		nik_ces auto result(Pack p)
			{ return dispatch::template result<parameter_entry, l, 0, m>(p); }
	};

/***********************************************************************************************************************/

// cycle:

	template<auto static_parsed, auto this_f, auto env>
	struct T_lookup<LN::link, LT::cycle, static_parsed, this_f, env>
	{
		nik_ces auto & parsed = member_value_U<static_parsed>;
		using dispatch        = T_lookup_id_link<env>;

		// action:

			nik_ces auto & action_entry(gindex_type l, gindex_type n, gindex_type m)
				{ return parsed.cycle_level[l].action[m]; }

			template<auto l, auto m, typename Pack>
			nik_ces auto action(Pack p)
				{ return dispatch::template result<action_entry, l, 0, m>(p); }

		// parameter:

			nik_ces auto & parameter_entry(gindex_type l, gindex_type n, gindex_type m)
				{ return parsed.cycle_level[l].parameter[n][m]; }

			template<auto l, auto n, auto m, typename Pack>
			nik_ces auto parameter(Pack p)
				{ return dispatch::template result<parameter_entry, l, n, m>(p); }

		// iterator:

			nik_ces auto & iterator_entry(gindex_type l, gindex_type n, gindex_type m)
				{ return parsed.cycle_level[l].iterator[n][m]; }

			template<auto l, auto n, auto m, typename Pack>
			nik_ces auto iterator(Pack p)
				{ return dispatch::template result<iterator_entry, l, n, m>(p); }

		// tonic:

			nik_ces auto & tonic_entry(gindex_type l, gindex_type n, gindex_type m)
				{ return parsed.cycle_level[l].tonic_iter[m]; }

			template<auto l, auto m, typename Pack>
			nik_ces auto tonic(Pack p)
				{ return dispatch::template result<tonic_entry, l, 0, m>(p); }
	};

/***********************************************************************************************************************/

// tree:

	template<auto static_parsed, auto this_f, auto env>
	struct T_lookup<LN::link, LT::tree, static_parsed, this_f, env>
	{
		nik_ces auto & parsed = member_value_U<static_parsed>;

		template<auto n, auto m, auto... Us>
		nik_ces auto result(nik_vp(U)(T_pack_Vs<Us...>*))
		{
			nik_ce auto sign = parsed.link_entry_sign(n, m);

			if nik_ce (Sign::is_static_arg(sign))
			{
				nik_ce auto pos = parsed.link_entry_index(n, m);
				nik_ce auto U   = eval<_par_at_, pos, Us...>;

				return U_restore_T<T_store_U<U>>; // constexpr cast
			}
			else if nik_ce (Sign::is_env(sign))
			{
				using T_frame_lookup = T_lookup_frame<env>;
				nik_ce auto & entry  = parsed.link_entry(n, m);
				nik_ce auto record   = T_frame_lookup::find_frame(entry);

				return T_frame_lookup::template map<record.v0, record.v1>();
			}
			else if nik_ce (Sign::is_morph(sign))
			{
				nik_ce auto index  = parsed.link_entry_index(n, m);
				nik_ce auto & line = parsed.morph_level[index];
				nik_ce auto pack   = eval<_par_segment_, line.parameter.size()>;
				nik_ce auto types  = U_restore_T<decltype(U)>;
				using T_morph      = T_morph_dispatch<line.token, static_parsed, this_f, env>;

				return T_morph::template result<index, types>(pack);
			}
			else if nik_ce (Sign::is_cycle(sign))
			{
				nik_ce auto index = parsed.link_entry_index(n, m);
				nik_ce auto token = parsed.cycle_level[index].token;
				nik_ce auto size  = parsed.cycle_level[index].interval.size();
				nik_ce auto notes = eval<_par_segment_, size>;
				nik_ce auto types = U_restore_T<decltype(U)>;
				using T_cycle     = T_cycle_dispatch<token, static_parsed, this_f, env>;

				return T_cycle::template result<index, types>(notes);
			}
			else if nik_ce (Sign::is_recurse(sign)) return this_f;
			else return _nop_; // error
		}

		template<auto n, auto m, typename... Ts>
		nik_ces auto result(Ts...) { return result<n, m>(U_pack_Ts<Ts...>); }
	};

/***********************************************************************************************************************/

// constant:

	template<auto U_link>
	struct T_lookup<LN::link, LT::constant, U_link>
	{
		using T_link = T_store_U<U_link>;

		template<auto n, auto m, typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto pos = T_link::parsed.link_entry_index(n, m);

			return T_apply_at<_id_, pos>::template result<Ts...>(vs...);
		}
	};

/***********************************************************************************************************************/

// mutable:

	// pointer:

		template<auto U_link, typename T, nik_vp(U)(T*)>
		struct T_lookup<LN::link, LT::mu_table, U_link, U>
		{
			using T_link = T_store_U<U_link>;
			using Type   = modify_type<_read_write_, T>;

			template<auto n, auto m, typename... Ts>
			nik_ces auto result(Ts... vs) -> Type
			{
				nik_ce auto pos = T_link::parsed.link_entry_index(n, m);

				return const_cast<Type>(T_apply_at<_id_, pos>::template result<Ts...>(vs...));
			}
		};

	// reference:

		template<auto U_link, typename T, nik_vp(U)(T&)>
		struct T_lookup<LN::link, LT::mu_table, U_link, U>
		{
			using T_link = T_store_U<U_link>;
			using Type   = modify_type<_read_write_, T>;

			template<auto n, auto m, typename... Ts>
			nik_ces auto result(Ts... vs) -> Type&
			{
				nik_ce auto pos = T_link::parsed.link_entry_index(n, m);

				return const_cast<Type&>(T_ref_at<pos>::template result<Ts...>(vs...));
			}
		};

/***********************************************************************************************************************/

// resolve:

	template<typename T_link, auto n, auto m, auto... Us>
	nik_ce auto dispatch_link()
	{
		nik_ce auto sign   = T_link::parsed.link_entry_sign(n, m);
		nik_ce auto U_link = U_store_T<T_link>;

		if nik_ce (Sign::is_mutable_arg(sign))
		{
			nik_ce auto pos = T_link::parsed.link_entry_index(n, m);
			nik_ce auto U   = eval<_par_at_, pos, Us...>;

			return U_lookup_mutable_link<U_link, U>;
		}
		else if nik_ce (Sign::is_constant_arg(sign) || Sign::is_paste(sign))

			return U_lookup_constant_link<U_link>;
		else
			return U_link;
	}

	template<typename T_link, auto n, auto m, typename... Ts>
	using T_resolve_link = T_store_U<dispatch_link<T_link, n, m, U_store_T<Ts>...>()>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// line:

	template<auto... Vs> using T_lookup_unit		= T_lookup < LN::line , LT::unit  , Vs... >;
	template<auto... Vs> using T_lookup_void		= T_lookup < LN::line , LT::vo_id , Vs... >;
	template<auto... Vs> using T_lookup_swap		= T_lookup < LN::line , LT::swap  , Vs... >;
	template<auto... Vs> using T_lookup_apply		= T_lookup < LN::line , LT::apply , Vs... >;
	template<auto... Vs> using T_lookup_line		= T_lookup < LN::line , LT::id    , Vs... >;

	template<auto... Vs> nik_ce auto U_lookup_unit		= U_store_T < T_lookup_unit  < Vs... > >;
	template<auto... Vs> nik_ce auto U_lookup_void		= U_store_T < T_lookup_void  < Vs... > >;
	template<auto... Vs> nik_ce auto U_lookup_swap		= U_store_T < T_lookup_swap  < Vs... > >;
	template<auto... Vs> nik_ce auto U_lookup_apply		= U_store_T < T_lookup_apply < Vs... > >;
	template<auto... Vs> nik_ce auto U_lookup_line		= U_store_T < T_lookup_line  < Vs... > >;

/***********************************************************************************************************************/

// unit:

	template
	<
		auto static_parsed, auto this_f, auto env,
		auto m0, nik_vp(pack)(T_pack_Vs<m0>*)
	>
	struct T_lookup<LN::line, LT::unit, static_parsed, this_f, env, pack>
	{
		using T_link = T_lookup_tree_link<static_parsed, this_f, env>;

		template<auto n, typename... Ts>
		nik_ces auto result(Ts... vs)
			{ return T_resolve_link<T_link, n, m0, Ts...>::template result<n, m0, Ts...>(vs...); }
	};

/***********************************************************************************************************************/

// apply:

	template
	<
		auto static_parsed, auto this_f, auto env,
		auto m0, auto... ms, nik_vp(pack)(T_pack_Vs<m0, ms...>*)
	>
	struct T_lookup<LN::line, LT::apply, static_parsed, this_f, env, pack>
	{
		using T_link = T_lookup_tree_link<static_parsed, this_f, env>;

		template<auto n, typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto f = T_link::template result<n, m0>(U_pack_Ts<Ts...>);

				// direct member call required to preserve reference semantics.
			return T_store_U<f>::template result<>
				(T_resolve_link<T_link, n, ms, Ts...>::template result<n, ms, Ts...>(vs...)...);
		}
	};

/***********************************************************************************************************************/

// void:

	template
	<
		auto static_parsed, auto this_f, auto env,
		auto m0, auto... ms, nik_vp(pack)(T_pack_Vs<m0, ms...>*)
	>
	struct T_lookup<LN::line, LT::vo_id, static_parsed, this_f, env, pack>
	{
		nik_ces auto & parsed = member_value_U<static_parsed>;
		using T_link          = T_lookup_tree_link<static_parsed, this_f, env>;

		template<auto n, typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto f = T_link::template result<n, m0>(U_pack_Ts<Ts...>);

				// direct member call required to preserve reference semantics.
			return T_store_U<f>::template result<>
				(T_resolve_link<T_link, n, ms, Ts...>::template result<n, ms, Ts...>(vs...)...);
		}
	};

/***********************************************************************************************************************/

// swap:

	template
	<
		auto static_parsed, auto this_f, auto env,
		auto m0, auto m1, auto... ms, nik_vp(pack)(T_pack_Vs<m0, m1, ms...>*)
	>
	struct T_lookup<LN::line, LT::swap, static_parsed, this_f, env, pack>
	{
		nik_ces auto & parsed = member_value_U<static_parsed>;
		using T_link          = T_lookup_tree_link<static_parsed, this_f, env>;

		template<auto n, typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto f = T_link::template result<n, m1>(U_pack_Ts<Ts...>);

				// direct member call required to preserve reference semantics.
			return T_store_U<f>::template result<>
			(
				T_resolve_link<T_link, n, m0, Ts...>::template result<n, m0, Ts...>(vs...),
			 	T_resolve_link<T_link, n, ms, Ts...>::template result<n, ms, Ts...>(vs...)...
			);
		}
	};

/***********************************************************************************************************************/

// interface:

	template<auto static_targeted, auto this_f_link>
	struct T_lookup<LN::line, LT::id, static_targeted, this_f_link>
	{
		nik_ces auto static_parsed	= member_type_U<static_targeted>::static_parsed;
		nik_ces auto & parsed		= member_value_U<static_parsed>;

		nik_ces auto this_f		= unpack_<this_f_link, _car_>;
		nik_ces auto env		= unpack_<this_f_link, _cadr_>;

		template<auto n>
		nik_ces auto dispatch()
		{
			nik_ce auto & line = parsed.link_level[n];
			nik_ce auto pack   = eval<_par_segment_, line.size()>;

			if nik_ce (line.is_assign() || line.is_return())

				return U_lookup_unit<static_parsed, this_f, env, pack>;

			else if nik_ce (line.is_apply() || line.is_test())

				return U_lookup_apply<static_parsed, this_f, env, pack>;
			else
			{
				nik_ce auto sign = parsed.link_entry_sign(n, _zero);

				if nik_ce (Sign::is_mutable_arg(sign))

					return U_lookup_swap<static_parsed, this_f, env, pack>;
				else
					return U_lookup_void<static_parsed, this_f, env, pack>;
			}
		}

		template<auto n, typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			using T_lookup = T_store_U<dispatch<n>()>;

			return T_lookup::template result<n, Ts...>(vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace chord

