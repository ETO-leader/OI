#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,k,a,b,c;cin>>n>>k>>a>>b>>c;
    vector<int64_t> w(n);
    for(auto&i:w) cin>>i;
    vector<vector<int>> gr(n);
    vector<int> ban(n);
    cir(i,0,n) cir(j,i+1,n) if(abs(w[i]-w[j])==a||w[i]*b==w[j]||w[j]*b==w[i]||w[i]%c==w[j]%c) gr[i].emplace_back(j);
    auto ans=0;
    mt19937 eng(random_device().operator()());
    for(auto&x:gr) shuffle(x.begin(),x.end(),eng);
    cir(i,0,k){
        vector<int> f(n);
        for(auto j=n-1;~j;--j){
            f[j]=(!ban[j]);
            for(auto&v:gr[j]) f[j]=max(f[j],f[v]+(!ban[j]));
        }
        auto mx=max_element(f.begin(),f.end())-f.begin();
        auto u=(int)(mx);
        ans+=f[u];
        while(f[u]!=(!ban[u])){
            const auto uw=!ban[u];
            ban[u]=true;
            for(auto&v:gr[u]) if(f[v]+uw==f[u]){
                u=v;break;
            }
        }
        ban[u]=true;
    }
    cout<<ans<<'\n';
    return 0;
}
