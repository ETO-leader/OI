
def main():
    inf = open('inf', 'r')
    ouf = open('ouf', 'r')
    ouf.readline()
    P, n = map(int, inf.readline().split())
    x = list(map(int, inf.readline().split()))
    ans = [-1] * n
    for i in range(n - 1):
        u = x[i]
        ans[u] = int(ouf.readline().split()[0])

    print(ans)
    num = ''
    for i in ans:
        if i == 1:
            num += '0'
        elif i == 6:
            num += '1'
    print(f'number = {num}')

if __name__ == '__main__':
    main() 
