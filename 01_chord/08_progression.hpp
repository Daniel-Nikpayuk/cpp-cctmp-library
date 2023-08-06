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

// progression:

namespace chord {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

	template<auto V>
	nik_ce auto _constant_						= cctmp::_constant_<V>;

	template<auto Op, auto... Vs>
	nik_ce auto sift_						= cctmp::sift_<Op, Vs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// space:

/***********************************************************************************************************************/

// one cycle:

	using CycleName = typename T_chord_assembly_lexer::Token;

	template<token_type, typename...> struct T_one_cycle;

	template<auto Token, typename... Ts>
	nik_ce auto U_one_cycle = U_store_T<T_one_cycle<Token, Ts...>>;

/***********************************************************************************************************************/

// dependencies:

	// interval:

		template<auto static_parsed, auto index>
		struct T_ival_not_fixed
		{
			nik_ces auto & parsed = member_value_U<static_parsed>;

			template<auto pos>
			nik_ces bool result = not parsed.cycle_level[index].interval[pos].is_fixed;

		}; template<auto static_parsed, auto index>
			nik_ce auto _ival_not_fixed_ = U_custom_T<T_ival_not_fixed<static_parsed, index>>;

	// iterator:

		// not none:

			template<typename Iter>
			nik_ce bool iter_not_none(gcindex_type index, gcindex_type pos)
			{
				auto & cycle = Iter::parsed.cycle_level[index];
				auto & ival  = cycle.interval[pos];
				auto & iter  = cycle.iterator[pos];

				return !(ival.is_fixed || (iter[0].is_none && iter[1].is_none));
			}

		// not void:

			template<auto static_parsed>
			struct T_iter_not_void
			{
				nik_ces auto & parsed = member_value_U<static_parsed>;

				template<auto l, auto n, auto m>
				nik_ces bool result = not parsed.cycle_level[l].iterator[n][m].is_void;

			}; template<auto static_parsed>
				nik_ce auto _iter_not_void_ = U_custom_T<T_iter_not_void<static_parsed>>;

// sifters:

	template<auto static_parsed, auto index>
	nik_ce auto _ival_sift_ = U_pack_Vs<_ival_not_fixed_<static_parsed, index>, _constant_<true>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// cycle dispatch:

/***********************************************************************************************************************/

// precycle:

	template<auto index, auto types, typename Iter, typename Chord>
	struct T_precycle
	{
		template<auto pos, auto mode, typename Note>
		nik_ces void note_iter(Note & note)
		{
			nik_ce auto iter = Iter::template note_iter<index, pos, types, mode>();

			if nik_ce (mode) note = T_store_U<iter>::template result<Note>(note);
		}

		template<auto root, typename T>
		nik_ces void root_iter(T & v) { note_iter<root, Chord::pre_root_iter_mode(root)>(v); }

		template<auto tone, typename T>
		nik_ces void tone_iter(T & v)
		{
			if nik_ce (iter_not_none<Iter>(index, tone))
				note_iter<tone, Chord::pre_tone_iter_mode(tone), T>(v); // optimize for void intervals.
		}

		template<typename T>
		nik_ces void tonic_iter(T & v)
		{
			nik_ce auto mode = Chord::pre_tonic_iter_mode();
			nik_ce auto iter = Iter::template tonic_iter<index, types, mode>();

			if nik_ce (mode) v = T_store_U<iter>::template result<T>(v);
		}
	};

/***********************************************************************************************************************/

// cycle:

	template<auto index, auto types, auto pack, typename Param, typename Iter, typename Chord, typename Proc>
	struct T_cycle
	{
		template<auto root, typename In, typename End>
		nik_ces bool loop_pred(In in, End end)
		{
			nik_ce bool is_peek   = Chord::is_peek(root);
			nik_ce auto root_iter = Iter::template note_next<index, root, types>();
			nik_ce auto predicate = Param::template binary_peek
							<index, Proc::loop_pred, types, is_peek, root_iter>();

			return T_store_U<predicate>::template result<In, End>(in, end);
		}

		template<typename Out, typename T>
		nik_ces void mutate(Out out, T v)
		{
			nik_ce auto mutate_func = Param::template binary_func<index, Proc::mutate, types>();

			T_store_U<mutate_func>::template result<Out, T>(out, v);
		}

