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

// generic assembly parser:

/***********************************************************************************************************************/

  /*---------------------------------*/  /*---------------------------------*/  /*---------------------------------*/
  /* generic assembly paradigm:      */  /* terminals (tokens):             */  /* context-free grammar (CFG):     */
  /*                                 */  /*                                 */  /*                                 */
  /* function-name names...        ; */  /* l - label                       */  /* S -> P;R                        */
  /*                                 */  /* t - test                        */  /* P -> iN                         */
  /* label:                        ; */  /* b - branch                      */  /* N -> iN     | e                 */
  /* var = operation vars...       ; */  /* g - goto                        */  /* R -> BC                         */
  /* test operation vars...        ; */  /* r - return                      */  /* C -> BC     | e                 */
  /* branch label                  ; */  /* i - identifier                  */  /* B -> l;Lgi; | l;rM;             */
  /* var = operation vars...       ; */  /* . - anonymous *lvalue*          */  /* L -> IJ                         */
  /* ...                           ; */  /* _ - anonymous *rvalue*          */  /* J -> IJ     | e                 */
  /* goto label                    ; */  /* = - assignment                  */  /* I -> tF;bi; | T=F;              */
  /*                                 */  /* ; - statement (end)             */  /* F -> iV                         */
  /* label:                        ; */  /* e - empty                       */  /* V -> MV     | e                 */
  /* test operation vars...        ; */  /*---------------------------------*/  /* T -> i      | .                 */
  /* branch label                  ; */  /* nonterminals:                   */  /* M -> i      | _                 */
  /* var = operation vars...       ; */  /*                                 */  /*---------------------------------*/
  /* ...                           ; */  /* S - start                       */  /* minimized CFG:                  */
  /*                                 */  /* P - preamble (signature)        */  /*                                 */
  /* label:                        ; */  /* N - name (denies anonymity)     */  /* S -> iN;BC                      */
  /* var = operation vars...       ; */  /* R - block (at least one)        */  /* N -> iN      | e                */
  /* ...                           ; */  /* C - block (recursive)           */  /* C -> BC      | e                */
  /* return var                    ; */  /* B - block                       */  /* B -> l;IJgi; | l;rM;            */
  /*---------------------------------*/  /* L - instruction (at least one)  */  /* J -> IJ      | e                */
  /* left factored CFG:              */  /* J - instruction (recursive)     */  /* I -> tiV;bi; | T=iV;            */
  /*                                 */  /* I - instruction                 */  /* V -> MV      | e                */
  /* S -> iN;BC                      */  /* F - identifier (at least one)   */  /* T -> i       | .                */
  /* N -> iN      | e                */  /* V - variable (allows anonymity) */  /* M -> i       | _                */
  /* C -> BC      | e                */  /* T - tag (lvalue variable)       */  /*---------------------------------*/
  /* B -> l;E                        */  /* M - mark (rvalue variable)      */
  /* E -> IJgi;   | rM;              */  /*---------------------------------*/
  /* J -> IJ      | e                */
  /* I -> tiV;bi; | T=iV;            */
  /* V -> MV      | e                */
  /* T -> i       | .                */
  /* M -> i       | _                */
  /*---------------------------------*/

  /*---------------------------------------------------------------------------------------------------------*/
  /* parse table:                                                                                            */
  /*                                                                                                         */
  /* n\t | i          | .          | t            | l        | _       | ;      | r        | g      | $      */
  /*---------------------------------------------------------------------------------------------------------*/
  /*   S | S -> iN;BC |            |              |          |         |        |          |        |        */
  /*   N | N -> iN    |            |              |          |         | N -> e |          |        |        */
  /*   C |            |            |              | C -> BC  |         |        |          |        | C -> e */
  /*   B |            |            |              | B -> l;E |         |        |          |        |        */
  /*   E | E -> IJgi; | E -> IJgi; | E -> IJgi;   |          |         |        | E -> rM; |        |        */
  /*   J | J -> IJ    | J -> IJ    | J -> IJ      |          |         |        |          | J -> e |        */
  /*   I | I -> T=iV; | I -> T=iV; | I -> tiV;bi; |          |         |        |          |        |        */
  /*   V | V -> MV    |            |              |          | V -> MV | V -> e |          |        |        */
  /*   T | T -> i     | T -> .     |              |          |         |        |          |        |        */
  /*   M | M -> i     |            |              |          | M -> _  |        |          |        |        */
  /*---------------------------------------------------------------------------------------------------------*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

