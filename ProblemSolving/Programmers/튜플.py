
def parse(string):
    ret = string.lstrip('{').rstrip('}').split('},{')
    for i in range(len(ret)):
        ret[i] = ret[i].split(',')
    return ret


def pushMap(list, dict):
    n = len(list)
    for item in list:
        if dict.get(item):
            dict[item] = min(dict[item], n)
        else:
            dict[item] = n
            
            
def solution(s):
    map = {}
    lists = parse(s)
    for list in lists:
        pushMap(list, map)
    items = sorted(map.items(), key = lambda x : x[1])
    answer = [int(item[0]) for item in items]
    return answer
