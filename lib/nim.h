// http://web.mit.edu/sp.268/www/nim.pdf
// http://www.math.ucla.edu/~tom/Game_Theory/comb.pdf
// https://www.topcoder.com/community/competitive-programming/tutorials/algorithm-games/
// Winning ways for your mathematical plays by Elwyn R. Berlekamp, John H. Conway, Richard K. Guy
// https://en.wikipedia.org/wiki/Sprague%E2%80%93Grundy_theorem
//
//
// for n-piles, option: take exactly one pile remove >0 elements
//  thm,  ^ x_i = 0 iff losing.
//
//  g(x) = mex( g(y): y\in F(x) );
//
//  S-G thm, compose games, g(X) = ^ g_i(X_i)
