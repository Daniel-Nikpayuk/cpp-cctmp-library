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

// capture:

/***********************************************************************************************************************/

	// (define (sq x) (* x x))
	// (sq 2)

	// 1. append sq to args
	// 2. cons_f controller
	// 3. assign as sq

	// 4. call apply on sq
	// 5. push 2 to back of context
	// 6. call sq, pass context size to determine arg0 (x).

/***********************************************************************************************************************/

	// (define (sum-of-sq x y) (+ (sq x) (sq y)))
	// (sum-of-sq 2 3)

	//  . call apply on sum-of-sq
	//  . push 2 then 3 to back of context
	//  . call sum-of-sq, pass context size to determine arg0, arg1.

	//  . when we call sum-of-sq, we pass |context| x y
	//  . by calling sum-of-sq we are calling apply on its body definition.
	//  . we call apply on sq, hence our local context becomes ||context| x y|
	//  . we push x to the back and call sq
	//  . we call square with input ||context| x y| x

	//  . context size is always determined when we first call apply.

	//  . we get back the value of (sq x) and push it to the back getting ||context| x y| (sq x)
	//  . we call apply on sq, our local context becomes |||context| x y| (sq x)|
	//  . we push y to the back and call sq
	//  . we call square with input |||context| x y| (sq x)| y

	//  . we get back the value of (sq y) and push it to the back getting ||context| x y| (sq x) (sq y)
	//  . we call add which is primitive, thus drop ||context x y| and apply add to (sq x) (sq y) values.

/***********************************************************************************************************************/

	// (define (sq x) (* x x))
	// (define (sum-of-sq x y) (+ (sq x) (sq y)))
	// (sum-of-sq 2 3)

		// evaluation showing variadic pack:

			// apply (sum-of-sq):
			// 1. |Context...|
			// 2. |Context...| 2
			// 3. |Context...| 2 3
				// apply (+ (sq x) (sq y)):
				// A. ||Context...| 2 3|
					// apply (sq x):
					// a. ||Context...| 2 3|
					// b. ||Context...| 2 3| 2
						// apply (* x x):
						// i.   |||Context...| 2 3| 2|
						// ii.  |||Context...| 2 3| 2| 2
						// iii. |||Context...| 2 3| 2| 2 2
						// iv.  (* 2 2)
						// v.   4
				// B. ||Context...| 2 3| 4
					// apply (sq y):
					// a. |||Context...| 2 3| 4|
					// b. |||Context...| 2 3| 4| 3
						// apply (* x x):
						// i.   ||||Context...| 2 3| 4| 3|
						// ii.  ||||Context...| 2 3| 4| 3| 3
						// iii. ||||Context...| 2 3| 4| 3| 3 3
						// iv.  (* 3 3)
						// v.   9
				// C. ||Context...| 2 3| 4 9
				// D. (+ 4 9)
				// E. 13

/***********************************************************************************************************************/

	// (define (sq x) (* x x))
	// (define (sum-of-sq x y) (+ (sq x) (sq y)))
	// (sum-of-sq 2 3)

		// evaluation showing variadic pack:

			// apply (sum-of-sq):					// 1. when we create apply, we extend the context
			// 1. |Context...|					// with the args being applied.
			// 2. |Context...| 2
			// 3. |Context...| 2 3					// 3. notice we technically drop the baggage context
				// apply (+ (sq x) (sq y)):			// when we call, except there isn't any here.
				// A. ||Context...| 2 3|
					// apply (sq x):			// a. when we call *apply* itself we pass the current
					// a. ||Context...| 2 3|		// context which includes outer (nested) args.
					// b. ||Context...| 2 3| 2
					// c.  |Context...| 2			// c. we drop the baggage context when
						// apply (* x x):		// calling any functions of interest within
						// i.   ||Context...| 2|	// the ongoing application.
						// ii.  ||Context...| 2| 2
						// iii. ||Context...| 2| 2 2
						// iv.  (* 2 2)			// iv. for atomic functions, we drop all
						// v.   4			// context as the called function wouldn't
				// B. ||Context...| 2 3| 4			// know what to do with it.
					// apply (sq y):
					// a. |||Context...| 2 3| 4|
					// b. |||Context...| 2 3| 4| 3
					// c.   |Context...| 3
						// apply (* x x):		// summary: *apply* is a meta function,
						// i.   ||Context...| 3|	// it takes the current context allowing
						// ii.  ||Context...| 3| 3	// said context to grow.
						// iii. ||Context...| 3| 3 3
						// iv.  (* 3 3)			// internal calls drop any context that isn't
						// v.   9			// required. for atomic functions that means
				// C. ||Context...| 2 3| 4 9			// everything but the args. for compound functions
				// D. (+ 4 9)					// it means any context which didn't exist
				// E. 13					// at the location of the function definition.

