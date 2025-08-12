while True:

    q = list(map(int, input().split()))

    n = len(q)

    p = [3, 1, 4, 2]

    k = 1

    ans = 0
    for i in range(n):
        if i == k: continue
        for j in range(i + 1, n):
            ans += (p[q[i] - 1] == q[j])

    print(ans)
