
class Truck:
    def __init__(self, weight=0, dist=0):
        self.weight = weight
        self.dist = dist

    def to_string(self):
        return '''({}, {})'''.format(self.weight, self.dist)


class Bridge:
    def __init__(self, weight=0, length=0, limit=0):
        self.q = []
        self.total_weight = weight
        self.limit = limit
        self.length = length

    def is_full(self, add_weight):
        return self.limit < self.total_weight + add_weight

    def add(self, w):
        truck = Truck(weight=w)
        self.q.append(truck)
        self.total_weight += w

    def update(self):
        ret = 0
        for i in range(len(self.q) - 1, -1, -1):
            self.q[i].dist += 1
            if self.q[i].dist >= self.length:
                ret += 1
                self.total_weight -= self.q.pop(i).weight
        return ret

    def __str__(self):
        return '''total weight : {}
        limit weight : {}
        length : {}
        queue : {}'''.format(self.total_weight, self.limit, self.length, [item.to_string() for item in self.q])


def solution(bridge_length, weight, trucks):
    finished = 0
    answer = 0
    n = len(trucks)
    bridge = Bridge(limit=weight, length=bridge_length)

    while finished < n:
        answer += 1
        if trucks:
            if not bridge.is_full(trucks[0]):
                bridge.add(trucks.pop(0))
        finished += bridge.update()

    return answer + 1
 