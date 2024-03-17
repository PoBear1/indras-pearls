indras-pearls
=====================

This is the source code to generate all figures in C++/asy; still in progress.

Prelude: How to compile the asy sources
---------------------
If you have asy installed, typing `asy -o example.asy example` into the terminal if you want to compile `example.asy` should be enough.

ch1: The Language of Symmetry
---------------------
`example.asy` - testing asy's drawing capabilities out with a sample program (Box 3, pg. 32). 

`template.asy` - source code for project 1.4

ch2-3: A Delightful Fiction/Double Spirals and Mobius Maps
---------------------
`cmplx_lib/complex_calc.h` - main lib we are going to be using for most of the calculations: contains cline classes and matrix classes that allow for mobius map computations. 

`cmplx_lib/asy_drawing.h` - header file to allow us to draw our figures directly from our calculations in C++

`example.cpp` - an example trying to showcase what we can do; also some tests of the cline class, especially with the mobius function being applied on it with the function $f(z)=\frac{1}{z}$ (i.e. almost inversion) and also showcasing some uses of the draw class.
