#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("sail.in");
ofstream fcout("sail.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
using lint=long long;
static constexpr auto MOD=998244353;
class mathbase{
public:
    constexpr auto qpow(lint a,auto b) const{
        auto res=1ll;
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    constexpr auto inv(auto x) const{return qpow(x,MOD-2);}
} math;
auto gauss(vector<vector<lint>> a){
    const auto n=(int)(a.size());
    cir(i,0,n){
        auto p=i;
        while(p<(int)(a.size())&&(!(a[p][i]))) ++p;
        if(p==(int)(a.size())) continue;
        swap(a[i],a[p]);
        cir(x,i+1,n) if(a[x][i]){
            const auto w=a[x][i]*math.inv(a[i][i])%MOD;
            cir(j,i,n+1) (a[x][j]+=MOD-w*a[i][j]%MOD)%=MOD;
        }
    }
    vector<lint> ans(n);
    for(auto i=n-1;~i;--i) if(a[i][i]){
        auto cur=(lint)(a[i][n]);
        cir(j,i+1,n) (cur+=MOD-ans[j]*a[i][j]%MOD)%=MOD;
        ans[i]=cur*math.inv(a[i][i])%MOD;
    }
    return ans;
}
int main(){
    ios::sync_with_stdio(false),fcin.tie(nullptr);
    int n;fcin>>n;vector<lint> p(n);
    for(auto&i:p) fcin>>i,(i*=math.inv(100))%=MOD;
    const auto sec=(int)(sqrtl(n)*1.5);
    vector f(n,vector(n+1,vector<lint>(sec*2+7)));
    cir(i,0,n) f[i][i][sec]=1;
    for(auto i=n-1;~i;--i) cir(w,1,sec+1){
        f[i][n][w+sec]=1;
        cir(k,0,n+1) (f[i][k][w+sec]+=(i+w-1<n?f[i+w-1][k][w-1+sec]:0)*p[i])%=MOD;
        cir(k,0,n+1) (f[i][k][w+sec]+=(i+w+1<n&&w<sec?f[i+w+1][k][w+1+sec]:0)*(MOD+1-p[i]))%=MOD;
    }
    cir(i,0,n) cir(w,-sec,0){
        f[i][n][w+sec]=1;
        cir(k,0,n+1) (f[i][k][w+sec]+=(i+w-1>-1&&-w<sec?f[i+w-1][k][w-1+sec]:0)*p[i])%=MOD;
        cir(k,0,n+1) (f[i][k][w+sec]+=(i+w+1>-1?f[i+w+1][k][w+1+sec]:0)*(MOD+1-p[i]))%=MOD;
    }
    vector g(n,vector<lint>(n+1));
    cir(i,0,n){
        g[i][i]=MOD-1;g[i][n]=1;
		if(i) cir(w,0,n+1) (g[i][w]+=p[i]*f[i-1][w][-1+sec])%=MOD;
		if(i<n-1) cir(w,0,n+1) (g[i][w]+=(MOD+1-p[i])*f[i+1][w][1+sec])%=MOD;
        g[i][n]=(MOD-g[i][n])%MOD;
    }
    const auto ans=gauss(g);
    vector<unordered_set<int>> vis(n);
    auto chkvaild=[&](auto __self,int u,int v)->bool {
        if(u<0||u>n-1||p[u]>1) return true;
        if(vis[u].count(v)) return false;
        vis[u].insert(v);
        if(p[u]) return __self(__self,u+(v-1),v-1);
        return __self(__self,u+v+1,v+1);
    };
    cir(i,0,n){
        for(auto&i:vis) i.clear();
        fcout<<(chkvaild(chkvaild,i,0)?ans[i]:-1)<<' ';
    }
    fcout<<'\n';
    return 0;
}
