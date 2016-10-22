def solution():
    mod = 10**9+7
    T = int(input())
    for t in range(T):
        V, S = map(int, input().split(' '))
        # hash vocabulary
        vocabulary = {}
        for v in range(V):
            word = input()
            lst = [0] * 26
            for letter in word:
                lst[ord(letter) - ord('a')] += 1
            word = tuple(lst)
            if word in vocabulary:
                vocabulary[word] += 1
            else:
                vocabulary[word] = 1
        # dynamic program
        orinum = []
        for s in range(S):
            cipher = input()
            dp = [1]
            for c_i in range(len(cipher)):
                dp.append(0)
                clst = [0] * 26
                k = 0
                while k<20 and c_i>=k:
                    clst[ord(cipher[c_i-k]) - ord('a')] += 1
                    cword = tuple(clst)
                    if cword in vocabulary:
                        dp[-1] = (dp[-1] + dp[-2-k]*vocabulary[cword]) % mod
                    k += 1
            orinum.append(dp[-1])
        print('Case #%d: %s' % (t+1, ' '.join(str(e) for e in orinum)))
solution()
