#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e4+10;

int main() {
    freopen("grandiloquence.in", "r", stdin);
    freopen("grandiloquence.out", "w", stdout);
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int tp, n, m, k;
    cin >> tp;
    cin >> n >> m >> k;
    int tot_node = n;
    int fa[MAXN];
    int depth[MAXN];
    int color[MAXN];
    vector<int> g[MAXN];

    for (int i = 1; i <= n; i++) {
        color[i] = -1;
    }

    for (int i = 1; i <= n; i++) {
        cin >> fa[i];
    }

    depth[1] = 0;
    for (int i = 2; i <= n; i++) {
        depth[i] = depth[fa[i]] + 1;
        g[fa[i]].push_back(i);
    }

    int last_ans = 0;
    for (int i = 0; i < m; i++) {
        int op;
        cin >> op;
        if (op == 1 || op == 2) {
            int u, c;
            cin >> u >> c;
            if (tp == 1) {
                u = u ^ last_ans;
                c = c ^ last_ans;
            }
            if (op == 2) {
                c = (c % k + k) % k;
            }
            if (op == 1) {
                queue<int> q;
                q.push(u);
                while (!q.empty()) {
                    int v = q.front();
                    q.pop();
                    int d = (depth[v] - depth[u] + c-1)%k+1;
                    int new_color = (d % k + k) % k;
                    color[v] = new_color;
                    for (int w : g[v]) {
                        q.push(w);
                    }
                }
            } else {
                int count = 0;
                queue<int> q;
                q.push(u);
                while (!q.empty()) {
                    int v = q.front();
                    q.pop();
                    if (color[v] == c) {
                        count++;
                    }
                    for (int w : g[v]) {
                        q.push(w);
                    }
                }
                cout << count << endl;
                last_ans = count;
            }
        } else {
            int u;
            cin >> u;
            if (tp == 1) {
                u = u ^ last_ans;
            }
            tot_node++;
            depth[tot_node] = depth[u] + 1;
            color[tot_node] = -1;
            g[u].push_back(tot_node);
        }
    }

    return 0;
}
