import numpy as np

def solution():
    T = int(input())
    for t in range(1, T+1):
        solve(t)
def solve(t):
    n, q = map(int, input().split(' '))
    a = list(map(int, input().split(' ')))
    x = np.cumsum(a)
    y = np.cumsum(x)
    x = x.tolist()
    y = y.tolist()
    x.insert(0, 0)
    y.insert(0, 0)
    #print(x)
    #print(y)
    print('Case #%d:' % (t))
    for i in range(q):
        l, r = map(int, input().split(' '))
        ans = cum(a, x, y, r) - cum(a, x, y, l-1)
        print(ans)
def cum(a, x, y, k):
    n = len(x)-1
    left, right = min(a), y[-1]
    aless, aequal = 0, 0
    while left < right:
        mid = (left+right)>>1
        less, equal = 0, 0
        j = 0
        for i in range(1, n+1):
            while j<i and x[i]-x[j]>mid:
                j += 1
            if i!=j:
                if x[i]-x[j]==mid:
                    less += i-j-1
                else:
                    less += i-j
            if x[i]-x[j]==mid:
                equal += 1
        if less+equal < k:
            left = mid+1
        else:
            right = mid
            aless = less
            aequal = equal
    res = (k-aless) * left
    #print(res, k, aless, left)
    j = 0
    #print(x)
    #print(y)
    for i in range(1, n+1):
        while j<i and x[i]-x[j]>left:
            j += 1
        #print(i, j, res)
        if i!=j:
            if x[i]-x[j]<left:
                #tricky here notice j is 0
                if j!=0:
                    addi = ((i-j)*x[i] - (y[i-1]-y[j-1]))
                else:
                    addi = (i-j)*x[i] - y[i-1]
                res += addi
                #print(res, addi, '<')
            else:
                addi = ((i-j-1)*x[i] - (y[i-1]-y[j]))
                res += addi
                #print(res, addi, '=')
        #print(i, res)
    #print(res)
    return res
solution()
