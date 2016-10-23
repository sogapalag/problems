def solution():
    T = int(input())
    for t in range(T):
        solve(t)
def solve(t):
    r, c, rs, cs, s = map(int, input().split(' '))
    p, q = map(float, input().split(' '))
    cell, vell = [], []
    for i in range(r):
        line = input().split(' ')
        cell.append(line)
        line = list(map(lambda x:p if x=='A' else q, line))
        vell.append(line)
    visit = [[0,]*c for i in range(r)]
    en = dfs(r, c, rs, cs, s, vell, visit)
    print('Case #%d: %.7f' % (t+1, en))
lx = [[-1, 0],
      [1, 0],
      [0, -1],
      [0, 1]]
def dfs(r, c, rs, cs, s, vell, visit):
    if s==0:
        return 0.0
    res, tmp = 0., 0.
    for i in range(4):
        rnext = rs + lx[i][0]
        cnext = cs + lx[i][1]
        if 0<=rnext<r and 0<=cnext<c:
            tmp = vell[rnext][cnext]
            tmp = tmp * (1-tmp)**visit[rnext][cnext]
            visit[rnext][cnext] += 1
            res = max(res, tmp + dfs(r, c, rnext, cnext, s-1, vell, visit))
            visit[rnext][cnext] -= 1
    return res
solution()
