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

// graph:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// guider:

/***********************************************************************************************************************/

// immutable:

	class cguider : public citerator<gindex_type>
	{
		protected:

			using base		= citerator<gindex_type>;

		public:

			using type		= typename base::type;
			using type_ptr		= typename base::type_ptr;
			using type_ref		= typename base::type_ref;
			using type_cptr		= typename base::type_cptr;

			using ctype		= typename base::ctype;
			using ctype_ptr		= typename base::ctype_ptr;
			using ctype_cptr	= typename base::ctype_cptr;
			using ctype_ref		= typename base::ctype_ref;

			using size_type		= typename base::size_type;
			using csize_type	= typename base::csize_type;

		protected:

			enum Position : size_type
			{
				absolute = 0,
				relative,
				content,

				dimension
			};

			ctype_ptr origin;
			ctype_ptr vertex;

			nik_ce ctype_ptr cptr_meta(csize_type pos) const { return vertex + pos; }
			nik_ce ctype_ref cref_meta(csize_type pos) const { return *cptr_meta(pos); }

		public:

			nik_ce cguider() : base{}, origin{}, vertex{} { }
			nik_ce cguider(ctype_cptr o, csize_type p = 0) : base{}, origin{o}, vertex{} { reorient(p); }
			nik_ce cguider(const cguider *g) : base{g}, origin{g->origin}, vertex{g->vertex} { }

			nik_ce auto citerate() const { return citerator{this}; }

			nik_ce size_type pos() const { return vertex - origin; }
			nik_ce size_type dim() const { return dimension; }

			nik_ce ctype_ref cabsolute_size () const { return cref_meta(absolute); }
			nik_ce ctype_ref crelative_size () const { return cref_meta(relative); }

			nik_ce ctype_ref operator ~ () const { return cref_meta(content); }

			nik_ce cguider & operator -= (csize_type num) { base::current -= num; return *this; }
			nik_ce cguider & operator += (csize_type num) { base::current += num; return *this; }
			nik_ce cguider & operator -- () { --base::current; return *this; }
			nik_ce cguider & operator ++ () { ++base::current; return *this; }

			nik_ce cguider operator  - (csize_type num) { cguider g{*this}; return g -= num; }
			nik_ce cguider operator  + (csize_type num) { cguider g{*this}; return g += num; }
			nik_ce cguider operator -- (int) { cguider g{*this}; --base::current; return g; }
			nik_ce cguider operator ++ (int) { cguider g{*this}; ++base::current; return g; }

		public:

			nik_ce void reorient(csize_type pos, csize_type offset = 0)
			{
				vertex        = origin + pos;
				base::start   = vertex + dimension;
				base::finish  = base::cptr_at(crelative_size());
				base::current = base::cptr_at(offset);
			}

			nik_ce void go   () { reorient(base::operator * ()); }
			nik_ce void pass () { if (base::not_end()) go(); }

			nik_ce void cross (csize_type pos) { base::pivot (pos); go   (); }
			nik_ce void walk  (csize_type pos) { base::step  (pos); pass (); }

			nik_ce void cross_first () { cross(0); }
			nik_ce void cross_last  () { cross(base::size() - 1); }

			nik_ce void walk_first () { walk(0); }
			nik_ce void walk_last  () { walk(base::size() - 1); }

			nik_ce cguider & operator + () { go(); return *this; }

			nik_ce cguider & move(csize_type pos) { cross(pos); return *this; }

			nik_ce cguider next() const { cguider g{*this}; return +g; }
			nik_ce cguider next(csize_type pos) { cguider g{*this}; return g.move(pos); }
	};

	using cguider_ctype	= cguider const;
	using cguider_ctype_ptr	= cguider_ctype*;
	using cguider_ctype_ref	= cguider_ctype&;

/***********************************************************************************************************************/

