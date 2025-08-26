s = input()

p, m = map(int, input().split())

x = 0
b = eval(s) % m

x = 1
k = (eval(s) % m + m - b) % m


for c in range(m):
    if (k * c + b) % m == p:
        print(c)
        break
