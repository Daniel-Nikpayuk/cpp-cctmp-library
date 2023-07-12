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

// metapiler:

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

namespace chord {

	nik_ce auto H_id					= cctmp::H_id;

	template<auto f>
	nik_ce auto _wrap_					= cctmp::_wrap_<f>;

	nik_ce auto _push_					= cctmp::_push_;

	nik_ce auto _read_write_				= cctmp::_read_write_;

	template<auto H = H_id>
	nik_ce auto _list_					= cctmp::_list_<H>;

	template<typename T>
	nik_ce auto U_custom_T					= cctmp::U_custom_T<T>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// source:

	template<typename CharType, auto N>
	nik_ce auto source(const CharType (&s)[N]) { return cctmp::string_literal(s); }

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// metapiler:

/***********************************************************************************************************************/

// interface:

	template<auto callable_source, auto Env = U_null_Vs>
	struct T_chord_assembly_metapiler
	{
		nik_ces auto static_src		= _static_callable_<callable_source>;
		nik_ces auto static_scanned	= U_store_T<T_chord_assembly_scanned<static_src>>;
		nik_ces auto static_targeted	= U_store_T<T_chord_assembly_targeted<static_scanned>>;

		nik_ces auto static_parsed	= member_type_U<static_targeted>::static_parsed;
		nik_ces auto & targeted		= member_value_U<static_targeted>;
		nik_ces auto & toc		= targeted.toc;
		nik_ces auto & lookup		= toc.lookup_level;

		nik_ces auto env		= eval<_push_, H_id, Env, default_machine_frame>;

		using T_lookup			= T_env_lookup<env>;

		// toc:

			struct T_entry_poses
			{
				template<auto n>
				nik_ces auto result = eval<_par_segment_, lookup[n].size()>;

			}; nik_ces auto _entry_poses_ = U_custom_T<T_entry_poses>;

		// lookup:

			template<auto n, auto m, auto... static_frames>
			nik_ces auto resolve(nik_avp(T_pack_Vs<static_frames...>*))
			{
				nik_ce auto record	 = T_lookup::find_frame(toc.lookup_entry(n, m));
				nik_ce auto position     = record.v0;
				nik_ce auto subposition  = record.v1;
				nik_ce auto static_frame = eval<_par_at_, position, static_frames...>;

				return U_cast_lookup<subposition, static_frame>;
			}

			template<auto n, auto m>
			nik_ces auto resolve_chord()
			{
				nik_ce auto sign  = toc.lookup_entry_sign(n, m);
				nik_ce auto index = toc.lookup_entry_index(n, m);

				return U_one_cycle<sign, index, static_parsed, env>;
			}

			template<auto this_f>
			nik_ces auto resolve_recurse()
				{ return U_cast_lookup<_zero, recurse_machine_frame<this_f>>; }
	
			template<auto this_f, auto n, auto m>
			nik_ces auto resolve_value()
			{
				nik_ce auto sign = toc.lookup_entry_sign(n, m);

				if nik_ce      (Sign::is_env(sign))     return resolve<n, m>(env);
				else if nik_ce (Sign::is_chord(sign))   return resolve_chord<n, m>();
				else if nik_ce (Sign::is_recurse(sign)) return resolve_recurse<this_f>();
				else                                    return toc.lookup_entry_index(n, m);
			}

			template<auto n, auto m>
			nik_ces auto resolve_type()
			{
				nik_ce auto sign = toc.lookup_entry_sign(n, m);

				if nik_ce (Sign::is_marg(sign)) return _read_write_;
				else                            return _id_;
			}

			template<auto this_f, auto n, auto m0>
			nik_ces auto resolve_line_single(nik_avp(T_pack_Vs<m0>*))
			{
				nik_ce auto f_pack = U_pack_Vs<resolve_value<this_f, n, m0>()>;
				nik_ce auto t_pack = U_pack_Vs<resolve_type<n, m0>()>;

				return eval<_list_<>, f_pack, t_pack>;
			}

