def solution():
    T = int(input())
    for t in range(1, T+1):
        solve(t)
def solve(t):
    n = int(input())
    deck = []
    for i in range(n):
        deck.append(input())
    # pay only when less than top deck
    maxName = ''
    cost = 0
    for name in deck:
        if name >= maxName:
            maxName = name
        else:
            cost += 1
    print('Case #%d: %d' % (t, cost))
solution()
