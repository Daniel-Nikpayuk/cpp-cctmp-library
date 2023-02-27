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

// generic assembly grammar:

/***********************************************************************************************************************/

  /*---------------------------------*/  /*---------------------------------*/  /*---------------------------------*/
  /* generic assembly paradigm:      */  /* context-free grammar (CFG):     */  /* nonterminals:                   */
  /*                                 */  /*                                 */  /*                                 */
  /* function-name names...        ; */  /* S -> P;R                        */  /* S - start                       */
  /*                                 */  /* P -> iN                         */  /* P - preamble (signature)        */
  /* label:                        ; */  /* N -> iN      | e                */  /* N - name (denies anonymity)     */
  /* var = operation vars...       ; */  /* R -> BC                         */  /* R - block (at least one)        */
  /* test operation vars...        ; */  /* C -> BC      | e                */  /* C - block (recursive)           */
  /* branch label                  ; */  /* B -> l;Lgi;  | l;rM;            */  /* B - block                       */
  /* var = operation vars...       ; */  /* L -> IJ                         */  /* L - instruction (at least one)  */
  /* ...                           ; */  /* J -> IJ      | e                */  /* J - instruction (recursive)     */
  /* goto label                    ; */  /* I -> T=F;    | !i=F;  | tF;bi;  */  /* I - instruction                 */
  /*                                 */  /* F -> OV                         */  /* F - identifier (at least one)   */
  /* label:                        ; */  /* V -> MV      | e                */  /* V - variable (allows anonymity) */
  /* test operation vars...        ; */  /* T -> i       | .                */  /* T - tag (lvalue variable)       */
  /* branch label                  ; */  /* O -> i       | q                */  /* O - option (rvalue variable)    */
  /* var = operation vars...       ; */  /* M -> i       | q      | _       */  /* M - mark (rvalue variable)      */
  /* ...                           ; */  /*---------------------------------*/  /*---------------------------------*/
  /*                                 */  /* minimized CFG:                  */  /* terminals (tokens):             */
  /* label:                        ; */  /*                                 */  /*                                 */
  /* var = operation vars...       ; */  /* S -> iN;BC                      */  /* l - label                       */
  /* ...                           ; */  /* N -> iN      | e                */  /* t - test                        */
  /* return var                    ; */  /* C -> BC      | e                */  /* b - branch                      */
  /*---------------------------------*/  /* B -> l;IJgi; | l;rM;            */  /* g - goto                        */
                                         /* J -> IJ      | e                */  /* r - return                      */
                                         /* I -> T=OV;   | !i=OV; | tOV;bi; */  /* i - identifier                  */
                                         /* V -> MV      | e                */  /* ! - punctuation                 */
                                         /* T -> i       | .                */  /* q - quote                       */
                                         /* O -> i       | q                */  /* . - anonymous *lvalue*          */
                                         /* M -> i       | q      | _       */  /* _ - anonymous *rvalue*          */
                                         /*---------------------------------*/  /* = - assignment                  */
                                         /* left factored CFG:              */  /* ; - statement (end)             */
                                         /*                                 */  /* e - empty                       */
                                         /* S -> iN;BC                      */  /*---------------------------------*/
                                         /* N -> iN      | e                */
                                         /* C -> BC      | e                */
                                         /* B -> l;E                        */
                                         /* E -> IJgi;   | rM;              */
                                         /* J -> IJ      | e                */
                                         /* I -> T=OV;   | !i=OV; | tOV;bi; */
                                         /* V -> MV      | e                */
                                         /* T -> i       | .                */
                                         /* O -> i       | q                */
                                         /* M -> i       | q      | _       */
                                         /*---------------------------------*/

  /*---------------------------------------------------------------------------------*/
  /* parse table:                                                                    */
  /*                                                                                 */
  /* n\t | i          | .          | !           | t            | q       | l        */
  /*---------------------------------------------------------------------------------*/
  /*   S | S -> iN;BC |            |             |              |         |          */
  /*   N | N -> iN    |            |             |              |         |          */
  /*   C |            |            |             |              |         | C -> BC  */
  /*   B |            |            |             |              |         | B -> l;E */
  /*   E | E -> IJgi; | E -> IJgi; | E -> IJgi;  | E -> IJgi;   |         |          */
  /*   J | J -> IJ    | J -> IJ    | J -> IJ     | J -> IJ      |         |          */
  /*   I | I -> T=OV; | I -> T=OV; | I -> !i=OV; | I -> tOV;bi; |         |          */
  /*   V | V -> MV    |            |             |              | V -> MV |          */
  /*   T | T -> i     | T -> .     |             |              |         |          */
  /*   O | O -> i     |            |             |              | O -> q  |          */
  /*   M | M -> i     |            |             |              | M -> q  |          */
  /*---------------------------------------------------------------------------------*/
  /* n\t | _          | ;          | r           | g            | $       |          */
  /*---------------------------------------------------------------------------------*/
  /*   S |            |            |             |              |         |          */
  /*   N |            | N -> e     |             |              |         |          */
  /*   C |            |            |             |              | C -> e  |          */
  /*   B |            |            |             |              |         |          */
  /*   E |            |            | E -> rM;    |              |         |          */
  /*   J |            |            |             | J -> e       |         |          */
  /*   I |            |            |             |              |         |          */
  /*   V | V -> MV    | V -> e     |             |              |         |          */
  /*   T |            |            |             |              |         |          */
  /*   O |            |            |             |              |         |          */
  /*   M | M -> _     |            |             |              |         |          */
  /*---------------------------------------------------------------------------------*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

