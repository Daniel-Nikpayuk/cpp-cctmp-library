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

// signifier method:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// base:

/***********************************************************************************************************************/

// immutable:

	template<typename Base, typename Base::size_type Name, typename Base::size_type Dimension>
	class signifier_cmethod_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;
			using model_type		= typename facade::model_type;

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;
			using size_ctype_ptr		= typename alias<size_type>::ctype_ptr;
			using size_ctype_cptr		= typename alias<size_type>::ctype_cptr;

			using gram_type			= gram<size_type>;
			using gram_ctype_ref		= typename alias<gram_type>::ctype_ref;

		protected:

			nik_ces size_type name		= Name;
			nik_ces size_type dimension	= Dimension;

			using page_cmethod_type		= typename model_type::page_cmethod_type;
			using text_cmethod_type		= typename model_type::text_cmethod_type;

			page_cmethod_type page_cmethod;
			text_cmethod_type text_cmethod;

		public:

			nik_ce signifier_cmethod_disjoint() : base{}, page_cmethod{}, text_cmethod{} { }
			nik_ce signifier_cmethod_disjoint(const facade & f) :

				base{f},
				page_cmethod{page_cequip(name)},
				text_cmethod{text_cequip()}
				{ }

			// page:

				nik_ce auto page_cequip(size_ctype n) const
					{ return base::model->page_cequip(n); }

			// text:

				nik_ce auto text_cequip() const { return base::model->text_cequip(); }

					// unsafe, does not test against name().

				nik_ce auto text_csubequip(size_ctype n) const
					{ return base::model->text_csubequip(n); }

				nik_ce auto page_to_text_cequip(size_ctype n) const
					{ return text_csubequip(page_cmethod[n]); }

				nik_ce auto gram_to_text_cequip(gram_ctype_ref g) const
					{ return page_to_text_cequip(g.index()); }

			// gram:

				nik_ce auto fail_gram() const { return gram_type{Logo::fail, 0}; }
				nik_ce auto make_gram(size_ctype pos) const { return gram_type{name, pos}; }

			// find:

				nik_ce bool found(size_ctype n) const
					{ return (n != page_cmethod.size()); }

				template<typename T, auto N>
				nik_ce auto find(const T (&field)[N]) const
				{
					auto in = page_cmethod.cbegin();

					while (in != page_cmethod.cend())
					{
						auto text_csubmethod = text_csubequip(*in);

						bool same{true};
						for (size_type k = 0; same && (k != N); ++k)
							{ same = (text_csubmethod[k] == field[k]); }

						if (same) { break; } else { ++in; }
					}

					return in;
				}

				template<typename T, auto N>
				nik_ce size_type left_find(const T (&field)[N]) const
					{ return find(field) - page_cmethod.cbegin(); }

			// same:

				template<typename T, typename... Ts>
				nik_ce bool same_types(size_ctype n, const T l, const Ts... rs) const
					{ return same_methods(n, page_to_text_cequip(l), page_to_text_cequip(rs)...); }

				template<typename T, typename... Ts>
				nik_ce bool same_methods(size_ctype n, const T & l, const Ts &... rs) const
				{
					for (size_type k = 0; k != n; ++k)
						{ if (different_values(l[k], rs[k]...)) return false; }

					return true;
				}

				template<typename T, typename... Ts>
				nik_ce bool different_values(const T l, const Ts... rs) const
					{ return (... || (l != rs)); }
	};

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class signifier_method_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;
			using model_type		= typename base::model_type;

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

			using gram_type			= typename base::gram_type;
			using gram_ctype_ref		= typename base::gram_ctype_ref;

		protected:

			nik_ce bool facade_overlay() { return facade::overlay(base::name, base::dimension); }

		public:

			nik_ce signifier_method_disjoint() : base{} { }
			nik_ce signifier_method_disjoint(const facade & f) : base{f} { }

			// text:

				 // unsafe, does not test against name().

				nik_ce auto text_subequip(size_ctype n)
					{ return base::model->text_subequip(n); }

				nik_ce auto page_to_text_equip(size_ctype n)
					{ return text_subequip(base::page_cmethod[n]); }

				nik_ce auto gram_to_text_equip(gram_ctype_ref g)
					{ return page_to_text_equip(g.index()); }

			// overlay:

				nik_ce auto overlay()
				{
					if (not facade_overlay()) return base::fail_gram();

					return base::make_gram(base::page_cmethod.max());
				}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// builtin:

/***********************************************************************************************************************/

// names:

	struct SignifierBuiltin
	{
		enum : gkey_type
		{
			name, bits,
			dimension
		};
	};

	using RBuiltin = SignifierBuiltin;

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class signifier_builtin_cmethod_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;
			using model_type		= typename base::model_type;

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

			using gram_type			= typename base::gram_type;
			using gram_ctype_ref		= typename base::gram_ctype_ref;

		public:

			nik_ce signifier_builtin_cmethod_disjoint() : base{} { }
			nik_ce signifier_builtin_cmethod_disjoint(const facade & f) : base{f} { }

			// find:

				nik_ce size_type left_find(size_ctype bits) const
					{ return base::left_find({base::name, bits}); }
	};

	// syntactic sugar:

		template<typename Facade, auto Name>
		using rbuiltin_cmethod =
			signifier_builtin_cmethod_disjoint <
			signifier_cmethod_disjoint         < Facade, Name, RBuiltin::dimension >>;

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class signifier_builtin_method_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;
			using model_type		= typename base::model_type;

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

			using gram_type			= typename base::gram_type;
			using gram_ctype_ref		= typename base::gram_ctype_ref;

		public:

			nik_ce signifier_builtin_method_disjoint() : base{} { }
			nik_ce signifier_builtin_method_disjoint(const facade & f) : base{f} { }
	};

	// syntactic sugar:

		template<typename Facade, auto Name>
		using rbuiltin_method =
			signifier_builtin_method_disjoint  <
			signifier_builtin_cmethod_disjoint <
			signifier_method_disjoint          <
			signifier_cmethod_disjoint         < Facade, Name, RBuiltin::dimension >>>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// ring:

/***********************************************************************************************************************/

// names:

	using RRing = RBuiltin;

/***********************************************************************************************************************/

// immutable:

	// syntactic sugar:

		template<typename Facade>
		using rring_cmethod = rbuiltin_cmethod<Facade, Logo::ringN>;

/***********************************************************************************************************************/

// mutable:

	// syntactic sugar:

		template<typename Facade>
		using rring_method = rbuiltin_method<Facade, Logo::ringN>;

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

	using RUtf8Char = RBuiltin;

/***********************************************************************************************************************/

// immutable:

	// syntactic sugar:

		template<typename Facade>
		using rutf8_char_cmethod = rbuiltin_cmethod<Facade, Logo::utf8_charN>;

/***********************************************************************************************************************/

// mutable:

	// syntactic sugar:

		template<typename Facade>
		using rutf8_char_method = rbuiltin_method<Facade, Logo::utf8_charN>;

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

