#include <iostream>
#include <algorithm>
#include <string.h>
#include <vector>
#include <queue>
#define lowbit(x) ((x) & (-(x)))
using namespace std;
const int inf = 0x3f3f3f3f;
const __int128 B = 5551, P = 3355779988664422213;
inline void Cmin(int &x, int y) { x = min(x, y); }
int T[2000005][4];
int ed[2000005], fail[2000005], ncnt;
int New() {
    ++ncnt; ed[ncnt] = inf; fail[ncnt] = 0;
    memset(T[ncnt], 0, sizeof T[ncnt]);
    return ncnt;
}
void Clear() { ncnt = -1; New(); }
queue<int> q;
int Insert(string str) {
    int p = 0;
    for (auto v : str) {
        int t = v - 'A';
        if (!T[p][t]) T[p][t] = New();
        p = T[p][t];
    }
    Cmin(ed[p], str.size());
    return p;
}
void Build() {
    for (int i = 0; i < 4; i++) {
        if (T[0][i]) 
            q.push(T[0][i]);
    }
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        Cmin(ed[x], ed[fail[x]]);
        for (int i = 0; i < 4; i++) {
            if (T[x][i]) 
                q.push(T[x][i]), fail[T[x][i]] = T[fail[x]][i];
            else 
                T[x][i] = T[fail[x]][i];
        }
    }
}
int c1[2000005], c2[2000005], len[2000005];
__int128 h1[2000005], h2[2000005], pw[2000005];
vector<int> vec[2000005];
bool fl[2000005][4];
void build() {
    for (int i = 0; i < 4; i++) T[0][i] ? (fl[0][i] = 1, q.push(T[0][i])) : void();
    while (!q.empty()) {
        int x = q.front(); q.pop();
        vec[fail[x]].emplace_back(x);
        for (int i = 0; i < 4; i++) T[x][i] ? (fl[x][i] = 1, q.push(T[x][i]), fail[T[x][i]] = T[fail[x]][i]) : (T[x][i] = T[fail[x]][i]);
    }
}
int n;
string str[1000005];
int stk[2000005], sz;
bool ok[1000005];
void dfs1(int x) {
    for (int v : vec[x]) {
        len[x] += len[v], len[v] = 0, c1[x] += c1[v], c1[v] = 0, h1[x] = (h1[x] + h1[v]) % P, h1[v] = 0;
        dfs1(v);
        len[x] += len[v], c1[x] += c1[v], h1[x] = (h1[x] + h1[v]) % P;
    }
}
void dfs2(int x) {
    for (int i = 0; i < 4; i++) {
        int v = T[x][i];
        if (fl[x][i]) {
            c2[x] += c2[v], c2[v] = 0, h2[x] = (h2[x] + h2[v]) % P, h2[v] = 0;
            dfs2(v);
            c2[x] += c2[v], h2[x] = (h2[x] + h2[v]) % P;
        }
    }
}
bool okk;
void dfs3(int x, int d, __int128 h) {
    if (x) {
        if ((c1[x] > 1 && c2[x]) || (c2[x] > 1 && c1[x])) okk = 1;
        else if (c1[x] == 1 && c2[x] == 1) {
            __int128 a = h1[x], b = h2[x];
            okk |= ((a + h * pw[len[x]]) % P != (b * pw[d] + h) % P);
        }
    }
    if (okk) return;
    for (int i = 0; i < 4 && !okk; i++) {
        int v = T[x][i];
        if (fl[x][i]) dfs3(v, d + 1, (h * B + i + 1) % P);
    }
}
int main() {
    pw[0] = 1;
    for (int i = 1; i <= 2000000; i++) pw[i] = pw[i - 1] * B % P;
    cin >> n; Clear();
    for (int i = 1; i <= n; i++) cin >> str[i], Insert(str[i]);
    Build();
    for (int i = 1; i <= n; i++) {
        int p = sz = 0, lst = -1;
        for (auto v : str[i]) {
            p = T[p][v - 'A']; stk[++sz] = p;
            if (ed[p] != inf) lst = ed[p], sz -= ed[p], p = stk[sz];
        }
        ok[i] = (sz || lst == (int)str[i].size());
    }
    Clear();
    for (int i = 1; i <= n; i++) ok[i] ? Insert(str[i]) : 0;
    Build();
    for (int i = 1; i <= n; i++) {
        if (!ok[i]) continue;
        int p = 0, mn = str[i].size();
        for (auto v : str[i]) p = T[p][v - 'A'], mn = min(mn, ed[p]);
        if (mn != (int)str[i].size()) return cout << "Yes\n", 0;
    }
    Clear();
    for (int i = 1; i <= n; i++) {
        if (!ok[i]) continue;
        int p = Insert(str[i]); ++c1[p], ++c2[p], len[p] = str[i].size();
        for (int j = 0; j < (int)str[i].size(); j++) h1[p] = (h1[p] * B + str[i][j] - 'A' + 1) % P;
        h2[p] = h1[p];
    }
    build();
    dfs1(0), dfs2(0);
    dfs3(0, 0, 0);
    cout << (okk ? "Yes\n" : "No\n");
    return 0;
}