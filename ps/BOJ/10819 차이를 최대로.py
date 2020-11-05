
INF = 987654321

def cal(arr):
  ret = 0

  for i in range(0, len(arr)-1):
    ret += abs(arr[i] - arr[i+1])

  return ret


def solve(n, arr, depth, picked, perm):
  if depth == n:
    return cal(perm)
  ret = -INF
  
  for i in range(n):
    if picked[i]:
      continue
    picked[i] = True
    perm[depth] = arr[i]
    ret = max(ret, solve(n, arr, depth+1, picked, perm))
    picked[i] = False
  
  return ret


n = int(input())
picked = [False]*n
arr = list(map(int ,list(input().split())))
perm = [0]*n
print(solve(n, arr, 0, picked, perm))
