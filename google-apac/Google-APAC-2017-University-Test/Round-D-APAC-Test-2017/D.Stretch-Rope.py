import numpy as np
def solution():
    T = int(input())
    for t in range(T):
        N, M, L = map(int, input().split(' '))
        dp = [np.inf,] * (L+1)
        dp[0] = 0
        for n in range(N):
            A, B, P = map(int, input().split(' '))
            i = A
            d = []
            while L>=i and i<B:
                while d and dp[d[-1]]>=dp[L-i]:
                    d.pop()
                d.append(L-i)
                i += 1
            for j in range(L, -1, -1):
                if j>=B:
                    while d and dp[d[-1]]>=dp[j-B]:
                        d.pop()
                    d.append(j-B)
                if d:
                    dp[j] = min(dp[j], dp[d[0]] + P)
                    if d[0] >= j-A:
                        d.pop(0)
        if dp[L]<=M:
            print('Case #%d: %d' % (t+1, dp[L]))
        else:
            print('Case #%d: IMPOSSIBLE' % (t+1))
solution()
