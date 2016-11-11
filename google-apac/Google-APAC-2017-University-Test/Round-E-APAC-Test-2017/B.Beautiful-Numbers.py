def solution():
    T = int(input())
    for t in range(1, T+1):
        p = solve(t)
        print('Case #%d: %d' % (t, p))
def isAllOne(i, n):
    while n:
        if n%i != 1:
            return False
        n //= i
    return True
def solve(t):
    n = int(input())
    # (p^x-1)/(p-1) = n
    # x>4, p<10^5
    minN = min(n, 10**5)
    for i in range(2, minN):
        if isAllOne(i, n):
            return i
    # x=4, note that |p* - p|~ 0.5
    p = int(n**(1/3))
    if isAllOne(p, n):
        return p
    # x=3, note that |p* - p|~ 0.5
    p = int(n**0.5)
    if isAllOne(p, n):
        return p
    # x=2
    return n-1
solution()
