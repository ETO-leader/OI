from sys import stdout

class interactor:
    
    @staticmethod
    def ask(u : int, k : int, a : set | list):
        print('?', u + 1, k, len(a), *list(map(lambda x : x + 1, a)))
        stdout.flush()
        return int(input())
    
    @staticmethod
    def answer(a : set | list):
        print('!', len(a), *list(map(lambda x : x + 1, a)))
        stdout.flush()

def jmpkth(u : int, k : int, n : int):
    l = 0
    r = n - 1
    ans = -1
    while l - 1 < r:
        mid = (l + r) // 2
        if interactor.ask(u, k, [i for i in range(mid + 1)]):
            r = mid - 1
            ans = mid
        else:
            l = mid + 1
    return ans

def main():
    n = int(input())
    u = jmpkth(0, 10086, n)
    c = 64
    S = {u}
    
    for i in range(c - 1):
        S.add(jmpkth(u, i + 1, n))
    
    def extend(nc : int):
        nonlocal n, S
        lsiz = len(S)
        for i in range(n):
            if i not in S and interactor.ask(i, nc, S):
                S.add(i)
        if len(S) - lsiz < nc: return False
        return True

    while True:
        if not extend(c):
            break
        c *= 2

    for i in range(n):
        if i not in S and interactor.ask(i, 10086, S):
            S.add(i)
    
    interactor.answer(S)

if __name__ == '__main__':
    main()

