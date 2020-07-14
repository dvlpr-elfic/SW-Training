
class Node:
    def __init__(self, count, idplay):
        self.total_count = count
        self.musics = [idplay]
    
    def __str__(self):
        return '''total_count : {}
        musics : {}'''.format(self.total_count, self.musics)
            

def solution(genres, plays):
    table = {}
    answer = []
    
    for i in range(len(plays)):
        genre = genres[i]
        play = plays[i]
        
        if table.get(genre):
            table[genre].total_count += play
            table[genre].musics.append((i, play))
        else:
            table[genre] = Node(play, (i, play))
            
    for value in table.values():
        value.musics.sort(key = lambda x: x[1], reverse = True)
        value.musics = value.musics[:2]
        
    nodes = list(table.values())
    nodes.sort(key = lambda x : -x.total_count)
    
    for node in nodes:
        for music in node.musics:
            answer.append(music[0])
    
    return answer
 