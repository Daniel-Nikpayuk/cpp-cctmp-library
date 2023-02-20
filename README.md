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

As of February 20th, 2023 the general roadmap is to clean up what is currently
*proof of concept* code for a version 1.0 release of the metapiler in the Spring.
As of yet, the documentation and single source folders are empty. The testing folder
is currently an ad-hoc collection of otherwise disorganized tests (and older obsolete
code I intend to bring in and translate at a later date). It is part of the roadmap
to clean this up as proper source test files.

Versioning will be established as single source files supplied with version release details.
Otherwise, the modularized multisource files in the root directory of this repository should
always be considered ongoing (experimental snapshots).

As this project grows and stabilizes, I hope you find it to be of interest, and even maybe some use.

Thank you.

