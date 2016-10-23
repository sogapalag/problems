import re
def solution():
    T = int(input())
    for t in range(1, T+1):
        solve(t)
def solve(t):
    n = int(input())
    eva = {''}
    ok = True
    assi = []
    for i in range(n):
        r = re.split('[\=\,\(\)]', input())
        assi.append([r[0], set(r[2:-1])])
    while assi:
        noupdate = True
        needpop = []
        for i, r in enumerate(assi):
            if r[1]:
                if r[1]<= eva:
                    eva.add(r[0])
                    noupdate = False
                    needpop.append(i)
                else:
                    r[1] -= eva
        if noupdate:
            ok = False
            break
        for index in needpop[::-1]:
            assi.pop(index)
    out = 'GOOD' if ok else 'BAD'
    print('Case #%d: %s' % (t, out))
solution()

