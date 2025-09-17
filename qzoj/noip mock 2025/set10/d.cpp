#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=(int)(1e7+7);
class dp{
private:
    lint a,b;
    vector<array<array<lint,2>,2>> f,g;
    vector<array<array<bool,2>,2>> vis;
    auto calc(int x,bool la,bool lb){
        if(!(~x)) return make_pair(0ll,1ll);
        if(vis[x][la][lb]) return make_pair(f[x][la][lb],g[x][la][lb]);
        vis[x][la][lb]=true;
        const auto va=(la?((a>>x)&1):1);
        const auto vb=(lb?((b>>x)&1):1);
        cir(i,0,va+1) cir(j,0,vb+1){
            const auto[nf,ng]=calc(x-1,la&&(i==va),lb&&(j==vb));
            (f[x][la][lb]+=nf+(((lint)(i)^j)<<x)%MOD*ng)%=MOD;
            (g[x][la][lb]+=ng)%=MOD;
        }
        return make_pair(f[x][la][lb],g[x][la][lb]);
    }
public:
    auto calc(){
        if(a<0||b<0) return 0ll;
        return calc(60,true,true).first;
    }
    dp(auto _a,auto _b):a(_a),b(_b),f(63),g(63),vis(63){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        lint a,b,c,d;cin>>a>>b>>c>>d;
        cout<<(
            dp(b,d).calc()+MOD-
            dp(a-1,d).calc()+MOD-
            dp(b,c-1).calc()+
            dp(a-1,c-1).calc()
        )%MOD<<'\n';
    }();
    return 0;
}
