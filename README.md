
ulam
====

An application to render the
[Ulam spiral](http://en.wikipedia.org/wiki/Ulam_spiral).

    usage:  ./ulam [-b <beg>] [-a | -p] -s <size>
     
    Draw an Ulam spiral into an image that is sent to the standard
    output.
     
    -b <beg>   Start with value <beg> at center.
    -a         Output an ASCII plot.
    -p         Output a PPM image.
    -s <size>  Draw spiral in a square of width <size> cells.
     
    By default, start with the beginning value 1 at the center, and
    decide on the basis of <size> what output format to use. Without
    specification of '-a' or '-p', output as an ASCII plot for
    <size> smaller than 24; otherwise output a PPM image.
     
    If specified, <beg> must be a POSITIVE INTEGER.
    <size> MUST be specified and must be a POSITIVE INTEGER.

Installation
------------

In order to build 'ulam', one needs to have the following installed in a
unix-like system (such as GNU/Linux or Cygwin):
 * make
 * g++
 * convert (part of the ImageMagick toolset)
 * exuberant-ctags

After one uses git to clone this project (or otherwise downloads the files into
a directory called 'ulam'), one may simply change to the 'ulam' directory and
type 'make'.

Sieve of Eratosthenes
---------------------

As a part of the program, I have implemented my own, custom version of the
Sieve of Eratosthenes. It not only efficiently finds all of the primes up to a
limit but also efficiently constructs the prime factorization of every natural
number up to the limit.

The complete prime factorization of every number on the spiral might in
principle be useful for coloring the plot in interesting ways. At the moment, a
basic, two-component coloring scheme is implemented and described below.

Example Output
--------------

For sizes up to 23, the default output is an ASCII plot, in which an at-sign
represents a prime. The following example is for size=23.

    - - - - - - @ - - - - - - - - - - - @ - - - @
    - @ - - - @ - - - - - - - @ - - - - - @ - - -
    @ - - - - - - - - - @ - - - @ - @ - - - @ - @
    - - - @ - - - - - @ - - - - - - - - - @ - @ -
    - - - - @ - - - @ - @ - - - - - - - - - - - -
    - - - - - - - - - - - @ - @ - - - - - @ - - -
    @ - - - @ - @ - - - @ - - - - - - - @ - - - @
    - - - - - - - - - - - @ - @ - - - @ - - - - -
    - - @ - - - @ - @ - - - - - @ - @ - @ - - - -
    - @ - @ - @ - @ - @ - - - @ - - - - - - - @ -
    - - - - - - - - - - @ - @ - @ - - - - - - - -
    - - - - - @ - - - @ - - @ @ - @ - @ - @ - - -
    - - - - - - @ - @ - @ - - - - - - - - - - - -
    - - - - - - - @ - - - @ - - - - - - - - - - -
    @ - @ - - - @ - @ - - - @ - - - @ - @ - - - @
    - - - @ - - - @ - - - - - @ - - - - - @ - @ -
    - - - - - - - - @ - - - - - - - - - - - @ - -
    - - - @ - @ - - - - - @ - - - @ - - - @ - - -
    @ - - - @ - - - - - - - - - - - @ - - - - - -
    - @ - - - - - @ - - - @ - @ - - - - - - - - -
    - - - - - - @ - @ - - - @ - - - - - @ - - - @
    - @ - - - - - - - - - @ - @ - - - - - @ - - -
    - - @ - - - - - - - - - - - @ - @ - - - - - -

For sizes above 23, the default output is a PPM image. The following example is
for size=512.

![512x512UlamSpiral](example-output.png)

Each red pixel is a prime. For every other pixel, the intensity of the green
component of the pixel is proportional to the logarithm of the largest prime
factor in the number corresponding to the pixel.

