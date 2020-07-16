
ZERO = ord('0')

numbers = [(ord(number)-ZERO) for number in input()]

def solve(numbers):
    cards = [0]*9
    ret = 0
    for number in numbers:
        if number == 9:
            number = 6
        if cards[number] <= 0:
            for i in range(9): cards[i] += 1
            cards[6] += 1
            ret += 1
        cards[number] -= 1
    return ret

print(solve(numbers))
 