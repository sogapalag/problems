def main():
    n = int(input())
    s = input()
    res = int(s)
    i = n//2
    j = (n+1)//2
    while i >= 0 and s[i] == '0':
        i -= 1
    while j < n and s[j] == '0':
        j += 1
    assert(i>0 or j<n)
    if i > 0:
        res = min(res, int(s[:i]) + int(s[i:]))
    if j < n:
        res = min(res, int(s[:j]) + int(s[j:]))
    print(res)

if __name__ == '__main__':
    main()
