dx = [0, 1, 0, -1]
dy = [-1, 0, 1, 0]


def is_wall(x, y, n, m):
    return (x < 0) or (y < 0) or (x >= m) or (y >= n)


def put(depth, val, x, y, n, m):
    global visited
    if depth == 3:
        return val
    ret = -1
    for i in range(4):
        nx = x + dx[i]
        ny = y + dy[i]
        if is_wall(nx, ny, n, m):
            continue
        if visited[ny][nx]:
            continue
        visited[ny][nx] = True
        ret = max(ret, put(depth+1, val+board[ny][nx], nx, ny, n, m))
        visited[ny][nx] = False
    return ret


def put_except(board, x, y, n, m):
    ret = 0
    for dir in range(4):
        cur = board[y][x]
        for delta in range(3):
            ndir = (dir + delta) % 4
            nx = x + dx[ndir]
            ny = y + dy[ndir]
            if is_wall(nx, ny, n, m):
                cur = 0
                break
            cur += board[ny][nx]
        ret = max(ret, cur)
    return ret


def solve(board, n, m):
    ret = -1
    global visited
    for y in range(n):
        for x in range(m):
            visited[y][x] = True
            ret = max(ret, put(0, board[y][x], x, y, n, m))
            visited[y][x] = False
            ret = max(ret, put_except(board, x, y, n, m))
    return ret


n, m = tuple(map(int, input().split()))

board = []
visited = [[False] * m for _ in range(n)]

for _ in range(n):
    board.append(list(map(int, input().split())))

print(solve(board, n, m))
