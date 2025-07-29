#include<bits/stdc++.h>
#include<tr2/dynamic_bitset>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=998244353;
class mathbase{
public:
    constexpr auto qpow(lint a,auto b){
        auto res=1ll;
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    constexpr auto inv(auto x){return qpow(x,MOD-2);}
} math;
class base{
private:
    vector<pair<tr2::dynamic_bitset<uint64_t>,int>> a;
    vector<int> vis;
public:
    auto emplace(tr2::dynamic_bitset<uint64_t> x,int w){
        cir(i,0,(int)(vis.size())) if(x.test(i)){
            if(!vis[i]){
                a[i]=pair(x,w);
                vis[i]=true;
                return true;
            }
            x^=a[i].first;
            w^=a[i].second;
        }
        return !w;
    }
    auto rank(){return ranges::count(vis,true);}
    base(int _n):a(_n),vis(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    auto T=1;
    while(T--) []{
        lint n,m,k;cin>>n>>m>>k;
        if(n*m<(int)(1e4)){
            base bs(n*m);
            vector id(n,vector<int>(m));
            for(auto c=-1;auto&x:id) for(auto&i:x) i=++c;
            cir(i,0,n){
                tr2::dynamic_bitset<uint64_t> ins(n*m);
                cir(j,0,m) ins.set(id[i][j]);
                if(!bs.emplace(ins,1)) return cout<<'0'<<'\n',void();
            }
            cir(j,0,m){
                tr2::dynamic_bitset<uint64_t> ins(n*m);
                cir(i,0,n) ins.set(id[i][j]);
                if(!bs.emplace(ins,1)) return cout<<'0'<<'\n',void();
            }
            cir(i,0,k){
                int x,y,w;cin>>x>>y>>w;--x;--y;
                tr2::dynamic_bitset<uint64_t> ins(n*m);
                ins.set(id[x][y]);
                if(!bs.emplace(ins,w)) return cout<<'0'<<'\n',void(); 
            }
            cout<<math.qpow(2,n*m-bs.rank())<<'\n';
        }else{
            cout<<math.qpow(2,(n-1)*(m-1)-k)<<'\n';
        }
    }();
    return 0;
}
