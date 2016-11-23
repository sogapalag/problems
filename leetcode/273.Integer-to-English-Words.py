class Solution(object):
    def numberToWords(self, num):
        """
        :type num: int
        :rtype: str
        """
        if num == 0:
            return 'Zero'
        f = ['Thousand ', 'Million ', 'Billion ']
        s = ''
        if num > 10**9 - 1:
            s += self.helper(num // 10**9) + f[2]
            num %= 10**9
        if num > 10**6 - 1:
            s += self.helper(num // 10**6) + f[1]
            num %= 10**6
        if num > 10**3 - 1:
            s += self.helper(num // 10**3) + f[0]
            num %= 10**3
        s += self.helper(num)
        return s[:-1]
    def helper(self, x):
        d = ['Zero ', 'One ', 'Two ', 'Three ', 'Four ',
                'Five ', 'Six ', 'Seven ', 'Eight ', 'Nine ',
                'Ten ', 'Eleven ', 'Twelve ', 'Thirteen ', 'Fourteen ',
                'Fifteen ', 'Sixteen ', 'Seventeen ', 'Eighteen ', 'Nineteen ',
                'Twenty ']
        e = ['Twenty ', 'Thirty ', 'Forty ', 'Fifty ', 'Sixty ',
                'Seventy ', 'Eighty ', 'Ninety ', 'Hundred ']
        s = ''
        if x > 99:
            s += d[x//100] + e[-1]
            x %= 100
        if 0 < x <=20:
            s += d[x]
            return s
        if x > 20:
            s += e[x//10 - 2]
            x %= 10
        if 0 < x:
            s += d[x]
        return s
