
def set_hash_table(items):
    hash_table = {}
    for item in items:
        key = item[1]
        if hash_table.get(key):
            hash_table[key] += 1
        else:
            hash_table[key] = 1
    return hash_table
        

def solution(clothes):
    
    ret = 1
    hash_table = set_hash_table(clothes)
    for key, value in hash_table.items():
        ret *= (value + 1)
    ret -= 1
    return ret

 