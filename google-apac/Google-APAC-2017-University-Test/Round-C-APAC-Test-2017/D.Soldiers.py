import numpy as np

def solution():
    T = int(input())
    for t in range(1, T+1):
        solve(t)
def solve(t):
    n = int(input())
    a, b = [], []
    for i in range(n):
        x, y = map(int, input().split(' '))
        a.append(x)
        b.append(y)
    ia = np.argsort(a).tolist()
    ib = np.argsort(b).tolist()
    ok = itcheck(a, b, ia, ib)
    out = 'YES' if ok else 'NO'
    print('Case #%d: %s' % (t, out))
def itcheck(a, b, ia, ib):
    while ia and ib:
        xa = len(ia)-1
        sa = set()
        for i in range(xa, -1, -1):
            if a[ia[i]]==a[ia[-1]]:
                sa.add(ia[i])
            else:
                break
        xb = len(ib)-1
        sb = set()
        for i in range(xb, -1, -1):
            if b[ib[i]]==b[ib[-1]]:
                sb.add(ib[i])
            else:
                break
        if (sa & sb):
            return True
        for e in (sa | sb):
            ia.remove(e)
            ib.remove(e)
    return False

# Recursive version, depth overflow
def check(a, b, ia, ib):
    if not ia and not ib:
        return False
    if not ia or not ib:
        return True
    xa = len(ia)-1
    sa = set()
    for i in range(xa, -1, -1):
        if a[ia[i]]==a[ia[-1]]:
            sa.add(ia[i])
        else:
            break
    xb = len(ib)-1
    sb = set()
    for i in range(xb, -1, -1):
        if b[ib[i]]==b[ib[-1]]:
            sb.add(ib[i])
        else:
            break
    if (sa & sb):
        return True
    for e in (sa | sb):
        ia.remove(e)
        ib.remove(e)
    return check(a, b, ia, ib)
solution()
