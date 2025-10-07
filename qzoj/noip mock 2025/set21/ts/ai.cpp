#include <bits/stdc++.h>
using namespace std;

/*
 修复版：优先枚举首元素 v（从小到大），找第一个 feasible([v]) 成功的起点，
 然后从该起点贪心扩展 B。
 其它结构与之前的 BFS 可行性判定一致。
*/

struct State {
    int pos;
    int bpos;
    int comp; // 0 equal, 1 s1 < s2 already, 2 invalid (s1 > s2)
    int side; // 0 balanced, 1 s1 leads (queue stores s1 pending), 2 s2 leads
    string q;
    bool operator==(State const& o) const {
        return pos==o.pos && bpos==o.bpos && comp==o.comp && side==o.side && q==o.q;
    }
};

struct StateHash {
    size_t operator()(State const& s) const noexcept {
        // combine small ints then hash string
        size_t h = ((size_t)s.pos << 32) ^ ((size_t)s.bpos << 16) ^ (size_t)s.comp;
        h ^= (size_t)s.side * 0x9e3779b97f4a7c15ULL;
        uint64_t sh = 1469598103934665603ULL;
        for(char c: s.q) sh = (sh ^ (unsigned char)c) * 1099511628211ULL;
        h ^= (size_t)sh;
        return h;
    }
};

int n;
vector<int> a;
vector<vector<int>> posList;

bool has_pos_ge(int v, int start) {
    if(v < 0 || v >= (int)posList.size()) return false;
    auto &vec = posList[v];
    auto it = lower_bound(vec.begin(), vec.end(), start);
    return it != vec.end();
}

string push_q(const string &oldq, int val) {
    if(oldq.empty()) return std::to_string(val);
    string s = oldq;
    s.push_back(',');
    s += std::to_string(val);
    return s;
}

pair<string,int> pop_q(const string &q) {
    if(q.empty()) return {string(), -1};
    size_t p = q.find(',');
    if(p == string::npos) {
        int v = stoi(q);
        return {string(), v};
    } else {
        int v = stoi(q.substr(0,p));
        string rest = q.substr(p+1);
        return {rest, v};
    }
}

int cmp_after_compare(int comp, int s1val, int s2val) {
    if(comp == 1) return 1;
    if(s1val < s2val) return 1;
    if(s1val > s2val) return 2;
    return 0;
}

bool feasible(const vector<int> &B) {
    int m = (int)B.size();
    // B must be subsequence of a
    int curpos = 0;
    for(int i=0;i<m;i++){
        int val = B[i];
        if(!has_pos_ge(val, curpos)) return false;
        auto &vec = posList[val];
        auto it = lower_bound(vec.begin(), vec.end(), curpos);
        curpos = (*it) + 1;
    }

    deque<State> dq;
    unordered_set<State, StateHash> vis;
    State init{0, 0, 0, 0, ""};
    dq.push_back(init);
    vis.insert(init);

    while(!dq.empty()) {
        State s = dq.front(); dq.pop_front();
        if(s.comp == 2) continue;
        if(s.pos == n) {
            if(s.bpos != m) continue;
            if(s.comp == 1) return true;
            int s2len = s.bpos;
            int s1len = s.pos - s.bpos;
            if(s1len <= s2len) return true;
            else continue;
        }

        int pos = s.pos;
        int bpos = s.bpos;
        int comp = s.comp;
        int side = s.side;
        string q = s.q;
        int cur = a[pos];

        // put cur into s1
        {
            State ns = s;
            ns.pos = pos + 1;
            if(ns.side == 0) {
                ns.side = 1;
                ns.q = push_q("", cur);
            } else if(ns.side == 1) {
                ns.q = push_q(ns.q, cur);
            } else { // ns.side == 2
                auto pr = pop_q(ns.q);
                string newq = pr.first;
                int s2val = pr.second;
                int newcomp = cmp_after_compare(ns.comp, cur, s2val);
                if(newcomp != 2) {
                    ns.comp = newcomp;
                    if(newq.empty()) { ns.side = 0; ns.q = ""; }
                    else { ns.side = 2; ns.q = newq; }
                } else {
                    ns.comp = 2;
                }
            }
            if(ns.comp != 2) {
                if(vis.insert(ns).second) dq.push_back(ns);
            }
        }

        // put cur into s2 (only if matches next B element)
        if(bpos < m && cur == B[bpos]) {
            State ns = s;
            ns.pos = pos + 1;
            ns.bpos = bpos + 1;
            if(ns.side == 0) {
                ns.side = 2;
                ns.q = push_q("", cur);
            } else if(ns.side == 2) {
                ns.q = push_q(ns.q, cur);
            } else { // ns.side == 1
                auto pr = pop_q(ns.q);
                string newq = pr.first;
                int s1val = pr.second;
                int newcomp = cmp_after_compare(ns.comp, s1val, cur);
                if(newcomp != 2) {
                    ns.comp = newcomp;
                    if(newq.empty()) { ns.side = 0; ns.q = ""; }
                    else { ns.side = 1; ns.q = newq; }
                } else {
                    ns.comp = 2;
                }
            }
            if(ns.comp != 2) {
                if(vis.insert(ns).second) dq.push_back(ns);
            }
        }
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if(!(cin>>T)) return 0;
    while(T--) {
        cin >> n;
        a.assign(n,0);
        int maxv = 0;
        for(int i=0;i<n;i++){
            cin >> a[i];
            maxv = max(maxv, a[i]);
        }
        posList.assign(maxv+1, {});
        for(int i=0;i<n;i++) posList[a[i]].push_back(i);

        vector<int> vals;
        {
            vector<char> seen(maxv+1, 0);
            for(int x: a) if(!seen[x]) { seen[x]=1; vals.push_back(x); }
            sort(vals.begin(), vals.end());
        }

        vector<int> answer;

        // Try each possible first element v in ascending order; for first v that is feasible, start greedy from it.
        bool foundStart = false;
        for(int v : vals) {
            // quick check: v must have occurrence from 0
            if(!has_pos_ge(v, 0)) continue;
            vector<int> B;
            B.push_back(v);
            if(!feasible(B)) continue; // not a valid start
            // start with this B and greedily extend
            foundStart = true;
            while(true) {
                bool extended = false;
                // compute earliest position after matching current B (for quick pruning)
                int curpos = 0;
                for(int i=0;i<(int)B.size();i++){
                    auto &vec = posList[B[i]];
                    auto it = lower_bound(vec.begin(), vec.end(), curpos);
                    if(it==vec.end()){ curpos = n+1; break; }
                    curpos = (*it) + 1;
                }
                for(int w : vals) {
                    if(!has_pos_ge(w, curpos)) continue;
                    B.push_back(w);
                    if(feasible(B)) { extended = true; break; }
                    B.pop_back();
                }
                if(!extended) break;
            }
            answer = B;
            break;
        }

        if(!foundStart) {
            // fallback: put all into s2 (always valid)
            answer = a;
        }

        cout << (int)answer.size() << "\n";
        for(size_t i=0;i<answer.size();i++){
            if(i) cout << ' ';
            cout << answer[i];
        }
        cout << "\n";
    }
    return 0;
}
