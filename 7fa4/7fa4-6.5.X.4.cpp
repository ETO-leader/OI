#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto maxc=307;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,k;cin>>n>>k;vector<vector<lint>> a(maxc);
    cir(i,0,n){
        int c;lint w;cin>>c>>w;
        a[c].push_back(w);
    }
    for(auto&i:a){
        sort(i.begin(),i.end(),greater<lint>());
        lint pre=0;
        for(auto&x:i) x=(pre+=x);
    }
    vector<lint> f(k+1);auto mx=0;
    cir(i,1,maxc) if(!a[i].empty()){
        for(int p=mx;~p;--p){
            auto pos=p;
            for(auto&w:a[i]){
                if((pos+=i)>k) break;
                if(f[p]+w>f[pos]) f[pos]=f[p]+w;
                else break;
            }
        }
        mx+=a[i].size()*i;
        mx=min(mx,k);
        cir(p,1,mx+1) f[p]=max(f[p],f[p-1]);
    }
    cir(i,1,k+1) cout<<f[i]<<' ';
    cout<<'\n';
    return 0;
}
