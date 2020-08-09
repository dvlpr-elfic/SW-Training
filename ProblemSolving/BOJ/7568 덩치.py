
def larger(cur, side):
return (side[0] > cur[0]) and (side[1] > cur[1])


def solve(arr):
ret = []
for cur in range(len(arr)):
count = 1
for side in range(len(arr)):
if side == cur:
continue
if larger(arr[cur], arr[side]):
count += 1
ret.append(count)
return ret


n = int(input())
db = []
for _ in range(n):
w, h = tuple(input().split(' '))
db.append((w, h))


answer = solve(db)

for item in answer:
print("{}".format(item), end=' ')
print()
