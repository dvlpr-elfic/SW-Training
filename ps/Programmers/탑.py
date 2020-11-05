
def find_receive(heights, pos):
    height = heights[pos]
    ret = 0
    for i in reversed(range(pos)):
        if heights[i] > height:
            ret = i+1
            break
    return ret

def solution(heights):
    answer = []
    for i in range(len(heights)):
        answer.append(find_receive(heights, i))
    return answer
 