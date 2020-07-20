
def setHashTable(string_list):
    ret = {}
    for string in string_list:
        if ret.get(string):
            return None
        else:
            ret[string] = True
    return ret

def checking(table, string_list):
    for string in string_list:
        n = len(string)
        for cut in range(1, n):
            if table.get(string[:cut]):
                return False
    return True

def solution(phone_book):
    hashtable = setHashTable(phone_book)
    if hashtable is None:
        return False
    return checking(hashtable, phone_book)

 