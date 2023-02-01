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

// context free grammars:

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// generic parser:

/***********************************************************************************************************************/

  /*---------------------------------*/  /*---------------------------------*/  /*---------------------------------*/
  /* generic assembly paradigm:      */  /* terminals (tokens):             */  /* context-free grammar (CFG):     */
  /*                                 */  /*                                 */  /*                                 */
  /* function-name names...        ; */  /* l - label                       */  /* S -> P;R                        */
  /*                                 */  /* t - test                        */  /* P -> iN                         */
  /* label:                        ; */  /* b - branch                      */  /* N -> iN     | e                 */
  /* var = operation vars...       ; */  /* g - goto                        */  /* R -> BC                         */
  /* test operation vars...        ; */  /* r - return                      */  /* C -> BC     | e                 */
  /* branch label                  ; */  /* i - identifier                  */  /* B -> l;Lgi; | l;JrM;            */
  /* var = operation vars...       ; */  /* . - anonymous *lvalue*          */  /* L -> IJ                         */
  /* ...                           ; */  /* _ - anonymous *rvalue*          */  /* J -> IJ     | e                 */
  /* goto label                    ; */  /* = - assignment                  */  /* I -> tF;bi; | T=F;              */
  /*                                 */  /* ; - statement (end)             */  /* F -> iV                         */
  /* label:                        ; */  /* e - empty                       */  /* V -> MV     | e                 */
  /* test operation vars...        ; */  /*---------------------------------*/  /* T -> i      | .                 */
  /* branch label                  ; */  /* nonterminals:                   */  /* M -> i      | _                 */
  /* var = operation vars...       ; */  /*                                 */  /*---------------------------------*/
  /* ...                           ; */  /* S - start                       */  /* left factored CFG:              */
  /*                                 */  /* P - preamble (signature)        */  /*                                 */
  /* label:                        ; */  /* N - name (denies anonymity)     */  /* S -> P;R                        */
  /* var = operation vars...       ; */  /* R - block (at least one)        */  /* P -> iN                         */
  /* ...                           ; */  /* C - block (recursive)           */  /* N -> iN     | e                 */
  /* return var                    ; */  /* B - block                       */  /* R -> BC                         */
  /*---------------------------------*/  /* L - instruction (at least one)  */  /* C -> BC     | e                 */
                                         /* J - instruction (recursive)     */  /* B -> l;E                        */
                                         /* I - instruction                 */  /* E -> Lgi;   | JrM;              */
                                         /* F - identifier (at least one)   */  /* L -> IJ                         */
                                         /* V - variable (allows anonymity) */  /* J -> IJ     | e                 */
                                         /* T - tag (lvalue variable)       */  /* I -> tF;bi; | T=F;              */
                                         /* M - mark (rvalue variable)      */  /* F -> iV                         */
                                         /*---------------------------------*/  /* V -> MV     | e                 */
                                                                                /* T -> i      | .                 */
                                                                                /* M -> i      | _                 */
                                                                                /*---------------------------------*/

      /*--------------------------------------------------------------------------------------------------------*/
      /* parse table:                                                                                           */
      /*                                                                                                        */
      /* n\t | l         | t           | g      | r         | i         | .         | _       | ;      | $      */
      /*--------------------------------------------------------------------------------------------------------*/
      /*   S |           |             |        |           | S -> P;R  |           |         |        |        */
      /*   P |           |             |        |           | P -> iN   |           |         |        |        */
      /*   N |           |             |        |           | N -> iN   |           |         | N -> e |        */
      /*   R | R -> BC   |             |        |           |           |           |         |        |        */
      /*   C | C -> BC   |             |        |           |           |           |         |        | C -> e */
      /*   B | B -> l;E  |             |        |           |           |           |         |        |        */
      /*   E |           | E -> Lgi    |        | E -> JrM; | E -> Lgi  | E -> Lgi  |         |        |        */
      /*   L |           | L -> IJ     |        |           | L -> IJ   | L -> IJ   |         |        |        */
      /*   J |           | J -> IJ     | J -> e | J -> e    | J -> IJ   | J -> IJ   |         |        |        */
      /*   I |           | I -> tF;bi; |        |           | I -> T=F; | I -> T=F; |         |        |        */
      /*   F |           |             |        |           | F -> iV   |           |         |        |        */
      /*   V |           |             |        |           | V -> MV   |           | V -> MV | V -> e |        */
      /*   T |           |             |        |           | T -> i    | T -> .    |         |        |        */
      /*   M |           |             |        |           | M -> i    |           | M -> _  |        |        */
      /*--------------------------------------------------------------------------------------------------------*/

/***********************************************************************************************************************/

      /*--------------------------------------------------------------------------------------------------------*/
      /* parse table:                                                                                           */
      /*                                                                                                        */
      /* n\t | l         | t           | g      | r         | i         | .         | _       | ;      | $      */
      /*--------------------------------------------------------------------------------------------------------*/
      /*   S |           |             |        |           | S -> P;R  |           |         |        |        */
      /*   P |           |             |        |           | P -> iN   |           |         |        |        */
      /*   N |           |             |        |           | N -> iN   |           |         | N -> e |        */
      /*   R | R -> BC   |             |        |           |           |           |         |        |        */
      /*   C | C -> BC   |             |        |           |           |           |         |        | C -> e */
      /*   B | B -> l;E  |             |        |           |           |           |         |        |        */
      /*   E |           | E -> Lgi    |        | E -> JrM; | E -> Lgi  | E -> Lgi  |         |        |        */
      /*   L |           | L -> IJ     |        |           | L -> IJ   | L -> IJ   |         |        |        */
      /*   J |           | J -> IJ     | J -> e | J -> e    | J -> IJ   | J -> IJ   |         |        |        */
      /*   I |           | I -> tF;bi; |        |           | I -> T=F; | I -> T=F; |         |        |        */
      /*   F |           |             |        |           | F -> iV   |           |         |        |        */
      /*   V |           |             |        |           | V -> MV   |           | V -> MV | V -> e |        */
      /*   T |           |             |        |           | T -> i    | T -> .    |         |        |        */
      /*   M |           |             |        |           | M -> i    |           | M -> _  |        |        */
      /*--------------------------------------------------------------------------------------------------------*/

/***********************************************************************************************************************/

	// parsing the string should be done in two rounds:

		// The first to collect memory allocation optimizers
		// such as block, max line, max entry, and distinct identifiers.
		// (if we're going to commit an extra parse cycle, we might as well
		//  collect as much relevant optimizing info as possible here)

		// the second round then builds the table of contents.

		// a line is an array of two arrays: begin entries, and end entries.
		// a block is an array of lines.
		// a table of contents is an array of blocks.

		// we can get the toc size (number of blocks) right away from the source.
		// if we want variable size blocks (numbers of lines) we have to statically build them first,
		// then cast those arrays as pointers.

	// lexemes should hold enough info for the parser to:

	// 1) build an error report.
	// 2) build a table of contents (syntax tree), referencing the given lexemes;
	//    referencing lines and blocks. Specific lexemes will want to reference
	//    variable and label assigned values.
	// 3) build a variable lookup table.
	// 4) build a label lookup table.
	// 5) parse according to the tokens (and thus the context free grammar) to validate the source code.
	// 6) Hold symbolic type info to determine dependencies/errors.

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

