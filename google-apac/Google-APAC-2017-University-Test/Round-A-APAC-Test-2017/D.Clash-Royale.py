def solution():
    T = int(input())
    for t in range(1, T+1):
        solve(t)
def solve(t):
    m, n = map(int, input().split(' '))
    k, l = [], []
    a, c = [], []
    for i in range(n):
        kk, ll = map(int, input().split(' '))
        k.append(kk)
        l.append(ll)
        a.append(list(map(int, input().split(' '))))
        c.append(list(map(int, input().split(' '))))

