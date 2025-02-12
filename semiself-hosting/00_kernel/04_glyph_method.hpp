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

// glyph method:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// base:

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class glyph_cmethod_disjoint : public book_cmethod_disjoint<Base, array_cmethod, table_csubmethod, icon>
	{
		public:

			using base		= book_cmethod_disjoint<Base, array_cmethod, table_csubmethod, icon>;
			using facade		= typename base::facade;

			nik_using_size_type	(base)

		public:

			nik_ce glyph_cmethod_disjoint() : base{} { }
			nik_ce glyph_cmethod_disjoint(const facade & f) : base{f} { }

			// type check:

			//	template<typename T, typename... Ts>
			//	nik_ce bool same_types(size_ctype n, const T l, const Ts... rs) const
			//		{ return same_methods(n, page_to_text_cequip(l), page_to_text_cequip(rs)...); }

			//	template<typename T, typename... Ts>
			//	nik_ce bool same_methods(size_ctype n, const T & l, const Ts &... rs) const
			//	{
			//		for (size_type k = 0; k != n; ++k)
			//			{ if (different_values(l[k], rs[k]...)) return false; }

			//		return true;
			//	}

			//	template<typename T, typename... Ts>
			//	nik_ce bool different_values(const T l, const Ts... rs) const
			//		{ return (... || (l != rs)); }
	};

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class glyph_method_disjoint : public book_method_disjoint<Base, array_method, table_submethod>
	{
		public:

			using base		= book_method_disjoint<Base, array_method, table_submethod>;
			using facade		= typename base::facade;

			nik_using_size_type	(base)

		public:

			nik_ce glyph_method_disjoint() : base{} { }
			nik_ce glyph_method_disjoint(const facade & f) : base{f} { }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// builtin:

/***********************************************************************************************************************/

// names:

	struct GlyphBuiltin
	{
		enum : gkey_type
		{
			name, bytes,
			dimension
		};
	};

	using GBuiltin = GlyphBuiltin;

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class glyph_builtin_cmethod_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;
			using model_type		= typename base::model_type;

			nik_using_size_type		(base)

			using icon_type			= typename base::icon_type;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

		protected:

			nik_ces size_type unit_length	= 1;

		public:

			nik_ce glyph_builtin_cmethod_disjoint() : base{} { }
			nik_ce glyph_builtin_cmethod_disjoint(const facade & f) : base{f} { }

			nik_ce size_type unit_size() const { return unit_length; }

			// find:

			//	nik_ce size_type left_find(size_ctype bits) const
			//		{ return base::left_find({base::name, (bits >> 3)}); }
	};

	// syntactic sugar:

		template<typename Facade>
		using gbuiltin_cmethod =
			glyph_builtin_cmethod_disjoint <
			glyph_cmethod_disjoint         < Facade >>;

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class glyph_builtin_method_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;
			using model_type		= typename base::model_type;

			nik_using_size_type		(base)

			using icon_type			= typename base::icon_type;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

		public:

			nik_ce glyph_builtin_method_disjoint() : base{} { }
			nik_ce glyph_builtin_method_disjoint(const facade & f) : base{f} { }

		//	nik_ce void initialize(icon_ctype_ref icon, size_ctype bytes)
		//	{
		//		auto glyph_submethod = glyph_method.icon_to_text_equip(icon);

		//			// name is redundant, bits is now bytes.
		//			// each types specifies to which universe it belongs.
		//			// has free (glyph).
		//		glyph_submethod[GRing::arity] = Gram::ringN;
		//		glyph_submethod[GRing::lines] = bytes;
		//		glyph_submethod[GRing::bytes] = bytes;
		//	}

		//	nik_ce auto instantiate(size_ctype bytes)
		//	{
		//		auto icon = glyph_method.overlay();

		//		if (icon.not_fail()) { initialize(icon, bytes); }

		//		return icon;
		//	}

		//	nik_ce auto declare(size_ctype bytes)
		//	{
		//		size_ctype pos = glyph_method.left_find(bytes);

		//		if (glyph_method.found(pos)) { return glyph_method.make_icon(pos); }
		//		else                         { return instantiate(bytes); }
		//	}
	};

	// syntactic sugar:

		template<typename Facade>
		using gbuiltin_method =
			glyph_builtin_method_disjoint  <
			glyph_builtin_cmethod_disjoint <
			glyph_method_disjoint          <
			glyph_cmethod_disjoint         < Facade >>>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// ring:

/***********************************************************************************************************************/

// names:

	using GRing = GBuiltin;

/***********************************************************************************************************************/

// immutable:

	// syntactic sugar:

		template<typename Facade>
		using gring_cmethod = gbuiltin_cmethod<Facade>;

/***********************************************************************************************************************/

// mutable:

	// syntactic sugar:

		template<typename Facade>
		using gring_method = gbuiltin_method<Facade>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// flex:

/***********************************************************************************************************************/

// :

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// utf8 char:

/***********************************************************************************************************************/

// names:

	using GUtf8Char = GBuiltin;

/***********************************************************************************************************************/

// immutable:

	// syntactic sugar:

		template<typename Facade>
		using gutf8_char_cmethod = gbuiltin_cmethod<Facade>;

/***********************************************************************************************************************/

// mutable:

	// syntactic sugar:

		template<typename Facade>
		using gutf8_char_method = gbuiltin_method<Facade>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// tuple:

/***********************************************************************************************************************/

// :

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// cotuple:

/***********************************************************************************************************************/

// :

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// function:

/***********************************************************************************************************************/

// :

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// list:

/***********************************************************************************************************************/

// :

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// identity:

/***********************************************************************************************************************/

// :

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// exists:

/***********************************************************************************************************************/

// :

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// forall:

/***********************************************************************************************************************/

// :

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

