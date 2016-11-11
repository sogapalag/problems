def solution():
    T = int(input())
    for t in range(1, T+1):
        solve(t)
def solve(t):
    s = input()
    i, j = map(int, input().split(' '))
    n = len(s)
    b = s.count('B')
    period = (j-i)//n
    i = (i-1) % n
    j = (j-1) % n
    if i<=j:
        ans = s[i:j+1].count('B')
    else:
        ans = (s[i:]+s[:j+1]).count('B')
    ans += period * b
    print('Case #%d: %d' % (t, ans))
solution()
