import re

class Solution(object):
    def isNumber(self, s):
        """
        :type s: str
        :rtype: bool
        """
        #s = input()
        rnum = '([\-\+]?((\d+\.?\d*)|(\.\d+)))'
        intnum = '([\-\+]?\d+)'
        reg = '^\s*' + '(' + rnum + '|(' + rnum + 'e' + intnum + '))\s*$'
        match = re.match(reg, s)
        #print(True if match else False)
        #print(match)
        return True if match else False
#Solution().isNumber('s')
