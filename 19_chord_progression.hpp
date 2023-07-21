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

// space:

/***********************************************************************************************************************/

// proto cycle:

	template<auto, auto, auto, typename...> struct T_precycle;
	template<auto, auto, auto, typename...> struct T_cycle;
	template<auto, auto, auto, typename...> struct T_postcycle;

// one cycle:

	using CycleName = typename T_chord_assembly_lexer::Token;

	template<token_type, typename...> struct T_one_cycle;

	template<auto Token, typename... Ts>
	nik_ce auto U_one_cycle = U_store_T<T_one_cycle<Token, Ts...>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// unidirected:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// precycle:

	template<auto filler, auto index, auto note, typename Chord>
	struct T_precycle<filler, index, note, Chord> { nik_ces auto mode = Chord::is_pre_next(note); };

// cycle:

	template<auto filler, auto index, auto types, typename Param, typename Iter, typename Proc>
	struct T_cycle<filler, index, types, Param, Iter, Proc>
	{
		nik_ces auto loop_pred   = Param::template binary_func < index , Proc::loop_pred , types >();
		nik_ces auto mutate_func = Param::template binary_func < index , Proc::mutate    , types >();
	};

// postcycle:

	template<auto filler, auto index, auto note, typename Chord>
	struct T_postcycle<filler, index, note, Chord> { nik_ces bool mode = Chord::is_post_func(note); };

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// repeat:

/***********************************************************************************************************************/

// cycle:

	template<auto index, auto types, typename Param, typename Iter, typename Proc, typename Note>
	struct T_cycle<CycleName::repeat, index, types, Param, Iter, Proc, Note> :
		public T_cycle<CycleName::repeat, index, types, Param, Iter, Proc>
	{
		nik_ces auto action_func = Param::template unary_func<index, Proc::action, types>();

		nik_ces auto iter        = Iter::template note_next<index, Note::out, types>();
	};

/***********************************************************************************************************************/

