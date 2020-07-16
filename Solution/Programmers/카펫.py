
def solution(brown, yellow):
    answer = [0, 0]
    area = brown + yellow
    
    for width in reversed(range(area + 1)):
        height, m = divmod(area, width)
        
        if m != 0:
            continue
            
        if (width-2)*(height-2) == yellow:
            answer = [width, height]
            break
        
    return answer
 