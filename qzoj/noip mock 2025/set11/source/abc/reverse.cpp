#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> PII;
struct Fentree{
    vector<int> tree;
    int size;
    Fentree(int n):size(n),tree(n+2,0){}
    void update(int idx, int delta){
        for (;idx<=size;idx+=idx&-idx){
            tree[idx] += delta;
        }
    }
    int query(int idx){
        int res=0;
        for (;idx>0;idx-=idx&-idx){
            res += tree[idx];
        }
        return res;
    }
};

struct Query {
    int l,r,idx;
};
int count_in(const vector<int>& A, int n) {
    Fentree ft(n);
    int inv = 0;
    for (int i = n; i >= 1; --i) {
        inv += ft.query(A[i] - 1);
        ft.update(A[i], 1);
    }
    return inv;
}

pair<vector<int>, vector<PII> > fun(const vector<int>& A, int n) {
    int q = n * (n + 1) / 2;
    vector<Query> queries(q);
    vector<pair<int, int>> lr_pairs(q);
    int idx = 0;
    for (int l = 1; l <= n; ++l) {
        for (int r = l; r <= n; ++r) {
            queries[idx] = {l, r, idx};
            lr_pairs[idx] = {l, r};
            idx++;
        }
    }
    
    int block_size = sqrt(n) + 1;
    sort(queries.begin(), queries.end(), [block_size](const Query& a, const Query& b) {
        if (a.l / block_size != b.l / block_size) {
            return a.l < b.l;
        }
        return (a.l / block_size % 2) ? (a.r > b.r) : (a.r < b.r);
    });
    
    vector<int> cnt(q, 0);
    int cur_l = 1, cur_r = 0;
    int cur_cnt = 0;
    Fentree ft(n);
    
    for (const auto& query : queries) {
        int l = query.l;
        int r = query.r;
        int idx = query.idx;
        
        while (cur_r < r) {
            cur_r++;
            int greater = (cur_r - cur_l) - ft.query(A[cur_r]);
            cur_cnt += greater;
            ft.update(A[cur_r], 1);
        }
        
        while (cur_r > r) {
            ft.update(A[cur_r], -1);
            int greater = (cur_r - cur_l) - ft.query(A[cur_r]);
            cur_cnt -= greater;
            cur_r--;
        }
        
        while (cur_l > l) {
            cur_l--;
            int less = ft.query(A[cur_l] - 1);
            cur_cnt += less;
            ft.update(A[cur_l], 1);
        }
        
        while (cur_l < l) {
            ft.update(A[cur_l], -1);
            int less = ft.query(A[cur_l] - 1);
            cur_cnt -= less;
            cur_l++;
        }
        
        cnt[idx] = cur_cnt;
    }
    
    return {cnt, lr_pairs};
}
pair<pair<int, int>, int> find_first_operation(const vector<int>& A, int n) {
    for (int i = 1; i < n; ++i) {
        if (A[i] > A[i + 1]) {
            return {{i, i + 1}, 1};
        }
    }
    return {{1, 1}, 0};
}
vector<int> sort_in(const vector<int>& A, int L, int R) {
    vector<int> B = A;
    sort(B.begin() + L, B.begin() + R + 1);
    return B;
}

int main() {
    int n, k,id;
    cin>>id>>n>>k;
    vector<int>a(n + 1);
    for (int i=1;i<=n;i++){
        cin>>a[i];
    }
    int inv=count_in(a, n);
    int target=inv-k;
    if (target==0) {
        cout <<"0\n";
        return 0;
    }
    pair<vector<int>, vector<pair<int, int>>> result = fun(a, n);
	vector<int> cnt = result.first; 
	vector<pair<int, int>> lr_pairs = result.second;
    for (int i = 0; i < cnt.size(); ++i) {
        if (cnt[i] == target) {
            cout << "1\n";
            cout << lr_pairs[i].first+1 << " " << lr_pairs[i].second +1<< "\n";
            return 0;
        }
    }
    
    pair<pair<int, int>, int> first_result = find_first_operation(a, n);
	pair<int, int> first_interval = first_result.first;
	int x = first_result.second;
	
    int L1 = first_interval.first, R1 = first_interval.second;
    
	vector<int> A_after_first = sort_in(a, L1, R1);
    int inv_after_first = count_in(A_after_first, n);
    int y = inv_after_first - k;
    
	pair<vector<int>, vector<pair<int, int>>> result_after =fun(A_after_first, n);
	vector<int> cnt_after = result_after.first;
	vector<pair<int, int>> lr_pairs_after = result_after.second;
    
	for (int i = 0; i < cnt_after.size(); ++i) {
        if (cnt_after[i] == y) {
            cout << "2\n";
            cout << L1 << " " << R1 << "\n";
            cout << lr_pairs_after[i].first+1 << " " << lr_pairs_after[i].second+1 << "\n";
            return 0;
        }
    }
     return 0;
}
    
