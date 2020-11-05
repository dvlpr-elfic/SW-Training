
def get(x, base):
  if x % base == 0:
    return base
  else:
    return (x % base)


def solve(e, s, m):
  ret = 1
  while True:
    if (e == get(ret, 15)) and (s == get(ret, 28)) and (m == get(ret, 19)):
      break
    else:
      ret += 1
  return ret


E, S, M = tuple(map(int, input().split()))

print(solve(E, S, M))
