def solution():
    T = int(input())
    for t in range(1, T+1):
        solve(t)
# O(N^2)
def solve(t):
    n, k = map(int, input().split(' '))
    num = []
    for i in range(4):
        num.append(list(map(int, input().split(' '))))
    dicX, dicY = {}, {}
    for a in num[0]:
        for b in num[1]:
            x = a^b
            if x in dicX:
                dicX[x] += 1
            else:
                dicX[x] = 1
    for c in num[2]:
        for d in num[3]:
            y = c^d
            if y in dicY:
                dicY[y] += 1
            else:
                dicY[y] = 1
    ans = 0
    for x in dicX:
        y = x^k
        if y in dicY:
            ans += dicX[x] * dicY[y]
    print('Case #%d: %d' % (t, ans))
solution()
