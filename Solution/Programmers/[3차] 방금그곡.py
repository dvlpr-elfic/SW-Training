
def getTime(start, end):
    start = int(start[0:2]) * 60 + int(start[3:5])
    end = int(end[0:2]) * 60 + int(end[3:5])
    return end - start


def parse(codes):
    ret = []
    for code in codes:
        if code == '#':
            ret[-1] = ret[-1] + code
        else:
            ret.append(code)
    return ret


def isEqualCode(lval, rval):
    for i in range(len(lval)):
        if lval[i] != rval[i]:
            return False
    return True


def isPattern(src, dst):
    src_len = len(src)
    dst_len = len(dst)
    if dst_len > src_len:
        return False
    for i in range(src_len - dst_len + 1):
        if isEqualCode(dst, src[i:i + dst_len]):
            return True
    return False


def setLen(codes, time):
    ret = []
    n = len(codes)
    for i in range(time):
        ret.append(codes[i % n])
    return ret


def solution(target, musicinfos):
    answer = ''
    hits = []
    dst = parse(target)
    id = 1
    for info in musicinfos:
        info = info.split(',')
        start, end, name, codes = info
        time = getTime(start, end)
        src = parse(codes)
        src = setLen(src, time)
        if isPattern(src, dst):
            hits.append(Music(time, name, id))
            id += 1
    if not hits:
        return "(None)"
    hits.sort(key=lambda x: (-x.time, x.id))
    return hits[0].name


class Music:
    def __init__(self, time, name, id):
        self.time = time
        self.name = name
        self.id = id