// mutable:

	struct guider : public cguider
	{
		template<auto> friend class navigator;

		using base		= cguider;

		using type		= typename base::type;
		using type_ptr		= typename base::type_ptr;
		using type_ref		= typename base::type_ref;
		using type_cptr		= typename base::type_cptr;

		using ctype		= typename base::ctype;
		using ctype_ptr		= typename base::ctype_ptr;
		using ctype_cptr	= typename base::ctype_cptr;
		using ctype_ref		= typename base::ctype_ref;

		using size_type		= typename base::size_type;
		using csize_type	= typename base::csize_type;

		nik_ce guider() : base{} { }
		nik_ce guider(ctype_cptr o) : base{o} { }
		nik_ce guider(const guider *g) : base{g} { }

		nik_ce auto cguide() const { return cguider{this}; }

		nik_ce type_ref absolute_size () { return (type_ref) base::cref_meta(absolute); }
		nik_ce type_ref relative_size () { return (type_ref) base::cref_meta(relative); }

		nik_ce type_ref operator * () { return (type_ref) base::operator * (); }
		nik_ce type_ref operator ~ () { return (type_ref) base::operator ~ (); }

		nik_ce guider & operator -= (csize_type num) { base::current -= num; return *this; }
		nik_ce guider & operator += (csize_type num) { base::current += num; return *this; }
		nik_ce guider & operator -- () { --base::current; return *this; }
		nik_ce guider & operator ++ () { ++base::current; return *this; }

		nik_ce guider operator  - (csize_type num) { guider g{*this}; return g -= num; }
		nik_ce guider operator  + (csize_type num) { guider g{*this}; return g += num; }
		nik_ce guider operator -- (int) { guider g{*this}; --base::current; return g; }
		nik_ce guider operator ++ (int) { guider g{*this}; ++base::current; return g; }

		nik_ce guider & operator + () { base::go(); return *this; }

		nik_ce type_ptr begin () { return (type_ptr) base::cbegin(); }
		nik_ce type_ptr last  () { return (type_ptr) base::clast(); }
		nik_ce type_ptr end   () { return (type_ptr) base::cend(); }

		nik_ce void push(ctype_ref v) { *end() = v; base::upright(); ++relative_size(); }
		nik_ce type pop() { auto v = *end(); base::downright(); --relative_size(); return v; }

		nik_ce guider & move(csize_type pos) { base::cross(pos); return *this; }

		nik_ce guider next() const { guider g{*this}; return +g; }
		nik_ce guider next(csize_type pos) { guider g{*this}; return g.move(pos); }
	};

	using guider_ctype	= guider const;
	using guider_ctype_ptr	= guider_ctype*;
	using guider_ctype_ref	= guider_ctype&;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// shape:

/***********************************************************************************************************************/

