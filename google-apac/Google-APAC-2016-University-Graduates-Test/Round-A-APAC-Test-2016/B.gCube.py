import numpy as np

def solution():
    T = int(input())
    for t in range(1, T+1):
        solve(t)
# O(n+m)
def solve(t):
    n, m = map(int, input().split(' '))
    a = list(map(int, input().split(' ')))
    print('Case #%d:' % (t))
    la = np.cumsum(np.log(a))
    # \prod a_i = x^#i
    # edge := x
    for i in range(m):
        l, r = map(int, input().split(' '))
        ll = la[l-1] if l else 0
        lr = la[r]
        edge = np.exp((lr-ll)/(r-l+1)) if r!=l else a[l]
        print('%.9f' % (edge))
solution()
