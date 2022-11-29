/************************************************************************************************************************
**
** Copyright 2022 Daniel Nikpayuk, Inuit Nunangat, The Inuit Nation
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
  /* branch label                  ; */  /* i - identifier                  */  /* B -> l;Lgi; | l;LrM;            */
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
                                         /* J - instruction (recursive)     */  /* B -> l;LE                       */
                                         /* I - instruction                 */  /* E -> gi;    | rM;               */
                                         /* F - identifier (at least one)   */  /* L -> IJ                         */
                                         /* V - variable (allows anonymity) */  /* J -> IJ     | e                 */
                                         /* T - tag (lvalue variable)       */  /* I -> tF;bi; | T=F;              */
                                         /* M - mark (rvalue variable)      */  /* F -> iV                         */
                                         /*---------------------------------*/  /* V -> MV     | e                 */
                                                                                /* T -> i      | .                 */
                                                                                /* M -> i      | _                 */
                                                                                /*---------------------------------*/

  /*------------------------------------------------------------------------------------------------------------------*/
  /* parse table:                                                                                                     */
  /*                                                                                                                  */
  /* nt\t | l         | t           | b | g        | r        | i         | .         | _       | = | ;      | $      */
  /*------------------------------------------------------------------------------------------------------------------*/
  /*    S |           |             |   |          |          | S -> P;R  |           |         |   |        |        */
  /*    P |           |             |   |          |          | P -> iN   |           |         |   |        |        */
  /*    N |           |             |   |          |          | N -> iN   |           |         |   | N -> e |        */
  /*    R | R -> BC   |             |   |          |          |           |           |         |   |        |        */
  /*    C | C -> BC   |             |   |          |          |           |           |         |   |        | C -> e */
  /*    B | B -> l;LE |             |   |          |          |           |           |         |   |        |        */
  /*    E |           |             |   | E -> gi; | E -> rM; |           |           |         |   |        |        */
  /*    L |           | L -> IJ     |   |          |          | L -> IJ   | L -> IJ   |         |   |        |        */
  /*    J |           | J -> IJ     |   | J -> e   | J -> e   | J -> IJ   | J -> IJ   |         |   |        |        */
  /*    I |           | I -> tF;bi; |   |          |          | I -> T=F; | I -> T=F; |         |   |        |        */
  /*    F |           |             |   |          |          | F -> iV   |           |         |   |        |        */
  /*    V |           |             |   |          |          | V -> MV   |           | V -> MV |   | V -> e |        */
  /*    T |           |             |   |          |          | T -> i    | T -> .    |         |   |        |        */
  /*    M |           |             |   |          |          | M -> i    |           | M -> _  |   |        |        */
  /*------------------------------------------------------------------------------------------------------------------*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

