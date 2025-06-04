def runcase():
    n = int(input())
    A = [[int(x) for x in input()] for _ in range(n)]
    R = list(map(int, input().split()))
    C = list(map(int, input().split()))
    st_row = [0] * n
    st_col = [0] * n

    def flip_row(x):
        nonlocal n, A
        st_row[x] ^= 1
        for i in range(n):
            A[x][i] ^= 1

    def flip_col(x):
        nonlocal n, A
        st_col[x] ^= 1
        for i in range(n):
            A[i][x] ^= 1
    
    def col_sum(x):
        nonlocal n, A
        res = 0
        for i in range(n):
            res += A[i][x]
        return res

    for i in range(n):
        if A[0][i]: flip_col(i)
    
    for i in range(n):
        if sum(A[i]) > (n - 1) // 2: flip_row(i)

    for i in range(n):
        if col_sum(i) > (n - 1) // 2: flip_col(i)

    for i in range(n):
        if sum(A[i]) != R[i]:
            print('No')
            return
        
    for i in range(n):
        if col_sum(i) != C[i]:
            print('No')
            return
    
    print('Yes')
    print(*st_row, sep = '')
    print(*st_col, sep = '')

def main():
    T = int(input())
    for i in range(T):
        runcase()

if __name__ == '__main__':
    main()
