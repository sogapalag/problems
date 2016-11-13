def solution():
    T = int(input())
    for t in range(1, T+1):
        solve(t)
def solve(t):
    k = int(input())
    i = 63
    rev = 0
    while i>0:
        mid = 2**i
        if k>mid:
            rev += 1
            k = (mid<<1) - k
        elif k==mid:
            break
        i -= 1
    out = rev%2
    print('Case #%d: %d' % (t, out))
solution()
