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
			using model_type		= typename Facade::model_type;

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

		protected:

			using rcmethod_type		= typename model_type::rcmethod_type;
			using mcmethod_type		= typename model_type::mcmethod_type;

			using record_model_type		= typename model_type::record_type::base;
			using dcmethod_type		= typename record_model_type::dcmethod_type;

			rcmethod_type rcmethod;
			mcmethod_type mcmethod;

			dcmethod_type dcmethod;

		public:

			nik_ce corpus_ring_cmethod() : base{}, rcmethod{}, mcmethod{}, dcmethod{} { }
			nik_ce corpus_ring_cmethod(const Facade & f) :

				base{f},
				rcmethod{record_cequip()},
				mcmethod{memory_cequip()},
				dcmethod{signified_cequip()}
				{ }

			// record:

				nik_ce auto record_cequip() { return base::model->record_cequip(); }

			// memory:

				nik_ce auto memory_cequip() { return base::model->memory_cequip(); }

			// signified:

				nik_ce auto signified_cequip() { return base::crecord().signified_cequip(); }
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
			using model_type		= typename base::model_type;

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

			using sign_type			= sign<size_type>;
			using sign_ctype_ref		= typename alias<sign_type>::ctype_ref;

			using gram_type			= typename sign_type::gram_type;
			using gram_ctype_ref		= typename alias<gram_type>::ctype_ref;

			using icon_type			= typename sign_type::icon_type;
			using icon_ctype_ref		= typename alias<icon_type>::ctype_ref;

		protected:

			using rmethod_type		= typename model_type::rmethod_type;
			using mmethod_type		= typename model_type::mmethod_type;

			using record_model_type		= typename model_type::record_type::base;
			using dmethod_type		= typename record_model_type::dmethod_type;

			rmethod_type rmethod;
			mmethod_type mmethod;

			dmethod_type dmethod;

		public:

			nik_ce corpus_ring_method() : base{}, rmethod{}, mmethod{}, dmethod{} { }
			nik_ce corpus_ring_method(const Facade & f) :

				base{f},
				rmethod{record_equip()},
				mmethod{memory_equip()},
				dmethod{signified_equip()}
				{ }

			// record:

				nik_ce auto record_equip() { return base::model->record_equip(); }

			// memory:

				nik_ce auto memory_equip() { return base::model->memory_equip(); }

			// signified:

				nik_ce auto signified_equip() { return base::record().signified_equip(); }

			// initialization:

				nik_ce auto declare(size_ctype bits)
				{
					size_ctype offset = base::dcmethod.byte_size();

					return rmethod.declare(bits, mmethod.expand(offset));
				}

				nik_ce auto define(size_ctype bits, size_ctype value)
				{
					auto sign = declare(bits);

					if (sign.kind() == Logo::ring)
					{
									// signified_start ? index instead of icon ?
						auto sub_dmethod = dmethod.icon_to_text_equip(sign.to_icon());

						mmethod[sub_dmethod[DRing::start]] = value;
					}

					return sign;
				}

			// add to memory:

				template<typename T, typename... Ts>
				nik_ce void add_to_memory(const T & l, const Ts &... rs)
				{
					const auto & l_dcmethod = dmethod.icon_to_ctext_equip(l.to_icon());

					add_to_methods(l_dcmethod, dmethod.icon_to_ctext_equip(rs.to_icon())...);
				}

				template<typename T, typename... Ts>
				nik_ce void add_to_methods(const T & l, const Ts &... rs)
					{ add_to_positions(l[DRing::start], rs[DRing::start]...); }

				template<typename T, typename... Ts>
				nik_ce void add_to_positions(T l, Ts... rs)
					{ mmethod[l] = (... + base::mcmethod[rs]); }

			// add to:

				nik_ce void add_to(sign_ctype_ref out, sign_ctype_ref in1, sign_ctype_ref in2)
					{ if (rmethod.same_types(out, in1, in2)) { add_to_memory(out, in1, in2); } }
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

