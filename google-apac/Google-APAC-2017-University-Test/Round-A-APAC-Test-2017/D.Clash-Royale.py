# Perfomance 4~5 min for large
# if not use lisDic, then need 12~13 min
def solution():
    T = int(input())
    for t in range(1, T+1):
        solve(t)
def solve(t):
    global maxim, card
    global m,n,k,l,a,c
    global lisDic
    m, n = map(int, input().split(' '))
    k, l = [], []
    a, c = [], []
    lisDic = {}
    for i in range(n):
        kk, ll = map(int, input().split(' '))
        k.append(kk)
        l.append(ll-1)
        a.append(list(map(int, input().split(' '))))
        cost = input()
        if cost=='':
            c.append([])
        else:
            c.append(list(map(int, cost.split(' '))))
    maxim = 0
    dfs(0, 0)
    #print(k)
    #print(l)
    #print(a)
    #print(c)
    print('Case #%d: %d' % (t, maxim))
card = [0,]*8
maxim = 0
m, n = 0, 0
k, l = [], []
a, c = [], []
def dfs(i, level):
    global maxim, card
    global m,n,k,l,a,c
    if level==8:
        update()
    else:
        if i>=n:
            return
        card[level]=i
        dfs(i+1, level+1)
        dfs(i+1, level)
# Find best update of 8 cards
lisDic = {}
def update():
    global maxim, card
    global m,n,k,l,a,c
    global lisDic
    # Meet in the middle
    lisA, lisB = [], []
    comb = (card[0], card[1], card[2], card[3])
    if comb not in lisDic:
        for ii in range(k[card[0]]):
            for jj in range(k[card[1]]):
                for kk in range(k[card[2]]):
                    for ll in range(k[card[3]]):
                        if (ii>=l[card[0]] and jj>=l[card[1]] and kk>=l[card[2]]
                            and ll>=l[card[3]]):
                            totcost = 0
                            totcost += sum(c[card[0]][ l[card[0]] : ii])
                            totcost += sum(c[card[1]][ l[card[1]] : jj])
                            totcost += sum(c[card[2]][ l[card[2]] : kk])
                            totcost += sum(c[card[3]][ l[card[3]] : ll])
                            if totcost<=m:
                                totpower = 0
                                totpower += a[card[0]][ii]
                                totpower += a[card[1]][jj]
                                totpower += a[card[2]][kk]
                                totpower += a[card[3]][ll]
                                lisA.append((totcost, totpower))
        lisA = sorted(lisA, key=lambda e:(e[0], -e[1]))
        topv = 0
        for i, e in enumerate(lisA):
            if e[1]>=topv:
                topv = e[1]
            else:
                lisA[i] = (e[0], topv)
        lisDic[comb] = lisA
    else:
        lisA = lisDic[comb]
    # for lisB
    comb = (card[4], card[5], card[6], card[7])
    if comb not in lisDic:
        for ii in range(k[card[4]]):
            for jj in range(k[card[5]]):
                for kk in range(k[card[6]]):
                    for ll in range(k[card[7]]):
                        if (ii>=l[card[4]] and jj>=l[card[5]] and kk>=l[card[6]]
                            and ll>=l[card[7]]):
                            totcost = 0
                            totcost += sum(c[card[4]][ l[card[4]] : ii])
                            totcost += sum(c[card[5]][ l[card[5]] : jj])
                            totcost += sum(c[card[6]][ l[card[6]] : kk])
                            totcost += sum(c[card[7]][ l[card[7]] : ll])
                            if totcost<=m:
                                totpower = 0
                                totpower += a[card[4]][ii]
                                totpower += a[card[5]][jj]
                                totpower += a[card[6]][kk]
                                totpower += a[card[7]][ll]
                                lisB.append((totcost, totpower))
        lisB = sorted(lisB, key=lambda e:(e[0], -e[1]))
        # make value grows
        topv = 0
        for i, e in enumerate(lisB):
            if e[1]>=topv:
                topv = e[1]
            else:
                lisB[i] = (e[0], topv)
        lisDic[comb] = lisB
    else:
        lisB = lisDic[comb]
    # binary search
    for e in lisA:
        left = 0
        right = len(lisB)
        mid = (left+right)//2
        resm = m - e[0]
        while right-left > 1:
            if lisB[mid][0] > resm:
                right = mid
            else:
                left = mid
            mid = (left+right)//2
        maxim = max(maxim, e[1] + lisB[mid][1])
solution()