// one cycle:

	template<typename Pre, typename Cycle, typename Post>
	struct T_one_cycle<CycleName::repeat, Pre, Cycle, Post>
	{
		template<typename Out, typename End, typename In>
		nik_ces auto result(Out out, End end, In in)
		{
			if nik_ce (Pre::mode) out = cctmp::apply<Cycle::iter>(out);

			while (cctmp::apply<Cycle::loop_pred>(out, end))
			{
				cctmp::apply<Cycle::mutate_func>(out, cctmp::apply<Cycle::action_func>(in));

				out = cctmp::apply<Cycle::iter>(out);
			}

			if nik_ce (Post::mode)
				cctmp::apply<Cycle::mutate_func>(out, cctmp::apply<Cycle::action_func>(in));

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

		struct Proc { enum : gkey_type { action, mutate, loop_pred, dimension }; };
		struct Note { enum : gkey_type { out, dimension }; }; // in is fixed.

		template<auto index, auto types>
		nik_ces auto result()
		{
			using Ival  = T_cycle_interval < static_parsed , index >;
			using Chord = T_cycle_quality  < DQ::interval  , Ival  >;

			using Pre   = T_precycle  < CycleName::repeat , index , Note::out , Chord >;
			using Post  = T_postcycle < CycleName::repeat , index , Note::out , Chord >;

			using Cycle = T_cycle<CycleName::repeat, index, types, Param, Iter, Proc, Note>;

			return U_one_cycle<CycleName::repeat, Pre, Cycle, Post>;
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// fold:

/***********************************************************************************************************************/

// cycle:

	template<auto index, auto types, typename Param, typename Iter, typename Proc, typename Note>
	struct T_cycle<CycleName::fold, index, types, Param, Iter, Proc, Note> :
		public T_cycle<CycleName::fold, index, types, Param, Iter, Proc>
	{
		nik_ces auto combine_func = Param::template binary_func<index, Proc::combine, types>();

		nik_ces auto iter         = Iter::template note_next<index, Note::in, types>();
	};

/***********************************************************************************************************************/

// one cycle:

	template<typename Pre, typename Cycle, typename Post>
	struct T_one_cycle<CycleName::fold, Pre, Cycle, Post>
	{
		template<typename Out, typename In, typename End>
		nik_ces auto result(Out out, In in, End end)
		{
			if nik_ce (Pre::mode) in = cctmp::apply<Cycle::iter>(in);

			while (cctmp::apply<Cycle::loop_pred>(in, end))
			{
				cctmp::apply<Cycle::mutate_func>(out, cctmp::apply<Cycle::combine_func>(out, in));

				in = cctmp::apply<Cycle::iter>(in);
			}

			if nik_ce (Post::mode)
				cctmp::apply<Cycle::mutate_func>(out, cctmp::apply<Cycle::combine_func>(out, in));

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
		struct Note { enum : gkey_type { in, dimension }; }; // out is fixed.

		template<auto index, auto types>
		nik_ces auto result()
		{
			using Ival  = T_cycle_interval < static_parsed , index >;
			using Chord = T_cycle_quality  < DQ::interval  , Ival  >;

			using Pre   = T_precycle  < CycleName::fold , index , Note::in , Chord >;
			using Post  = T_postcycle < CycleName::fold , index , Note::in , Chord >;

			using Cycle = T_cycle<CycleName::fold, index, types, Param, Iter, Proc, Note>;

			return U_one_cycle<CycleName::fold, Pre, Cycle, Post>;
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// find:

	// If the in iterator is privileged for all interval types,
	// then the out iterator is restricted to being an opening interval,
	// so as to indicate whether or not a match was found.

/***********************************************************************************************************************/

// cycle:

	template<auto index, auto types, typename Param, typename Iter, typename Proc, typename Note>
	struct T_cycle<CycleName::find, index, types, Param, Iter, Proc, Note> :
		public T_cycle<CycleName::find, index, types, Param, Iter, Proc>
	{
		nik_ces auto match_pred = Param::template unary_func<index, Proc::match, types>();

		nik_ces auto out_iter   = Iter::template note_next<index, Note::out, types>();
		nik_ces auto in_iter    = Iter::template note_next<index, Note::in, types>();
	};

/***********************************************************************************************************************/

// one cycle:

	template<typename Pre, typename Cycle, typename Post>
	struct T_one_cycle<CycleName::find, Pre, Cycle, Post>
	{
		template<typename Out, typename In, typename End>
		nik_ces auto result(Out out, In in, End end)
		{
			bool match{false};

			if nik_ce (Pre::mode) in = cctmp::apply<Cycle::in_iter>(in);

			while (cctmp::apply<Cycle::loop_pred>(in, end))
			{
				if (cctmp::apply<Cycle::match_pred>(in))
				{
					cctmp::apply<Cycle::mutate_func>(out, in);
					out   = cctmp::apply<Cycle::out_iter>(out);
					match = true;
					break;
				}

				in = cctmp::apply<Cycle::in_iter>(in);
			}

			if nik_ce (Post::mode)
				if (!match && cctmp::apply<Cycle::match_pred>(in))
				{
					cctmp::apply<Cycle::mutate_func>(out, in);
					out = cctmp::apply<Cycle::out_iter>(out);
				}

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

		struct Proc { enum : gkey_type { match, mutate, loop_pred, dimension }; };
		struct Note { enum : gkey_type { out, in, dimension }; };

		template<auto index, auto types>
		nik_ces auto result()
		{
			using Ival  = T_cycle_interval < static_parsed , index >;
			using Chord = T_cycle_quality  < DQ::interval  , Ival  >;

			using Pre   = T_precycle  < CycleName::find , index , Note::in , Chord >;
			using Post  = T_postcycle < CycleName::find , index , Note::in , Chord >;

			using Cycle = T_cycle<CycleName::find, index, types, Param, Iter, Proc, Note>;

			return U_one_cycle<CycleName::find, Pre, Cycle, Post>;
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

	template<typename Pre, typename Cycle, typename Post>
	struct T_one_cycle<CycleName::sift, Pre, Cycle, Post>
	{
		template<typename Out, typename In, typename End>
		nik_ces auto result(Out out, In in, End end)
		{
			if nik_ce (Pre::mode) in = cctmp::apply<Cycle::in_iter>(in);

			while (cctmp::apply<Cycle::loop_pred>(in, end))
			{
				if (cctmp::apply<Cycle::match_pred>(in))
				{
					cctmp::apply<Cycle::mutate_func>(out, in);
					out = cctmp::apply<Cycle::out_iter>(out);
				}

				in = cctmp::apply<Cycle::in_iter>(in);
			}

			if nik_ce (Post::mode)
				if (cctmp::apply<Cycle::match_pred>(in))
				{
					cctmp::apply<Cycle::mutate_func>(out, in);
					out = cctmp::apply<Cycle::out_iter>(out);
				}

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

		struct Proc { enum : gkey_type { match, mutate, loop_pred, dimension }; };
		struct Note { enum : gkey_type { out, in, dimension }; };

		template<auto index, auto types>
		nik_ces auto result()
		{
			using Ival  = T_cycle_interval < static_parsed , index >;
			using Chord = T_cycle_quality  < DQ::interval  , Ival  >;

			using Pre   = T_precycle  < CycleName::sift , index , Note::in , Chord >;
			using Post  = T_postcycle < CycleName::sift , index , Note::in , Chord >;

			using Cycle = T_cycle<CycleName::find, index, types, Param, Iter, Proc, Note>;

			return U_one_cycle<CycleName::sift, Pre, Cycle, Post>;
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// bidirected:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// cycle:

	template<auto root, auto index, auto types, typename Param, typename Iter, typename Chord, typename Proc>
	struct T_cycle<root, index, types, Param, Iter, Chord, Proc>
	{
		nik_ces auto root_iter   = Iter::template note_next<index, root, types>();

		nik_ces bool is_peek     = Chord::is_peek(root);
		nik_ces auto loop_pred   = Param::template
						binary_peek<index, Proc::loop_pred, types, is_peek, root_iter>();

		nik_ces auto mutate_func = Param::template binary_func<index, Proc::mutate, types>();
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// map:

/***********************************************************************************************************************/

// precycle:

	template<auto index, auto types, typename Iter, typename Chord, typename Note>
	struct T_precycle<CycleName::map, index, types, Iter, Chord, Note>
	{
		nik_ces auto end_mode = Chord::pre_tonic_iter_mode (Note::end);
		nik_ces auto in_mode  = Chord::pre_root_iter_mode  (Note::in );
		nik_ces auto out_mode = Chord::pre_tone_iter_mode  (Note::out);

		nik_ces auto end_iter = Iter::template note_iter < index , Note::end , types , end_mode >();
		nik_ces auto in_iter  = Iter::template note_iter < index , Note::in  , types , in_mode  >();
		nik_ces auto out_iter = Iter::template note_iter < index , Note::out , types , out_mode >();
	};

// cycle:

	template<auto index, auto types, typename Param, typename Iter, typename Chord, typename Proc, typename Note>
	struct T_cycle<CycleName::map, index, types, Param, Iter, Chord, Proc, Note> :
		public T_cycle<Note::in, index, types, Param, Iter, Chord, Proc>
	{
		using base               = T_cycle<Note::in, index, types, Param, Iter, Chord, Proc>;

		nik_ces auto action_func = Param::template unary_func<index, Proc::action, types>();
		nik_ces auto out_iter    = Iter::template note_next<index, Note::out, types>();
		nik_ces auto in_iter     = base::root_iter;
	};

// postcycle:

	template<auto index, auto types, typename Iter, typename Chord, typename Note>
	struct T_postcycle<CycleName::map, index, types, Iter, Chord, Note>
	{
		nik_ces auto out_mode  = Chord::post_tone_iter_mode  (Note::out);
		nik_ces auto in_mode   = Chord::post_root_iter_mode  (Note::in );
		nik_ces auto end_mode  = Chord::post_tonic_iter_mode (Note::end);

		nik_ces bool mode      = Chord::is_post_func(Note::in);

		nik_ces auto out_iter  = Iter::template note_iter < index , Note::out , types , out_mode >();
		nik_ces auto in_iter   = Iter::template note_iter < index , Note::in  , types , in_mode  >();
		nik_ces auto end_iter  = Iter::template note_iter < index , Note::end , types , end_mode >();
	};

/***********************************************************************************************************************/

// one cycle:

	template<typename Pre, typename Cycle, typename Post>
	struct T_one_cycle<CycleName::map, Pre, Cycle, Post>
	{
		template<typename Out, typename In, typename End>
		nik_ces auto result(Out out, In in, End end)
		{
			if nik_ce (Pre::end_mode) end = cctmp::apply<Pre::end_iter>(end);
			if nik_ce (Pre::out_mode) out = cctmp::apply<Pre::out_iter>(out);
			if nik_ce (Pre::in_mode ) in  = cctmp::apply<Pre::in_iter>(in);

			while (cctmp::apply<Cycle::loop_pred>(in, end))
			{
				cctmp::apply<Cycle::mutate_func>(out, cctmp::apply<Cycle::action_func>(in));

				out = cctmp::apply<Cycle::out_iter>(out);
				in  = cctmp::apply<Cycle::in_iter>(in);
			}

			if nik_ce (Post::mode)
				cctmp::apply<Cycle::mutate_func>(out, cctmp::apply<Cycle::action_func>(in));

			if nik_ce (Post::out_mode) out = cctmp::apply<Post::out_iter>(out);
			if nik_ce (Post::in_mode ) in  = cctmp::apply<Post::in_iter>(in);
			if nik_ce (Post::end_mode) end = cctmp::apply<Post::end_iter>(end);

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

		struct Proc { enum : gkey_type { action, mutate, loop_pred, dimension }; };
		struct Note { enum : gkey_type { out, in, end, dimension }; };

		template<auto index, auto types>
		nik_ces auto result()
		{
			using Ival  = T_cycle_interval<static_parsed, index>;
			using Chord = dispatch_chord<Ival, Note::in, Note::end, Note::out>;

			using Pre   = T_precycle  < CycleName::map , index , types, Iter , Chord , Note >;
			using Post  = T_postcycle < CycleName::map , index , types, Iter , Chord , Note >;

			using Cycle = T_cycle<CycleName::map, index, types, Param, Iter, Chord, Proc, Note>;

			return U_one_cycle<CycleName::map, Pre, Cycle, Post>;
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// zip (bimap):

/***********************************************************************************************************************/

// precycle:

	template<auto index, auto types, typename Iter, typename Chord, typename Note>
	struct T_precycle<CycleName::zip, index, types, Iter, Chord, Note>
	{
		nik_ces auto end2_mode = Chord::pre_tonic_iter_mode (Note::end2);
		nik_ces auto in2_mode  = Chord::pre_root_iter_mode  (Note::in2 );
		nik_ces auto in1_mode  = Chord::pre_tone_iter_mode  (Note::in1 );
		nik_ces auto out_mode  = Chord::pre_tone_iter_mode  (Note::out );

		nik_ces auto end2_iter = Iter::template note_iter < index , Note::end2 , types , end2_mode >();
		nik_ces auto in2_iter  = Iter::template note_iter < index , Note::in2  , types , in2_mode  >();
		nik_ces auto in1_iter  = Iter::template note_iter < index , Note::in1  , types , in1_mode  >();
		nik_ces auto out_iter  = Iter::template note_iter < index , Note::out  , types , out_mode  >();
	};

// cycle:

	template<auto index, auto types, typename Param, typename Iter, typename Chord, typename Proc, typename Note>
	struct T_cycle<CycleName::zip, index, types, Param, Iter, Chord, Proc, Note> :
		public T_cycle<Note::in2, index, types, Param, Iter, Chord, Proc>
	{
		using base               = T_cycle<Note::in2, index, types, Param, Iter, Chord, Proc>;

		nik_ces auto action_func = Param::template binary_func<index, Proc::action, types>();
		nik_ces auto out_iter    = Iter::template note_next<index, Note::out, types>();
		nik_ces auto in1_iter    = Iter::template note_next<index, Note::in1, types>();
		nik_ces auto in2_iter    = base::root_iter;
	};

// postcycle:

	template<auto index, auto types, typename Iter, typename Chord, typename Note>
	struct T_postcycle<CycleName::zip, index, types, Iter, Chord, Note>
	{
		nik_ces auto out_mode   = Chord::post_tone_iter_mode  (Note::out );
		nik_ces auto in1_mode   = Chord::post_tone_iter_mode  (Note::in1 );
		nik_ces auto in2_mode   = Chord::post_root_iter_mode  (Note::in2 );
		nik_ces auto end2_mode  = Chord::post_tonic_iter_mode (Note::end2);

		nik_ces bool mode       = Chord::is_post_func(Note::in2);

		nik_ces auto out_iter   = Iter::template note_iter < index , Note::out  , types , out_mode  >();
		nik_ces auto in1_iter   = Iter::template note_iter < index , Note::in1  , types , in1_mode  >();
		nik_ces auto in2_iter   = Iter::template note_iter < index , Note::in2  , types , in2_mode  >();
		nik_ces auto end2_iter  = Iter::template note_iter < index , Note::end2 , types , end2_mode >();
	};

/***********************************************************************************************************************/

// one cycle:

	template<typename Pre, typename Cycle, typename Post>
	struct T_one_cycle<CycleName::zip, Pre, Cycle, Post>
	{
		template<typename Out, typename In1, typename In2, typename End2>
		nik_ces auto result(Out out, In1 in1, In2 in2, End2 end2)
		{
			if nik_ce (Pre::end2_mode) end2 = cctmp::apply<Pre::end2_iter>(end2);
			if nik_ce (Pre::in2_mode ) in2  = cctmp::apply<Pre::in2_iter>(in2);
			if nik_ce (Pre::in1_mode ) in1  = cctmp::apply<Pre::in1_iter>(in1);
			if nik_ce (Pre::out_mode ) out  = cctmp::apply<Pre::out_iter>(out);

			while (cctmp::apply<Cycle::loop_pred>(in2, end2))
			{
				cctmp::apply<Cycle::mutate_func>(out, cctmp::apply<Cycle::action_func>(in1, in2));

				out = cctmp::apply<Cycle::out_iter>(out);
				in1 = cctmp::apply<Cycle::in1_iter>(in1);
				in2 = cctmp::apply<Cycle::in2_iter>(in2);
			}

			if nik_ce (Post::mode)
				cctmp::apply<Cycle::mutate_func>(out, cctmp::apply<Cycle::action_func>(in1, in2));

			if nik_ce (Post::out_mode ) out  = cctmp::apply<Post::out_iter>(out);
			if nik_ce (Post::in1_mode ) in1  = cctmp::apply<Post::in1_iter>(in1);
			if nik_ce (Post::in2_mode ) in2  = cctmp::apply<Post::in2_iter>(in2);
			if nik_ce (Post::end2_mode) end2 = cctmp::apply<Post::end2_iter>(end2);

			return out;
		}
	};

/***********************************************************************************************************************/

// cycle dispatch:

	template<auto static_parsed, auto this_f, auto env>
	struct T_cycle_dispatch<CycleName::zip, static_parsed, this_f, env>
	{
		using Param = T_cycle_parameter < static_parsed , this_f , env >;
		using Iter  = T_cycle_iterator  < static_parsed , this_f , env >;

		struct Proc { enum : gkey_type { action, mutate, loop_pred, dimension }; };
		struct Note { enum : gkey_type { out, in1, in2, end2, dimension }; };

		template<auto index, auto types>
		nik_ces auto result()
		{
			using Ival  = T_cycle_interval<static_parsed, index>;
			using Chord = dispatch_chord<Ival, Note::in2, Note::end2, Note::out, Note::in1>;

			using Pre   = T_precycle  < CycleName::zip , index , types, Iter , Chord , Note >;
			using Post  = T_postcycle < CycleName::zip , index , types, Iter , Chord , Note >;

			using Cycle = T_cycle<CycleName::zip, index, types, Param, Iter, Chord, Proc, Note>;

			return U_one_cycle<CycleName::zip, Pre, Cycle, Post>;
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// glide (bifold):

/***********************************************************************************************************************/

// precycle:

	template<auto index, auto types, typename Iter, typename Chord, typename Note>
	struct T_precycle<CycleName::glide, index, types, Iter, Chord, Note>
	{
		nik_ces auto end2_mode = Chord::pre_tonic_iter_mode (Note::end2);
		nik_ces auto in2_mode  = Chord::pre_root_iter_mode  (Note::in2 );
		nik_ces auto in1_mode  = Chord::pre_tone_iter_mode  (Note::in1 );

		nik_ces auto end2_iter = Iter::template note_iter < index , Note::end2 , types , end2_mode >();
		nik_ces auto in2_iter  = Iter::template note_iter < index , Note::in2  , types , in2_mode  >();
		nik_ces auto in1_iter  = Iter::template note_iter < index , Note::in1  , types , in1_mode  >();
	};

// cycle:

	template<auto index, auto types, typename Param, typename Iter, typename Chord, typename Proc, typename Note>
	struct T_cycle<CycleName::glide, index, types, Param, Iter, Chord, Proc, Note> :
		public T_cycle<Note::in2, index, types, Param, Iter, Chord, Proc>
	{
		using base                = T_cycle<Note::in2, index, types, Param, Iter, Chord, Proc>;

		nik_ces auto action_func  = Param::template binary_func<index, Proc::action, types>();
		nik_ces auto combine_func = Param::template binary_func<index, Proc::combine, types>();
		nik_ces auto in1_iter     = Iter::template note_next<index, Note::in1, types>();
		nik_ces auto in2_iter     = base::root_iter;
	};

// postcycle:

	template<auto index, auto types, typename Iter, typename Chord, typename Note>
	struct T_postcycle<CycleName::glide, index, types, Iter, Chord, Note>
	{
		nik_ces auto in1_mode   = Chord::post_tone_iter_mode  (Note::in1 );
		nik_ces auto in2_mode   = Chord::post_root_iter_mode  (Note::in2 );
		nik_ces auto end2_mode  = Chord::post_tonic_iter_mode (Note::end2);

		nik_ces bool mode       = Chord::is_post_func(Note::in2);

		nik_ces auto in1_iter   = Iter::template note_iter < index , Note::in1  , types , in1_mode  >();
		nik_ces auto in2_iter   = Iter::template note_iter < index , Note::in2  , types , in2_mode  >();
		nik_ces auto end2_iter  = Iter::template note_iter < index , Note::end2 , types , end2_mode >();
	};

/***********************************************************************************************************************/

// one cycle:

	template<typename Pre, typename Cycle, typename Post>
	struct T_one_cycle<CycleName::glide, Pre, Cycle, Post>
	{
		template<typename Out, typename In1, typename In2, typename End2>
		nik_ces auto result(Out out, In1 in1, In2 in2, End2 end2)
		{
			if nik_ce (Pre::end2_mode) end2 = cctmp::apply<Pre::end2_iter>(end2);
			if nik_ce (Pre::in2_mode ) in2  = cctmp::apply<Pre::in2_iter>(in2);
			if nik_ce (Pre::in1_mode ) in1  = cctmp::apply<Pre::in1_iter>(in1);

			while (cctmp::apply<Cycle::loop_pred>(in2, end2))
			{
				auto val = cctmp::apply<Cycle::action_func>(in1, in2);
				cctmp::apply<Cycle::mutate_func>(out, cctmp::apply<Cycle::combine_func>(out, val));

				in1 = cctmp::apply<Cycle::in1_iter>(in1);
				in2 = cctmp::apply<Cycle::in2_iter>(in2);
			}

			if nik_ce (Post::mode)
			{
				auto val = cctmp::apply<Cycle::action_func>(in1, in2);
				cctmp::apply<Cycle::mutate_func>(out, cctmp::apply<Cycle::combine_func>(out, val));
			}

			if nik_ce (Post::in1_mode ) in1  = cctmp::apply<Post::in1_iter>(in1);
			if nik_ce (Post::in2_mode ) in2  = cctmp::apply<Post::in2_iter>(in2);
			if nik_ce (Post::end2_mode) end2 = cctmp::apply<Post::end2_iter>(end2);

			return out;
		}
	};

/***********************************************************************************************************************/

// cycle dispatch:

	template<auto static_parsed, auto this_f, auto env>
	struct T_cycle_dispatch<CycleName::glide, static_parsed, this_f, env>
	{
		using Param = T_cycle_parameter < static_parsed , this_f , env >;
		using Iter  = T_cycle_iterator  < static_parsed , this_f , env >;

		struct Proc { enum : gkey_type { action, combine, mutate, loop_pred, dimension }; };
		struct Note { enum : gkey_type { in1, in2, end2, dimension }; }; // out is fixed.

		template<auto index, auto types>
		nik_ces auto result()
		{
			using Ival  = T_cycle_interval<static_parsed, index>;
			using Chord = dispatch_chord<Ival, Note::in2, Note::end2, Note::in1>;

			using Pre   = T_precycle  < CycleName::glide , index , types, Iter , Chord , Note >;
			using Post  = T_postcycle < CycleName::glide , index , types, Iter , Chord , Note >;

			using Cycle = T_cycle<CycleName::glide, index, types, Param, Iter, Chord, Proc, Note>;

			return U_one_cycle<CycleName::glide, Pre, Cycle, Post>;
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// fasten (zip with a carry):

/***********************************************************************************************************************/

// cycle:

	template<auto index, auto types, typename Param, typename Iter, typename Chord, typename Proc, typename Note>
	struct T_cycle<CycleName::fasten, index, types, Param, Iter, Chord, Proc, Note> :
		public T_cycle<Note::in2, index, types, Param, Iter, Chord, Proc>
	{
		using base               = T_cycle<Note::in2, index, types, Param, Iter, Chord, Proc>;

		nik_ces auto action_func = Param::template binary_func < index , Proc::action , types>();

		nik_ces auto carry0_func = Param::template binary_func < index , Proc::carry0 , types>();
		nik_ces auto carry1_func = Param::template unary_func  < index , Proc::carry1 , types>();
		nik_ces auto carry2_func = Param::template unary_func  < index , Proc::carry2 , types>();

		nik_ces auto out_iter    = Iter::template note_next<index, Note::out, types>();
		nik_ces auto in1_iter    = Iter::template note_next<index, Note::in1, types>();
		nik_ces auto in2_iter    = base::root_iter;
	};

/***********************************************************************************************************************/

// one cycle:

	template<typename Pre, typename Cycle, typename Post>
	struct T_one_cycle<CycleName::fasten, Pre, Cycle, Post>
	{
		template<typename Out, typename In, typename In1, typename In2, typename End2>
		nik_ces auto result(Out out, In in, In1 in1, In2 in2, End2 end2)
		{
			if nik_ce (Pre::end2_mode) end2 = cctmp::apply<Pre::end2_iter>(end2);
			if nik_ce (Pre::in2_mode ) in2  = cctmp::apply<Pre::in2_iter>(in2);
			if nik_ce (Pre::in1_mode ) in1  = cctmp::apply<Pre::in1_iter>(in1);
			if nik_ce (Pre::out_mode ) out  = cctmp::apply<Pre::out_iter>(out);

			while (cctmp::apply<Cycle::loop_pred>(in2, end2))
			{
				auto aux = cctmp::apply<Cycle::carry0_func>(in, cctmp::apply<Cycle::action_func>(in1, in2));
				cctmp::apply<Cycle::mutate_func>(out, cctmp::apply<Cycle::carry1_func>(aux));
				cctmp::apply<Cycle::mutate_func>(in, cctmp::apply<Cycle::carry2_func>(aux));

				out = cctmp::apply<Cycle::out_iter>(out);
				in1 = cctmp::apply<Cycle::in1_iter>(in1);
				in2 = cctmp::apply<Cycle::in2_iter>(in2);
			}

			if nik_ce (Post::mode)
			{
				auto aux = cctmp::apply<Cycle::carry0_func>(in, cctmp::apply<Cycle::action_func>(in1, in2));
				cctmp::apply<Cycle::mutate_func>(out, cctmp::apply<Cycle::carry1_func>(aux));
				cctmp::apply<Cycle::mutate_func>(in, cctmp::apply<Cycle::carry2_func>(aux));
			}

			if nik_ce (Post::out_mode ) out  = cctmp::apply<Post::out_iter>(out);
			if nik_ce (Post::in1_mode ) in1  = cctmp::apply<Post::in1_iter>(in1);
			if nik_ce (Post::in2_mode ) in2  = cctmp::apply<Post::in2_iter>(in2);
			if nik_ce (Post::end2_mode) end2 = cctmp::apply<Post::end2_iter>(end2);

			return out;
		}
	};

/***********************************************************************************************************************/

// cycle dispatch:

	template<auto static_parsed, auto this_f, auto env>
	struct T_cycle_dispatch<CycleName::fasten, static_parsed, this_f, env>
	{
		using Param = T_cycle_parameter < static_parsed , this_f , env >;
		using Iter  = T_cycle_iterator  < static_parsed , this_f , env >;

		struct Proc { enum : gkey_type { action, carry0, carry1, carry2, mutate, loop_pred, dimension }; };
		struct Note { enum : gkey_type { out, in1, in2, end2, dimension }; }; // in is fixed.

		template<auto index, auto types>
		nik_ces auto result()
		{
			using Ival  = T_cycle_interval<static_parsed, index>;
			using Chord = dispatch_chord<Ival, Note::in2, Note::end2, Note::out, Note::in1>;

			using Pre   = T_precycle  < CycleName::zip , index , types, Iter , Chord , Note >;
			using Post  = T_postcycle < CycleName::zip , index , types, Iter , Chord , Note >;
					// Pre and Post are factored through zip.

			using Cycle = T_cycle<CycleName::fasten, index, types, Param, Iter, Chord, Proc, Note>;

			return U_one_cycle<CycleName::fasten, Pre, Cycle, Post>;
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace chord

