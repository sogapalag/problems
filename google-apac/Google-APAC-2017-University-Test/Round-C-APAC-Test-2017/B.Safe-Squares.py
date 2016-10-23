def solution():
    T = int(input())
    for t in range(1, T+1):
        solve(t)
def solve(t):
    r, c, k = map(int, input().split(' '))
    cum = [[1,]*c for i in range(r)]
    for i in range(k):
        x, y = map(int, input().split(' '))
        cum[x][y] = 0
    res = 0
    for i in range(r):
        res += cum[i][0]
    for i in range(1, c):
        res += cum[0][i]
    for i in range(1, r):
        for j in range(1, c):
            if cum[i][j]==1:
                cum[i][j] = 1 + min(cum[i-1][j-1],
                                    cum[i-1][j],
                                    cum[i][j-1])
                res += cum[i][j]
    print('Case #%d: %d' % (t, res))
solution()