// interface:

	template<auto Size>
	class T_shape : public sequence<gindex_type, Size>
	{
		protected:

			using base		= sequence<gindex_type, Size>;

		public:

			using type		= typename base::type;
			using ctype		= typename base::ctype;
			using type_ptr		= typename base::type_ptr;
			using ctype_ptr		= typename base::ctype_ptr;
			using type_ref		= typename base::type_ref;
			using ctype_ref		= typename base::ctype_ref;

			nik_ce T_shape(ctype l, ctype v = 0) : base{}
			{
				guider g{base::initial};

				g.absolute_size() = l;
				~g = v;

				base::upsize(l + g.dim());
			}

			nik_ce auto cguide() const { return cguider{base::initial}; }
			nik_ce auto guide() { return guider{base::initial}; }

		protected:

			nik_ce void fast_append(guider & g, ctype l, ctype v)
			{
				g.push(base::size());

				guider j{base::terminal};
				j.absolute_size() = l;
				~j = v;

				base::upsize(l + j.dim());
			}

		public:

			nik_ce bool append(guider & g, ctype l, ctype v = 0)
			{
				auto success = (g.crelative_size() < g.cabsolute_size());

				if (success) fast_append(g, l, v);

				return success;
			}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// navigator:

/***********************************************************************************************************************/

// immutable:

	template<auto Size>
	class cnavigator : public cguider
	{
		template<auto, auto> friend class T_hierarchy;

		protected:

			using base		= cguider;

		public:

			using type		= typename base::type;
			using type_ptr		= typename base::type_ptr;
			using type_ref		= typename base::type_ref;
			using type_cptr		= typename base::type_cptr;

			using ctype		= typename base::ctype;
			using ctype_ptr		= typename base::ctype_ptr;
			using ctype_cptr	= typename base::ctype_cptr;
			using ctype_ref		= typename base::ctype_ref;

			using size_type		= typename base::size_type;
			using csize_type	= typename base::csize_type;

			using path_type		= sequence<type, Size>;

		protected:

			path_type vertex_path;
			path_type current_path;

		public:

			nik_ce cnavigator() : base{} { }
			nik_ce cnavigator(ctype_cptr o) : base{o} { }
			nik_ce cnavigator(const cnavigator *n) :
				base{n}, vertex_path{n->vertex_path}, current_path{n->current_path} { }

			nik_ce auto cguide() const { return cguider{this}; }
			nik_ce ctype depth() const { return vertex_path.size(); }

			nik_ce cnavigator & operator -= (csize_type num) { base::current -= num; return *this; }
			nik_ce cnavigator & operator += (csize_type num) { base::current += num; return *this; }
			nik_ce cnavigator & operator -- () { --base::current; return *this; }
			nik_ce cnavigator & operator ++ () { ++base::current; return *this; }

			nik_ce cnavigator operator  - (csize_type num) { cnavigator n{*this}; return n -= num; }
			nik_ce cnavigator operator  + (csize_type num) { cnavigator n{*this}; return n += num; }
			nik_ce cnavigator operator -- (int) { cnavigator n{*this}; --base::current; return n; }
			nik_ce cnavigator operator ++ (int) { cnavigator n{*this}; ++base::current; return n; }

			nik_ce cnavigator & operator - () { preorient(); return *this; }
			nik_ce cnavigator & operator + () { go(); return *this; }

		//	nik_ce cnavigator & operator <<= (csize_type num) { shift_backward (num); return *this; }
		//	nik_ce cnavigator & operator >>= (csize_type num) { shift_forward  (num); return *this; }

		public:

			nik_ce void reorient(csize_type pos, csize_type offset = 0)
			{
				vertex_path.push(base::pos());
				current_path.push(base::left_size());

				base::reorient(pos, offset);
			}

			nik_ce void preorient() { base::reorient(vertex_path.pop(), current_path.pop()); }

			nik_ce void go() { reorient(base::operator * ()); }
			nik_ce void pass () { if (base::not_end()) go(); }

			nik_ce void cross (csize_type pos) { base::pivot (pos); go   (); }
			nik_ce void walk  (csize_type pos) { base::step  (pos); pass (); }

			nik_ce void cross_first () { cross(0); }
			nik_ce void cross_last  () { cross(base::size() - 1); }

			nik_ce void walk_first () { walk(0); }
			nik_ce void walk_last  () { walk(base::size() - 1); }

			nik_ce cnavigator & move(csize_type pos) { cross(pos); return *this; }

			nik_ce cnavigator next() const { cnavigator n{*this}; return +n; }
			nik_ce cnavigator next(csize_type pos) { cnavigator n{*this}; return n.move(pos); }

		//	nik_ce auto cedge() const { return cguider{*point}; }
		//	nik_ce auto cedge(ctype pos) const { return cedge().next(pos); }

		protected:

			// immutable:

			//	nik_ce bool not_path_first() { return (*point != path.citerate().cbegin()); }
			//	nik_ce bool not_path_last() { return (*point != path.citerate().clast()); }

			//	nik_ce path_citer_type fast_previous() { return (point - 1); }
			//	nik_ce path_citer_type previous() { return point - not_path_first(); }

			// mutable:

			//	nik_ce void fast_up   () { --point; }
			//	nik_ce void fast_down () { *(point + 1) = point->next(); ++point; }

			//	nik_ce void up   () { if (not_path_first()) fast_up(); }
			//	nik_ce void down () { if (not_path_last()) fast_down(); }

			//	nik_ce void backward (csize_type num = 1) { point->backward(num); }
			//	nik_ce void forward  (csize_type num = 1) { point->forward(num); }

			//	nik_ce void shift_backward(csize_type num = 1)
			//	{
			//		fast_up();
			//		backward(num);
			//		fast_down();
			//	}

			//	nik_ce void shift_forward(csize_type num = 1)
			//	{
			//		fast_up();
			//		forward(num);
			//		fast_down();
			//	}
	};

/***********************************************************************************************************************/

// mutable:

	template<auto Size>
	class navigator : public cnavigator<Size>
	{
		protected:

			using base		= cnavigator<Size>;

		public:

			using type		= typename base::type;
			using type_ptr		= typename base::type_ptr;
			using type_ref		= typename base::type_ref;
			using type_cptr		= typename base::type_cptr;

			using ctype		= typename base::ctype;
			using ctype_ptr		= typename base::ctype_ptr;
			using ctype_cptr	= typename base::ctype_cptr;
			using ctype_ref		= typename base::ctype_ref;

			using size_type		= typename base::size_type;
			using csize_type	= typename base::csize_type;

			using path_type		= typename base::path_type;

		public:

			nik_ce navigator() : base{} { }
			nik_ce navigator(ctype_cptr o) : base{o} { }
			nik_ce navigator(const navigator *n) : base{n} { }

			nik_ce auto cnavigate() const { return cnavigator{this}; }
			nik_ce auto guide() const
			{
				guider g{base::origin};
				g.reorient(base::pos());
				return g;
			}

			nik_ce type_ref absolute_size () { return (type_ref) base::cref_meta(base::absolute); }
			nik_ce type_ref relative_size () { return (type_ref) base::cref_meta(base::relative); }

			nik_ce type_ref operator * () { return (type_ref) base::operator * (); }
			nik_ce type_ref operator ~ () { return (type_ref) base::operator ~ (); }

			nik_ce navigator & operator -= (csize_type num) { base::current -= num; return *this; }
			nik_ce navigator & operator += (csize_type num) { base::current += num; return *this; }
			nik_ce navigator & operator -- () { --base::current; return *this; }
			nik_ce navigator & operator ++ () { ++base::current; return *this; }

			nik_ce navigator operator  - (csize_type num) { navigator n{*this}; return n -= num; }
			nik_ce navigator operator  + (csize_type num) { navigator n{*this}; return n += num; }
			nik_ce navigator operator -- (int) { navigator n{*this}; --base::current; return n; }
			nik_ce navigator operator ++ (int) { navigator n{*this}; ++base::current; return n; }

			nik_ce navigator & operator - () { base::preorient(); return *this; }
			nik_ce navigator & operator + () { base::go(); return *this; }

		//	nik_ce navigator & operator <<= (csize_type num) { base::shift_backward (num); return *this; }
		//	nik_ce navigator & operator >>= (csize_type num) { base::shift_forward  (num); return *this; }

		public:

			nik_ce type_ptr begin () { return (type_ptr) base::cbegin(); }
			nik_ce type_ptr last  () { return (type_ptr) base::clast(); }
			nik_ce type_ptr end   () { return (type_ptr) base::cend(); }

			nik_ce void push(ctype_ref v) { *end() = v; base::upright(); ++relative_size(); }
			nik_ce type pop() { auto v = *end(); base::downright(); --relative_size(); return v; }

			nik_ce navigator & move(csize_type pos) { base::cross(pos); return *this; }

			nik_ce navigator next() const { navigator n{*this}; return +n; }
			nik_ce navigator next(csize_type pos) { navigator n{*this}; return n.move(pos); }

		//	nik_ce auto cprevious() const { return cguider{*base::previous()}; }
		//	nik_ce auto previous() { return guider{*base::previous()}; }

		//	nik_ce auto edge() { return guider{*base::point}; }
		//	nik_ce auto edge(ctype pos) { return edge().next(pos); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// hierarchy:

/***********************************************************************************************************************/

// interface:

	template<auto Depth, auto Size>
	class T_hierarchy : public T_shape<Size>
	{
		protected:

			using base			= T_shape<Size>;
			using depth_type		= decltype(Depth);

		public:

			using type		= typename base::type;
			using ctype		= typename base::ctype;
			using max_type		= sequence<type, Depth>;
			using cnavigator_type	= cnavigator<Depth>;
			using navigator_type	= navigator<Depth>;

		protected:

			nik_ces auto depth	= Depth;
			nik_ces auto length	= Size;

			max_type max;

		public:

			template<typename... Ts>
			nik_ce T_hierarchy(ctype l0, Ts... ls) : base{l0}, max{l0, type(ls)...} { }

			nik_ce auto origin() const { return base::initial; }

			nik_ce auto cguide() const { return cguider{base::initial}; }
			nik_ce auto guide() const { return guider{base::initial}; }

			nik_ce auto cnavigate() const { return cnavigator_type{base::initial}; }
			nik_ce auto navigate() const { return navigator_type{base::initial}; }

			nik_ce bool append(navigator_type & n, ctype v = 0)
			{
				auto g = n.guide();

				auto l = max[n.depth() + 1];

				return base::append(g, l, v);
			}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

