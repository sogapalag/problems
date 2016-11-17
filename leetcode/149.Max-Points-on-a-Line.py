# Definition for a point.
# class Point(object):
#     def __init__(self, a=0, b=0):
#         self.x = a
#         self.y = b

class Solution(object):
    def maxPoints(self, points):
        """
        :type points: List[Point]
        :rtype: int
        """
        lines = {}
        n = len(points)
        if n == 0:
            return 0
        if n == 1:
            return 1
        for i in range(n):
            for j in range(0, i):
                li = line(points[i], points[j])
                if li in lines:
                    lines[li].add(i)
                    lines[li].add(j)
                else:
                    lines[li] = {j, i}
        maxl = max(lines, key=lambda l:len(lines[l]))
        return len(lines[maxl])
def line(p0, p1):
    a = p0.y - p1.y
    b = p1.x - p0.x
    # test case a==b==0
    if a == b == 0:
        return (p0.x, p0.y)
    rev = -1 if (a < 0 or (a == 0 and b < 0)) else 1
    rev /= (a**2 + b**2)**0.5
    a *= rev
    b *= rev
    c = a*p0.x + b*p0.y
    # almost equal
    prec = lambda x: float('%.12f' % x)
    a = prec(a)
    b = prec(b)
    c = prec(c)
    return (a, b, c)
