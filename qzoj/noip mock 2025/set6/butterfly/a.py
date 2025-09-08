def binom(A : int, B : int):
    ans = 1
    for i in range(1, A + 1):
        ans *= i
    for i in range(1, B + 1):
        ans //= i
    for i in range(1, A - B + 1):
        ans //= i
    return ans

print(10)

k = 0

for n in range(10):
    ans = 0
    for i in range(n + 1):
        for j in range(i + 1):
            ans += binom(i, j) * (i + k) * (j + k)
    print(ans % 998244353)

