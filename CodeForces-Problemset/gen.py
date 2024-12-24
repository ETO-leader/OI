from random import randint

N = 100000

def main():
    print(N)
    for i in range(N):
        print(randint(1, 200000), end=' ')
    print()
    print(N)
    for i in range(N):
        print(randint(1, N), randint(1, N), end=' ')

if __name__ == '__main__':
    main()
