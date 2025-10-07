#include <bits/stdc++.h>
using namespace std;

// 插入函数，完全按题目给出的伪代码实现
void ins(int x, int &u, vector<pair<int,int>>& a){
    if(!u){
        u = x;
        return;
    }
    if(x < u){
        a[x].first = u; // a[x][0] = u
        u = x;
        return;
    }
    swap(a[u].first, a[u].second); // swap(a[u][0], a[u][1])
    ins(x, a[u].first, a);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long P;
    if(!(cin >> n >> P)) return 0;
    vector<int> ls(n+1), rs(n+1);
    for(int i=1;i<=n;i++){
        cin >> ls[i] >> rs[i];
    }

    vector<int> perm(n);
    for(int i=0;i<n;i++) perm[i] = i+1;

    long long ans = 0;
    // 枚举所有排列（阶乘复杂度）
    do{
        // 重置斜堆的孩子数组（1..n），用 pair<left,right>
        vector<pair<int,int>> a(n+1, {0,0});
        int root = 0;
        // 依次插入
        for(int x : perm){
            ins(x, root, a);
        }
        // 比较生成的树和输入树是否完全相同（左右孩子都要一致）
        bool ok = true;
        for(int i=1;i<=n;i++){
            if(a[i].first != ls[i] || a[i].second != rs[i]){
                ok = false;
                break;
            }
        }
        if(ok){
            ans = (ans + 1) % P;
        }
    } while(next_permutation(perm.begin(), perm.end()));

    cout << (ans % P + P) % P << "\n";
    return 0;
}
