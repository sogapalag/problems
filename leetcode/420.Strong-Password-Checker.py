class Solution(object):
    def strongPasswordChecker(self, s):
        """
        :type s: str
        :rtype: int
        """
        miss = 3
        if any('a' <= c <= 'z' for c in s):
            miss -= 1
        if any('A' <= c <= 'Z' for c in s):
            miss -= 1
        if any(c.isdigit() for c in s):
            miss -= 1

        repl = 0
        one = two = 0
        p = 2
        while p < len(s):
            if s[p-2] == s[p-1] == s[p]:
                length = 2
                while p < len(s) and s[p] == s[p-1]:
                    length += 1
                    p += 1
                repl += length / 3
                if length % 3 == 0:
                    one += 1
                elif length % 3 == 1:
                    two += 1
            else:
                p += 1

        if len(s) < 6:
            return max(miss, 6-len(s))
        elif len(s) <= 20:
            return max(miss, repl)
        else:
            dele = len(s) - 20
            repl -= min(dele, one)
            repl -= min(max(dele-one, 0), two * 2) / 2
            repl -= max(dele - one - two * 2, 0) / 3
            return dele + max(miss, repl)
