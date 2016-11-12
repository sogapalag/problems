import numpy as np

def solution():
    T = int(input())
    for t in range(1, T+1):
        solve(t)
def solve(t):
    v, d = map(int, input().split(' '))
    g = 9.8
    # trivial physics, some test case flow a little bit
    s = max(-1., min(1., g*d/v**2))
    theta = np.rad2deg(np.arcsin(s)/2)
    print('Case #%d: %.8f' % (t, theta))
solution()
