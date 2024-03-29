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

// context free grammars:

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// parser generator grammar:

/***********************************************************************************************************************/

  /*---------------------------------*/  /*---------------------------------*/  /*---------------------------------*/
  /* terminals (tokens):             */  /* nonterminals:                   */  /* context-free grammar (CFG):     */
  /*                                 */  /*                                 */  /*                                 */
  /*  i - identifier                 */  /* S - start                       */  /* S -> iFD                        */
  /*  a - arrow (right)              */  /* D - declaration (recursive)     */  /* D -> iHD   | e                  */
  /*  m - empty (generated)          */  /* F - declaration (first)         */  /* F -> aMA;B | =IJK               */
  /*  = - equal                      */  /* H - declaration (head)          */  /* H -> aMA;B | =IJK               */
  /*  : - colon                      */  /* B - declaration (body)          */  /* B -> aMA;B | e                  */
  /*  ; - semicolon                  */  /* M - name (dispatch)             */  /*                                 */
  /*  e - empty (generator)          */  /* N - name (recursive)            */  /* M -> TN    | m                  */
  /*---------------------------------*/  /* T - name (token)                */  /*                                 */
                                         /* A - action                      */  /* N -> TN    | e                  */
                                         /* C - call                        */  /* T -> i                          */
                                         /* J - alias (recursive)           */  /* A -> :C    | e                  */
                                         /* I - alias (token)               */  /* C -> i                          */
                                         /* K - alias (end of)              */  /*                                 */
                                         /*---------------------------------*/  /* J -> IJ    | e                  */
                                                                                /* I -> i                          */
                                                                                /* K -> ;                          */
                                                                                /*---------------------------------*/

  /*------------------------------------------------------------------------------------------------*/
  /* parse table:                                                                                   */
  /*                                                                                                */
  /* n\t | i          | ;          | a          | :          | $          | =          | m          */
  /*------------------------------------------------------------------------------------------------*/
  /*   S | S -> iFD   |            |            |            |            |            |            */
  /*   D | D -> iHD   |            |            |            | D -> e     |            |            */
  /*   F |            |            | F -> aMA;B |            |            | F -> =IJK  |            */
  /*   H |            |            | H -> aMA;B |            |            | H -> =IJK  |            */
  /*   B | B -> e     |            | B -> aMA;B |            | B -> e     |            |            */
  /*   M | M -> TN    |            |            |            |            |            | M -> m     */
  /*   N | N -> TN    | N -> e     |            | N -> e     |            |            |            */
  /*   T | T -> i     |            |            |            |            |            |            */
  /*   A |            | A -> e     |            | A -> :C    |            |            |            */
  /*   C | C -> i     |            |            |            |            |            |            */
  /*   J | J -> IJ    | J -> e     |            |            |            |            |            */
  /*   I | I -> i     |            |            |            |            |            |            */
  /*   K |            | K -> ;     |            |            |            |            |            */
  /*------------------------------------------------------------------------------------------------*/

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
  /* var # var                     ; */
  /* test operation vars...        ; */
  /* branch label                  ; */
  /* var = operation vars...       ; */
  /* ...                           ; */
  /* goto label                    ; */
  /*                                 */
  /* label:                        ; */
  /* test operation vars...        ; */
  /* branch label                  ; */
  /* var = operation vars...       ; */
  /* ...                           ; */
  /*                                 */
  /* label:                        ; */
  /* var # var                     ; */
  /* ...                           ; */
  /* return var                    ; */
  /*---------------------------------*/

  /*---------------------------------*/
  /* context-free grammar (CFG):     */
  /*---------------------------------*/
  /* jvalues:                        */
  /*                                 */
  /* J -> i                          */
  /*---------------------------------*/
  /* mvalues:                        */
  /*                                 */
  /* M -> i                          */
  /*---------------------------------*/
  /* lvalues:                        */
  /*                                 */
  /* L -> i       | .                */
  /*---------------------------------*/
  /* rvalues:                        */
  /*                                 */
  /* N -> i                          */
  /* R -> i       | _       | q      */
  /*                                 */
  /* Y -> [       | (                */
  /* Z -> ]       | )                */
  /* Q -> R       | ~                */
  /* W -> @       | *       | R      */
  /* U -> W       | e                */
  /* B -> RX      | e                */
  /* X -> WU      | e                */
  /* D -> +       | -                */
  /*   -> R       | e                */
  /* P -> +\|-    | -\|+             */
  /*   -> R\|Q    | e                */
  /*---------------------------------*/
  /* cvalues:                        */
  /*                                 */
  /* C -> R                          */
  /*   -> 0<U\|B\|B>YD,Z{}           */
  /*   -> 2<B\|B\|B>{}YD,Z           */
  /*   -> 3<U\|B>YD,Z                */
  /*   -> 4<U\|B\|B>YDZYD,Z          */
  /*   -> 1<U\|B\|B>YPZYP,PZ         */
  /*   -> 5<B\|B\|B>YPZYPZYP,PZ      */
  /*   -> 6<B\|B\|B\|B>YPZ{}YPZYP,PZ */
  /*   -> 7<B\|B\|B\|B>{}YPZYP,PZ    */
  /*---------------------------------*/
  /* svalues:                        */
  /*                                 */
  /* S -> NA;TO                      */
  /* A -> iA      | e                */
  /* O -> TO      | e                */
  /* T -> l;E                        */
  /* E -> IHG     | rC;              */
  /* H -> IH      | e                */
  /* G -> gJ;     | rC;              */
  /* I -> LK      | !M=CV;           */
  /*   -> tRV;bJ; | vCV;             */
  /* K -> #C;     | =CV;             */
  /* V -> CV      | !MV     | e      */
  /*---------------------------------*/

  /*---------------------------------*/
  /* nonterminals:                   */
  /*                                 */
  /* A -                             */
  /* B -                             */
  /* C -                             */
  /* D -                             */
  /* E -                             */
  /* G -                             */
  /* H -                             */
  /* I -                             */
  /* J -                             */
  /* K -                             */
  /* L -                             */
  /* M -                             */
  /* N -                             */
  /* O -                             */
  /* P -                             */
  /* Q -                             */
  /* R -                             */
  /* S -                             */
  /* T -                             */
  /* U -                             */
  /* V -                             */
  /* W -                             */
  /* X -                             */
  /* Y -                             */
  /* Z -                             */
  /*---------------------------------*/
  /* terminals (tokens):             */
  /*                                 */
  /*  l - label                      */
  /*  t - test                       */
  /*  b - branch                     */
  /*  g - goto                       */
  /*  r - return                     */
  /*  i - identifier                 */
  /*  ! - punctuation                */
  /*  v - void                       */
  /*  q - quote                      */
  /*  . - anonymous *lvalue*         */
  /*  _ - anonymous *rvalue*         */
  /*  # - assignment                 */
  /*  = - application                */
  /*  ; - statement (end)            */
  /*  0 - repeat                     */
  /*  1 - map                        */
  /*  2 - fold                       */
  /*  3 - find first                 */
  /*  4 - find all                   */
  /*  5 - zip (bimap)                */
  /*  6 - fasten (zip with a carry)  */
  /*  7 - glide (bifold)             */
  /*  < - left angle                 */
  /*  > - right angle                */
  /* \| - bar                        */
  /*  @ - identity                   */
  /*  * - dereference                */
  /*  + - increment                  */
  /*  - - decrement                  */
  /*  ~ - tilde                      */
  /*  [ - left closed                */
  /*  ( - left open                  */
  /*  ] - right closed               */
  /*  ) - right open                 */
  /*  { - left fixed                 */
  /*  } - right fixed                */
  /*  , - comma                      */
  /*  e - empty                      */
  /*---------------------------------*/

  /*--------------------------------------------------------------------------------------------------------------*/
  /* parse table:                                                                                                 */
  /*                                                                                                              */
  /* n\t | i            | _            | q            | .            | !            | t            | v            */
  /*--------------------------------------------------------------------------------------------------------------*/
  /*   A | A -> iA      |              |              |              |              |              |              */
  /*   B | B -> RX      | B -> RX      | B -> RX      |              |              |              |              */
  /*   C | C -> R       | C -> R       | C -> R       |              |              |              |              */
  /*   D | D -> R       | D -> R       | D -> R       |              |              |              |              */
  /*   E | E -> IHG     |              |              | E -> IHG     | E -> IHG     | E -> IHG     | E -> IHG     */
  /*   G |              |              |              |              |              |              |              */
  /*   H | H -> IH      |              |              | H -> IH      | H -> IH      | H -> IH      | H -> IH      */
  /*   I | I -> LK      |              |              | I -> LK      | I -> !M=CV;  | I -> tRV;bJ; | I -> vCV;    */
  /*   J | J -> i       |              |              |              |              |              |              */
  /*   K |              |              |              |              |              |              |              */
  /*   L | L -> i       |              |              | L -> .       |              |              |              */
  /*   M | M -> i       |              |              |              |              |              |              */
  /*   N | N -> i       |              |              |              |              |              |              */
  /*   O |              |              |              |              |              |              |              */
  /*   P | P -> R\|Q    | P -> R\|Q    | P -> R\|Q    |              |              |              |              */
  /*   Q | Q -> R       | Q -> R       | Q -> R       |              |              |              |              */
  /*   R | R -> i       | R -> _       | R -> q       |              |              |              |              */
  /*   S | S -> NA;TO   |              |              |              |              |              |              */
  /*   T |              |              |              |              |              |              |              */
  /*   U | U -> W       | U -> W       | U -> W       |              |              |              |              */
  /*   V | V -> CV      | V -> CV      | V -> CV      |              | V -> !MV     |              |              */
  /*   W | W -> R       | W -> R       | W -> R       |              |              |              |              */
  /*   X | X -> WU      | X -> WU      | X -> WU      |              |              |              |              */
  /*   Y |              |              |              |              |              |              |              */
  /*   Z |              |              |              |              |              |              |              */
  /*--------------------------------------------------------------------------------------------------------------*/
  /* n\t | r            | @            | *            | \|           | >            | ]            | )            */
  /*--------------------------------------------------------------------------------------------------------------*/
  /*   A |              |              |              |              |              |              |              */
  /*   B |              |              |              | B -> e       | B -> e       |              |              */
  /*   C |              |              |              |              |              |              |              */
  /*   D |              |              |              |              |              | D -> e       | D -> e       */
  /*   E | E -> rC;     |              |              |              |              |              |              */
  /*   G | G -> rC;     |              |              |              |              |              |              */
  /*   H | H -> e       |              |              |              |              |              |              */
  /*   I |              |              |              |              |              |              |              */
  /*   J |              |              |              |              |              |              |              */
  /*   K |              |              |              |              |              |              |              */
  /*   L |              |              |              |              |              |              |              */
  /*   M |              |              |              |              |              |              |              */
  /*   N |              |              |              |              |              |              |              */
  /*   O |              |              |              |              |              |              |              */
  /*   P |              |              |              |              |              | P -> e       | P -> e       */
  /*   Q |              |              |              |              |              |              |              */
  /*   R |              |              |              |              |              |              |              */
  /*   S |              |              |              |              |              |              |              */
  /*   T |              |              |              |              |              |              |              */
  /*   U |              | U -> W       | U -> W       | U -> e       | U -> e       |              |              */
  /*   V |              |              |              |              |              |              |              */
  /*   W |              | W -> @       | W -> *       |              |              |              |              */
  /*   X |              | X -> WU      | X -> WU      | X -> e       | X -> e       |              |              */
  /*   Y |              |              |              |              |              |              |              */
  /*   Z |              |              |              |              |              | Z -> ]       | Z -> )       */
  /*--------------------------------------------------------------------------------------------------------------*/
  /* n\t | l            | g            | +            | -            | 0            | 1            | 2            */
  /*--------------------------------------------------------------------------------------------------------------*/
  /*   A |              |              |              |              |              |              |              */
  /*   B |              |              |              |              |              |              |              */
  /*   C |              |              |              |              | C -> 0```    | C -> 1```    | C -> 2```    */
  /*   D |              |              | D -> +       | D -> -       |              |              |              */
  /*   E |              |              |              |              |              |              |              */
  /*   G |              | G -> gJ;     |              |              |              |              |              */
  /*   H |              | H -> e       |              |              |              |              |              */
  /*   I |              |              |              |              |              |              |              */
  /*   J |              |              |              |              |              |              |              */
  /*   K |              |              |              |              |              |              |              */
  /*   L |              |              |              |              |              |              |              */
  /*   M |              |              |              |              |              |              |              */
  /*   N |              |              |              |              |              |              |              */
  /*   O | O -> TO      |              |              |              |              |              |              */
  /*   P |              |              | P -> +\|-    | P -> -\|+    |              |              |              */
  /*   Q |              |              |              |              |              |              |              */
  /*   R |              |              |              |              |              |              |              */
  /*   S |              |              |              |              |              |              |              */
  /*   T | T -> l;E     |              |              |              |              |              |              */
  /*   U |              |              |              |              |              |              |              */
  /*   V |              |              |              |              | V -> CV      | V -> CV      | V -> CV      */
  /*   W |              |              |              |              |              |              |              */
  /*   X |              |              |              |              |              |              |              */
  /*   Y |              |              |              |              |              |              |              */
  /*   Z |              |              |              |              |              |              |              */
  /*--------------------------------------------------------------------------------------------------------------*/
  /* n\t | 3            | 4            | 5            | 6            | 7            | #            | =            */
  /*--------------------------------------------------------------------------------------------------------------*/
  /*   A |              |              |              |              |              |              |              */
  /*   B |              |              |              |              |              |              |              */
  /*   C | C -> 3```    | C -> 4```    | C -> 5```    | C -> 6```    | C -> 7```    |              |              */
  /*   D |              |              |              |              |              |              |              */
  /*   E |              |              |              |              |              |              |              */
  /*   G |              |              |              |              |              |              |              */
  /*   H |              |              |              |              |              |              |              */
  /*   I |              |              |              |              |              |              |              */
  /*   J |              |              |              |              |              |              |              */
  /*   K |              |              |              |              |              | K -> #C;     | K -> =CV;    */
  /*   L |              |              |              |              |              |              |              */
  /*   M |              |              |              |              |              |              |              */
  /*   N |              |              |              |              |              |              |              */
  /*   O |              |              |              |              |              |              |              */
  /*   P |              |              |              |              |              |              |              */
  /*   Q |              |              |              |              |              |              |              */
  /*   R |              |              |              |              |              |              |              */
  /*   S |              |              |              |              |              |              |              */
  /*   T |              |              |              |              |              |              |              */
  /*   U |              |              |              |              |              |              |              */
  /*   V | V -> CV      | V -> CV      | V -> CV      | V -> CV      | V -> CV      |              |              */
  /*   W |              |              |              |              |              |              |              */
  /*   X |              |              |              |              |              |              |              */
  /*   Y |              |              |              |              |              |              |              */
  /*   Z |              |              |              |              |              |              |              */
  /*--------------------------------------------------------------------------------------------------------------*/
  /* n\t | [            | (            | ,            | ~            | ;            | $            |              */
  /*--------------------------------------------------------------------------------------------------------------*/
  /*   A |              |              |              |              | A -> e       |              |              */
  /*   B |              |              |              |              |              |              |              */
  /*   C |              |              |              |              |              |              |              */
  /*   D |              |              | D -> e       |              |              |              |              */
  /*   E |              |              |              |              |              |              |              */
  /*   G |              |              |              |              |              |              |              */
  /*   H |              |              |              |              |              |              |              */
  /*   I |              |              |              |              |              |              |              */
  /*   J |              |              |              |              |              |              |              */
  /*   K |              |              |              |              |              |              |              */
  /*   L |              |              |              |              |              |              |              */
  /*   M |              |              |              |              |              |              |              */
  /*   N |              |              |              |              |              |              |              */
  /*   O |              |              |              |              |              | O -> e       |              */
  /*   P |              |              | P -> e       |              |              |              |              */
  /*   Q |              |              |              | Q -> ~       |              |              |              */
  /*   R |              |              |              |              |              |              |              */
  /*   S |              |              |              |              |              |              |              */
  /*   T |              |              |              |              |              |              |              */
  /*   U |              |              |              |              |              |              |              */
  /*   V |              |              |              |              | V -> e       |              |              */
  /*   W |              |              |              |              |              |              |              */
  /*   X |              |              |              |              |              |              |              */
  /*   Y | Y -> [       | Y -> (       |              |              |              |              |              */
  /*   Z |              |              |              |              |              |              |              */
  /*--------------------------------------------------------------------------------------------------------------*/

	// distribution:

	// C  V  B  D  P  U  X  H  E  I  W  Q  R  L  O  K  Y  Z  G  A  T  M  J  N  S
	// 22 13 10 8  8  7  7  7  6  5  5  4  3  2  2  2  2  2  2  2  1  1  1  1  1

  	// i_q.!tvr@*|>])lg+-01234567#=[(,~;$

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

