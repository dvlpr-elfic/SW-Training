class Solution:
    def canFormArray(self, arr: List[int], pieces: List[List[int]]) -> bool:
        d = dict()
        for idx in range(len(arr)):
            key = arr[idx]
            d[key] = idx
        
        for piece in pieces:
            for i in range(1, len(piece)):
                try:
                    if (d[piece[i]] - d[piece[i-1]]) != 1:
                        return False
                except:
                    return False
        
        return True
