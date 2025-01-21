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

// corpus method:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// ring:

/***********************************************************************************************************************/

// immutable:

	template<typename Facade>
	class corpus_ring_cmethod : public Facade
	{
		public:

			using base			= Facade;

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

		public:

			nik_ce corpus_ring_cmethod() : base{} { }
			nik_ce corpus_ring_cmethod(const Facade & f) : base{f} { }
	};

	// syntactic sugar:

		template<typename Facade>
		using cring_cmethod = corpus_ring_cmethod<Facade>;

/***********************************************************************************************************************/

// mutable:

	template<typename Facade>
	class corpus_ring_method : public corpus_ring_cmethod<Facade>
	{
		public:

			using base			= corpus_ring_cmethod<Facade>;

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

			using sign_type			= sign<size_type>;
			using sign_ctype_ref		= typename alias<sign_type>::ctype_ref;

		protected:

			using record_type		= typename Facade::record_type;
			using signifier_type		= typename record_type::signifier_type;
			using signified_type		= typename record_type::signified_type;

			using rmethod_type		= resolve_method<signifier_type, rring_method>;
			using dmethod_type		= resolve_method<signified_type, dring_method>;

			using gram_type			= typename rmethod_type::gram_type;
			using gram_ctype_ref		= typename rmethod_type::gram_ctype_ref;

			using icon_type			= typename dmethod_type::icon_type;
			using icon_ctype_ref		= typename dmethod_type::icon_ctype_ref;

		protected:

			rmethod_type rmethod;
			dmethod_type dmethod;

			nik_ce auto make_rmethod()
				{ return base::record().template signifier_equip<rmethod_type>(); }

			nik_ce auto make_dmethod()
				{ return base::record().template signified_equip<dmethod_type>(); }

			nik_ce bool not_fail(gram_ctype_ref g) const { return (g.get_kind() != Logo::fail); }
			nik_ce bool not_fail(icon_ctype_ref i) const { return (i.get_kind() != Logo::fail); }

			nik_ce bool not_fail(gram_ctype_ref g, icon_ctype_ref i) const
				{ return (not_fail(g) && not_fail(i)); }

			// declare signifier:

				nik_ce void initialize_signifier(gram_ctype_ref gram, size_ctype bits)
				{
					auto sub_rmethod = rmethod.text_right_equip(gram);

					sub_rmethod[RRing::name] = Logo::ring;
					sub_rmethod[RRing::bits] = bits;
				}

				nik_ce auto instantiate_signifier(size_ctype bits)
				{
					auto gram = rmethod.overlay();

					if (not_fail(gram)) { initialize_signifier(gram, bits); }

					return gram;
				}

				nik_ce auto declare_signifier(size_ctype bits)
				{
					size_ctype pos = rmethod.left_find(bits);

					if (rmethod.found(pos)) { return rmethod.ring_gram(pos); }
					else                    { return instantiate_signifier(bits); }
				}

			// declare signified:

				nik_ce void initialize_signified(icon_ctype_ref icon, size_ctype start)
				{
					auto sub_dmethod = dmethod.text_right_equip(icon);

					sub_dmethod[DRing::start] = start;
					sub_dmethod[DRing::bytes] = dmethod.byte_size();
				}

				nik_ce auto instantiate_signified(size_ctype start)
				{
					auto icon = dmethod.overlay();

					if (not_fail(icon)) { initialize_signified(icon, start); }

					return icon;
				}

				nik_ce auto declare_signified(size_ctype start)
				{
					size_ctype pos = dmethod.left_find(start);

					if (dmethod.found(pos)) { return dmethod.fail_icon(); }
					else                    { return instantiate_signified(start); }
				}

		public:

			nik_ce corpus_ring_method() :
				base{}, rmethod{make_rmethod()}, dmethod{make_dmethod()} { }

			nik_ce corpus_ring_method(const Facade & f) :
				base{f}, rmethod{make_rmethod()}, dmethod{make_dmethod()} { }

			// initialization:

				nik_ce auto declare(size_ctype bits)
				{
					auto gram = declare_signifier(bits);
					auto icon = declare_signified(base::memory().expand(dmethod.byte_size()));
					auto kind = not_fail(gram, icon) ? Logo::ring : Logo::fail;

					return sign_type{kind, gram.get_index(), icon.get_index()};
				}

				nik_ce auto define(size_ctype bits, size_ctype value)
				{
					auto & memory = base::memory();
					auto gram     = declare_signifier(bits);
					auto icon     = declare_signified(memory.expand(dmethod.byte_size()));
					auto kind     = not_fail(gram, icon) ? Logo::ring : Logo::fail;

					if (kind == Logo::ring)
					{
						auto sub_dmethod = dmethod.text_right_equip(icon);

						memory[sub_dmethod[DRing::start]] = value;
					}

					return sign_type{kind, gram.get_index(), icon.get_index()};
				}

			// same types:

				template<typename T, typename... Ts>
				nik_ce bool same_types(const T & l, const Ts &... rs)
				{
					return rmethod.same_types
					(
						RRing::dimension, l.get_symbol_index(), rs.get_symbol_index()...
					);
				}

			// add to memory:

				template<typename T, typename... Ts>
				nik_ce void add_to_memory(const T & l, const Ts &... rs)
				{
					const auto & l_dcmethod = dmethod.ctext_right_equip(l.to_icon());

					add_to_methods(l_dcmethod, dmethod.ctext_right_equip(rs.to_icon())...);
				}

				template<typename T, typename... Ts>
				nik_ce void add_to_methods(const T & l, const Ts &... rs)
					{ add_to_positions(l[DRing::start], rs[DRing::start]...); }

				template<typename T, typename... Ts>
				nik_ce void add_to_positions(T l, Ts... rs)
					{ base::memory()[l] = (... + base::cmemory()[rs]); }

			// add to:

				nik_ce void add_to(sign_ctype_ref out, sign_ctype_ref in1, sign_ctype_ref in2)
					{ if (same_types(out, in1, in2)) { add_to_memory(out, in1, in2); } }
	};

	// syntactic sugar:

		template<typename Facade>
		using cring_method = corpus_ring_method<Facade>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// flex:

/***********************************************************************************************************************/

// :

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

