#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;vector<int> a(n),b(m);
    vector c(n,vector<int>(m));
    for(auto&i:a) cin>>i;
    for(auto&i:b) cin>>i;
    for(auto&x:c) for(auto&i:x) cin>>i;
    vector<map<vector<int>,int>> f(n+1);
    auto dfs=[&](auto __self,int p,vector<int> a,int sum,int rest,const int id){
        if(p==m) return [&]{
            if(!rest){
                if(!f[id].contains(a)) f[id][a]=sum;
                else f[id][a]=min(f[id][a],sum);
            }
        }();
        __self(__self,p+1,a,sum,rest,id);
        cir(w,0,min(a[p],rest)+1) __self(__self,p+1,[&]{
            auto res=a;res[p]-=w;
            return res;
        }(),sum+c[id-1][p],rest-w,id);
    };
    f[0][b]=0;
    cir(c,0,n) for(auto&[s,w]:f[c]) dfs(dfs,0,s,w,a[c],c+1);
    auto ans=_inf;
    for(auto&[s,w]:f[n]) ans=min(ans,w);
    println("{}",ans<_inf?ans:-1);
    return 0;
}
