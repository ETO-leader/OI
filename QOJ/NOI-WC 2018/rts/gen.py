from random import randint

print(300000, 5000000, 1)

las = 1

for i in range(2, 300001):
    if randint(0, 2):
        print(las, i)
        las = i
    else:
        print(randint(1, i - 1), i)