			template<auto this_f, auto n, auto m0, auto m1, auto... ms>
			nik_ces auto resolve_void_swap(nik_avp(T_pack_Vs<m0, m1, ms...>*))
			{
				nik_ce auto first  = resolve_value<this_f, n, m1>();
				nik_ce auto second = resolve_value<this_f, n, m0>();
				nik_ce auto f_pack = U_pack_Vs<first, second, resolve_value<this_f, n, ms>()...>;
				nik_ce auto t_pack = U_pack_Vs<_read_write_, resolve_type<n, ms>()...>;

				return eval<_list_<>, f_pack, t_pack>;
			}

			template<auto this_f, auto n, auto m0, auto... ms>
			nik_ces auto resolve_void(nik_avp(T_pack_Vs<m0, ms...>*))
			{
				nik_ce auto first  = resolve_value<this_f, n, m0>();
				nik_ce auto f_pack = U_pack_Vs<first, resolve_value<this_f, n, ms>()...>;
				nik_ce auto t_pack = U_pack_Vs<resolve_type<n, ms>()...>;

				return eval<_list_<>, f_pack, t_pack>;
			}

			template<auto this_f, auto n, typename Pack>
			nik_ces auto resolve_line_void(Pack p)
			{
				nik_ce auto sign = toc.lookup_entry_sign(n, _zero);

				if nik_ce (Sign::is_marg(sign)) return resolve_void_swap<this_f, n>(p);
				else                            return resolve_void<this_f, n>(p);
			}

			template<auto this_f, auto n, auto m0, auto... ms>
			nik_ces auto resolve_line_apply(nik_avp(T_pack_Vs<m0, ms...>*))
			{
				nik_ce auto first  = resolve_value<this_f, n, m0>();
				nik_ce auto f_pack = U_pack_Vs<first, resolve_value<this_f, n, ms>()...>;
				nik_ce auto t_pack = U_pack_Vs<resolve_type<n, ms>()...>;

				return eval<_list_<>, f_pack, t_pack>;
			}

			template<auto this_f, auto n, typename Pack>
			nik_ces auto unpack_entry(Pack p)
			{
				if nik_ce      (lookup[n].is_assign()) return resolve_line_single <this_f, n>(p);
				else if nik_ce (lookup[n].is_return()) return resolve_line_single <this_f, n>(p);
				else if nik_ce (lookup[n].is_void  ()) return resolve_line_void   <this_f, n>(p);
				else                                   return resolve_line_apply  <this_f, n>(p);
			}

			template<auto this_f, auto... l_ps, auto... e_ps>
			nik_ces auto to_pack(nik_avp(T_pack_Vs<l_ps...>*), nik_avp(T_pack_Vs<e_ps...>*))
				{ return eval<_list_<>, unpack_entry<this_f, l_ps>(e_ps)...>; }

			template<auto this_f>
			nik_ces auto to_lookup_pack()
			{
				nik_ce auto line_poses  = eval<_par_segment_, lookup.size()>;
				nik_ce auto entry_poses = unpack_<line_poses, cctmp::_map_, H_id, _entry_poses_>;

				return to_pack<this_f>(line_poses, entry_poses);
			}

			template<auto this_f>
			nik_ces auto resolve_lookup = to_lookup_pack<this_f>();

		// function:

			template<typename S, typename... Ts>
			nik_ces S result(Ts... vs)
			{
				nik_ce auto out_type = U_store_T<S>;
				nik_ce auto contr    = static_targeted;
				nik_ce auto this_f   = _wrap_<result<S, Ts...>>;
				nik_ce auto lookup   = resolve_lookup<this_f>;

				return T_machine_start::template result
				<
					out_type, contr, lookup, modify_type<_read_only_, Ts>...

				>((modify_type<_read_only_, Ts>) vs...);
			}
	};

	// syntactic sugar:

		template<auto callable_source, auto Env, typename S, typename... Ts>
		nik_ce auto metapiler_apply(Ts... vs)
		{
			using T_function = T_chord_assembly_metapiler<callable_source, Env>;

			return T_function::template result<S, Ts...>(vs...);
		}

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace chord

