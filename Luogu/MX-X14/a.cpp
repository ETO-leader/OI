#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;
    vector info(n,vector<int>(m));
    for(auto&x:info) for(auto&i:x) cin>>i;
    cir(j,0,m){
        map<int,int> id;
        cir(i,0,n) id.emplace(info[i][j],0);
        for(auto c=-1;auto&[a,b]:id) b=++c;
        cir(i,0,n) info[i][j]=id[info[i][j]];
    }
    vector<int> ok;
    cir(i,0,m) cir(j,0,n){
        auto s=0;
        cir(x,0,n) if(info[x][i]==j) s|=(1<<x);
        ok.emplace_back(s);
    }
    vector<int> f(1<<n,_inf);
    f[(1<<n)-1]=0;
    for(auto&x:ok){
        cir(s,0,(1<<n)){
            f[s&x]=min(f[s&x],f[s]+1);
            f[s&((1<<n)^x)]=min(f[s&((1<<n)^x)],f[s]+1);
        }
    }
    cir(i,0,n) cout<<(f[(1<<i)]==_inf?-1:f[1<<i])<<' ';
    cout<<'\n';
    return 0;
}
