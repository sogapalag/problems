// http://mathforum.org/advanced/robertd/catalan.html
// https://www.geeksforgeeks.org/applications-of-catalan-numbers/
// https://en.wikipedia.org/wiki/Catalan_number
// https://en.wikipedia.org/wiki/Catalan%27s_triangle
//
// grid (0,0) -> (n,n) below paths
// C_{n+1} = \sum_{i=0}^n C_i * C_{n-i}; C_0=1
// C_n = bino(2n, n) / (n+1)
//     = bino(2n, n) - bino(2n, n+1) // reflection method
