import numpy as np

def solution():
    T = int(input())
    for t in range(1, T+1):
        solve(t)
# Floyd-Warshall O(V^3+E)
def solve(t):
    n, m = map(int, input().split(' '))
    E = []
    for i in range(m):
        E.append(list(map(int, input().split(' '))))
    dist = [[np.inf,]*n for i in range(n)]
    for i in range(n):
        dist[i][i] = 0
    for e in E:
        dist[e[0]][e[1]] = dist[e[1]][e[0]] = min(dist[e[1]][e[0]], e[2])
    for k in range(n):
        for i in range(n):
            for j in range(n):
                if dist[i][j] > dist[i][k] + dist[k][j]:
                    dist[i][j] = dist[i][k] + dist[k][j]
    print('Case #%d:' % (t))
    # e is inefficient iif there is a shorter path
    for i,e in enumerate(E):
        if dist[e[0]][e[1]] < e[2]:
            print(i)
solution()
