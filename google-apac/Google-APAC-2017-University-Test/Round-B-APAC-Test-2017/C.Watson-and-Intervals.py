def solution():
    T = int(input())
    for t in range(1, T+1):
        solve(t)
# O(n log n)
def solve(t):
    n, l1, r1, a, b, c1, c2, m = map(int, input().split(' '))
    # (o, p, q): point, left or right, index of interval
    bound = [(l1,1,1), (r1+1,-1,1)]
    for i in range(2,n+1):
        x = (a*l1 + b*r1 + c1) % m
        y = (a*r1 + b*l1 + c2) % m
        # THIS!! use x,y recur, not min/max
        l1 = x
        r1 = y
        bound.append((min(l1, r1), 1, i))
        bound.append((max(l1, r1)+1, -1, i))
    #print(bound)
    sort_bound = sorted(bound, key=lambda e:(e[0], e[1]))
    #print(sort_bound)
    bus = set()
    total = 0
    single = [0,]*(n+1)
    last_left = 0
    single_left = 0
    for i, elem in enumerate(sort_bound):
        old = len(bus)
        if old==1:
            only = list(bus)[0]
        if elem[1]==1:
            bus.add(elem[2])
        else:
            bus.remove(elem[2])
        # count total
        if old>=1:
            total += elem[0] - sort_bound[i-1][0]
        # count single
        if old==1:
            single[only] += elem[0] - sort_bound[i-1][0]
    ans = total - max(single)
 #   for i, e in enumerate(single):
 #       if e!=0:
 #           print(i, e)
    print('Case #%d: %d' % (t, ans))
solution()
