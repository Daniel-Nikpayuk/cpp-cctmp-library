# cpp-cctmp-library
-------------------

A C++17 "calculus of constructions" compile time register machine library.

This repository includes two file generators (bash scripts):

i) generate undef macros
ii) generate single source

which allows for the regeneration of their respective files:

i) undef\_macros.hpp
ii) cpp\_cctmp\_library.hpp

The single source file is ideal for use in compiler explorer.

Otherwise the library is broken up into three parts:

a) The backend, which can be thought of the "hardware" simulating these register machines.
b) The fronend, which (will) allow for the translation of cstrings into register machine controllers.
c) Programs to be read as case studies.

Consider the backend to be stable in its overall design, but otherwise experimental as it has not been
rigorously tested.

As for the frontend, it has yet to be implemented. Although the frontend is not strictly necessary,
it is intended to be a user-friendly and concise alternative to manually writing register machine
controllers by hand. I hope to have this portion of the library complete by the end of 2022.

Finally, as for the case study programs, they notably include:

i) The factorial function (more than one version).
ii) The Fibonacci function.
iii) Mergesort.

Notably mergesort is defined to be generic as it allows for arbitrary comparison operators.

As for performance: The library was designed with performance in mind, though as of yet I have not
done any thorough benchmarking. Simple programs such as factorial and fibonacci run under a second
for small values, but as these machines reach their nesting depth limits they do start to slow
down considerably.

Keep in mind, as with many things, this library is to be contextually applied per use case: For example if
you need to sort numbers at compile time it's better to use constexpr arrays, but if you need to sort a small
number of types or mixed objects this implementation might then be preferred.

With that said, sorting a list even of length 200 becomes time consuming:

gcc 11 - 20.12s
clang 13 - 2m4.21s

In any case, that's it for now. I'll update this library on occassion in terms of bug fixes and the frontend,
but you can otherwise consider it to be complete. Thanks.