/***********************************************************************************************************************/

	// when we define a compound function in Scheme, we store three values:

		// (arg-list, body, env)

	// where env is a snapshot of the extended (cons'ed) env
	// by adding a frame containing bindings for new definitions.

	// we translate this triple here as:

		// (arity, instrs)

	// where arity is the arg size, instrs is actually the location in the controller where this subroutine starts.
	// we don't require an extended env because we don't define/assign values within { argpose, subpose, curry }.
	// we do (currently will) require a temporary arg list for argpose to reference bindings.

	// when we call a compound function in Scheme, we bind the arg-list with the values being applied
	// and temporarily cons it to the env within the triple. We then evaluate the body as expression passing
	// the temporary env.

	// when we define a function in chord, we can hard code the argument indices as being offset by the context.
	// This way we're calling the same functione each time. The operators { argpose, subpose, curry } don't
	// naturally lend themselves to recusive definitions given their intent. To prevent any such complications,
	// the chord language does not allow it.

/***********************************************************************************************************************/

	// in Scheme, internal recursion is problematic.

	// One possible way to solve this is if we define all values before any
	// function definitions, we should then be able to guarantee internal recursion
	// when passing unrefined context.

	// Another possibility is to restrict recursion to functions which are self contained,
	// they would then have no variable capture. We could even parse its definition and encode
	// it as an entirely separate cpp-scheme function.

	// Finally, as we read through the definition, we can create a variable capture list,
	// so that every time we call the function we can recreate its capture each time.
	// this would remove auxiliary context which would otherwise mess with the type system
	// since calling with different types means calling a different function altogether.

/***********************************************************************************************************************/

	// sq        # argpose[] x : multiply x x
	// sum_of_sq # subpose[]   : add sq sq
	// twice     # curry[c2] x : multiply c2 x

/***********************************************************************************************************************/

	// twice          # curry[c2] : multiply c2
	// n_plus         # curry[n]  : add n
	// n_times        # curry[n]  : multiply n
	// twice_plus_n   # subpose[] : n_plus twice
	// n_times_plus_n # subpose[] : n_plus n_times

		// twice          x c2   : multiply c2 x
		// n_plus         x n    : add n x
		// n_times        x n    : multiply n x
		// twice_plus_n   x c2 n : n_plus (twice x c2) n
		// n_times_plus_n x n    : n_plus (n_times x n) n

		// twice          (x, 0), (c2, 1)
		// n_plus         (x, 0), (n , 1)
		// n_times        (x, 0), (n , 1)
		// twice_plus_n   (x, 0), (c2, 1), (n, 2)
		// n_times_plus_n (x, 0), (n , 1) (do we check against redundancy and remove?)

/***********************************************************************************************************************/

	// function application as a meta-function isn't intended to be recursive the way functions are.
	// this means we can pass full context to applications, even when those applications are called within
	// other applications. It's the compound function call itself that requires minimal context (variable capture).

	// this is to say: each constructed function application is intended to be unique.

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// scheme:

/***********************************************************************************************************************/

	// recursive call:

		// (define (f0 ...)						// line 0
		//  (define (f1 ...)						// line 1
		//   ...
		//    (define (fk ...)						// line k
		//     ...
		//      (define (fn-1 ...)					// line n-1
		//       (define (fn ...) ... (fk ...) ...))...)		// line n
		//
		//    (fk ...)...))
		//
		// ...
		//
		// (f0 ...)

	// 1. If a function is defined at a given nested context, we can assume it will be called at that nesting level.
	// 2. A defined function cannot be called from an external nesting level as it does not exist.
	// 3. If a function is called from an internal nesting level, it is a recursive call.

	// When calling fk within fn, we first look for fk in the existing
	// captured variables. If not there, we add it relative to fn1.
	// To determine its index we then search fn-1. If there, fine.
	// Otherwise we add it to fn1 relative to fn2. This way
	// the capture propogates until we arrive back at fk itself.

	// But if fk+1 is defined within fk, it is in practice expected
	// to be called within fk, and so now fk requires fk+1 and
	// fk+1 requires fk ?

	// In this case it's a recursive call, which doesn't require
	// a variable on the stack, it only needs reference the compound
	// function which is known by its registry?

/***********************************************************************************************************************/

	// variable capture:

		// (define (f0 ...)						// line 0
		//  (define (f1 ...)						// line 1
		//   ...
		//    (define (fk ...)						// line k
		//      (define (v ...))					// line k+1
		//       ...
		//        (define (fn-1 ...)					// line n-1
		//         (define (fn ...) ... (... v ...) ...))...)		// line n
		//
		//    (fk ...)...))
		//
		// ...
		//
		// (f0 ...)

	// 1. If a function is defined at a given nested context, we can assume it will be called at that nesting level.
	// 2. When a function is called, we must sift and pass the required environment (variable capture).
	// 3. When we index a variable, we first check the current function definition's bindings, then its arg list.
	//    Otherwise we add it to the function definition's environment, indexing it accordingly.
	//    As the environment of this function definition is updated, any call to the function must also be updated
	//    to pass the captured variable. Thus, this updated environment requires us to propogate further updates
	//    across the function definition's external nesting levels.
	// 4. If we reach the top nesting level without a match, we then check the registered lookup functions.

	// How best to do this without performing the actual propogation? What if it's a lookup variable,
	// in which case optimizing to call the lookup directly would be preferred.

	// It seems I have to first search the compound registry to figure out if it's a compound variable or a lookup
	// or an error. If it's an error, add to the error message and return. If it's a lookup I can optimize
	// for it there. Otherwise I need to propogate the variable upward.

	// It's potentially expensive processing.

/***********************************************************************************************************************/

