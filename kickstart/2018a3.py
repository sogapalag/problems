# Scrambled_Words
def trans(word: str) -> tuple:
    letters_count = [0] * 26
    for w in word:
        letters_count[ord(w) - 97] += 1
    return (word[0], word[-1], tuple(letters_count))

def solve(L, words, s1, s2, n, a, b, c, d):
    # key = (start_letter, end_letter, (letters_count))
    # value = #same scrambled words
    vocab = {}
    for word in words:
        key = trans(word)
        if key not in vocab:
            vocab[key] = 1
        else:
            vocab[key] += 1
    # generate string
    X = [ord(s1), ord(s2)]
    for i in range(n-2):
        X.append((a*X[-1] + b*X[-2] + c) % d)
    X[0] -= 97
    X[1] -= 97
    S = list(map(lambda x: chr(97 + x%26), X))
    print(S)
    # check
    res = 0
    for i in range(n-1):
        count = [0]*26
        count[ord(S[i]) - 97] = 1
        for j in range(i+1, n):
            count[ord(S[j]) - 97] += 1
            key = (S[i], S[j], tuple(count))
            if key in vocab:
                res += vocab.pop(key)
    return res

def main():
    T = int(input())
    for i in range(T):
        L = int(input())
        words = input().split(' ')
        s1, s2, n, a, b, c, d = input().split(' ')
        n, a, b, c, d = int(n), int(a), int(b), int(c), int(d)
        res = solve(L, words, s1, s2, n, a, b, c, d)
        print('Case #{}: {}'.format(i+1, res))

if __name__ == '__main__':
    main()
