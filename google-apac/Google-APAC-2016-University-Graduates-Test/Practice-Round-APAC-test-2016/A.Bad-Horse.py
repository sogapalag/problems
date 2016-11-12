def solution():
    T = int(input())
    for t in range(1, T+1):
        ok = solve(t)
        s = 'Yes' if ok else 'No'
        print('Case #%d: %s' % (t, s))
# bipartiate, O(m^2)
def solve(t):
    m = int(input())
    pair = []
    for i in range(m):
        pair.append(list(input().split(' ')))
    light, dark = set(), set()
    index = [False,]*m
    i = 0
    while i<m:
        added = False
        for j in range(i, m):
            if not index[j]:
                a, b = pair[j][0], pair[j][1]
                # check a,b related founded set
                if (a in light and b in light) or (a in dark and b in dark):
                    return False
                if a in dark or b in light:
                    dark.add(a)
                    light.add(b)
                    index[j] = True
                    added = True
                if a in light or b in dark:
                    light.add(a)
                    dark.add(b)
                    index[j] = True
                    added = True
        # no related to past
        if not added:
            while i<m:
                if index[i]:
                    i += 1
                else:
                    break
            if i>=m:
                return True
            light.add(pair[i][0])
            dark.add(pair[i][1])
            i += 1
    return True
solution()
