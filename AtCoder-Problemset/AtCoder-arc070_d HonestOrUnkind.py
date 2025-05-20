from sys import stdout
from collections import deque
stack = deque

class interactor:
    
    def register(self):
        return map(int, input().split())
    
    def ask(self, u, v):
        print(f'? {u} {v}')
        stdout.flush()
        return input()

    def impossible(self):
        print('Impossible')
        stdout.flush()

    def answer(self, ans):
        print('! ', end = '')
        for x in ans: print(int(x), end = '')
        print()
        stdout.flush()

def main():
    interact = interactor()
    a, b = interact.register()
    n = a + b
    if a < b + 1:
        interact.impossible()
    else:
        stc = stack()
        for i in range(n):
            if len(stc) < 1:
                stc.append(i)
            elif interact.ask(stc[-1], i) == 'N':
                stc.pop()
            else:
                stc.append(i)
        u = stc[-1]
        ans = [False] * n
        for i in range(n):
            ans[i] = interact.ask(u, i) == 'Y'
        interact.answer(ans)

if __name__ == '__main__':
    main()
