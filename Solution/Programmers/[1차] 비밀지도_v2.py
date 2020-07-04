
def getStrCode(code, n):
    ret = ""
    base = 1 << (n - 1)
    
    for i in range(0, n):
        and_value = code & base
        base = base >> 1
        if and_value == 0:
            ret += " "
        else:
            ret += "#"

    return ret

def solution(n, arr1, arr2):
    answer = []
    for i in range(0, n):
        code = arr1[i] | arr2[i]
        answer.append(getStrCode(code, n))
    return answer
    
    
