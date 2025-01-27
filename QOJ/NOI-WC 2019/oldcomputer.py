from os import system
from sys import argv
from sys import stderr
from random import randint
from queue import Queue as queue

class Commands:

    def __init__(self):
        self.curline = 0
        self.tags = dict()

    def Select(self, id):
        self.curline += 1
        print(f"node {id}")

    def Copy(self, a, b):
        self.curline += 1
        print(f"mov {a} {b}")

    def Operator(self, op, reg, val):
        self.curline += 1
        print(f"{op} {reg} {val}")

    def Goto(self, line):
        self.curline += 1
        print(f"jmp {line}")

    def If_Goto(self, reg, line):
        self.curline += 1
        print(f"jz {reg} {line}")

    def Ifnot_Goto(self, reg, line):
        self.curline += 1
        print(f"jnz {reg} {line}")

    def Ifgreater_Goto(self, reg, line):
        self.curline += 1
        print(f"jgz {reg} {line}")

    def Ifless_Goto(self, reg, line):
        self.curline += 1
        print(f"jsz {reg} {line}")

    def read(self, reg, inf = 0):
        self.curline += 1
        print(f"read {inf} {reg}")

    def write(self, reg, inf = 0):
        self.curline += 1
        print(f"write {reg} {inf}")
    
    def makeTag(self, key):
        self.tags[key] = self.curline

    def getTag(self, key):
        return self.tags[key]

cmd = Commands()

class Task1:

    def main(self):
        cmd.Select(1)
        cmd.read('a')
        cmd.write('a')

class Task2:

    def main(self):
        cmd.Select(1)
        cmd.read('a')
        cmd.Operator('add', 'a', 4)
        cmd.Goto('a')
        f = [0] * 50
        f[1] = 1
        for i in range(2, 50): f[i] = f[i - 1] + f[i - 2]
        for i in range(50):
            if f[i] > 10 ** 9: break
            cmd.write(f[i])

class Task3:
    
    def bfs(self, ux, N, es):
        f = [0] * N
        vis = [False] * N
        dis = [10 ** 9] * N
        dis[ux] = 0
        vis[ux] = True
        q = queue()
        q.put(ux)
        while not q.empty():
            u = q.get()
            for v in es[u]:
                if vis[v]: continue
                vis[v] = True
                dis[v] = dis[u] + 1
                f[v] = u
                q.put(v)
        return f

    def main(self):
        CaseID, N, M = map(int, input().split())
        es = [[] for _ in range(N)]
        for _ in range(M):
            u, v = map(int, input().split())
            u -= 1
            v -= 1
            es[u].append(v)
            es[v].append(u)
        f = self.bfs(0, N, es)
        fr = [N - 1]
        u = N - 1
        while u:
            u = f[u]
            fr.append(u)
        fr.reverse()
        L = len(fr)
        cmd.Select(fr[0] + 1)
        cmd.read('a')
        cmd.write('a', fr[1] + 1)
        for i in range(1, L - 1):
            cmd.Select(fr[i] + 1)
            cmd.read('a', fr[i - 1] + 1)
            cmd.write('a', fr[i + 1] + 1)
        cmd.Select(fr[L - 1] + 1)
        cmd.read('a', fr[L - 2] + 1)
        cmd.write('a')

class Task4:
    
    def bfs(self, ux, N, es):
        vis = [False] * N
        dis = [10 ** 9] * N
        q = queue()
        for u in ux:
            q.put(u)
            dis[u] = 0
            vis[u] = True
        while not q.empty():
            u = q.get()
            for v in es[u]:
                if vis[v]: continue
                vis[v] = True
                dis[v] = dis[u] + 1
                q.put(v)
        return dis

    def main(self):
        CaseID, N, M = map(int, input().split())
        es = [[] for _ in range(N)]
        for _ in range(M):
            u, v = map(int, input().split())
            u -= 1
            v -= 1
            es[u].append(v)
            es[v].append(u)
        dis = self.bfs(list(range(50, 100)), N, es)
        cur = queue()
        msg = [[] for _ in range(N)]
        for u in range(50):
            cur.put(u)
            msg[u].append((0, -1))
        while not cur.empty():
            u = cur.get()
            cmd.Select(u + 1)
            v = -1
            for vx in es[u]:
                if dis[u] == dis[vx] + 1:
                    v = vx
            msg[u].sort()
            for t, fr in msg[u]:
                cmd.read('a', fr + 1)
                cmd.write('a', v + 1)
                msg[v].append((t + 1, u))
            if v > -1:
                cur.put(v)

def main():
    if argv[1] == 'task1':
        Task1().main()
    elif argv[1] == 'task2':
        Task2().main()
    elif argv[1] == 'task3':
        Task3().main()
    elif argv[1] == 'task4':
        Task4().main()
    else:
        system('g++ gen-5.cpp -O2 -o gen-5 -Wall -Wextra -Wshadow -Wconversion -W -fsanitize=address,undefined -g -std=c++26')
        system('./gen-5')

if __name__ == '__main__':
    main()
