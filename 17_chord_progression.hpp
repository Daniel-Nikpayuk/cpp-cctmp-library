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

	nik_ce auto _id_					= cctmp::_id_;

	nik_ce auto _same_					= cctmp::_same_;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// chord:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// parameter:

/***********************************************************************************************************************/

// interface:

	template<gindex_type index, auto static_parsed, auto env>
	struct T_chord_parameter
	{
		nik_ces auto & parsed		= member_value_U<static_parsed>;
		nik_ces auto & chord		= parsed.chord_level[index];
		nik_ces auto & parameter	= chord.parameter;

		using T_lookup			= T_env_lookup<env>;

		template<auto n, auto m, auto... static_frames>
		nik_ces auto resolve(nik_avp(T_pack_Vs<static_frames...>*))
		{
			nik_ce auto record	 = T_lookup::find_frame(parameter[n][m]);
			nik_ce auto position     = record.v0;
			nik_ce auto subposition  = record.v1;
			nik_ce auto static_frame = eval<_par_at_, position, static_frames...>;

			nik_ce auto & frame      = member_value_U<static_frame>;
			nik_ce auto   value      = frame.template map<subposition>();

			return value;
		}

		//

		template<auto n>
		nik_ces auto unary_func()
		{
			nik_ce auto op        = resolve<n, 0>(env);
			nik_ce auto arg       = resolve<n, 1>(env);
			nik_ce bool arg_is_id = eval<_same_, arg, _id_>;

			if nik_ce (arg_is_id) return op;
			else return arg_subpose<op, arg>;
		}

		template<auto n>
		nik_ces auto binary_func()
		{
			nik_ce auto op         = resolve<n, 0>(env);
			nik_ce auto arg0       = resolve<n, 1>(env);
			nik_ce auto arg1       = resolve<n, 2>(env);
			nik_ce bool arg0_is_id = eval<_same_, arg0, _id_>;
			nik_ce bool arg1_is_id = eval<_same_, arg1, _id_>;

			if nik_ce (arg0_is_id && arg1_is_id) return op;
			else return arg_subpose<op, arg0, arg1>;
		}

		template<auto n, bool is_peek, auto iter>
		nik_ces auto binary_peek()
		{
			nik_ce auto op = binary_func<n>();

			if nik_ce (!is_peek) return op;
			else return arg_subpose<op, iter, _id_>;
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// iterator:

	struct ChordIterator
	{
		enum : gkey_type { none, next, prev, dimension };

		nik_ces bool is_iter(gckey_type k) { return (k != none); }

		template<typename Interval>
		nik_ces auto pre_next_mode(gckey_type note) { return Interval::is_left_open(note) ? next : none; }

		template<typename Interval>
		nik_ces auto post_next_mode(gckey_type note) { return Interval::is_right_open(note) ? next : none; }

		template<typename Interval>
		nik_ces auto post_prev_mode(gckey_type note) { return Interval::is_right_closed(note) ? prev : none; }
	};

	using DI = ChordIterator;

/***********************************************************************************************************************/

// interface:

	template<gindex_type index, auto static_parsed, auto env>
	struct T_chord_iterator
	{
		nik_ces auto & parsed		= member_value_U<static_parsed>;
		nik_ces auto & chord		= parsed.chord_level[index];
		nik_ces auto & iterator		= chord.iterator;

		using T_lookup			= T_env_lookup<env>;

		template<auto n, auto m, auto... static_frames>
		nik_ces auto resolve(nik_avp(T_pack_Vs<static_frames...>*))
		{
			nik_ce auto record	 = T_lookup::find_frame(iterator[n][m]);
			nik_ce auto position     = record.v0;
			nik_ce auto subposition  = record.v1;
			nik_ce auto static_frame = eval<_par_at_, position, static_frames...>;

			nik_ce auto & frame      = member_value_U<static_frame>;
			nik_ce auto   value      = frame.template map<subposition>();

			return value;
		}

		template<auto note> nik_ces auto note_next() { return resolve<note, 0>(env); }
		template<auto note> nik_ces auto note_prev() { return resolve<note, 1>(env); }

		template<auto mode, auto note>
		nik_ces auto note_iter()
		{
			if      nik_ce (mode == DI::next) return note_next<note>();
			else if nik_ce (mode == DI::prev) return note_prev<note>();
			else                              return _id_;
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// interval:

/***********************************************************************************************************************/

// interface:

	template<gindex_type index, auto static_parsed>
	struct T_chord_interval
	{
		nik_ces auto & parsed   = member_value_U<static_parsed>;
		nik_ces auto & chord    = parsed.chord_level[index];
		nik_ces auto & interval = chord.interval;

		nik_ces bool is_left_open    (gckey_type note) { return interval[note].is_left_open(); }
		nik_ces bool is_right_closed (gckey_type note) { return interval[note].is_right_closed(); }
		nik_ces bool is_right_open   (gckey_type note) { return interval[note].is_right_open(); }

		template<typename... Ts>
		nik_ces bool all_right_closed(Ts... tones) { return (is_right_closed(tones) && ...); }

		template<typename... Ts>
		nik_ces bool all_right_open(Ts... tones) { return (is_right_open(tones) && ...); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// quality:

	struct ChordQuality
	{
		enum : gkey_type
		{
			interval, major, diminished, minor,
			tonic_augmented, tone_augmented, peek_augmented,
			dimension
		};

		private:

			template<typename Interval>
			nik_ces auto reversible(gckey_type note) { return Interval::chord.is_reversible(note); }

			template<typename Interval>
			nik_ces void update(bool & match, gckey_type tone)
				{ if (match && Interval::is_right_closed(tone)) match = reversible<Interval>(tone); }

			template<typename Interval, typename... Ts>
			nik_ces auto right_closed_reversible(Ts... tones)
			{
				bool match = true;

				(update<Interval>(match, tones), ...);

				return match;
			}

			template<typename Interval, typename... Ts>
			nik_ces auto open(gckey_type tonic, Ts... tones)
			{
				if      (Interval::all_right_open(tones...)         ) return major;
				else if (reversible<Interval>(tonic)                ) return tonic_augmented;
				else if (right_closed_reversible<Interval>(tones...)) return tone_augmented;
				else                                                  return peek_augmented;
			}

			template<typename Interval, typename... Ts>
			nik_ces auto closed(gckey_type tonic, Ts... tones)
			{
				if (Interval::all_right_closed(tones...)) return diminished;
				else                                      return minor;
			}

		public:

			template<typename Interval, typename... Ts>
			nik_ces auto name(gckey_type root, gckey_type tonic, Ts... tones)
			{
				if (Interval::is_right_open(root)) return open<Interval>(tonic, tones...);
				else                               return closed<Interval>(tonic, tones...);
			}
	};

	using DQ = ChordQuality;

	template<gkey_type, typename> struct T_chord_quality;

	template<typename Interval, auto root, auto tonic, auto... tones>
	using dispatch_chord = T_chord_quality<DQ::name<Interval>(root, tonic, tones...), Interval>;

/***********************************************************************************************************************/

// interval:

	template<gindex_type index, auto static_parsed>
	struct T_chord_quality<DQ::interval, T_chord_interval<index, static_parsed>>
	{
		using Interval = T_chord_interval<index, static_parsed>;

		nik_ces bool is_pre_next  (gckey_type note) { return Interval::is_left_open(note); }
		nik_ces bool is_post_func (gckey_type note) { return Interval::is_right_closed(note); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// major:

	// { root, tonic ) ; { tone ) // tone aligns centre

/***********************************************************************************************************************/

// interface:

	template<gindex_type index, auto static_parsed>
	struct T_chord_quality<DQ::major, T_chord_interval<index, static_parsed>>
	{
		using Interval = T_chord_interval<index, static_parsed>;

		nik_ces auto pre_root_iter_mode   (gckey_type note) { return DI::pre_next_mode<Interval>(note); }
		nik_ces auto pre_tone_iter_mode   (gckey_type note) { return DI::pre_next_mode<Interval>(note); }
		nik_ces auto pre_tonic_iter_mode  (gckey_type note) { return DI::none; }

		nik_ces auto post_root_iter_mode  (gckey_type note) { return DI::none; }
		nik_ces auto post_tone_iter_mode  (gckey_type note) { return DI::none; }
		nik_ces auto post_tonic_iter_mode (gckey_type note) { return DI::none; }

		nik_ces bool is_peek      (gckey_type note) { return false; }
		nik_ces bool is_post_func (gckey_type note) { return false; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// augmented:

	//  { root, tonic ) ; { tone ] // tone aligns left

/***********************************************************************************************************************/

// tonic:

	// tonic is reversible: we move tonic back one; march (move) root and tones; update root and tones;
	// update tonic. root acts on its last position as if it were right closed before being updated.

	template<gindex_type index, auto static_parsed>
	struct T_chord_quality<DQ::tonic_augmented, T_chord_interval<index, static_parsed>>
	{
		using Interval = T_chord_interval<index, static_parsed>;

		nik_ces auto pre_root_iter_mode   (gckey_type note) { return DI::pre_next_mode<Interval>(note); }
		nik_ces auto pre_tone_iter_mode   (gckey_type note) { return DI::pre_next_mode<Interval>(note); }
		nik_ces auto pre_tonic_iter_mode  (gckey_type note) { return DI::prev; }

		nik_ces auto post_root_iter_mode  (gckey_type note) { return DI::next; }
		nik_ces auto post_tone_iter_mode  (gckey_type note) { return DI::post_next_mode<Interval>(note); }
		nik_ces auto post_tonic_iter_mode (gckey_type note) { return DI::next; }

		nik_ces bool is_peek      (gckey_type note) { return false; }
		nik_ces bool is_post_func (gckey_type note) { return true; }
	};

/***********************************************************************************************************************/

// tone:

	// tonic is not reversible, but tones that stop short are all reversible: march root and tones;
	// backdate said tones.

	template<gindex_type index, auto static_parsed>
	struct T_chord_quality<DQ::tone_augmented, T_chord_interval<index, static_parsed>>
	{
		using Interval = T_chord_interval<index, static_parsed>;

		nik_ces auto pre_root_iter_mode   (gckey_type note) { return DI::pre_next_mode<Interval>(note); }
		nik_ces auto pre_tone_iter_mode   (gckey_type note) { return DI::pre_next_mode<Interval>(note); }
		nik_ces auto pre_tonic_iter_mode  (gckey_type note) { return DI::none; }

		nik_ces auto post_root_iter_mode  (gckey_type note) { return DI::none; }
		nik_ces auto post_tone_iter_mode  (gckey_type note) { return DI::post_prev_mode<Interval>(note); }
		nik_ces auto post_tonic_iter_mode (gckey_type note) { return DI::none; }

		nik_ces bool is_peek      (gckey_type note) { return false; }
		nik_ces bool is_post_func (gckey_type note) { return false; }
	};

/***********************************************************************************************************************/

// peek:

	// tonic is not reversible, at least one tone is not reversible: we peek march root and tones;
	// update root and tones. root acts on its last position as if it were right closed before being updated.

	template<gindex_type index, auto static_parsed>
	struct T_chord_quality<DQ::peek_augmented, T_chord_interval<index, static_parsed>>
	{
		using Interval = T_chord_interval<index, static_parsed>;

		nik_ces auto pre_root_iter_mode   (gckey_type note) { return DI::pre_next_mode<Interval>(note); }
		nik_ces auto pre_tone_iter_mode   (gckey_type note) { return DI::pre_next_mode<Interval>(note); }
		nik_ces auto pre_tonic_iter_mode  (gckey_type note) { return DI::none; }

		nik_ces auto post_root_iter_mode  (gckey_type note) { return DI::next; }
		nik_ces auto post_tone_iter_mode  (gckey_type note) { return DI::post_next_mode<Interval>(note); }
		nik_ces auto post_tonic_iter_mode (gckey_type note) { return DI::none; }

		nik_ces bool is_peek      (gckey_type note) { return true; }
		nik_ces bool is_post_func (gckey_type note) { return true; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// diminished:

	// { root, tonic ] ; { tone ] // tone aligns centre

/***********************************************************************************************************************/

// interface:

	template<gindex_type index, auto static_parsed>
	struct T_chord_quality<DQ::diminished, T_chord_interval<index, static_parsed>>
	{
		using Interval = T_chord_interval<index, static_parsed>;

		nik_ces auto pre_root_iter_mode   (gckey_type note) { return DI::pre_next_mode<Interval>(note); }
		nik_ces auto pre_tone_iter_mode   (gckey_type note) { return DI::pre_next_mode<Interval>(note); }
		nik_ces auto pre_tonic_iter_mode  (gckey_type note) { return DI::none; }

		nik_ces auto post_root_iter_mode  (gckey_type note) { return DI::none; }
		nik_ces auto post_tone_iter_mode  (gckey_type note) { return DI::none; }
		nik_ces auto post_tonic_iter_mode (gckey_type note) { return DI::none; }

		nik_ces bool is_peek      (gckey_type note) { return false; }
		nik_ces bool is_post_func (gckey_type note) { return true; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// minor:

	// { root, tonic ] ; { tone ) // tone aligns right

/***********************************************************************************************************************/

// interface:

	template<gindex_type index, auto static_parsed>
	struct T_chord_quality<DQ::minor, T_chord_interval<index, static_parsed>>
	{
		using Interval = T_chord_interval<index, static_parsed>;

		nik_ces auto pre_root_iter_mode   (gckey_type note) { return DI::pre_next_mode<Interval>(note); }
		nik_ces auto pre_tone_iter_mode   (gckey_type note) { return DI::pre_next_mode<Interval>(note); }
		nik_ces auto pre_tonic_iter_mode  (gckey_type note) { return DI::none; }

		nik_ces auto post_root_iter_mode  (gckey_type note) { return DI::none; }
		nik_ces auto post_tone_iter_mode  (gckey_type note) { return DI::post_next_mode<Interval>(note); }
		nik_ces auto post_tonic_iter_mode (gckey_type note) { return DI::none; }

		nik_ces bool is_peek      (gckey_type note) { return false; }
		nik_ces bool is_post_func (gckey_type note) { return true; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// one cycle:

	template<sign_type, gindex_type, auto, auto> struct T_one_cycle;

	template<sign_type Sign, gindex_type Pos, auto static_parsed, auto env>
	nik_ce auto U_one_cycle = U_store_T<T_one_cycle<Sign, Pos, static_parsed, env>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// unidirected:

/***********************************************************************************************************************/

// repeat:

	template<gindex_type index, auto static_parsed, auto env>
	struct T_one_cycle<Sign::repeat, index, static_parsed, env>
	{
		using Parameter = T_chord_parameter <index, static_parsed, env>;
		using Iterator  = T_chord_iterator  <index, static_parsed, env>;
		using Interval  = T_chord_interval  <index, static_parsed     >;
		using Chord     = T_chord_quality   <DQ::interval, Interval   >;

		struct Proc { enum : gkey_type { action, mutate, loop_pred, dimension }; };
		struct Note { enum : gkey_type { out, dimension }; }; // in is fixed.

		nik_ces bool is_pre_out_next		= Chord::is_pre_next(Note::out);
		nik_ces bool is_post_func		= Chord::is_post_func(Note::out);

		nik_ces auto loop_pred			= Parameter::template binary_func < Proc::loop_pred >();
		nik_ces auto action_func		= Parameter::template unary_func  < Proc::action    >();
		nik_ces auto mutate_func		= Parameter::template binary_func < Proc::mutate    >();

		nik_ces auto out_next			= Iterator::template note_next<Note::out>();

		template<typename Out, typename End, typename In>
		nik_ces auto result(Out out, End end, In in)
		{
			if nik_ce (is_pre_out_next) out = cctmp::apply<out_next>(out);

			while (cctmp::apply<loop_pred>(out, end))
			{
				cctmp::apply<mutate_func>(out, cctmp::apply<action_func>(in));

				out = cctmp::apply<out_next>(out);
			}

			if nik_ce (is_post_func) cctmp::apply<mutate_func>(out, cctmp::apply<action_func>(in));

			return out;
		}
	};

/***********************************************************************************************************************/

// fold:

	template<gindex_type index, auto static_parsed, auto env>
	struct T_one_cycle<Sign::fold, index, static_parsed, env>
	{
		using Parameter = T_chord_parameter <index, static_parsed, env>;
		using Iterator  = T_chord_iterator  <index, static_parsed, env>;
		using Interval  = T_chord_interval  <index, static_parsed     >;
		using Chord     = T_chord_quality   <DQ::interval, Interval   >;

		struct Proc { enum : gkey_type { combine, mutate, loop_pred, dimension }; };
		struct Note { enum : gkey_type { in, dimension }; }; // out is fixed.

		nik_ces bool is_pre_in_next		= Chord::is_pre_next(Note::in);
		nik_ces bool is_post_func		= Chord::is_post_func(Note::in);

		nik_ces auto loop_pred			= Parameter::template binary_func < Proc::loop_pred >();
		nik_ces auto combine_func		= Parameter::template binary_func < Proc::combine   >();
		nik_ces auto mutate_func		= Parameter::template binary_func < Proc::mutate    >();

		nik_ces auto in_next			= Iterator::template note_next<Note::in>();

		template<typename Out, typename In, typename End>
		nik_ces auto result(Out out, In in, End end)
		{
			if nik_ce (is_pre_in_next) in = cctmp::apply<in_next>(in);

			while (cctmp::apply<loop_pred>(in, end))
			{
				cctmp::apply<mutate_func>(out, cctmp::apply<combine_func>(out, in));

				in = cctmp::apply<in_next>(in);
			}

			if nik_ce (is_post_func) cctmp::apply<mutate_func>(out, cctmp::apply<combine_func>(out, in));

			return out;
		}
	};

/***********************************************************************************************************************/

// find:

		// If the in iterator is privileged for all interval types,
		// then the out iterator is restricted to being an opening interval,
		// so as to indicate whether or not a match was found.

	template<gindex_type index, auto static_parsed, auto env>
	struct T_one_cycle<Sign::find, index, static_parsed, env>
	{
		using Parameter = T_chord_parameter <index, static_parsed, env>;
		using Iterator  = T_chord_iterator  <index, static_parsed, env>;
		using Interval  = T_chord_interval  <index, static_parsed     >;
		using Chord     = T_chord_quality   <DQ::interval, Interval   >;

		struct Proc { enum : gkey_type { action, mutate, loop_pred, dimension }; };
		struct Note { enum : gkey_type { out, in, dimension }; };

		nik_ces bool is_pre_in_next		= Chord::is_pre_next(Note::in);
		nik_ces bool is_post_pred		= Chord::is_post_func(Note::in);

		nik_ces auto loop_pred			= Parameter::template binary_func < Proc::loop_pred >();
		nik_ces auto match_pred			= Parameter::template unary_func  < Proc::action    >();
		nik_ces auto mutate_func		= Parameter::template binary_func < Proc::mutate    >();

		nik_ces auto out_next			= Iterator::template note_next<Note::out>();
		nik_ces auto in_next			= Iterator::template note_next<Note::in>();

		template<typename Out, typename In, typename End>
		nik_ces auto result(Out out, In in, End end)
		{
			bool match{false};

			if nik_ce (is_pre_in_next) in = cctmp::apply<in_next>(in);

			while (cctmp::apply<loop_pred>(in, end))
			{
				if (cctmp::apply<match_pred>(in))
				{
					cctmp::apply<mutate_func>(out, in);
					out   = cctmp::apply<out_next>(out);
					match = true;
					break;
				}

				in = cctmp::apply<in_next>(in);
			}

			if nik_ce (is_post_pred)
				if (!match && cctmp::apply<match_pred>(in))
				{
					cctmp::apply<mutate_func>(out, in);
					out = cctmp::apply<out_next>(out);
				}

			return out;
		}
	};

/***********************************************************************************************************************/

// sift:

		// If the in iterator is privileged for all interval types,
		// then the out iterator is restricted to being an opening interval,
		// so as to indicate whether or not a match was found.

	template<gindex_type index, auto static_parsed, auto env>
	struct T_one_cycle<Sign::sift, index, static_parsed, env>
	{
		using Parameter = T_chord_parameter <index, static_parsed, env>;
		using Iterator  = T_chord_iterator  <index, static_parsed, env>;
		using Interval  = T_chord_interval  <index, static_parsed     >;
		using Chord     = T_chord_quality   <DQ::interval, Interval   >;

		struct Proc { enum : gkey_type { action, mutate, loop_pred, dimension }; };
		struct Note { enum : gkey_type { out, in, dimension }; };

		nik_ces bool is_pre_in_next		= Chord::is_pre_next(Note::in);
		nik_ces bool is_post_pred		= Chord::is_post_func(Note::in);

		nik_ces auto loop_pred			= Parameter::template binary_func < Proc::loop_pred >();
		nik_ces auto match_pred			= Parameter::template unary_func  < Proc::action    >();
		nik_ces auto mutate_func		= Parameter::template binary_func < Proc::mutate    >();

		nik_ces auto out_next			= Iterator::template note_next<Note::out>();
		nik_ces auto in_next			= Iterator::template note_next<Note::in>();

		template<typename Out, typename In, typename End>
		nik_ces auto result(Out out, In in, End end)
		{
			if nik_ce (is_pre_in_next) in = cctmp::apply<in_next>(in);

			while (cctmp::apply<loop_pred>(in, end))
			{
				if (cctmp::apply<match_pred>(in))
				{
					cctmp::apply<mutate_func>(out, in);
					out = cctmp::apply<out_next>(out);
				}

				in = cctmp::apply<in_next>(in);
			}

			if nik_ce (is_post_pred)
				if (cctmp::apply<match_pred>(in))
				{
					cctmp::apply<mutate_func>(out, in);
					out = cctmp::apply<out_next>(out);
				}

			return out;
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// bidirected:

/***********************************************************************************************************************/

// map:

	template<gindex_type index, auto static_parsed, auto env>
	struct T_one_cycle<Sign::map, index, static_parsed, env>
	{
		using Parameter = T_chord_parameter <index, static_parsed, env>;
		using Iterator  = T_chord_iterator  <index, static_parsed, env>;
		using Interval  = T_chord_interval  <index, static_parsed     >;

		struct Proc { enum : gkey_type { action, mutate, loop_pred, dimension }; };
		struct Note { enum : gkey_type { out, in, end, dimension }; };

		using Chord = dispatch_chord<Interval, Note::in, Note::end, Note::out>;

		nik_ces auto pre_end_mode	= Chord::pre_tonic_iter_mode (Note::end);
		nik_ces auto pre_in_mode	= Chord::pre_root_iter_mode  (Note::in );
		nik_ces auto pre_out_mode	= Chord::pre_tone_iter_mode  (Note::out);

		nik_ces auto post_out_mode	= Chord::post_tone_iter_mode  (Note::out);
		nik_ces auto post_in_mode	= Chord::post_root_iter_mode  (Note::in );
		nik_ces auto post_end_mode	= Chord::post_tonic_iter_mode (Note::end);

		nik_ces bool is_peek		= Chord::is_peek(Note::in);
		nik_ces bool is_post_func	= Chord::is_post_func(Note::in);

		nik_ces auto action_func	= Parameter::template unary_func  < Proc::action >();
		nik_ces auto mutate_func	= Parameter::template binary_func < Proc::mutate >();

		nik_ces auto pre_out_iter	= Iterator::template note_iter <  pre_out_mode , Note::out >();
		nik_ces auto out_iter		= Iterator::template note_next <                 Note::out >();
		nik_ces auto post_out_iter	= Iterator::template note_iter < post_out_mode , Note::out >();

		nik_ces auto pre_in_iter	= Iterator::template note_iter <  pre_in_mode  , Note::in  >();
		nik_ces auto in_iter		= Iterator::template note_next <                 Note::in  >();
		nik_ces auto post_in_iter	= Iterator::template note_iter < post_in_mode  , Note::in  >();

		nik_ces auto pre_end_iter	= Iterator::template note_iter <  pre_end_mode , Note::end >();
		nik_ces auto post_end_iter	= Iterator::template note_iter < post_end_mode , Note::end >();

		nik_ces auto loop_pred		= Parameter::template binary_peek
							<Proc::loop_pred, is_peek, in_iter>();

		template<typename Out, typename In, typename End>
		nik_ces auto result(Out out, In in, End end)
		{
			if nik_ce (DI::is_iter(pre_end_mode)) end = cctmp::apply<pre_end_iter>(end);
			if nik_ce (DI::is_iter(pre_out_mode)) out = cctmp::apply<pre_out_iter>(out);
			if nik_ce (DI::is_iter(pre_in_mode )) in  = cctmp::apply<pre_in_iter>(in);

			while (cctmp::apply<loop_pred>(in, end))
			{
				cctmp::apply<mutate_func>(out, cctmp::apply<action_func>(in));

				out = cctmp::apply<out_iter>(out);
				in  = cctmp::apply<in_iter>(in);
			}

			if nik_ce (is_post_func) cctmp::apply<mutate_func>(out, cctmp::apply<action_func>(in));

			if nik_ce (DI::is_iter(post_out_mode)) out = cctmp::apply<post_out_iter>(out);
			if nik_ce (DI::is_iter(post_in_mode )) in  = cctmp::apply<post_in_iter>(in);
			if nik_ce (DI::is_iter(post_end_mode)) end = cctmp::apply<post_end_iter>(end);

			return out;
		}
	};

/***********************************************************************************************************************/

// zip (bimap):

	template<gindex_type index, auto static_parsed, auto env>
	struct T_one_cycle<Sign::zip, index, static_parsed, env>
	{
		using Parameter = T_chord_parameter <index, static_parsed, env>;
		using Iterator  = T_chord_iterator  <index, static_parsed, env>;
		using Interval  = T_chord_interval  <index, static_parsed     >;

		struct Proc { enum : gkey_type { action, mutate, loop_pred, dimension }; };
		struct Note { enum : gkey_type { out, in1, in2, end2, dimension }; };

		using Chord = dispatch_chord<Interval, Note::in2, Note::end2, Note::out, Note::in1>;

		nik_ces auto pre_end2_mode	= Chord::pre_tonic_iter_mode (Note::end2);
		nik_ces auto pre_in2_mode	= Chord::pre_root_iter_mode  (Note::in2);
		nik_ces auto pre_in1_mode	= Chord::pre_tone_iter_mode  (Note::in1);
		nik_ces auto pre_out_mode	= Chord::pre_tone_iter_mode  (Note::out);

		nik_ces auto post_out_mode	= Chord::post_tone_iter_mode  (Note::out);
		nik_ces auto post_in1_mode	= Chord::post_tone_iter_mode  (Note::in1);
		nik_ces auto post_in2_mode	= Chord::post_root_iter_mode  (Note::in2);
		nik_ces auto post_end2_mode	= Chord::post_tonic_iter_mode (Note::end2);

		nik_ces bool is_peek		= Chord::is_peek(Note::in2);
		nik_ces bool is_post_func	= Chord::is_post_func(Note::in2);

		nik_ces auto action_func	= Parameter::template binary_func < Proc::action >();
		nik_ces auto mutate_func	= Parameter::template binary_func < Proc::mutate >();

		nik_ces auto pre_out_iter	= Iterator::template note_iter <  pre_out_mode  , Note::out  >();
		nik_ces auto out_iter		= Iterator::template note_next <                  Note::out  >();
		nik_ces auto post_out_iter	= Iterator::template note_iter < post_out_mode  , Note::out  >();

		nik_ces auto pre_in1_iter	= Iterator::template note_iter <  pre_in1_mode  , Note::in1  >();
		nik_ces auto in1_iter		= Iterator::template note_next <                  Note::in1  >();
		nik_ces auto post_in1_iter	= Iterator::template note_iter < post_in1_mode  , Note::in1  >();

		nik_ces auto pre_in2_iter	= Iterator::template note_iter <  pre_in2_mode  , Note::in2  >();
		nik_ces auto in2_iter		= Iterator::template note_next <                  Note::in2  >();
		nik_ces auto post_in2_iter	= Iterator::template note_iter < post_in2_mode  , Note::in2  >();

		nik_ces auto pre_end2_iter	= Iterator::template note_iter <  pre_end2_mode , Note::end2 >();
		nik_ces auto post_end2_iter	= Iterator::template note_iter < post_end2_mode , Note::end2 >();

		nik_ces auto loop_pred		= Parameter::template binary_peek
							<Proc::loop_pred, is_peek, in2_iter>();

		template<typename Out, typename In1, typename In2, typename End2>
		nik_ces auto result(Out out, In1 in1, In2 in2, End2 end2)
		{
			if nik_ce (DI::is_iter(pre_end2_mode)) end2 = cctmp::apply<pre_end2_iter>(end2);
			if nik_ce (DI::is_iter(pre_in2_mode )) in2  = cctmp::apply<pre_in2_iter>(in2);
			if nik_ce (DI::is_iter(pre_in1_mode )) in1  = cctmp::apply<pre_in1_iter>(in1);
			if nik_ce (DI::is_iter(pre_out_mode )) out  = cctmp::apply<pre_out_iter>(out);

			while (cctmp::apply<loop_pred>(in2, end2))
			{
				cctmp::apply<mutate_func>(out, cctmp::apply<action_func>(in1, in2));

				out = cctmp::apply<out_iter>(out);
				in1 = cctmp::apply<in1_iter>(in1);
				in2 = cctmp::apply<in2_iter>(in2);
			}

			if nik_ce (is_post_func) cctmp::apply<mutate_func>(out, cctmp::apply<action_func>(in1, in2));

			if nik_ce (DI::is_iter(post_out_mode )) out  = cctmp::apply<post_out_iter>(out);
			if nik_ce (DI::is_iter(post_in1_mode )) in1  = cctmp::apply<post_in1_iter>(in1);
			if nik_ce (DI::is_iter(post_in2_mode )) in2  = cctmp::apply<post_in2_iter>(in2);
			if nik_ce (DI::is_iter(post_end2_mode)) end2 = cctmp::apply<post_end2_iter>(end2);

			return out;
		}
	};

/***********************************************************************************************************************/

// glide (bifold):

	template<gindex_type index, auto static_parsed, auto env>
	struct T_one_cycle<Sign::glide, index, static_parsed, env>
	{
		using Parameter = T_chord_parameter <index, static_parsed, env>;
		using Iterator  = T_chord_iterator  <index, static_parsed, env>;
		using Interval  = T_chord_interval  <index, static_parsed     >;

		struct Proc { enum : gkey_type { action, combine, mutate, loop_pred, dimension }; };
		struct Note { enum : gkey_type { in1, in2, end2, dimension }; }; // out is fixed.

		using Chord = dispatch_chord<Interval, Note::in2, Note::end2, Note::in1>;

		nik_ces auto pre_end2_mode	= Chord::pre_tonic_iter_mode (Note::end2);
		nik_ces auto pre_in2_mode	= Chord::pre_root_iter_mode  (Note::in2);
		nik_ces auto pre_in1_mode	= Chord::pre_tone_iter_mode  (Note::in1);

		nik_ces auto post_in1_mode	= Chord::post_tone_iter_mode  (Note::in1);
		nik_ces auto post_in2_mode	= Chord::post_root_iter_mode  (Note::in2);
		nik_ces auto post_end2_mode	= Chord::post_tonic_iter_mode (Note::end2);

		nik_ces bool is_peek		= Chord::is_peek(Note::in2);
		nik_ces bool is_post_func	= Chord::is_post_func(Note::in2);

		nik_ces auto action_func	= Parameter::template binary_func < Proc::action  >();
		nik_ces auto combine_func	= Parameter::template binary_func < Proc::combine >();
		nik_ces auto mutate_func	= Parameter::template binary_func < Proc::mutate  >();

		nik_ces auto pre_in1_iter	= Iterator::template note_iter <  pre_in1_mode  , Note::in1  >();
		nik_ces auto in1_iter		= Iterator::template note_next <                  Note::in1  >();
		nik_ces auto post_in1_iter	= Iterator::template note_iter < post_in1_mode  , Note::in1  >();

		nik_ces auto pre_in2_iter	= Iterator::template note_iter <  pre_in2_mode  , Note::in2  >();
		nik_ces auto in2_iter		= Iterator::template note_next <                  Note::in2  >();
		nik_ces auto post_in2_iter	= Iterator::template note_iter < post_in2_mode  , Note::in2  >();

		nik_ces auto pre_end2_iter	= Iterator::template note_iter <  pre_end2_mode , Note::end2 >();
		nik_ces auto post_end2_iter	= Iterator::template note_iter < post_end2_mode , Note::end2 >();

		nik_ces auto loop_pred		= Parameter::template binary_peek
							<Proc::loop_pred, is_peek, in2_iter>();

		template<typename Out, typename In1, typename In2, typename End2>
		nik_ces auto result(Out out, In1 in1, In2 in2, End2 end2)
		{
			if nik_ce (DI::is_iter(pre_end2_mode)) end2 = cctmp::apply<pre_end2_iter>(end2);
			if nik_ce (DI::is_iter(pre_in2_mode )) in2  = cctmp::apply<pre_in2_iter>(in2);
			if nik_ce (DI::is_iter(pre_in1_mode )) in1  = cctmp::apply<pre_in1_iter>(in1);

			while (cctmp::apply<loop_pred>(in2, end2))
			{
				auto val = cctmp::apply<action_func>(in1, in2);
				cctmp::apply<mutate_func>(out, cctmp::apply<combine_func>(out, val));

				in1 = cctmp::apply<in1_iter>(in1);
				in2 = cctmp::apply<in2_iter>(in2);
			}

			if nik_ce (is_post_func)
			{
				auto val = cctmp::apply<action_func>(in1, in2);
				cctmp::apply<mutate_func>(out, cctmp::apply<combine_func>(out, val));
			}

			if nik_ce (DI::is_iter(post_in1_mode )) in1  = cctmp::apply<post_in1_iter>(in1);
			if nik_ce (DI::is_iter(post_in2_mode )) in2  = cctmp::apply<post_in2_iter>(in2);
			if nik_ce (DI::is_iter(post_end2_mode)) end2 = cctmp::apply<post_end2_iter>(end2);

			return out;
		}
	};

/***********************************************************************************************************************/

// fasten (zip with a carry):

	template<gindex_type index, auto static_parsed, auto env>
	struct T_one_cycle<Sign::fasten, index, static_parsed, env>
	{
		using Parameter = T_chord_parameter <index, static_parsed, env>;
		using Iterator  = T_chord_iterator  <index, static_parsed, env>;
		using Interval  = T_chord_interval  <index, static_parsed     >;

		struct Proc { enum : gkey_type { action, carry0, carry1, carry2, mutate, loop_pred, dimension }; };
		struct Note { enum : gkey_type { out, in1, in2, end2, dimension }; }; // in is fixed.

		using Chord = dispatch_chord<Interval, Note::in2, Note::end2, Note::out, Note::in1>;

		nik_ces auto pre_end2_mode	= Chord::pre_tonic_iter_mode (Note::end2);
		nik_ces auto pre_in2_mode	= Chord::pre_root_iter_mode  (Note::in2);
		nik_ces auto pre_in1_mode	= Chord::pre_tone_iter_mode  (Note::in1);
		nik_ces auto pre_out_mode	= Chord::pre_tone_iter_mode  (Note::out);

		nik_ces auto post_out_mode	= Chord::post_tone_iter_mode  (Note::out);
		nik_ces auto post_in1_mode	= Chord::post_tone_iter_mode  (Note::in1);
		nik_ces auto post_in2_mode	= Chord::post_root_iter_mode  (Note::in2);
		nik_ces auto post_end2_mode	= Chord::post_tonic_iter_mode (Note::end2);

		nik_ces bool is_peek		= Chord::is_peek(Note::in2);
		nik_ces bool is_post_func	= Chord::is_post_func(Note::in2);

		nik_ces auto action_func	= Parameter::template binary_func < Proc::action >();
		nik_ces auto carry0_func	= Parameter::template binary_func < Proc::carry0 >();
		nik_ces auto carry1_func	= Parameter::template unary_func  < Proc::carry1 >();
		nik_ces auto carry2_func	= Parameter::template unary_func  < Proc::carry2 >();
		nik_ces auto mutate_func	= Parameter::template binary_func < Proc::mutate >();

		nik_ces auto pre_out_iter	= Iterator::template note_iter <  pre_out_mode  , Note::out  >();
		nik_ces auto out_iter		= Iterator::template note_next <                  Note::out  >();
		nik_ces auto post_out_iter	= Iterator::template note_iter < post_out_mode  , Note::out  >();

		nik_ces auto pre_in1_iter	= Iterator::template note_iter <  pre_in1_mode  , Note::in1  >();
		nik_ces auto in1_iter		= Iterator::template note_next <                  Note::in1  >();
		nik_ces auto post_in1_iter	= Iterator::template note_iter < post_in1_mode  , Note::in1  >();

		nik_ces auto pre_in2_iter	= Iterator::template note_iter <  pre_in2_mode  , Note::in2  >();
		nik_ces auto in2_iter		= Iterator::template note_next <                  Note::in2  >();
		nik_ces auto post_in2_iter	= Iterator::template note_iter < post_in2_mode  , Note::in2  >();

		nik_ces auto pre_end2_iter	= Iterator::template note_iter <  pre_end2_mode , Note::end2 >();
		nik_ces auto post_end2_iter	= Iterator::template note_iter < post_end2_mode , Note::end2 >();

		nik_ces auto loop_pred		= Parameter::template binary_peek
							<Proc::loop_pred, is_peek, in2_iter>();

		template<typename Out, typename In, typename In1, typename In2, typename End2>
		nik_ces auto result(Out out, In in, In1 in1, In2 in2, End2 end2)
		{
			if nik_ce (DI::is_iter(pre_end2_mode)) end2 = cctmp::apply<pre_end2_iter>(end2);
			if nik_ce (DI::is_iter(pre_in2_mode )) in2  = cctmp::apply<pre_in2_iter>(in2);
			if nik_ce (DI::is_iter(pre_in1_mode )) in1  = cctmp::apply<pre_in1_iter>(in1);
			if nik_ce (DI::is_iter(pre_out_mode )) out  = cctmp::apply<pre_out_iter>(out);

			while (cctmp::apply<loop_pred>(in2, end2))
			{
				auto aux = cctmp::apply<carry0_func>(in, cctmp::apply<action_func>(in1, in2));
				cctmp::apply<mutate_func>(out, cctmp::apply<carry1_func>(aux));
				cctmp::apply<mutate_func>(in, cctmp::apply<carry2_func>(aux));

				out = cctmp::apply<out_iter>(out);
				in1 = cctmp::apply<in1_iter>(in1);
				in2 = cctmp::apply<in2_iter>(in2);
			}

			if nik_ce (is_post_func)
			{
				auto aux = cctmp::apply<carry0_func>(in, cctmp::apply<action_func>(in1, in2));
				cctmp::apply<mutate_func>(out, cctmp::apply<carry1_func>(aux));
				cctmp::apply<mutate_func>(in, cctmp::apply<carry2_func>(aux));
			}

			if nik_ce (DI::is_iter(post_out_mode )) out  = cctmp::apply<post_out_iter>(out);
			if nik_ce (DI::is_iter(post_in1_mode )) in1  = cctmp::apply<post_in1_iter>(in1);
			if nik_ce (DI::is_iter(post_in2_mode )) in2  = cctmp::apply<post_in2_iter>(in2);
			if nik_ce (DI::is_iter(post_end2_mode)) end2 = cctmp::apply<post_end2_iter>(end2);

			return out;
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace chord

