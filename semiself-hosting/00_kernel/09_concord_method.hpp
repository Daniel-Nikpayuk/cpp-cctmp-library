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

// concord method:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// ring:

/***********************************************************************************************************************/

// immutable:

	template<typename Facade>
	class concord_ring_cmethod : public Facade
	{
		public:

			using base			= Facade;
			using model_type		= typename Facade::model_type;

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

		protected:

			using symbol_cmethod_type	= typename model_type::symbol_cmethod_type;
			using record_cmethod_type	= typename model_type::record_cmethod_type;

			using symbol_model_type		= typename model_type::symbol_type::base;
			using image_cmethod_type	= typename symbol_model_type::image_cmethod_type;

			symbol_cmethod_type symbol_cmethod;
			record_cmethod_type record_cmethod;

			image_cmethod_type image_cmethod;

		public:

			nik_ce concord_ring_cmethod() :
				base{}, symbol_cmethod{}, record_cmethod{}, image_cmethod{} { }

			nik_ce concord_ring_cmethod(const Facade & f) :

				base{f},
				symbol_cmethod{symbol_cequip()},
				record_cmethod{record_cequip()},
				image_cmethod{image_cequip()}
				{ }

			// symbol:

				nik_ce auto symbol_cequip() { return base::model->symbol_cequip(); }

			// record:

				nik_ce auto record_cequip() { return base::model->record_cequip(); }

			// image:

				nik_ce auto image_cequip() { return base::csymbol().image_cequip(); }
	};

	// syntactic sugar:

		template<typename Facade>
		using cring_cmethod = concord_ring_cmethod<Facade>;

/***********************************************************************************************************************/

// mutable:

	template<typename Facade>
	class concord_ring_method : public concord_ring_cmethod<Facade>
	{
		public:

			using base			= concord_ring_cmethod<Facade>;
			using model_type		= typename base::model_type;

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

			using sign_type			= sign<size_type>;
			using sign_ctype_ref		= typename alias<sign_type>::ctype_ref;

		protected:

			using symbol_method_type	= typename model_type::symbol_method_type;
			using record_method_type	= typename model_type::record_method_type;

			using symbol_model_type		= typename model_type::symbol_type::base;
			using image_method_type		= typename symbol_model_type::image_method_type;

			symbol_method_type symbol_method;
			record_method_type record_method;

			image_method_type image_method;

		public:

			nik_ce concord_ring_method() :
				base{}, symbol_method{}, record_method{}, image_method{} { }

			nik_ce concord_ring_method(const Facade & f) :

				base{f},
				symbol_method{symbol_equip()},
				record_method{record_equip()},
				image_method{image_equip()}
				{ }

			// symbol:

				nik_ce auto symbol_equip() { return base::model->symbol_equip(); }

			// record:

				nik_ce auto record_equip() { return base::model->record_equip(); }

			// image:

				nik_ce auto image_equip() { return base::symbol().image_equip(); }

			// initialization:

				nik_ce auto declare(size_ctype bytes)
				{
					size_ctype offset = base::image_cmethod.byte_size();

					return symbol_method.declare(bytes, record_method.expand(offset));
				}

				nik_ce auto define(size_ctype bytes, size_ctype value)
				{
					auto sign = declare(bytes);

					if (sign.kind() == Gram::ringN)
					{
									// image_start ? index instead of sign ?
						auto image_submethod = base::image_cmethod.
										sign_to_text_cequip(sign.index());

						record_method[image_submethod[IRing::start]] = value;
					}

					return sign;
				}

			// add to record:

				template<typename T, typename... Ts>
				nik_ce void add_to_record(const T & l, const Ts &... rs)
				{
					const auto & l_image_cmethod = base::image_cmethod.
										sign_to_text_cequip(l.index());

					add_to_methods(l_image_cmethod,
						base::image_cmethod.sign_to_text_cequip(rs.index())...);
				}

				template<typename T, typename... Ts>
				nik_ce void add_to_methods(const T & l, const Ts &... rs)
					{ add_to_positions(l[IRing::start], rs[IRing::start]...); }

				template<typename T, typename... Ts>
				nik_ce void add_to_positions(T l, Ts... rs)
					{ record_method[l] = (... + base::record_cmethod[rs]); }

			// add to:

				nik_ce void add_to(sign_ctype_ref out, sign_ctype_ref in1, sign_ctype_ref in2)
				{
					if (symbol_method.same_types(out, in1, in2))
						{ add_to_record(out, in1, in2); }
				}
	};

	// syntactic sugar:

		template<typename Facade>
		using cring_method = concord_ring_method<Facade>;

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

