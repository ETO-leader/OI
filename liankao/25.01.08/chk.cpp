#include<bits/stdc++.h>
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
#define N 3
int main(){
    ios::sync_with_stdio(false);
    mt19937 rnd(251);
    vector<pair<int,int>> E={{0,1},{1,0},{1,2},{2,1}};
    auto px=0.0l;
    auto cnt=0ll;
    while(true){
        ++cnt;
        vector<int> c(N);
        vector p(N,vector<int>(N));
        auto w=0;
        c[0]=1;
        while(ranges::count(c,0)){
            ++w;
            for(auto&[u,v]:E) p[u][v]=rnd()&1;
            cir(x,0,5){
                cir(u,0,N) cir(v,0,N) if(p[u][v]) c[v]|=c[u];
            }
        }
        cerr<<"w = "<<w<<'\n';
        ((px*=cnt)+=w)/=(cnt+1);
        cerr<<"EXPECT: "<<px<<'\n';
    }
    return 0;
}
