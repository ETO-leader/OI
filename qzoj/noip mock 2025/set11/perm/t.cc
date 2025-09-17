#include <bits/stdc++.h>
using namespace std;
#define cir(i,a,b) for(int i=(a); i<(b); ++i)

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int sid, T;
    if(!(cin >> sid >> T)) return 0;
    while(T--){
        int n; cin >> n;
        int N = 1 << n;
        vector<int> a(N);
        for(int i = 0; i < N; ++i) cin >> a[i];
        vector<int> pos(N);
        for(int i = 0; i < N; ++i) pos[a[i]] = i;

        long long ans = LLONG_MAX;

        for(int shift = 0; shift < n; ++shift){
            // 关键修复：用 tmp 做分治，避免修改 pos 本身
            vector<int> tmp = pos;

            vector<long long> cnt(n, 0), tot(n, 0);
            vector<int> L, R;

            auto dfs = [&](auto self, int bit, auto lf, auto rg) -> void {
                if (rg - lf < 2 || bit < 0) return;
                int pcnt = 0;
                L.clear(); R.clear();
                for (auto it = lf; it != rg; ++it){
                    int val = *it;
                    if ((val >> bit) & 1){
                        ++pcnt;
                        R.push_back(val);
                    } else {
                        cnt[bit] += pcnt;
                        L.push_back(val);
                    }
                }
                tot[bit] += 1LL * L.size() * R.size();
                auto it = lf;
                for (int i = 0; i < (int)L.size(); ++i) *it++ = L[i];
                for (int i = 0; i < (int)R.size(); ++i) *it++ = R[i];
                auto mid = lf + (int)L.size();
                self(self, bit - 1, lf, mid);
                self(self, bit - 1, mid, rg);
            };

            dfs(dfs, n - 1, tmp.begin(), tmp.end()); // 注意：传 tmp 的迭代器

            long long cur = 0;
            for (int i = 0; i < n; ++i) cur += min(cnt[i], tot[i] - cnt[i]);
            ans = min(ans, cur);

            // 在 pos 上执行循环左移，为下一次 shift 做准备（不在 tmp 上）
            for (auto &v : pos){
                int high = (v >> (n - 1)) & 1;
                v = ((v << 1) | high) & ((1 << n) - 1);
            }
        }

        cout << ans << '\n';
    }
    return 0;
}
