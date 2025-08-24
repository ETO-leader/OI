def main():
    T = int(input())
    for i in range(T):
        N, M = map(int, input().split())
        a = list(map(int, input().split()))
        b = list(map(int, input().split()))
        pos = 0
        for i in a:
            if pos < M and i == b[pos]:
                pos += 1
        print('Yes' if pos == M else 'No')

if __name__ == '__main__':
    main()
