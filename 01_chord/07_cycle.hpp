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

// cycle:

namespace chord {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

	nik_ce auto _same_					= cctmp::_same_;

	template<auto... Vs>
	nik_ce auto _curry_					= cctmp::_curry_<Vs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// morph:

	using MorphName = typename T_chord_assembly_lexer::Token;

/***********************************************************************************************************************/

// subpose:

	template<auto static_parsed, auto this_f, auto env>
	struct T_morph_dispatch<MorphName::subpose, static_parsed, this_f, env>
	{
		nik_ces auto & parsed = member_value_U<static_parsed>;
		using T_link          = T_lookup_morph_link<static_parsed, this_f, env>;

		template<auto index, auto types, auto... Is>
		nik_ces auto result(nik_avp(T_pack_Vs<Is...>*))
			{ return _subpose_<T_link::template result<index, Is>(types)...>; }
	};

/***********************************************************************************************************************/

// compose:

	template<auto static_parsed, auto this_f, auto env>
	struct T_morph_dispatch<MorphName::compose, static_parsed, this_f, env>
	{
		nik_ces auto & parsed = member_value_U<static_parsed>;
		using T_link          = T_lookup_morph_link<static_parsed, this_f, env>;

		template<auto index, auto types, auto... Is>
		nik_ces auto result(nik_avp(T_pack_Vs<Is...>*))
			{ return _compose_<T_link::template result<index, Is>(types)...>; }
	};

/***********************************************************************************************************************/

// curry:

	template<auto static_parsed, auto this_f, auto env>
	struct T_morph_dispatch<MorphName::curry, static_parsed, this_f, env>
	{
		nik_ces auto & parsed = member_value_U<static_parsed>;
		using T_link          = T_lookup_morph_link<static_parsed, this_f, env>;

