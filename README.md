
ulam
====

An (UNFINISHED!) application to render the
[Ulam spiral](http://en.wikipedia.org/wiki/Ulam_spiral) in various ways.

    usage:  ./ulam [-b <beg>] [-c] [-d | -l | -u] -s <size>
    
    Draw an Ulam spiral into a PPM image that is sent to the
    standard output.
    
    -b <beg>   Start with value <beg> at center.
    -c         Draw clockwise.
    -d         Move first downward.
    -l         Move first to the left.
    -u         Move first upward.
    -s <size>  Draw spiral of width <size> cells.
    
    By default, start with the beginning value 1 at the center, draw
    counter-clockwise, and move first to the right.
    
    If specified, <beg> must be a POSITIVE INTEGER.
    Only ONE of the directions may be specified.
    <size> MUST be specified and must be a POSITIVE INTEGER.

So far, what has been implemented are the command-line interface and the code
that calculates the prime factorization of every natural number that will be
needed to construct the spiral.

Sieve of Eratosthenes
---------------------

As a part of the program, I have implemented my own, custom version of the
Sieve of Eratosthenes. It not only efficiently finds all of the primes up to a
limit but also efficiently constructs the prime factorization of every natural
number up to the limit.

