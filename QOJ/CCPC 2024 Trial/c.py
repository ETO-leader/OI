from sys import stdout

def main():
    l = 1
    r = int(1e9)
    ans = -1
    while l - 1 < r:
        mid = (l + r) // 2
        print(f'? {mid}')
        stdout.flush()
        v = int(input())
        if v:
            r = mid - 1
        else:
            l = mid + 1
            ans = mid
    print(f'! {ans}')
    stdout.flush()

if __name__ == '__main__':
    main()
