
def init(priorities):
    ret = []
    for idx in range(len(priorities)):
        ret.append((priorities[idx], idx))
    return ret

def get_max_priority(arr):
    ret = 0
    for priority, idx in arr:
        ret = max(priority, ret)
    return ret

def solution(priorities, location):
    answer = 1
    q = init(priorities)
    
    while True:
        priority, idx = q.pop(0)
        
        if get_max_priority(q) > priority:
            q.append((priority, idx))
        else:
            if idx == location:
                break
            answer += 1
        
    return answer
