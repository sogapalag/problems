import bisect

def solve(n, k, v):
    E = [0] * (k+1)
    E[0] = sum(v) / n
    # E[i+1] = (<)E[i] + (>)
    for i in range(k):
        t = bisect.bisect(v, E[i])
        E[i+1] = (t * E[i] + sum(v[t:]))/n
    return E[k]

def main():
    T = int(input())
    for i in range(T):
        n, k = map(int, input().split(' '))
        v = sorted(map(float, input().split(' ')))
        res = solve(n, k, v)
        print('Case #{}: {:.6f}'.format(i+1, res))

if __name__ == '__main__':
    main()
