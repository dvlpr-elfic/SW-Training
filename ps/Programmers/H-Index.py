
def checking(arr, h):
    upper_count = 0
    lower_count = 0
    for item in arr:
        if h <= item:
            upper_count += 1
        else:
            lower_count += 1
    return upper_count >= h and (lower_count + upper_count == len(arr))


def bst(arr, left, right):
    ret = 0
    while left < right:
        mid = int((left+right)/2)
        if checking(arr, mid):
            ret = max(ret, mid)
            left = mid+1
        else:
            right = mid
    return ret


def solution(arr):
    answer = 0
    arr.sort()
    answer = bst(arr, 0, 10001)
    return answer
 