#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int n, m;
        long long k;
        cin >> n >> m >> k;
        vector<int> eu(m), ev(m), ec(m);
        vector<vector<pair<int,int>>> adj(n+1);
        for (int i = 0; i < m; ++i) {
            int u,v,c; cin >> u >> v >> c;
            eu[i]=u; ev[i]=v; ec[i]=c;
            adj[u].emplace_back(v,i);
            adj[v].emplace_back(u,i);
        }

        // remaining degree and removed flag for edges
        vector<int> remDeg(n+1,0);
        for (int v=1; v<=n; ++v) remDeg[v] = (int)adj[v].size();
        vector<char> removedEdge(m, 0);

        // For each vertex, map color -> count among remaining incident edges.
        // Use unordered_map and reserve to reduce rehashing.
        vector<unordered_map<int,int>> cnt(n+1);
        for (int v=1; v<=n; ++v) {
            cnt[v].reserve(adj[v].size()? (size_t)min((size_t)adj[v].size(), (size_t)8) : 0);
            for (auto &pr : adj[v]) {
                int id = pr.second;
                int color = ec[id];
                ++cnt[v][color];
            }
        }

        deque<int> q;
        vector<char> inq(n+1,0);
        for (int v=1; v<=n; ++v) {
            if (remDeg[v]>0 && cnt[v].size()==1) {
                q.push_back(v);
                inq[v]=1;
            }
        }

        int removedEdgesCount = 0;
        while (!q.empty()) {
            int v = q.front(); q.pop_front();
            inq[v]=0;
            if (remDeg[v]==0) continue; // already processed
            // v is guaranteed to have exactly one distinct color among remaining incident edges
            // remove all its remaining incident edges
            for (auto &pr : adj[v]) {
                int nb = pr.first;
                int id = pr.second;
                if (removedEdge[id]) continue;
                int color = ec[id];
                removedEdge[id] = 1;
                ++removedEdgesCount;
                // update neighbor nb
                auto it = cnt[nb].find(color);
                if (it != cnt[nb].end()) {
                    if (--(it->second) == 0) {
                        cnt[nb].erase(it);
                    }
                }
                // update remDeg
                if (remDeg[nb] > 0) --remDeg[nb];
                // if neighbor becomes good, push it
                if (remDeg[nb] > 0 && cnt[nb].size() == 1 && !inq[nb]) {
                    q.push_back(nb);
                    inq[nb]=1;
                }
            }
            // after removing edges incident to v, its remDeg becomes 0
            remDeg[v]=0;
            cnt[v].clear();
        }

        cout << (removedEdgesCount == m ? "Yes" : "No") << '\n';
    }
    return 0;
}
