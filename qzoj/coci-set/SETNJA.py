from sys import stderr

def main():
    s = input()
    n = len(s)
    f = 1
    c = 0
    for i in range(0, n):
        u = s[i]
        if u == '*':
            f = f * 5 + (3 ** c)
            c += 1
        elif u == 'L':
            f = f * 2
        elif u == 'R':
            f = f * 2 + (3 ** c)
    print(f)

if __name__ == '__main__':
    main()
