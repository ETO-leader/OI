#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class random_engine{
private:
    mt19937_64 eng;
public:
    auto randuint64(uint64_t l=0,uint64_t r=numeric_limits<uint64_t>::max()){
        return uniform_int_distribution<uint64_t>(l,r)(eng);
    }
    random_engine():eng(random_device().operator()()){}
} rnd;
using ulint=uint64_t;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;vector<ulint> val(n);
    for(auto&x:val) x=rnd.randuint64();
    vector<ulint> cur(n),rmv(n);
    const auto ans=accumulate(val.begin(),val.end(),0ull,[](auto a,auto b){return a+b;});
    auto curw=0ull;
    cir(i,0,m){
        int u,v;cin>>u>>v;--u;--v;
        cur[v]+=val[u];curw+=val[u];
    }
    int q;cin>>q;
    cir(i,0,q){
        int op;cin>>op;
        if(op==1){
            int u,v;cin>>u>>v;--u;--v;
            cur[v]-=val[u];rmv[v]+=val[u];
            curw-=val[u];
        }else if(op==2){
            int u;cin>>u;--u;
            rmv[u]+=cur[u];curw-=cur[u];
            cur[u]=0;
        }else if(op==3){
            int u,v;cin>>u>>v;--u;--v;
            cur[v]+=val[u];rmv[v]-=val[u];
            curw+=val[u];
        }else{
            int u;cin>>u;--u;
            cur[u]+=rmv[u];curw+=rmv[u];
            rmv[u]=0;
        }
        cout<<(curw==ans?"YES":"NO")<<'\n';
    }
    return 0;
}
