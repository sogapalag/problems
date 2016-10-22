# (n, k) represent nCk
# (N+M-1, N-1)-(N+M-1, N) = (N-M)/(N+M) * (N+M, N)
def solution():
    T = int(input())
    for i in range(T):
        N, M = map(float, input().split(' '))
        print('Case #%d: %f' % (i+1, (N-M)/(N+M)))
solution()
