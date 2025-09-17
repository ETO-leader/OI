def main():
    a = list(map(int, input().split()))
    n = len(a)
    for i in range(n // 2):
        if a[i] > a[n - i - 1]:
            a[i], a[n - i - 1] = a[n - i - 1], a[i]
    print(a)
    ans = 0
    for i in range(n):
        for j in range(i + 1, n):
            ans += a[i] > a[j]
    print(ans)

if __name__ == '__main__':
    main()
