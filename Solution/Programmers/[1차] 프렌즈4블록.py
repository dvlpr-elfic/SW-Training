
dx = (0, 1, 0, 1)
dy = (0, 0, 1, 1)

def visited_flush(n, m):
    return [[False]*m for _ in range(n)]

def erasable(b, x, y):
    for i in range(1, 4):
        if b[y][x] != b[y+dy[i]][x+dx[i]]:
            return False
    return True

def travel(n, m, board, visited):
    q = []
    for y in range(n-1):
        for x in range(m-1):
            if board[y][x] == 'x':  continue
            if erasable(board, x, y):
                for i in range(4):
                    nx = x + dx[i]
                    ny = y + dy[i]
                    if not visited[ny][nx]:
                        visited[ny][nx] = True
                        q.append((nx, ny))
    return q

    
def empty(q):
    return not q

def board_cleaning(n, m, board):
    for x in range(m):
        tmp = []
        for y in reversed(range(n)):
            if board[y][x] != 'x':
                tmp.append(board[y][x])
        while len(tmp) < n:
            tmp.append('x')
        for y in reversed(range(n)):
            board[y][x] = tmp.pop(0)
    return None

def erasing(board, q):
    for x, y in q:
        board[y][x] = 'x'
    return None

def strings_to_lists(board, n, m):
    ret = []
    for y in range(n):
        ret.append(list(board[y]))
    return ret

def show(board):
    print("-------------show------------")
    for y in range(len(board)):
        print(board[y])

def solution(n, m, board):
    answer = 0
    board = strings_to_lists(board, n, m)
    while True:
        visited = visited_flush(n, m)
        q = travel(n, m, board, visited)
        if empty(q):
            break
        answer += len(q)
        erasing(board, q)
        board_cleaning(n, m, board)
    return answer
 