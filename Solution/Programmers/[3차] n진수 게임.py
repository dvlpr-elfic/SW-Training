

TO_HEX = '0123456789ABCDEF'

def converting(input, n):
    if input == 0:
        return ''
    share, rest = divmod(input, n)
    value = TO_HEX[rest]
    return converting(share, n) + value

def converter(dec, n):
    if dec == 0:
        return '0'
    else:
        return converting(dec, n)

def solution(n, t, m, p):
    answer = ''
    count = 0
    numbers = []
    limit = (p - 1) + t * m
    while len(numbers) < limit:
        value = converter(count, n)
        for item in value:  numbers.append(item)
        count += 1
    index = p - 1
    for i in range(t):
        answer += numbers[index]
        index += m
    return answer

  