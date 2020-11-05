
def split(s):
    s = s.lower()
    ret = []
    for i in range(len(s) - 1):
        cur = s[i:i+2]
        if cur[0] >= 'a' and cur[0] <='z' and cur[1] >= 'a' and cur[1] <='z':
            ret.append(cur)
    return ret


def setting(li):
    ret = {}

    for key in li:
        if not ret.get(key):
            ret[key] = 1
        else:
            ret[key] += 1

    return ret


def get_and(lhs, rhs):
    ret = 0

    for key, value in lhs.items():
        if rhs.get(key):
            ret += min(rhs[key], value)

    return ret

def get_or(lhs, rhs):
    table = {}
    ret = 0

    for key, value in lhs.items():
        table[key] = value

    for key, value in rhs.items():
        if table.get(key):
            table[key] = max(table[key], value)
        else:
            table[key] = value

    for value in table.values():
        ret += value

    return ret

def solution(str1, str2):
    list1 = split(str1)
    list2 = split(str2)

    dict1 = setting(list1)
    dict2 = setting(list2)

    and_val = get_and(dict1, dict2)
    or_val = get_or(dict1, dict2)

    if or_val == 0:
        return 65536

    answer = float(and_val) / float(or_val) * 65536

    answer = int(answer)

    return answer
 