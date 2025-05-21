#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
const int N = 1e7 + 5;
const int MX = 0x7fffffff;
int n, m, xx, W, pans, jans, pcnt, jcnt, idx;
pair<int, int> e;
int H[N], E[N], NE[N], C[N];
map<pair<int, int>, int> EDGE;
struct dsu
{
    int fa[N];
    int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
    void merge(int x, int y)
    {
        x = find(x);
        y = find(y);
        if (x != y)
            fa[x] = y;
    }
    void init()
    {
        for (int i = 1; i <= n; i++)
            fa[i] = i;
    }
} d;
bool check(int k)
{
    d.init();
    for (int i = 1; i <= n; i++)
    {
        for (int j = H[i]; ~j; j = NE[j])
        {
            int kkk = E[j];
            if (!(C[j] & ~k))
                d.merge(i, kkk);
        }
    }
    int f = d.find(1);
    for (int i = 2; i <= n; i++)
    {
        if (d.find(i) != f)
            return false;
    }
    return true;
}
void add(int u, int v, int w, bool tp)
{
    if (EDGE.count(make_pair(u, v)))
    {
        if (MX - C[EDGE[make_pair(u, v)]] < w)
            quitf(_wa, "A");
        C[EDGE[make_pair(u, v)]] += w;
    }
    else
    {
        if (tp)
            quitf(_wa, "A");
        E[idx] = v, C[idx] = w, EDGE[make_pair(u, v)] = idx, NE[idx] = H[u], H[u] = idx++;
    }
}
int main(int argc, char **argv)
{
    registerTestlibCmd(argc, argv);
    memset(H, -1, sizeof H);
    W = inf.readInt();
    n = inf.readInt();
    m = inf.readInt();
    xx = inf.readInt();
    for (int i = 1; i <= n; i++)
    {
        int x = inf.readInt(), y = inf.readInt();
    }
    for (int i = 1; i <= m; i++)
    {
        int u = inf.readInt();
        int v = inf.readInt();
        int w = inf.readInt();
        add(u, v, w, 0);
        add(v, u, w, 0);
    }
    pans = ouf.readInt();
    jans = ans.readInt();
    for (int i = 1; i <= pans; i++)
    {
        int u = ouf.readInt();
        int v = ouf.readInt();
        int w = ouf.readInt();
        add(u, v, w, 1);
        add(v, u, w, 1);
        pcnt += __builtin_popcount(w);
    }
    for (int i = 1; i <= jans; i++)
    {
        int u = ans.readInt();
        int v = ans.readInt();
        int w = ans.readInt();
        jcnt += __builtin_popcount(w);
    }
    if (pans > 10000 || pans < 0)
        quitf(_wa, "A");
    int now = 0x7fffffff;
    for (int b = 30; b >= 0; b--)
    {
        if (check(now - (1 << b)))
            now = now - (1 << b);
    }
    if (now > xx)
    {
        if (jcnt > pcnt)
            quitf(_fail, "Oh, there is something wrong with the std program...");
        else if (jcnt == pcnt)
            quitf(_ok, "Your answer is correct. Congratulations!");
        else
            quitp(max(1 - 1.0 * (pcnt - jcnt) / (jcnt)*W, 0.0), "B %d %d", pcnt, jcnt);
    }
    else
    {
        quitf(_wa, "C");
    }
}