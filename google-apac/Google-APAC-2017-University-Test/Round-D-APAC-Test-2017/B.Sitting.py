def solution():
    T = int(input())
    for i in range(T):
        R, C = map(int, input().split(' '))
        print('Case #%d: %d' % (i+1, f(R, C)))
# idea of count diag element (i,j) which
# sum is 4, 7, 10...
# and note R=2 special case
def f(R, C):
    if R>C:
        return f(C, R)
    if R==2:
        return 2*f(1, C)
    spare = 0
    for i in range(4, R+C+1, 3):
        k = i-1
        k = k - max(0, k-R) - max(0, k-C)
        spare += k
    return R*C - spare
solution()
