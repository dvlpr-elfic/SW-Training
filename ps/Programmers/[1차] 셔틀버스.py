
def time_to_int(string):
    li = string.split(':')
    ret = int(li[0]) * 60
    ret += int(li[1])
    return ret

def int_to_time(integer):
    hour, minute = divmod(integer, 60)
    if hour < 10:
        hour = '0'+str(hour)
    else:
        hour = str(hour)
    if minute < 10:
        minute = '0' + str(minute)
    else:
        minute = str(minute)
    return hour + ':' + minute

class Bus:
    def __init__(self, time, c):
        self.time = time
        self.cap = c
        self.li = []
        self.count = 0
    
    def full(self):
        return self.count is self.cap
    
    def get_in(self, timetable):
        while timetable and self.count < self.cap:
            if timetable[0] <= self.time:
                self.li.append(timetable[0])
                self.count += 1
                timetable.pop(0)
            else:
                break
    
    def get_last_time(self):
        return self.li[self.count - 1]
        

def solution(n, t, m, times):
    bus_time = time_to_int("09:00")
    buses = []
    for _ in range(n):
        buses.append(Bus(bus_time, m))
        bus_time += t
    timetable = [time_to_int(x) for x in times]
    timetable.sort()
    for bus in buses:
        bus.get_in(timetable)
    last = buses[len(buses) - 1]
    if last.full():
        answer = last.get_last_time() - 1
    else:
        answer = last.time
        
    return int_to_time(answer)
 