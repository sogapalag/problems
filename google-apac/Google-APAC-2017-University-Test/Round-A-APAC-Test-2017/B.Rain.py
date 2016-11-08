import heapq
def solution():
    T = int(input())
    for t in range(1, T+1):
        solve(t)
xx = [0, 1, 0, -1]
yy = [1, 0, -1, 0]
def solve(t):
    r, c = map(int, input().split(' '))
    h = []
    for i in range(r):
        h.append(list(map(int, input().split(' '))))
    measured = [[False,]*c for i in range(r)]
    p = [[0,]*c for i in range(r)]
    board = []
    for i in range(r):
        for j in range(c):
            if i==0 or i==r-1 or j==0 or j==c-1:
                measured[i][j] = True
                heapq.heappush(board, (h[i][j], i, j))
    while board:
        lowest, i, j = heapq.heappop(board)
        for k in range(4):
            ii = i + xx[k]
            jj = j + yy[k]
            if 0<=ii<r and 0<=jj<c and not measured[ii][jj]:
                height = max(lowest, h[ii][jj])
                p[ii][jj] = height - h[ii][jj]
                measured[ii][jj] = True
                heapq.heappush(board, (height, ii, jj))
    total = 0
    for i in range(r):
        for j in range(c):
            total += p[i][j]
    print('Case #%d: %d' % (t, total))
solution()


