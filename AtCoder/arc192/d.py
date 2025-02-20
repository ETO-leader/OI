from math import sqrt

MOD = 998244353

def isprime(x):
    for i in range(2, min((int)(sqrt(x)) + 3, x)):
        if x % i == 0: return False
    return True

def main():
    n = int(input())
    a = list(map(int, input().split()))

    ans = 1

    for x in range(2, max(a) + 1):

        if not isprime(x): continue
        
        c = [0] * (n - 1)
        for i in range(n - 1):
            while a[i] % x == 0:
                a[i] //= x 
                c[i] += 1

        s = sum(c)

        if s:
            
            powx = [1] * (s + 1)
            for i in range(1, s + 1):
                powx[i] = powx[i - 1] * x

            f = [[powx[i], 0] for i in range(s + 1)]
            f[0] = [0, 1]

            for cw in c:

                nf = [[0, 0] for i in range(s + 1)]
            
                for w in range(s + 1):
                    # current type = 0
                    if w > cw - 1:
                        nxt = 1 if w == cw else 0
                        nf[w - cw][nxt] += f[w][0] * powx[w - cw]
                        nf[w - cw][nxt] %= MOD
                        nf[w - cw][1] += f[w][1] * powx[w - cw]
                        nf[w - cw][1] %= MOD
                    #current type = 1
                    if w + cw < s + 1 and cw:
                        nf[w + cw][0] += f[w][0] * powx[w + cw]
                        nf[w + cw][0] %= MOD
                        nf[w + cw][1] += f[w][1] * powx[w + cw]
                        nf[w + cw][1] %= MOD

                f = nf

            def getans_f():
                nonlocal f
                res = 0
                for ax, bx in f: res += bx
                return res

            ans *= getans_f()
            ans %= MOD

    print(ans)

if __name__ == '__main__':
    main()
