#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,k;cin>>n>>k;
    if(k<20){
        vector<vector<int>> vx(n);
        cir(i,0,n-1){
            int u,v;cin>>u>>v;--u;--v;
            vx[u].emplace_back(v);
            vx[v].emplace_back(u);
        }
        vector<int> dep(n),fr(n);
        auto dfs=[&](auto __self,int u,int f)->void {
            fr[u]=f;
            dep[u]=dep[f]+1;
            for(auto&i:vx[u]) if(i!=f) __self(__self,i,u);
        };
        vector<int> usf(n);
        vector<int> rdfn,ddep;
        auto udfs=[&](auto __self,int u,int f)->void {
            const auto p=(int)(rdfn.size());
            if(usf[u]){
                rdfn.emplace_back(u);
                ddep.emplace_back(dep[u]);
            }
            for(auto&i:vx[u]) if(i!=f&&dep[i]<k+1) __self(__self,i,u);
            if(usf[u]){
                rdfn[p]=(int)(rdfn.size())-1;
            }
        };
        dep[0]=-1;
        dfs(dfs,0,0);
        cir(i,0,n) if(dep[i]==k){
            auto x=i;
            while(x){
                usf[x]=true;
                x=fr[x];
            }
        }
        udfs(udfs,0,0);
        const auto c=(int)(rdfn.size());
        vector<vector<int>> f(c+1,vector<int>(1<<k));
        fill(f[c].begin(),f[c].end(),1);
        for(auto i=c-1;~i;--i){
            if(rdfn[i]>i) f[i]=f[i+1];
            const auto l=rdfn[i]+1;
            const auto v=1<<(ddep[i]-1);
            cir(s,0,(1<<k)) if (!(s&v)) f[i][s|v]|=f[l][s];
        }
        cout<<(f[0][(1<<k)-1]?"DA":"NE")<<'\n';
    }else{
        cout<<"DA"<<'\n';
    }
    return 0;
}
