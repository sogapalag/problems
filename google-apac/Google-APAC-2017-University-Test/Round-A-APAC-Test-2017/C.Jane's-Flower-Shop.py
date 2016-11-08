def solution():
    T = int(input())
    for t in range(1, T+1):
        solve(t)
def solve(t):
    m = int(input())
    c = list(map(int, input().split(' ')))
    c[0] = -c[0]
    # Newton's method, not well, binary is good
    f = lambda x: sum([e*x**(m-i) for i,e in enumerate(c)])
    ef = lambda x: sum([(m-i)*e*x**(m-i-1) for i,e in enumerate(c)])
    x = 1.0
    left, right = 10**-10, 2.0 - 10**-10
    while right - left > 10**-10:
        a = f(left)
        b = f(x)
        if a==0:
            x = a
            break
        if b==0:
            break
        if a*b > 0:
            left = x
        else:
            right = x
        x = (left+right)/2
    print('Case #%d: %.12f' % (t, x-1))
solution()
