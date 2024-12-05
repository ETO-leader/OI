#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class tree{
private:
    vector<vector<int>> gr;
    vector<int> col,siz;
    vector<vector<pair<int,int>>> cntw;
    auto init(int u,int f=-1)->int{
        if(f>-1) gr[u].erase(find(gr[u].begin(),gr[u].end(),f));
        siz[u]=1;
        for(auto&i:gr[u]) siz[u]+=init(i,u);
        return siz[u];
    }
    auto dfs(int u,map<int,int>&cur,map<int,int>&cnt){
        if(gr[u].empty()){
            ++cur[1];cnt[col[u]]=1;
            for(auto&x:cur) cntw[u].emplace_back(x);
            return;
        }
        sort(gr[u].begin(),gr[u].end(),[this](int a,int b){
            return siz[a]>siz[b];
        });
        dfs(gr[u][0],cur,cnt);
        --cur[cnt[col[u]]];
        if(!cur[cnt[col[u]]]) cur.erase(cnt[col[u]]);
        ++cur[++cnt[col[u]]];
        for(auto&i:gr[u]) if(i!=gr[u][0]){
            map<int,int> curx,cntv;
            dfs(i,curx,cntv);
            for(auto&[c,x]:cntv){
                --cur[cnt[c]];
                if(!cur[cnt[c]]) cur.erase(cnt[c]);
                cnt[c]+=x;
                ++cur[cnt[c]];
            }
        }
        for(auto&x:cur) cntw[u].emplace_back(x);
    }
public:
    auto link(int u,int v){
        gr[u].push_back(v);
        gr[v].push_back(u);
    }
    auto initcol(auto c){col=c;}
    auto init(){
        init(0);
        map<int,int> cur,cnt;
        dfs(0,cur,cnt);
    }
    auto check(int u,int k){
        auto res=0;
        for(auto&[w,c]:cntw[u]) res+=c*(w>k-1);
        return res;
    }
    tree(int _n):gr(_n),siz(_n),cntw(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,q;cin>>n>>q;vector<int> col(n);
    for(auto&i:col) cin>>i;
    tree tr(n);
    tr.initcol(col);
    cir(i,0,n-1){
        int u,v;cin>>u>>v;--u;--v;
        tr.link(u,v);
    }
    tr.init();
    cir(i,0,q){
        int u,k;cin>>u>>k;--u;
        println("{}",tr.check(u,k));
    }
    return 0;
}
