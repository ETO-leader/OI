from collections import deque

def main():
    n, d = map(int, input().split())
    q = deque[tuple]()
    cnt = 0
    usum = 0
    ans = 0
    for i in range(n):
        pos, op = map(int, input().split())
        while len(q) > 0 and q[0][0] + d < pos:
            usum -= q[0][1]
            q.popleft()
        if op == 0:
            cnt += 1
        else:
            ans += cnt * len(q) - usum
            usum += cnt
            q.append((pos, cnt))
    print(ans)

if __name__ == '__main__':
    main()

