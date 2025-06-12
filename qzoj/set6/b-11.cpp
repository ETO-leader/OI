#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class dsu{
private:
    vector<int> f;
public:
    int findset(int u){
        return f[u]==u?u:(f[u]=findset(f[u]));
    }
    void merge(int u,int v){
        f[findset(u)]=findset(v);
    }
    dsu(int _n):f(_n){iota(f.begin(),f.end(),0);}
};
tuple<int,int,char> split(string s){
    const auto op=count(s.begin(),s.end(),'=')?'=':'<';
    const auto p=find(s.begin(),s.end(),op)-s.begin();
    return make_tuple(atoi(s.substr(0,p).data()),atoi(s.substr(p+1,(int)(s.size())-p-1).data()),op);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int k,n,m;cin>>k>>n>>m;
    dsu sim(n);
    vector<pair<int,int>> es;
    cir(i,0,m){
        string s;cin>>s;
        auto[u,v,op]=split(s);
        --u;--v;
        if(op=='=') sim.merge(u,v);
        else es.emplace_back(u,v);
    }
    // Topsort
    const auto ans=[&]{
        vector<int> imp(n);
        cir(i,0,n) imp[sim.findset(i)]=true;
        vector<vector<int>> gr(n);
        for(auto&[u,v]:es) gr[sim.findset(u)].emplace_back(sim.findset(v));
        vector<int> ans(n,-1),cnt(n),ord;
        for(auto&x:gr) for(auto&i:x) ++cnt[i];
        queue<int> q;
        cir(i,0,n) if(imp[i]&&(!cnt[i])) q.emplace(i),ans[i]=0;
        while(!q.empty()){
            const auto u=q.front();q.pop();
            ord.emplace_back(u);
            for(auto&i:gr[u]) if(ans[i]=max(ans[i],ans[u]+1);!(--cnt[i])){
                q.emplace(i);
            }
        }
        if(*max_element(ans.begin(),ans.end())<k-1) return vector<int>(n,-1);
        reverse(ord.begin(),ord.end());
        for(auto&u:ord) if(ans[u]<k-1){
            auto mn=k;
            for(auto&i:gr[u]) if(ans[i]>-1) mn=min(mn,ans[i]);
            if(mn>ans[u]+1) ans[u]=-1;
        }
        return ans;
    }();
    cir(u,0,n){
        const auto ansu=ans[sim.findset(u)];
        cout<<(ansu==-1?"?":("K"+to_string(ansu+1)).data())<<'\n';
    }
    return 0;
}
