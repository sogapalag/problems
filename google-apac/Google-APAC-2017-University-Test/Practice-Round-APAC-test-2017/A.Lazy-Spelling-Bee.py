def solution():
    T = int(input())
    for t in range(1, T+1):
        solve(t)
m = 10**9 + 7
def solve(t):
    w = input()
    n = len(w)
    ans = 1
    for i, e in enumerate(w):
        l = i-1 if i>0 else 0
        r = i+1 if i<n-1 else n-1
        ans *= len(set(w[l:r+1]))
        ans %= m
    print('Case #%d: %d' % (t, ans))
solution()
