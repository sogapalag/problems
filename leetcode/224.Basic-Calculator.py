class Solution(object):
    def calculate(self, s):
        """
        :type s: str
        :rtype: int
        """
        total = 0
        i = 0
        signs = [1, 1]
        while i < len(s):
            c = s[i]
            if c.isdigit():
                start = i
                while i < len(s) and s[i].isdigit():
                    i += 1
                total += signs.pop() * int(s[start:i])
                continue
            if c in '+-(':
                signs.append(signs[-1] * (1, -1)[c == '-'])
            elif c == ')':
                signs.pop()
            i += 1
        return total