		template<typename Out, typename T>
		nik_ces auto combine(Out out, T v)
		{
			nik_ce auto combine_func = Param::template binary_func<index, Proc::combine, types>();

			return T_store_U<combine_func>::template result<Out, T>(out, v);
		}

		template<typename In, typename... Ins>
		nik_ces auto action(In in, Ins... ins)
		{
			nik_ce auto action_func = Param::template action_func<index, types>(pack);

			return T_store_U<action_func>::template result<In, Ins...>(in, ins...);
		}

		template<typename In, typename... Ins>
		nik_ces auto match(In in, Ins... ins)
		{
			nik_ce auto action_func = Param::template action_func<index, types>(pack);

			return T_store_U<action_func>::template result<In, Ins...>(in, ins...);
		}

		template<typename Out, typename In, typename... Ins>
		nik_ces void action_mutate(Out out, In in, Ins... ins)
		{
			auto val = action<In, Ins...>(in, ins...);

			mutate<Out, decltype(val)>(out, val);
		}

		template<typename Out, typename In, typename... Ins>
		nik_ces void action_combine_mutate(Out out, In in, Ins... ins)
		{
			auto val0 = action<In, Ins...>(in, ins...);
			auto val1 = combine<Out, decltype(val0)>(out, val0);

			mutate<Out, decltype(val1)>(out, val1);
		}

		template<auto pos, typename Note>
		nik_ces void note_iter(Note & note)
		{
			nik_ce auto iter = Iter::template note_next<index, pos, types>();

			note = T_store_U<iter>::template result<Note>(note);
		}

		template<auto root, typename Note>
		nik_ces void root_iter(Note & note)
		{
			note_iter<root, Note>(note); // optimize for void intervals.
		}

		template<auto tone, typename T>
		nik_ces void tone_iter(T & v)
		{
			if nik_ce (iter_not_none<Iter>(index, tone))
				note_iter<tone, T>(v); // optimize for void intervals.
		}
	};

/***********************************************************************************************************************/

// postcycle:

	template<auto index, auto types, typename Iter, typename Chord>
	struct T_postcycle
	{
		template<auto pos, auto mode, typename Note>
		nik_ces void note_iter(Note & note)
		{
			nik_ce auto iter = Iter::template note_iter<index, pos, types, mode>();

			if nik_ce (mode) note = T_store_U<iter>::template result<Note>(note);
		}

		template<auto root, typename T>
		nik_ces void root_iter(T & v) { note_iter<root, Chord::post_root_iter_mode()>(v); }

		template<auto tone, typename T>
		nik_ces void tone_iter(T & v)
		{
			if nik_ce (iter_not_none<Iter>(index, tone))
				note_iter<tone, Chord::post_tone_iter_mode(tone), T>(v); // optimize for void intervals.
		}

