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

  /*---------------------------------*/
  /* generic assembly paradigm:      */
  /*                                 */
  /* function-name args...         ; */
  /*                                 */
  /* label:                        ; */
  /* var = operation vars...       ; */
  /* test operation vars...        ; */
  /* branch label                  ; */
  /* var = operation vars...       ; */  /*---------------------------------*/
  /* ...                           ; */  /* context-free grammar (CFG):     */
  /* goto label                    ; */  /*                                 */
  /*                                 */  /* S -> P;R                        */
  /* label:                        ; */  /* P -> iN                         */
  /* test operation vars...        ; */  /* N -> iN      | e                */
  /* branch label                  ; */  /* R -> BC                         */
  /* var = operation vars...       ; */  /* C -> BC      | e                */
  /* ...                           ; */  /* B -> l;Lgi;  | l;rM;            */
  /*                                 */  /* L -> IJ                         */
  /* label:                        ; */  /* J -> IJ      | e                */
  /* var = operation vars...       ; */  /* I -> T=F;    | tF;bi;  | vF;    */
  /* ...                           ; */  /* F -> OV                         */
  /* return var                    ; */  /* V -> MV      | e                */
  /*---------------------------------*/  /* T -> i       | !i      | .      */
  /* nonterminals:                   */  /* O -> i       | q                */
  /*                                 */  /*   -> 0       | 1       | 2      */
  /* S - start                       */  /*   -> 3       | 4       | 5      */
  /* P - preamble (signature)        */  /*   -> 6       | 7                */
  /* N - name (denies anonymity)     */  /* M -> i       | !i               */
  /* R - block (at least one)        */  /*   -> _       | q                */
  /* C - block (recursive)           */  /*---------------------------------*/
  /* B - block                       */  /* minimized CFG:                  */
  /* L - instruction (at least one)  */  /*                                 */
  /* J - instruction (recursive)     */  /* S -> iN;BC                      */
  /* I - instruction                 */  /* N -> iN      | e                */
  /* F - identifier (at least one)   */  /* C -> BC      | e                */
  /* V - variable (allows anonymity) */  /* B -> l;IJgi; | l;rM;            */
  /* T - tag (lvalue variable)       */  /* J -> IJ      | e                */
  /* O - option (rvalue variable)    */  /* I -> T=OV;   | tOV;bi; | vOV;   */
  /* M - mark (rvalue variable)      */  /* V -> MV      | e                */
  /*---------------------------------*/  /* T -> i       | !i      | .      */
  /* terminals (tokens):             */  /* O -> i       | q                */
  /*                                 */  /*   -> 0       | 1       | 2      */
  /* l - label                       */  /*   -> 3       | 4       | 5      */
  /* t - test                        */  /*   -> 6       | 7                */
  /* b - branch                      */  /* M -> i       | !i               */
  /* g - goto                        */  /*   -> _       | q                */
  /* r - return                      */  /*---------------------------------*/
  /* i - identifier                  */  /* left factored CFG:              */
  /* ! - punctuation                 */  /*                                 */
  /* v - void                        */  /* S -> iN;BC                      */
  /* q - quote                       */  /* N -> iN      | e                */
  /* . - anonymous *lvalue*          */  /* C -> BC      | e                */
  /* _ - anonymous *rvalue*          */  /* B -> l;E                        */
  /* 0 - repeat                      */  /* E -> IJgi;   | rM;              */
  /* 1 - map                         */  /* J -> IJ      | e                */
  /* 2 - fold                        */  /* I -> T=OV;   | tOV;bi; | vOV;   */
  /* 3 - find first                  */  /* V -> MV      | e                */
  /* 4 - find all                    */  /* T -> i       | !i      | .      */
  /* 5 - zip (bimap)                 */  /* O -> i       | q                */
  /* 6 - fasten (zip with a carry)   */  /*   -> 0       | 1       | 2      */
  /* 7 - glide (bifold)              */  /*   -> 3       | 4       | 5      */
  /* = - assignment                  */  /*   -> 6       | 7                */
  /* ; - statement (end)             */  /* M -> i       | !i               */
  /* e - empty                       */  /*   -> _       | q                */
  /*---------------------------------*/  /*---------------------------------*/

  /*----------------------------------------------------------------------------------*/
  /* parse table:                                                                     */
  /*                                                                                  */
  /* n\t | i          | !          | .          | t            | v          | q       */
  /*----------------------------------------------------------------------------------*/
  /*   S | S -> iN;BC |            |            |              |            |         */
  /*   N | N -> iN    |            |            |              |            |         */
  /*   C |            |            |            |              |            |         */
  /*   B |            |            |            |              |            |         */
  /*   E | E -> IJgi; | E -> IJgi; | E -> IJgi; | E -> IJgi;   | E -> IJgi; |         */
  /*   J | J -> IJ    | J -> IJ    | J -> IJ    | J -> IJ      | J -> IJ    |         */
  /*   I | I -> T=OV; | I -> T=OV; | I -> T=OV; | I -> tOV;bi; | I -> vOV;  |         */
  /*   V | V -> MV    | V -> MV    |            |              |            | V -> MV */
  /*   T | T -> i     | T -> !i    | T -> .     |              |            |         */
  /*   O | O -> i     |            |            |              |            | O -> q  */
  /*   M | M -> i     | M -> !i    |            |              |            | M -> q  */
  /*----------------------------------------------------------------------------------*/
  /* n\t | _          | l          | ;          | r            | g          | $       */
  /*----------------------------------------------------------------------------------*/
  /*   S |            |            |            |              |            |         */
  /*   N |            |            | N -> e     |              |            |         */
  /*   C |            | C -> BC    |            |              |            | C -> e  */
  /*   B |            | B -> l;E   |            |              |            |         */
  /*   E |            |            |            | E -> rM;     |            |         */
  /*   J |            |            |            |              | J -> e     |         */
  /*   I |            |            |            |              |            |         */
  /*   V | V -> MV    |            | V -> e     |              |            |         */
  /*   T |            |            |            |              |            |         */
  /*   O |            |            |            |              |            |         */
  /*   M | M -> _     |            |            |              |            |         */
  /*----------------------------------------------------------------------------------*/
  /* n\t | 0          | 1          | 2          | 3            | 4          | 5       */
  /*----------------------------------------------------------------------------------*/
  /*   S |            |            |            |              |            |         */
  /*   N |            |            |            |              |            |         */
  /*   C |            |            |            |              |            |         */
  /*   B |            |            |            |              |            |         */
  /*   E |            |            |            |              |            |         */
  /*   J |            |            |            |              |            |         */
  /*   I |            |            |            |              |            |         */
  /*   V |            |            |            |              |            |         */
  /*   T |            |            |            |              |            |         */
  /*   O | O -> 0     | O -> 1     | O -> 2     | O -> 3       | O -> 4     | O -> 5  */
  /*   M |            |            |            |              |            |         */
  /*----------------------------------------------------------------------------------*/
  /* n\t | 6          | 7          |            |              |            |         */
  /*----------------------------------------------------------------------------------*/
  /*   S |            |            |            |              |            |         */
  /*   N |            |            |            |              |            |         */
  /*   C |            |            |            |              |            |         */
  /*   B |            |            |            |              |            |         */
  /*   E |            |            |            |              |            |         */
  /*   J |            |            |            |              |            |         */
  /*   I |            |            |            |              |            |         */
  /*   V |            |            |            |              |            |         */
  /*   T |            |            |            |              |            |         */
  /*   O | O -> 6     | O -> 7     |            |              |            |         */
  /*   M |            |            |            |              |            |         */
  /*----------------------------------------------------------------------------------*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

