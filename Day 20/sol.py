def f(key, n):
    numbers = [int(x) * key for x in open('input.txt')]
    indexes = list(range(len(numbers)))

    for i in indexes * n:
        indexes.pop(j := indexes.index(i))
        indexes.insert((j+numbers[i]) % len(indexes), i)

    zero = indexes.index(numbers.index(0))
    return sum(numbers[indexes[(zero+p*1000) % len(numbers)]] for p in [1,2,3])

print(f(1, 1), f(811589153, 10))