		template<auto index, auto types, auto... Is>
		nik_ces auto result(nik_avp(T_pack_Vs<Is...>*))
			{ return _curry_<T_link::template result<index, Is>(types)...>; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// space:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// parameter:

/***********************************************************************************************************************/

// interface:

	template<auto static_parsed, auto this_f, auto env>
	struct T_cycle_parameter
	{
		nik_ces auto & parsed = member_value_U<static_parsed>;
		using T_link          = T_lookup_cycle_link<static_parsed, this_f, env>;

		template<auto l, auto types, auto... Is>
		nik_ces auto all_id = (... && eval<_same_, _id_, T_link::template action<l, Is>(types)>);

		template<auto l, auto types, auto I0, auto... Is>
		nik_ces auto action_func(nik_avp(T_pack_Vs<I0, Is...>*))
		{
			nik_ce auto op = T_link::template action<l, I0>(types);

			if nik_ce (all_id<l, types, Is...>) return op;
			else return _subpose_<op, T_link::template action<l, Is>(types)...>;
		}

		template<auto l, auto n, auto types>
		nik_ces auto binary_func()
		{
			nik_ce auto op         = T_link::template parameter<l, n, 0>(types);
			nik_ce auto arg0       = T_link::template parameter<l, n, 1>(types);
			nik_ce auto arg1       = T_link::template parameter<l, n, 2>(types);
			nik_ce bool arg0_is_id = eval<_same_, arg0, _id_>;
			nik_ce bool arg1_is_id = eval<_same_, arg1, _id_>;

			if nik_ce (arg0_is_id && arg1_is_id) return op;
			else return _subpose_<op, arg0, arg1>;
		}

		template<auto l, auto n, auto types, bool is_peek, auto iter>
		nik_ces auto binary_peek()
		{
			nik_ce auto op = binary_func<l, n, types>();

			if nik_ce (!is_peek) return op;
			else return _subpose_<op, iter, _id_>;
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// iterator:

	struct ChordIterator
	{
		enum : gkey_type { none, next, prev, dimension };

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

	template<auto static_parsed, auto this_f, auto env>
	struct T_cycle_iterator
	{
		nik_ces auto & parsed = member_value_U<static_parsed>;
		using T_link          = T_lookup_cycle_link<static_parsed, this_f, env>;

		template<auto l, auto n, auto types>
		nik_ces auto note_next() { return T_link::template iterator<l, n, 0>(types); }

		template<auto l, auto n, auto types>
		nik_ces auto note_prev() { return T_link::template iterator<l, n, 1>(types); }

		template<auto l, auto n, auto types, auto mode>
		nik_ces auto note_iter()
		{
			if      nik_ce (mode == DI::next) return note_next<l, n, types>();
			else if nik_ce (mode == DI::prev) return note_prev<l, n, types>();
			else                              return _id_;
		}

		template<auto l, auto types, auto mode>
		nik_ces auto tonic_iter()
		{
			if      nik_ce (mode == DI::next) return T_link::template tonic<l, 0>(types);
			else if nik_ce (mode == DI::prev) return T_link::template tonic<l, 1>(types);
			else                              return _id_;
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// interval:

/***********************************************************************************************************************/

// interface:

	template<auto static_parsed, gindex_type index>
	struct T_cycle_interval
	{
		nik_ces auto & parsed   = member_value_U<static_parsed>;
		nik_ces auto & cycle    = parsed.cycle_level[index]; // referenced externally.
		nik_ces auto & interval = cycle.interval;

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
			major, diminished, minor,
			tonic_augmented, tone_augmented, peek_augmented,
			dimension
		};

		private:

			template<typename Interval>
			nik_ces auto reversible(gckey_type note) { return Interval::cycle.is_reversible(note); }

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
			nik_ces auto open(Ts... tones)
			{
				if      (Interval::all_right_open(tones...)         ) return major;
				else if (Interval::cycle.tonic_is_reversible()      ) return tonic_augmented;
				else if (right_closed_reversible<Interval>(tones...)) return tone_augmented;
				else                                                  return peek_augmented;
			}

			template<typename Interval, typename... Ts>
			nik_ces auto closed(Ts... tones)
			{
				if (Interval::all_right_closed(tones...)) return diminished;
				else                                      return minor;
			}

		public:

			template<typename Interval, auto root, auto... tones>
			nik_ces auto name(nik_avp(T_pack_Vs<root, tones...>*))
			{
				if (Interval::is_right_open(root)) return open<Interval>(tones...);
				else                               return closed<Interval>(tones...);
			}
	};

	using DQ = ChordQuality;

	template<gkey_type, typename> struct T_cycle_quality;

	template<typename Interval, auto pack>
	using dispatch_chord = T_cycle_quality<DQ::name<Interval>(pack), Interval>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// major:

	// { root, tonic ) ; { tone ) // tone aligns centre

/***********************************************************************************************************************/

// interface:

	template<gindex_type index, auto static_parsed>
	struct T_cycle_quality<DQ::major, T_cycle_interval<static_parsed, index>>
	{
		using Interval = T_cycle_interval<static_parsed, index>;

		nik_ces auto pre_root_iter_mode   (gckey_type note) { return DI::pre_next_mode<Interval>(note); }
		nik_ces auto pre_tone_iter_mode   (gckey_type note) { return DI::pre_next_mode<Interval>(note); }
		nik_ces auto pre_tonic_iter_mode  (               ) { return DI::none; }

		nik_ces auto post_root_iter_mode  (               ) { return DI::none; }
		nik_ces auto post_tone_iter_mode  (gckey_type note) { return DI::none; }
		nik_ces auto post_tonic_iter_mode (               ) { return DI::none; }

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
	struct T_cycle_quality<DQ::tonic_augmented, T_cycle_interval<static_parsed, index>>
	{
		using Interval = T_cycle_interval<static_parsed, index>;

		nik_ces auto pre_root_iter_mode   (gckey_type note) { return DI::pre_next_mode<Interval>(note); }
		nik_ces auto pre_tone_iter_mode   (gckey_type note) { return DI::pre_next_mode<Interval>(note); }
		nik_ces auto pre_tonic_iter_mode  (               ) { return DI::prev; }

		nik_ces auto post_root_iter_mode  (               ) { return DI::next; }
		nik_ces auto post_tone_iter_mode  (gckey_type note) { return DI::post_next_mode<Interval>(note); }
		nik_ces auto post_tonic_iter_mode (               ) { return DI::next; }

		nik_ces bool is_peek      (gckey_type note) { return false; }
		nik_ces bool is_post_func (gckey_type note) { return true; }
	};

/***********************************************************************************************************************/

// tone:

	// tonic is not reversible, but tones that stop short are all reversible: march root and tones;
	// backdate said tones.

	template<gindex_type index, auto static_parsed>
	struct T_cycle_quality<DQ::tone_augmented, T_cycle_interval<static_parsed, index>>
	{
		using Interval = T_cycle_interval<static_parsed, index>;

		nik_ces auto pre_root_iter_mode   (gckey_type note) { return DI::pre_next_mode<Interval>(note); }
		nik_ces auto pre_tone_iter_mode   (gckey_type note) { return DI::pre_next_mode<Interval>(note); }
		nik_ces auto pre_tonic_iter_mode  (               ) { return DI::none; }

		nik_ces auto post_root_iter_mode  (               ) { return DI::none; }
		nik_ces auto post_tone_iter_mode  (gckey_type note) { return DI::post_prev_mode<Interval>(note); }
		nik_ces auto post_tonic_iter_mode (               ) { return DI::none; }

		nik_ces bool is_peek      (gckey_type note) { return false; }
		nik_ces bool is_post_func (gckey_type note) { return false; }
	};

/***********************************************************************************************************************/

// peek:

	// tonic is not reversible, at least one tone is not reversible: we peek march root and tones;
	// update root and tones. root acts on its last position as if it were right closed before being updated.

	template<gindex_type index, auto static_parsed>
	struct T_cycle_quality<DQ::peek_augmented, T_cycle_interval<static_parsed, index>>
	{
		using Interval = T_cycle_interval<static_parsed, index>;

		nik_ces auto pre_root_iter_mode   (gckey_type note) { return DI::pre_next_mode<Interval>(note); }
		nik_ces auto pre_tone_iter_mode   (gckey_type note) { return DI::pre_next_mode<Interval>(note); }
		nik_ces auto pre_tonic_iter_mode  (               ) { return DI::none; }

		nik_ces auto post_root_iter_mode  (               ) { return DI::next; }
		nik_ces auto post_tone_iter_mode  (gckey_type note) { return DI::post_next_mode<Interval>(note); }
		nik_ces auto post_tonic_iter_mode (               ) { return DI::none; }

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
	struct T_cycle_quality<DQ::diminished, T_cycle_interval<static_parsed, index>>
	{
		using Interval = T_cycle_interval<static_parsed, index>;

		nik_ces auto pre_root_iter_mode   (gckey_type note) { return DI::pre_next_mode<Interval>(note); }
		nik_ces auto pre_tone_iter_mode   (gckey_type note) { return DI::pre_next_mode<Interval>(note); }
		nik_ces auto pre_tonic_iter_mode  (               ) { return DI::none; }

		nik_ces auto post_root_iter_mode  (               ) { return DI::none; }
		nik_ces auto post_tone_iter_mode  (gckey_type note) { return DI::none; }
		nik_ces auto post_tonic_iter_mode (               ) { return DI::none; }

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
	struct T_cycle_quality<DQ::minor, T_cycle_interval<static_parsed, index>>
	{
		using Interval = T_cycle_interval<static_parsed, index>;

		nik_ces auto pre_root_iter_mode   (gckey_type note) { return DI::pre_next_mode<Interval>(note); }
		nik_ces auto pre_tone_iter_mode   (gckey_type note) { return DI::pre_next_mode<Interval>(note); }
		nik_ces auto pre_tonic_iter_mode  (               ) { return DI::none; }

		nik_ces auto post_root_iter_mode  (               ) { return DI::none; }
		nik_ces auto post_tone_iter_mode  (gckey_type note) { return DI::post_next_mode<Interval>(note); }
		nik_ces auto post_tonic_iter_mode (               ) { return DI::none; }

		nik_ces bool is_peek      (gckey_type note) { return false; }
		nik_ces bool is_post_func (gckey_type note) { return true; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace chord

