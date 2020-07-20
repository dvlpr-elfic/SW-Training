def solution(participant, completion):
    map = {}
    
    for player in participant:
        if map.get(player) is None:
            map[player] = 1
        else:
            map[player] += 1
    
    for player in completion:
        map[player] -= 1
    
    for key in map:
        value = map[key]
        if value > 0:
            return key
    
    return ""
