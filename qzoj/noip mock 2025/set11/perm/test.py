import math

def op0(n : int, a : list):
    return a[2 ** (n - 1):] + a[:2 ** (n - 1)]

def op1(n : int, a : list):
    return a[1::2] + a[::2]

result = []

def dfs(n : int, L : list):
    global result
    if L in result: return
    result.append(L)
    dfs(n, op0(n, L))
    dfs(n, op1(n, L))

def main():
    L = list(map(int, input().split()))
    n = int(math.log2(len(L))+0.01)
    # orig = [i for i in L]
    # cur = 0
    # L = op1(n, L)
    # cnt = 1
    # while L != orig:
    #     cnt += 1
    #     print(cnt)
    #     if cur == 0:
    #         L = op1(n, L)
    #     else:
    #         L = op1(n, L)
    dfs(n, L)
    # print(len(result))
    result.sort()
    for x in result:
        print(x)

if __name__ == '__main__':
    main()

