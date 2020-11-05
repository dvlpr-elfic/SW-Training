
from itertools import combinations


def minimal(key, answer):
    for item in answer:
        count = 0
        for number in item:
            if number in key:
                count += 1
        if count == len(item):
            return False
    return True


def make_tuples(key, relation):
    tuples = []
    for r in relation:
        temp = []
        for i in key:
            temp.append(r[i])
        tuples.append(temp)
    return tuples


def unique(tuples):
    n = len(tuples)
    for i in range(n):
        for j in range(n):
            if i == j:  continue
            if tuples[i] == tuples[j]:
                return False
    return True


def solution(relation):
    
    answer = []
    col = len(relation[0])
    items = [i for i in range(col)]
    
    for n in range(1, col+1):
        combi = list(map(list, combinations(items, n)))
        for key in combi:
            if not minimal(key, answer):    continue
            tuples = make_tuples(key, relation)
            if not unique(tuples):   continue
            answer.append(key)
            
    return len(answer)
