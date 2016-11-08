def solution():
    T = int(input())
    m = 10**9 + 7
    for t in range(1, T+1):
        solve(t, m)
def solve(t, m):
    a, b, n, k = map(int, input().split(' '))
    pair = 0
    ave, mor = (n//k)%m, n%k
    # x[i]: #(j mod k = i), j in [1,n]
    x = [ave,]*k
    for index in range(1, mor+1):
        x[index] = (x[index]+1) % m
    # am[i]: i^a mod k
    am = [modular_pow(base=i, exponent=a, modulus=k) for i in range(k)]
    bm = [modular_pow(base=i, exponent=b, modulus=k) for i in range(k)]
    # amod[i]: #(j^a mod k = i)
    amod = [0,]*k
    bmod = [0,]*k
    for i in range(k):
        pair += bmod[(k - am[i]) % k] * x[i] % m
        pair += amod[(k - bm[i]) % k] * x[i] % m
        if (am[i] + bm[i]) % k == 0:
            pair += x[i] * (x[i] - 1) % m
        pair %= m
        amod[am[i]] += x[i]
        bmod[bm[i]] += x[i]
    print('Case #%d: %d' % (t, pair))
# O(log e)
def modular_pow(base, exponent, modulus):
    if modulus==1:
        return 0
    res = 1
    while exponent>0:
        if exponent % 2 == 1:
            res = (res*base) % modulus
        exponent >>= 1
        base = base**2 % modulus
    return res
solution()
