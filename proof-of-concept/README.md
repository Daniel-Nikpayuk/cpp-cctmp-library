# cpp-cctmp-library
-------------------

A C++17 general purpose library oriented around and built on top of a *metapiler*
paradigm: It offers the ability to translate embedded sublanguages (represented as
constexpr string literals) into constexpr functions. This paradigm allows for
the creation of domain specific languages to ease the creation of domain specific
modules and sublibraries.

This metapiler paradigm is achieved using a combination of constexpr and TMP magic.
Emphasis is on constexpr for reliability and performance, but even when TMP is used,
its design adheres as closely as possible to Type Theory with the intent of keeping
it reasonably type safe. The frontend (lexer/parser) components are constexpr oriented,
referencing The Dragon Book on compiler theory for their implementation. The backend
achieves its translation by making use of a theoretical correspondence between assembly
language and an extension of continuation passing style.

This project is currently proof of concept, with the following roadmap leading to
a version 1.0 release:

a) The major goal for a version 1.0 release is to build two embedded domain specific languages (DSL) which will then be used
to rebuild as much of this library as is reasonable. The idea is for it to be semi-self hosting.

b) The first DSL is call Chord: It is a generic assembly which supports a chord progression paradigm. This chord progression
paradigm offers grammar to create functional operators { repeat, map, fold, find, sift }.

c) The second DSL is a Scheme-like language called Hustle: It is intended to be as close to Scheme as is reasonable given
the differences in their underlying computational models.

d) Both languages will be implemented using a common DSL Engine which supports a common continuation assembly language.

e) Continuation Assembly: This is a metaobject assembly (used to build constexpr functions through continuation machines).
I will be adding markup instructions so that DSL architects can encode documentation into their front end translations.
I will (re)implement my Chord and Hustle langs to do the same, and will provide an initial -O0 backend.

f) Higher Order Functions: The Hustle lang should be able to pass expressions as arguments to function calls.
This becomes a problem relative to the underlying continuation machine type system. This problem will be solved
by adding in new continuation machines to support expression trampolining. Notably, it is the conditional expression
(if pred ante conse) that complicates things.

As such, I will add in machines that compute the predicate function, which then returns a deferral:

A deferral is a pair that holds the branching subroutines as compile time objects, and holds the predicate return
as a constexpr runtime bool value. The thing to note is that the function created to evaluate the expression is guaranteed
to return a single type. Once returned, we check to see if it is a trampolined value: If so we try again and reevaluate,
otherwise we pass the resolved value to the next instruction accordingly.
This works because we're within a larger continuation's scope.

The Hustle lang will need to be tweaked to update this approach.

g) Syntax Tree Exposure:

For the initial purpose of encoding data structures within the continuation assembly, and in particular the intent
of creating a DSL to freely manipulate tuples (while deferring tuple type commitment), a syntax tree IR is required.

The hustle lang is a natural choice to support this, and as such I've decided I will add in grammar to work
with both C++ (imported) types, as well as this syntax tree IR. What this means in the long run is that
the Hustle lang will also need to support the ability to convert between these representations.

h) Add in lexer, structure, and LR(1) generators;
i) add in error messaging.
j) add in unit tests.

At such a point the project's version 1.0 will be done. I intend to leave backend optimizers to others.
As this project grows and stabilizes, I hope you find it to be of interest, and even maybe some use.


[comment]: GCC -fconstexpr-depth=2048


[comment:] Clang -fconstexpr-steps=2097152 (2^21)

Thank you.

