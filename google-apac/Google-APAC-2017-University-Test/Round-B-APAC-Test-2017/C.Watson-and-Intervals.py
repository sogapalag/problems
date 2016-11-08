def solution():
    T = int(input())
    for t in range(1, T+1):
        solve(t)
# O(n log n)
def solve(t):
    n, l1, r1, a, b, c1, c2, m = map(int, input().split(' '))
    # (o, p, q): point, left or right, index of interval
    bound = [(l1,1,1), (r1,-1,1)]
    for i in range(2,n+1):
        x = (a*l1 + b*r1 + c1) % m
        y = (a*r1 + b*l1 + c2) % m
        l1 = min(x, y)
        r1 = max(x, y)
        bound.append((l1, 1, i))
        bound.append((r1, -1, i))
    sort_bound = sorted(bound, key=lambda e:(e[0], -e[1]))
    bus = set()
    total = 0
    single = [0,]*(n+1)
    last_left = 0
    single_left = 0
    for elem in sort_bound:
        old = len(bus)
        if old==1:
            only = list(bus)[0]
        if elem[1]==1:
            bus.add(elem[2])
        else:
            bus.remove(elem[2])
        # count total
        if old==0 and len(bus)==1:
            last_left = elem[0]
        if old==1 and len(bus)==0:
            total += elem[0] - last_left + 1
        # count single
        if len(bus)==1:
            single_left = elem[0]
            if elem[1]==-1:
                single_left += 1
        if old==1:
            single[only] += elem[0] - single_left + 1
            if elem[1]==1:
                single[only] -= 1
    ans = total - max(single)
    print('Case #%d: %d' % (t, ans))
solution()
