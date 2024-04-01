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

// cycle:

namespace chord {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// quality:

	template<typename> struct T_chord_subcycle;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// augmented:

/***********************************************************************************************************************/

// tonic:

	template<typename Cycle>
	struct T_chord_augmented_tonic
	{
		using size_type		= typename Cycle::size_type;
		using csize_type	= typename Cycle::csize_type;
		using Subcycle		= T_chord_subcycle<Cycle>;

		// am, out, in, ins:

			template<typename Prog, typename AST>
			nik_ces void am_out_in_ins(AST *t)
			{
			}

		// am, out, ins:

			template<typename Prog, typename AST>
			nik_ces void am_out_ins(AST *t)
			{
			}

		// acm, in, ins:

			template<typename Prog, typename AST>
			nik_ces void acm_in_ins(AST *t)
			{
			}
	};

/***********************************************************************************************************************/

// tone:

	template<typename Cycle>
	struct T_chord_augmented_tone
	{
		using size_type		= typename Cycle::size_type;
		using csize_type	= typename Cycle::csize_type;
		using Subcycle		= T_chord_subcycle<Cycle>;

		// am, out, in, ins:

			template<typename Prog, typename AST>
			nik_ces void am_out_in_ins(AST *t)
			{
			}

		// am, out, ins:

			template<typename Prog, typename AST>
			nik_ces void am_out_ins(AST *t)
			{
			}

		// acm, in, ins:

			template<typename Prog, typename AST>
			nik_ces void acm_in_ins(AST *t)
			{
			}
	};

/***********************************************************************************************************************/

// peek:

	template<typename Cycle>
	struct T_chord_augmented_peek
	{
		using size_type		= typename Cycle::size_type;
		using csize_type	= typename Cycle::csize_type;
		using Subcycle		= T_chord_subcycle<Cycle>;

		// am, out, in, ins:

			template<typename Prog, typename AST>
			nik_ces void am_out_in_ins(AST *t)
			{
			}

		// am, out, ins:

			template<typename Prog, typename AST>
			nik_ces void am_out_ins(AST *t)
			{
			}

		// acm, in, ins:

			template<typename Prog, typename AST>
			nik_ces void acm_in_ins(AST *t)
			{
			}
	};

/***********************************************************************************************************************/

// interface:

	template<typename Cycle>
	struct T_chord_augmented
	{
		using size_type		= typename Cycle::size_type;
		using csize_type	= typename Cycle::csize_type;
		using Tonic		= T_chord_augmented_tonic <Cycle>;
		using Tone		= T_chord_augmented_tone  <Cycle>;
		using Peek		= T_chord_augmented_peek  <Cycle>;

		// am, out, in, ins:

			template<typename Prog, typename AST>
			nik_ces void am_out_in_ins(AST *t)
			{
				if      (t->interval.is_tonic(Prog::Ival::in)) Tonic::template am_out_in_ins<Prog>(t);
				else if (t->interval.is_tone())                Tone::template  am_out_in_ins<Prog>(t);
				else                                           Peek::template  am_out_in_ins<Prog>(t);
			}

		// am, out, ins:

			template<typename Prog, typename AST>
			nik_ces void am_out_ins(AST *t)
			{
				if      (t->interval.is_tonic(Prog::Ival::out)) Tonic::template am_out_ins<Prog>(t);
				else if (t->interval.is_tone())                 Tone::template  am_out_ins<Prog>(t);
				else                                            Peek::template  am_out_ins<Prog>(t);
			}

		// acm, in, ins:

			template<typename Prog, typename AST>
			nik_ces void acm_in_ins(AST *t)
			{
				if      (t->interval.is_tonic(Prog::Ival::in)) Tonic::template acm_in_ins<Prog>(t);
				else if (t->interval.is_tone())                Tone::template  acm_in_ins<Prog>(t);
				else                                           Peek::template  acm_in_ins<Prog>(t);
			}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// diminished:

/***********************************************************************************************************************/

// interface:

