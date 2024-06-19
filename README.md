indras-pearls
=====================

This is the source code to generate all figures in C++/asy; still in progress.

Prelude: How to compile the asy sources
---------------------
If you have asy installed, typing `asy -o example.asy example` into the terminal if you want to compile `example.asy` as an example should be enough.

ch1: The Language of Symmetry
---------------------
`example.asy` - testing asy's drawing capabilities out with a sample program (Box 3, pg. 32). 

`template.asy` - source code for project 1.4

ch2-3: A Delightful Fiction/Double Spirals and Mobius Maps
---------------------
`cmplx_lib/complex_calc.h` - main lib we are going to be using for most of the calculations: contains `cline` classes and `matrix` functions that allow for mobius map computations. 

`cmplx_lib/asy_drawing.h` - header file to allow us to draw our figures directly from our calculations in C++ into Asymptote; compiling this will then be enough.

`example.cpp` - an example trying to showcase what we can do; also some tests of the cline class, especially with the mobius function being applied on it with the function $f(z)=\frac{1}{z}$ (i.e. almost inversion) and also showcasing some uses of the draw class. 

**Note**: after wrestling with trying to render Schottky groups, significant changes were made to the cline class in order to provide a fully correct version of the transformations. Unfortunately this has meant that the code in `example.cpp` is outdated and canot be used as an example of the cline class.

ch4: The Schottky Dance
---------------------
`schottky.cpp` - code to render the $\frac{\pi}{4}$-Schottky group.

`cmplx_lib/schottky.h` - complete implementation of the schottky fractal for two generators; can be edited (although not without some effort) to generate fractals with more generators.

`./asy/theta-fuchsian.asy`, `./asy/theta-fuchsian.asy.pdf` - rendering of the $\frac{\pi}{4}$-Schottky group.

appendix: Historical memories (`historical_files`)
---------------------
`asy_drawing_historic.h`, `complex_calc_historic.h`, `schottky_historic.cpp` - older versions of the respective files from the time of attempting to get the code working.

`bfs.cpp` - similar to `schottky.cpp` but instead only containing the BFS section of the code.

`example.asy` - similar to `ch4/asy/theta-fuchsian.asy`.
