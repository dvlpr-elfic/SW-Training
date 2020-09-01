
def enter(users, name, history, uid, string):
    users[uid] = name
    history.append((uid, string))
    return None


def leave(history, uid, string):
    history.append((uid, string))
    return None


def change(users, uid, name):
    users[uid] = name
    return None


def make_answer(history, users):
    ret = []
    for message in history:
        uid, string = message
        ret.append("{}{}".format(users[uid], string))
    return ret        


def solution(records):
    history = []
    answer = None
    users = {}
        
    for record in records:
        record = tuple(record.split())
        if len(record) == 2:
            cmd, uid = record
        else:
            cmd, uid, name = record
        if cmd == "Enter":
            enter(users, name, history, uid, "님이 들어왔습니다.")
        elif cmd == "Leave":
            leave(history, uid, "님이 나갔습니다.")
        else:
            change(users, uid, name)
    
    answer = make_answer(history, users)
    
    return answer