	template<typename Cycle>
	struct T_chord_diminished
	{
		using size_type		= typename Cycle::size_type;
		using csize_type	= typename Cycle::csize_type;
		using Subcycle		= T_chord_subcycle<Cycle>;

		// am, out, in, ins:

			template<typename Prog, typename AST>
			nik_ces void am_out_in_ins(AST *t) { Cycle::action(t); }

		// am, out, ins:

			template<typename Prog, typename AST>
			nik_ces void am_out_ins(AST *t) { Cycle::action(t); }

		// acm, in, ins:

			template<typename Prog, typename AST>
			nik_ces void acm_in_ins(AST *t) { Cycle::action(t); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// minor:

/***********************************************************************************************************************/

// interface:

	template<typename Cycle>
	struct T_chord_minor
	{
		using size_type		= typename Cycle::size_type;
		using csize_type	= typename Cycle::csize_type;
		using Subcycle		= T_chord_subcycle<Cycle>;

		// am, out, in, ins:

			template<typename Prog, typename AST>
			nik_ces void am_out_in_ins(AST *t)
			{
				Cycle::action(t);

				if      (t->interval.is_right_open(Prog::Ival::out)) next_out_in_ins <Prog>(t);
				else if (t->interval.is_right_open(Prog::Ival::in))  next_in_ins     <Prog>(t);
				else                                                 next_ins        <Prog>(t);
			}

		// am, out, ins:

			template<typename Prog, typename AST>
			nik_ces void am_out_ins(AST *t)
			{
				Cycle::action(t);

				if (t->interval.is_right_open(Prog::Ival::out)) next_out_in_ins <Prog>(t);
				else                                            next_ins        <Prog>(t);
			}

		// acm, in, ins:

			template<typename Prog, typename AST>
			nik_ces void acm_in_ins(AST *t)
			{
				Cycle::action(t);

				if (t->interval.is_right_open(Prog::Ival::in)) next_in_ins <Prog>(t);
				else                                           next_ins    <Prog>(t);
			}

		// generic:

			template<typename Prog, typename AST>
			nik_ces void next_out_in_ins(AST *t) { Subcycle::template next_out_in_ins<Prog>(t); }

			template<typename Prog, typename AST>
			nik_ces void next_in_ins(AST *t) { Subcycle::template next_in_ins<Prog>(t); }

			template<typename Prog, typename AST>
			nik_ces void next_ins(AST *t) { Subcycle::template next_ins<Prog>(t); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// one cycle:

/***********************************************************************************************************************/

// subcycle:

	template<typename Cycle>
	struct T_chord_subcycle
	{
		using size_type		= typename Cycle::size_type;
		using csize_type	= typename Cycle::csize_type;

		// sign:

			template<typename Prog, typename AST>
			nik_ces auto sign_out(AST *t) { return t->verse.size() + Prog::Sign::out; }

			template<typename Prog, typename AST>
			nik_ces auto sign_in(AST *t) { return sign_out<Prog>(t) + Prog::Sign::in; }

			template<typename Prog, typename AST>
			nik_ces auto sign_ins(AST *t) { return sign_out<Prog>(t) + Prog::Sign::ins; }

		// next:

			template<typename Prog, typename AST>
			nik_ces void next_out_in_ins(AST *t)
			{
				auto out_pos = sign_out <Prog>(t);
				auto in_pos  = sign_in  <Prog>(t);
				auto ins_pos = sign_ins <Prog>(t);

				Cycle::next_begin(t, out_pos);
				Cycle::next_cont(t, Prog::Ival::out, in_pos);
				Cycle::next_cont(t, Prog::Ival::in, ins_pos);
				Cycle::next_rest(t, Prog::Ival::ins, ins_pos);
				Cycle::next_end(t);
			}

			template<typename Prog, typename AST>
			nik_ces void next_out_ins(AST *t)
			{
				auto out_pos = sign_out<Prog>(t);
				auto ins_pos = sign_ins<Prog>(t);

				Cycle::next_begin(t, out_pos);
				Cycle::next_cont(t, Prog::Ival::out, ins_pos);
				Cycle::next_rest(t, Prog::Ival::ins, ins_pos);
				Cycle::next_end(t);
			}

			template<typename Prog, typename AST>
			nik_ces void next_in_ins(AST *t)
			{
				auto in_pos  = sign_in  <Prog>(t);
				auto ins_pos = sign_ins <Prog>(t);

				Cycle::next_begin(t, in_pos);
				Cycle::next_cont(t, Prog::Ival::in, ins_pos);
				Cycle::next_rest(t, Prog::Ival::ins, ins_pos);
				Cycle::next_end(t);
			}

			template<typename Prog, typename AST>
			nik_ces void next_ins(AST *t)
			{
				auto ins_pos = sign_ins<Prog>(t);

				Cycle::next_rest(t, Prog::Ival::ins, ins_pos);
				Cycle::next_end(t);
			}
	};

/***********************************************************************************************************************/

// precycle:

	template<typename SizeType>
	struct T_chord_precycle
	{
		using size_type		= SizeType;
		using csize_type	= size_type const;
		using Subcycle		= T_chord_subcycle<T_chord_precycle>;

		// define:

			// out, in, ins:

				template<typename Prog, typename AST>
				nik_ces void define_out_in_ins(AST *t)
					{ if (t->interval.has_left_next()) dispatch_out_in_ins<Prog>(t); }

			// out, ins:

				template<typename Prog, typename AST>
				nik_ces void define_out_ins(AST *t)
					{ if (t->interval.has_left_next()) dispatch_out_ins<Prog>(t); }

			// in, ins:

				template<typename Prog, typename AST>
				nik_ces void define_in_ins(AST *t)
					{ if (t->interval.has_left_next()) dispatch_in_ins<Prog>(t); }

		// dispatch:

			// out, in, ins:

				template<typename Prog, typename AST>
				nik_ces void dispatch_out_in_ins(AST *t)
				{
					if      (t->interval.is_left_open(Prog::Ival::out)) next_out_in_ins <Prog>(t);
					else if (t->interval.is_left_open(Prog::Ival::in))  next_in_ins     <Prog>(t);
					else                                                next_ins        <Prog>(t);
				}

			// out, ins:

				template<typename Prog, typename AST>
				nik_ces void dispatch_out_ins(AST *t)
				{
					if (t->interval.is_left_open(Prog::Ival::out)) next_out_ins <Prog>(t);
					else                                           next_ins     <Prog>(t);
				}

			// in, ins:

				template<typename Prog, typename AST>
				nik_ces void dispatch_in_ins(AST *t)
				{
					if (t->interval.is_left_open(Prog::Ival::in)) next_in_ins <Prog>(t);
					else                                          next_ins    <Prog>(t);
				}

			// next:

				// out, in, ins:

					template<typename Prog, typename AST>
					nik_ces void next_out_in_ins(AST *t)
					{
						if (t->interval.is_left_open(Prog::Ival::in))

							Subcycle::template next_out_in_ins<Prog>(t);
						else
							Subcycle::template next_out_ins<Prog>(t);
					}

				// out, ins:

					template<typename Prog, typename AST>
					nik_ces void next_out_ins(AST *t) { Subcycle::template next_out_ins<Prog>(t); }

				// in, ins:

					template<typename Prog, typename AST>
					nik_ces void next_in_ins(AST *t) { Subcycle::template next_in_ins<Prog>(t); }

				// ins:

					template<typename Prog, typename AST>
					nik_ces void next_ins(AST *t) { Subcycle::template next_ins<Prog>(t); }

		// generic:

			template<typename AST>
			nik_ces void next_begin(AST *t, csize_type first_arg)
				{ t->next_begin(t->cycle_front, AST::CycleFront::next, first_arg); }

			template<typename AST>
			nik_ces void next_cont(AST *t, csize_type ival_pos, csize_type next_arg)
				{ if (t->interval.is_left_open(ival_pos)) t->define_next_cont(ival_pos, next_arg); }

			template<typename AST>
			nik_ces void next_rest(AST *t, csize_type b, csize_type n)
				{ for (auto k = b; k != t->interval.size(); ++k) next_cont(t, k, n + k - 1); }

			template<typename AST>
			nik_ces void next_end(AST *t) { t->define_next_end(); }
	};

/***********************************************************************************************************************/

// cycle:

	template<typename SizeType>
	struct T_chord_cycle
	{
		using size_type		= SizeType;
		using csize_type	= size_type const;
		using Subcycle		= T_chord_subcycle<T_chord_cycle>;

		// am, out, in, ins:

			template<typename Prog, typename AST>
			nik_ces void define_am_out_in_ins(AST *t)
			{
				define_pred            <Prog>(t);
				define_action_am       <Prog>(t);
				define_next_out_in_ins <Prog>(t);
			}

		// am, out, ins:

			template<typename Prog, typename AST>
			nik_ces void define_am_out_ins(AST *t)
			{
				define_pred         <Prog>(t);
				define_action_am    <Prog>(t);
				define_next_out_ins <Prog>(t);
			}

		// acm, in, ins:

			template<typename Prog, typename AST>
			nik_ces void define_acm_in_ins(AST *t)
			{
				define_pred        <Prog>(t);
				define_action_acm  <Prog>(t);
				define_next_in_ins <Prog>(t);
			}

		// pred:

			template<typename Prog, typename AST>
			nik_ces void define_pred(AST *t)
			{
				auto ni = t->get_predicate();

				t->cycle_id[AST::CycleId::predicate] = t->contr.current(1);
				t->template assembly_action<AAN::id, AAT::begin>();
				t->template assembly_action<AAN::push, AAT::instr>(Prog::name, AT::pred, ni);
			}

		// action:

			// am:

				template<typename Prog, typename AST>
				nik_ces void define_action_am(AST *t)
				{
					auto name = Prog::name;
					auto note = AT::act_mut;
					auto ni   = t->get_action();
					auto mi   = t->get_mutate();

					t->cycle_side[AST::CycleSide::action] = t->contr.current(1);
					t->template assembly_action<AAN::id, AAT::begin>();
					t->template assembly_action<AAN::push, AAT::instr>(name, note, ni, mi);
				}

			// acm:

				template<typename Prog, typename AST>
				nik_ces void define_action_acm(AST *t)
				{
					auto name = Prog::name;
					auto note = AT::comb_mut;
					auto ni   = t->get_action();
					auto mi   = t->get_combine();
					auto li   = t->get_mutate();

					t->cycle_side[AST::CycleSide::action] = t->contr.current(1);
					t->template assembly_action<AAN::id, AAT::begin>();
					t->template assembly_action<AAN::push, AAT::instr>(name, note, ni, mi, li);
				}

		// next:

			// out, in, ins:

				template<typename Prog, typename AST>
				nik_ces void define_next_out_in_ins(AST *t) { Subcycle::template next_out_in_ins<Prog>(t); }

			// out, ins:

				template<typename Prog, typename AST>
				nik_ces void define_next_out_ins(AST *t) { Subcycle::template next_out_ins<Prog>(t); }

			// in, ins:

				template<typename Prog, typename AST>
				nik_ces void define_next_in_ins(AST *t) { Subcycle::template next_in_ins<Prog>(t); }

		// generic:

			template<typename AST>
			nik_ces void next_begin(AST *t, csize_type first_arg)
				{ t->next_begin(t->cycle_side, AST::CycleSide::next, first_arg); }

			template<typename AST>
			nik_ces void next_cont(AST *t, csize_type ival_pos, csize_type next_arg)
				{ if (t->interval.not_fixed(ival_pos)) t->define_next_cont(ival_pos, next_arg); }

			template<typename AST>
			nik_ces void next_rest(AST *t, csize_type b, csize_type n)
				{ for (auto k = b; k != t->interval.size(); ++k) next_cont(t, k, n + k - 1); }

			template<typename AST>
			nik_ces void next_end(AST *t) { t->define_next_end(); }
	};

/***********************************************************************************************************************/

// postcycle:

	template<typename SizeType>
	struct T_chord_postcycle
	{
		using size_type		= SizeType;
		using csize_type	= size_type const;
		using Subcycle		= T_chord_subcycle   <T_chord_postcycle>;
		using Augmented		= T_chord_augmented  <T_chord_postcycle>;
		using Diminished	= T_chord_diminished <T_chord_postcycle>;
		using Minor		= T_chord_minor      <T_chord_postcycle>;

		// define:

			// am, out, in, ins:

				template<typename Prog, typename AST>
				nik_ces void define_am_out_in_ins(AST *t)
				{
					if      (t->interval.is_augmented())  Augmented::template  am_out_in_ins<Prog>(t);
					else if (t->interval.is_diminished()) Diminished::template am_out_in_ins<Prog>(t);
					else if (t->interval.is_minor())      Minor::template      am_out_in_ins<Prog>(t);
				}

			// am, out, ins:

				template<typename Prog, typename AST>
				nik_ces void define_am_out_ins(AST *t)
				{
					if      (t->interval.is_augmented())  Augmented::template  am_out_ins<Prog>(t);
					else if (t->interval.is_diminished()) Diminished::template am_out_ins<Prog>(t);
					else if (t->interval.is_minor())      Minor::template      am_out_ins<Prog>(t);
				}

			// acm, in, ins:

				template<typename Prog, typename AST>
				nik_ces void define_acm_in_ins(AST *t)
				{
					if      (t->interval.is_augmented())  Augmented::template  acm_in_ins<Prog>(t);
					else if (t->interval.is_diminished()) Diminished::template acm_in_ins<Prog>(t);
					else if (t->interval.is_minor())      Minor::template      acm_in_ins<Prog>(t);
				}

		// generic:

			template<typename AST>
			nik_ces void action(AST *t)
				{ t->cycle_back[AST::CycleBack::action] = t->cycle_side[AST::CycleSide::action]; }

			template<typename AST>
			nik_ces void next_begin(AST *t, csize_type first_arg)
				{ t->next_begin(t->cycle_back, AST::CycleBack::next, first_arg); }

			template<typename AST>
			nik_ces void next_cont(AST *t, csize_type ival_pos, csize_type next_arg)
				{ if (t->interval.is_right_open(ival_pos)) t->define_next_cont(ival_pos, next_arg); }

			template<typename AST>
			nik_ces void next_rest(AST *t, csize_type b, csize_type n)
				{ for (auto k = b; k != t->interval.size(); ++k) next_cont(t, k, n + k - 1); }

			template<typename AST>
			nik_ces void next_end(AST *t) { t->define_next_end(); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// progression:

/***********************************************************************************************************************/

// repeat:

	template<typename size_type>
	struct T_chord_repeat
	{
		nik_ces size_type name = AN::out_ins;

		struct Ival { enum : size_type { out, ins, dimension, in }; };		// debugging.
		struct Sign { enum : size_type { out, end, ins, dimension, in }; };	// debugging.
	};

/***********************************************************************************************************************/

// map:

	template<typename size_type>
	struct T_chord_map
	{
		nik_ces size_type name = AN::out_in_ins;

		struct Ival { enum : size_type { out, in, ins, dimension }; };
		struct Sign { enum : size_type { out, in, end, ins, dimension }; };
	};

/***********************************************************************************************************************/

// fold:

	template<typename size_type>
	struct T_chord_fold
	{
		nik_ces size_type name = AN::out_in_ins;

		struct Ival { enum : size_type { out, in, ins, dimension }; };
		struct Sign { enum : size_type { out, in, end, ins, dimension }; };
	};

/***********************************************************************************************************************/

// find:

	template<typename size_type>
	struct T_chord_find
	{
		nik_ces size_type name = AN::out_in_ins;

		struct Ival { enum : size_type { out, in, ins, dimension }; };
		struct Sign { enum : size_type { out, in, end, ins, dimension }; };
	};

/***********************************************************************************************************************/

// sift:

	template<typename size_type>
	struct T_chord_sift
	{
		nik_ces size_type name = AN::out_in_ins;

		struct Ival { enum : size_type { out, in, ins, dimension }; };
		struct Sign { enum : size_type { out, in, end, ins, dimension }; };
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace chord

