#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
using lint=long long;
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
class blocks{
private:
    static constexpr auto b=3;
    const int n;
    vector<vector<lint>> c,pre;
    vector<lint> cnt;
    vector<int> a;
    auto init(){
        for(auto i=0;i<n+1;i+=b){
            const auto u=i/b;
            auto cur=0ll;
            for(auto p=i-1;~p;--p){
                cur+=cnt[a[p]];
                ++cnt[a[p]];
                c[u][p]=cur;
            }
            pre[u]=cnt;
            ranges::fill(cnt,0);
        }
    }
public:
    auto query(int l,int r){
        if(r-l+1<b+7){
            auto cur=0ll;
            cir(i,l,r+1){
                cur+=cnt[a[i]];
                ++cnt[a[i]];
            }
            cir(i,l,r+1) cnt[a[i]]=0;
            return cur;
        }
        const auto u=(l+b-1)/b,ul=u-1,ur=r/b;
        auto ans=c[ur][l];
        auto&ucnt=pre[ur];
        cir(i,max(ul,0)*b,l) --ucnt[a[i]];
        cir(i,ur*b,r+1){
            ans+=(ucnt[a[i]]-(ul>-1?pre[ul][a[i]]:0));
            ++ucnt[a[i]];
        }
        cir(i,ur*b,r+1) --ucnt[a[i]];
        cir(i,max(ul,0)*b,l) ++ucnt[a[i]];
        return ans;
    }
    blocks(vector<int> _a):
        n(_a.size()),
        c(_a.size()/b+2,vector<lint>(_a.size())),
        pre(_a.size()/b+2,vector<lint>(_a.size())),
        a(_a),
        cnt(_a.size()){
        init();
    }
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
        auto lasans=0ll;
        for(auto&x:uq) for(auto&i:x) i=gr.sccof(i);
        vector<blocks> blc;
        cir(i,0,k) blc.emplace_back(uq[i]);
        cir(i,0,q){
            lint a,l,r;cin>>a>>l>>r;
            (a+=lasans)%=k;
            (l+=lasans)%=n;
            (r+=lasans)%=n;
            const auto ans=blc[a].query(l,r);
            cout<<(lasans=ans)<<'\n';
        }
    }();
    return 0;
}

