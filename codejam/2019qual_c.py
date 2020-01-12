# use some gcd recover all
from fractions import gcd
def solve():
    #_n = int(input())
    #_l = int(input())
    input()
    prod = list(map(int, input().split(' ')))
    n = len(prod)
    a = [-1] * (n+1)
    for i in range(1, n):
        if prod[i-1] != prod[i]:
            a[i] = gcd(prod[i-1], prod[i])
            k = i-1
            while k >= 0:
                a[k] = prod[k] // a[k+1]
                k -= 1
            k = i
            while k < n:
                a[k+1] = prod[k] // a[k]
                k += 1
            break
    alpha = sorted(set(a))
    assert(len(alpha) == 26)
    res = ""
    for x in a:
        for i in range(26):
            if alpha[i] == x:
                res += chr(ord('A') + i)
    return res
def main():
    T = int(input())
    for t in range(1, T+1):
        print("Case #%d: %s" % (t, solve()))
main()
