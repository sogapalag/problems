def solution():
    T = int(input())
    for t in range(1, T+1):
        solve(t)
def solve(t):
    l, r = map(int, input().split(' '))
    s = min(l, r)
    s = s*(s+1)/2
    print('Case #%d: %d' % (t, s))
solution()
