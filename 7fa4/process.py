
if __name__ == '__main__':
    with open('inf') as data:
        edges = set((0, 0))
        edges.remove((0, 0))
        for ln in data:
            sd = ln.split()
            if sd[0] == '!': continue
            op, u, v = sd
            u, v = map(int, [u, v])
            if op == 'C': edges.remove((u, v))
            else: edges.add((u, v))

