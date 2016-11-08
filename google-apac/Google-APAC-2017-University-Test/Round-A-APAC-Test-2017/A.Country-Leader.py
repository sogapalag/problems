def solution():
    T = int(input())
    for t in range(1, T+1):
        solve(t)
def solve(t):
    n = int(input())
    name_lst = []
    for i in range(n):
        name = input()
        set_n = set(name)
        if ' ' in set_n:
            set_n.remove(' ')
        name_lst.append((-len(set_n), name))
    leader = min(name_lst)[1]
    print('Case #%d: %s' % (t, leader))
solution()
