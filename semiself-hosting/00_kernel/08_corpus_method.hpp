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

			nik_ces size_type bytes		= 1;

			using record_type		= typename Facade::record_type;
			using signifier_type		= typename record_type::signifier_type;
			using signified_type		= typename record_type::signified_type;

			using rring_method		= resolve_method<signifier_type, rring_method>;
			using dring_method		= resolve_method<signified_type, dring_method>;

			using gram_type			= typename rring_method::gram_type;
			using gram_ctype_ref		= typename rring_method::gram_ctype_ref;

			using icon_type			= typename dring_method::icon_type;
			using icon_ctype_ref		= typename dring_method::icon_ctype_ref;

		protected:

			rring_method global_rring;
			dring_method global_dring;

			nik_ce bool not_fail(gram_ctype_ref g) const { return (g.get_kind() != Logo::fail); }
			nik_ce bool not_fail(icon_ctype_ref i) const { return (i.get_kind() != Logo::fail); }

			nik_ce bool not_fail(gram_ctype_ref g, icon_ctype_ref i) const
				{ return (not_fail(g) && not_fail(i)); }

			nik_ce auto make_rring()
				{ return base::record().signifier()->template equip<rring_method>(); }

			nik_ce auto make_dring()
				{ return base::record().signified()->template equip<dring_method>(); }

			// declare signifier:

				nik_ce void initialize_signifier(gram_ctype_ref gram, size_ctype bits)
				{
					auto local_ring = global_rring.text_right_equip(gram);

					local_ring[RRing::bits] = bits;
				}

				nik_ce auto declare_signifier(size_ctype bits)
				{
					auto gram = global_rring.initialize();

					if (not_fail(gram)) { initialize_signifier(gram, bits); }

					return gram;
				}

			// declare signified:

				nik_ce void initialize_signified(icon_ctype_ref icon)
				{
					auto local_ring = global_dring.text_right_equip(icon);

					local_ring[DRing::bytes] = bytes;
				}

				nik_ce auto declare_signified()
				{
					auto icon = global_dring.initialize(base::memory().expand(bytes));

					if (not_fail(icon)) { initialize_signified(icon); }

					return icon;
				}

		public:

			nik_ce corpus_ring_method() :
				base{}, global_rring{make_rring()}, global_dring{make_dring()} { }

			nik_ce corpus_ring_method(const Facade & f) :
				base{f}, global_rring{make_rring()}, global_dring{make_dring()} { }

			// initialization:

				nik_ce auto declare(size_ctype bits)
				{
					auto gram = declare_signifier(bits);
					auto icon = declare_signified();
					auto kind = not_fail(gram, icon) ? Logo::ring : Logo::fail;

					return sign_type{kind, gram.get_index(), icon.get_index()};
				}

				nik_ce auto define(size_ctype bits, size_ctype value)
				{
					auto gram = declare_signifier(bits);
					auto icon = declare_signified();
					auto kind = not_fail(gram, icon) ? Logo::ring : Logo::fail;

					if (kind == Logo::ring)
					{
						auto local_dring = global_dring.text_right_equip(icon);
						auto & memory    = base::memory();

						memory[local_dring[DRing::start]] = value;
					}

					return sign_type{kind, gram.get_index(), icon.get_index()};
				}

			// arithetic:

				nik_ce bool binary_type_check(sign_ctype_ref out, sign_ctype_ref in1, sign_ctype_ref in2)
				{
					auto out_rring       = global_rring.ctext_right_equip(out.to_gram());
					auto in1_rring       = global_rring.ctext_right_equip(in1.to_gram());
					auto in2_rring       = global_rring.ctext_right_equip(in2.to_gram());

					size_ctype out_name  = out_rring[RRing::name];
					size_ctype in1_name  = in1_rring[RRing::name];
					size_ctype in2_name  = in2_rring[RRing::name];

					size_ctype out_bits  = out_rring[RRing::bits];
					size_ctype in1_bits  = in1_rring[RRing::bits];
					size_ctype in2_bits  = in2_rring[RRing::bits];

					const bool same_name = (out_name == in1_name) && (out_name == in2_name);
					const bool same_bits = (out_bits == in1_bits) && (out_bits == in2_bits);

					return (same_name && same_bits);
				}

				nik_ce void add_to_memory(sign_ctype_ref out, sign_ctype_ref in1, sign_ctype_ref in2)
				{
					auto & memory     = base::memory();
					auto out_dring    = global_dring.text_right_equip(out.to_icon());
					auto in1_dring    = global_dring.text_right_equip(in1.to_icon());
					auto in2_dring    = global_dring.text_right_equip(in2.to_icon());

					const auto value1 = memory[in1_dring[DRing::start]];
					const auto value2 = memory[in2_dring[DRing::start]];

					memory[out_dring[DRing::start]] = value1 + value2;
				}

				nik_ce void add_to(sign_ctype_ref out, sign_ctype_ref in1, sign_ctype_ref in2)
					{ if (binary_type_check(out, in1, in2)) { add_to_memory(out, in1, in2); } }
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

