#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=(int)(1e9+7);
class mathbase{
private:
    vector<vector<lint>> c;
public:
    auto registermath(int n){
        c.resize(n,vector<lint>(n));
        c[0][0]=1;
        cir(i,1,n) cir(j,0,n){
            c[i][j]=c[i-1][j];
            if(j) (c[i][j]+=c[i-1][j-1])%=MOD;
        }
    }
    auto C(int a,int b){return c[a][b];}
} math;
class node{
private:
    int n,x,y,xl,yl;
    vector<vector<lint>> a;
public:
    auto&operator[](size_t p){return a[p];}
    auto&nx(){return x;}
    auto&ny(){return y;}
    auto operator*(node b) const{
        auto res=node(n,xl,yl);
        res.x=(x+b.x)%MOD;
        res.y=(y+b.y)%MOD;
        res.a=a;
        cir(i,0,xl+1) cir(j,0,yl+1){
            auto ax=1ll;
            for(auto c=0;c<i+1;++c,(ax*=x)%=MOD){
                auto ay=1ll;
                for(auto d=0;d<j+1;++d,(ay*=y)%=MOD){
                    (res[i][j]+=math.C(i,c)*math.C(j,d)%MOD*ax%MOD*ay%MOD*b[i-c][j-d])%=MOD;
                }
            }
        }
        return res;
    }
    auto pow(lint k){
        auto res=node(n,xl,yl),pw=*this;
        while(k){
            if(k&1) res=res*pw;
            pw=pw*pw;k>>=1;
        }
        return res;
    }
    node(int _n,int _xl,int _yl):n(_n),x(0),y(0),xl(_xl),yl(_yl),a(_n,vector<lint>(_n)){}
};
class calculator{
public:
    static const auto f(lint a,lint b,lint c,lint n,node un,node rn){
        const auto m=(a*n+b)/c;
        if(!m) return rn.pow(n);
        if(a>c-1) return f(a%c,b,c,n,un,un.pow(a/c)*rn);
        return rn.pow((c-b-1)/a)*un*f(c,(c-b-1)%a,a,m-1,rn,un)*rn.pow(n-(m*c-b-1)/a);
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    math.registermath(17);
    while(T--) [&](){
        lint n,a,b,c;int xl,yl;cin>>n>>a>>b>>c>>yl>>xl;
        auto rn=node(max(xl,yl)+3,xl,yl),un=node(max(xl,yl)+3,xl,yl);
        rn.ny()=1;un.nx()=1;
        fill(rn[0].begin(),rn[0].begin()+yl+1,1);
        auto ans=node(max(xl,yl)+3,xl,yl);
        ans.nx()=b/c;
        auto prod=1ll;
        for(auto i=0;i<xl+1;++i,(prod*=ans.nx())%=MOD){
            ans[i][0]=prod;
        }
        cout<<(ans*calculator::f(a,b%c,c,n,un,rn))[xl][yl]<<'\n';
    }();
    return 0;
}
