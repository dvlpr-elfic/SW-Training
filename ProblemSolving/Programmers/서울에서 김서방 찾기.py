
def solution(seoul):
    for name in seoul:
        if name == "Kim":
            result = seoul.index(name)
            break
            
    return "김서방은 {}에 있다".format(result)

