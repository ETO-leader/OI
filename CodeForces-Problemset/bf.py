T = int(input())

assert T == 1

N = int(input())

s = input()

vis = set()

def dfs(cs : str):
    global vis
    if cs in vis:
        return
    vis.add(cs)
    for i in range(len(cs) - 2):
        ns = ''
        if cs[i] == cs[i + 1] or cs[i] == cs[i + 2]:
            if i > 0:
                ns += cs[: i]
            ns += cs[i + 1 :]
        else:
            ns += cs[0 : i + 1] + cs[i + 2 :]
        dfs(ns)

dfs(s)

print(len(vis), vis)

