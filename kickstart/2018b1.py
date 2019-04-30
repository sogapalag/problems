# No_Nine
def legal(num: str) -> int:
    """
    one can prove in [0, 10^z], z~[1,.)
    not cantain 9, there are 9^z
    and 0~8 (mod 9) are equal 9^(z-1)
    thus iter num_i
    """
    l = len(num)
    if l == 1:
        d = int(num)
        if d == 9:
            d = 8
        return d
    res = 0
    m = 0
    for i, d in enumerate(num):
        if i < l-1:
            d = int(d)
            m += d
            # not robust, input num may not valid FL, but FL valid pass test
            if d == 9:
                d = 8
            res += d * 8 * 9**(l-1 - i-1)
    d = int(num[-1])
    if d == 9:
        d = 8
    res += d+1
    m = m%9
    if (9-m)%9 <= d:
        res -= 1
    return res

def main():
    T = int(input())
    for i in range(T):
        F, L = input().split(' ')
        print('Case #{}: {}'.format(i+1, legal(L) - legal(F) + 1))

if __name__ == '__main__':
    main()
