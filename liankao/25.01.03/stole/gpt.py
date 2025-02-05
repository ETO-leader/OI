import sys
from functools import lru_cache

class FileIO:
    def __init__(self, input_file, output_file):
        self.input_file = input_file
        self.output_file = output_file
        self.inf = open(input_file, "r")
        self.ouf = open(output_file, "w")

    def read(self):
        return self.inf.read()

    def write(self, data):
        self.ouf.write(data)

    def close(self):
        self.inf.close()
        self.ouf.close()

# Handle input/output using FileIO
file_io = FileIO("stole.in", "stole.out")
sys.stdin = file_io.inf
sys.stdout = file_io.ouf

class MathBase:
    def __init__(self, p):
        self.p = p

    def qpow(self, a, b):
        res = 1
        while b:
            if b & 1:
                res = res * a % self.p
            a = a * a % self.p
            b >>= 1
        return res

    def inv(self, x):
        return self.qpow(x, self.p - 2)

def main():
    input = sys.stdin.read
    data = input().split()
    n, r, p = map(int, data)
    
    math = MathBase(p)
    
    # Precompute factorials and their modular inverses
    fct = [1] * (n + 7)
    for i in range(1, n + 7):
        fct[i] = fct[i - 1] * i % p
    
    ifct = [math.inv(x) for x in fct]
    
    def C(a, b):
        if a < b:
            return 0
        return fct[a] * ifct[b] % p * ifct[a - b] % p

    m = n + 7
    f = [[0] * (m + 1) for _ in range(n + 1)]
    for w in range(1, m + 1):
        pw = [1] * (n * n + 7)
        for i in range(1, n * n + 7):
            pw[i] = pw[i - 1] * (m - w + 2) % p

        g = [[0] * (n + 1) for _ in range(n + 1)]
        g[1][0] = 1
        
        for a in range(2, n + 1):
            f[a][w] = f[a][w - 1]
            g[a][0] = f[a][w - 1]
            
            for k in range(1, n):
                for b in range(1, a):
                    for x in range(0, k):
                        g[a][k] = (g[a][k] +
                                   g[b][x] * g[a - b][k - x - 1] % p *
                                   C(a, 2) % p * C(a - 2, b - 1) % p *
                                   pw[b * (a - b) - 1]) % p
                
                g[a][k] = g[a][k] * math.inv(k) % p
                f[a][w] = (f[a][w] + g[a][k]) % p

    print(f[n][r])

if __name__ == "__main__":
    main()
    file_io.close()
