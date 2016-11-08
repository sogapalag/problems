def solution():
    T = int(input())
    for t in range(1, T+1):
        solve(t)
# hint: left chunks has all smallest number 1~i
def solve(t):
    n, m = map(int, input().split(' '))
    fac = [1]
    for i in range(1, n+1):
        fac.append(i*fac[-1] % m)
    # number of single trunk with length i
    chunk_of_length = [0,]*(n+1)
    for i in range(1, n+1):
        chunk_of_length[i] = fac[i]
        for j in range(1, i):
            # illegal(splited), first chunk_length is j
            chunk_of_length[i] += (-fac[j]*chunk_of_length[i-j])%m
            chunk_of_length[i] %= m
    # g[i][j]: length i, sum of [f(p)]^j
    g = [[1, 0, 0]]
    for i in range(1, n+1):
        g.append([fac[i], 0, 0])
        for j in range(1, i+1):
            # first chunk_length is j
            g[i][1] += (g[i-j][0] + g[i-j][1])%m * chunk_of_length[j]%m
            g[i][2] += ((g[i-j][0] + 2*g[i-j][1] + g[i-j][2])%m *
                        chunk_of_length[j])%m
            g[i][1] %= m
            g[i][2] %= m
    print('Case #%d: %d' % (t, g[n][2]))
solution()
