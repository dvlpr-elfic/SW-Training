
n, m, start = map(int, input().split())

graph = [[0]*(n+1) for _ in range(n+1)]

for _ in range(m):
    i, j = map(int, input().split())
    graph[i][j] = True
    graph[j][i] = True

def dfs(cur):
    visited[cur] = True
    print(cur, end = ' ')
    for next in range(n+1):
        if graph[cur][next] and not visited[next]:
            dfs(next)
    
def bfs(start):
    q = []
    q.append(start)
    visited[start] = True
    while q:
        cur = q.pop(0)
        print(cur, end = ' ')
        for next in range(n+1):
            if graph[cur][next] and not visited[next]:
                visited[next] = True
                q.append(next)
                
    
visited = [False for _ in range(n+1)]
dfs(start)
print()
visited = [False for _ in range(n+1)]
bfs(start)

  