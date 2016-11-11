def solution():
    T = int(input())
    for t in range(1, T+1):
        solve(t)
def solve(t):
    n, d = map(int, input().split(' '))
    ans = 0
    choi = lambda p, k: p//2+1 if p<=k-1 else (2*(k-1)-p)//2+1
    for k in range(1, n//d+1):
        # valid a* dk <= n <= a*dk + 2*(k-1)
        # print(k, ans)
        a = n//(d*k)
        p = n%(d*k)
        if a<=0 or p > 2*(k-1):
            continue
        ans += choi(p, k)
        if d==1:
            a -= 1
            p = n - a*d*k
            if a<=0 or p > 2*(k-1):
                continue
            ans += choi(p, k)
    print('Case #%d: %d' % (t, ans))
solution()
