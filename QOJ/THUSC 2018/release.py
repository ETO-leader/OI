n = 831041201685240

x = 2

while x * x < n + 1:
    while n % x == 0:
        print(x)
        n //= x
    x += 1

if n > 1: print(n)
