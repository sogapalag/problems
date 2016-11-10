import numpy as np
from numpy.linalg import matrix_power as mp

def solution():
    T = int(input())
    for t in range(1, T+1):
        solve(t)
# O(log(10^9))
def solve(t):
    n, x, k, a, b, c = map(int, input().split(' '))
    # Think bitwisely
    # Transform matrix
    pa, pb, pc = a/100, b/100, c/100
    ix = np.array([[pa, pc],
                   [pb+pc, pa+pb]])
    tx = mp(ix, n)
    # p[x_i, k_i]: prob return 1, when bits of x,k is x_i, k_i
    p = [[0, tx[1][0]],
         [(pb+pc)**n, tx[1][1]]]
    ans = 0
    i = 0
    while x>0 or k>0:
        x_i = 0
        if x>0:
            x_i = x % 2
            x >>= 1
        k_i = 0
        if k>0:
            k_i = k % 2
            k >>= 1
        ans += p[x_i][k_i] * 2**i
        i += 1
    print('Case #%d: %.12f' % (t, ans))
solution()
