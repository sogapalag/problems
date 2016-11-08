def solution():
    T = int(input())
    for t in range(1, T+1):
        solve(t)
def solve(t):
    m = int(input())
    c = list(map(int, input().split(' ')))
    c[0] = -c[0]
    # Newton's method
    f = lambda x: sum([e*x**(m-i) for i,e in enumerate(c)])
    ef = lambda x: sum([(m-i)*e*x**(m-i-1) for i,e in enumerate(c)])
    x = 1.0
    a, b = 1.0, 1.0
    while abs(a)>abs(b*10**-9):
        a = f(x)
        b = ef(x)
        x -= a/b
        #print(x, a, b)
        #print(a/b)
    print('Case #%d: %.12f' % (t, x-1))
solution()
