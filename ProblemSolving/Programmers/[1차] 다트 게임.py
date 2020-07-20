def isNumber(token):
    return token <= '9' and token >= '0'

def isPow(token):
    return token == 'S' or token == 'D' or token == 'T'

def pow(value, token):
    if token == 'S':
        return value
    elif token == 'D':
        return value * value
    elif token == 'T':
        return value * value * value
    else:
        print("pow error")
        return None

def solution(dartResult):
    ret = 0
    nodes = []
    value = 0
    for token in dartResult:
        if isNumber(token):
            value = value * 10 + int(token)
        elif isPow(token):
            nodes.append(pow(value, token))
            value = 0
        else:
            if token == '*':
                operand = 2
            else:
                operand = -1
            index = len(nodes) - 1
            if index == 0:
                nodes[index] = nodes[index] * operand
            else:
                nodes[index] = nodes[index] * operand
                if operand > 0:
                    nodes[index - 1] = nodes[index - 1] * operand
    for node in nodes:
        ret += node
    return ret
