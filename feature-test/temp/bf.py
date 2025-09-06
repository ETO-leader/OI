def check(n : int, b : list):
    a = [i for i in range(n)]
    for i in b:
        ln = len(a) - 1
        for p in range(ln + 1):
            if a[p] == i:
                a[p], a[ln] = a[ln], a[p]
                del a[ln]
                break
    # if a == sorted(a):
        # print(b)
    return a == sorted(a)

def dfs(b : list, n : int, k : int):
    if len(b) == k:
        return (int)(check(n, b))
    res = 0
    for w in range(n):
        if w not in b:
            res += dfs(b + [w], n, k)
    return res

def main():
    T = int(input())
    for i in range(T):
        n, k = map(int, input().split())
        print(dfs([], n, k))

if __name__ == '__main__':
    main()
