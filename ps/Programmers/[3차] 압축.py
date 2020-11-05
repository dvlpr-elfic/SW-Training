
dict_index = 1

def dict_init():
    ret = {}
    global dict_index
    for cur in range(ord('A'), ord('Z')+1):
        ret[chr(cur)] = dict_index
        dict_index += 1
    return ret

def get_w(d, msg):
    for l in range(1, len(msg)+1):
        if not d.get(msg[:l]):
            return msg[:l-1]
    return msg

def get_c(msg, w_len):
    if len(msg) <= w_len:
        return None
    return msg[w_len]

def add_dict(d, w, c):
    global dict_index
    d[w+c] = dict_index
    dict_index += 1

def solution(msg):
    answer = []
    d = dict_init()
    i = 0
    while True:
        w = get_w(d, msg[i:])
        c = get_c(msg[i:], len(w))
                    
        answer.append(d[w])
        if c is None:
            break
        add_dict(d, w, c)
        i += len(w)
        
    return answer
 