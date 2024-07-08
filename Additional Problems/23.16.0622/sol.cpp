#include "iostream"
#include "algorithm"
#include "cstring"
#include "cstdio"
#include "array"
using namespace std;
#define MAXN 2006
#define P 998244353
using ary=array<array<int,MAXN>,MAXN>;
int n, m, k;
ary A,S,f11,f12,f21,f22;
void work(ary&A) {
    for (int i = 1 ; i <= n ; ++ i)
        for (int j = 1 ; j <= m ; ++ j)
            A[i][j] += ((A[i - 1][j] + A[i][j - 1]) % P - A[i - 1][j - 1] + P) % P;
}
int pw(int a, int b = k) {
    int cur = a, ans = 1;
    while (b) {
        if (b & 1)
            ans = 1ll * ans * cur % P;

        cur = 1ll * cur * cur % P, b >>= 1;
    }
    return ans;
}
int main() {
    cin >> n >> m >> k;
    for (int i = 1 ; i <= n ; ++ i)
        for (int j = 1 ; j <= m ; ++ j) {
            scanf("%1d", &(A[i][j])), S[i][j] = S[i][j - 1] + A[i][j];
        }
    for (int x = 1 ; x <= n ; ++ x)
        for (int y = 1 ; y <= m ; ++ y)
            for (int Y = y ; Y <= m && A[x][Y] ; ++ Y)
                for (int X = x ; X <= n && S[X][Y] - S[X][y - 1] == Y - y + 1 ; ++ X)
                    ++ f11[x][y], -- f11[X + 1][y], -- f11[x][Y + 1], ++ f11[X + 1][Y + 1],
                    ++ f12[x][y], -- f12[X + 1][y], -- f12[x][Y], ++ f12[X + 1][Y],
                    ++ f21[x][y], -- f21[X][y], -- f21[x][Y + 1], ++ f21[X][Y + 1],
                    ++ f22[x][y], -- f22[X][y], -- f22[x][Y], ++ f22[X][Y];
    work(f11), work(f12), work(f21), work(f22);
    int res = 0;
    for (int x = 1 ; x <= n ; ++ x)
        for (int y = 1 ; y <= m ; ++ y){
            (res += ((pw(f11[x][y]) - pw(f12[x][y]) - pw(f21[x][y]) + pw(f22[x][y])) % P + P) % P) %= P;
        }
    cout << res << endl;
}