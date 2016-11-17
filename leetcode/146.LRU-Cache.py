class LRUCache(object):

    def __init__(self, capacity):
        """
        :type capacity: int
        """
        self.c = capacity
        self.cache = []
        self.d = {}

    def get(self, key):
        """
        :rtype: int
        """
        if key not in self.cache:
            return -1
        else:
            i = self.cache.index(key)
            self.cache.pop(i)
            self.cache.insert(0, key)
            return self.d[key]

    def set(self, key, value):
        """
        :type key: int
        :type value: int
        :rtype: nothing
        """
        if key in self.cache:
            i = self.cache.index(key)
            #self.cache = self.cache[i:i+1] + self.cache[:i] + self.cache[i+1:]
            self.cache.pop(i)
            self.cache.insert(0, key)
            self.d[key] = value
        elif len(self.cache) < self.c:
            self.cache.insert(0, key)
            self.d[key] = value
        else:
            self.cache.pop()
            self.cache.insert(0, key)
            self.d[key] = value

