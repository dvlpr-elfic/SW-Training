

def init():
    t = int(input())
    numbers = []
    for _ in range(t):
        numbers.append(int(input()))
    return t, numbers


def get_count(number, cur):
    if cur > number:
        return 0
    if cur == number:
        return 1
    ret = 0
    for n in range(1, 4):
        ret += get_count(number, cur+n)
    return ret


def solve(t, numbers):
    counts = [0]*t
    for i in range(t):
        counts[i] = get_count(numbers[i], 0)
    return counts


def main():
    t, numbers = init()
    for cnt in solve(t, numbers):
        print(cnt)


if __name__ == "__main__":
    main()