		template<typename T>
		nik_ces void tonic_iter(T & v)
		{
			nik_ce auto mode = Chord::post_tonic_iter_mode();
			nik_ce auto iter = Iter::template tonic_iter<index, types, mode>();

			if nik_ce (mode) v = T_store_U<iter>::template result<T>(v);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// repeat:

/***********************************************************************************************************************/

// one cycle:

	template<typename Pre, typename Cycle, typename Post, typename Chord, auto _out, auto... _ins>
	struct T_one_cycle<CycleName::repeat, Pre, Cycle, Post, Chord, T_pack_Vs<_out, _ins...>>
	{
		template<typename Out, typename End, typename... Ins>
		nik_ces auto result(Out out, End end, Ins... ins)
		{
			 Pre::template root_iter  < _out , Out >(out);
			 Pre::template tonic_iter <        End >(end);
			(Pre::template tone_iter  < _ins , Ins >(ins), ...);

			while (Cycle::template loop_pred<_out, Out, End>(out, end))
			{
				Cycle::template action_mutate<Out, Ins...>(out, ins...);

				 Cycle::template root_iter < _out , Out >(out);
				(Cycle::template tone_iter < _ins , Ins >(ins), ...);
			}

			if nik_ce (Chord::is_post_func(_out))
				Cycle::template action_mutate<Out, Ins...>(out, ins...);

			 Post::template tone_iter  < _out , Out >(out);
			 Post::template tonic_iter <        End >(end);
			(Post::template tone_iter  < _ins , Ins >(ins), ...);

			return out;
		}
	};

/***********************************************************************************************************************/

// cycle dispatch:

	template<auto static_parsed, auto this_f, auto env>
	struct T_cycle_dispatch<CycleName::repeat, static_parsed, this_f, env>
	{
		using Param = T_cycle_parameter < static_parsed , this_f , env >;
		using Iter  = T_cycle_iterator  < static_parsed , this_f , env >;

		struct Proc { enum : gkey_type { mutate, loop_pred, dimension }; };

		template<auto index, auto types, auto out, auto... ins>
		nik_ces auto result(nik_vp(U)(T_pack_Vs<out, ins...>*))
		{
			nik_ce auto ival_pack = sift_<_ival_sift_<static_parsed, index>, out, ins...>;
			nik_ce auto base_pack = U_restore_T<decltype(U)>;

			using Ival  = T_cycle_interval<static_parsed, index>;
			using Chord = dispatch_chord<Ival, ival_pack>;
			using Pack  = T_store_U<base_pack>;

			using Pre   = T_precycle  < index , types, Iter, Chord >;
			using Post  = T_postcycle < index , types, Iter, Chord >;

			using Cycle = T_cycle<index, types, base_pack, Param, Iter, Chord, Proc>;

			return U_one_cycle<CycleName::repeat, Pre, Cycle, Post, Chord, Pack>;
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// map:

/***********************************************************************************************************************/

// one cycle:

	template<typename Pre, typename Cycle, typename Post, typename Chord, auto _out, auto _in, auto... _ins>
	struct T_one_cycle<CycleName::map, Pre, Cycle, Post, Chord, T_pack_Vs<_out, _in, _ins...>>
	{
		template<typename Out, typename In, typename End, typename... Ins>
		nik_ces auto result(Out out, In in, End end, Ins... ins)
		{
			 Pre::template tone_iter  < _out , Out >(out);
			 Pre::template root_iter  < _in  , In  >(in );
			 Pre::template tonic_iter <        End >(end);
			(Pre::template tone_iter  < _ins , Ins >(ins), ...);

			while (Cycle::template loop_pred<_in, In, End>(in, end))
			{
				Cycle::template action_mutate<Out, In, Ins...>(out, in, ins...);

				 Cycle::template tone_iter < _out , Out >(out);
				 Cycle::template root_iter < _in  , In  >(in );
				(Cycle::template tone_iter < _ins , Ins >(ins), ...);
			}

			if nik_ce (Chord::is_post_func(_in))
				Cycle::template action_mutate<Out, In, Ins...>(out, in, ins...);

			 Post::template tone_iter  < _out , Out >(out);
			 Post::template root_iter  < _in  , In  >(in );
			 Post::template tonic_iter <        End >(end);
			(Post::template tone_iter  < _ins , Ins >(ins), ...);

			return out;
		}
	};

/***********************************************************************************************************************/

// cycle dispatch:

	template<auto static_parsed, auto this_f, auto env>
	struct T_cycle_dispatch<CycleName::map, static_parsed, this_f, env>
	{
		using Param = T_cycle_parameter < static_parsed , this_f , env >;
		using Iter  = T_cycle_iterator  < static_parsed , this_f , env >;

		struct Proc { enum : gkey_type { mutate, loop_pred, dimension }; };

		template<auto index, auto types, auto out, auto in, auto... ins>
		nik_ces auto result(nik_vp(U)(T_pack_Vs<out, in, ins...>*))
		{
			nik_ce auto ival_pack = sift_<_ival_sift_<static_parsed, index>, in, out, ins...>;
			nik_ce auto base_pack = U_restore_T<decltype(U)>;

			using Ival  = T_cycle_interval<static_parsed, index>;
			using Chord = dispatch_chord<Ival, ival_pack>;
			using Pack  = T_store_U<base_pack>;

			using Pre   = T_precycle  < index , types, Iter , Chord >;
			using Post  = T_postcycle < index , types, Iter , Chord >;

			using Cycle = T_cycle<index, types, base_pack, Param, Iter, Chord, Proc>;

			return U_one_cycle<CycleName::map, Pre, Cycle, Post, Chord, Pack>;
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// fold:

/***********************************************************************************************************************/

// one cycle:

	template<typename Pre, typename Cycle, typename Post, typename Chord, auto _out, auto _in, auto... _ins>
	struct T_one_cycle<CycleName::fold, Pre, Cycle, Post, Chord, T_pack_Vs<_out, _in, _ins...>>
	{
		template<typename Out, typename In, typename End, typename... Ins>
		nik_ces auto result(Out out, In in, End end, Ins... ins)
		{
			 Pre::template root_iter  < _in  , In  >(in );
			 Pre::template tonic_iter <        End >(end);
			(Pre::template tone_iter  < _ins , Ins >(ins), ...);

			while (Cycle::template loop_pred<_in, In, End>(in, end))
			{
				Cycle::template action_combine_mutate<Out, In, Ins...>(out, in, ins...);

				 Cycle::template root_iter < _in  , In  >(in );
				(Cycle::template tone_iter < _ins , Ins >(ins), ...);
			}

			if nik_ce (Chord::is_post_func(_in))
				Cycle::template action_combine_mutate<Out, In, Ins...>(out, in, ins...);

			 Post::template root_iter  < _in  , In  >(in );
			 Post::template tonic_iter <        End >(end);
			(Post::template tone_iter  < _ins , Ins >(ins), ...);

			return out;
		}
	};

/***********************************************************************************************************************/

// cycle dispatch:

	template<auto static_parsed, auto this_f, auto env>
	struct T_cycle_dispatch<CycleName::fold, static_parsed, this_f, env>
	{
		using Param = T_cycle_parameter < static_parsed , this_f , env >;
		using Iter  = T_cycle_iterator  < static_parsed , this_f , env >;

		struct Proc { enum : gkey_type { combine, mutate, loop_pred, dimension }; };

		template<auto index, auto types, auto out, auto in, auto... ins>
		nik_ces auto result(nik_vp(U)(T_pack_Vs<out, in, ins...>*))
		{
			nik_ce auto ival_pack = sift_<_ival_sift_<static_parsed, index>, in, out, ins...>;
			nik_ce auto base_pack = U_restore_T<decltype(U)>;

			using Ival  = T_cycle_interval<static_parsed, index>;
			using Chord = dispatch_chord<Ival, ival_pack>;
			using Pack  = T_store_U<base_pack>;

			using Pre   = T_precycle  < index , types, Iter , Chord >;
			using Post  = T_postcycle < index , types, Iter , Chord >;

			using Cycle = T_cycle<index, types, base_pack, Param, Iter, Chord, Proc>;

			return U_one_cycle<CycleName::fold, Pre, Cycle, Post, Chord, Pack>;
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// find:

	// If the in iterator is privileged for all interval types,
	// then the out iterator is restricted to being an opening interval,
	// so as to indicate whether or not a match was found.

/***********************************************************************************************************************/

// one cycle:

	template<typename Pre, typename Cycle, typename Post, typename Chord, auto _out, auto _in, auto... _ins>
	struct T_one_cycle<CycleName::find, Pre, Cycle, Post, Chord, T_pack_Vs<_out, _in, _ins...>>
	{
		template<typename Out, typename In, typename End, typename... Ins>
		nik_ces auto result(Out out, In in, End end, Ins... ins)
		{
			bool match{false};

			 Pre::template root_iter  < _in  , In  >(in );
			 Pre::template tonic_iter <        End >(end);
			(Pre::template tone_iter  < _ins , Ins >(ins), ...);

			while (Cycle::template loop_pred<_in, In, End>(in, end))
			{
				if (Cycle::template match<In, Ins...>(in, ins...))
				{
					Cycle::template mutate<Out, In>(out, in);
				 	Cycle::template tone_iter<_out, Out>(out);
					match = true;
					break;
				}

				 Cycle::template root_iter < _in  , In  >(in );
				(Cycle::template tone_iter < _ins , Ins >(ins), ...);
			}

			if nik_ce (Chord::is_post_func(_in))
				if (!match && Cycle::template match<In, Ins...>(in, ins...))
				{
					Cycle::template mutate<Out, In>(out, in);
				 	Cycle::template tone_iter<_out, Out>(out);
				}

			 Post::template root_iter  < _in  , In  >(in );
			 Post::template tonic_iter <        End >(end);
			(Post::template tone_iter  < _ins , Ins >(ins), ...);

			return out;
		}
	};

/***********************************************************************************************************************/

// cycle dispatch:

	template<auto static_parsed, auto this_f, auto env>
	struct T_cycle_dispatch<CycleName::find, static_parsed, this_f, env>
	{
		using Param = T_cycle_parameter < static_parsed , this_f , env >;
		using Iter  = T_cycle_iterator  < static_parsed , this_f , env >;

		struct Proc { enum : gkey_type { mutate, loop_pred, dimension }; };

		template<auto index, auto types, auto out, auto in, auto... ins>
		nik_ces auto result(nik_vp(U)(T_pack_Vs<out, in, ins...>*))
		{
			nik_ce auto ival_pack = sift_<_ival_sift_<static_parsed, index>, in, out, ins...>;
			nik_ce auto base_pack = U_restore_T<decltype(U)>;

			using Ival  = T_cycle_interval<static_parsed, index>;
			using Chord = dispatch_chord<Ival, ival_pack>;
			using Pack  = T_store_U<base_pack>;

			using Pre   = T_precycle  < index , types , Iter , Chord >;
			using Post  = T_postcycle < index , types , Iter , Chord >;

			using Cycle = T_cycle<index, types, base_pack, Param, Iter, Chord, Proc>;

			return U_one_cycle<CycleName::find, Pre, Cycle, Post, Chord, Pack>;
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// sift:

	// If the in iterator is privileged for all interval types,
	// then the out iterator is restricted to being an opening interval,
	// so as to indicate whether or not a match was found.

/***********************************************************************************************************************/

// one cycle:

	template<typename Pre, typename Cycle, typename Post, typename Chord, auto _out, auto _in, auto... _ins>
	struct T_one_cycle<CycleName::sift, Pre, Cycle, Post, Chord, T_pack_Vs<_out, _in, _ins...>>
	{
		template<typename Out, typename In, typename End, typename... Ins>
		nik_ces auto result(Out out, In in, End end, Ins... ins)
		{
			 Pre::template root_iter  < _in  , In  >(in );
			 Pre::template tonic_iter <        End >(end);
			(Pre::template tone_iter  < _ins , Ins >(ins), ...);

			while (Cycle::template loop_pred<_in, In, End>(in, end))
			{
				if (Cycle::template match<In, Ins...>(in, ins...))
				{
					Cycle::template mutate<Out, In>(out, in);
				 	Cycle::template tone_iter<_out, Out>(out);
				}

				 Cycle::template root_iter < _in  , In  >(in );
				(Cycle::template tone_iter < _ins , Ins >(ins), ...);
			}

			if nik_ce (Chord::is_post_func(_in))
				if (Cycle::template match<In, Ins...>(in, ins...))
				{
					Cycle::template mutate<Out, In>(out, in);
				 	Cycle::template tone_iter<_out, Out>(out);
				}

			 Post::template root_iter  < _in  , In  >(in );
			 Post::template tonic_iter <        End >(end);
			(Post::template tone_iter  < _ins , Ins >(ins), ...);

			return out;
		}
	};

/***********************************************************************************************************************/

// cycle dispatch:

	template<auto static_parsed, auto this_f, auto env>
	struct T_cycle_dispatch<CycleName::sift, static_parsed, this_f, env>
	{
		using Param = T_cycle_parameter < static_parsed , this_f , env >;
		using Iter  = T_cycle_iterator  < static_parsed , this_f , env >;

		struct Proc { enum : gkey_type { mutate, loop_pred, dimension }; };

		template<auto index, auto types, auto out, auto in, auto... ins>
		nik_ces auto result(nik_vp(U)(T_pack_Vs<out, in, ins...>*))
		{
			nik_ce auto ival_pack = sift_<_ival_sift_<static_parsed, index>, in, out, ins...>;
			nik_ce auto base_pack = U_restore_T<decltype(U)>;

			using Ival  = T_cycle_interval<static_parsed, index>;
			using Chord = dispatch_chord<Ival, ival_pack>;
			using Pack  = T_store_U<base_pack>;

			using Pre   = T_precycle  < index , types , Iter , Chord >;
			using Post  = T_postcycle < index , types , Iter , Chord >;

			using Cycle = T_cycle<index, types, base_pack, Param, Iter, Chord, Proc>;

			return U_one_cycle<CycleName::sift, Pre, Cycle, Post, Chord, Pack>;
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace chord

