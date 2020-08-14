
def get_sum(x):
  ret = x
  while x != 0:
    ret += x % 10
    x = int(x/10)
  return ret


def solve(n):
  ret = 0
  for x in range(n):
    if get_sum(x) == n:
      ret = x
      break
  return ret

n = int(input())
print(solve(n))
