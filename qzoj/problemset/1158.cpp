#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=5557;
class matrix{
private:
    vector<vector<lint>> a;
    auto I() const{
        auto res=matrix(a.size());
        cir(i,0,(int)(a.size())) res.a[i][i]=1;
        return res;
    }
public:
    vector<lint>&operator[](auto p){return a[p];}
    const vector<lint>&operator[](auto p) const{return a[p];}
    auto operator*(const matrix x) const{
        auto res=matrix(a.size());
        const auto n=(int)(a.size());
        cir(k,0,n) cir(i,0,n) cir(j,0,n){
            (res[i][j]+=a[i][k]*x[k][j])%=MOD;
        }
        return res;
    }
    auto pow(auto b) const{
        auto res=I(),pw=*this;
        while(b){
            if(b&1) res=res*pw;
            pw=pw*pw;b>>=1;
        }
        return res;
    }
    matrix(auto _n):a(_n,vector<lint>(_n)){}
};
static const auto str=(string)("BJMP");
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;
    vector<matrix> g(1<<4,matrix((n<<1)+1));
    cir(i,0,m){
        int u,v;string s;cin>>u>>v>>s;--u;--v;
        auto st=0;
        for(auto&i:s) st|=(1<<str.find(i));
        cir(ns,0,(1<<4)){
            if(!(ns&st)) ++g[ns][u<<1][(v<<1)|1];
            ++g[ns][u<<1][v<<1];
        }
    }
    int k;cin>>k;
    cir(s,0,(1<<4)) cir(i,0,n) g[s][(i<<1)|1][i<<1]=1;
    cir(s,0,(1<<4)) g[s][0][n<<1]=1,g[s][n<<1][n<<1]=1;
    auto ans=0ll;
    cir(s,0,(1<<4)){
        const auto c=g[s].pow(k+1)[0][n<<1];
        (ans+=c*(__builtin_popcount(s)&1?MOD-1:1))%=MOD;
    }
    cout<<ans<<'\n';
    return 0;
}
