import random
from collections import defaultdict

class RandomizedCollection(object):

    def __init__(self):
        """
        Initialize your data structure here.
        """
        self.collection = defaultdict(set)
        self.element = []

    def insert(self, val):
        """
        Inserts a value to the collection. Returns true if the collection did not already contain the specified element.
        :type val: int
        :rtype: bool
        """
        ok = not self.collection[val]
        n = len(self.element)
        self.element += val,
        self.collection[val].add(n)
        return ok

    def remove(self, val):
        """
        Removes a value from the collection. Returns true if the collection contained the specified element.
        :type val: int
        :rtype: bool
        """
        if not self.collection[val]:
            return False
        index = self.collection[val].pop()
        if index != len(self.element) - 1:
            self.element[index] = self.element[-1]
            self.collection[self.element[-1]].add(index)
            self.collection[self.element[-1]].remove(len(self.element) - 1)
        self.element.pop()
        return True

    def getRandom(self):
        """
        Get a random element from the collection.
        :rtype: int
        """
        if len(self.element) == 0:
            return -1
        # OJ is python2., randint
        return self.element[random.randint(0, len(self.element)-1)]


# Your RandomizedCollection object will be instantiated and called as such:
# obj = RandomizedCollection()
# param_1 = obj.insert(val)
# param_2 = obj.remove(val)
# param_3 = obj.getRandom()
