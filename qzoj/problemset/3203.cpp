#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto MOD=998244353;
template<const int v>
class gcd_base{
private:
    vector<vector<int>> g;
    static constexpr auto sqr=(int)(sqrt(v)+7);
    vector<int> a,b,c,mnp;
    auto init(){
        vector<int> p;
        vector<int> vis(v);
        iota(mnp.begin(),mnp.end(),0);
        cir(i,2,v){
            if(!vis[i]) p.emplace_back(i);
            for(auto&x:p){
                if(i*x>v-1) break;
                vis[i*x]=true;
                mnp[i*x]=min({mnp[i*x],mnp[i],mnp[x]});
                if(!(i%x)) break;
            }
            const auto fr=i/mnp[i];
            a[i]=a[fr];
            b[i]=b[fr];
            c[i]=c[fr];
            if(a[i]==1||a[i]*mnp[i]<sqr) a[i]*=mnp[i];
            else if(b[i]==1||b[i]*mnp[i]<sqr) b[i]*=mnp[i];
            else c[i]*=mnp[i];
        }
        cir(i,1,sqr) g[i][1]=g[1][i]=1;
        cir(i,0,sqr) g[i][0]=g[0][i]=i;
        cir(i,1,sqr) cir(j,1,sqr){
            g[i][j]=g[i][j/mnp[j]];
            if(!((i/g[i][j])%mnp[j])) g[i][j]*=mnp[j];
        }
    }
public:
    constexpr auto gcd(int x,int y) const{
        auto res=1;
        if(a[x]>sqr-1) res*=((!(y%a[x]))?a[x]:1);
        else res*=g[a[x]][y%a[x]];
        if(b[x]>sqr-1) res*=((!((y/res)%b[x]))?b[x]:1);
        else res*=g[b[x]][(y/res)%b[x]];
        if(c[x]>sqr-1) res*=((!((y/res)%c[x]))?c[x]:1);
        else res*=g[c[x]][(y/res)%c[x]];
        return res;
    }
    gcd_base():g(sqr,vector<int>(sqr)),a(v,1),b(v,1),c(v,1),mnp(v){init();}
};
class binary_gcd{
public:
    constexpr auto gcd(uint x,uint y) const{
        auto c=0;
        while(x>1){
            const auto vx=__builtin_ctz(x);
            const auto vy=__builtin_ctz(y);
            c+=min(vx,vy);
            x>>vx;y>>=vy;
            tie(x,y)=minmax({x,y});
            y-=x;
            tie(x,y)=minmax({x,y});
        }
        return (x==1?1:y)<<c;
    }
};
static constexpr auto maxv=(int)(1e6+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    // gcd_base<maxv> math;
    binary_gcd math;
    vector<int> a(n),b(n);
    for(auto&i:a) cin>>i;
    for(auto&i:b) cin>>i;
    cir(i,0,n){
        auto ans=0ll,pw=1ll;
        cir(j,0,n){
            (pw*=(i+1))%=MOD;
            (ans+=pw*math.gcd(a[i],b[j]))%=MOD;
        }
        cout<<ans<<'\n';
    }
    return 0;
}
