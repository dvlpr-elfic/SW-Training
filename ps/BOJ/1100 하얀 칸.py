
arr = []

for _ in range(8):
    arr.append(list(input().strip()))

start = 0
answer = 0

for y in range(8):
    for x in range(start, 8, 2):
        if arr[y][x] == 'F':
            answer += 1
    start ^= 1

print(answer)
 