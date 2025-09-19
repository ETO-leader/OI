#include <bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
static constexpr auto _inf = (int)(1e9+7);

class segment {
private:
    struct node {
        int mx, mntag, ans;
        // 改名参数以免和成员名冲突
        auto tag_val(int v){
            mntag = min(mntag, v);
            // 更新答案（如果 mx 有效并且 mntag 有改变就会反映出来）
            ans = max(ans, mx - mntag);
        }
        node(): mx(-_inf), mntag(_inf), ans(-_inf) {}
    };

    vector<node> tr;
    const int n;

    constexpr int ls(int u) const { return u << 1; }
    constexpr int rs(int u) const { return u << 1 | 1; }

    void push_down(int u){
        if(tr[u].mntag == _inf) return; // 若没有懒标记则直接返回，避免不必要计算
        tr[ls(u)].tag_val(tr[u].mntag);
        tr[rs(u)].tag_val(tr[u].mntag);
        tr[u].mntag = _inf;
    }

    void maintain(int u){
        tr[u].mx = max(tr[ls(u)].mx, tr[rs(u)].mx);
        tr[u].ans = max(tr[ls(u)].ans, tr[rs(u)].ans);
    }

    void update_a(int u, int l, int r, int p, int w){
        if(l == r){
            tr[u].mx = w;
            // 关键：叶子被设置 mx 后，需要根据已有的 mntag 重新计算 ans
            // tr[u].ans = max(tr[u].ans, tr[u].mx - tr[u].mntag);
            return;
        }
        const auto mid = (l + r) >> 1;
        push_down(u);
        if (p <= mid) update_a(ls(u), l, mid, p, w);
        else update_a(rs(u), mid + 1, r, p, w);
        maintain(u);
    }

    void update_t(int u, int l, int r, int ql, int qr, int w){
        if(qr < l || r < ql) return;
        if(ql <= l && r <= qr){
            tr[u].tag_val(w);
            return;
        }
        const auto mid = (l + r) >> 1;
        push_down(u);
        update_t(ls(u), l, mid, ql, qr, w);
        update_t(rs(u), mid + 1, r, ql, qr, w);
        maintain(u);
    }

    int query_inner(int u, int l, int r, int ql, int qr){
        if(r < ql || qr < l) return -_inf; // 返回极小值以便 max 合并正确
        if(ql <= l && r <= qr) return tr[u].ans;
        const auto mid = (l + r) >> 1;
        push_down(u);
        return max(query_inner(ls(u), l, mid, ql, qr),
                   query_inner(rs(u), mid + 1, r, ql, qr));
    }

public:
    segment(int _n): n(_n), tr(_n << 2) {}

    void update_a(int p, int w){
        update_a(1, 0, n - 1, p, w);
    }
    void update_t(int l, int r, int w){
        if(l <= r) update_t(1, 0, n - 1, l, r, w);
    }
    int query(int l, int r){
        if(!(l <= r)) return -1;
        int res = query_inner(1, 0, n - 1, l, r);
        if(res == -_inf) return -1; // 没有可区分对
        return res;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; if(!(cin >> n)) return 0;
    vector<tuple<int,int,int>> a(n);
    for(auto &t : a) cin >> get<0>(t) >> get<1>(t) >> get<2>(t);
    int q; cin >> q;
    vector<int> ans(q, -1);
    vector<vector<pair<int,int>>> qry(n);
    cir(i,0,q){
        int L,R; cin >> L >> R; --L; --R;
        qry[R].emplace_back(L,i);
    }

    auto calc = [&](void){
        segment sg(n);
        vector<vector<int>> tags(n), rtags(n);
        cir(i,0,n){
            const auto & [x,l,r] = a[i];
            // 将已经“激活”的前序点加载到树上
            for(auto c : tags[i]) sg.update_a(c, get<0>(a[c]));
            // 将需要移除的点设为 -inf（代表不在集合内）
            for(auto c : rtags[i]) sg.update_a(c, -_inf);
            // 对能与 i 区分的前序点区间施加懒标记（把后点的 x 作为候选最小值）
            int L = max(i - r, 0);
            int R = i - l;
            if(L <= R) sg.update_t(L, R, x);
            // 计划什么时候把当前点 i 加入/移出激活集合
            if(i + l < n) tags[i + l].emplace_back(i);
            if(i + r + 1 < n) rtags[i + r + 1].emplace_back(i);
            // 回答以 i 为右端点的所有询问
            for(auto &pr : qry[i]){
                int ql = pr.first, id = pr.second;
                int val = sg.query(ql, i);
                if(val > ans[id]) ans[id] = val;
            }
        }
    };

    // 正负两次计算以覆盖 |xi - xj|
    calc();
    for(auto &t : a) get<0>(t) = -get<0>(t);
    calc();

    for(auto v : ans) cout << v << '\n';
    return 0;
}
