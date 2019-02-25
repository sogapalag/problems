def solve(n: str) -> int:
    # find high odd
    h = len(n)
    l = len(n)
    for i, d in enumerate(n):
        if int(d) % 2 == 1:
            h = i
            break
    if h == len(n):
        return 0
    # must be minus
    if int(n[h]) == 9:
        return int(n[h:]) - int(str(int(n[h])-1) + '8'*(l-h-1))
    # comp dist. (x+1)00...0, (x-1)88...8
    return min(int(n[h:]) - int(str(int(n[h])-1) + '8'*(l-h-1)),
               (int(n[h])+1) * 10**(l-h-1) - int(n[h:]))

def main():
    T = int(input())
    for i in range(T):
        res = solve(input())
        print('Case #{}: {}'.format(i+1, res))

if __name__ == '__main__':
    main()
