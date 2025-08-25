N, K = map(int, input().split())

ans = N

for k in range(2, K + 1):
    ans += (N // k) + ((N - 1) // k) + 1

print(ans)
