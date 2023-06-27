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

This project is ongoing.

The last major update to this repo was on June 27th, 2023. The update adds a constexpr
LL(1) parser generator built upon a framework of iterator-like classes and their arrays
(see the scope/relation/graph files). Furthermore, these *constant expression* safe
classes along with the parser generator have been used to reimplement the previously
existing generic assembly language which his the base of the metapiler itself.

The general roadmap from this update is to clean up and extend the parser generator's
capabilities, then use them to extend the generic assembly language to include what
I am calling the *chord progression* paradigm. I will further complete the chord assembly
language by adding the ability to *quote* and thus embed its own sublanguages.

Beyond this, I still need to properly build the error reporting system for these
languages, but before I do the plan is to build two specific modules to test out and
demonstrate the grammatical stability of the chord assembly language itself. The first
module will be *big number arithmetic* (along with some basic number theoretic cryptography).
The second module will be *fast fourier algorithms*, hopefully with some proof of concept
image or sound analysis.

Once these goals are achieved I will release version 1.0 of the metapiler. I expect this
to take at least year. Versioning will be established as single source files supplied with
version release details. Otherwise, the modularized multisource files in the root directory
of this repository should always be considered ongoing (experimental snapshots).

Finally, and as of yet, the documentation and single source folders are empty. The testing folder
is currently an ad-hoc collection of otherwise disorganized tests (and older obsolete
code I intend to bring in and translate at a later date). It is part of the roadmap
to clean this up as proper source test files.

As this project grows and stabilizes, I hope you find it to be of interest, and even maybe some use.

Thank you.

