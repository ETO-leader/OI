#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
class graph{
private:
    vector<vector<int>> gr;
    vector<int> dfn,low,scc,inst,stc;
    int dcnt,scnt;
    auto tarjan(int u)->void{
        dfn[u]=low[u]=++dcnt;
        inst[u]=true;
        stc.emplace_back(u);
        for(auto&i:gr[u]){
            if(!dfn[i]) tarjan(i),low[u]=min(low[u],low[i]);
            else if(inst[i]) low[u]=min(low[u],dfn[i]);
        }
        if(dfn[u]==low[u]){
            ++scnt;
            auto ux=-1;
            while(ux!=u){
                ux=stc.back();stc.pop_back();
                inst[ux]=false;
                scc[ux]=scnt;
            }
        }
    }
public:
    auto link(int u,int v){
        gr[u].emplace_back(v);
    }
    auto init(){
        cir(i,0,(int)(gr.size())) if(!dfn[i]) tarjan(i);
    }
    auto sccof(int u){return scc[u];}
    graph(int _n):gr(_n),dfn(_n),low(_n),scc(_n),inst(_n),dcnt(0),scnt(-1){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int n,k,q;cin>>n>>k>>q;
        graph gr(n);
        vector<vector<int>> uq;
        cir(i,0,k){
            vector<int> a(n);
            for(auto&x:a) cin>>x,--x;
            cir(i,1,n) gr.link(a[i-1],a[i]);
            uq.emplace_back(a);
        }
        gr.init();
        auto lasans=0;
        cir(i,0,q){
            int a,l,r;cin>>a>>l>>r;
            // (a+=lasans)%=k;
            // (l+=lasans)%=n;
            // (r+=lasans)%=n;
            unordered_map<int,int> cnt;
            cir(i,l,r+1) ++cnt[gr.sccof(uq[a][i])];
            auto ans=0ll;
            for(auto&[w,z]:cnt) ans+=(int64_t)(z)*(z-1)/2;
            cout<<(lasans=ans)<<'\n';
        }
    }();
    return 0;
}
