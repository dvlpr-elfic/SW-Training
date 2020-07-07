
class File:
    def _parse(self, name):
        for i in range(0, len(name)):
            if isNumber(name[i]):
                number_index = i
                self.head = name[0:i].lower()
                break
        for i in range(number_index, len(name)):
            if not isNumber(name[i]):
                self.n = int(name[number_index:i])
                break

        if self.n is None:
            self.n = int(name[number_index:len(name)])


    def __init__(self, name, id):
        self.name = name
        self.id = id
        self.n = None
        self.head = None
        self._parse(name)


    def __str__(self):
        return '''
        name = {}
        head = {}
        number = {}
        id = {}
        '''.format(self.name, self.head, self.n, self.id)


def isNumber(ch):
    return ch >= '0' and ch <='9'


def solution(names):
    answer = []
    files = []
    id = 0
    for name in names:
        files.append(File(name, id))
        id += 1
    files.sort(key=lambda x : (x.head, x.n))
    for file in files:  answer.append(file.name)
    return answer


