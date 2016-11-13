def solution():
    T = int(input())
    for t in range(1, T+1):
        solve(t)
def solve(t):
    s, r, c = map(int, input().split(' '))
    act = []
    for i in range(s):
        time, action = input().split(' ')
        act.append((int(time), action))
    LIMIT_TIME = 10**9
    # R, D, L, U
    dx = [0, 1, 0, -1]
    dy = [1, 0, -1, 0]

    turn = 0
    x, y = 1, 1
    l = 1
    food = set()
    path = {}
    d = 0
    keep = 0
    for i in range(1, LIMIT_TIME+1):
        # keep on one line
        if turn==s and keep > 2*r and keep > 2*c:
            break
        # step
        x += dx[d]
        y += dy[d]
        if x<1:
            x = r
        if x>r:
            x = 1
        if y<1:
            y = c
        if y>c:
            y = 1

        # eat
        cell = (x, y)
        if (x + y) % 2 and cell not in food:
            food.add(cell)
            l += 1
            keep = 0

        # self-death
        last = path[cell] if cell in path else -1
        if i - l < last:
            break
        path[cell] = i

        # next action
        if turn < s and act[turn][0] == i:
            if act[turn][1] == 'R':
                d = (d + 1) % 4
            else:
                d = (d + 3) % 4
            turn += 1
            keep = 0
        keep += 1
    print('Case #%d: %d' % (t, l))
solution()
