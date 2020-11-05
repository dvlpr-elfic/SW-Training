class Solution:
    def pick(self, n, depth, start) -> int:
        if depth == n:
            return 1
        
        ret = 0
        
        for i in range(start, 5):
            ret += self.pick(n, depth+1, i)
            
        return ret
        
    def countVowelStrings(self, n: int) -> int:
        return self.pick(n, 0, 0)
