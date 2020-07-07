
def pushMap(list, dict):
    n = len(list)
    for item in list:
        if dict.get(item):
            dict[item] = min(dict[item], n)
        else:
            dict[item] = n

class Node:
    def __init__(self, key = "", value = 0):
        self.key = key
        self.value = value

            
def solution(sets):
    answer = []
    map = {}
    number = ""
    for i in range(1, len(sets) - 1):
        if sets[i] == '{':
            temp = []
            continue
        elif sets[i] == '}':
            temp.append(number)
            pushMap(temp, map)
            number = ""
        elif sets[i] == ',':
            if not number:
                continue
            temp.append(number)
            number = ""
        else:       # 숫자
            number += sets[i]
    list = [Node(key, value) for key, value in map.items()]
    list.sort(key = lambda x : x.value)
    answer = [int(node.key) for node in list]
    return answer

